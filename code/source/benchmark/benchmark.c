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

void fossil_benchmark_init(FossilBenchmark* benchmark, const char* name) {
    benchmark->name = name;
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
    benchmark->running = 0;
}

void fossil_benchmark_start(FossilBenchmark* benchmark) {
    if (!benchmark->running) {
        benchmark->start_time = clock();
        benchmark->running = 1;
    }
}

void fossil_benchmark_stop(FossilBenchmark* benchmark) {
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

double fossil_benchmark_elapsed_seconds(const FossilBenchmark* benchmark) {
    return benchmark->total_duration;
}

double fossil_benchmark_min_time(const FossilBenchmark* benchmark) {
    return benchmark->min_duration;
}

double fossil_benchmark_max_time(const FossilBenchmark* benchmark) {
    return benchmark->max_duration;
}

double fossil_benchmark_avg_time(const FossilBenchmark* benchmark) {
    return benchmark->num_samples > 0 ? benchmark->total_duration / benchmark->num_samples : 0.0;
}

void fossil_benchmark_reset(FossilBenchmark* benchmark) {
    benchmark->num_samples = 0;
    benchmark->total_duration = 0.0;
    benchmark->min_duration = DBL_MAX;
    benchmark->max_duration = 0.0;
}

void fossil_benchmark_report(const FossilBenchmark* benchmark) {
    printf("\033[1;36mBenchmark : %s\n", benchmark->name);
    printf("\033[1;32mTotal Time: %.6f seconds\n", fossil_benchmark_elapsed_seconds(benchmark));
    printf("\033[1;32mMin Time  : %.6f seconds\n", fossil_benchmark_min_time(benchmark));
    printf("\033[1;32mMax Time  : %.6f seconds\n", fossil_benchmark_max_time(benchmark));
    printf("\033[1;32mAvg Time  : %.6f seconds\n", fossil_benchmark_avg_time(benchmark));
}

void fossil_scoped_benchmark_init(ScopedBenchmark* scoped_benchmark, FossilBenchmark* benchmark) {
    scoped_benchmark->benchmark = benchmark;
    fossil_benchmark_start(scoped_benchmark->benchmark);
}

void fossil_scoped_benchmark_destroy(ScopedBenchmark* scoped_benchmark) {
    fossil_benchmark_stop(scoped_benchmark->benchmark);
}
