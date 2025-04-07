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

// Suggestions arrays based on different outcomes
const char *empty_suite_suggestions[] = {
    "Check if your test suite has defined tests.",
    "Make sure your test cases are properly configured.",
    "Review the test configuration to ensure it’s correct.",
    "Verify that your test suite is correctly initialized.",
    "Check if test scripts are properly linked.",
    "Ensure your testing framework is correctly set up.",
    "Double-check if your test directories and files are valid.",
    "Ensure the tests are compiled correctly.",
    "Make sure tests are registered with the test runner.",
    "Verify that all necessary modules are loaded for testing.",
    "Ensure no tests are excluded or skipped by mistake.",
    "Check if you’ve specified the correct test entry points.",
    "Review whether your test framework supports the required features.",
    "Confirm that all test cases are included in the build process.",
    "Verify that no test dependencies are missing.",
    "Ensure that all required test resources are available.",
    "Check if any testing tools need configuration.",
    "Make sure your test suite is executed with the right parameters.",
    "Confirm the right environment variables are set for tests.",
    "Ensure that tests are properly isolated from the system environment.",
    "Check if the tests are being executed in the expected environment.",
    "Verify that your test suite hasn’t been inadvertently disabled.",
    "Check if your test suite has been corrupted or altered.",
    "Make sure your testing environment is up-to-date.",
    "Ensure that the test results are being captured correctly.",
    "Verify that your testing platform supports your test types.",
    "Review if your test framework is up-to-date and compatible.",
    "Ensure tests are not being skipped due to unsupported features.",
    "Check if you have proper logging or error handling in place.",
    "Verify the test output directory is correctly specified.",
    "Check if the test suite outputs meaningful logs or results.",
    "Ensure that all test dependencies are installed and available.",
    "Confirm that your build system includes the necessary test files.",
    "Check for any overlooked configuration settings in the test suite.",
    "Ensure there are no naming conflicts in the test directory structure.",
    "Review your test suite’s memory and resource usage.",
    "Verify that tests are not blocked due to missing permissions.",
    "Check if tests are running with the required privileges.",
    "Make sure your test runner is executing tests in the right order.",
    "Ensure the tests don’t require external resources unavailable in the environment.",
    "Verify that no steps in your test suite are being skipped inadvertently.",
    "Check if there’s a version mismatch between your test framework and environment.",
    "Ensure that you have enough logging output to debug your tests.",
    "Make sure your test environment matches the production environment closely."
};

const char *failure_suggestions[] = {
    "Look into the test failures and their root causes.",
    "Check for bugs, missing dependencies, or misconfigured tests.",
    "Examine the test environment for potential issues.",
    "Review the test case logic and expected behavior.",
    "Consider adding more edge cases to capture hidden bugs.",
    "Check if the failed test cases have valid input data.",
    "Verify that the expected output is correct for failed tests.",
    "Ensure there are no race conditions in your tests.",
    "Review if there are any memory or resource leaks.",
    "Double-check the test setup and teardown procedures.",
    "Look for dependency issues or configuration mismatches.",
    "Verify the test environment matches the expected conditions.",
    "Make sure the test dependencies are properly installed and up to date.",
    "Check if recent changes have affected the test behavior.",
    "Consider increasing the verbosity of your test logs for debugging.",
    "Ensure tests are not dependent on unpredictable external factors.",
    "Review the error messages and stack traces for more details.",
    "Consider running the failed tests in isolation to identify causes.",
    "Ensure you’re not testing with outdated or incorrect input data.",
    "Check if the failure is due to a logic error in the application.",
    "Test the system under a variety of conditions to expose hidden bugs.",
    "Try different configurations or platforms to identify the issue.",
    "Check the system’s resource usage to ensure it isn’t causing the failure.",
    "Verify that the failure doesn’t result from a system or platform limitation.",
    "Review recent updates in the codebase that might impact test behavior.",
    "Test the specific test case individually and ensure correct behavior.",
    "Check for inconsistencies between the test case and actual implementation.",
    "Ensure that third-party dependencies are compatible with your tests.",
    "Re-examine the test case for edge cases that were missed.",
    "Look into whether any time-dependent issues are causing failures.",
    "Check if there are any environment-specific issues affecting tests.",
    "Test the system with smaller, isolated inputs to identify bugs.",
    "Investigate any external resources required for tests to work properly.",
    "Try running the test suite on a different platform or environment.",
    "Look into possible memory corruption or incorrect memory handling.",
    "Check if the test’s timing constraints or limits are too tight.",
    "Review error-handling mechanisms to ensure proper feedback.",
    "Consider testing with more realistic inputs to simulate real-world behavior.",
    "Verify if test failures are isolated or part of a larger systemic issue.",
    "Make sure test cases correctly handle different user scenarios.",
    "Check if failures are related to thread safety or parallel execution.",
    "Consider running tests under various loads to stress the system.",
    "Try testing with different versions of dependencies to rule out compatibility issues."
};

const char *success_suggestions[] = {
    "Great job! Keep adding tests to cover edge cases.",
    "Fantastic! Consider adding performance and stress tests.",
    "Success! Now, look at adding additional tests for edge cases.",
    "Well done! You’re on the right track, keep it up.",
    "Good job! Now, consider reviewing code for possible optimizations.",
    "Excellent work! Think about testing with larger input datasets.",
    "Well done! Consider testing under load to simulate real-world conditions.",
    "Great! Time to refine the code and improve error handling.",
    "Nice work! Next, consider checking for potential memory leaks.",
    "Awesome! Try adding tests for concurrency and thread safety.",
    "Great success! Start testing for edge cases and unexpected inputs.",
    "Well done! Ensure tests are comprehensive and cover every possible scenario.",
    "Excellent! Look into integrating continuous integration for automated tests.",
    "Fantastic job! Start testing the performance of the system under stress.",
    "Great work! Keep iterating to improve coverage and test completeness.",
    "Awesome! Make sure to run tests in various environments to ensure compatibility.",
    "Well done! Try testing with more complex data structures and inputs.",
    "Excellent! Don’t forget to add edge cases and potential failure modes.",
    "Nice! Keep up the great work and start testing corner cases.",
    "Great! Keep building up your test coverage to ensure robust software.",
    "Nice! Ensure that your tests cover all relevant code paths.",
    "Fantastic! Consider using mock objects to improve test isolation.",
    "Awesome! Now look into running automated tests on multiple platforms.",
    "Excellent! Test your code under different load conditions for scalability.",
    "Great! Review your test output to ensure all cases are covered.",
    "Well done! Think about testing for long-term stability and memory usage.",
    "Fantastic! Time to start profiling the application’s performance.",
    "Nice work! Think about optimizing the system after completing testing.",
    "Awesome! Ensure your tests reflect real-world usage patterns.",
    "Great! Start testing the system with different network configurations.",
    "Nice! Keep up the good work by testing boundary cases for reliability.",
    "Excellent! Begin testing different configurations for system flexibility.",
    "Fantastic! Add integration tests to ensure different components work together.",
    "Great! Consider using fuzz testing to uncover hidden bugs.",
    "Well done! Add regression tests to catch issues with new changes.",
    "Awesome! Time to start integrating tests with your build pipeline.",
    "Excellent! Keep improving your test cases to cover all edge conditions.",
    "Nice! Think about automating test execution for faster feedback.",
    "Fantastic! Keep testing under high load to ensure stability and performance.",
    "Awesome! Consider testing the system's scalability under high traffic.",
    "Great! Don’t forget to validate that the system handles all error conditions.",
    "Nice! Keep testing in various environments for cross-platform compatibility.",
    "Well done! Think about adding security tests for potential vulnerabilities."
};

const char *timeout_suggestions[] = {
    "Check resource usage and adjust timeout values.",
    "Investigate slow-running tests and optimize them.",
    "Consider breaking large tests into smaller ones to avoid timeouts.",
    "Check for any environmental factors affecting test performance.",
    "Consider adjusting the test parameters to reduce execution time.",
    "Examine the test case to ensure there are no infinite loops or deadlocks.",
    "Look into possible network issues if tests depend on network resources.",
    "Consider profiling the test to identify performance bottlenecks.",
    "Check if the system is running out of memory or resources during tests.",
    "Try running tests with different configurations to pinpoint the cause.",
    "Investigate test dependencies to ensure they don’t block execution.",
    "Ensure your system is not overloaded with other processes during tests.",
    "Look into optimizing algorithms to reduce test execution time.",
    "Consider running tests in parallel to speed up overall execution.",
    "Check if the system has enough hardware resources to handle tests.",
    "Test with smaller data sets to see if the timeout issue persists.",
    "Look into reducing unnecessary waits or sleep intervals in the test cases.",
    "Check if the timeout values are set appropriately for different test cases.",
    "Investigate if any external services are slowing down the tests.",
    "Ensure tests are isolated and not dependent on external factors.",
    "Consider adjusting the execution environment to improve performance.",
    "Make sure tests are not waiting on unnecessary synchronization.",
    "Try optimizing your code to avoid long-running operations in tests.",
    "Check if there are any operations that can be optimized for speed.",
    "Investigate if the timeout is caused by network latency or delays.",
    "Ensure that timeout values reflect the actual test execution times.",
    "Break tests into smaller chunks to better manage timeouts.",
    "Check the system logs for errors or warnings during test execution.",
    "Look into improving the algorithmic complexity of long-running tests.",
    "Consider adding more logging to track where the test is stalling.",
    "Ensure the environment is clean and not affecting test performance.",
    "Try testing on a different platform to compare execution times.",
    "Look into system-wide performance issues affecting the tests.",
    "Test the system under a reduced load to identify performance bottlenecks.",
    "Consider adding more granular timeout checks to diagnose issues.",
    "Investigate whether background processes are affecting test performance.",
    "Test in a more controlled environment to eliminate external influences.",
    "Consider using profiling tools to identify long-running sections in the tests.",
    "Check if running tests in isolation resolves the timeout issues.",
    "Look into optimizing data access patterns in long-running tests.",
    "Consider breaking tests into independent smaller tests to improve performance.",
    "Investigate if there are unnecessary dependencies in the test cases.",
    "Consider using mock data to speed up test execution and avoid delays.",
    "Check if large input sizes are contributing to the timeout.",
    "Investigate if your timeout limits need adjustment for specific tests."
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
    return options;
}

void usage_info(void) {
    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Usage: fossil [options] [command]"                                   FOSSIL_TEST_COLOR_RESET);
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "===================================================================" FOSSIL_TEST_COLOR_RESET);
    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD   "\tOptions:" FOSSIL_TEST_COLOR_RESET);
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_OPTIONS) / sizeof(FOSSIL_TEST_OPTIONS[0]); i++) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\t>\t%s" FOSSIL_TEST_COLOR_RESET, FOSSIL_TEST_OPTIONS[i]);
    }

    puts(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD   "\tCommands:" FOSSIL_TEST_COLOR_RESET);
    for (size_t i = 0; i < sizeof(FOSSIL_TEST_COMMANDS) / sizeof(FOSSIL_TEST_COMMANDS[0]); i++) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\t>\t%s" FOSSIL_TEST_COLOR_RESET, FOSSIL_TEST_COMMANDS[i]);
    }
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "===================================================================" FOSSIL_TEST_COLOR_RESET);
}

void version_info(void) {
    puts(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD   "Fossil Logic Test Framework");
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\tVersion: %s\n", FOSSIL_TEST_VERSION);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\tAuthor: %s\n", FOSSIL_TEST_AUTHOR);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\tLicense: %s\n", FOSSIL_TEST_LICENSE);
}

// Parse command-line arguments
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
        printf(FOSSIL_TEST_COLOR_BLUE "Registered test suite: %s\n" FOSSIL_TEST_COLOR_RESET, suite->name);
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

// Run all test cases in a test suite
void fossil_test_run_suite(fossil_test_suite_t *suite, fossil_test_env_t *env) {
    if (!suite || !env) {
        return;
    }

    if (env->options.show_info) {
        printf(FOSSIL_TEST_COLOR_BLUE "Running suite: %s\n" FOSSIL_TEST_COLOR_RESET, suite->name);
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
        printf(FOSSIL_TEST_COLOR_CYAN "Total execution time for suite %s: %.3f seconds\n" FOSSIL_TEST_COLOR_RESET,
               suite->name, total_execution_time);
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
            last_message = message;
            last_file = file;
            last_line = line;
            last_func = func;
            printf(FOSSIL_TEST_COLOR_RED "Assertion failed: %s (%s:%d in %s)\n" FOSSIL_TEST_COLOR_RESET, message, file, line, func);
        }

        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

// Run an individual test case
void fossil_test_run_case(fossil_test_case_t *test_case, fossil_test_env_t *env) {
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
                printf(FOSSIL_TEST_COLOR_ORANGE "TIMEOUT: " FOSSIL_TEST_COLOR_BLUE "%s\n" FOSSIL_TEST_COLOR_RESET, test_case->name);
                break;
            }
        }
    } else {
        test_case->status = TEST_STATUS_FAIL;
        printf(FOSSIL_TEST_COLOR_RED "FAILED: " FOSSIL_TEST_COLOR_BLUE "%s\n", test_case->name);
        printf("Failure Message: %s\n" FOSSIL_TEST_COLOR_RESET, test_case->failure_message);
    }

    clock_t end_iter = clock();
    test_case->execution_time = (double)(end_iter - start_iter) / CLOCKS_PER_SEC;

    fossil_fossil_test_case_teardown(test_case);

    switch (test_case->status) {
        case TEST_STATUS_PASS:
            if (env->options.show_info) {
                printf(FOSSIL_TEST_COLOR_GREEN "PASSED: " FOSSIL_TEST_COLOR_BLUE "%s (%.3f seconds)\n" FOSSIL_TEST_COLOR_RESET,
                       test_case->name, test_case->execution_time);
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

    fossil_test_suite_t *current_suite = env->test_suites;

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

void fossil_test_comment(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Dynamic comment based on test result
    if (env->pass_count > 0 && env->fail_count == 0 && env->timeout_count == 0) {
        // Positive outcome - playful
        printf(FOSSIL_TEST_COLOR_CYAN "Comment: %s\n" FOSSIL_TEST_COLOR_RESET, great_news_messages[rand() % (sizeof(great_news_messages) / sizeof(great_news_messages[0]))]);
    } else if (env->fail_count > 0) {
        // Failure detected - humorous to lighten the mood
        printf(FOSSIL_TEST_COLOR_RED "Comment: %s\n" FOSSIL_TEST_COLOR_RESET, humorous_messages[rand() % (sizeof(humorous_messages) / sizeof(humorous_messages[0]))]);
    } else if (env->timeout_count > 0) {
        // Timeout encountered - insightful
        printf(FOSSIL_TEST_COLOR_ORANGE "Comment: %s\n" FOSSIL_TEST_COLOR_RESET, timeout_messages[rand() % (sizeof(timeout_messages) / sizeof(timeout_messages[0]))]);
    } else if (env->pass_count == 0 && env->fail_count == 0 && env->timeout_count == 0) {
        // No results - sarcastic twist
        printf(FOSSIL_TEST_COLOR_CYAN "Comment: %s\n" FOSSIL_TEST_COLOR_RESET, sarcastic_messages[rand() % (sizeof(sarcastic_messages) / sizeof(sarcastic_messages[0]))]);
    } else {
        // Mixed results - deeper analysis
        printf(FOSSIL_TEST_COLOR_CYAN "Comment: The test results are mixed. Consider analyzing individual test cases to uncover underlying issues.\n" FOSSIL_TEST_COLOR_RESET);
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
        printf(FOSSIL_TEST_COLOR_CYAN "Failure rate: %.2f%%\n" FOSSIL_TEST_COLOR_RESET, failure_rate);
    }

    // Next worst: Timeout tests
    if (env->timeout_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN "Timeout tests: %.2f%%\n" FOSSIL_TEST_COLOR_RESET, timeout_rate);
    }

    // Skipped tests next
    if (env->skip_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN "Skipped tests: %.2f%% (%d tests)\n" FOSSIL_TEST_COLOR_RESET, skip_rate, env->skip_count);
    }

    // Best case: Success rate
    if (env->pass_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN "Success rate: %.2f%%\n" FOSSIL_TEST_COLOR_RESET, success_rate);
    }

    // Additional insights
    printf(FOSSIL_TEST_COLOR_CYAN "Probability of success: %.2f\n" FOSSIL_TEST_COLOR_RESET, probability_of_success);
    printf(FOSSIL_TEST_COLOR_CYAN "Average test rate: %.2f%%\n" FOSSIL_TEST_COLOR_RESET, average_rate);
    printf(FOSSIL_TEST_COLOR_CYAN "Prediction (Future Success Rate): %.2f%%\n" FOSSIL_TEST_COLOR_RESET, prediction);

    // Skipped tests analysis route
    if (env->skip_count > 0) {
        printf(FOSSIL_TEST_COLOR_YELLOW "Note: There were %d skipped tests. Please check the conditions or requirements for those tests.\n" FOSSIL_TEST_COLOR_RESET, env->skip_count);
    }
}

void fossil_test_suggest(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Dynamic suggestion based on results and test state
    if (env->pass_count == 0 && env->fail_count == 0 && env->skip_count == 0 && env->timeout_count == 0 && env->empty_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Suggestion: %s\n" FOSSIL_TEST_COLOR_RESET, empty_suite_suggestions[rand() % 50]);
    } else if (env->fail_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Suggestion: %s\n" FOSSIL_TEST_COLOR_RESET, failure_suggestions[rand() % 50]);
    } else if (env->pass_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Suggestion: %s\n" FOSSIL_TEST_COLOR_RESET, success_suggestions[rand() % 50]);
    } else if (env->timeout_count > 0) {
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Suggestion: %s\n" FOSSIL_TEST_COLOR_RESET, timeout_suggestions[rand() % 50]);
    } else if (env->skip_count > 0) {
        // Skipped tests specific suggestions
        printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "Suggestion: Review skipped tests for prerequisites or intentional exclusions. Ensure tests are not being skipped due to unmet conditions.\n" FOSSIL_TEST_COLOR_RESET);
    }
}

// Function to calculate and provide AI-driven insights and predictions based on execution time
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
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "==================================================================================\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\tInsight: Based on the execution time analysis, we observe the following:\n" FOSSIL_TEST_COLOR_RESET);

    // Anomaly Detection & Optimization Insight
    if (total_execution_time > 5.0) {
        printf(
            "Execution time is exceptionally long, indicating possible critical\n"
            "inefficiencies, extensive test coverage, or hardware constraints.\n"
            "Investigate parallel execution strategies, resource bottlenecks, or\n"
            "excessive test dependencies. Consider breaking test suites into smaller\n"
            "units to isolate performance-heavy areas.\n"
        );
    } else if (total_execution_time > 2.0) {
        printf(
            "Execution time is unusually long, suggesting potential bottlenecks\n"
            "or inefficiencies in the test suite. Optimization strategies, such as\n"
            "test parallelization or resource allocation adjustments, could help\n"
            "reduce time consumption.\n"
        );
    } else if (total_execution_time < 0.2) {
        printf(
            "Execution time is abnormally short. This could mean tests were\n"
            "skipped or misconfigured. Ensure full test coverage is executed and\n"
            "no critical paths are being inadvertently bypassed in the\n"
            "environment.\n"
        );
    }

    // Footer and execution time display
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "==================================================================================\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "|\tExecution time:\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "|\t(%02d) sec, (%03d) ms, (%06d) us, (%09d) ns\n" FOSSIL_TEST_COLOR_RESET, (int32_t)seconds, (int32_t)milliseconds, (int32_t)microseconds, (int32_t)nanoseconds);
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "==================================================================================\n" FOSSIL_TEST_COLOR_RESET);
}

void fossil_test_summary(fossil_test_env_t *env) {
    if (!env) {
        return;
    }

    // Check dry run mode
    if (env->options.dry_run) {
        printf(FOSSIL_TEST_COLOR_PURPLE "Dry run mode enabled. No tests were executed or evaluated.\n" FOSSIL_TEST_COLOR_RESET);
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
                    printf(FOSSIL_TEST_COLOR_RED "Test '%s' failed: %s\n" FOSSIL_TEST_COLOR_RESET, test->name, test->failure_message);
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
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "==================================================================================\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_ITALIC "\tFossil Test Summary\n" FOSSIL_TEST_COLOR_RESET);
    printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD "==================================================================================\n" FOSSIL_TEST_COLOR_RESET);

    fossil_test_analyze(env);  // Add analysis of test results
    fossil_test_comment(env);  // Add comments based on results
    fossil_test_suggest(env);  // Add suggestions for improvement
    fossil_test_execution_time(env);
}
