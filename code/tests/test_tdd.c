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

// list of include headers that extends
// the framework assertion collection.
#include <fossil/unittest/assert.h>
#include <fossil/unittest/assume.h>
#include <fossil/unittest/expect.h>

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

FOSSIL_TEST(xassert_run_of_int8_shortcut) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    ASSERT_ITS_EQUAL_I8((int8_t)x, 42);
    ASSERT_ITS_EQUAL_I8((int8_t)y, 20);
    ASSERT_NOT_EQUAL_I8((int8_t)x, (int8_t)y);
    ASSERT_ITS_LESS_THAN_I8((int8_t)y, (int8_t)x);
    ASSERT_ITS_LESS_OR_EQUAL_I8((int8_t)y, (int8_t)x);
} // end case

FOSSIL_TEST(xassert_run_of_int16_shortcut) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    ASSERT_ITS_EQUAL_I16((int16_t)x, 42);
    ASSERT_ITS_EQUAL_I16((int16_t)y, 20);
    ASSERT_NOT_EQUAL_I16((int16_t)x, (int16_t)y);
    ASSERT_ITS_LESS_THAN_I16((int16_t)y, (int16_t)x);
    ASSERT_ITS_LESS_OR_EQUAL_I16((int16_t)y, (int16_t)x);
} // end case

FOSSIL_TEST(xassert_run_of_int32_shortcut) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    ASSERT_ITS_EQUAL_I32((int32_t)x, 42);
    ASSERT_ITS_EQUAL_I32((int32_t)y, 20);
    ASSERT_NOT_EQUAL_I32((int32_t)x, (int32_t)y);
    ASSERT_ITS_LESS_THAN_I32((int32_t)y, (int32_t)x);
    ASSERT_ITS_LESS_OR_EQUAL_I32((int32_t)y, (int32_t)x);
} // end case

FOSSIL_TEST(xassert_run_of_int64_shortcut) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    ASSERT_ITS_EQUAL_I64((int64_t)x, 42);
    ASSERT_ITS_EQUAL_I64((int64_t)y, 20);
    ASSERT_NOT_EQUAL_I64((int64_t)x, (int64_t)y);
    ASSERT_ITS_LESS_THAN_I64((int64_t)y, (int64_t)x);
    ASSERT_ITS_LESS_OR_EQUAL_I64((int64_t)y, (int64_t)x);
} // end case

FOSSIL_TEST(xassume_run_of_int) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSUME(x == 42, "Should have passed the test case");
    TEST_ASSUME(y == 20, "Should have passed the test case");
    TEST_ASSUME(x != y, "Should have passed the test case");
    TEST_ASSUME(y < x, "Should have passed the test case");
    TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassume_run_of_int8) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    TEST_ASSUME((int8_t)x == 42, "Should have passed the test case");
    TEST_ASSUME((int8_t)y == 20, "Should have passed the test case");
    TEST_ASSUME((int8_t)x != (int8_t)y, "Should have passed the test case");
    TEST_ASSUME((int8_t)y < (int8_t)x, "Should have passed the test case");
    TEST_ASSUME((int8_t)y <= (int8_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassume_run_of_int16) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    TEST_ASSUME((int16_t)x == 42, "Should have passed the test case");
    TEST_ASSUME((int16_t)y == 20, "Should have passed the test case");
    TEST_ASSUME((int16_t)x != (int16_t)y, "Should have passed the test case");
    TEST_ASSUME((int16_t)y < (int16_t)x, "Should have passed the test case");
    TEST_ASSUME((int16_t)y <= (int16_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassume_run_of_int32) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    TEST_ASSUME((int32_t)x == 42, "Should have passed the test case");
    TEST_ASSUME((int32_t)y == 20, "Should have passed the test case");
    TEST_ASSUME((int32_t)x != (int32_t)y, "Should have passed the test case");
    TEST_ASSUME((int32_t)y < (int32_t)x, "Should have passed the test case");
    TEST_ASSUME((int32_t)y <= (int32_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassume_run_of_int64) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    TEST_ASSUME((int64_t)x == 42, "Should have passed the test case");
    TEST_ASSUME((int64_t)y == 20, "Should have passed the test case");
    TEST_ASSUME((int64_t)x != (int64_t)y, "Should have passed the test case");
    TEST_ASSUME((int64_t)y < (int64_t)x, "Should have passed the test case");
    TEST_ASSUME((int64_t)y <= (int64_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassume_run_of_int8_shortcut) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I8((int8_t)x, 42);
    ASSUME_ITS_EQUAL_I8((int8_t)y, 20);
    ASSUME_NOT_EQUAL_I8((int8_t)x, (int8_t)y);
    ASSUME_ITS_LESS_THAN_I8((int8_t)y, (int8_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I8((int8_t)y, (int8_t)x);
} // end case

FOSSIL_TEST(xassume_run_of_int16_shortcut) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I16((int16_t)x, 42);
    ASSUME_ITS_EQUAL_I16((int16_t)y, 20);
    ASSUME_NOT_EQUAL_I16((int16_t)x, (int16_t)y);
    ASSUME_ITS_LESS_THAN_I16((int16_t)y, (int16_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I16((int16_t)y, (int16_t)x);
} // end case

FOSSIL_TEST(xassume_run_of_int32_shortcut) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I32((int32_t)x, 42);
    ASSUME_ITS_EQUAL_I32((int32_t)y, 20);
    ASSUME_NOT_EQUAL_I32((int32_t)x, (int32_t)y);
    ASSUME_ITS_LESS_THAN_I32((int32_t)y, (int32_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I32((int32_t)y, (int32_t)x);
} // end case

FOSSIL_TEST(xassume_run_of_int64_shortcut) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I64((int64_t)x, 42);
    ASSUME_ITS_EQUAL_I64((int64_t)y, 20);
    ASSUME_NOT_EQUAL_I64((int64_t)x, (int64_t)y);
    ASSUME_ITS_LESS_THAN_I64((int64_t)y, (int64_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I64((int64_t)y, (int64_t)x);
} // end case

FOSSIL_TEST(xexpect_run_of_int) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_EXPECT(x == 42, "Should have passed the test case");
    TEST_EXPECT(y == 20, "Should have passed the test case");
    TEST_EXPECT(x != y, "Should have passed the test case");
    TEST_EXPECT(y < x, "Should have passed the test case");
    TEST_EXPECT(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xexpect_run_of_int8) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    TEST_EXPECT((int8_t)x == 42, "Should have passed the test case");
    TEST_EXPECT((int8_t)y == 20, "Should have passed the test case");
    TEST_EXPECT((int8_t)x != (int8_t)y, "Should have passed the test case");
    TEST_EXPECT((int8_t)y < (int8_t)x, "Should have passed the test case");
    TEST_EXPECT((int8_t)y <= (int8_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xexpect_run_of_int16) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    TEST_EXPECT((int16_t)x == 42, "Should have passed the test case");
    TEST_EXPECT((int16_t)y == 20, "Should have passed the test case");
    TEST_EXPECT((int16_t)x != (int16_t)y, "Should have passed the test case");
    TEST_EXPECT((int16_t)y < (int16_t)x, "Should have passed the test case");
    TEST_EXPECT((int16_t)y <= (int16_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xexpect_run_of_int32) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    TEST_EXPECT((int32_t)x == 42, "Should have passed the test case");
    TEST_EXPECT((int32_t)y == 20, "Should have passed the test case");
    TEST_EXPECT((int32_t)x != (int32_t)y, "Should have passed the test case");
    TEST_EXPECT((int32_t)y < (int32_t)x, "Should have passed the test case");
    TEST_EXPECT((int32_t)y <= (int32_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xexpect_run_of_int64) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    TEST_EXPECT((int64_t)x == 42, "Should have passed the test case");
    TEST_EXPECT((int64_t)y == 20, "Should have passed the test case");
    TEST_EXPECT((int64_t)x != (int64_t)y, "Should have passed the test case");
    TEST_EXPECT((int64_t)y < (int64_t)x, "Should have passed the test case");
    TEST_EXPECT((int64_t)y <= (int64_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xexpect_run_of_int8_shortcut) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    EXPECT_ITS_EQUAL_I8((int8_t)x, 42);
    EXPECT_ITS_EQUAL_I8((int8_t)y, 20);
    EXPECT_NOT_EQUAL_I8((int8_t)x, (int8_t)y);
    EXPECT_ITS_LESS_THAN_I8((int8_t)y, (int8_t)x);
    EXPECT_ITS_LESS_OR_EQUAL_I8((int8_t)y, (int8_t)x);
} // end case

FOSSIL_TEST(xexpect_run_of_int16_shortcut) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    EXPECT_ITS_EQUAL_I16((int16_t)x, 42);
    EXPECT_ITS_EQUAL_I16((int16_t)y, 20);
    EXPECT_NOT_EQUAL_I16((int16_t)x, (int16_t)y);
    EXPECT_ITS_LESS_THAN_I16((int16_t)y, (int16_t)x);
    EXPECT_ITS_LESS_OR_EQUAL_I16((int16_t)y, (int16_t)x);
} // end case

FOSSIL_TEST(xexpect_run_of_int32_shortcut) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    EXPECT_ITS_EQUAL_I32((int32_t)x, 42);
    EXPECT_ITS_EQUAL_I32((int32_t)y, 20);
    EXPECT_NOT_EQUAL_I32((int32_t)x, (int32_t)y);
    EXPECT_ITS_LESS_THAN_I32((int32_t)y, (int32_t)x);
    EXPECT_ITS_LESS_OR_EQUAL_I32((int32_t)y, (int32_t)x);
} // end case

FOSSIL_TEST(xexpect_run_of_int64_shortcut) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    EXPECT_ITS_EQUAL_I64((int64_t)x, 42);
    EXPECT_ITS_EQUAL_I64((int64_t)y, 20);
    EXPECT_NOT_EQUAL_I64((int64_t)x, (int64_t)y);
    EXPECT_ITS_LESS_THAN_I64((int64_t)y, (int64_t)x);
    EXPECT_ITS_LESS_OR_EQUAL_I64((int64_t)y, (int64_t)x);
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
    ADD_TEST(xassert_run_of_int8_shortcut);
    ADD_TEST(xassert_run_of_int16_shortcut);
    ADD_TEST(xassert_run_of_int32_shortcut);
    ADD_TEST(xassert_run_of_int64_shortcut);
    ADD_TEST(xassume_run_of_int);
    ADD_TEST(xassume_run_of_int8);
    ADD_TEST(xassume_run_of_int16);
    ADD_TEST(xassume_run_of_int32);
    ADD_TEST(xassume_run_of_int64);
    ADD_TEST(xassume_run_of_int8_shortcut);
    ADD_TEST(xassume_run_of_int16_shortcut);
    ADD_TEST(xassume_run_of_int32_shortcut);
    ADD_TEST(xassume_run_of_int64_shortcut);
    ADD_TEST(xexpect_run_of_int);
    ADD_TEST(xexpect_run_of_int8);
    ADD_TEST(xexpect_run_of_int16);
    ADD_TEST(xexpect_run_of_int32);
    ADD_TEST(xexpect_run_of_int64);
    ADD_TEST(xexpect_run_of_int8_shortcut);
    ADD_TEST(xexpect_run_of_int16_shortcut);
    ADD_TEST(xexpect_run_of_int32_shortcut);
    ADD_TEST(xexpect_run_of_int64_shortcut);
} // end of group
