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
#ifndef FOSSIL_TEST_INTERNAL_H
#define FOSSIL_TEST_INTERNAL_H

#include "common.h"
#include "introspect.h"
#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

static const char* FOSSIL_TEST_NAME = "Fossil Test";
static const char* FOSSIL_TEST_VERSION = "3.0.0";
static const char* FOSSIL_TEST_AUTHOR = "Michael Gene Brockus (Dreamer)";
static const char* FOSSIL_TEST_INFO = "Fossil Test is a next-generation unit testing framework for C.";

extern xenv _fossil_test_env;

// =================================================================
// Initial implementation
// =================================================================

// Internal functions for envirment logic
xenv _fossil_test_environment_create(int argc, char* *argv);
void _fossil_test_environment_erase(void);
void _fossil_test_environment_add(xenv* test_env, xtest* test_case, xfixture* fixture);
void _fossil_test_environment_run(void);
int _fossil_test_environment_summary(void);

// Internal functions for managing analysis of test cases
void _fossil_test_scoreboard_update(xenv* test_env);
void _fossil_test_scoreboard_expected_rules(xenv* test_env);
void _fossil_test_scoreboard_unexpected_rules(xenv* test_envm);
void _fossil_test_scoreboard_feature_rules(xenv* test_env, xtest* test_case);
void _fossil_test_scoreboard(xenv* test_env, xtest* test_case);

// Internal functions for managing test cases
void _fossil_test_assume_unit_apply_xtags(xtest* test_case);
void _fossil_test_assume_unit_apply_marks(xtest* test_case);
void _fossil_test_assume_unit(xtest* test_case);
void _fossil_test_assume_unit_runner(xtest* test_case);

// Runs a test case with a specified fixture within the testing engine
void xbenchmark(char* duration_type, double expected, double actual);
void fossil_test_start_benchmark(void);
uint64_t fossil_test_stop_benchmark(void);

/**
 * @brief Internal function for handling test assertions.
 * 
 * @param expression The expression to evaluate.
 * @param behavior The behavior of the assertion (e.g., ASSERT, EXPECT, ASSUME).
 * @param message The message associated with the assertion.
 * @param file The file name where the assertion occurred.
 * @param line The line number where the assertion occurred.
 * @param func The function name where the assertion occurred.
 */
void _fossil_test_assert_class(bool expression, xassert_type_rule behavior, char* message, char* file, int line, char* func);

/**
 * Applies an xtag to a test case.
 * 
 * This function applies the specified xtag to the given test case. 
 * It modifies the test case's properties accordingly.
 * 
 * @param test_case A pointer to the test case structure.
 * @param tag The xtag to be applied, represented as an 'char*'.
 */
void _fossil_test_apply_xtag(xtest* test_case, char* tag);

/**
 * Applies a mark to a test case.
 * 
 * This function applies the specified mark to the given test case. 
 * It modifies the test case's properties accordingly.
 * 
 * @param test_case A pointer to the test case structure.
 * @param mark The mark to be applied, represented as an 'char*'.
 */
void _fossil_test_apply_mark(xtest* test_case, char* mark);

/**
 * Function to apply a priority to a test case.
 * This function is used to set the priority of a given test case.
 * It is intended to be called indirectly through the APPLY_PRIORITY macro.
 * 
 * @param test_case A pointer to the xtest structure representing the test case.
 * @param priority An integer value representing the priority to be assigned to the test case.
 */
void _fossil_test_apply_priority(xtest *test_case, char* priority);

// algorithms use for advanced assumtions
bool _assume_regex_match(const char *pattern, const char *str);

// Function to generate a random humorous comment about an empty test runner
// becuse way not add a little sillyness.
static inline char* empty_runner_comment(void) {
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
static inline char* helpful_tester_tip(void) {
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

/**
 * @brief Macro to apply a priority to a test case.
 * 
 * This macro is used to apply a priority to a test case. It is used in conjunction
 * with the _APPLY_PRIORITY macro to define the priority to be applied.
 * 
 * @param test_case The test case to which the priority is to be applied.
 * @param priority The priority to be applied.
 */
#define _APPLY_PRIORITY(test_case, priority) _fossil_test_apply_priority(test_case, priority)

/**
 * @brief Macro to apply a tag to a test case.
 * 
 * This macro is used to apply a tag to a test case. It is used in conjunction
 * with the _APPLY_XTAG macro to define the tag to be applied.
 * 
 * @param test_case The test case to which the tag is to be applied.
 * @param xtag The tag to be applied.
 */
#define _APPLY_XTAG(test_case, xtag) _fossil_test_apply_xtag(&test_case, (char*)xtag)

/**
 * @brief Macro to apply a mark to a test case.
 * 
 * This macro is used to apply a mark to a test case. It is used in conjunction
 * with the _APPLY_MARK macro to define the mark to be applied.
 * 
 * @param test_case The test case to which the mark is to be applied.
 * @param mark The mark to be applied.
 */
#define _APPLY_MARK(test_case, mark) _fossil_test_apply_mark(&test_case, (char*)mark)

/**
 * @brief Macro to add a test case.
 * 
 * This macro is used to add a test case. It is used in conjunction with the
 * _ADD_TEST macro to define the test case function.
 * 
 * @param test_case The test case to be added.
 */
#define _ADD_TEST(test_case) _fossil_test_environment_add(test_env, &test_case, xnullptr)

/**
 * @brief Macro to add a test case with a fixture.
 * 
 * This macro is used to add a test case with a fixture. It is used in conjunction
 * with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param test_case The test case to be added.
 * @param fixture The fixture to be added.
 */
#define _ADD_TESTF(test_case, fixture) _fossil_test_environment_add(test_env, &test_case, &fixture)

/**
 * @brief Macro to define a fixture.
 * 
 * This macro is used to define a fixture. It is used in conjunction with the
 * _FOSSIL_SETUP and _FOSSIL_TEARDOWN macros to define the setup and teardown functions for
 * the fixture.
 * 
 * @param fixture_name The name of the fixture.
 * @param setup The setup function for the fixture.
 * @param teardown The teardown function for the fixture.
 */
#define _FOSSIL_FIXTURE(fixture_name) \
    void setup_##fixture_name(void); \
    void teardown_##fixture_name(void); \
    xfixture fixture_name = { setup_##fixture_name, teardown_##fixture_name }

/**
 * @brief Macro to define a setup function for a fixture.
 * 
 * This macro is used to define a setup function for a fixture. It is used in
 * conjunction with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param fixture_name The name of the fixture.
 */
#define _FOSSIL_SETUP(fixture_name) void setup_##fixture_name(void)

/**
 * @brief Macro to define a teardown function for a fixture.
 * 
 * This macro is used to define a teardown function for a fixture. It is used in
 * conjunction with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param fixture_name The name of the fixture.
 */
#define _FOSSIL_TEARDOWN(fixture_name) void teardown_##fixture_name(void)

/**
 * @brief Macro to define a test case.
 * 
 * This macro is used to define a test case. It is used in conjunction with the
 * _FOSSIL_TEST macro to define the test case function.
 * 
 * @param name The name of the test case.
 */
#define _FOSSIL_TEST(name)                                           \
    void name##_xtest(void);                                  \
    xtest name = {                                            \
        (char*)#name,                                       \
        name##_xtest,                                         \
        {                                                     \
            {(char*)"default", TEST_ASSERT_TAG_RULE_DEFAULT}\
        },                                                    \
        {                                                     \
            {(char*)"default", TEST_ASSERT_MARK_RULE_DEFAULT}\
        },                                                    \
        {0, 0, 0, {0, 0, 0, 0, 0}},                           \
        {xnull, xnull},                                       \
        0,                                                    \
        xnull,                                                \
        xnull                                                 \
    };                                                        \
    void name##_xtest(void)

#ifdef __cplusplus
}
#endif

#endif
