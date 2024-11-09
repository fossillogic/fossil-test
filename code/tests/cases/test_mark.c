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
FOSSIL_TEST_SUITE(c_mark_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_mark_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_mark_suite) {
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
FOSSIL_TEST_CASE(c_mark_initialization) {
    MARK_BENCHMARK(init_test);
    FOSSIL_TEST_ASSUME(benchmark_init_test.name != NULL, "Benchmark initialization failed");
}

// A test case to check if the benchmark start works correctly
FOSSIL_TEST_CASE(c_mark_start) {
    MARK_BENCHMARK(start_test);
    MARK_START(start_test);
    FOSSIL_TEST_ASSUME(benchmark_start_test.start_time != 0, "Benchmark start failed");
}

// A test case to check if the benchmark stop works correctly
FOSSIL_TEST_CASE(c_mark_stop) {
    MARK_BENCHMARK(stop_test);
    MARK_START(stop_test);
    MARK_STOP(stop_test);
    FOSSIL_TEST_ASSUME(benchmark_stop_test.end_time != 0, "Benchmark stop failed");
}

// A test case to check if the benchmark report works correctly
FOSSIL_TEST_CASE(c_mark_report) {
    MARK_BENCHMARK(report_test);
    MARK_START(report_test);
    MARK_STOP(report_test);
    MARK_REPORT(report_test);
    FOSSIL_TEST_ASSUME(benchmark_report_test.total_duration != 0, "Benchmark report failed");
}

// A test case to check if the scoped benchmark works correctly
FOSSIL_TEST_CASE(c_mark_scoped_benchmark) {
    MARK_BENCHMARK(scoped_test);
    MARK_SCOPED(scoped_test);
    FOSSIL_TEST_ASSUME(scoped_benchmark_scoped_test.benchmark != NULL, "Scoped benchmark failed");
}

// A test case to check if the benchmark duration in minutes works correctly
FOSSIL_TEST_CASE(c_mark_duration_minutes) {
    MARK_BENCHMARK(duration_minutes_test);
    MARK_START(duration_minutes_test);
    // Simulate some work here
    MARK_STOP(duration_minutes_test);
    TEST_DURATION_MIN(benchmark_duration_minutes_test.start_time, benchmark_duration_minutes_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_minutes_test.total_duration != 0, "Benchmark duration in minutes failed");
}

// A test case to check if the benchmark duration in seconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_seconds) {
    MARK_BENCHMARK(duration_seconds_test);
    MARK_START(duration_seconds_test);
    // Simulate some work here
    MARK_STOP(duration_seconds_test);
    TEST_DURATION_SEC(benchmark_duration_seconds_test.start_time, benchmark_duration_seconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_seconds_test.total_duration != 0, "Benchmark duration in seconds failed");
}

// A test case to check if the benchmark duration in milliseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_milliseconds) {
    MARK_BENCHMARK(duration_milliseconds_test);
    MARK_START(duration_milliseconds_test);
    // Simulate some work here
    MARK_STOP(duration_milliseconds_test);
    TEST_DURATION_MIL(benchmark_duration_milliseconds_test.start_time, benchmark_duration_milliseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_milliseconds_test.total_duration != 0, "Benchmark duration in milliseconds failed");
}

// A test case to check if the benchmark duration in microseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_microseconds) {
    MARK_BENCHMARK(duration_microseconds_test);
    MARK_START(duration_microseconds_test);
    // Simulate some work here
    MARK_STOP(duration_microseconds_test);
    TEST_DURATION_MIC(benchmark_duration_microseconds_test.start_time, benchmark_duration_microseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_microseconds_test.total_duration != 0, "Benchmark duration in microseconds failed");
}

// A test case to check if the benchmark duration in nanoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_nanoseconds) {
    MARK_BENCHMARK(duration_nanoseconds_test);
    MARK_START(duration_nanoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_nanoseconds_test);
    TEST_DURATION_NAN(benchmark_duration_nanoseconds_test.start_time, benchmark_duration_nanoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_nanoseconds_test.total_duration != 0, "Benchmark duration in nanoseconds failed");
}

// A test case to check if the benchmark duration in picoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_picoseconds) {
    MARK_BENCHMARK(duration_picoseconds_test);
    MARK_START(duration_picoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_picoseconds_test);
    TEST_DURATION_PIC(benchmark_duration_picoseconds_test.start_time, benchmark_duration_picoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_picoseconds_test.total_duration != 0, "Benchmark duration in picoseconds failed");
}

// A test case to check if the benchmark duration in femtoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_femtoseconds) {
    MARK_BENCHMARK(duration_femtoseconds_test);
    MARK_START(duration_femtoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_femtoseconds_test);
    TEST_DURATION_FEM(benchmark_duration_femtoseconds_test.start_time, benchmark_duration_femtoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_femtoseconds_test.total_duration != 0, "Benchmark duration in femtoseconds failed");
}

// A test case to check if the benchmark duration in attoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_attoseconds) {
    MARK_BENCHMARK(duration_attoseconds_test);
    MARK_START(duration_attoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_attoseconds_test);
    TEST_DURATION_ATT(benchmark_duration_attoseconds_test.start_time, benchmark_duration_attoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_attoseconds_test.total_duration != 0, "Benchmark duration in attoseconds failed");
}

// A test case to check if the benchmark duration in zeptoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_zeptoseconds) {
    MARK_BENCHMARK(duration_zeptoseconds_test);
    MARK_START(duration_zeptoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_zeptoseconds_test);
    TEST_DURATION_ZEP(benchmark_duration_zeptoseconds_test.start_time, benchmark_duration_zeptoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_zeptoseconds_test.total_duration != 0, "Benchmark duration in zeptoseconds failed");
}

// A test case to check if the benchmark duration in yoctoseconds works correctly
FOSSIL_TEST_CASE(c_mark_duration_yoctoseconds) {
    MARK_BENCHMARK(duration_yoctoseconds_test);
    MARK_START(duration_yoctoseconds_test);
    // Simulate some work here
    MARK_STOP(duration_yoctoseconds_test);
    TEST_DURATION_YOC(benchmark_duration_yoctoseconds_test.start_time, benchmark_duration_yoctoseconds_test.end_time);
    FOSSIL_TEST_ASSUME(benchmark_duration_yoctoseconds_test.total_duration != 0, "Benchmark duration in yoctoseconds failed");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_mark_test_cases) {
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_initialization);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_start);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_stop);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_report);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_scoped_benchmark);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_minutes);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_seconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_milliseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_microseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_nanoseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_picoseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_femtoseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_attoseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_zeptoseconds);
    FOSSIL_TEST_ADD(c_mark_suite, c_mark_duration_yoctoseconds);

    FOSSIL_TEST_REGISTER(c_mark_suite);
}
