/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include "fossil/unittest/console.h"
#include "fossil/unittest/internal.h"
#include <stdarg.h>

static const char* FOSSIL_TEST_NAME = "Fossil Test";
static const char* FOSSIL_TEST_VERSION = "1.0.0";
static const char* FOSSIL_TEST_AUTHOR = "Michael Gene Brockus (Dreamer)";
static const char* FOSSIL_TEST_INFO = "Fossil Test is a next-generation unit testing/mockup framework for C/C++.";

// ==============================================================================
// Xtest internal console stream logic
// ==============================================================================

// Function to generate a random humorous comment about an empty test runner
// becuse way not add a little sillyness.
char* empty_runner_comment(void) {
    char* comments[] = { // add more to this
        "Looks like the test runner is on a coffee break!",
        "The test runner is feeling a bit empty today, like my coffee cup.",
        "The test runner is as empty as a developer's coffee mug on Monday morning.",
        "Did someone forget to load the tests? The runner seems quite empty!",
        "The test runner is as empty as a promise to write documentation.",
        "The test runner is emptier than a developer's promise to refactor code.",
        "The test runner seems to be on a diet - it's looking quite empty!",
        "Did the tests escape? The runner seems unusually empty!",
        "The test runner is as empty as a JavaScript developer's promises.",
        "The test runner seems as empty as my enthusiasm for Monday mornings.",
        "The test runner is emptier than a meeting agenda without a clear purpose.",
        "The test runner is looking as empty as a developer's patience with legacy code.",
        "The test runner is as empty as a database without any data.",
        "The test runner seems to be in stealth mode - it's quite empty!",
        "The test runner is emptier than a startup's promise of equity.",
        "The test runner is as empty as a meeting room during a free lunch seminar.",
        "The test runner is looking as empty as a developer's snack stash on Friday afternoon.",
        "The test runner seems to be as empty as a Git repository with no commits.",
        "The test runner is emptier than a developer's memory after a long debugging session.",
        "The test runner is looking as empty as a developer's inbox after vacation.",
        "The test runner is as empty as a conference room during a fire drill.",
        "The test runner seems to be as empty as a developer's coffee pot after a long night of coding.",
        "The test runner is emptier than a developer's promise to write unit tests."
    };

    int num_comments = sizeof(comments) / sizeof(comments[0]);

    srand(time(xnullptr));

    // Generate a random index
    int random_index = rand() % num_comments;

    return comments[random_index];
}

// Function to generate a random tip for unit testing released tasks
// as this would servse as a handy feature and be helpful for teaching
// new developers how they can write good test cases.
char* helpful_tester_tip(void) {
    char* tips[] = {
        "Always write meaningful test names.",
        "Test both positive and negative cases.",
        "Use mocking for external dependencies.",
        "Run tests frequently during development.",
        "Ensure tests are isolated and independent.",
        "Avoid hardcoding values in test cases.",
        "Focus on testing the functionality, not the implementation.",
        "Regularly update and maintain test cases.",
        "Use code coverage tools to identify untested code.",
        "Test edge cases and boundary conditions.",
        "Keep unit tests fast and repeatable.",
        "Use setup and teardown methods when necessary.",
        "Automate the execution of tests.",
        "Review and refactor tests regularly.",
        "Write tests for both happy paths and error paths.",
        "Test for performance and scalability where applicable.",
        "Use assertions effectively to verify outcomes.",
        "Consider using property-based testing for complex logic.",
        "Document the purpose and expected run_as of each test.",
        "Collaborate with the development team to identify test cases.",
        "Prioritize and focus on critical and high-risk areas.",
        "Write tests early in the development process.",
        "Use version control for test code and test data.",
        "Ensure that tests can run in different environments.",
        "Consider the maintainability and readability of test code.",
        "Use test frameworks and libraries to simplify testing.",
        "Use test data generation tools to create test data.",
        "Use test reporting tools to track test results.",
        "Use test management tools to organize and execute tests.",
        "Use continuous integration to automate test execution."
    };

    int num_tips = sizeof(tips) / sizeof(tips[0]);

    srand(time(xnullptr));

    // Generate a random index
    int random_index = rand() % num_tips;

    return tips[random_index];
}

char* current_datetime(void) {
    time_t rawtime;
    struct tm* timeinfo;
    static char datetime[20];  // Buffer to hold the formatted date and time

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);

    char* copy = _custom_fossil_test_strdup(datetime);  // Return a dynamically allocated copy of the datetime
    if (!copy) {
        return xnullptr; // Check for memory allocation failure
    }

    char* result = _custom_fossil_test_strdup(datetime);  // Return a dynamically allocated copy of the datetime
    free(copy);  // Free the temporary copy

    return result;
}

static char* replace_underscore(const char* str) {
    if (!str) {
        return xnullptr; // Check for xnull input
    }

    char* result = _custom_fossil_test_strdup(str);
    if (!result) {
        return xnullptr; // Check for memory allocation failure
    }

    for (char* ptr = result; *ptr; ptr++) {
        if (*ptr == '_') {
            *ptr = ' ';
        }
    }

    char* copy = _custom_fossil_test_strdup(result);  // Create a copy to free the original
    free(result);  // Free the original

    return copy;
}

// Define color codes
#define COLOR_RED        "\033[1;31m"
#define COLOR_GREEN      "\033[1;32m"
#define COLOR_YELLOW     "\033[1;33m"
#define COLOR_BLUE       "\033[1;34m"
#define COLOR_BRIGHT_BLUE "\033[1;94m"
#define COLOR_DARK_BLUE  "\033[0;34m"
#define COLOR_RESET      "\033[0m"

// Define a structure to map color names to their corresponding codes
typedef struct {
    const char* name;
    const char* code;
} ColorMap;

// printf has its use cases but to handle multable general purpose features without
// forgetting to change a printf this would servse as the internal prinf with color
// and potintal for additnal output releated functionality.
void fossil_test_cout(const char* color_name, const char* format, ...) {
    static const ColorMap color_map[] = {
        {"red", COLOR_RED},
        {"green", COLOR_GREEN},
        {"yellow", COLOR_YELLOW},
        {"blue", COLOR_BLUE},
        {"bright blue", COLOR_BRIGHT_BLUE},
        {"dark blue", COLOR_DARK_BLUE},
        {xnullptr, COLOR_RESET} // Default color
    };

    va_list args;
    va_start(args, format);

    // Check if color output is enabled
    if (strcmp(commands->long_name, "--color") && commands->flag == true) {
        // Default color code
        const char* color_code = COLOR_RESET;

        // Find the corresponding color code
        for (int i = 0; color_map[i].name != xnull; i++) {
            if (strcmp(color_name, color_map[i].name) == 0) {
                color_code = color_map[i].code;
                break;
            }
        }

        // Print color code and formatted string
        printf("%s", color_code);
        vprintf(format, args);
        printf("%s", COLOR_RESET); // Reset color
    } else {
        // Color output disabled, print formatted string directly
        vprintf(format, args);
    }

    va_end(args);
}

void fossil_test_io_unittest_start(fossil_test_t *test);
void fossil_test_io_unittest_ended(fossil_test_t *test);

void fossil_test_io_asserted(xassert_info *assume);

void fossil_test_io_summary_start(fossil_env_t *env);

void fossil_test_io_summary_ended(fossil_env_t *env) {
    fossil_test_cout("blue", "\n%s %s: %S\n", FOSSIL_TEST_NAME, FOSSIL_TEST_VERSION, FOSSIL_TEST_INFO);
    fossil_test_cout("blue", "==============================================================================\n");
    fossil_test_cout("blue", " message: %s\n", empty_runner_comment());
    fossil_test_cout("blue", "  Expected Passed: %3d   Expected Failed: %3d\n", env->stats.expected_passed_count, env->stats.expected_failed_count);
    fossil_test_cout("blue", "Unexpected Passed: %3d Unexpected Failed: %3d\n", env->stats.expected_passed_count, env->stats.expected_failed_count);
    fossil_test_cout("blue", " Timeout Cases: %3d Skipped Cases %3d\n", env->stats.expected_timeout_count, env->stats.expected_skipped_count);
    fossil_test_cout("blue", "==============================================================================\n");
    fossil_test_cout("blue", "Test Summary\n");
    fossil_test_cout("blue", "==============================================================================\n");
    fossil_test_cout("blue", "Total Tests: %d\n", env->stats.expected_total_count);
    fossil_test_cout("blue", "Total Ghost: %d\n", env->stats.untested_count);

}
