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

#include "fossil/_common/common.h"
#include "fossil/_common/platform.h"
#include "types.h"
#include "feature.h"
#include "commands.h"
#include "console.h"

/**
 * Introspection Data in Fossil Test
 *
 * Introspection, in the context of Fossil Test, refers to the process of gathering
 * detailed information about the testing environment. This information is crucial
 * for ensuring test stability, reliability, and portability across different
 * platforms and environments. Fossil Test relies heavily on introspection data to
 * adapt its behavior dynamically based on the characteristics of the system where
 * it runs.
 *
 * The importance of introspection data can be summarized as follows:
 *
 * 1. System Compatibility:
 *    Introspection data allows Fossil Test to identify the underlying architecture,
 *    operating system, CPU count, endianness, and memory size of the test environment.
 *    This information is vital for ensuring that tests execute correctly on diverse
 *    platforms, including ARM, Windows, macOS, and various POSIX-based systems.
 *
 * 2. Test Adaptation:
 *    By analyzing introspection data, Fossil Test can adapt its behavior and configuration
 *    to suit the characteristics of the current environment. For example, the console
 *    output may be adjusted based on the console width and height, and color support
 *    may be enabled or disabled depending on the capabilities of the terminal.
 *
 * 3. Performance Optimization:
 *    Introspection data helps Fossil Test optimize test execution performance by providing
 *    insights into system resources such as CPU count and memory size. This information
 *    allows Fossil Test to allocate resources efficiently and prioritize test execution
 *    based on available hardware resources.
 *
 * 4. Cross-Platform Testing:
 *    With introspection data, Fossil Test can facilitate cross-platform testing by
 *    identifying and handling platform-specific differences transparently. Whether
 *    running on Windows, macOS, Linux, or other operating systems, Fossil Test can
 *    leverage introspection data to ensure consistent test behavior and results.
 *
 * In conclusion, introspection data forms the foundation of Fossil Test's ability
 * to operate effectively in diverse testing environments. By gathering and analyzing
 * detailed information about the test environment, Fossil Test enhances compatibility,
 * adaptability, performance, and cross-platform testing capabilities, thereby
 * empowering developers to write robust and portable test suites.
 */

#ifdef __cplusplus
extern "C"
{
#endif

extern fossil_env_t _fossil_test_env;

// =================================================================
// Initial implementation
// =================================================================

// Internal functions for envirment logic
/**
 * @brief Creates the test environment.
 * 
 * This function creates the test environment by initializing the necessary
 * data structures and setting up the environment based on the command line
 * arguments.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return The created test environment.
 */
fossil_env_t _fossil_test_environment_create(int argc, char** argv);

/**
 * @brief Erases the test environment.
 * 
 * This function erases the test environment by freeing the allocated memory
 * and cleaning up any resources used by the environment.
 */
void _fossil_test_environment_erase(void);

/**
 * @brief Adds a test case to the test environment.
 * 
 * This function adds a test case to the test environment. It associates the
 * test case with the specified fixture, if provided.
 * 
 * @param test_env The test environment.
 * @param test_case The test case to be added.
 * @param fixture The fixture associated with the test case.
 */
void _fossil_test_environment_add(fossil_env_t* test_env, fossil_test_t* test_case, fossil_fixture_t* fixture);

/**
 * @brief Runs the test environment.
 * 
 * This function runs the test environment by executing all the test cases
 * added to the environment.
 */
void _fossil_test_environment_run(void);

/**
 * @brief Summarizes the test environment.
 * 
 * This function summarizes the test environment by providing a summary of
 * the test results, including the number of passed, failed, and skipped
 * test cases.
 * 
 * @return The test summary.
 */
int _fossil_test_environment_summary(void);

// Internal functions for managing analysis of test cases

/**
 * @brief Updates the scoreboard based on the test results.
 * 
 * This function updates the scoreboard based on the test results. It
 * calculates the number of passed, failed, and skipped test cases and
 * updates the corresponding counters in the scoreboard.
 * 
 * @param test_env The test environment.
 */
void _fossil_test_scoreboard_update(fossil_env_t* test_env);

/**
 * @brief Checks the expected rules against the test results.
 * 
 * This function checks the expected rules against the test results. It
 * compares the actual test results with the expected results specified
 * in the test case and updates the scoreboard accordingly.
 * 
 * @param test_env The test environment.
 */
void _fossil_test_scoreboard_expected_rules(fossil_env_t* test_env);

/**
 * @brief Checks the unexpected rules against the test results.
 * 
 * This function checks the unexpected rules against the test results. It
 * compares the actual test results with the unexpected results specified
 * in the test case and updates the scoreboard accordingly.
 * 
 * @param test_env The test environment.
 */
void _fossil_test_scoreboard_unexpected_rules(fossil_env_t* test_envm);

/**
 * @brief Checks the feature rules against the test results.
 * 
 * This function checks the feature rules against the test results. It
 * compares the actual test results with the feature rules specified
 * in the test case and updates the scoreboard accordingly.
 * 
 * @param test_env The test environment.
 * @param test_case The test case.
 */
void _fossil_test_scoreboard_feature_rules(fossil_env_t* test_env, fossil_test_t* test_case);

/**
 * @brief Updates the scoreboard based on the test case results.
 * 
 * This function updates the scoreboard based on the test case results. It
 * calculates the number of passed, failed, and skipped test cases and
 * updates the corresponding counters in the scoreboard.
 * 
 * @param test_env The test environment.
 * @param test_case The test case.
 */
void _fossil_test_scoreboard(fossil_env_t* test_env, fossil_test_t* test_case);

// Internal functions for managing test cases

/**
 * @brief Applies xtags to a test case.
 * 
 * This function applies the specified xtags to the given test case. 
 * It modifies the test case's properties accordingly.
 * 
 * @param test_case A pointer to the test case structure.
 */
void _fossil_test_assume_unit_apply_xtags(fossil_test_t* test_case);

/**
 * @brief Applies marks to a test case.
 * 
 * This function applies the specified marks to the given test case. 
 * It modifies the test case's properties accordingly.
 * 
 * @param test_case A pointer to the test case structure.
 */
void _fossil_test_assume_unit_apply_marks(fossil_test_t* test_case);

/**
 * @brief Executes a unit test case with assumptions.
 * 
 * This function executes a unit test case with assumptions. It checks
 * if the assumptions hold true before running the test case. If any
 * assumption fails, the test case is skipped.
 * 
 * @param test_case A pointer to the test case structure.
 */
void _fossil_test_assume_unit(fossil_test_t* test_case);

/**
 * @brief Executes a unit test case runner with assumptions.
 * 
 * This function executes a unit test case runner with assumptions. It
 * checks if the assumptions hold true before running the test case
 * runner. If any assumption fails, the test case runner is skipped.
 * 
 * @param test_case A pointer to the test case structure.
 */
void _fossil_test_assume_unit_runner(fossil_test_t* test_case);

// algorithms use for advanced assumtions
bool _assume_regex_match(const char *pattern, const char *str);

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
    fossil_fixture_t fixture_name = { setup_##fixture_name, teardown_##fixture_name }

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
    void name##_fossil_test_t(void);                                  \
    fossil_test_t name = {                                            \
        (char*)#name,                                       \
        name##_fossil_test_t,                                         \
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
    void name##_fossil_test_t(void)

#ifdef __cplusplus
}
#endif

#endif
