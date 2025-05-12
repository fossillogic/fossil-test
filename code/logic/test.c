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
#include <sys/time.h>

jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp
static int _ASSERT_COUNT = 0; // Counter for the number of assertions

// --- Internal helper for timing ---
static uint64_t fossil_pizza_now_ns(void) {
    struct timeval tv;
    gettimeofday(&tv, null);
    return (uint64_t)tv.tv_sec * 1000000000ULL + (uint64_t)tv.tv_usec * 1000ULL;
}

// --- Start ---
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv) {
    if (!engine || !argv) return FOSSIL_PIZZA_FAILURE;

    pizza_sys_memory_set(engine, 0, sizeof(*engine));
    engine->suites = null;
    engine->count = 0;
    engine->capacity = 0;
    engine->score_total = 0;
    engine->score_possible = 0;
    engine->pallet = fossil_pizza_pallet_create(argc, argv);
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

// --- Update Score ---
void fossil_pizza_update_score(fossil_pizza_case_t* test_case, fossil_pizza_suite_t* suite) {
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
}

// --- Run One Test ---
void fossil_pizza_test_output(const fossil_pizza_case_t* test_case) {
    if (!test_case) return;

    const char* result_str = 
        (test_case->result == FOSSIL_PIZZA_CASE_PASS) ? "PASS" :
        (test_case->result == FOSSIL_PIZZA_CASE_FAIL) ? "FAIL" :
        (test_case->result == FOSSIL_PIZZA_CASE_EMPTY) ? "EMPTY" : "UNKNOWN";

    switch (G_PIZZA_THEME) {
        case PIZZA_THEME_FOSSIL:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{blue}Test Case:{reset} %s | {green}Result:{reset} %s | {yellow}Time:{reset} %llu ns\n",
                test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{blue}========================================{reset}\n");
            pizza_io_printf("{cyan}Test Case:{reset} %s\n", test_case->name);
            pizza_io_printf("{cyan}Given Result:{reset} %s\n", result_str);
            pizza_io_printf("{cyan}With Timestamp:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{blue}========================================{reset}\n");
            }
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{cyan}Test Case:{reset} %s | {green}Result:{reset} %s | {yellow}Time:{reset} %llu ns\n",
            test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{cyan}========================================{reset}\n");
            pizza_io_printf("{cyan}Test Case:{reset} %s\n", test_case->name);
            pizza_io_printf("{cyan}Given Result:{reset} %s\n", result_str);
            pizza_io_printf("{cyan}With Timestamp:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{cyan}========================================{reset}\n");
            }
            break;

        case PIZZA_THEME_CPPUTEST:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{blue}[TEST CASE]{reset} %s | {green}[RESULT]{reset} %s | {yellow}[TIME]{reset} %llu ns\n",
            test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{blue}[========================================]{reset}\n");
            pizza_io_printf("{blue}[Test Case]:{reset} %s\n", test_case->name);
            pizza_io_printf("{blue}[Given Result]:{reset} %s\n", result_str);
            pizza_io_printf("{blue}[With Timestamp]:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{blue}[========================================]{reset}\n");
            }
            break;

        case PIZZA_THEME_TAP:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{green}ok - Test Case:{reset} %s | {green}Result:{reset} %s | {yellow}Time:{reset} %llu ns\n",
            test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{green}# ========================================{reset}\n");
            pizza_io_printf("{green}# Test Case:{reset} %s\n", test_case->name);
            pizza_io_printf("{green}# Given Result:{reset} %s\n", result_str);
            pizza_io_printf("{green}# With Timestamp:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{green}# ========================================{reset}\n");
            }
            break;

        case PIZZA_THEME_GOOGLETEST:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{blue}[ RUN      ]{reset} %s\n", test_case->name);
            pizza_io_printf("{green}[       %s ]{reset} %s ({yellow}%llu ns{reset})\n", result_str, test_case->name, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{blue}[========================================]{reset}\n");
            pizza_io_printf("{blue}[Test Case]:{reset} %s\n", test_case->name);
            pizza_io_printf("{blue}[Given Result]:{reset} %s\n", result_str);
            pizza_io_printf("{blue}[With Timestamp]:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{blue}[========================================]{reset}\n");
            }
            break;

        case PIZZA_THEME_UNITY:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{magenta}Unity Test Case:{reset} %s | {green}Result:{reset} %s | {yellow}Time:{reset} %llu ns\n",
            test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{magenta}========================================{reset}\n");
            pizza_io_printf("{magenta}Test Case:{reset} %s\n", test_case->name);
            pizza_io_printf("{magenta}Given Result:{reset} %s\n", result_str);
            pizza_io_printf("{magenta}With Timestamp:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{magenta}========================================{reset}\n");
            }
            break;

        default:
            if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_PLAIN) {
            pizza_io_printf("{cyan}Test Case:{reset} %s | {green}Result:{reset} %s | {yellow}Time:{reset} %llu ns\n",
            test_case->name, result_str, test_case->elapsed_ns);
            } else if (G_PIZZA_VERBOSE == PIZZA_VERBOSE_DOGE) {
            pizza_io_printf("{cyan}========================================{reset}\n");
            pizza_io_printf("{cyan}Test Case:{reset} %s\n", test_case->name);
            pizza_io_printf("{cyan}Given Result:{reset} %s\n", result_str);
            pizza_io_printf("{cyan}With Timestamp:{reset} %llu ns\n", test_case->elapsed_ns);
            pizza_io_printf("{cyan}========================================{reset}\n");
            }
            break;
    }
}

void fossil_pizza_run_test(const fossil_pizza_engine_t* engine, fossil_pizza_case_t* test_case, fossil_pizza_suite_t* suite) {
    if (!test_case || !suite) return;

    if (test_case->result != FOSSIL_PIZZA_CASE_SKIPPED) {
        // Check if the test case name matches the --only filter
        if (engine->pallet.run.only && pizza_io_cstr_compare(engine->pallet.run.only, test_case->name) != 0) {
            return;
        }

        for (int i = 0; i < (engine->pallet.run.repeat ? engine->pallet.run.repeat : 1); ++i) {
            if (test_case->setup) test_case->setup();

            uint64_t start_time = fossil_pizza_now_ns();

            if (test_case->run) {
                if (setjmp(test_jump_buffer) == 0) {
                    test_case->run();
                    uint64_t elapsed_time = fossil_pizza_now_ns() - start_time;

                    if (1000000ULL > 0 && elapsed_time > 1000000ULL) {
                        test_case->result = FOSSIL_PIZZA_CASE_TIMEOUT;
                    } else {
                        test_case->result = FOSSIL_PIZZA_CASE_PASS;
                    }
                } else {
                    test_case->result = FOSSIL_PIZZA_CASE_FAIL;
                    if (engine->pallet.run.fail_fast) {
                        fossil_pizza_test_output(test_case);
                        return; // Exit immediately if --fail-fast is enabled
                    }
                }
            } else {
                test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
            }
            test_case->elapsed_ns = fossil_pizza_now_ns() - start_time;

            if (test_case->teardown) test_case->teardown();
        }

        // Output test case result
        fossil_pizza_test_output(test_case);
    } else {
        // Handle unexpected cases
        test_case->result = FOSSIL_PIZZA_CASE_UNEXPECTED;
        fossil_pizza_test_output(test_case);
    }

    // Update scores based on result
    fossil_pizza_update_score(test_case, suite);
    _ASSERT_COUNT = 0; // Reset the assertion count for the next test case
}

// --- Algorithmic modifications ---

// --- Sorting Test Cases ---
static int compare_name_asc(const void* a, const void* b) {
    return pizza_io_cstr_compare(((fossil_pizza_case_t*)a)->name, ((fossil_pizza_case_t*)b)->name);
}

static int compare_name_desc(const void* a, const void* b) {
    return pizza_io_cstr_compare(((fossil_pizza_case_t*)b)->name, ((fossil_pizza_case_t*)a)->name);
}

static int compare_result_asc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)a)->result - ((fossil_pizza_case_t*)b)->result;
}

static int compare_result_desc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)b)->result - ((fossil_pizza_case_t*)a)->result;
}

static int compare_time_asc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)a)->elapsed_ns - ((fossil_pizza_case_t*)b)->elapsed_ns;
}

static int compare_time_desc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)b)->elapsed_ns - ((fossil_pizza_case_t*)a)->elapsed_ns;
}

void fossil_pizza_sort_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases || suite->count <= 1 || !engine) return;

    int (*compare)(const void*, const void*) = null;

    if (engine->pallet.sort.by) {
        if (pizza_io_cstr_compare(engine->pallet.sort.by, "name") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_name_desc : compare_name_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "result") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_result_desc : compare_result_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "time") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_time_desc : compare_time_asc;
        } else {
            // Invalid sort criteria
            return;
        }
    }

    if (engine->pallet.sort.order) {
        if (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) {
            compare = (compare == compare_name_asc) ? compare_name_desc : compare;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.order, "asc") == 0) {
            compare = (compare == compare_name_desc) ? compare_name_asc : compare;
        }
    }

    if (compare) {
        qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare);
    }
}

// --- Filtering Test Cases ---
size_t fossil_pizza_filter_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine, fossil_pizza_case_t** filtered_cases) {
    if (!suite || !suite->cases || !filtered_cases || !engine) return 0;

    size_t count = 0;
    for (size_t i = 0; i < suite->count; ++i) {
        fossil_pizza_case_t* test_case = &suite->cases[i];

        // Apply filters based on engine->pallet.filter
        if (engine->pallet.filter.test_name && pizza_io_cstr_compare(test_case->name, engine->pallet.filter.test_name) != 0) {
            continue;
        }
        if (engine->pallet.filter.suite_name && pizza_io_cstr_compare(suite->suite_name, engine->pallet.filter.suite_name) != 0) {
            continue;
        }
        if (engine->pallet.filter.tag && (!test_case->tags || !strstr(test_case->tags, engine->pallet.filter.tag))) {
            continue;
        }

        filtered_cases[count++] = test_case;
    }
    return count;
}

// --- Shuffling Test Cases ---
void fossil_pizza_shuffle_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases || suite->count < 2) return;

    unsigned int seed = (engine && engine->pallet.shuffle.seed) 
                        ? (unsigned int)atoi(engine->pallet.shuffle.seed) 
                        : (unsigned int)time(null);
    srand(seed);

    for (size_t i = suite->count - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        fossil_pizza_case_t temp = suite->cases[i];
        suite->cases[i] = suite->cases[j];
        suite->cases[j] = temp;
    }

    if (engine && engine->pallet.shuffle.by) {
        if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "name") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), 
                  (int (*)(const void*, const void*))pizza_io_cstr_compare);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "result") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_result_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "time") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_time_asc);
        }
    }
}

// --- Run One Suite ---
int fossil_pizza_run_suite(const fossil_pizza_engine_t* engine, fossil_pizza_suite_t* suite) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;
    if (suite->setup) suite->setup();

    suite->time_elapsed_ns = fossil_pizza_now_ns();
    suite->total_score = 0;
    suite->total_possible = 0;
    pizza_sys_memory_set(&suite->score, 0, sizeof(suite->score));

    if (!suite->cases) return FOSSIL_PIZZA_FAILURE;

    // Apply filtering, sorting, and shuffling
    fossil_pizza_case_t* filtered_cases[suite->count];
    size_t filtered_count = fossil_pizza_filter_cases(suite, engine, filtered_cases);

    if (filtered_count > 0) {
        fossil_pizza_sort_cases(suite, engine);
        fossil_pizza_shuffle_cases(suite, engine);

        for (size_t i = 0; i < filtered_count; ++i) {
            fossil_pizza_case_t* test_case = filtered_cases[i];
            fossil_pizza_run_test(engine, test_case, suite);
        }
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
        fossil_pizza_run_suite(engine, &engine->suites[i]);

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
void fossil_pizza_summary_timestamp(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    uint64_t total_elapsed_ns = 0;
    for (size_t i = 0; i < engine->count; ++i) {
        total_elapsed_ns += engine->suites[i].time_elapsed_ns;
    }

    uint64_t total_elapsed_us = total_elapsed_ns / 1000;
    uint64_t total_elapsed_ms = total_elapsed_us / 1000;
    uint64_t total_elapsed_s = total_elapsed_ms / 1000;
    uint64_t minutes = total_elapsed_s / 60;
    uint64_t seconds = total_elapsed_s % 60;
    uint64_t microseconds = total_elapsed_us % 1000;
    uint64_t nanoseconds = total_elapsed_ns % 1000;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}\n========================================================================={reset}\n");
            pizza_io_printf("{blue,bold}Elapsed Time:{white} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n{reset}",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("\n=========================================================================\n");
            pizza_io_printf("Elapsed Time: %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("\n=========================================================================\n");
            pizza_io_printf("[Elapsed Time]: %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("\n# Elapsed Time: %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] Elapsed Time: %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Test Elapsed Time\n");
            pizza_io_printf("Minutes: %llu, Seconds: %llu, Microseconds: %llu, Nanoseconds: %llu\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display elapsed time.\n");
            break;
    }

    // Calculate averages
    double avg_time_per_suite_ns = (engine->count > 0) ? (double)total_elapsed_ns / engine->count : 0;
    double avg_time_per_test_ns = (engine->score_possible > 0) ? (double)total_elapsed_ns / engine->score_possible : 0;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Average Time per Suite:{white} %.2f nanoseconds\n{reset}", avg_time_per_suite_ns);
            pizza_io_printf("{blue,bold}Average Time per Test :{white} %.2f nanoseconds\n{reset}", avg_time_per_test_ns);
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[Average Time per Suite]: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("[Average Time per Test ]: %.2f nanoseconds\n", avg_time_per_test_ns);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("# Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("# Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[----------] Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("[----------] Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display average times.\n");
            break;
    }
}

void fossil_pizza_summary_scoreboard(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    double success_rate = (engine->score_possible > 0) 
                          ? ((double)engine->score_total / engine->score_possible) * 100 
                          : 0;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Suites run:{cyan} %4zu, {blue}Test run:{cyan} %4d, {blue}Score:{cyan} %d/%d\n{reset}",
                engine->count, engine->score_possible, engine->score_total, engine->score_possible);
            pizza_io_printf("{blue}Passed    :{cyan} %4d\n{reset}", engine->score.passed);
            pizza_io_printf("{blue}Failed    :{cyan} %4d\n{reset}", engine->score.failed);
            pizza_io_printf("{blue}Skipped   :{cyan} %4d\n{reset}", engine->score.skipped);
            pizza_io_printf("{blue}Timeouts  :{cyan} %4d\n{reset}", engine->score.timeout);
            pizza_io_printf("{blue}Unexpected:{cyan} %4d\n{reset}", engine->score.unexpected);
            pizza_io_printf("{blue}Empty     :{cyan} %4d\n{reset}", engine->score.empty);
            pizza_io_printf("{blue}Success Rate:{cyan} %.2f%%\n{reset}", success_rate);
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Suites run: %zu, Test run: %d, Score: %d/%d\n",
                engine->count, engine->score_possible, engine->score_total, engine->score_possible);
            pizza_io_printf("Passed    : %d\n", engine->score.passed);
            pizza_io_printf("Failed    : %d\n", engine->score.failed);
            pizza_io_printf("Skipped   : %d\n", engine->score.skipped);
            pizza_io_printf("Timeouts  : %d\n", engine->score.timeout);
            pizza_io_printf("Unexpected: %d\n", engine->score.unexpected);
            pizza_io_printf("Empty     : %d\n", engine->score.empty);
            pizza_io_printf("Success Rate: %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("TEST SUMMARY:\n");
            pizza_io_printf("Suites run: %zu\n", engine->count);
            pizza_io_printf("Tests run : %d\n", engine->score_possible);
            pizza_io_printf("Score     : %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("Passed    : %d\n", engine->score.passed);
            pizza_io_printf("Failed    : %d\n", engine->score.failed);
            pizza_io_printf("Skipped   : %d\n", engine->score.skipped);
            pizza_io_printf("Timeouts  : %d\n", engine->score.timeout);
            pizza_io_printf("Unexpected: %d\n", engine->score.unexpected);
            pizza_io_printf("Empty     : %d\n", engine->score.empty);
            pizza_io_printf("Success Rate: %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# Suites run: %zu\n", engine->count);
            pizza_io_printf("# Tests run : %d\n", engine->score_possible);
            pizza_io_printf("# Score     : %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("# Passed    : %d\n", engine->score.passed);
            pizza_io_printf("# Failed    : %d\n", engine->score.failed);
            pizza_io_printf("# Skipped   : %d\n", engine->score.skipped);
            pizza_io_printf("# Timeouts  : %d\n", engine->score.timeout);
            pizza_io_printf("# Unexpected: %d\n", engine->score.unexpected);
            pizza_io_printf("# Empty     : %d\n", engine->score.empty);
            pizza_io_printf("# Success Rate: %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] Suites run: %zu\n", engine->count);
            pizza_io_printf("[----------] Tests run : %d\n", engine->score_possible);
            pizza_io_printf("[==========] Score     : %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("[  PASSED  ] %d tests.\n", engine->score.passed);
            pizza_io_printf("[  FAILED  ] %d tests.\n", engine->score.failed);
            pizza_io_printf("[  SKIPPED ] %d tests.\n", engine->score.skipped);
            pizza_io_printf("[ TIMEOUTS ] %d tests.\n", engine->score.timeout);
            pizza_io_printf("[UNEXPECTED] %d tests.\n", engine->score.unexpected);
            pizza_io_printf("[   EMPTY  ] %d tests.\n", engine->score.empty);
            pizza_io_printf("[ SUCCESS  ] %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Test Summary\n");
            pizza_io_printf("Suites run: %zu\n", engine->count);
            pizza_io_printf("Tests run : %d\n", engine->score_possible);
            pizza_io_printf("Score     : %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("Passed    : %d\n", engine->score.passed);
            pizza_io_printf("Failed    : %d\n", engine->score.failed);
            pizza_io_printf("Skipped   : %d\n", engine->score.skipped);
            pizza_io_printf("Timeouts  : %d\n", engine->score.timeout);
            pizza_io_printf("Unexpected: %d\n", engine->score.unexpected);
            pizza_io_printf("Empty     : %d\n", engine->score.empty);
            pizza_io_printf("Success Rate: %.2f%%\n", success_rate);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display scoreboard.\n");
            break;
    }
}

void fossil_pizza_summary_heading(const fossil_pizza_engine_t* engine) {
    pizza_sys_hostinfo_system_t system_info;
    pizza_sys_hostinfo_endianness_t endianness_info;

    pizza_sys_hostinfo_get_system(&system_info);
    pizza_sys_hostinfo_get_endianness(&endianness_info);

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            pizza_io_printf("{blue}==={cyan} Fossil Pizza Summary {blue}===: os{magenta} %s {blue}endianess:{magenta} %s {reset}\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("=========================================================================\n");
            pizza_io_printf("=== Fossil Pizza Summary ===: os %s endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("=========================================================================\n");
            pizza_io_printf("[Fossil Pizza Summary]: os %s endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# Fossil Pizza Summary: os %s endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {red}F{yellow}o{yellow}s{green}s{blue}i{red}l {yellow}P{green}i{blue}z{red}z{yellow}a {green}S{blue}u{red}m{yellow}m{green}a{blue}r{red}y{reset}\n");
            pizza_io_printf("[----------] OS: %s, Endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Test Summary\n");
            pizza_io_printf("OS: %s, Endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display heading.\n");
            break;
    }
}

void fossil_pizza_summary(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    fossil_pizza_summary_heading(engine);
    fossil_pizza_summary_scoreboard(engine);
    fossil_pizza_summary_timestamp(engine);
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

void pizza_test_assert_internal_output(const char *message, const char *file, int line, const char *func, int anomaly_count) {
    // Output assertion failure based on theme
    switch (G_PIZZA_THEME) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{red,bold}Assertion failed:{reset} {yellow}%s{reset} {blue}(%s:%d in %s){reset}\n",
                            message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("{yellow}Duplicate or similar assertion detected [Anomaly Count: %d]{reset}\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[ASSERTION FAILED] %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("[DUPLICATE ASSERTION] Anomaly Count: %d\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("not ok - Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("# Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[  FAILED  ] Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("[  WARNING ] Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Assertion Failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Unity Duplicate Assertion Detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        default:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;
    }
}

static int pizza_test_assert_internal_detect(const char *message, const char *file, int line, const char *func) {
    static const char *last_message = null; // Store the last assertion message
    static const char *last_file = null;    // Store the last file name
    static int last_line = 0;               // Store the last line number
    static const char *last_func = null;    // Store the last function name
    static int anomaly_count = 0;           // Counter for anomaly detection

    // Check if the current assertion is the same or similar to the last one
    if (last_message && strstr(message, last_message) != null &&
        last_file && pizza_io_cstr_compare(last_file, file) == 0 &&
        last_line == line &&
        last_func && pizza_io_cstr_compare(last_func, func) == 0) {
        anomaly_count++;
    } else {
        anomaly_count = 0; // Reset anomaly count for new assertion
        last_message = message;
        last_file = file;
        last_line = line;
        last_func = func;
    }

    return anomaly_count;
}

void pizza_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
    _ASSERT_COUNT++; // Increment the assertion count

    if (!condition) {
        int anomaly_count = pizza_test_assert_internal_detect(message, file, line, func);

        // Output assertion failure
        pizza_test_assert_internal_output(message, file, line, func, anomaly_count);

        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

// *********************************************************************************************
// internal messages
// *********************************************************************************************

void _given(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}Given %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("Given: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[GIVEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# Given: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] Given: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity Given: %s\n", description);
                break;
            default:
                pizza_io_printf("Given: %s\n", description);
                break;
        }
    }
}

void _when(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}When %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("When: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[WHEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# When: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] When: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity When: %s\n", description);
                break;
            default:
                pizza_io_printf("When: %s\n", description);
                break;
        }
    }
}

void _then(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}Then %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("Then: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[THEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# Then: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] Then: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity Then: %s\n", description);
                break;
            default:
                pizza_io_printf("Then: %s\n", description);
                break;
        }
    }
}

void _on_skip(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{yellow}On Skip %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("On Skip: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[SKIP] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# On Skip: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[ SKIPPED ] %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity On Skip: %s\n", description);
                break;
            default:
                pizza_io_printf("On Skip: %s\n", description);
                break;
        }
    }
}
