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
#include "fossil/benchmark/benchmark.h"
#include <stdio.h>
#include <time.h>
#include <float.h>
#include <stdarg.h>

//
// local types
//
static uint64_t start_time;

#if defined(_WIN32)
static double frequency; // Variable to store the frequency for Windows
#endif

void fossil_test_start_benchmark(void) {
#if defined(_WIN32)
    LARGE_INTEGER freq;
    if (!QueryPerformanceFrequency(&freq)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceFrequency failed\n");
        exit(EXIT_FAILURE);
    }
    frequency = (double)freq.QuadPart;
    if (!QueryPerformanceCounter((LARGE_INTEGER*)&start_time)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceCounter failed\n");
        exit(EXIT_FAILURE);
    }
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        // Handle error
        perror("Error: clock_gettime failed");
        exit(EXIT_FAILURE);
    }
    start_time = ts.tv_sec * 1e9 + ts.tv_nsec;
#endif
}

uint64_t fossil_test_stop_benchmark(void) {
#if defined(_WIN32)
    LARGE_INTEGER end_time;
    if (!QueryPerformanceCounter(&end_time)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceCounter failed\n");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)((end_time.QuadPart - start_time) * 1e9 / frequency);
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        // Handle error
        perror("Error: clock_gettime failed");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)((ts.tv_sec * 1e9 + ts.tv_nsec) - start_time);
#endif
}

void assume_duration(double expected, double actual, double unit) {
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / ((double)CLOCKS_PER_SEC / unit);
    if (elapsed_time < expected) {
        printf("Benchmark failed: expected %f, got %f\n", expected, actual);
    }
}

// Marks a test case as timeout with a specified time and prints it to stderr.
void fossil_test_benchmark(char* duration_type, double expected, double actual) {
    if (strcmp(duration_type, "minutes") == 0) {
        assume_duration(expected, actual, 60.0);
    } else if (strcmp(duration_type, "seconds") == 0) {
        assume_duration(expected, actual, 1.0);
    } else if (strcmp(duration_type, "milliseconds") == 0) {
        assume_duration(expected, actual, 0.001);
    } else if (strcmp(duration_type, "microseconds") == 0) {
        assume_duration(expected, actual, 1e-6);
    } else if (strcmp(duration_type, "nanoseconds") == 0) {
        assume_duration(expected, actual, 1e-9);
    } else if (strcmp(duration_type, "picoseconds") == 0) {
        assume_duration(expected, actual, 1e-12);
    } else if (strcmp(duration_type, "femtoseconds") == 0) {
        assume_duration(expected, actual, 1e-15);
    } else if (strcmp(duration_type, "attoseconds") == 0) {
        assume_duration(expected, actual, 1e-18);
    } else if (strcmp(duration_type, "zeptoseconds") == 0) {
        assume_duration(expected, actual, 1e-21);
    } else if (strcmp(duration_type, "yoctoseconds") == 0) {
        assume_duration(expected, actual, 1e-24);
    } else {
        printf("Unknown option: %s\n", duration_type);
    }
} // end of func

void fossil_benchmark_init(fossil_benchmark_t* benchmark, const char* name) {
    benchmark->name = name;
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
    benchmark->running = 0;
}

void fossil_benchmark_start(fossil_benchmark_t* benchmark) {
    if (!benchmark->running) {
        benchmark->start_time = clock();
        benchmark->running = 1;
    }
}

void fossil_benchmark_stop(fossil_benchmark_t* benchmark) {
    if (benchmark->running) {
        benchmark->end_time = clock();
        double elapsed = ((double)(benchmark->end_time - benchmark->start_time)) / CLOCKS_PER_SEC;
        benchmark->total_duration += elapsed;
        if (elapsed < benchmark->min_duration) {
            benchmark->min_duration = elapsed;
        }
        if (elapsed > benchmark->max_duration) {
            benchmark->max_duration = elapsed;
        }
        benchmark->num_samples++;
        benchmark->running = 0;
    }
}

double fossil_benchmark_elapsed_seconds(const fossil_benchmark_t* benchmark) {
    return benchmark->total_duration;
}

double fossil_benchmark_min_time(const fossil_benchmark_t* benchmark) {
    return benchmark->min_duration;
}

double fossil_benchmark_max_time(const fossil_benchmark_t* benchmark) {
    return benchmark->max_duration;
}

double fossil_benchmark_avg_time(const fossil_benchmark_t* benchmark) {
    return benchmark->num_samples > 0 ? benchmark->total_duration / benchmark->num_samples : 0.0;
}

void fossil_benchmark_reset(fossil_benchmark_t* benchmark) {
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
}

void fossil_benchmark_report(const fossil_benchmark_t* benchmark) {
    printf("\033[1;36mBenchmark : %s\n", benchmark->name);
    printf("\033[1;32mTotal Time: %.6f seconds\n", fossil_benchmark_elapsed_seconds(benchmark));
    printf("\033[1;32mMin Time  : %.6f seconds\n", fossil_benchmark_min_time(benchmark));
    printf("\033[1;32mMax Time  : %.6f seconds\n", fossil_benchmark_max_time(benchmark));
    printf("\033[1;32mAvg Time  : %.6f seconds\n", fossil_benchmark_avg_time(benchmark));
}

void fossil_scoped_benchmark_init(scoped_benchmark_t* scoped_benchmark, fossil_benchmark_t* benchmark) {
    scoped_benchmark->benchmark = benchmark;
    fossil_benchmark_start(scoped_benchmark->benchmark);
}

void fossil_scoped_benchmark_destroy(scoped_benchmark_t* scoped_benchmark) {
    fossil_benchmark_stop(scoped_benchmark->benchmark);
}
