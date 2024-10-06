/*
 * -----------------------------------------------------------------------------
 * File: framework.hpp
 * Project: Fossil Logic
 * Description: This file implments the framework for benchmarking.
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
#ifndef FOSSIL_MARK_FRAMEWORK_HPP
#define FOSSIL_MARK_FRAMEWORK_HPP

#include "benchmark.h"

// Macros for benchmarking
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

#endif // FOSSIL_MARK_FRAMEWORK_HPP 