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
#ifndef FSCL_XTEST_H
#define FSCL_XTEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xtest/internal.h" // internal header file for xtest

// =================================================================
// XTest create and erase commands
// =================================================================

/**
 * Macro to create and initialize a test environment.
 * This macro simplifies the process of calling the function to create a test environment,
 * making the code more concise and readable. It initializes an xenv structure named `test_env`,
 * which is used to manage the state and configuration of the test environment.
 * 
 * Usage: XTEST_CREATE(argc, argv)
 * 
 * @param argc The argument count from the command line. This is typically passed from the `main` function.
 * @param argv The argument vector from the command line. This is typically passed from the `main` function.
 * 
 * Example:
 * int main(int argc, char *argv[]) {
 *     // Initialize the test environment with command-line arguments
 *     XTEST_CREATE(argc, argv);
 *     
 *     // Your test code here
 *     
 *     // Clean up the test environment before exiting
 *     return XTEST_ERASE();
 * }
 */
#define XTEST_CREATE(argc, argv) _xtest_env = _xtest_environment_create(argc, argv)

/**
 * @brief Macro to start the execution of the test environment.
 *
 * This macro serves as the primary entry point to run all the tests
 * defined within the testing framework. When invoked, it calls the 
 * `_xtest_environment_run` function, which initializes the testing 
 * environment, executes all the test cases, and provides a summary 
 * of the test results.
 *
 * @details
 * The `_xtest_environment_run` function performs several key tasks:
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
 *     xtest_define_cases();
 * 
 *     // Run all defined test cases
 *     XTEST_RUN();
 * 
 *     return 0;
 * }
 * @endcode
 *
 * Note:
 * - Ensure that all test cases are defined and properly configured
 *   before invoking `XTEST_RUN()`. Any test cases added after the 
 *   macro is called will not be executed.
 * - This macro abstracts the complexity of the underlying test 
 *   execution function, providing a clean and simple interface for 
 *   running the tests.
 *
 * @see _xtest_environment_run
 */
#define XTEST_RUN() _xtest_environment_run()

/**
 * Macro to erase and clean up the test environment.
 * This macro simplifies the process of calling the function to clean up the test environment,
 * ensuring that all allocated resources are properly released and the environment is reset.
 * It operates on the `test_env` variable that was initialized using the XTEST_CREATE macro.
 * 
 * Usage: XTEST_ERASE()
 * 
 * Example:
 * int main(int argc, char *argv[]) {
 *     // Initialize the test environment with command-line arguments
 *     XTEST_CREATE(argc, argv);
 *     
 *     // Your test code here
 *     
 *     // Clean up the test environment before exiting
 *     return XTEST_ERASE();
 * }
 */
#define XTEST_ERASE() _xtest_environment_summary()

// =================================================================
// XTest run commands
// =================================================================

/**
 * @brief Assign a mark to a test case.
 *
 * This macro is used to apply a mark to a given test case. It wraps the
 * _xtest_apply_mark function, providing a convenient way to mark test cases
 * with specific attributes or states.
 *
 * @param test_case The test case to which the mark will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param mark      The mark to assign to the test case. This is typically a string
 *                  used to indicate specific attributes or states of the test case.
 *                  The mark is cast to xstring for compatibility.
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
 * the _xtest_apply_xtag function, providing a convenient way to tag test cases
 * with additional metadata.
 *
 * @param test_case The test case to which the xtag will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param xtag      The xtag to assign to the test case. This is typically a string
 *                  used to add additional metadata or categorization to the test
 *                  case. The xtag is cast to xstring for compatibility.
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
 * _xtest_apply_priority function, providing a more intuitive and convenient
 * way to specify test priorities in the code.
 *
 * @param test_case The test case to which the priority will be applied. This should
 *                  be a valid identifier for a registered test case.
 * @param priority  The priority level to assign to the test case. Higher values
 *                  typically indicate higher priority, though this depends on the
 *                  implementation details of _xtest_apply_priority.
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
#define XFIXTURE(fixture_name) _XFIXTURE(fixture_name)

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
#define XSETUP(fixture_name) _XSETUP(fixture_name)

/**
 * @brief Define macro for declaring a teardown function for a test fixture.
 * 
 * This macro is used to declare a teardown function for a test fixture. It creates
 * a function declaration for the teardown function associated with the specified
 * fixture name. This function typically performs cleanup tasks after each test case.
 * 
 * @param fixture_name The name of the test fixture.
 */
#define XTEARDOWN(fixture_name) _XTEARDOWN(fixture_name)

/**
 * Defines a test case with a given name and sets up its properties.
 * 
 * This macro generates a function prototype and an instance of an xtest struct 
 * for the specified test case name. It initializes the test case with default 
 * values for various properties, including mark and tag rules, description 
 * strings, and flags.
 * 
 * @param name The name of the test case. This name is used to generate the function
 *             prototype and the xtest struct instance.
 */
#define XTEST(name) _XTEST(name)

/**
 * @brief Define macro for a BDD style test case.
 * 
 * This macro is used to define a BDD style test case. It creates a function prototype
 * and an instance of an xtest struct for the specified test case name. It initializes
 * the test case with default values for various properties, including mark and tag rules,
 * description strings, and flags. This macro is typically used for behavior-driven
 * development (BDD) style tests, where the test case is structured as a series of GIVEN,
 * WHEN, and THEN conditions.
 * 
 * @param name The name of the test case.
 */
#define XSONIREO(name) _XTEST(name)

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
#define XTEST_DEFINE_POOL(group_name) void group_name(xenv* test_env)

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
#define XTEST_EXTERN_POOL(group_name) extern void group_name(xenv* test_env)

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
#define XTEST_IMPORT_POOL(group_name) group_name(&_xtest_env)

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
#define GIVEN(description) printf("%s%s\n", "  > GIVEN ", description); if (true)

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
#define WHEN(description) printf("%s%s\n", "  >\t WHEN ", description); if (true)

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
#define THEN(description) printf("%s%s\n", "  >\t\t THEN ", description); if (true)

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
#define XTEST_DATA(group_name) typedef struct group_name##_xdata group_name##_xdata; struct group_name##_xdata

/**
 * @brief Define macro for indicating that a test is not implemented yet.
 * 
 * This macro is used to mark a test as not implemented yet. It invokes
 * the TEST_ASSUME macro with a false condition, indicating that the test
 * is not implemented, and includes a message indicating the same.
 */
#define XTEST_NOT_IMPLEMENTED() TEST_ASSUME(false, (const xstring)"Test not implemented yet")

// =================================================================
// Bench specific commands
// =================================================================

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to mark the start of a benchmark. It typically initializes
 * any necessary resources or variables required for benchmarking.
 */
#define TEST_BENCHMARK() xtest_start_benchmark()

/**
 * @brief Define macro for getting the current time.
 * 
 * This macro is used to retrieve the current time, which is typically used
 * in conjunction with TEST_BENCHMARK to calculate the elapsed time for a benchmark.
 */
#define TEST_CURRENT_TIME() xtest_stop_benchmark()

/**
 * @brief Define macro for reporting test duration with a given timeout.
 * 
 * This macro is used to report the duration of a test with a given timeout.
 * It takes the timeout duration, elapsed time, and actual duration as arguments
 * and reports the results, typically in the form of logs or console output.
 * 
 * @param duration The duration unit (e.g., "minutes", "seconds").
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION(duration, elapsed, actual) xbenchmark((const xstring)duration, elapsed, actual)

/**
 * @brief Define macro for reporting test duration in minutes.
 * 
 * This macro is a shorthand for reporting test duration in minutes using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in minutes.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_MIN(elapsed, actual) TEST_DURATION((const xstring)"minutes", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in seconds.
 * 
 * This macro is a shorthand for reporting test duration in seconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in seconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_SEC(elapsed, actual) TEST_DURATION((const xstring)"seconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in milliseconds.
 * 
 * This macro is a shorthand for reporting test duration in milliseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in milliseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_MIL(elapsed, actual) TEST_DURATION((const xstring)"milliseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in microseconds.
 * 
 * This macro is a shorthand for reporting test duration in microseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in microseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_MIC(elapsed, actual) TEST_DURATION((const xstring)"microseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in nanoseconds.
 * 
 * This macro is a shorthand for reporting test duration in nanoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in nanoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_NAN(elapsed, actual) TEST_DURATION((const xstring)"nanoseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in picoseconds.
 * 
 * This macro is a shorthand for reporting test duration in picoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in picoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_PIC(elapsed, actual) TEST_DURATION((const xstring)"picoseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in femtoseconds.
 * 
 * This macro is a shorthand for reporting test duration in femtoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in femtoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_FEM(elapsed, actual) TEST_DURATION((const xstring)"femtoseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in attoseconds.
 * 
 * This macro is a shorthand for reporting test duration in attoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in attoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_ATT(elapsed, actual) TEST_DURATION((const xstring)"attoseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in zeptoseconds.
 * 
 * This macro is a shorthand for reporting test duration in zeptoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in zeptoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_ZEP(elapsed, actual) TEST_DURATION((const xstring)"zeptoseconds", elapsed, actual)

/**
 * @brief Define macro for reporting test duration in yoctoseconds.
 * 
 * This macro is a shorthand for reporting test duration in yoctoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in yoctoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 */
#define TEST_DURATION_YOC(elapsed, actual) TEST_DURATION((const xstring)"yoctoseconds", elapsed, actual)

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
    _xtest_assert_class(expression, TEST_ASSERT_AS_CLASS_ASSERT, (const xstring)message, (xstring)__FILE__, __LINE__, (const xstring)__func__)

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
    _xtest_assert_class(expression, TEST_ASSERT_AS_CLASS_EXPECT, (const xstring)message, (xstring)__FILE__, __LINE__, (const xstring)__func__)

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
    _xtest_assert_class(expression, TEST_ASSERT_AS_CLASS_ASSUME, (const xstring)message, (xstring)__FILE__, __LINE__, (const xstring)__func__)

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
    _xtest_assert_class(expression, TEST_ASSERT_AS_CLASS_EXCEPT, (const xstring)message, (xstring)__FILE__, __LINE__, (const xstring)__func__)

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
    _xtest_assert_class(expression, TEST_ASSERT_AS_CLASS_SANITY, (const xstring)message, (xstring)__FILE__, __LINE__, (const xstring)__func__)

#ifdef __cplusplus
}
#endif

#endif
