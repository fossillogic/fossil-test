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
#include <fossil/unittest/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// placeholder

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(xassert_run_of_int) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSERT(x == 42, "Should have passed the test case");
    TEST_ASSERT(y == 20, "Should have passed the test case");
    TEST_ASSERT(x != y, "Should have passed the test case");
    TEST_ASSERT(y < x, "Should have passed the test case");
    TEST_ASSERT(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_run_of_int8) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    TEST_ASSERT((int8_t)x == 42, "Should have passed the test case");
    TEST_ASSERT((int8_t)y == 20, "Should have passed the test case");
    TEST_ASSERT((int8_t)x != (int8_t)y, "Should have passed the test case");
    TEST_ASSERT((int8_t)y < (int8_t)x, "Should have passed the test case");
    TEST_ASSERT((int8_t)y <= (int8_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_run_of_int16) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    TEST_ASSERT((int16_t)x == 42, "Should have passed the test case");
    TEST_ASSERT((int16_t)y == 20, "Should have passed the test case");
    TEST_ASSERT((int16_t)x != (int16_t)y, "Should have passed the test case");
    TEST_ASSERT((int16_t)y < (int16_t)x, "Should have passed the test case");
    TEST_ASSERT((int16_t)y <= (int16_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_run_of_int32) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    TEST_ASSERT((int32_t)x == 42, "Should have passed the test case");
    TEST_ASSERT((int32_t)y == 20, "Should have passed the test case");
    TEST_ASSERT((int32_t)x != (int32_t)y, "Should have passed the test case");
    TEST_ASSERT((int32_t)y < (int32_t)x, "Should have passed the test case");
    TEST_ASSERT((int32_t)y <= (int32_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_run_of_int64) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    TEST_ASSERT((int64_t)x == 42, "Should have passed the test case");
    TEST_ASSERT((int64_t)y == 20, "Should have passed the test case");
    TEST_ASSERT((int64_t)x != (int64_t)y, "Should have passed the test case");
    TEST_ASSERT((int64_t)y < (int64_t)x, "Should have passed the test case");
    TEST_ASSERT((int64_t)y <= (int64_t)x, "Should have passed the test case");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(tdd_test_group) {
    ADD_TEST(xassert_run_of_int);
    ADD_TEST(xassert_run_of_int8);
    ADD_TEST(xassert_run_of_int16);
    ADD_TEST(xassert_run_of_int32);
    ADD_TEST(xassert_run_of_int64);
} // end of group
