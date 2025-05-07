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
#include <unistd.h>
#include <setjmp.h>
#include <stdio.h>
#include <time.h>

jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp
static int _ASSERT_COUNT = 0; // Counter for the number of assertions

// --- Internal helper for timing ---
static uint64_t fossil_pizza_now_ns(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000000ULL + (uint64_t)tv.tv_usec * 1000ULL;
}

// --- Start ---
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv) {
    if (!engine || !argv) return FOSSIL_PIZZA_FAILURE;

    pizza_sys_memory_set(engine, 0, sizeof(*engine));
    engine->suites = NULL;
    engine->count = 0;
    engine->capacity = 0;
    engine->score_total = 0;
    engine->score_possible = 0;
    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));

    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Suite ---
int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    if (engine->count >= engine->capacity) {
        size_t new_cap = engine->capacity ? engine->capacity * 2 : 4;
        fossil_pizza_suite_t* resized = pizza_sys_memory_realloc(engine->suites, new_cap * sizeof(*engine->suites));
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
        fossil_pizza_case_t* resized = pizza_sys_memory_realloc(suite->cases, new_cap * sizeof(*suite->cases));
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

    if (!suite->cases) return FOSSIL_PIZZA_FAILURE;
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
        if (&engine->suites[i] == NULL) continue;

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
    pizza_io_printf("{blue}================================={reset}\n");
    pizza_io_printf("{blue}=== Fossil Pizza Test Summary ==={reset}\n");
    pizza_io_printf("{blue}================================={reset}\n");
    pizza_io_printf("{blue}Suites run:{cyan} %4zu\n{reset}", engine->count);
    pizza_io_printf("{blue}Total     :{cyan} %4d\n{reset}", engine->score_possible);
    pizza_io_printf("{blue}Passed    :{cyan} %4d\n{reset}", engine->score.passed);
    pizza_io_printf("{blue}Failed    :{cyan} %4d\n{reset}", engine->score.failed);
    pizza_io_printf("{blue}Skipped   :{cyan} %4d\n{reset}", engine->score.skipped);
    pizza_io_printf("{blue}Timeouts  :{cyan} %4d\n{reset}", engine->score.timeout);
    pizza_io_printf("{blue}Unexpected:{cyan} %4d\n{reset}", engine->score.unexpected);
    pizza_io_printf("{blue}Empty     :{cyan} %4d\n{reset}", engine->score.empty);
    pizza_io_printf("{blue}\nScore:{cyan} %d/%d\n{reset}", engine->score_total, engine->score_possible);
    pizza_io_printf("{blue}\n================================={reset}\n");
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

// -- Assume --

/**
 * @brief Internal function to handle assertions with anomaly detection.
 * 
 * This function is used internally by the test framework to handle assertions
 * and detect duplicate assertions. It is not intended to be called directly.
 * 
 * @param condition The condition to check.
 * @param message The message to display if the condition is false.
 * @param file The file name where the assertion occurred.
 * @param line The line number where the assertion occurred.
 * @param func The function name where the assertion occurred.
 */

void pizza_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
    static const char *last_message = NULL; // Store the last assertion message
    static const char *last_file = NULL;    // Store the last file name
    static int last_line = 0;               // Store the last line number
    static const char *last_func = NULL;    // Store the last function name
    static int anomaly_count = 0;           // Counter for anomaly detection

    _ASSERT_COUNT++; // Increment the assertion count

    if (!condition) {
        // Check if the current assertion is the same or similar to the last one
        if (last_message && strstr(message, last_message) != NULL &&
            last_file && strcmp(last_file, file) == 0 &&
            last_line == line &&
            last_func && strcmp(last_func, func) == 0) {
            anomaly_count++;
            pizza_io_printf("{yellow}Duplicate or similar assertion detected: %s (%s:%d in %s) [Anomaly Count: %d]{reset}\n",
                                 message, file, line, func, anomaly_count);
        } else {
            anomaly_count = 0; // Reset anomaly count for new assertion
            last_message = message;
            last_file = file;
            last_line = line;
            last_func = func;
            pizza_io_printf("{red}Assertion failed: %s (%s:%d in %s){reset}\n", message, file, line, func);
        }

        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}
