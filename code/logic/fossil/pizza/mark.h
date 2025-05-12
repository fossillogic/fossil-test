/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_MARK_H
#define FOSSIL_MARK_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure to hold the benchmark statistics.
 * 
 * This structure contains various fields to manage the statistics for a benchmark,
 * including the name of the benchmark, the start and end times, the number of samples,
 * the total duration, the minimum and maximum durations, and a flag to indicate if the
 * benchmark is currently running.
 */
typedef struct {
    const char* name;
    clock_t start_time;
    clock_t end_time;
    int num_samples;
    double total_duration;
    double min_duration;
    double max_duration;
    int running;
} fossil_mark_t;

/**
 * @brief Initializes a fossil_mark_t object with the given name.
 * @param benchmark The fossil_mark_t object to initialize.
 * @param name The name of the benchmark.
 */
void fossil_benchmark_init(fossil_mark_t* benchmark, const char* name);

/**
 * @brief Starts the benchmark timer.
 * @param benchmark The fossil_mark_t object to start.
 */
void fossil_benchmark_start(fossil_mark_t* benchmark);

/**
 * @brief Stops the benchmark timer.
 * @param benchmark The fossil_mark_t object to stop.
 */
void fossil_benchmark_stop(fossil_mark_t* benchmark);

/**
 * @brief Returns the total elapsed time in seconds.
 * @param benchmark The fossil_mark_t object to get the elapsed time from.
 * @return The total elapsed time in seconds.
 */
double fossil_benchmark_elapsed_seconds(const fossil_mark_t* benchmark);

/**
 * @brief Returns the minimum elapsed time in seconds.
 * @param benchmark The fossil_mark_t object to get the minimum time from.
 * @return The minimum elapsed time in seconds.
 */
double fossil_benchmark_min_time(const fossil_mark_t* benchmark);

/**
 * @brief Returns the maximum elapsed time in seconds.
 * @param benchmark The fossil_mark_t object to get the maximum time from.
 * @return The maximum elapsed time in seconds.
 */
double fossil_benchmark_max_time(const fossil_mark_t* benchmark);

/**
 * @brief Returns the average elapsed time in seconds.
 * @param benchmark The fossil_mark_t object to get the average time from.
 * @return The average elapsed time in seconds.
 */
double fossil_benchmark_avg_time(const fossil_mark_t* benchmark);

/**
 * @brief Resets the benchmark statistics.
 * @param benchmark The fossil_mark_t object to reset.
 */
void fossil_benchmark_reset(fossil_mark_t* benchmark);

/**
 * @brief Prints a report of the benchmark statistics.
 * @param benchmark The fossil_mark_t object to report.
 */
void fossil_benchmark_report(const fossil_mark_t* benchmark);

typedef struct {
    fossil_mark_t* benchmark;
} fossil_scoped_mark_t;

/**
 * @brief Initializes a fossil_scoped_mark_t object with the given benchmark.
 * @param scoped_benchmark The fossil_scoped_mark_t object to initialize.
 * @param benchmark The benchmark to be scoped.
 */
void fossil_scoped_benchmark_init(fossil_scoped_mark_t* scoped_benchmark, fossil_mark_t* benchmark);

/**
 * @brief Destroys a fossil_scoped_mark_t object.
 * @param scoped_benchmark The fossil_scoped_mark_t object to destroy.
 */
void fossil_scoped_benchmark_destroy(fossil_scoped_mark_t* scoped_benchmark);

/**
 * Function to test benchmark with specified duration type, expected value, and actual value.
 * 
 * @param duration_type The duration type to test.
 * @param expected The expected value.
 * @param actual The actual value.
 */
void fossil_test_benchmark(char* duration_type, double expected, double actual);

/**
 * Function to start the benchmark.
 */
void fossil_test_start_benchmark(void);

/**
 * Function to stop the benchmark and return the elapsed time in nanoseconds.
 * 
 * @return The elapsed time in nanoseconds.
 */
uint64_t fossil_test_stop_benchmark(void);

// *****************************************************************************
// Macro definitions
// *****************************************************************************

/**
 * @brief Define macro for marking a benchmark.
 * 
 * This macro is used to mark a benchmark with a given name. It initializes
 * the benchmark structure and sets the name of the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define _MARK_BENCHMARK(name) \
    fossil_mark_t benchmark_##name; \
    fossil_benchmark_init(&benchmark_##name, #name)

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to start a benchmark with a given name. It starts the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define _MARK_START(name) \
    fossil_benchmark_start(&benchmark_##name)

/**
 * @brief Define macro for stopping a benchmark.
 * 
 * This macro is used to stop a benchmark with a given name. It stops the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define _MARK_STOP(name) \
    fossil_benchmark_stop(&benchmark_##name)

/**
 * @brief Define macro for reporting a benchmark.
 * 
 * This macro is used to report the results of a benchmark with a given name.
 * It prints the benchmark name and the elapsed time.
 * 
 * @param name The name of the benchmark.
 */
#define _MARK_REPORT(name) \
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
#define _MARK_SCOPED(name) \
    fossil_scoped_mark_t scoped_benchmark_##name; \
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
#define _TEST_BENCHMARK() fossil_test_start_benchmark()

/**
 * @brief Define macro for getting the current time.
 * 
 * This macro is used to retrieve the current time, which is typically used
 * in conjunction with TEST_BENCHMARK to calculate the elapsed time for a benchmark.
 */
#define _TEST_CURRENT_TIME() fossil_test_stop_benchmark()

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
#define _TEST_DURATION(duration, elapsed, actual) fossil_test_benchmark((char*)duration, elapsed, actual)

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
#define _TEST_DURATION_MIN(elapsed, actual) _TEST_DURATION((char*)"minutes", elapsed, actual)

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
#define _TEST_DURATION_SEC(elapsed, actual) _TEST_DURATION((char*)"seconds", elapsed, actual)

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
#define _TEST_DURATION_MIL(elapsed, actual) _TEST_DURATION((char*)"milliseconds", elapsed, actual)

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
#define _TEST_DURATION_MIC(elapsed, actual) _TEST_DURATION((char*)"microseconds", elapsed, actual)

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
#define _TEST_DURATION_NAN(elapsed, actual) _TEST_DURATION((char*)"nanoseconds", elapsed, actual)

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
#define _TEST_DURATION_PIC(elapsed, actual) _TEST_DURATION((char*)"picoseconds", elapsed, actual)

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
#define _TEST_DURATION_FEM(elapsed, actual) _TEST_DURATION((char*)"femtoseconds", elapsed, actual)

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
#define _TEST_DURATION_ATT(elapsed, actual) _TEST_DURATION((char*)"attoseconds", elapsed, actual)

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
#define _TEST_DURATION_ZEP(elapsed, actual) _TEST_DURATION((char*)"zeptoseconds", elapsed, actual)

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
#define _TEST_DURATION_YOC(elapsed, actual) _TEST_DURATION((char*)"yoctoseconds", elapsed, actual)

// *****************************************************************************
// Public API Macros
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
    _MARK_BENCHMARK(name)

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to start a benchmark with a given name. It starts the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_START(name) \
    _MARK_START(name)

/**
 * @brief Define macro for stopping a benchmark.
 * 
 * This macro is used to stop a benchmark with a given name. It stops the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_STOP(name) \
    _MARK_STOP(name)

/**
 * @brief Define macro for reporting a benchmark.
 * 
 * This macro is used to report the results of a benchmark with a given name.
 * It prints the benchmark name and the elapsed time.
 * 
 * @param name The name of the benchmark.
 */
#define MARK_REPORT(name) \
    _MARK_REPORT(name)

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
    _MARK_SCOPED(name)

// =================================================================
// Bench specific commands
// =================================================================

/**
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to mark the start of a benchmark. It typically initializes
 * any necessary resources or variables required for benchmarking.
 */
#define TEST_BENCHMARK() \
    _TEST_BENCHMARK()

/**
 * @brief Define macro for getting the current time.
 * 
 * This macro is used to retrieve the current time, which is typically used
 * in conjunction with TEST_BENCHMARK to calculate the elapsed time for a benchmark.
 */
#define TEST_CURRENT_TIME() \
    _TEST_CURRENT_TIME()

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
#define TEST_DURATION(duration, elapsed, actual) \
    _TEST_DURATION(duration, elapsed, actual)

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
#define TEST_DURATION_MIN(elapsed, actual) \
    _TEST_DURATION_MIN(elapsed, actual)

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
#define TEST_DURATION_SEC(elapsed, actual) \
    _TEST_DURATION_SEC(elapsed, actual)

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
#define TEST_DURATION_MIL(elapsed, actual) \
    _TEST_DURATION_MIL(elapsed, actual)

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
#define TEST_DURATION_MIC(elapsed, actual) \
    _TEST_DURATION_MIC(elapsed, actual)

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
#define TEST_DURATION_NAN(elapsed, actual) \
    _TEST_DURATION_NAN(elapsed, actual)

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
#define TEST_DURATION_PIC(elapsed, actual) \
    _TEST_DURATION_PIC(elapsed, actual)

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
#define TEST_DURATION_FEM(elapsed, actual) \
    _TEST_DURATION_FEM(elapsed, actual)

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
#define TEST_DURATION_ATT(elapsed, actual) \
    _TEST_DURATION_ATT(elapsed, actual)

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
#define TEST_DURATION_ZEP(elapsed, actual) \
    _TEST_DURATION_ZEP(elapsed, actual)

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
#define TEST_DURATION_YOC(elapsed, actual) \
    _TEST_DURATION_YOC(elapsed, actual)

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_MARK_FRAMEWORK_H
