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
#include "fossil/unittest/benchmark.h"
#include "fossil/unittest/internal.h"
#include <stdarg.h>

// ==============================================================================
// Xmark functions for benchmarks
// ==============================================================================

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
        output_benchmark_format(expected, actual);
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
        fossil_test_cout("red", "Unknown option: %s\n", duration_type);
    }
} // end of func
