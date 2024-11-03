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

#ifdef __cplusplus
extern "C" {
#endif

#include "benchmark.h"
#include "unittest.h"
#include "mockup.h"
#include "assume.h"

/**
 * Macro to define a given step in a test case.
 * This macro is used to define a given step in a test case. The given step
 * should contain the setup logic required to prepare the environment for the
 * test case.
 */
#define GIVEN(description) _GIVEN(description)

/**
 * Macro to define a when step in a test case.
 * This macro is used to define a when step in a test case. The when step should
 * contain the logic to execute the functionality that is being tested.
 */
#define WHEN(description) _WHEN(description)

/**
 * Macro to define a then step in a test case.
 * This macro is used to define a then step in a test case. The then step should
 * contain the logic to verify the correctness of the functionality that was
 * tested.
 */
#define THEN(description) _THEN(description)

/**
 * Macro to define the main test runner.
 * This macro is used to define the main test runner function that will be
 * executed when the test suite is run. The main test runner function will
 * initialize the test framework, run all test cases, and output the test
 * results.
 */
#define FOSSIL_TEST_MAIN() \
    _FOSSIL_TEST_MAIN()

/**
 * Macro to start the test runner.
 * This macro is used to start the test runner, which will initialize the test
 * framework and prepare to run all test cases in the test suite.
 */
#define FOSSIL_TEST_START() \
    _FOSSIL_TEST_START()

/**
 * Macro to run all test cases in the test suite.
 * This macro is used to run all test cases in the test suite. The test cases
 * will be executed in sequence, and the results will be output to the console.
 */
#define FOSSIL_TEST_RUN() \
    _FOSSIL_TEST_RUN()

/**
 * Macro to print a summary of the test results.
 * This macro is used to print a summary of the test results after all test
 * cases have been executed. The summary will include the number of test cases
 * that passed, failed, and were skipped.
 */
#define FOSSIL_TEST_SUMMARY() \
    _FOSSIL_TEST_SUMMARY()

/**
 * Macro to end the test runner.
 * This macro is used to end the test runner, which will clean up the test
 * framework and return the appropriate exit code based on the test results.
 */
#define FOSSIL_TEST_END() \
    _FOSSIL_TEST_END()

/**
 * Macro to define a test case.
 * This macro is used to declare a test case function that will be executed
 * as part of the test suite. The test case function should contain the logic
 * to verify the correctness of a specific functionality.
 */
#define FOSSIL_TEST_ADD(suite, test_case) \
    _FOSSIL_TEST_ADD(suite, test_case)

/**
 * Macro to define a test suite.
 * This macro is used to declare a test suite, which is a collection of test
 * cases that are related to each other. The test suite can be executed as a
 * whole to verify the correctness of a group of functionalities.
 */
#define FOSSIL_TEST_SUITE(suite_name) \
    _FOSSIL_TEST_SUITE(suite_name)

/**
 * Macro to define a setup function for a test.
 * This macro is used to declare a setup function that will be executed before
 * each test case in a test suite. The setup function should contain the logic
 * to initialize the environment or state required for the test cases.
 */
#define FOSSIL_SETUP(name) \
    _FOSSIL_TEST_SETUP(name)

/**
 * Macro to define a teardown function for a test.
 * This macro is used to declare a teardown function that will be executed after
 * each test case in a test suite. The teardown function should contain the logic
 * to clean up the environment or state after the test cases have been executed.
 */
#define FOSSIL_TEARDOWN(name) \
    _FOSSIL_TEST_TEARDOWN(name)

/**
 * Macro to define test data.
 * This macro is used to declare a structure that contains the data required
 * for a test case. The test data structure can be used to pass input parameters
 * to the test case and store the expected output values.
 */
#define FOSSIL_TEST_DATA(name) \
    _FOSSIL_TEST_DATA(name)

/**
 * Macro to define a test case.
 * This macro is used to declare a test case function that will be executed
 * as part of the test suite. The test case function should contain the logic
 * to verify the correctness of a specific functionality.
 */
#define FOSSIL_TEST_CASE(name) \
    _FOSSIL_TEST_CASE(name)

/**
 * Macro to assume a condition in a test runner.
 * This macro is used to assert that a specific condition is true within a test
 * runner. If the condition is false, the test runner will output the specified
 * message and may abort the execution of the test case or test suite.
 */
#define FOSSIL_TEST_ASSUME(condition, message) \
    _FOSSIL_TEST_ASSUME(condition, message)

#define FOSSIL_TEST_ASSERT(condition, message) \
    _FOSSIL_TEST_ASSUME(condition, message)


// *****************************************************************************
// Mocking framework
// *****************************************************************************

/**
 * @brief Macro for initializing the mock list.
 *
 * This macro initializes the mock list by calling the fossil_mock_init function.
 *
 * @param list The mock list to initialize.
 */
#define MOCK_INIT(list) _MOCK_INIT(list)

/**
 * @brief Macro for destroying the mock list.
 *
 * This macro destroys the mock list by calling the fossil_mock_destroy function.
 *
 * @param list The mock list to destroy.
 */
#define MOCK_DESTROY(list) _MOCK_DESTROY(list)

/**
 * @brief Macro for adding a mock function call to the mock list.
 *
 * This macro adds a mock function call to the mock list by calling the fossil_mock_add_call function.
 *
 * @param list     The mock list to add the call to.
 * @param func     The mock function to add the call for.
 * @param args     The arguments of the mock function call.
 * @param num_args The number of arguments in the mock function call.
 */
#define MOCK_ADD_CALL(list, func, args, num_args) _MOCK_ADD_CALL(list, func, args, num_args)

/**
 * @brief Macro for printing the mock list.
 *
 * This macro prints the mock list by calling the fossil_mock_print function.
 *
 * @param list The mock list to print.
 */
#define MOCK_PRINT(list) _MOCK_PRINT(list)
/**
 * @def FOSSIL_MOCK_FUNC
 * @brief Macro for creating a mock function with the specified return type, name, and parameters.
 *
 * This macro simplifies the creation of mock functions by defining a function with the given return
 * type, name, and parameters. The function name will be prefixed with "fossil_mockup_" to clearly indicate
 * that it is a mock function.
 *
 * @param return_type   The return type of the mock function.
 * @param name          The name of the mock function.
 * @param ...           The parameters of the mock function in the format: (type1 param1, type2 param2, ...).
 * @return The return type specified for the mock function.
 */
#define FOSSIL_MOCK_FUNC(return_type, name, ...) _FOSSIL_MOCK_FUNC(return_type, name, __VA_ARGS__)

/**
 * @def FOSSIL_MOCK_ALIAS
 * @brief Macro for creating a type alias based on an existing type.
 *
 * This macro creates a type alias for a given existing type.
 *
 * @param new_type       The name of the new type alias.
 * @param existing_type  The existing type to create an alias for.
 */
#define FOSSIL_MOCK_ALIAS(new_type, existing_type) _FOSSIL_MOCK_ALIAS(new_type, existing_type)

/**
 * @def FOSSIL_MOCK_STRUCT
 * @brief Macro for creating a mock struct with the specified name and members.
 *
 * This macro simplifies the creation of mock structs by defining a struct with the given name
 * and members. The struct name will be prefixed with "fossil_mockup_" to clearly indicate that it is a mock struct.
 *
 * @param name     The name of the mock struct.
 * @param ...      The members of the mock struct in the format: (type1 member1, type2 member2, ...).
 */
#define FOSSIL_MOCK_STRUCT(name, ...) _FOSSIL_MOCK_STRUCT(name, __VA_ARGS__)

// *****************************************************************************
// Benchmark framework
// *****************************************************************************

/**
 * @brief Define macro for marking a benchmark.
 * 
 * This macro is used to mark a benchmark with a given name. It initializes
 * the benchmark structure and sets the name of the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_BENCHMARK(name) \
    fossil_benchmark_t benchmark_##name; \
    fossil_benchmark_init(&benchmark_##name, #name)

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to start a benchmark with a given name. It starts the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_START(name) \
    fossil_benchmark_start(&benchmark_##name)

/**
 * @brief Define macro for stopping a benchmark.
 * 
 * This macro is used to stop a benchmark with a given name. It stops the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_STOP(name) \
    fossil_benchmark_stop(&benchmark_##name)

/**
 * @brief Define macro for reporting a benchmark.
 * 
 * This macro is used to report the results of a benchmark with a given name.
 * It prints the benchmark name and the elapsed time.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_REPORT(name) \
    fossil_benchmark_report(&benchmark_##name)

/**
 * @brief Define macro for scoped benchmarking.
 * 
 * This macro is used to create a scoped benchmark with a given name. It
 * initializes the scoped benchmark structure and sets the benchmark to be
 * used.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_SCOPED(name) \
    scoped_benchmark_t scoped_benchmark_##name; \
    fossil_scoped_benchmark_init(&scoped_benchmark_##name, &benchmark_##name)

// =================================================================
// Bench specific commands
// =================================================================

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to mark the start of a benchmark. It typically initializes
 * any necessary resources or variables required for benchmarking.
 */
#define TEST_BENCHMARK() fossil_test_start_benchmark()

/**
 * @brief Define macro for getting the current time.
 * 
 * This macro is used to retrieve the current time, which is typically used
 * in conjunction with TEST_BENCHMARK to calculate the elapsed time for a benchmark.
 */
#define TEST_CURRENT_TIME() fossil_test_stop_benchmark()

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
#define TEST_DURATION(duration, elapsed, actual) fossil_test_benchmark((char*)duration, elapsed, actual)

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
#define TEST_DURATION_MIN(elapsed, actual) TEST_DURATION((char*)"minutes", elapsed, actual)

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
#define TEST_DURATION_SEC(elapsed, actual) TEST_DURATION((char*)"seconds", elapsed, actual)

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
#define TEST_DURATION_MIL(elapsed, actual) TEST_DURATION((char*)"milliseconds", elapsed, actual)

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
#define TEST_DURATION_MIC(elapsed, actual) TEST_DURATION((char*)"microseconds", elapsed, actual)

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
#define TEST_DURATION_NAN(elapsed, actual) TEST_DURATION((char*)"nanoseconds", elapsed, actual)

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
#define TEST_DURATION_PIC(elapsed, actual) TEST_DURATION((char*)"picoseconds", elapsed, actual)

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
#define TEST_DURATION_FEM(elapsed, actual) TEST_DURATION((char*)"femtoseconds", elapsed, actual)

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
#define TEST_DURATION_ATT(elapsed, actual) TEST_DURATION((char*)"attoseconds", elapsed, actual)

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
#define TEST_DURATION_ZEP(elapsed, actual) TEST_DURATION((char*)"zeptoseconds", elapsed, actual)

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
#define TEST_DURATION_YOC(elapsed, actual) TEST_DURATION((char*)"yoctoseconds", elapsed, actual)

#ifdef __cplusplus
}
#endif

#endif
