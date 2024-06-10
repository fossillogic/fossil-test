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
#ifndef FOSSIL_TEST_BENCHMARK_H
#define FOSSIL_TEST_BENCHMARK_H

#include "fossil/_common/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif

#endif
