/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/pizza/test.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

// --- Internal helper for timing ---
static uint64_t fossil_pizza_now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

// --- Start ---
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    pizza_sys_memory_set(engine, 0, sizeof(*engine));
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Suite ---
int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    if (engine->count >= engine->capacity) {
        size_t new_cap = engine->capacity ? engine->capacity * 2 : 4;
        fossil_pizza_suite_t* resized = pizza_sys_memory_realloc(engine->suites, new_cap * sizeof(*resized));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        engine->suites = resized;
        engine->capacity = new_cap;
    }
    engine->suites[engine->count++] = suite;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Case ---
int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;
    if (suite->count >= suite->capacity) {
        size_t new_cap = suite->capacity ? suite->capacity * 2 : 4;
        fossil_pizza_case_t* resized = pizza_sys_memory_realloc(suite->cases, new_cap * sizeof(*resized));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        suite->cases = resized;
        suite->capacity = new_cap;
    }
    suite->cases[suite->count++] = test_case;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Run One Suite ---
int fossil_pizza_run_suite(fossil_pizza_suite_t* suite) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;
    if (suite->setup) suite->setup();

    suite->time_elapsed_ns = fossil_pizza_now_ns();
    suite->total_score = 0;
    suite->total_possible = 0;
    pizza_sys_memory_set(&suite->score, 0, sizeof(suite->score));

    for (size_t i = 0; i < suite->count; ++i) {
        fossil_pizza_case_t* test_case = &suite->cases[i];
        if (test_case->setup) test_case->setup();

        uint64_t start_time = fossil_pizza_now_ns();
        if (test_case->run) {
            test_case->run();
            test_case->result = FOSSIL_PIZZA_CASE_PASS;
        } else {
            test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
        }
        test_case->elapsed_ns = fossil_pizza_now_ns() - start_time;

        // Update scores based on result
        switch (test_case->result) {
            case FOSSIL_PIZZA_CASE_PASS:
                suite->score.passed++;
                suite->total_score++;
                break;
            case FOSSIL_PIZZA_CASE_FAIL:
                suite->score.failed++;
                break;
            case FOSSIL_PIZZA_CASE_TIMEOUT:
                suite->score.timeout++;
                break;
            case FOSSIL_PIZZA_CASE_SKIPPED:
                suite->score.skipped++;
                break;
            case FOSSIL_PIZZA_CASE_UNEXPECTED:
                suite->score.unexpected++;
                break;
            case FOSSIL_PIZZA_CASE_EMPTY:
            default:
                suite->score.empty++;
                break;
        }
        suite->total_possible++;

        if (test_case->teardown) test_case->teardown();
    }

    suite->time_elapsed_ns = fossil_pizza_now_ns() - suite->time_elapsed_ns;

    if (suite->teardown) suite->teardown();
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Run All Suites ---
int fossil_pizza_run_all(fossil_pizza_engine_t* engine) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));
    engine->score_total = 0;
    engine->score_possible = 0;

    for (size_t i = 0; i < engine->count; ++i) {
        fossil_pizza_run_suite(&engine->suites[i]);

        engine->score_total += engine->suites[i].total_score;
        engine->score_possible += engine->suites[i].total_possible;

        // aggregate suite scores
        fossil_pizza_score_t* src = &engine->suites[i].score;
        engine->score.passed     += src->passed;
        engine->score.failed     += src->failed;
        engine->score.skipped    += src->skipped;
        engine->score.timeout    += src->timeout;
        engine->score.unexpected += src->unexpected;
        engine->score.empty      += src->empty;
    }
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Summary Report ---
void fossil_pizza_summary(const fossil_pizza_engine_t* engine) {
    if (!engine) return;
    pizza_io_printf("{blue}\n=== Fossil Pizza Test Summary ==={reset}\n");
    pizza_io_printf("{blue}Suites run:{cyan} %zu\n{reset}", engine->count);
    pizza_io_printf("{blue}Total:{cyan} %d  {blue}Passed:{cyan} %d  {blue}Failed:{cyan} %d  {blue}Skipped:{cyan} %d\n{reset}", engine->score_possible, engine->score.passed, engine->score.failed, engine->score.skipped);
    pizza_io_printf("{blue}Timeouts:{cyan} %d  {blue}Unexpected:{cyan} %d  {blue}Empty:{cyan} %d\n{reset}", engine->score.timeout, engine->score.unexpected, engine->score.empty);
    pizza_io_printf("{blue}Score:{cyan} %d/%d\n{reset}", engine->score_total, engine->score_possible);
}

// --- End / Cleanup ---
int32_t fossil_pizza_end(fossil_pizza_engine_t* engine) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    for (size_t i = 0; i < engine->count; ++i) {
        fossil_pizza_suite_t* suite = &engine->suites[i];
        if (suite->cases) {
            for (size_t j = 0; j < suite->count; ++j) {
                fossil_pizza_case_t* test_case = &suite->cases[j];
                if (test_case->teardown) {
                    test_case->teardown();
                }
            }
            pizza_sys_memory_free(suite->cases);
        }
    }
    pizza_sys_memory_free(engine->suites);
    return FOSSIL_PIZZA_SUCCESS;
}
