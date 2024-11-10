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

// A test case to check if the benchmark initialization works correctly
FOSSIL_TEST_CASE(cpp_mark_initialization) {
    MARK_BENCHMARK(init_test);
    FOSSIL_TEST_ASSUME(benchmark_init_test.name != NULL, "Benchmark initialization failed");
}

// A test case to check if the benchmark start works correctly
FOSSIL_TEST_CASE(cpp_mark_start) {
    MARK_BENCHMARK(start_test);
    MARK_START(start_test);
    FOSSIL_TEST_ASSUME(benchmark_start_test.start_time != 0, "Benchmark start failed");
}

// A test case to check if the benchmark stop works correctly
FOSSIL_TEST_CASE(cpp_mark_stop) {
    MARK_BENCHMARK(stop_test);
    MARK_START(stop_test);
    MARK_STOP(stop_test);
    FOSSIL_TEST_ASSUME(benchmark_stop_test.end_time != 0, "Benchmark stop failed");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mark_test_cases) {
    FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_initialization);
    FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start);
    FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_stop);

    FOSSIL_TEST_REGISTER(cpp_mark_suite);
}
