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

// Array of messages for each category
const char *sarcastic_messages[] = {
    "Wow, no tests were run! What a productive day!",
    "No tests to run, guess we're all just too good at writing code.",
    "Congratulations, you've done absolutely nothing today.",
    "Oh, look! No tests were executed. What an achievement!",
    "Not a single test run, but hey, that's one way to keep things perfect!",
    "All set for a day of zero productivity? Nice!",
    "The test suite is empty, but hey, at least the code didn't break!",
    "Zero tests executed. Clearly, you've mastered the art of doing nothing.",
    "Great! We've made it through an entire test run without running a single test.",
    "Isn't it great when there's nothing to test?",
    "No tests today, must be a holiday!",
    "Looks like the tests took a day off.",
    "No tests? Guess it's time for a coffee break.",
    "No tests executed. Time to celebrate doing nothing!",
    "No tests? Must be a sign of perfection.",
    "No tests run. Maybe tomorrow.",
    "No tests? Guess we're just that good.",
    "No tests today. Enjoy the free time!",
    "No tests? Must be a coding miracle.",
    "No tests executed. Time to relax.",
    "No tests? Guess it's a lazy day.",
    "No tests run. Must be a record.",
    "No tests? Time to enjoy the silence.",
    "No tests executed. Time to chill.",
    "No tests? Must be a coding vacation.",
    "No tests run. Time to take it easy.",
    "No tests? Guess we're flawless.",
    "No tests executed. Time to unwind.",
    "No tests? Must be a coding break.",
    "No tests run. Time to kick back.",
    "No tests executed. What a surprise!",
    "No tests? Guess we're all perfect coders.",
    "No tests run. Time to take a nap.",
    "No tests? Must be a coding dream.",
    "No tests executed. Time to party!",
    "No tests? Guess we're all geniuses.",
    "No tests run. Time to celebrate!",
    "No tests? Must be a coding legend.",
    "No tests executed. Time to rejoice.",
    "No tests? Guess we're all experts.",
    "No tests run. Time to relax and enjoy.",
    "No tests? Must be a coding utopia.",
    "No tests executed. Time to have fun.",
    "No tests? Guess we're all masters.",
    "No tests run. Time to take a break.",
    "No tests? Must be a coding paradise.",
    "No tests executed. Time to chill out.",
    "No tests? Guess we're all wizards.",
    "No tests run. Time to unwind and relax.",
    "No tests? Must be a coding heaven."
};

const char *humorous_messages[] = {
    "Well, that was an epic failure! Better luck next time!",
    "Whoops! Someone's definitely gonna need to debug that.",
    "Looks like someone forgot to write the test cases.",
    "Your tests failed, but at least you got closer to perfection... not.",
    "Not all heroes wear capes. Some of them fail tests.",
    "Don't worry, failure is just success in disguise. Or maybe not.",
    "Well, that was awkward. Let's try again, shall we?",
    "Looks like we've encountered a bug! Hope you've got a magnifying glass.",
    "Your tests are taking a nap, but don't worry, we'll wake them up!",
    "It's not a failure, it's just a learning experience! A very *expensive* one.",
    "Oops! That didn't go as planned.",
    "Well, that was a disaster. Time to debug!",
    "Looks like we hit a snag. Time to fix it!",
    "Your tests failed spectacularly. Congrats!",
    "Well, that was a mess. Let's clean it up.",
    "Oops! Something went wrong. Time to investigate.",
    "Well, that was a flop. Better luck next time.",
    "Looks like we have some bugs to squash.",
    "Your tests failed. Time to roll up your sleeves.",
    "Oops! That didn't work. Time to try again.",
    "Well, that was a fail. Let's fix it.",
    "Looks like we have some issues to resolve.",
    "Your tests failed. Time to get to work.",
    "Oops! That was a fail. Time to debug.",
    "Well, that was a bust. Let's fix it.",
    "Looks like we have some problems to solve.",
    "Your tests failed. Time to figure it out.",
    "Oops! That didn't go well. Time to debug.",
    "Well, that was a fail. Let's try again.",
    "Looks like we have some errors to fix.",
    "Your tests failed. Time to troubleshoot.",
    "Oops! That was unexpected. Time to investigate.",
    "Well, that was a blunder. Let's correct it.",
    "Looks like we have some debugging to do.",
    "Your tests failed. Time to analyze the issue.",
    "Oops! That didn't go as expected. Time to debug.",
    "Well, that was a setback. Let's resolve it.",
    "Looks like we have some fixing to do.",
    "Your tests failed. Time to diagnose the problem.",
    "Oops! That was a misstep. Time to debug.",
    "Well, that was a glitch. Let's fix it.",
    "Looks like we have some troubleshooting to do.",
    "Your tests failed. Time to rectify the issue.",
    "Oops! That was a hiccup. Time to debug.",
    "Well, that was a malfunction. Let's repair it.",
    "Looks like we have some correcting to do.",
    "Your tests failed. Time to address the problem.",
    "Oops! That was a slip-up. Time to debug.",
    "Well, that was a snag. Let's fix it."
};

const char *great_news_messages[] = {
    "Great news! All tests passed. You're a testing genius!",
    "Success! Everything works as expected. Go celebrate!",
    "You did it! All tests passed. You're officially a rock star!",
    "Congrats, all tests passed! You've earned a gold star!",
    "Woohoo! All tests passed with flying colors!",
    "No bugs found today, you're on fire!",
    "Amazing! You've got a perfect test suite. Keep it up!",
    "Nice job! All tests passed. I think we've found the next coding superhero!",
    "Fantastic! No issues at all, just pure success!",
    "All tests passed, everything's awesome.",
    "Great job! All tests passed with no issues.",
    "Congratulations! All tests passed successfully.",
    "Well done! All tests passed with flying colors.",
    "Awesome! All tests passed without a hitch.",
    "Fantastic! All tests passed with no problems.",
    "Excellent! All tests passed with ease.",
    "Superb! All tests passed without any issues.",
    "Outstanding! All tests passed with no errors.",
    "Brilliant! All tests passed with no failures.",
    "Impressive! All tests passed with no bugs.",
    "Wonderful! All tests passed with no glitches.",
    "Terrific! All tests passed with no hiccups.",
    "Marvelous! All tests passed with no snags.",
    "Spectacular! All tests passed with no setbacks.",
    "Phenomenal! All tests passed with no troubles.",
    "Remarkable! All tests passed with no obstacles.",
    "Incredible! All tests passed with no difficulties.",
    "Stellar! All tests passed with no challenges.",
    "Magnificent! All tests passed with no hurdles.",
    "Fabulous! All tests passed with no impediments.",
    "Perfect! All tests passed without any issues.",
    "Great! All tests passed with no errors.",
    "Wonderful! All tests passed with no problems.",
    "Amazing! All tests passed with no failures.",
    "Fantastic! All tests passed with no bugs.",
    "Excellent! All tests passed with no glitches.",
    "Superb! All tests passed with no hiccups.",
    "Outstanding! All tests passed with no snags.",
    "Brilliant! All tests passed with no setbacks.",
    "Impressive! All tests passed with no troubles.",
    "Wonderful! All tests passed with no obstacles.",
    "Terrific! All tests passed with no difficulties.",
    "Marvelous! All tests passed with no challenges.",
    "Spectacular! All tests passed with no hurdles.",
    "Phenomenal! All tests passed with no impediments.",
    "Remarkable! All tests passed with no issues.",
    "Incredible! All tests passed with no errors.",
    "Stellar! All tests passed with no problems.",
    "Magnificent! All tests passed with no failures.",
    "Fabulous! All tests passed with no bugs."
};

const char *timeout_messages[] = {
    "Some tests timed out. Please check the test cases.",
    "Looks like some tests took too long to complete. Time to debug!",
    "Uh-oh! Some tests took too long to run. Time to investigate!",
    "Looks like some tests are still running. Did you forget to add a timeout?",
    "Some tests are still in progress. Time to grab a coffee and debug!",
    "Timeout alert! Some tests didn't finish in time.",
    "Tests are taking longer than expected. Time to check for infinite loops!",
    "Some tests exceeded the time limit. Let's optimize!",
    "Tests are running slow. Time to profile and improve performance!",
    "Timeout detected! Some tests need a closer look.",
    "Tests are taking forever. Time to investigate!",
    "Some tests are stuck. Time to debug!",
    "Tests are running longer than expected. Time to check for bottlenecks!",
    "Timeout warning! Some tests didn't complete in time.",
    "Tests are still running. Time to check for performance issues!",
    "Some tests are taking too long. Time to optimize!",
    "Tests are timing out. Time to investigate the cause!",
    "Timeout issue detected. Some tests need attention!",
    "Tests are running slow. Time to improve efficiency!",
    "Timeout alert! Some tests are not finishing in time.",
    "Tests are taking too long. Time to debug and optimize!",
    "Timeout detected. Some tests are running indefinitely!",
    "Tests are exceeding the time limit. Time to investigate!",
    "Timeout issue. Some tests are not completing in time!",
    "Tests are running longer than expected. Time to debug!",
    "Timeout warning. Some tests are taking too long!",
    "Tests are still running. Time to check for issues!",
    "Timeout detected. Some tests need optimization!",
    "Tests are taking forever. Time to investigate the cause!",
    "Timeout alert. Some tests are not finishing in time!",
    "Tests are taking too long. Time to find the bottleneck!",
    "Timeout detected. Some tests need a performance review!",
    "Tests are running indefinitely. Time to debug!",
    "Timeout warning. Some tests are stuck!",
    "Tests are taking too long. Time to optimize performance!",
    "Timeout issue detected. Some tests need a closer look!",
    "Tests are running slow. Time to investigate!",
    "Timeout alert. Some tests are not completing!",
    "Tests are taking too long. Time to debug!",
    "Timeout detected. Some tests are running too long!",
    "Tests are exceeding the time limit. Time to optimize!",
    "Timeout issue. Some tests are not finishing!",
    "Tests are running longer than expected. Time to debug!",
    "Timeout warning. Some tests are taking too long!",
    "Tests are still running. Time to check for issues!",
    "Timeout detected. Some tests need optimization!",
    "Tests are taking forever. Time to investigate the cause!",
    "Timeout alert. Some tests are not finishing in time!",
    "Tests are taking too long. Time to find the bottleneck!"
};

enum {
    _FOSSIL_TEST_RESPONSE_LENGTH = 50
};

static const char *FOSSIL_TEST_OPTIONS[] = {
    "--version - Displays the current version of Fossil Test\n",
    "--help - Shows help message with usage\n",
    "--info - Displays detailed information about the test run\n"
};

static const char *FOSSIL_TEST_COMMANDS[] = {
    "reverse [enable|disable] - Enables or disables reverse order of test execution\n",
    "repeat [count] - Repeats the test suite a specified number of times\n",
    "shuffle [enable|disable] - Enables or disables shuffling of test execution order\n",
    "dry-run [enable|disable] - Enables or disables dry-run mode\n"
};

static const char *FOSSIL_TEST_VERSION = "1.1.5"; // Version of Fossil Test
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
fossil_options_t init_options(void) {
    fossil_options_t options;
    options.show_version = false;
    options.show_help = false;
    options.show_info = false;
    options.reverse = false;
    options.repeat_enabled = false;
    options.repeat_count = 1;
    options.shuffle_enabled = false;
    options.dry_run = false;
    return options;
}

void usage_info(void) {
    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Usage: fossil [options] [command]"                                   FOSSIL_TEST_COLOR_RESET);
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "===================================================================" FOSSIL_TEST_COLOR_RESET);
    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD   "\tOptions:" FOSSIL_TEST_COLOR_RESET);
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_OPTIONS) / sizeof(FOSSIL_TEST_OPTIONS[0]); i++) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "\t>\t%s" FOSSIL_TEST_COLOR_RESET, FOSSIL_TEST_OPTIONS[i]);
    }

    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD   "\tCommands:" FOSSIL_TEST_COLOR_RESET);
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_COMMANDS) / sizeof(FOSSIL_TEST_COMMANDS[0]); i++) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "\t>\t%s" FOSSIL_TEST_COLOR_RESET, FOSSIL_TEST_COMMANDS[i]);
    }
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "===================================================================" FOSSIL_TEST_COLOR_RESET);
}

void version_info(void) {
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "Fossil Logic Test Framework");
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "\tVersion: %s\n", FOSSIL_TEST_VERSION);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "\tAuthor: %s\n", FOSSIL_TEST_AUTHOR);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "\tLicense: %s\n", FOSSIL_TEST_LICENSE);
}

// Parse command-line arguments
fossil_options_t fossil_options_parse(int argc, char **argv) {
    fossil_options_t options = init_options();
    
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
        }
    }
    
    return options;
}

// Function to reverse the order of test cases in the linked list
void reverse_test_cases(test_case_t **test_cases) {
    if (!test_cases || !*test_cases) {
        return; // No test cases to reverse
    }

    test_case_t *prev = NULL;
    test_case_t *current = *test_cases;
    test_case_t *next = NULL;

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
void shuffle_test_cases(test_case_t **test_cases) {
    if (!test_cases || !*test_cases) {
        return; // No test cases to shuffle
    }

    // Calculate the length of the linked list (number of test cases)
    int n = 0;
    test_case_t *current = *test_cases;
    while (current) {
        n++;
        current = current->next;
    }

    // If there is only one or zero test cases, no need to shuffle
    if (n <= 1) {
        return;
    }

    // Create an array to hold the test cases
    test_case_t **array = malloc(sizeof(test_case_t *) * n);
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
        test_case_t *temp = array[i];
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
test_suite_t* fossil_test_create_suite(const char *name) {
    if (!name) {
        return NULL;
    }

    test_suite_t *suite = (test_suite_t*)malloc(sizeof(test_suite_t));
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
void fossil_test_register_suite(fossil_test_env_t *env, test_suite_t *suite) {
    if (!env || !suite) {
        return;
    }

    suite->next = env->test_suites;
    env->test_suites = suite;
    if (env->options.show_info) {
        printf(FOSSIL_TEST_COLOR_BLUE "Registered test suite: %s\n" FOSSIL_TEST_COLOR_RESET, suite->name);
    }
}

// Adds a test case to a suite
void fossil_test_add_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) {
        return;
    }

    test_case->next = suite->tests;
    suite->tests = test_case;
}

// Removes and frees a test case from a suite
void fossil_test_remove_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) {
        return;
    }

    test_case_t *prev = NULL;
    test_case_t *curr = suite->tests;

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
void fossil_test_case_setup(test_case_t *test_case) {
    if (test_case && test_case->setup_func) {
        test_case->setup_func();
    }
}

// Teardown for individual test case
void fossil_test_case_teardown(test_case_t *test_case) {
    if (test_case && test_case->teardown_func) {
        test_case->teardown_func();
    }
}

// Run all test cases in a test suite
void fossil_test_run_suite(test_suite_t *suite, fossil_test_env_t *env) {
    if (!suite || !env) {
        return;
    }

    if (env->options.show_info) {
        printf(FOSSIL_TEST_COLOR_BLUE "Running suite: %s\n" FOSSIL_TEST_COLOR_RESET, suite->name);
    }

    if (env->options.shuffle_enabled){
        shuffle_test_cases(&suite->tests);
    }

    if (env->options.reverse) {
        reverse_test_cases(&suite->tests);
    }

    if (suite->suite_setup_func) {
        suite->suite_setup_func();
    }

    double total_execution_time = 0.0;
    test_case_t *current_test = suite->tests;
    while (current_test) {
        fossil_test_run_case(current_test, env);
        total_execution_time += current_test->execution_time;
        current_test = current_test->next;
    }

    if (suite->suite_teardown_func) {
        suite->suite_teardown_func();
    }

    if (env->options.show_info) {
        printf(FOSSIL_TEST_COLOR_CYAN "Total execution time for suite %s: %.3f seconds\n" FOSSIL_TEST_COLOR_RESET, suite->name, total_execution_time);
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
            printf(FOSSIL_TEST_COLOR_YELLOW "Duplicate or similar assertion detected: %s (%s:%d in %s) [Anomaly Count: %d]\n" FOSSIL_TEST_COLOR_RESET, message, file, line, func, anomaly_count);
        } else {
            anomaly_count = 0; // Reset anomaly count for new assertion
            printf(FOSSIL_TEST_COLOR_RED "Assertion failed: %s (%s:%d in %s)\n" FOSSIL_TEST_COLOR_RESET, message, file, line, func);
        }

        // Update the last assertion details
        last_message = message;
        last_file = file;
        last_line = line;
        last_func = func;

        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

// Run an individual test case
void fossil_test_run_case(test_case_t *test_case, fossil_test_env_t *env) {
    if (!test_case || !env) {
        return;
    }

    if (env->options.dry_run) {
        puts(FOSSIL_TEST_COLOR_PURPLE "Dry run mode enabled. No tests will be executed." FOSSIL_TEST_COLOR_RESET);
        return;
    }

    test_case->status = TEST_STATUS_PASS;

    // Run setup
    fossil_test_case_setup(test_case);

    clock_t test_start_time = clock();
    clock_t timeout_limit = test_start_time + 3 * 60 * CLOCKS_PER_SEC; // 3 minutes timeout

    _ASSERT_COUNT = 0; // Reset assertion count before running the test

    if (setjmp(env->env) == 0) { // Attempt to run the test case
        for (int i = 0; i < env->options.repeat_count; i++) {
            test_case->test_func();
            if (clock() > timeout_limit) { // Timeout check
                test_case->status = TEST_STATUS_TTIMEOUT;
                printf(FOSSIL_TEST_COLOR_ORANGE "TIMEOUT: " FOSSIL_TEST_COLOR_BLUE " %s\n" FOSSIL_TEST_COLOR_RESET, test_case->name);
                break;
            }
        }
    } else { // Handle failure
        test_case->status = TEST_STATUS_FAIL;
        printf(FOSSIL_TEST_COLOR_RED "FAILED: " FOSSIL_TEST_COLOR_BLUE " %s\n", test_case->name);
        printf("Failure Message: %s\n" FOSSIL_TEST_COLOR_RESET, test_case->failure_message);
    }

    test_case->execution_time = (double)(clock() - test_start_time) / CLOCKS_PER_SEC;

    // Warn if the test case contains no assertions
    if (_ASSERT_COUNT == 0) {
        printf(FOSSIL_TEST_COLOR_YELLOW "WARNING: %s contains no assertions\n" FOSSIL_TEST_COLOR_RESET, test_case->name);
    }

    // Run teardown
    fossil_test_case_teardown(test_case);

    // Log result
    switch (test_case->status) {
        case TEST_STATUS_PASS:
            if (env->options.show_info) {
                printf(FOSSIL_TEST_COLOR_GREEN "PASSED: " FOSSIL_TEST_COLOR_BLUE " %s (%.3f seconds)\n" FOSSIL_TEST_COLOR_RESET, test_case->name, test_case->execution_time);
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

void fossil_test_run_all(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    if (env->options.dry_run) {
        puts(FOSSIL_TEST_COLOR_PURPLE "Dry run mode enabled. No tests will be executed." FOSSIL_TEST_COLOR_RESET);
        return;
    }

    test_suite_t *current_suite = env->test_suites;

    while (current_suite) {
        fossil_test_run_suite(current_suite, env);
        current_suite = current_suite->next;
    }
}

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
        puts(FOSSIL_TEST_COLOR_PURPLE "Dry run mode enabled. No tests will be executed or evaluated." FOSSIL_TEST_COLOR_RESET);
        return;
    }
}

// Function to generate a dynamic message based on the test results
void fossil_test_message(fossil_test_env_t *env) {
    // Seed random number generator
    srand(time(NULL));

    if (env->pass_count == 0 && env->fail_count == 0 && env->skip_count == 0 && env->timeout_count == 0 && env->empty_count > 0) {
        printf(FOSSIL_TEST_COLOR_YELLOW FOSSIL_TEST_ATTR_ITATIC "%s\n" FOSSIL_TEST_COLOR_RESET, sarcastic_messages[rand() % _FOSSIL_TEST_RESPONSE_LENGTH]);
    } else if (env->fail_count > 0) {
        printf(FOSSIL_TEST_COLOR_RED FOSSIL_TEST_ATTR_ITATIC "%s\n" FOSSIL_TEST_COLOR_RESET, humorous_messages[rand() % _FOSSIL_TEST_RESPONSE_LENGTH]);
    } else if (env->pass_count > 0) {
        printf(FOSSIL_TEST_COLOR_GREEN FOSSIL_TEST_ATTR_ITATIC "%s\n" FOSSIL_TEST_COLOR_RESET, great_news_messages[rand() % _FOSSIL_TEST_RESPONSE_LENGTH]);
    } else if (env->timeout_count > 0) {
        printf(FOSSIL_TEST_COLOR_ORANGE FOSSIL_TEST_ATTR_ITATIC "%s\n" FOSSIL_TEST_COLOR_RESET, timeout_messages[rand() % _FOSSIL_TEST_RESPONSE_LENGTH]);
    }
}

// Summary function for test results
void fossil_test_summary(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    if (env->options.dry_run) {
        puts(FOSSIL_TEST_COLOR_PURPLE "Dry run mode enabled. No tests were executed or evaluated." FOSSIL_TEST_COLOR_RESET);
        return;
    }

    test_suite_t *suite = env->test_suites;
    while (suite != NULL) {
        test_case_t *test = suite->tests;
        while (test != NULL) {
            if (test->status == TEST_STATUS_PASS) {
                env->pass_count++;
            } else if (test->status == TEST_STATUS_FAIL) {
                env->fail_count++;
                if (test->failure_message) {
                    printf("Test '%s' failed: %s\n", test->name, test->failure_message);
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

    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "===================================================================" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD FOSSIL_TEST_ATTR_ITATIC "\nFossil Test Summary:\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "===================================================================\n" FOSSIL_TEST_COLOR_RESET);

    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Passed: " FOSSIL_TEST_COLOR_ORANGE " %d\n" FOSSIL_TEST_COLOR_RESET, env->pass_count);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Failed: " FOSSIL_TEST_COLOR_ORANGE " %d\n" FOSSIL_TEST_COLOR_RESET, env->fail_count);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Skipped:" FOSSIL_TEST_COLOR_ORANGE " %d\n" FOSSIL_TEST_COLOR_RESET, env->skip_count);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Timeout:" FOSSIL_TEST_COLOR_ORANGE " %d\n" FOSSIL_TEST_COLOR_RESET, env->timeout_count);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Total: %d tests\n" FOSSIL_TEST_COLOR_RESET, env->pass_count + env->fail_count + env->skip_count);

    // Optionally, you could add the total execution time summary here
    double total_execution_time = (double)(env->end_execution_time - env->start_execution_time) / CLOCKS_PER_SEC;
    int seconds = (int)total_execution_time;
    int milliseconds = (int)((total_execution_time - seconds) * 1000);
    int microseconds = (int)((total_execution_time - seconds - milliseconds / 1000.0) * 1000000);

    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "===================================================================\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITATIC "Execution time: (%.2d) seconds, (%.2d) milliseconds, (%.3d) microseconds\n" FOSSIL_TEST_COLOR_RESET, seconds, milliseconds, microseconds);
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "===================================================================\n" FOSSIL_TEST_COLOR_RESET);

    fossil_test_message(env);
}
