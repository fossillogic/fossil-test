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
#include "fossil/maip/mark.h"
#include "fossil/maip/common.h"
#include <assert.h>

#if defined(_MSC_VER)
#define FOSSIL_THREAD_LOCAL __declspec(thread)
#elif defined(__GNUC__) || defined(__clang__)
#define FOSSIL_THREAD_LOCAL __thread
#else
#define FOSSIL_THREAD_LOCAL _Thread_local
#endif

#if defined(_WIN32)
static FOSSIL_THREAD_LOCAL LARGE_INTEGER frequency;
static FOSSIL_THREAD_LOCAL LARGE_INTEGER start_time;
#elif defined(__APPLE__)
static FOSSIL_THREAD_LOCAL uint64_t start_time;
#else
static FOSSIL_THREAD_LOCAL uint64_t start_time;
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
    uint64_t elapsed = end_time - start_time;
    return (elapsed / timebase.denom) * timebase.numer +
           ((elapsed % timebase.denom) * timebase.numer) / timebase.denom;
#else
    struct timeval tv;
    gettimeofday(&tv, null);
    uint64_t end_time = (uint64_t)tv.tv_sec * 1e6 + tv.tv_usec;
    return (end_time - start_time) * 1e3;
#endif
}

void assume_duration(double expected, double actual, double unit) {
    uint64_t elapsed_time = fossil_test_stop_benchmark();
    double elapsed_in_unit = (elapsed_time / 1e9) / unit;
    (void)actual;
    
    if (elapsed_in_unit > expected) {
        maip_io_printf("Benchmark failed: expected at most %f, got %f\n", expected, elapsed_in_unit);
        assert(elapsed_in_unit <= expected);
    }
}

// Marks a test case as timeout with a specified time and prints it to stderr.
void fossil_test_benchmark(char* duration_type, double expected, double actual) {
    if (duration_type == null) {
        maip_io_printf("Error: duration_type is null\n");
        return;
    }

    if (maip_io_cstr_compare(duration_type, "minutes") == 0) {
        assume_duration(expected, actual, 60.0);
    } else if (maip_io_cstr_compare(duration_type, "seconds") == 0) {
        assume_duration(expected, actual, 1.0);
    } else if (maip_io_cstr_compare(duration_type, "milliseconds") == 0) {
        assume_duration(expected, actual, 0.001);
    } else if (maip_io_cstr_compare(duration_type, "microseconds") == 0) {
        assume_duration(expected, actual, 1e-6);
    } else if (maip_io_cstr_compare(duration_type, "nanoseconds") == 0) {
        assume_duration(expected, actual, 1e-9);
    } else if (maip_io_cstr_compare(duration_type, "picoseconds") == 0) {
        assume_duration(expected, actual, 1e-12);
    } else if (maip_io_cstr_compare(duration_type, "femtoseconds") == 0) {
        assume_duration(expected, actual, 1e-15);
    } else if (maip_io_cstr_compare(duration_type, "attoseconds") == 0) {
        assume_duration(expected, actual, 1e-18);
    } else if (maip_io_cstr_compare(duration_type, "zeptoseconds") == 0) {
        assume_duration(expected, actual, 1e-21);
    } else if (maip_io_cstr_compare(duration_type, "yoctoseconds") == 0) {
        assume_duration(expected, actual, 1e-24);
    } else {
        printf("Unknown option: %s\n", duration_type);
    }
} // end of func

void fossil_benchmark_init(fossil_mark_t* benchmark, const char* name) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }

    if (name == null) {
        maip_io_printf("Error: name is null\n");
        return;
    }

    benchmark->name = name;
    benchmark->num_samples = 0;
    benchmark->num_iterations = 0;
    benchmark->num_warmup = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
    benchmark->mean_duration = 0.0;
    benchmark->median_duration = 0.0;
    benchmark->std_dev = 0.0;
    benchmark->capacity = 100;
    benchmark->iteration_times = (uint64_t*)malloc(benchmark->capacity * sizeof(uint64_t));
    if (benchmark->iteration_times == null) {
        benchmark->capacity = 0;
        maip_io_printf("Error: unable to allocate benchmark samples\n");
    }
    benchmark->running = 0;
}

void fossil_benchmark_start(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }

    if (!benchmark->running) {
        fossil_test_start_benchmark();
        benchmark->running = 1;
    }
}

void fossil_benchmark_calculate_stats(fossil_mark_t* benchmark);

void fossil_benchmark_stop(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }

    if (benchmark->running) {
        uint64_t elapsed = fossil_test_stop_benchmark();
        
        if (benchmark->num_iterations >= benchmark->num_warmup) {
            if (benchmark->num_samples >= benchmark->capacity) {
                size_t new_capacity = benchmark->capacity ? benchmark->capacity * 2 : 100;
                uint64_t* new_times = (uint64_t*)realloc(benchmark->iteration_times,
                                                         new_capacity * sizeof(uint64_t));
                if (new_times == null) {
                    maip_io_printf("Error: unable to grow benchmark sample buffer\n");
                    benchmark->num_iterations++;
                    benchmark->running = 0;
                    return;
                }
                benchmark->iteration_times = new_times;
                benchmark->capacity = new_capacity;
            }
            benchmark->iteration_times[benchmark->num_samples] = elapsed;
            benchmark->total_duration += elapsed / 1e9;
            benchmark->min_duration = (elapsed / 1e9 < benchmark->min_duration) ? (elapsed / 1e9) : benchmark->min_duration;
            benchmark->max_duration = (elapsed / 1e9 > benchmark->max_duration) ? (elapsed / 1e9) : benchmark->max_duration;
            benchmark->num_samples++;
            fossil_benchmark_calculate_stats(benchmark);
        }
        benchmark->num_iterations++;
        benchmark->running = 0;
    }
}

static int compare_uint64(const void* a, const void* b) {
    return (*((uint64_t*)a) > *((uint64_t*)b)) - (*((uint64_t*)a) < *((uint64_t*)b));
}

void fossil_benchmark_calculate_stats(fossil_mark_t* benchmark) {
    if (benchmark == null || benchmark->num_samples == 0) {
        return;
    }

    benchmark->mean_duration = benchmark->total_duration / benchmark->num_samples;
    
    qsort(benchmark->iteration_times, benchmark->num_samples, sizeof(uint64_t), compare_uint64);
    
    if (benchmark->num_samples % 2 == 0) {
        benchmark->median_duration = ((benchmark->iteration_times[benchmark->num_samples / 2 - 1] + 
                                       benchmark->iteration_times[benchmark->num_samples / 2]) / 2.0) / 1e9;
    } else {
        benchmark->median_duration = (benchmark->iteration_times[benchmark->num_samples / 2] / 1e9);
    }
    
    double variance = 0.0;
    for (size_t i = 0; i < benchmark->num_samples; i++) {
        double diff = (benchmark->iteration_times[i] / 1e9) - benchmark->mean_duration;
        variance += diff * diff;
    }
    benchmark->std_dev = sqrt(variance / benchmark->num_samples);
}

double fossil_benchmark_elapsed_seconds(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->total_duration;
}

double fossil_benchmark_min_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->min_duration;
}

double fossil_benchmark_max_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->max_duration;
}

double fossil_benchmark_avg_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->num_samples > 0 ? benchmark->mean_duration : 0.0;
}

double fossil_benchmark_median_time(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->median_duration;
}

double fossil_benchmark_std_dev(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return 0.0;
    }
    return benchmark->std_dev;
}

void fossil_benchmark_reset(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }
    benchmark->num_samples = 0;
    benchmark->num_iterations = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
    benchmark->mean_duration = 0.0;
    benchmark->median_duration = 0.0;
    benchmark->std_dev = 0.0;
}

void fossil_benchmark_report(const fossil_mark_t* benchmark) {
    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }
    maip_io_printf("{blue,bold}Benchmark : %s{reset}\n", benchmark->name);
    maip_io_printf("{cyan}Iterations: %zu (warmup: %zu){reset}\n", benchmark->num_samples, benchmark->num_warmup);
    maip_io_printf("{cyan}Total Time: %.6f seconds{reset}\n", fossil_benchmark_elapsed_seconds(benchmark));
    maip_io_printf("{cyan}Mean Time : %.6f seconds{reset}\n", fossil_benchmark_avg_time(benchmark));
    maip_io_printf("{cyan}Median Time: %.6f seconds{reset}\n", fossil_benchmark_median_time(benchmark));
    maip_io_printf("{cyan}Min Time  : %.6f seconds{reset}\n", fossil_benchmark_min_time(benchmark));
    maip_io_printf("{cyan}Max Time  : %.6f seconds{reset}\n", fossil_benchmark_max_time(benchmark));
    maip_io_printf("{cyan}Std Dev   : %.6f seconds (±%.2f%%){reset}\n", 
                    fossil_benchmark_std_dev(benchmark),
                    (fossil_benchmark_std_dev(benchmark) / fossil_benchmark_avg_time(benchmark)) * 100.0);
}

void fossil_benchmark_destroy(fossil_mark_t* benchmark) {
    if (benchmark == null) {
        return;
    }
    if (benchmark->iteration_times != null) {
        free(benchmark->iteration_times);
        benchmark->iteration_times = null;
    }
}

void fossil_scoped_benchmark_init(fossil_scoped_mark_t* scoped_benchmark, fossil_mark_t* benchmark) {
    if (scoped_benchmark == null) {
        maip_io_printf("Error: scoped_benchmark is null\n");
        return;
    }

    if (benchmark == null) {
        maip_io_printf("Error: benchmark is null\n");
        return;
    }

    scoped_benchmark->benchmark = benchmark;
    fossil_benchmark_start(scoped_benchmark->benchmark);
}

void fossil_scoped_benchmark_destroy(fossil_scoped_mark_t* scoped_benchmark) {
    if (scoped_benchmark == null) {
        maip_io_printf("Error: scoped_benchmark is null\n");
        return;
    }

    fossil_benchmark_stop(scoped_benchmark->benchmark);
}
