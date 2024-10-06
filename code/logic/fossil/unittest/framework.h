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
#ifndef FOSSIL_TEST_FRAMEWORK_H
#define FOSSIL_TEST_FRAMEWORK_H

// Fossil test specific header section of the test framework

#include "fossil/_common/common.h"
#include "fossil/_common/platform.h"
#include "internal.h"
#include "console.h"
#include "commands.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern fossil_env_t _TEST_ENV;
extern xassert_info _ASSERT_INFO;

// =================================================================
// Initial implementation
// =================================================================

// Function prototypes
fossil_env_t fossil_test_environment_create(int argc, char **argv);
void fossil_test_environment_run(fossil_env_t *env);
void fossil_test_environment_add(fossil_env_t *env, fossil_test_t *test, fossil_fixture_t *fixture);
int  fossil_test_environment_summary(void);

void fossil_test_apply_mark(fossil_test_t *test, const char *mark);
void fossil_test_apply_xtag(fossil_test_t *test, const char *tag);
void fossil_test_apply_priority(fossil_test_t *test, const char *priority);

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
void _fossil_test_assert_class(bool expression, xassert_type_t behavior, char* message, char* file, int line, char* func);


/**
 * @brief Macro to apply a priority to a test case.
 * 
 * This macro is used to apply a priority to a test case. It is used in conjunction
 * with the _APPLY_PRIORITY macro to define the priority to be applied.
 * 
 * @param test_case The test case to which the priority is to be applied.
 * @param priority The priority to be applied.
 */
#define _APPLY_PRIORITY(test_case, priority) fossil_test_apply_priority(test_case, (char*)priority)

/**
 * @brief Macro to apply a tag to a test case.
 * 
 * This macro is used to apply a tag to a test case. It is used in conjunction
 * with the _APPLY_XTAG macro to define the tag to be applied.
 * 
 * @param test_case The test case to which the tag is to be applied.
 * @param xtag The tag to be applied.
 */
#define _APPLY_XTAG(test_case, xtag) fossil_test_apply_xtag(&test_case, (char*)xtag)

/**
 * @brief Macro to apply a mark to a test case.
 * 
 * This macro is used to apply a mark to a test case. It is used in conjunction
 * with the _APPLY_MARK macro to define the mark to be applied.
 * 
 * @param test_case The test case to which the mark is to be applied.
 * @param mark The mark to be applied.
 */
#define _APPLY_MARK(test_case, mark) fossil_test_apply_mark(&test_case, (char*)mark)

/**
 * @brief Macro to add a test case.
 * 
 * This macro is used to add a test case. It is used in conjunction with the
 * _ADD_TEST macro to define the test case function.
 * 
 * @param test_case The test case to be added.
 */
#define _ADD_TEST(test_case) fossil_test_environment_add(test_env, &test_case, xnullptr)

/**
 * @brief Macro to add a test case with a fixture.
 * 
 * This macro is used to add a test case with a fixture. It is used in conjunction
 * with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param test_case The test case to be added.
 * @param fixture The fixture to be added.
 */
#define _ADD_TESTF(test_case, fixture) fossil_test_environment_add(test_env, &test_case, &fixture)

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
#define _FOSSIL_TEST(name)          \
    void name##_fossil_test(void);  \
    fossil_test_t name = {          \
        (char*)#name,               \
        name##_fossil_test,         \
        (char*)"fossil",            \
        (char*)"fossil",            \
        {0, 0, 0, {0, 0, 0, 0, 0}}, \
        {xnull, xnull},             \
        0,                          \
        xnull,                      \
        xnull                       \
    };                              \
    void name##_fossil_test(void)

/**
 * @brief Macro to define a test case with a priority.
 * 
 * This macro is used to define a test case with a priority. It is used in conjunction
 * with the _FOSSIL_TEST macro to define the test case function.
 * 
 * @param name The name of the test case.
 * @param priority The priority of the test case.
 */
#define _FOSSIL_TEST_ERASE() fossil_test_environment_summary()

/** Macro to create the test environment.
 * 
 * This macro is used to create the test environment by calling the _fossil_test_environment_create function.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 */
#define _FOSSIL_TEST_CREATE(argc, argv) _TEST_ENV = fossil_test_environment_create(argc, argv)

/** Macro to run the test environment.
 * 
 * This macro is used to run the test environment by calling the fossil_test_environment_run function.
 */
#define _FOSSIL_TEST_RUN() fossil_test_environment_run(&_TEST_ENV)

/**
 * @brief Define macro for defining a test queue.
 * 
 * This macro is used to define a test queue function for a specific test group.
 * It creates a function definition with the given group name and accepts a pointer
 * to a TestRegistry structure as a parameter. This function typically registers
 * all tests within the specified test group to the provided test registry.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_GROUP(group_name) void group_name(fossil_env_t* test_env)

/**
 * @brief Define macro for declaring an external test queue.
 * 
 * This macro is used to declare an external test queue function for a specific
 * test group. It creates an external function declaration with the given group name
 * and accepts a pointer to a TestRegistry structure as a parameter. This declaration
 * allows the test queue function to be defined in a separate source file and linked
 * with the test framework.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_EXPORT(group_name) extern void group_name(fossil_env_t* test_env)

/**
 * @brief Define macro for importing and executing a test queue.
 * 
 * This macro is used to import and execute a test queue function for a specific
 * test group. It calls the test queue function with the provided TestRegistry
 * structure, typically registering all tests within the specified test group
 * to the test registry.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_IMPORT(group_name) group_name(&_TEST_ENV)

#define _GIVEN(description) fossil_test_io_unittest_given(description); if (true)
#define _WHEN(description) fossil_test_io_unittest_when(description);   if (true)
#define _THEN(description) fossil_test_io_unittest_then(description);   if (true)



// =================================================================
// XTest create and erase commands
// =================================================================

/**
 * Macro to create and initialize a test environment.
 * This macro simplifies the process of calling the function to create a test environment,
 * making the code more concise and readable. It initializes an fossil_env_t structure named `test_env`,
 * which is used to manage the state and configuration of the test environment.
 * 
 * Usage: FOSSIL_TEST_CREATE(argc, argv)
 * 
 * @param argc The argument count from the command line. This is typically passed from the `main` function.
 * @param argv The argument vector from the command line. This is typically passed from the `main` function.
 * 
 * Example:
 * int main(int argc, char *argv[]) {
 *     // Initialize the test environment with command-line arguments
 *     FOSSIL_TEST_CREATE(argc, argv);
 *     
 *     // Your test code here
 *     
 *     // Clean up the test environment before exiting
 *     return FOSSIL_TEST_ERASE();
 * }
 */
#define FOSSIL_TEST_CREATE(argc, argv) _FOSSIL_TEST_CREATE(argc, argv)

/**
 * @brief Macro to start the execution of the test environment.
 *
 * This macro serves as the primary entry point to run all the tests
 * defined within the testing framework. When invoked, it calls the 
 * `_fossil_test_environment_run` function, which initializes the testing 
 * environment, executes all the test cases, and provides a summary 
 * of the test results.
 *
 * @details
 * The `_fossil_test_environment_run` function performs several key tasks:
 * 1. Initializes the test environment, which includes setting up
 *    necessary data structures, parsing command-line arguments,
 *    and preparing for test execution.
 * 2. Executes each test case in the order they were defined or 
 *    according to specified priorities.
 * 3. Collects and aggregates test results, including counts of 
 *    passed, failed, skipped, and timed-out tests.
 * 4. Generates and outputs a summary report of the test execution,
 *    providing detailed information about each test case and the 
 *    overall testing outcome.
 *
 * Usage:
 * To use this macro, simply include it at the point in your test 
 * program where you want to initiate the test execution. Typically, 
 * this is done at the end of the `main` function after all test 
 * cases have been defined and added to the test suite.
 *
 * Example:
 * @code
 * int main(int argc, char *argv[]) {
 *     // Initialize the test suite and define test cases
 *     fossil_test_define_cases();
 * 
 *     // Run all defined test cases
 *     FOSSIL_TEST_RUN();
 * 
 *     return 0;
 * }
 * @endcode
 *
 * Note:
 * - Ensure that all test cases are defined and properly configured
 *   before invoking `FOSSIL_TEST_RUN()`. Any test cases added after the 
 *   macro is called will not be executed.
 * - This macro abstracts the complexity of the underlying test 
 *   execution function, providing a clean and simple interface for 
 *   running the tests.
 *
 * @see _fossil_test_environment_run
 */
#define FOSSIL_TEST_RUN() _FOSSIL_TEST_RUN()

/**
 * Macro to erase and clean up the test environment.
 * This macro simplifies the process of calling the function to clean up the test environment,
 * ensuring that all allocated resources are properly released and the environment is reset.
 * It operates on the `test_env` variable that was initialized using the FOSSIL_TEST_CREATE macro.
 * 
 * Usage: FOSSIL_TEST_ERASE()
 * 
 * Example:
 * int main(int argc, char *argv[]) {
 *     // Initialize the test environment with command-line arguments
 *     FOSSIL_TEST_CREATE(argc, argv);
 *     
 *     // Your test code here
 *     
 *     // Clean up the test environment before exiting
 *     return FOSSIL_TEST_ERASE();
 * }
 */
#define FOSSIL_TEST_ERASE() _FOSSIL_TEST_ERASE()

// =================================================================
// XTest run commands
// =================================================================

/**
 * @brief Assign a mark to a test case.
 *
 * This macro is used to apply a mark to a given test case. It wraps the
 * _fossil_test_apply_mark function, providing a convenient way to mark test cases
 * with specific attributes or states.
 *
 * @param test_case The test case to which the mark will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param mark      The mark to assign to the test case. This is typically a string
 *                  used to indicate specific attributes or states of the test case.
 *                  The mark is cast to char* for compatibility.
 *
 * Example usage:
 * 
 * APPLY_MARK(my_test_case, "skip");
 *
 * This would mark 'my_test_case' with the "skip" mark, indicating that the test
 * should be skipped during execution.
 */
#define APPLY_MARK(test_case, mark) _APPLY_MARK(test_case, mark)

/**
 * @brief Assign an xtag to a test case.
 *
 * This macro is used to apply an xtag (extra tag) to a given test case. It wraps
 * the _fossil_test_apply_xtag function, providing a convenient way to tag test cases
 * with additional metadata.
 *
 * @param test_case The test case to which the xtag will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param xtag      The xtag to assign to the test case. This is typically a string
 *                  used to add additional metadata or categorization to the test
 *                  case. The xtag is cast to char* for compatibility.
 *
 * Example usage:
 * 
 * APPLY_XTAG(my_test_case, "regression");
 *
 * This would tag 'my_test_case' with the "regression" xtag.
 */
#define APPLY_XTAG(test_case, xtag) _APPLY_XTAG(test_case, xtag)

/**
 * @brief Assign a priority to a test case.
 *
 * This macro is used to set the priority of a given test case. It wraps the
 * _fossil_test_apply_priority function, providing a more intuitive and convenient
 * way to specify test priorities in the code.
 *
 * @param test_case The test case to which the priority will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param priority  The priority level to assign to the test case. Higher values
 *                  typically indicate higher priority, though this depends on the
 *                  implementation details of _fossil_test_apply_priority.
 *
 * Example usage:
 * 
 * APPLY_PRIORITY(my_test_case, 5);
 *
 * This would set the priority of 'my_test_case' to 5.
 */
#define APPLY_PRIORITY(test_case, priority) _APPLY_PRIORITY(test_case, priority)

/**
 * @brief Macro for adding a test to the test registry.
 * 
 * This macro is used to add a test to the test registry. It takes the test
 * name as an argument and adds the corresponding Test structure to the registry.
 * 
 * @param test The test to be added to the registry.
 */
#define ADD_TEST(test_case) _ADD_TEST(test_case)

/**
 * @brief Macro for adding a test with a fixture to the test registry.
 * 
 * This macro is used to add a test with a fixture to the test registry. It
 * takes the test name and fixture name as arguments, and adds the corresponding
 * Test structure to the registry, along with the setup and teardown functions
 * for the specified fixture.
 * 
 * @param test The test to be added to the registry.
 * @param fixture The fixture associated with the test.
 */
#define ADD_TESTF(test_case, fixture) _ADD_TESTF(test_case, fixture)

/**
 * @brief Define macro for declaring a test fixture.
 * 
 * This macro is used to declare setup and teardown functions for a test fixture.
 * It creates function declarations for the setup and teardown functions associated
 * with the specified fixture name. These functions typically perform initialization
 * and cleanup tasks before and after each test case, respectively.
 * 
 * @param fixture_name The name of the test fixture.
 */
#define FOSSIL_FIXTURE(fixture_name) _FOSSIL_FIXTURE(fixture_name)

/**
 * @brief Define macro for declaring a BDD test fixture.
 * 
 * This macro is used to declare a BDD test fixture. It creates function declarations
 * for the setup and teardown functions associated with the specified fixture name.
 * These functions typically perform initialization and cleanup tasks before and after
 * 
 * @param fixture_name The name of the test fixture.
 */
#define FOSSIL_FEATURE(fixture_name) _FOSSIL_FIXTURE(fixture_name)

/**
 * @brief Define macro for declaring a setup function for a test fixture.
 * 
 * This macro is used to declare a setup function for a test fixture. It creates
 * a function declaration for the setup function associated with the specified
 * fixture name. This function typically performs initialization tasks before
 * each test case.
 * 
 * @param fixture_name The name of the test fixture.
 */
#define FOSSIL_SETUP(fixture_name) _FOSSIL_SETUP(fixture_name)

/**
 * @brief Define macro for declaring a teardown function for a test fixture.
 * 
 * This macro is used to declare a teardown function for a test fixture. It creates
 * a function declaration for the teardown function associated with the specified
 * fixture name. This function typically performs cleanup tasks after each test case.
 * 
 * @param fixture_name The name of the test fixture.
 */
#define FOSSIL_TEARDOWN(fixture_name) _FOSSIL_TEARDOWN(fixture_name)

/**
 * Defines a test case with a given name and sets up its properties.
 * 
 * This macro generates a function prototype and an instance of an fossil_test_t struct 
 * for the specified test case name. It initializes the test case with default 
 * values for various properties, including mark and tag rules, description 
 * strings, and flags.
 * 
 * @param name The name of the test case. This name is used to generate the function
 *             prototype and the fossil_test_t struct instance.
 */
#define FOSSIL_TEST(name) _FOSSIL_TEST(name)

/**
 * @brief Define macro for a BDD style test case.
 * 
 * This macro is used to define a BDD style test case. It creates a function prototype
 * and an instance of an fossil_test_t struct for the specified test case name. It initializes
 * the test case with default values for various properties, including mark and tag rules,
 * description strings, and flags. This macro is typically used for behavior-driven
 * development (BDD) style tests, where the test case is structured as a series of GIVEN,
 * WHEN, and THEN conditions.
 * 
 * @param name The name of the test case.
 */
#define FOSSIL_SONIREO(name) _FOSSIL_TEST(name)

// =================================================================
// Test pool commands
// =================================================================

/**
 * @brief Define macro for defining a test queue.
 * 
 * This macro is used to define a test queue function for a specific test group.
 * It creates a function definition with the given group name and accepts a pointer
 * to a TestRegistry structure as a parameter. This function typically registers
 * all tests within the specified test group to the provided test registry.
 * 
 * @param group_name The name of the test group.
 */
#define FOSSIL_TEST_GROUP(group_name) _FOSSIL_TEST_GROUP(group_name)

/**
 * @brief Define macro for declaring an external test queue.
 * 
 * This macro is used to declare an external test queue function for a specific
 * test group. It creates an external function declaration with the given group name
 * and accepts a pointer to a TestRegistry structure as a parameter. This declaration
 * allows the test queue function to be defined in a separate source file and linked
 * with the test framework.
 * 
 * @param group_name The name of the test group.
 */
#define FOSSIL_TEST_EXPORT(group_name) _FOSSIL_TEST_EXPORT(group_name)

/**
 * @brief Define macro for importing and executing a test queue.
 * 
 * This macro is used to import and execute a test queue function for a specific
 * test group. It calls the test queue function with the provided TestRegistry
 * structure, typically registering all tests within the specified test group
 * to the test registry.
 * 
 * @param group_name The name of the test group.
 */
#define FOSSIL_TEST_IMPORT(group_name) _FOSSIL_TEST_IMPORT(group_name)

// =================================================================
// BDD specific commands
// =================================================================

/**
 * @brief Define macro for specifying a GIVEN condition in a test scenario.
 * 
 * This macro is used to specify a GIVEN condition in a test scenario.
 * It allows the test writer to describe the initial context or setup
 * for the test. The condition is always true, indicating that the
 * GIVEN condition is assumed to be true for the test scenario.
 * 
 * @param description The description of the GIVEN condition.
 */
#define GIVEN(description) _GIVEN(description)

/**
 * @brief Define macro for specifying a WHEN condition in a test scenario.
 * 
 * This macro is used to specify a WHEN condition in a test scenario.
 * It allows the test writer to describe the action or event that
 * triggers the behavior being tested. The condition is always true,
 * indicating that the WHEN condition is assumed to be true for the
 * test scenario.
 * 
 * @param description The description of the WHEN condition.
 */
#define WHEN(description) _WHEN(description)

/**
 * @brief Define macro for specifying a THEN condition in a test scenario.
 * 
 * This macro is used to specify a THEN condition in a test scenario.
 * It allows the test writer to describe the expected outcome or result
 * of the test scenario. The condition is always true, indicating that
 * the THEN condition is assumed to be true for the test scenario.
 * 
 * @param description The description of the THEN condition.
 */
#define THEN(description) _THEN(description)

// =================================================================
// TDD specific commands
// =================================================================

/**
 * @brief Define macro for defining test data structures.
 * 
 * This macro is used to define test data structures for a specific test group.
 * It creates a typedef for the test data structure with the given group name
 * and defines a struct with the same name suffixed with "_xdata".
 * 
 * @param group_name The name of the test group.
 */
#define FOSSIL_TEST_DATA(group_name) typedef struct group_name##_xdata group_name##_xdata; struct group_name##_xdata

/**
 * @brief Define macro for indicating that a test is not implemented yet.
 * 
 * This macro is used to mark a test as not implemented yet. It invokes
 * the TEST_ASSUME macro with a false condition, indicating that the test
 * is not implemented, and includes a message indicating the same.
 */
#define FOSSIL_TEST_NOT_IMPLEMENTED() TEST_ASSUME(false, (char*)"Test not implemented yet")

// =================================================================
// Assertion specific commands
// =================================================================

/**
 * @brief Define macros for test assertions with expression and message.
 * 
 * This macro is used to define a test assertion. It checks the given expression
 * and, if the expression evaluates to false, logs the failure with the provided
 * message, file name, line number, and function name. This type of assertion
 * typically halts the test execution upon failure.
 * 
 * @param expression The expression to be evaluated.
 * @param message The message to log if the assertion fails.
 */
#define TEST_ASSERT(expression, message) \
    _fossil_test_assert_class(expression, TEST_ASSERT_AS_CLASS_ASSERT, (char*)message, (char*)__FILE__, __LINE__, (char*)__func__)

/**
 * @brief Define macros for test expectations with expression and message.
 * 
 * This macro is used to define a test expectation. It checks the given expression
 * and, if the expression evaluates to false, logs the failure with the provided
 * message, file name, line number, and function name. Unlike assertions, expectations
 * typically do not halt the test execution upon failure, allowing subsequent tests to run.
 * 
 * @param expression The expression to be evaluated.
 * @param message The message to log if the expectation fails.
 */
#define TEST_EXPECT(expression, message) \
    _fossil_test_assert_class(expression, TEST_ASSERT_AS_CLASS_EXPECT, (char*)message, (char*)__FILE__, __LINE__, (char*)__func__)

/**
 * @brief Define macros for test assumptions with expression and message.
 * 
 * This macro is used to define a test assumption. It checks the given expression
 * and, if the expression evaluates to false, logs the failure with the provided
 * message, file name, line number, and function name. Assumptions are used to
 * validate preconditions for the test and can halt the test execution if a failure
 * occurs. However, they may allow multiple failures before halting, depending on the implementation.
 * 
 * @param expression The expression to be evaluated.
 * @param message The message to log if the assumption fails.
 */
#define TEST_ASSUME(expression, message) \
    _fossil_test_assert_class(expression, TEST_ASSERT_AS_CLASS_ASSUME, (char*)message, (char*)__FILE__, __LINE__, (char*)__func__)

/**
 * @brief Define macros for exception testing with expression and message.
 * 
 * This macro is used to define a test for exceptions. It checks the given expression
 * and, if the expression evaluates to false, logs the failure with the provided
 * message, file name, line number, and function name. This is typically used to
 * validate that the code under test correctly handles exceptions or error conditions.
 * 
 * @param expression The expression to be evaluated.
 * @param message The message to log if the exception test fails.
 */
#define TEST_EXCEPT(expression, message) \
    _fossil_test_assert_class(expression, TEST_ASSERT_AS_CLASS_EXCEPT, (char*)message, (char*)__FILE__, __LINE__, (char*)__func__)

/**
 * @brief Define macros for sanity pen testing with expression and message.
 * 
 * This macro is used to define a sanity check for penetration testing. It checks
 * the given expression and, if the expression evaluates to false, logs the failure
 * with the provided message, file name, line number, and function name. Sanity checks
 * are typically used for exact validation and security testing to ensure the system
 * behaves as expected under specific conditions.
 * 
 * @param expression The expression to be evaluated.
 * @param message The message to log if the sanity test fails.
 */
#define TEST_SANITY(expression, message) \
    _fossil_test_assert_class(expression, TEST_ASSERT_AS_CLASS_SANITY, (char*)message, (char*)__FILE__, __LINE__, (char*)__func__)

#ifdef __cplusplus
}
#endif

#endif
