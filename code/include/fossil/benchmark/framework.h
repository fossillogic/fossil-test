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

#ifdef __cplusplus
// C++ interface

// Macros for benchmarking
#define MARK_BENCHMARK(name) \
    fossil::mark::Benchmark benchmark_##name(#name)

#define MARK_START(name) \
    benchmark_##name.start()

#define MARK_STOP(name) \
    benchmark_##name.stop()

#define MARK_REPORT(name) \
    benchmark_##name.report()

#define MARK_SCOPED(name) \
    fossil::mark::ScopedBenchmark scoped_benchmark_##name(benchmark_##name)

#else
// C interface
// Macros for benchmarking
#define MARK_BENCHMARK(name) \
    FossilBenchmark benchmark_##name; \
    fossil_benchmark_init(&benchmark_##name, #name)

#define MARK_START(name) \
    fossil_benchmark_start(&benchmark_##name)

#define MARK_STOP(name) \
    fossil_benchmark_stop(&benchmark_##name)

#define MARK_REPORT(name) \
    fossil_benchmark_report(&benchmark_##name)

#define MARK_SCOPED(name) \
    ScopedBenchmark scoped_benchmark_##name; \
    fossil_scoped_benchmark_init(&scoped_benchmark_##name, &benchmark_##name)

#endif

#endif // FOSSIL_MARK_FRAMEWORK_HPP 
