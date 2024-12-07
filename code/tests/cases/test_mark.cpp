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

#include "fossil/test/framework.h"
#include <string>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(cpp_mark_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_mark_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_mark_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// A test case to check if the benchmark stop works correctly
FOSSIL_TEST_CASE(cpp_mark_start_and_stop) {
    std::string benchmark_stop_test_name = "stop_test";
    MARK_BENCHMARK(stop_test);
    MARK_START(stop_test);
    MARK_STOP(stop_test);
    ASSUME_ITS_EQUAL_CSTR(benchmark_stop_test.name, benchmark_stop_test_name.c_str());
}

// A test case to check if the benchmark initialization works correctly
FOSSIL_TEST_CASE(cpp_mark_init) {
    fossil_benchmark_t benchmark;
    fossil_benchmark_init(&benchmark, "init_test");
    ASSUME_ITS_EQUAL_CSTR(benchmark.name, "init_test");
}

// A test case to check if the benchmark start works correctly
FOSSIL_TEST_CASE(cpp_mark_start) {
    fossil_benchmark_t benchmark;
    fossil_benchmark_init(&benchmark, "start_test");
    fossil_benchmark_start(&benchmark);
    // Assuming some way to check if the benchmark has started
    ASSUME_ITS_TRUE(benchmark.running);
    fossil_benchmark_stop(&benchmark);
}

// A test case to check if the benchmark stop works correctly
FOSSIL_TEST_CASE(cpp_mark_stop) {
    fossil_benchmark_t benchmark;
    fossil_benchmark_init(&benchmark, "stop_test");
    fossil_benchmark_start(&benchmark);
    fossil_benchmark_stop(&benchmark);
    // Assuming some way to check if the benchmark has stopped
    ASSUME_ITS_FALSE(benchmark.running);
}

// A test case to check if the elapsed time calculation works correctly
FOSSIL_TEST_CASE(cpp_mark_elapsed_time) {
    fossil_benchmark_t benchmark;
    fossil_benchmark_init(&benchmark, "elapsed_time_test");
    fossil_benchmark_start(&benchmark);
    // Simulate some delay
    fossil_benchmark_stop(&benchmark);
    double elapsed_time = fossil_benchmark_elapsed_seconds(&benchmark);
    ASSUME_ITS_TRUE(elapsed_time > 0);
    fossil_benchmark_stop(&benchmark);
}

// A test case to check if the benchmark reset works correctly
FOSSIL_TEST_CASE(cpp_mark_reset) {
    fossil_benchmark_t benchmark;
    fossil_benchmark_init(&benchmark, "reset_test");
    fossil_benchmark_start(&benchmark);
    fossil_benchmark_stop(&benchmark);
    fossil_benchmark_reset(&benchmark);
    double elapsed_time = fossil_benchmark_elapsed_seconds(&benchmark);
    ASSUME_ITS_TRUE(elapsed_time == 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mark_test_cases) {
    FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start_and_stop);
    // FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_init);
    // FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start);
    // FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_stop);
    // FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_elapsed_time);
    // FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_reset);

    FOSSIL_TEST_REGISTER(cpp_mark_suite);
}
