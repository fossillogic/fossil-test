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
#include "fossil/test/internal.h"

#define FOSSIL_TEST_BUFFER_SIZE 1000

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

// Function to apply color
void internal_test_apply_color(const char *color) {
    if (strcmp(color, "red") == 0) {
        printf(FOSSIL_TEST_COLOR_RED);
    } else if (strcmp(color, "green") == 0) {
        printf(FOSSIL_TEST_COLOR_GREEN);
    } else if (strcmp(color, "yellow") == 0) {
        printf(FOSSIL_TEST_COLOR_YELLOW);
    } else if (strcmp(color, "blue") == 0) {
        printf(FOSSIL_TEST_COLOR_BLUE);
    } else if (strcmp(color, "magenta") == 0) {
        printf(FOSSIL_TEST_COLOR_MAGENTA);
    } else if (strcmp(color, "cyan") == 0) {
        printf(FOSSIL_TEST_COLOR_CYAN);
    } else if (strcmp(color, "white") == 0) {
        printf(FOSSIL_TEST_COLOR_WHITE);
    }
}

// Function to apply text attributes (e.g., bold, underline)
void internal_test_apply_attribute(const char *attribute) {
    if (strcmp(attribute, "bold") == 0) {
        printf(FOSSIL_TEST_ATTR_BOLD);
    } else if (strcmp(attribute, "underline") == 0) {
        printf(FOSSIL_TEST_ATTR_UNDERLINE);
    } else if (strcmp(attribute, "reset") == 0) {
        printf(FOSSIL_TEST_COLOR_RESET);
    } else if (strcmp(attribute, "normal") == 0) {
        printf(FOSSIL_TEST_ATTR_NORMAL);
    } else if (strcmp(attribute, "reversed") == 0) {
        printf(FOSSIL_TEST_ATTR_REVERSED);
    } else if (strcmp(attribute, "blink") == 0) {
        printf(FOSSIL_TEST_ATTR_BLINK);
    } else if (strcmp(attribute, "hidden") == 0) {
        printf(FOSSIL_TEST_ATTR_HIDDEN);
    }
}

// Function to print text with attributes, colors, and format specifiers
void internal_test_print_with_attributes(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[FOSSIL_TEST_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    const char *current_pos = buffer;
    const char *start = NULL;
    const char *end = NULL;

    while ((start = strchr(current_pos, '{')) != NULL) {
        printf("%.*s", (int)(start - current_pos), current_pos);
        end = strchr(start, '}');
        if (end) {
            size_t length = end - start - 1;
            char attributes[length + 1];
            strncpy(attributes, start + 1, length);
            attributes[length] = '\0';

            char *color = NULL;
            char *attribute = NULL;
            char *comma_pos = strchr(attributes, ',');
            if (comma_pos) {
                *comma_pos = '\0';
                color = attributes;
                attribute = comma_pos + 1;
            } else {
                color = attributes;
            }

            if (color) internal_test_apply_color(color);
            if (attribute) internal_test_apply_attribute(attribute);

            current_pos = end + 1;
        } else {
            break;
        }
    }

    printf("%s", current_pos);
    va_end(args);
}

// Internal utility function for color printing
void internal_test_print_color(const char *color, const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("%s", color);
    vprintf(format, args);
    printf("%s", FOSSIL_TEST_COLOR_RESET);
    va_end(args);
}

// Function to print a sanitized string with attributes inside {}
void internal_test_puts(const char *str) {
    if (str != NULL) {
        char sanitized_str[FOSSIL_TEST_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0';
        internal_test_print_with_attributes(sanitized_str);
    } else {
        fputs("NULL\n", stderr);
    }
}

// Function to print a single character
void internal_test_putchar(char c) {
    putchar(c);
}

// Function to print a single character in color
void internal_test_putchar_color(char c, const char *color) {
    printf("%s%c%s", color, c, FOSSIL_TEST_COLOR_RESET);
}

// Function to print sanitized formatted output with attributes
void internal_test_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[FOSSIL_TEST_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);
    internal_test_print_with_attributes(buffer);
    va_end(args);
}
