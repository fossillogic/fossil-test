/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */

#include "fossil/pizza/framework.h"
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

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mark_test_cases) {
    FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start_and_stop);

    FOSSIL_TEST_REGISTER(cpp_mark_suite);
}
