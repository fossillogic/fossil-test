/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/test/testing.h"

enum {
    _FOSSIL_TEST_RESPONSE_LENGTH = 50
};

static const char *FOSSIL_TEST_OPTIONS[] = {
    "--version - Displays the current version of Fossil Test\n",
    "--help    - Shows help message with usage\n",
    "--info    - Displays detailed information about the test run\n"
};

static const char *FOSSIL_TEST_COMMANDS[] = {
    "reverse   [enable|disable] - Enables or disables reverse order of test execution\n",
    "repeat    [count]          - Repeats the test suite a specified number of times\n",
    "shuffle   [enable|disable] - Enables or disables shuffling of test execution order\n",
    "dry-run   [enable|disable] - Enables or disables dry-run mode\n",
    "fail-fast [enable|disable] - Stops execution after the first test failure if enabled\n",
    "quiet     [enable|disable] - Suppresses non-essential output when enabled\n",
    "color     [enable|disable] - Enables or disables colored output\n",
    "format    [option name]    - Summary format options (jellyfish, chart, table, plain)\n"
};

static const char *FOSSIL_TEST_VERSION = "1.1.8"; // Version of Fossil Test
static const char *FOSSIL_TEST_AUTHOR = "Michael Gene Brockus (Dreamer)"; // Author of Fossil Test
static const char *FOSSIL_TEST_LICENSE = "Mozilla Public License 2.0"; // License of Fossil Test

jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp
static int _ASSERT_COUNT = 0; // Counter for the number of assertions

// *****************************************************************************
// Helper function declarations
// *****************************************************************************

// Custom implementation of strdup to avoid warnings on some platforms
char *_custom_fossil_test_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *new_str = (char *)malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    memcpy(new_str, str, len);
    return new_str;
}

// *****************************************************************************
// Function declarations
// *****************************************************************************

// Initialize the options structure
fossil_test_options_t fossil_test_init_options(void) {
    fossil_test_options_t options;
    options.show_version = false;
    options.show_help = false;
    options.show_info = false;
    options.reverse = false;
    options.repeat_enabled = false;
    options.repeat_count = 1;
    options.shuffle_enabled = false;
    options.dry_run = false;
    options.fail_fast = false;
    options.quiet = false;
    options.color_output = true; // default to true for better UX
    options.format = FOSSIL_TEST_FORMAT_PLAIN; // Default format is plain
    return options;
}

void usage_info(void) {
    internal_test_puts("{cyan,bold}==================================================\n");
    internal_test_puts("{white,bold}\tUsage: fossil [options] [command]\n");
    internal_test_puts("{cyan,bold}==================================================\n\n");

    internal_test_puts("{yellow,bold}Options:\n");
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_OPTIONS) / sizeof(FOSSIL_TEST_OPTIONS[0]); i++) {
        internal_test_printf("  {green}> %s\n", FOSSIL_TEST_OPTIONS[i]);
    }

    internal_test_puts("\n{yellow,bold}Commands:\n");
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_COMMANDS) / sizeof(FOSSIL_TEST_COMMANDS[0]); i++) {
        internal_test_printf("  {green}> %s\n", FOSSIL_TEST_COMMANDS[i]);
    }

    internal_test_puts("\n{cyan,bold}==================================================\n");
}

void version_info(void) {
    internal_test_puts("{magenta,bold}==================================================\n");
    internal_test_puts("{white,bold}\tFossil Logic Test Framework\n");
    internal_test_puts("{magenta,bold}==================================================\n");

    internal_test_printf("  {cyan}Version: %s\n", FOSSIL_TEST_VERSION);
    internal_test_printf("  {cyan}Author : %s\n", FOSSIL_TEST_AUTHOR);
    internal_test_printf("  {cyan}License: %s\n", FOSSIL_TEST_LICENSE);

    internal_test_puts("{magenta,bold}==================================================\n");
}

// Command pallet parser
fossil_test_options_t fossil_options_parse(int argc, char **argv) {
    fossil_test_options_t options = fossil_test_init_options();
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            options.show_version = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            options.show_help = true;
        } else if (strcmp(argv[i], "--info") == 0) {
            options.show_info = true;
        } else if (strcmp(argv[i], "reverse") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.reverse = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.reverse = false;
                i++;
            }
        } else if (strcmp(argv[i], "repeat") == 0) {
            options.repeat_enabled = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options.repeat_count = atoi(argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "shuffle") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.shuffle_enabled = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.shuffle_enabled = false;
                i++;
            }
        } else if (strcmp(argv[i], "dry-run") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.dry_run = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.dry_run = false;
                i++;
            }
        } else if (strcmp(argv[i], "fail-fast") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.fail_fast = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.fail_fast = false;
                i++;
            }
        } else if (strcmp(argv[i], "quiet") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.quiet = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.quiet = false;
                i++;
            }
        } else if (strcmp(argv[i], "color") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "on") == 0) {
                options.color_output = true;
                i++;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "off") == 0) {
                options.color_output = false;
                i++;
            }
        } else if (strcmp(argv[i], "format") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "plain") == 0) {
                    options.format = FOSSIL_TEST_FORMAT_PLAIN;
                } else if (strcmp(argv[i + 1], "chart") == 0) {
                    options.format = FOSSIL_TEST_FORMAT_CHART;
                } else if (strcmp(argv[i + 1], "table") == 0) {
                    options.format = FOSSIL_TEST_FORMAT_TABLE;
                } else  if (strcmp(argv[i + 1], "jellyfish") == 0) {
                    options.format = FOSSIL_TEST_FORMAT_JELLYFISH;
                } else if (strcmp(argv[i + 1], "markdown") == 0) {
                    options.format = FOSSIL_TEST_FORMAT_MARKDOWN;
                }
                i++;
            }
        }
    }
    
    return options;
}

// Function to reverse the order of test cases in the linked list
void reverse_test_cases(fossil_test_case_t **test_cases) {
    if (!test_cases || !*test_cases) {
        return; // No test cases to reverse
    }

    fossil_test_case_t *prev = NULL;
    fossil_test_case_t *current = *test_cases;
    fossil_test_case_t *next = NULL;

    // Traverse the linked list and reverse the 'next' pointers
    while (current) {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the current node's pointer
        prev = current;        // Move prev and current one step forward
        current = next;
    }

    // After the loop, prev will point to the new head of the list
    *test_cases = prev;
}

// Function to shuffle test cases using the Fisher-Yates algorithm
void shuffle_test_cases(fossil_test_case_t **test_cases) {
    if (!test_cases || !*test_cases) {
        return; // No test cases to shuffle
    }

    // Calculate the length of the linked list (number of test cases)
    int n = 0;
    fossil_test_case_t *current = *test_cases;
    while (current) {
        n++;
        current = current->next;
    }

    // If there is only one or zero test cases, no need to shuffle
    if (n <= 1) {
        return;
    }

    // Create an array to hold the test cases
    fossil_test_case_t **array = malloc(sizeof(fossil_test_case_t *) * n);
    if (!array) {
        return; // Memory allocation failed
    }

    // Fill the array with the test case pointers
    current = *test_cases;
    for (int i = 0; i < n; i++) {
        array[i] = current;
        current = current->next;
    }

    // Shuffle the array using the Fisher-Yates algorithm
    srand(time(NULL));  // Seed the random number generator

    for (int i = n - 1; i > 0; i--) {
        // Generate a random index between 0 and i
        int j = rand() % (i + 1);

        // Swap the elements
        fossil_test_case_t *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Rebuild the linked list from the shuffled array
    for (int i = 0; i < n - 1; i++) {
        array[i]->next = array[i + 1];
    }
    array[n - 1]->next = NULL; // Last test case points to NULL

    // Update the original test cases pointer
    *test_cases = array[0];

    // Free the array after use
    free(array);
}

// Creates and returns a new test suite
fossil_test_suite_t* fossil_test_create_suite(const char *name) {
    if (!name) {
        return NULL;
    }

    fossil_test_suite_t *suite = (fossil_test_suite_t*)malloc(sizeof(fossil_test_suite_t));
    if (!suite) {
        return NULL;
    }

    suite->name = name;
    suite->suite_setup_func = NULL;
    suite->suite_teardown_func = NULL;
    suite->tests = NULL;
    suite->next = NULL;
    return suite;
}

// Registers a test suite in the environment
void fossil_test_register_suite(fossil_test_env_t *env, fossil_test_suite_t *suite) {
    if (!env || !suite) {
        return;
    }

    suite->next = env->test_suites;
    env->test_suites = suite;
    if (env->options.show_info) {
        internal_test_printf("{blue,bold}Registered test suite: %s\n{reset}", suite->name);
    }
}

// Adds a test case to a suite
void fossil_test_add_case(fossil_test_suite_t *suite, fossil_test_case_t *test_case) {
    if (!suite || !test_case) {
        return;
    }

    test_case->next = suite->tests;
    suite->tests = test_case;
}

// Removes and frees a test case from a suite
void fossil_test_remove_case(fossil_test_suite_t *suite, fossil_test_case_t *test_case) {
    if (!suite || !test_case) {
        return;
    }

    fossil_test_case_t *prev = NULL;
    fossil_test_case_t *curr = suite->tests;

    while (curr) {
        if (curr == test_case) {
            if (prev) {
                prev->next = curr->next;
            } else {
                suite->tests = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Setup for individual test case
void fossil_test_case_setup(fossil_test_case_t *test_case) {
    if (test_case && test_case->setup_func) {
        test_case->setup_func();
    }
}

// Teardown for individual test case
void fossil_fossil_test_case_teardown(fossil_test_case_t *test_case) {
    if (test_case && test_case->teardown_func) {
        test_case->teardown_func();
    }
}

// Runs a test suite
void fossil_test_run_suite(fossil_test_suite_t *suite, fossil_test_env_t *env) {
    if (!suite || !env) {
        return;
    }

    if (env->options.show_info) {
        internal_test_printf("{blue,bold}Running suite: %s{reset}\n", suite->name);
    }

    if (env->options.shuffle_enabled) {
        shuffle_test_cases(&suite->tests);
    }

    if (env->options.reverse) {
        reverse_test_cases(&suite->tests);
    }

    if (suite->suite_setup_func) {
        suite->suite_setup_func();
    }

    clock_t suite_start = clock();

    fossil_test_case_t *current_test = suite->tests;
    while (current_test) {
        fossil_test_run_case(current_test, env);
        current_test = current_test->next;
    }

    clock_t suite_end = clock();
    double total_execution_time = (double)(suite_end - suite_start) / CLOCKS_PER_SEC;

    if (suite->suite_teardown_func) {
        suite->suite_teardown_func();
    }

    if (env->options.show_info) {
        internal_test_printf("{cyan}Total execution time for suite %s: %.3f seconds{reset}\n", suite->name, total_execution_time);
    }
}

// Internal function to handle assertions with anomaly detection
void fossil_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
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
            internal_test_printf("{yellow}Duplicate or similar assertion detected: %s (%s:%d in %s) [Anomaly Count: %d]{reset}\n",
                                 message, file, line, func, anomaly_count);
        } else {
            anomaly_count = 0; // Reset anomaly count for new assertion
            last_message = message;
            last_file = file;
            last_line = line;
            last_func = func;
            internal_test_printf("{red}Assertion failed: %s (%s:%d in %s){reset}\n", message, file, line, func);
        }

        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

// Runs a test case
void fossil_test_run_case(fossil_test_case_t *test_case, fossil_test_env_t *env) {
    if (!test_case || !env) {
        return;
    }

    if (env->options.dry_run) {
        internal_test_printf("{purple}Dry run mode enabled. No tests will be executed.{reset}\n");
        return;
    }

    test_case->status = TEST_STATUS_PASS;

    // Run setup
    fossil_test_case_setup(test_case);

    _ASSERT_COUNT = 0; // Reset assertion count before running the test

    clock_t start_iter = clock();
    double timeout_seconds = 180.0; // 3-minute timeout

    if (setjmp(env->env) == 0) {
        for (int i = 0; i < env->options.repeat_count; i++) {
            test_case->test_func();

            clock_t now = clock();
            double elapsed_seconds = (double)(now - start_iter) / CLOCKS_PER_SEC;

            if (elapsed_seconds > timeout_seconds) {
                test_case->status = TEST_STATUS_TTIMEOUT;
                internal_test_printf("{orange}TIMEOUT: {blue}%s{reset}\n", test_case->name);
                break;
            }
        }
    } else {
        test_case->status = TEST_STATUS_FAIL;
        internal_test_printf("{red}FAILED: {blue}%s{reset}\n", test_case->name);
        internal_test_printf("Failure Message: %s{reset}\n", test_case->failure_message);
    }

    clock_t end_iter = clock();
    test_case->execution_time = (double)(end_iter - start_iter) / CLOCKS_PER_SEC;

    fossil_fossil_test_case_teardown(test_case);

    switch (test_case->status) {
        case TEST_STATUS_PASS:
            if (env->options.show_info) {
                internal_test_printf("{green}PASSED: {blue}%s (%.3f seconds){reset}\n", test_case->name, test_case->execution_time);
            }
            break;
        case TEST_STATUS_FAIL:
            env->fail_count++;
            break;
        case TEST_STATUS_SKIP:
            env->skip_count++;
            break;
        case TEST_STATUS_TTIMEOUT:
            env->timeout_count++;
            break;
        default:
            env->unexpected_count++;
            break;
    }
}

// Runs all the test suites
void fossil_test_run_all(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    if (env->options.dry_run) {
        internal_test_printf("{purple}Dry run mode enabled. No tests will be executed.{reset}\n");
        return;
    }

    fossil_test_suite_t *current_suite = env->test_suites;

    while (current_suite) {
        fossil_test_run_suite(current_suite, env);
        current_suite = current_suite->next;
    }
}

// Initializes the test environment
void fossil_test_init(fossil_test_env_t *env, int argc, char **argv) {
    if (!env) {
        return;
    }

    env->options = fossil_options_parse(argc, argv);
    if (env->options.show_version) {
        version_info();
        exit(EXIT_SUCCESS);
    }

    if (env->options.show_help) {
        usage_info();
        exit(EXIT_SUCCESS);
    }

    env->pass_count = 0;
    env->fail_count = 0;
    env->skip_count = 0;
    env->empty_count = 0;
    env->total_tests = 0;
    env->timeout_count = 0;
    env->start_execution_time = clock();
    env->end_execution_time = 0.0;
    env->unexpected_count = 0;
    env->test_suites = NULL;

    if (env->options.dry_run) {
        internal_test_printf("{purple}Dry run mode enabled. No tests will be executed or evaluated.{reset}\n");
        return;
    }
}

void fossil_test_comment(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Dynamic comment based on test result
    if (env->pass_count > 0 && env->fail_count == 0 && env->timeout_count == 0) {
        // Positive outcome - playful
        internal_test_printf("{cyan}Comment: %s{reset}\n", great_news_messages[rand() % (sizeof(great_news_messages) / sizeof(great_news_messages[0]))]);
    } else if (env->fail_count > 0) {
        // Failure detected - humorous to lighten the mood
        internal_test_printf("{red}Comment: %s{reset}\n", humorous_messages[rand() % (sizeof(humorous_messages) / sizeof(humorous_messages[0]))]);
    } else if (env->timeout_count > 0) {
        // Timeout encountered - insightful
        internal_test_printf("{orange}Comment: %s{reset}\n", timeout_messages[rand() % (sizeof(timeout_messages) / sizeof(timeout_messages[0]))]);
    } else if (env->pass_count == 0 && env->fail_count == 0 && env->timeout_count == 0) {
        // No results - sarcastic twist
        internal_test_printf("{cyan}Comment: %s{reset}\n", sarcastic_messages[rand() % (sizeof(sarcastic_messages) / sizeof(sarcastic_messages[0]))]);
    } else {
        // Mixed results - deeper analysis
        internal_test_printf("{cyan}Comment: The test results are mixed. Consider analyzing individual test cases to uncover underlying issues.{reset}\n");
    }
}

void fossil_test_analyze(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    fossil_test_suite_t *suite = env->test_suites;
    while (suite) {
        fossil_test_case_t *test = suite->tests;
        while (test) {
            if (test->status == TEST_STATUS_SKIP) {
                env->skip_count++;  // Increment skipped count directly from env
            }
            test = test->next;
        }
        suite = suite->next;
    }

    // Total tests count
    int total_tests = env->pass_count + env->fail_count + env->skip_count + env->timeout_count;

    // Calculate success rate and other statistics
    double success_rate = (double)env->pass_count / (double)total_tests * 100;
    double failure_rate = (double)env->fail_count / (double)total_tests * 100;
    double skip_rate = (double)env->skip_count / (double)total_tests * 100;
    double timeout_rate = (double)env->timeout_count / (double)total_tests * 100;

    // Calculate probability (success probability)
    double probability_of_success = (double)env->pass_count / total_tests;

    // Calculate average (mean of success, failure, skip, timeout rates)
    double average_rate = (success_rate + failure_rate + skip_rate + timeout_rate) / 4.0;

    // Prediction (can be based on past success rate or other methods)
    double prediction = success_rate;  // For simplicity, using the past success rate as prediction

    // Sort conditions from worst case to best case:
    // 1. Failure Rate -> 2. Timeout Rate -> 3. Skipped Rate -> 4. Success Rate

    // Worst case: Failure rate
    if (env->fail_count > 0) {
        internal_test_printf("{cyan}Failure rate: %.2f%%{reset}\n", failure_rate);
    }

    // Next worst: Timeout tests
    if (env->timeout_count > 0) {
        internal_test_printf("{cyan}Timeout tests: %.2f%%{reset}\n", timeout_rate);
    }

    // Skipped tests next
    if (env->skip_count > 0) {
        internal_test_printf("{cyan}Skipped tests: %.2f%% (%d tests){reset}\n", skip_rate, env->skip_count);
    }

    // Best case: Success rate
    if (env->pass_count > 0) {
        internal_test_printf("{cyan}Success rate: %.2f%%{reset}\n", success_rate);
    }

    // Additional insights
    internal_test_printf("{cyan}Probability of success: %.2f{reset}\n", probability_of_success);
    internal_test_printf("{cyan}Average test rate: %.2f%%{reset}\n", average_rate);
    internal_test_printf("{cyan}Prediction (Future Success Rate): %.2f%%{reset}\n", prediction);

    // Skipped tests analysis route
    if (env->skip_count > 0) {
        internal_test_printf("{yellow}Note: There were %d skipped tests. Please check the conditions or requirements for those tests.{reset}\n", env->skip_count);
    }
}

void fossil_test_suggest(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Dynamic suggestion based on results and test state
    if (env->pass_count == 0 && env->fail_count == 0 && env->skip_count == 0 && env->timeout_count == 0 && env->empty_count > 0) {
        internal_test_printf("{cyan}{italic}Suggestion: %s{reset}\n", empty_suite_suggestions[rand() % 50]);
    } else if (env->fail_count > 0) {
        internal_test_printf("{cyan}{italic}Suggestion: %s{reset}\n", failure_suggestions[rand() % 50]);
    } else if (env->pass_count > 0) {
        internal_test_printf("{cyan}{italic}Suggestion: %s{reset}\n", success_suggestions[rand() % 50]);
    } else if (env->timeout_count > 0) {
        internal_test_printf("{cyan}{italic}Suggestion: %s{reset}\n", timeout_suggestions[rand() % 50]);
    } else if (env->skip_count > 0) {
        // Skipped tests specific suggestions
        internal_test_printf("{cyan}{italic}Suggestion: Review skipped tests for prerequisites or intentional exclusions. Ensure tests are not being skipped due to unmet conditions.{reset}\n");
    }
}

void fossil_test_execution_time(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Calculate total execution time in seconds
    double total_execution_time = (double)(env->end_execution_time - env->start_execution_time) / CLOCKS_PER_SEC;

    // Breakdown into smaller units
    int32_t seconds       = (int32_t)total_execution_time;
    int32_t milliseconds  = (int32_t)((total_execution_time - seconds) * 1000);
    int32_t microseconds  = (int32_t)((total_execution_time - seconds - milliseconds / 1000.0) * 1000000);
    int32_t nanoseconds   = (int32_t)((total_execution_time - seconds - milliseconds / 1000.0 - microseconds / 1000000.0) * 1000000000);

    // Start the output paragraph for insights
    internal_test_printf("{blue}{bold}=================================================================================={reset}\n");
    internal_test_printf("{cyan}{italic}\tInsight: Based on the execution time analysis, we observe the following:{reset}\n");

    // Anomaly Detection & Optimization Insight
    if (total_execution_time > 5.0) {
        internal_test_printf(
            "Execution time is exceptionally long, indicating possible critical\n"
            "inefficiencies, extensive test coverage, or hardware constraints.\n"
            "Investigate parallel execution strategies, resource bottlenecks, or\n"
            "excessive test dependencies. Consider breaking test suites into smaller\n"
            "units to isolate performance-heavy areas.\n"
        );
    } else if (total_execution_time > 2.0) {
        internal_test_printf(
            "Execution time is unusually long, suggesting potential bottlenecks\n"
            "or inefficiencies in the test suite. Optimization strategies, such as\n"
            "test parallelization or resource allocation adjustments, could help\n"
            "reduce time consumption.\n"
        );
    } else if (total_execution_time < 0.2) {
        internal_test_printf(
            "Execution time is abnormally short. This could mean tests were\n"
            "skipped or misconfigured. Ensure full test coverage is executed and\n"
            "no critical paths are being inadvertently bypassed in the\n"
            "environment.\n"
        );
    }

    // Footer and execution time display
    internal_test_printf("{blue}{bold}=================================================================================={reset}\n");
    internal_test_printf("{cyan}{italic}|\tExecution time:{reset}\n");
    internal_test_printf("{cyan}{italic}|\t(%02d) sec, (%03d) ms, (%06d) us, (%09d) ns\n{reset}", 
                          (int32_t)seconds, (int32_t)milliseconds, (int32_t)microseconds, (int32_t)nanoseconds);
    internal_test_printf("{blue}{bold}=================================================================================={reset}\n");
}

void fossil_test_summary(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Check dry run mode
    if (env->options.dry_run) {
        internal_test_printf("{purple}Dry run mode enabled. No tests were executed or evaluated.{reset}\n");
        return;
    }

    fossil_test_suite_t *suite = env->test_suites;
    while (suite != NULL) {
        fossil_test_case_t *test = suite->tests;
        while (test != NULL) {
            // Count test outcomes
            if (test->status == TEST_STATUS_PASS) {
                env->pass_count++;
            } else if (test->status == TEST_STATUS_FAIL) {
                env->fail_count++;
                if (test->failure_message) {
                    internal_test_printf("{red}Test '%s' failed: %s{reset}\n", test->name, test->failure_message);
                }
            } else if (test->status == TEST_STATUS_SKIP) {
                env->skip_count++;
            } else if (test->status == TEST_STATUS_TTIMEOUT) {
                env->timeout_count++;
            } else {
                env->unexpected_count++;
            }

            test = test->next;
        }
        suite = suite->next;
    }

    env->end_execution_time = clock();

    // TUI-like header and bold title
    internal_test_printf("{blue}{bold}=================================================================================={reset}\n");
    internal_test_printf("{cyan}{italic}\tFossil Test Summary{reset}\n");
    internal_test_printf("{blue}{bold}=================================================================================={reset}\n");

    fossil_test_analyze(env);  // Add analysis of test results
    fossil_test_comment(env);  // Add comments based on results
    fossil_test_suggest(env);  // Add suggestions for improvement
    fossil_test_execution_time(env);
}
