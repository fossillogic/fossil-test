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
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/pizza/mark.h"
#include "fossil/pizza/common.h"

#if defined(_WIN32)
static LARGE_INTEGER frequency;
static LARGE_INTEGER start_time;
#elif defined(__APPLE__)
clock_t start_time;
#else
clock_t start_time;
#endif

#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

void fossil_test_start_benchmark(void) {
#if defined(_WIN32)
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);
#elif defined(__APPLE__)
    start_time = mach_absolute_time();
#else
    struct timeval tv;
    gettimeofday(&tv, null);
    start_time = (uint64_t)tv.tv_sec * 1e6 + tv.tv_usec;
#endif
}

uint64_t fossil_test_stop_benchmark(void) {
#if defined(_WIN32)
    LARGE_INTEGER end_time;
    QueryPerformanceCounter(&end_time);
    return (uint64_t)((end_time.QuadPart - start_time.QuadPart) * 1e9 / frequency.QuadPart);
#elif defined(__APPLE__)
    uint64_t end_time = mach_absolute_time();
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    return (end_time - start_time) * timebase.numer / timebase.denom;
#else
    struct timeval tv;
    gettimeofday(&tv, null);
    uint64_t end_time = (uint64_t)tv.tv_sec * 1e6 + tv.tv_usec;
    return (end_time - start_time) * 1e3;
#endif
}

void assume_duration(double expected, double actual, double unit) {
    uint64_t elapsed_time = fossil_test_stop_benchmark();
    double elapsed_seconds = elapsed_time / (1e9 / unit);  // Convert to the desired time unit
    
    if (elapsed_seconds < expected) {
        pizza_io_printf("Benchmark failed: expected %f, got %f\n", expected, actual);
    }
}

// Marks a test case as timeout with a specified time and prints it to stderr.
void fossil_test_benchmark(char* duration_type, double expected, double actual) {
    if (duration_type == null) {
        pizza_io_printf("Error: duration_type is null\n");
        return;
    }

    if (pizza_io_cstr_compare(duration_type, "minutes") == 0) {
        assume_duration(expected, actual, 60.0);
    } else if (pizza_io_cstr_compare(duration_type, "seconds") == 0) {
        assume_duration(expected, actual, 1.0);
    } else if (pizza_io_cstr_compare(duration_type, "milliseconds") == 0) {
        assume_duration(expected, actual, 0.001);
    } else if (pizza_io_cstr_compare(duration_type, "microseconds") == 0) {
        assume_duration(expected, actual, 1e-6);
    } else if (pizza_io_cstr_compare(duration_type, "nanoseconds") == 0) {
        assume_duration(expected, actual, 1e-9);
    } else if (pizza_io_cstr_compare(duration_type, "picoseconds") == 0) {
        assume_duration(expected, actual, 1e-12);
    } else if (pizza_io_cstr_compare(duration_type, "femtoseconds") == 0) {
        assume_duration(expected, actual, 1e-15);
    } else if (pizza_io_cstr_compare(duration_type, "attoseconds") == 0) {
        assume_duration(expected, actual, 1e-18);
    } else if (pizza_io_cstr_compare(duration_type, "zeptoseconds") == 0) {
        assume_duration(expected, actual, 1e-21);
    } else if (pizza_io_cstr_compare(duration_type, "yoctoseconds") == 0) {
        assume_duration(expected, actual, 1e-24);
    } else {
        printf("Unknown option: %s\n", duration_type);
    }
} // end of func

void fossil_benchmark_init(fossil_mark_t* benchmark, const char* name) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }

    if (name == null) {
        pizza_io_printf("Error: name is null\n");
        return;
    }

    benchmark->name = name;
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
    benchmark->running = 0;
}

void fossil_benchmark_start(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }

    if (!benchmark->running) {
        benchmark->start_time = clock();
        benchmark->running = 1;
    }
}

void fossil_benchmark_stop(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }

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

double fossil_benchmark_elapsed_seconds(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->total_duration;
}

double fossil_benchmark_min_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->min_duration;
}

double fossil_benchmark_max_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->max_duration;
}

double fossil_benchmark_avg_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->num_samples > 0 ? benchmark->total_duration / benchmark->num_samples : 0.0;
}

void fossil_benchmark_reset(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
}

void fossil_benchmark_report(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }
    pizza_io_printf("{blue,bold}Benchmark : %s{reset}\n", benchmark->name);
    pizza_io_printf("{cyan}Total Time: %.6f seconds{reset}\n", fossil_benchmark_elapsed_seconds(benchmark));
    pizza_io_printf("{cyan}Min Time  : %.6f seconds{reset}\n", fossil_benchmark_min_time(benchmark));
    pizza_io_printf("{cyan}Max Time  : %.6f seconds{reset}\n", fossil_benchmark_max_time(benchmark));
    pizza_io_printf("{cyan}Avg Time  : %.6f seconds{reset}\n", fossil_benchmark_avg_time(benchmark));
}

void fossil_scoped_benchmark_init(fossil_scoped_mark_t* scoped_benchmark, fossil_mark_t* benchmark) {
    if (scoped_benchmark == null) {
        pizza_io_printf("Error: scoped_benchmark is null\n");
        return;
    }

    if (benchmark == null) {
        pizza_io_printf("Error: benchmark is null\n");
        return;
    }

    scoped_benchmark->benchmark = benchmark;
    fossil_benchmark_start(scoped_benchmark->benchmark);
}

void fossil_scoped_benchmark_destroy(fossil_scoped_mark_t* scoped_benchmark) {
    if (scoped_benchmark == null) {
        pizza_io_printf("Error: scoped_benchmark is null\n");
        return;
    }

    fossil_benchmark_stop(scoped_benchmark->benchmark);
}
