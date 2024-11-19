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

#ifdef __WIN32
// Array of messages for each category
const char *sarcastic_messages[] = {
    "Wow, no tests were run! What a productive day!",
    "No tests to run, guess we're all just too good at writing code.",
    "Congratulations, you’ve done absolutely nothing today.",
    "Oh, look! No tests were executed. What an achievement!",
    "Not a single test run, but hey, that's one way to keep things perfect!",
    "All set for a day of zero productivity? Nice!",
    "The test suite is empty, but hey, at least the code didn’t break!",
    "Zero tests executed. Clearly, you've mastered the art of doing nothing.",
    "Great! We’ve made it through an entire test run without running a single test.",
    "Isn’t it great when there’s nothing to test?"
};

const char *humorous_messages[] = {
    "Well, that was an epic failure! Better luck next time!",
    "Whoops! Someone’s definitely gonna need to debug that.",
    "Looks like someone forgot to write the test cases.",
    "Your tests failed, but at least you got closer to perfection... not.",
    "Not all heroes wear capes. Some of them fail tests.",
    "Don't worry, failure is just success in disguise. Or maybe not.",
    "Well, that was awkward. Let's try again, shall we?",
    "Looks like we’ve encountered a bug! Hope you’ve got a magnifying glass.",
    "Your tests are taking a nap, but don’t worry, we’ll wake them up!",
    "It’s not a failure, it’s just a learning experience! A very *expensive* one."
};

const char *great_news_messages[] = {
    "Great news! All tests passed. You’re a testing genius!",
    "Success! Everything works as expected. Go celebrate!",
    "You did it! All tests passed. You’re officially a rock star!",
    "Congrats, all tests passed! You’ve earned a gold star!",
    "Woohoo! All tests passed with flying colors!",
    "No bugs found today, you’re on fire!",
    "Amazing! You’ve got a perfect test suite. Keep it up!",
    "Nice job! All tests passed. I think we’ve found the next coding superhero!",
    "Fantastic! No issues at all, just pure success!",
    "All tests passed, everything’s awesome."
};

#else

// Array of messages for each category
const char *sarcastic_messages[] = {
    "Wow, no tests were run! What a productive day! 😏",
    "No tests to run, guess we're all just too good at writing code. 🧐",
    "Congratulations, you’ve done absolutely nothing today. 🙃",
    "Oh, look! No tests were executed. What an achievement! 🥳",
    "Not a single test run, but hey, that's one way to keep things perfect! 😆",
    "All set for a day of zero productivity? Nice! 💤",
    "The test suite is empty, but hey, at least the code didn’t break! 😜",
    "Zero tests executed. Clearly, you've mastered the art of doing nothing. 😎",
    "Great! We’ve made it through an entire test run without running a single test. 🥳",
    "Isn’t it great when there’s nothing to test? 🙃"
};

const char *humorous_messages[] = {
    "Well, that was an epic failure! Better luck next time! 😂",
    "Whoops! Someone’s definitely gonna need to debug that. 🐞",
    "Looks like someone forgot to write the test cases. 🤷‍♂️",
    "Your tests failed, but at least you got closer to perfection... not. 🤦‍♂️",
    "Not all heroes wear capes. Some of them fail tests. 🦸‍♂️",
    "Don't worry, failure is just success in disguise. Or maybe not. 😅",
    "Well, that was awkward. Let's try again, shall we? 🤔",
    "Looks like we’ve encountered a bug! Hope you’ve got a magnifying glass. 🧐",
    "Your tests are taking a nap, but don’t worry, we’ll wake them up! 😴",
    "It’s not a failure, it’s just a learning experience! A very *expensive* one. 💸"
};

const char *great_news_messages[] = {
    "Great news! All tests passed. You’re a testing genius! 🎉",
    "Success! Everything works as expected. Go celebrate! 🥳",
    "You did it! All tests passed. You’re officially a rock star! 🌟",
    "Congrats, all tests passed! You’ve earned a gold star! 🏅",
    "Woohoo! All tests passed with flying colors! 🎨",
    "No bugs found today, you’re on fire! 🔥",
    "Amazing! You’ve got a perfect test suite. Keep it up! 💪",
    "Nice job! All tests passed. I think we’ve found the next coding superhero! 🦸‍♀️",
    "Fantastic! No issues at all, just pure success! 😎",
    "All tests passed, everything’s awesome. 🎶"
};

#endif

jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp

char *_custom_fossil_test_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *new_str = (char *)malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    memcpy(new_str, str, len);
    return new_str;
}

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
    return options;
}

void usage_info(void) {
    printf("Usage: fossil [options] [command]\n");
    printf("Options:\n");
    printf("  --version\t\tDisplays the current version of Fossil Test\n");
    printf("  --help\t\tShows help message with usage\n");
    printf("  --info\t\tDisplays detailed information about the test run.\n");
    printf("Commands:\n");
    printf("  reverse [enable|disable]\tEnables or disables reverse order of test execution\n");
    printf("  repeat [count]\t\tRepeats the test suite a specified number of times\n");
    printf("  shuffle [enable|disable]\tEnables or disables shuffling of test execution order\n");
}

void version_info(void) {
    printf("Fossil Logic Test Framework\n");
    printf("Version: 1.1.2\n");
    printf("Author: Michael Gene Brockus (Dreamer)\n");
    printf("License: Mozila Public License 2.0\n");
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
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.reverse = false;
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
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.shuffle_enabled = false;
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
    test_suite_t *suite = (test_suite_t*)malloc(sizeof(test_suite_t));
    suite->name = name;
    suite->suite_setup_func = NULL;
    suite->suite_teardown_func = NULL;
    suite->tests = NULL;
    suite->next = NULL;
    return suite;
}

// Registers a test suite in the environment
void fossil_test_register_suite(fossil_test_env_t *env, test_suite_t *suite) {
    if (!suite) return;
    suite->next = env->test_suites;
    env->test_suites = suite;
    if (env->options.show_info) {
        printf(COLOR_INFO "Registered test suite: %s\n" COLOR_RESET, suite->name);
    }
}

// Adds a test case to a suite
void fossil_test_add_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) return;

    test_case->next = suite->tests;
    suite->tests = test_case;
}

// Removes and frees a test case from a suite
void fossil_test_remove_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) return;

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

// Run an individual test case
void fossil_test_run_case(test_case_t *test_case, fossil_test_env_t *env) {
    if (!test_case) return;

    test_case->status = TEST_STATUS_PASS;

    // Run setup
    fossil_test_case_setup(test_case);

    clock_t test_start_time = clock();
    if (setjmp(env->env) == 0) {
        for (int i = 0; i < env->options.repeat_count; i++) {
            test_case->test_func();
        }
    } else {
        test_case->status = TEST_STATUS_FAIL;
        printf(COLOR_FAIL "FAIL: " COLOR_INFO " %s\n", test_case->name);
        printf("Failure Message: %s\n" COLOR_RESET, test_case->failure_message);
    }
    test_case->execution_time = (double)(clock() - test_start_time) / CLOCKS_PER_SEC;

    // Run teardown
    fossil_test_case_teardown(test_case);

    // Log result
    if (test_case->status == TEST_STATUS_PASS) {
        if (env->options.show_info) {
            printf(COLOR_PASS "PASS: " COLOR_INFO " %s (%.3f seconds)\n" COLOR_RESET, test_case->name, test_case->execution_time);
        }
    } else if (test_case->status == TEST_STATUS_FAIL) {
        env->fail_count++;
    } else if (test_case->status == TEST_STATUS_SKIP) {
        env->skip_count++;
    }
}

// Run all test cases in a test suite
void fossil_test_run_suite(test_suite_t *suite, fossil_test_env_t *env) {
    if (!suite) return;

    if (env->options.show_info) {
        printf(COLOR_INFO "Running suite: %s\n" COLOR_RESET, suite->name);
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
        printf(COLOR_CYAN "Total execution time for suite %s: %.3f seconds\n" COLOR_RESET, suite->name, total_execution_time);
    }
}

// Internal function to handle assertions
void fossil_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
    if (!condition) {
        printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

void fossil_test_run_all(fossil_test_env_t *env) {
    test_suite_t *current_suite = env->test_suites;

    while (current_suite) {
        fossil_test_run_suite(current_suite, env);
        current_suite = current_suite->next;
    }
}

void fossil_test_init(fossil_test_env_t *env, int argc, char **argv) {
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
    env->total_tests = 0;
    env->total_execution_time = clock();
    env->unexpected_count = 0;
    env->test_suites = NULL;
}

// Function to generate a dynamic message based on the test results
void fossil_test_message(fossil_test_env_t *env) {
    // Seed random number generator
    srand(time(NULL));

    // Sarcastic message for no tests run
    if (env->pass_count == 0 && env->fail_count == 0 && env->skip_count == 0) {
        printf(COLOR_INFO "%s\n" COLOR_RESET, sarcastic_messages[rand() % 10]);
    }
    // Humorous message for failed tests
    else if (env->fail_count > 0) {
        printf(COLOR_FAIL "%s\n" COLOR_RESET, humorous_messages[rand() % 10]);
    }
    // Great news for passed tests
    else if (env->pass_count > 0) {
        printf(COLOR_PASS "%s\n" COLOR_RESET, great_news_messages[rand() % 10]);
    }
    // Default message for mixed results
    else {
        printf(COLOR_INFO "Test results are in. Keep pushing, you’re getting there! 💪\n" COLOR_RESET);
    }
}

// Summary function for test results
void fossil_test_summary(fossil_test_env_t *env) {
    double total_time = 0.0;
    test_suite_t *suite = env->test_suites;
    while (suite != NULL) {
        test_case_t *test = suite->tests;
        while (test != NULL) {
            total_time += test->execution_time;

            if (test->status == TEST_STATUS_PASS) {
                env->pass_count++;
            } else if (test->status == TEST_STATUS_FAIL) {
                env->fail_count++;
                if (test->failure_message) {
                    printf("Test '%s' failed: %s\n", test->name, test->failure_message);
                }
            } else if (test->status == TEST_STATUS_SKIP) {
                env->skip_count++;
            } else {
                env->unexpected_count++;
            }

            test = test->next;
        }
        suite = suite->next;
    }

    printf(COLOR_INFO "====================================" COLOR_RESET);
    printf(COLOR_INFO "\nFossil Test Summary:\n" COLOR_RESET);
    printf(COLOR_INFO "====================================\n" COLOR_RESET);

    printf(COLOR_INFO "Passed: " COLOR_PASS " %d\n" COLOR_RESET, env->pass_count);
    printf(COLOR_INFO "Failed: " COLOR_FAIL " %d\n" COLOR_RESET, env->fail_count);
    printf(COLOR_INFO "Skipped: " COLOR_SKIP " %d\n" COLOR_RESET, env->skip_count);
    printf(COLOR_INFO "Total: %d tests\n" COLOR_RESET, env->pass_count + env->fail_count + env->skip_count);

    // Optionally, you could add the total execution time summary here
    printf(COLOR_INFO "====================================\n" COLOR_RESET);
    printf(COLOR_INFO "Total execution time: %.3f seconds\n" COLOR_RESET, (env->total_execution_time - total_time) / CLOCKS_PER_SEC);
    printf(COLOR_INFO "====================================\n" COLOR_RESET);

    fossil_test_message(env);
}

void fossil_test_print_stack_trace(stack_frame_t *stack_trace) {
    stack_frame_t *current_frame = stack_trace;
    while (current_frame) {
        printf("  at %s (%s:%d)\n", current_frame->func, current_frame->file, current_frame->line);
        current_frame = current_frame->next;
    }
}
