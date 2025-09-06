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

 // * * * * * * * * * * * * * * * * * * * * * * * *
 // * Fossil Logic Test Utilites
 // * * * * * * * * * * * * * * * * * * * * * * * *
 // Setup steps for things like test fixtures and
 // mock objects are set here.
 // * * * * * * * * * * * * * * * * * * * * * * * *
 
 // Define the test suite and add test cases
 FOSSIL_SUITE(cpp_mark_suite);
 
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
 FOSSIL_TEST(cpp_mark_start_and_stop) {
     MARK_BENCHMARK(stop_test);
     MARK_START(stop_test);
     MARK_STOP(stop_test);
     ASSUME_ITS_EQUAL_CSTR(benchmark_stop_test.name, "stop_test");
 }
 
 // Test case for MARK_BENCHMARK
 FOSSIL_TEST(cpp_mark_benchmark) {
     MARK_BENCHMARK(test_benchmark);
     ASSUME_ITS_EQUAL_CSTR(benchmark_test_benchmark.name, "test_benchmark");
 }
 
 // Test case for MARK_START
 FOSSIL_TEST(cpp_mark_start) {
     MARK_BENCHMARK(start_test);
     MARK_START(start_test);
     ASSUME_ITS_TRUE(benchmark_start_test.running);
 }
 
 // Test case for MARK_STOP
 FOSSIL_TEST(cpp_mark_stop) {
     MARK_BENCHMARK(stop_test);
     MARK_START(stop_test);
     MARK_STOP(stop_test);
     ASSUME_ITS_FALSE(benchmark_stop_test.running);
 }
 
 // Test case for MARK_BENCHMARK with multiple benchmarks
 FOSSIL_TEST(cpp_mark_multiple_benchmarks) {
     MARK_BENCHMARK(benchmark1);
     MARK_BENCHMARK(benchmark2);
     ASSUME_ITS_EQUAL_CSTR(benchmark_benchmark1.name, "benchmark1");
     ASSUME_ITS_EQUAL_CSTR(benchmark_benchmark2.name, "benchmark2");
 }
 
 // Test case for MARK_START and MARK_STOP with elapsed time
 FOSSIL_TEST(cpp_mark_elapsed_time) {
     MARK_BENCHMARK(elapsed_test);
     MARK_START(elapsed_test);
     MARK_STOP(elapsed_test);
     ASSUME_ITS_FALSE(benchmark_elapsed_test.total_duration > 0.0);
 }
 
 // Test case for MARK_BENCHMARK with invalid name
 FOSSIL_TEST(cpp_mark_invalid_benchmark_name) {
     MARK_BENCHMARK(null_benchmark);
     ASSUME_NOT_CNULL(benchmark_null_benchmark.name);
 }
 
 // Test case for MARK_STOP without MARK_START
 FOSSIL_TEST(cpp_mark_stop_without_start) {
     MARK_BENCHMARK(stop_without_start);
     MARK_STOP(stop_without_start);
     ASSUME_ITS_FALSE(benchmark_stop_without_start.running);
 }
 
 // Test case for MARK_BENCHMARK with nested benchmarks
 FOSSIL_TEST(cpp_mark_nested_benchmarks) {
     MARK_BENCHMARK(outer_benchmark);
     MARK_START(outer_benchmark);
     MARK_BENCHMARK(inner_benchmark);
     MARK_START(inner_benchmark);
     MARK_STOP(inner_benchmark);
     MARK_STOP(outer_benchmark);
     ASSUME_ITS_TRUE(benchmark_outer_benchmark.total_duration >= benchmark_inner_benchmark.total_duration);
 }
 
 // Test case for resetting a benchmark
 FOSSIL_TEST(cpp_mark_reset_benchmark) {
     MARK_BENCHMARK(reset_test);
     MARK_START(reset_test);
     MARK_STOP(reset_test);
     fossil_benchmark_reset(&benchmark_reset_test);
     ASSUME_ITS_EQUAL_I32(benchmark_reset_test.total_duration, 0.0);
     ASSUME_ITS_EQUAL_I32(benchmark_reset_test.num_samples, 0);
 }
 
 // * * * * * * * * * * * * * * * * * * * * * * * *
 // * Fossil Logic Test Pool
 // * * * * * * * * * * * * * * * * * * * * * * * *
 FOSSIL_TEST_GROUP(cpp_mark_test_cases) {
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start_and_stop);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_benchmark);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_start);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_stop);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_multiple_benchmarks);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_elapsed_time);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_invalid_benchmark_name);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_stop_without_start);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_nested_benchmarks);
     FOSSIL_TEST_ADD(cpp_mark_suite, cpp_mark_reset_benchmark);
 
     FOSSIL_TEST_REGISTER(cpp_mark_suite);
 }
 