/*
 * -----------------------------------------------------------------------------
 * File: benchmark.h
 * Project: Fossil Logic
 * Description: This file implments the benchmakring and scoped benchmarking.
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

#ifdef __cplusplus
// C++ interface
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

namespace fossil::mark {

    using clock = std::chrono::high_resolution_clock;
    using time_point = std::chrono::time_point<clock>;
    using duration = std::chrono::duration<double>;

    /**
     * @brief A class for benchmarking code execution time.
     */
    class Benchmark {
    public:
        /**
         * @brief Constructs a Benchmark object with the given name.
         * @param name The name of the benchmark.
         */
        Benchmark(const std::string &name) 
            : name(name), num_samples(0), total_duration(duration::zero()), 
              min_duration(duration::max()), max_duration(duration::zero()) {}

        /**
         * @brief Starts the benchmark timer.
         */
        void start();

        /**
         * @brief Stops the benchmark timer and calculates the elapsed time.
         */
        void stop();

        /**
         * @brief Returns the total elapsed time in seconds.
         * @return The total elapsed time in seconds.
         */
        double elapsed_seconds() const;

        /**
         * @brief Returns the total elapsed time in milliseconds.
         * @return The total elapsed time in milliseconds.
         */
        double elapsed_milliseconds() const;

        /**
         * @brief Returns the total elapsed time in microseconds.
         * @return The total elapsed time in microseconds.
         */
        double elapsed_microseconds() const;

        /**
         * @brief Returns the total elapsed time in nanoseconds.
         * @return The total elapsed time in nanoseconds.
         */
        double elapsed_nanoseconds() const;

        /**
         * @brief Returns the total elapsed time in picoseconds.
         * @return The total elapsed time in picoseconds.
         */
        double elapsed_picoseconds() const;

        /**
         * @brief Returns the total elapsed time in femtoseconds.
         * @return The total elapsed time in femtoseconds.
         */
        double elapsed_femtoseconds() const;

        /**
         * @brief Returns the total elapsed time in attoseconds.
         * @return The total elapsed time in attoseconds.
         */
        double elapsed_attoseconds() const;

        /**
         * @brief Returns the total elapsed time in zeptoseconds.
         * @return The total elapsed time in zeptoseconds.
         */
        double elapsed_zeptoseconds() const;

        /**
         * @brief Returns the total elapsed time in yoctoseconds.
         * @return The total elapsed time in yoctoseconds.
         */
        double elapsed_yoctoseconds() const;

        /**
         * @brief Returns the minimum elapsed time in seconds.
         * @return The minimum elapsed time in seconds.
         */
        double min_time() const;

        /**
         * @brief Returns the maximum elapsed time in seconds.
         * @return The maximum elapsed time in seconds.
         */
        double max_time() const;

        /**
         * @brief Returns the average elapsed time in seconds.
         * @return The average elapsed time in seconds.
         */
        double avg_time() const;

        /**
         * @brief Resets the benchmark statistics.
         */
        void reset();

        /**
         * @brief Prints a report of the benchmark statistics.
         */
        void report() const;

    private:
        std::string name;
        time_point start_time, end_time;
        bool running = false;
        int num_samples;
        duration total_duration, min_duration, max_duration;
    };

    /**
     * @brief A scoped benchmark class that automatically starts and stops the benchmark timer.
     */
    class ScopedBenchmark {
    public:
        /**
         * @brief Constructs a ScopedBenchmark object with the given benchmark.
         * @param benchmark The benchmark to be scoped.
         */
        ScopedBenchmark(Benchmark &benchmark) : benchmark(benchmark) {
            benchmark.start();
        }

        /**
         * @brief Stops the benchmark timer when the ScopedBenchmark object is destroyed.
         */
        ~ScopedBenchmark() {
            benchmark.stop();
        }

    private:
        Benchmark &benchmark;
    };

}

#else
// C interface
#include <stdio.h>
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
} FossilBenchmark;

/**
 * @brief Initializes a FossilBenchmark object with the given name.
 * @param benchmark The FossilBenchmark object to initialize.
 * @param name The name of the benchmark.
 */
void fossil_benchmark_init(FossilBenchmark* benchmark, const char* name);

/**
 * @brief Starts the benchmark timer.
 * @param benchmark The FossilBenchmark object to start.
 */
void fossil_benchmark_start(FossilBenchmark* benchmark);

/**
 * @brief Stops the benchmark timer.
 * @param benchmark The FossilBenchmark object to stop.
 */
void fossil_benchmark_stop(FossilBenchmark* benchmark);

/**
 * @brief Returns the total elapsed time in seconds.
 * @param benchmark The FossilBenchmark object to get the elapsed time from.
 * @return The total elapsed time in seconds.
 */
double fossil_benchmark_elapsed_seconds(const FossilBenchmark* benchmark);

/**
 * @brief Returns the minimum elapsed time in seconds.
 * @param benchmark The FossilBenchmark object to get the minimum time from.
 * @return The minimum elapsed time in seconds.
 */
double fossil_benchmark_min_time(const FossilBenchmark* benchmark);

/**
 * @brief Returns the maximum elapsed time in seconds.
 * @param benchmark The FossilBenchmark object to get the maximum time from.
 * @return The maximum elapsed time in seconds.
 */
double fossil_benchmark_max_time(const FossilBenchmark* benchmark);

/**
 * @brief Returns the average elapsed time in seconds.
 * @param benchmark The FossilBenchmark object to get the average time from.
 * @return The average elapsed time in seconds.
 */
double fossil_benchmark_avg_time(const FossilBenchmark* benchmark);

/**
 * @brief Resets the benchmark statistics.
 * @param benchmark The FossilBenchmark object to reset.
 */
void fossil_benchmark_reset(FossilBenchmark* benchmark);

/**
 * @brief Prints a report of the benchmark statistics.
 * @param benchmark The FossilBenchmark object to report.
 */
void fossil_benchmark_report(const FossilBenchmark* benchmark);

typedef struct {
    FossilBenchmark* benchmark;
} ScopedBenchmark;

/**
 * @brief Initializes a ScopedBenchmark object with the given benchmark.
 * @param scoped_benchmark The ScopedBenchmark object to initialize.
 * @param benchmark The benchmark to be scoped.
 */
void fossil_scoped_benchmark_init(ScopedBenchmark* scoped_benchmark, FossilBenchmark* benchmark);

/**
 * @brief Destroys a ScopedBenchmark object.
 * @param scoped_benchmark The ScopedBenchmark object to destroy.
 */
void fossil_scoped_benchmark_destroy(ScopedBenchmark* scoped_benchmark);

#endif

#endif // FOSSIL_MARK_FRAMEWORK_H
