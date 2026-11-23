/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
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
    uint64_t start_time;
    uint64_t end_time;
    uint64_t* iteration_times;
    size_t num_iterations;
    size_t num_warmup;
    size_t capacity;
    double total_duration;
    double min_duration;
    double max_duration;
    double mean_duration;
    double median_duration;
    double std_dev;
    int running;
    uint32_t num_samples;
} fossil_mark_t;

/**
 * @brief Initializes a fossil_mark_t object with the given name.
 * 
 * @param benchmark The fossil_mark_t object to initialize.
 * @param name The name of the benchmark.
 * 
 * @note The benchmark object must be allocated before calling this function. The name should be a valid string.
 */
FOSSIL_MAIP_API void fossil_benchmark_init(fossil_mark_t* benchmark, const char* name);

/**
 * @brief Starts the benchmark timer.
 * 
 * @param benchmark The fossil_mark_t object to start.
 * 
 * @note This function should be called before the code section to be benchmarked. It records the start time of the benchmark.
 */
FOSSIL_MAIP_API void fossil_benchmark_start(fossil_mark_t* benchmark);

/**
 * @brief Stops the benchmark timer.
 * 
 * @param benchmark The fossil_mark_t object to stop.
 * 
 * @note This function should be called after the code section to be benchmarked. It records the end time of the benchmark and calculates the elapsed time.
 */
FOSSIL_MAIP_API void fossil_benchmark_stop(fossil_mark_t* benchmark);

/**
 * @brief Returns the total elapsed time in seconds.
 * 
 * @param benchmark The fossil_mark_t object to get the elapsed time from.
 * 
 * @return The total elapsed time in seconds.
 * 
 * @note This function returns the total duration of the benchmark, which is the sum of all elapsed times recorded during the benchmark.
 */
FOSSIL_MAIP_API double fossil_benchmark_elapsed_seconds(const fossil_mark_t* benchmark);

/**
 * @brief Returns the minimum elapsed time in seconds.
 * 
 * @param benchmark The fossil_mark_t object to get the minimum time from.
 * 
 * @return The minimum elapsed time in seconds.
 * 
 * @note This function returns the minimum duration recorded during the benchmark. If no samples have been recorded, it returns 0.0.
 */
FOSSIL_MAIP_API double fossil_benchmark_min_time(const fossil_mark_t* benchmark);

/**
 * @brief Returns the maximum elapsed time in seconds.
 * 
 * @param benchmark The fossil_mark_t object to get the maximum time from.
 * 
 * @return The maximum elapsed time in seconds.
 * 
 * @note This function returns the maximum duration recorded during the benchmark. If no samples have been recorded, it returns 0.0.
 */
FOSSIL_MAIP_API double fossil_benchmark_max_time(const fossil_mark_t* benchmark);

/**
 * @brief Returns the average elapsed time in seconds.
 * 
 * @param benchmark The fossil_mark_t object to get the average time from.
 * 
 * @return The average elapsed time in seconds.
 * 
 * @note This function returns the average duration recorded during the benchmark. If no samples have been recorded, it returns 0.0.
 */
FOSSIL_MAIP_API double fossil_benchmark_avg_time(const fossil_mark_t* benchmark);

/**
 * @brief Resets the benchmark statistics.
 * 
 * @param benchmark The fossil_mark_t object to reset.
 * 
 * @note This function resets all the statistics of the benchmark, including the number of samples, total duration, minimum and maximum durations, mean duration, median duration, and standard deviation. It does not free any allocated memory for iteration times.
 */
FOSSIL_MAIP_API void fossil_benchmark_reset(fossil_mark_t* benchmark);

/**
 * @brief Prints a report of the benchmark statistics.
 * 
 * @param benchmark The fossil_mark_t object to report.
 * 
 * @note This function prints the benchmark name, number of iterations, total time, mean time, median time, minimum time, maximum time, and standard deviation to the console. It provides a summary of the benchmark results.
 */
FOSSIL_MAIP_API void fossil_benchmark_report(const fossil_mark_t* benchmark);

typedef struct {
    fossil_mark_t* benchmark;
} fossil_scoped_mark_t;

/**
 * @brief Initializes a fossil_scoped_mark_t object with the given benchmark.
 * 
 * @param scoped_benchmark The fossil_scoped_mark_t object to initialize.
 * @param benchmark The benchmark to be scoped.
 * 
 * @note This function initializes the scoped benchmark and starts the benchmark timer. It is typically used to measure the duration of a specific code block within a function.
 */
FOSSIL_MAIP_API void fossil_scoped_benchmark_init(fossil_scoped_mark_t* scoped_benchmark, fossil_mark_t* benchmark);

/**
 * @brief Destroys a fossil_scoped_mark_t object.
 * 
 * @param scoped_benchmark The fossil_scoped_mark_t object to destroy.
 * 
 * @note This function stops the benchmark timer and cleans up any resources associated with the scoped benchmark. It should be called at the end of the code block being measured.
 */
FOSSIL_MAIP_API void fossil_scoped_benchmark_destroy(fossil_scoped_mark_t* scoped_benchmark);

/**
 * @brief Marks a test case as timeout with a specified time and prints it to stderr.
 * 
 * @param duration_type The duration type to test.
 * @param expected The expected value.
 * @param actual The actual value.
 * 
 * @note This function is used to mark a test case as timeout with a specified time and prints the result to stderr. It compares the expected and actual values based on the specified duration type.
 */
FOSSIL_MAIP_API void fossil_test_benchmark(char* duration_type, double expected, double actual);

/**
 * @brief Function to start the benchmark.
 * 
 * @note This function starts the benchmark timer.
 */
FOSSIL_MAIP_API void fossil_test_start_benchmark(void);

/**
 * @brief Function to stop the benchmark and return the elapsed time in nanoseconds.
 * 
 * @return The elapsed time in nanoseconds.
 * 
 * @note This function stops the benchmark timer and returns the elapsed time in nanoseconds. It is used to measure the duration of a specific code block or function.
 */
FOSSIL_MAIP_API uint64_t fossil_test_stop_benchmark(void);

// *****************************************************************************
// Macro definitions
// *****************************************************************************

#define _MARK_BENCHMARK(name) \
    fossil_mark_t benchmark_##name; \
    fossil_benchmark_init(&benchmark_##name, #name)

#define _MARK_START(name) \
    fossil_benchmark_start(&benchmark_##name)

#define _MARK_STOP(name) \
    fossil_benchmark_stop(&benchmark_##name)

#define _MARK_REPORT(name) \
    fossil_benchmark_report(&benchmark_##name)

#define _MARK_SCOPED(name) \
    fossil_scoped_mark_t scoped_benchmark_##name; \
    fossil_scoped_benchmark_init(&scoped_benchmark_##name, &benchmark_##name)

#define _TEST_BENCHMARK() fossil_test_start_benchmark()

#define _TEST_CURRENT_TIME() fossil_test_stop_benchmark()

#define _TEST_DURATION(duration, elapsed, actual) fossil_test_benchmark((char*)duration, elapsed, actual)

#define _TEST_DURATION_MIN(elapsed, actual) _TEST_DURATION((char*)"minutes", elapsed, actual)

#define _TEST_DURATION_SEC(elapsed, actual) _TEST_DURATION((char*)"seconds", elapsed, actual)

#define _TEST_DURATION_MIL(elapsed, actual) _TEST_DURATION((char*)"milliseconds", elapsed, actual)

#define _TEST_DURATION_MIC(elapsed, actual) _TEST_DURATION((char*)"microseconds", elapsed, actual)

#define _TEST_DURATION_NAN(elapsed, actual) _TEST_DURATION((char*)"nanoseconds", elapsed, actual)

#define _TEST_DURATION_PIC(elapsed, actual) _TEST_DURATION((char*)"picoseconds", elapsed, actual)

#define _TEST_DURATION_FEM(elapsed, actual) _TEST_DURATION((char*)"femtoseconds", elapsed, actual)

#define _TEST_DURATION_ATT(elapsed, actual) _TEST_DURATION((char*)"attoseconds", elapsed, actual)

#define _TEST_DURATION_ZEP(elapsed, actual) _TEST_DURATION((char*)"zeptoseconds", elapsed, actual)

#define _TEST_DURATION_YOC(elapsed, actual) _TEST_DURATION((char*)"yoctoseconds", elapsed, actual)

// *****************************************************************************
// Public API Macros
// *****************************************************************************

/**
 * @def MARK_BENCHMARK(name)
 * @brief Define macro for marking a benchmark.
 * 
 * This macro is used to mark a benchmark with a given name. It initializes
 * the benchmark structure and sets the name of the benchmark.
 * 
 * @param name The name of the benchmark.
 * @return None; declares and initializes the named benchmark.
 * @note The benchmark identifier must be valid in the current scope.
 */
#define MARK_BENCHMARK(name) \
    _MARK_BENCHMARK(name)

/**
 * @def MARK_START(name)
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to start a benchmark with a given name. It starts the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 * @return None.
 * @note The benchmark must have been declared with MARK_BENCHMARK.
 */
#define MARK_START(name) \
    _MARK_START(name)

/**
 * @def MARK_STOP(name)
 * @brief Define macro for stopping a benchmark.
 * 
 * This macro is used to stop a benchmark with a given name. It stops the
 * timer for the benchmark.
 * 
 * @param name The name of the benchmark.
 * @return None.
 * @note Call after the measured code section.
 */
#define MARK_STOP(name) \
    _MARK_STOP(name)

/**
 * @def MARK_REPORT(name)
 * @brief Define macro for reporting a benchmark.
 * 
 * This macro is used to report the results of a benchmark with a given name.
 * It prints the benchmark name and the elapsed time.
 * 
 * @param name The name of the benchmark.
 * @return None.
 * @note Reports the statistics collected for the named benchmark.
 */
#define MARK_REPORT(name) \
    _MARK_REPORT(name)

/**
 * @def MARK_SCOPED(name)
 * @brief Define macro for scoped benchmarking.
 * 
 * This macro is used to create a scoped benchmark with a given name. It
 * initializes the scoped benchmark structure and sets the benchmark to be
 * used.
 * 
 * @param name The name of the benchmark.
 * @return None; declares and initializes a scoped benchmark.
 * @note The scoped benchmark must leave scope or be destroyed to stop timing.
 */
#define MARK_SCOPED(name) \
    _MARK_SCOPED(name)

// =================================================================
// Bench specific commands
// =================================================================

/**
 * @def TEST_BENCHMARK()
 * @brief Define macro for starting a benchmark.
 * 
 * This macro is used to mark the start of a benchmark. It typically initializes
 * any necessary resources or variables required for benchmarking.
 * @param None.
 * @return None.
 * @note Starts the test benchmark timer.
 */
#define TEST_BENCHMARK() \
    _TEST_BENCHMARK()

/**
 * @def TEST_CURRENT_TIME()
 * @brief Define macro for getting the current time.
 * 
 * This macro is used to retrieve the current time, which is typically used
 * in conjunction with TEST_BENCHMARK to calculate the elapsed time for a benchmark.
 * @param None.
 * @return Elapsed time in nanoseconds.
 * @note Stops the test benchmark timer and returns its elapsed duration.
 */
#define TEST_CURRENT_TIME() \
    _TEST_CURRENT_TIME()

/**
 * @def TEST_DURATION(duration, elapsed, actual)
 * @brief Define macro for reporting test duration with a given timeout.
 * 
 * This macro is used to report the duration of a test with a given timeout.
 * It takes the timeout duration, elapsed time, and actual duration as arguments
 * and reports the results, typically in the form of logs or console output.
 * 
 * @param duration The duration unit (e.g., "minutes", "seconds").
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note The duration unit is passed through to the test duration reporter.
 */
#define TEST_DURATION(duration, elapsed, actual) \
    _TEST_DURATION(duration, elapsed, actual)

/**
 * @def TEST_DURATION_MIN(elapsed, actual)
 * @brief Define macro for reporting test duration in minutes.
 * 
 * This macro is a shorthand for reporting test duration in minutes using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in minutes.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "minutes" unit.
 */
#define TEST_DURATION_MIN(elapsed, actual) \
    _TEST_DURATION_MIN(elapsed, actual)

/**
 * @def TEST_DURATION_SEC(elapsed, actual)
 * @brief Define macro for reporting test duration in seconds.
 * 
 * This macro is a shorthand for reporting test duration in seconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in seconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "seconds" unit.
 */
#define TEST_DURATION_SEC(elapsed, actual) \
    _TEST_DURATION_SEC(elapsed, actual)

/**
 * @def TEST_DURATION_MIL(elapsed, actual)
 * @brief Define macro for reporting test duration in milliseconds.
 * 
 * This macro is a shorthand for reporting test duration in milliseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in milliseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "milliseconds" unit.
 */
#define TEST_DURATION_MIL(elapsed, actual) \
    _TEST_DURATION_MIL(elapsed, actual)

/**
 * @def TEST_DURATION_MIC(elapsed, actual)
 * @brief Define macro for reporting test duration in microseconds.
 * 
 * This macro is a shorthand for reporting test duration in microseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in microseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "microseconds" unit.
 */
#define TEST_DURATION_MIC(elapsed, actual) \
    _TEST_DURATION_MIC(elapsed, actual)

/**
 * @def TEST_DURATION_NAN(elapsed, actual)
 * @brief Define macro for reporting test duration in nanoseconds.
 * 
 * This macro is a shorthand for reporting test duration in nanoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in nanoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "nanoseconds" unit.
 */
#define TEST_DURATION_NAN(elapsed, actual) \
    _TEST_DURATION_NAN(elapsed, actual)

/**
 * @def TEST_DURATION_PIC(elapsed, actual)
 * @brief Define macro for reporting test duration in picoseconds.
 * 
 * This macro is a shorthand for reporting test duration in picoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in picoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "picoseconds" unit.
 */
#define TEST_DURATION_PIC(elapsed, actual) \
    _TEST_DURATION_PIC(elapsed, actual)

/**
 * @def TEST_DURATION_FEM(elapsed, actual)
 * @brief Define macro for reporting test duration in femtoseconds.
 * 
 * This macro is a shorthand for reporting test duration in femtoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in femtoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "femtoseconds" unit.
 */
#define TEST_DURATION_FEM(elapsed, actual) \
    _TEST_DURATION_FEM(elapsed, actual)

/**
 * @def TEST_DURATION_ATT(elapsed, actual)
 * @brief Define macro for reporting test duration in attoseconds.
 * 
 * This macro is a shorthand for reporting test duration in attoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in attoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "attoseconds" unit.
 */
#define TEST_DURATION_ATT(elapsed, actual) \
    _TEST_DURATION_ATT(elapsed, actual)

/**
 * @def TEST_DURATION_ZEP(elapsed, actual)
 * @brief Define macro for reporting test duration in zeptoseconds.
 * 
 * This macro is a shorthand for reporting test duration in zeptoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in zeptoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "zeptoseconds" unit.
 */
#define TEST_DURATION_ZEP(elapsed, actual) \
    _TEST_DURATION_ZEP(elapsed, actual)

/**
 * @def TEST_DURATION_YOC(elapsed, actual)
 * @brief Define macro for reporting test duration in yoctoseconds.
 * 
 * This macro is a shorthand for reporting test duration in yoctoseconds using TEST_DURATION.
 * It takes the elapsed time and actual duration as arguments and reports the results
 * in yoctoseconds.
 * 
 * @param elapsed The elapsed time since the benchmark started.
 * @param actual The actual duration of the test.
 * @return None.
 * @note Equivalent to TEST_DURATION with the "yoctoseconds" unit.
 */
#define TEST_DURATION_YOC(elapsed, actual) \
    _TEST_DURATION_YOC(elapsed, actual)

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_MARK_FRAMEWORK_H
