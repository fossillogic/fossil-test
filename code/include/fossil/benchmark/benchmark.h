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
#ifndef FOSSIL_MARK_BENCHMARK_H
#define FOSSIL_MARK_BENCHMARK_H

#include "fossil/_common/common.h"

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <float.h>

typedef struct {
    const char* name;
    clock_t start_time;
    clock_t end_time;
    int num_samples;
    double total_duration;
    double min_duration;
    double max_duration;
    int running;
} fossil_benchmark_t;

/**
 * @brief Initializes a fossil_benchmark_t object with the given name.
 * @param benchmark The fossil_benchmark_t object to initialize.
 * @param name The name of the benchmark.
 */
void fossil_benchmark_init(fossil_benchmark_t* benchmark, const char* name);

/**
 * @brief Starts the benchmark timer.
 * @param benchmark The fossil_benchmark_t object to start.
 */
void fossil_benchmark_start(fossil_benchmark_t* benchmark);

/**
 * @brief Stops the benchmark timer.
 * @param benchmark The fossil_benchmark_t object to stop.
 */
void fossil_benchmark_stop(fossil_benchmark_t* benchmark);

/**
 * @brief Returns the total elapsed time in seconds.
 * @param benchmark The fossil_benchmark_t object to get the elapsed time from.
 * @return The total elapsed time in seconds.
 */
double fossil_benchmark_elapsed_seconds(const fossil_benchmark_t* benchmark);

/**
 * @brief Returns the minimum elapsed time in seconds.
 * @param benchmark The fossil_benchmark_t object to get the minimum time from.
 * @return The minimum elapsed time in seconds.
 */
double fossil_benchmark_min_time(const fossil_benchmark_t* benchmark);

/**
 * @brief Returns the maximum elapsed time in seconds.
 * @param benchmark The fossil_benchmark_t object to get the maximum time from.
 * @return The maximum elapsed time in seconds.
 */
double fossil_benchmark_max_time(const fossil_benchmark_t* benchmark);

/**
 * @brief Returns the average elapsed time in seconds.
 * @param benchmark The fossil_benchmark_t object to get the average time from.
 * @return The average elapsed time in seconds.
 */
double fossil_benchmark_avg_time(const fossil_benchmark_t* benchmark);

/**
 * @brief Resets the benchmark statistics.
 * @param benchmark The fossil_benchmark_t object to reset.
 */
void fossil_benchmark_reset(fossil_benchmark_t* benchmark);

/**
 * @brief Prints a report of the benchmark statistics.
 * @param benchmark The fossil_benchmark_t object to report.
 */
void fossil_benchmark_report(const fossil_benchmark_t* benchmark);

typedef struct {
    fossil_benchmark_t* benchmark;
} scoped_benchmark_t;

/**
 * @brief Initializes a scoped_benchmark_t object with the given benchmark.
 * @param scoped_benchmark The scoped_benchmark_t object to initialize.
 * @param benchmark The benchmark to be scoped.
 */
void fossil_scoped_benchmark_init(scoped_benchmark_t* scoped_benchmark, fossil_benchmark_t* benchmark);

/**
 * @brief Destroys a scoped_benchmark_t object.
 * @param scoped_benchmark The scoped_benchmark_t object to destroy.
 */
void fossil_scoped_benchmark_destroy(scoped_benchmark_t* scoped_benchmark);

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

#endif // FOSSIL_MARK_FRAMEWORK_H
