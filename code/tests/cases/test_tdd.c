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
#include <fossil/pizza/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_tdd_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_tdd_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_tdd_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_assume_run_of_int) {
    int x = 42;
    int y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME(x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_int8) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((int8_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int8_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int8_t)x != (int8_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int8_t)y < (int8_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int8_t)y <= (int8_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_int16) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((int16_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int16_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int16_t)x != (int16_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int16_t)y < (int16_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int16_t)y <= (int16_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_int32) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((int32_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int32_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int32_t)x != (int32_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int32_t)y < (int32_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int32_t)y <= (int32_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_int64) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((int64_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int64_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int64_t)x != (int64_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int64_t)y < (int64_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((int64_t)y <= (int64_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_int8_shortcut) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I8((int8_t)x, 42);
    ASSUME_ITS_EQUAL_I8((int8_t)y, 20);
    ASSUME_NOT_EQUAL_I8((int8_t)x, (int8_t)y);
    ASSUME_ITS_LESS_THAN_I8((int8_t)y, (int8_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I8((int8_t)y, (int8_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_int16_shortcut) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I16((int16_t)x, 42);
    ASSUME_ITS_EQUAL_I16((int16_t)y, 20);
    ASSUME_NOT_EQUAL_I16((int16_t)x, (int16_t)y);
    ASSUME_ITS_LESS_THAN_I16((int16_t)y, (int16_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I16((int16_t)y, (int16_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_int32_shortcut) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I32((int32_t)x, 42);
    ASSUME_ITS_EQUAL_I32((int32_t)y, 20);
    ASSUME_NOT_EQUAL_I32((int32_t)x, (int32_t)y);
    ASSUME_ITS_LESS_THAN_I32((int32_t)y, (int32_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I32((int32_t)y, (int32_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_int64_shortcut) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_I64((int64_t)x, 42);
    ASSUME_ITS_EQUAL_I64((int64_t)y, 20);
    ASSUME_NOT_EQUAL_I64((int64_t)x, (int64_t)y);
    ASSUME_ITS_LESS_THAN_I64((int64_t)y, (int64_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_I64((int64_t)y, (int64_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_uint) {
    unsigned int x = 42;
    unsigned int y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME(x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_uint8) {
    uint8_t x = 42;
    uint8_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((uint8_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint8_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint8_t)x != (uint8_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint8_t)y < (uint8_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint8_t)y <= (uint8_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_uint16) {
    uint16_t x = 42;
    uint16_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((uint16_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint16_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint16_t)x != (uint16_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint16_t)y < (uint16_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint16_t)y <= (uint16_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_uint32) {
    uint32_t x = 42;
    uint32_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((uint32_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint32_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint32_t)x != (uint32_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint32_t)y < (uint32_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint32_t)y <= (uint32_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_uint64) {
    uint64_t x = 42;
    uint64_t y = 20;

    // Test cases
    FOSSIL_TEST_ASSUME((uint64_t)x == 42, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint64_t)y == 20, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint64_t)x != (uint64_t)y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint64_t)y < (uint64_t)x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME((uint64_t)y <= (uint64_t)x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_uint8_shortcut) {
    uint8_t x = 42;
    uint8_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_U8((uint8_t)x, 42);
    ASSUME_ITS_EQUAL_U8((uint8_t)y, 20);
    ASSUME_NOT_EQUAL_U8((uint8_t)x, (uint8_t)y);
    ASSUME_ITS_LESS_THAN_U8((uint8_t)y, (uint8_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_U8((uint8_t)y, (uint8_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_uint16_shortcut) {
    uint16_t x = 42;
    uint16_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_U16((uint16_t)x, 42);
    ASSUME_ITS_EQUAL_U16((uint16_t)y, 20);
    ASSUME_NOT_EQUAL_U16((uint16_t)x, (uint16_t)y);
    ASSUME_ITS_LESS_THAN_U16((uint16_t)y, (uint16_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_U16((uint16_t)y, (uint16_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_uint32_shortcut) {
    uint32_t x = 42;
    uint32_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_U32((uint32_t)x, 42);
    ASSUME_ITS_EQUAL_U32((uint32_t)y, 20);
    ASSUME_NOT_EQUAL_U32((uint32_t)x, (uint32_t)y);
    ASSUME_ITS_LESS_THAN_U32((uint32_t)y, (uint32_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_U32((uint32_t)y, (uint32_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_uint64_shortcut) {
    uint64_t x = 42;
    uint64_t y = 20;

    // Test cases
    ASSUME_ITS_EQUAL_U64((uint64_t)x, 42);
    ASSUME_ITS_EQUAL_U64((uint64_t)y, 20);
    ASSUME_NOT_EQUAL_U64((uint64_t)x, (uint64_t)y);
    ASSUME_ITS_LESS_THAN_U64((uint64_t)y, (uint64_t)x);
    ASSUME_ITS_LESS_OR_EQUAL_U64((uint64_t)y, (uint64_t)x);
} // end case

FOSSIL_TEST(c_assume_run_of_hex) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    FOSSIL_TEST_ASSUME(x == 0x2A, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 0x14, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_hex8) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    FOSSIL_TEST_ASSUME(x == 0x2A, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 0x14, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_hex16) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    FOSSIL_TEST_ASSUME(x == 0x2A, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 0x14, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_hex32) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    FOSSIL_TEST_ASSUME(x == 0x2A, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 0x14, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_hex64) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    FOSSIL_TEST_ASSUME(x == 0x2A, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y == 0x14, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(x != y, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y < x, "Should have passed the test case");
    FOSSIL_TEST_ASSUME(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(c_assume_run_of_hex8_shortcut) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    ASSUME_ITS_EQUAL_H8((int)x, 0x2A);
    ASSUME_ITS_EQUAL_H8((int)y, 0x14);
    ASSUME_NOT_EQUAL_H8((int)x, (int)y);
    ASSUME_ITS_LESS_THAN_H8((int)y, (int)x);
    ASSUME_ITS_LESS_OR_EQUAL_H8((int)y, (int)x);
} // end case

FOSSIL_TEST(c_assume_run_of_hex16_shortcut) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    ASSUME_ITS_EQUAL_H16((int)x, 0x2A);
    ASSUME_ITS_EQUAL_H16((int)y, 0x14);
    ASSUME_NOT_EQUAL_H16((int)x, (int)y);
    ASSUME_ITS_LESS_THAN_H16((int)y, (int)x);
    ASSUME_ITS_LESS_OR_EQUAL_H16((int)y, (int)x);
} // end case

FOSSIL_TEST(c_assume_run_of_hex32_shortcut) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    ASSUME_ITS_EQUAL_H32((int)x, 0x2A);
    ASSUME_ITS_EQUAL_H32((int)y, 0x14);
    ASSUME_NOT_EQUAL_H32((int)x, (int)y);
    ASSUME_ITS_LESS_THAN_H32((int)y, (int)x);
    ASSUME_ITS_LESS_OR_EQUAL_H32((int)y, (int)x);
} // end case

FOSSIL_TEST(c_assume_run_of_hex64_shortcut) {
    int x = 0x2A; // Hex for 42
    int y = 0x14; // Hex for 20

    // Test cases
    ASSUME_ITS_EQUAL_H64((int)x, 0x2A);
    ASSUME_ITS_EQUAL_H64((int)y, 0x14);
    ASSUME_NOT_EQUAL_H64((int)x, (int)y);
    ASSUME_ITS_LESS_THAN_H64((int)y, (int)x);
    ASSUME_ITS_LESS_OR_EQUAL_H64((int)y, (int)x);
} // end case

FOSSIL_TEST(c_assume_run_of_octal8_shortcut) {
    int8_t x = 052; // Octal for 42
    int8_t y = 024; // Octal for 20

    // Test cases
    ASSUME_ITS_EQUAL_O8(x, 052);
    ASSUME_ITS_EQUAL_O8(y, 024);
    ASSUME_NOT_EQUAL_O8(x, y);
    ASSUME_ITS_LESS_THAN_O8(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_O8(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_octal16_shortcut) {
    int16_t x = 052; // Octal for 42
    int16_t y = 024; // Octal for 20

    // Test cases
    ASSUME_ITS_EQUAL_O16(x, 052);
    ASSUME_ITS_EQUAL_O16(y, 024);
    ASSUME_NOT_EQUAL_O16(x, y);
    ASSUME_ITS_LESS_THAN_O16(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_O16(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_octal32_shortcut) {
    int32_t x = 052; // Octal for 42
    int32_t y = 024; // Octal for 20

    // Test cases
    ASSUME_ITS_EQUAL_O32(x, 052);
    ASSUME_ITS_EQUAL_O32(y, 024);
    ASSUME_NOT_EQUAL_O32(x, y);
    ASSUME_ITS_LESS_THAN_O32(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_O32(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_octal64_shortcut) {
    int64_t x = 052; // Octal for 42
    int64_t y = 024; // Octal for 20

    // Test cases
    ASSUME_ITS_EQUAL_O64(x, 052);
    ASSUME_ITS_EQUAL_O64(y, 024);
    ASSUME_NOT_EQUAL_O64(x, y);
    ASSUME_ITS_LESS_THAN_O64(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_O64(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_float32) {
    float x = 42.0f;
    float y = 20.0f;

    // Test cases
    ASSUME_ITS_EQUAL_F32(x, 42.0f, 0.001f);
    ASSUME_ITS_EQUAL_F32(y, 20.0f, 0.001f);
    ASSUME_NOT_EQUAL_F32(x, y, 0.001f);
    ASSUME_ITS_LESS_THAN_F32(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_F32(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_float64) {
    double x = 42.0;
    double y = 20.0;

    // Test cases
    ASSUME_ITS_EQUAL_F64(x, 42.0, 0.001);
    ASSUME_ITS_EQUAL_F64(y, 20.0, 0.001);
    ASSUME_NOT_EQUAL_F64(x, y, 0.001);
    ASSUME_ITS_LESS_THAN_F64(y, x);
    ASSUME_ITS_LESS_OR_EQUAL_F64(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_true) {
    bool x = true;
    bool y = false;

    // Test cases
    ASSUME_ITS_TRUE(x);
    ASSUME_ITS_FALSE(y);
    ASSUME_NOT_TRUE(y);
    ASSUME_NOT_FALSE(x);
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_false) {
    bool x = false;
    bool y = true;

    // Test cases
    ASSUME_ITS_FALSE(x);
    ASSUME_ITS_TRUE(y);
    ASSUME_NOT_FALSE(y);
    ASSUME_NOT_TRUE(x);
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_expression) {
    int a = 5;
    int b = 10;

    // Test cases
    ASSUME_ITS_TRUE(a < b);
    ASSUME_ITS_FALSE(a > b);
    ASSUME_NOT_TRUE(a > b);
    ASSUME_NOT_FALSE(a < b);
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_expression_negation) {
    int a = 5;
    int b = 10;

    // Test cases
    ASSUME_ITS_TRUE(!(a > b));
    ASSUME_ITS_FALSE(!(a < b));
    ASSUME_NOT_TRUE(!(a < b));
    ASSUME_NOT_FALSE(!(a > b));
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_complex_expression) {
    int a = 5;
    int b = 10;
    int c = 15;

    // Test cases
    ASSUME_ITS_TRUE((a < b) && (b < c));
    ASSUME_ITS_FALSE((a > b) || (b > c));
    ASSUME_NOT_TRUE((a > b) || (b > c));
    ASSUME_NOT_FALSE((a < b) && (b < c));
} // end case

FOSSIL_TEST(c_assume_run_of_boolean_complex_expression_negation) {
    int a = 5;
    int b = 10;
    int c = 15;

    // Test cases
    ASSUME_ITS_TRUE(!((a > b) || (b > c)));
    ASSUME_ITS_FALSE(!((a < b) && (b < c)));
    ASSUME_NOT_TRUE(!((a < b) && (b < c)));
    ASSUME_NOT_FALSE(!((a > b) || (b > c)));
} // end case

FOSSIL_TEST(c_assume_run_of_null_pointer) {
    void *ptr = NULL;

    // Test cases
    ASSUME_ITS_CNULL(ptr);
    ASSUME_NOT_CNULL((void *)0x1); // Assuming a non-null pointer
} // end case

FOSSIL_TEST(c_assume_run_of_pointer_equality) {
    int a = 42;
    int *ptr1 = &a;
    int *ptr2 = &a;
    int *ptr3 = NULL;

    // Test cases
    ASSUME_ITS_EQUAL_PTR(ptr1, ptr2);
    ASSUME_NOT_EQUAL_PTR(ptr1, ptr3);
} // end case

FOSSIL_TEST(c_assume_run_of_size_equality) {
    size_t size1 = 42;
    size_t size2 = 42;
    size_t size3 = 20;

    // Test cases
    ASSUME_ITS_EQUAL_SIZE(size1, size2);
    ASSUME_NOT_EQUAL_SIZE(size1, size3);
} // end case

FOSSIL_TEST(c_assume_run_of_size_comparison) {
    size_t size1 = 42;
    size_t size2 = 20;

    // Test cases
    ASSUME_ITS_LESS_THAN_SIZE(size2, size1);
    ASSUME_ITS_MORE_THAN_SIZE(size1, size2);
    ASSUME_ITS_LESS_OR_EQUAL_SIZE(size2, size1);
    ASSUME_ITS_LESS_OR_EQUAL_SIZE(size1, size1);
    ASSUME_ITS_MORE_OR_EQUAL_SIZE(size1, size2);
    ASSUME_ITS_MORE_OR_EQUAL_SIZE(size1, size1);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range) {
    int x = 42;
    int y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_u8) {
    uint8_t x = 42;
    uint8_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_U8(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_U8(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_u16) {
    uint16_t x = 42;
    uint16_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_U16(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_U16(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_u32) {
    uint32_t x = 42;
    uint32_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_U32(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_U32(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_u64) {
    uint64_t x = 42;
    uint64_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_U64(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_U64(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_i8) {
    int8_t x = 42;
    int8_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_I8(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_I8(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_i16) {
    int16_t x = 42;
    int16_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_I16(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_I16(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_i32) {
    int32_t x = 42;
    int32_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_I32(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_I32(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_i64) {
    int64_t x = 42;
    int64_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_I64(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_I64(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_f32) {
    float x = 42.0f;
    float y = 20.0f;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_F32(x, 40.0f, 45.0f);
    ASSUME_NOT_WITHIN_RANGE_F32(y, 21.0f, 30.0f);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_f64) {
    double x = 42.0;
    double y = 20.0;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_F64(x, 40.0, 45.0);
    ASSUME_NOT_WITHIN_RANGE_F64(y, 21.0, 30.0);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_bchar) {
    uint8_t x = 42;
    uint8_t y = 20;

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_BCHAR(x, 40, 45);
    ASSUME_NOT_WITHIN_RANGE_BCHAR(y, 21, 30);
} // end case

FOSSIL_TEST(c_assume_run_of_within_range_cchar) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_ITS_WITHIN_RANGE_CCHAR(x, 'A', 'Z');
    ASSUME_NOT_WITHIN_RANGE_CCHAR(y, 'C', 'Z');
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_equality) {
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";

    // Test cases
    ASSUME_ITS_EQUAL_CSTR(str1, str2);
    ASSUME_NOT_EQUAL_CSTR(str1, str3);
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_length) {
    const char *str1 = "Hello";

    // Test cases
    ASSUME_ITS_LENGTH_EQUAL_CSTR(str1, 5);
    ASSUME_NOT_LENGTH_EQUAL_CSTR(str1, 10);
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_prefix) {
    const char *str4 = "Hello, World!";
    const char *prefix = "Hello";
    const char *str3 = "World";

    // Test cases
    ASSUME_ITS_CSTR_STARTS_WITH(str4, prefix);
    ASSUME_NOT_CSTR_STARTS_WITH(str3, prefix);
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_suffix) {
    const char *str4 = "Hello, World!";
    const char *suffix = "World!";
    const char *str1 = "Hello";

    // Test cases
    ASSUME_ITS_CSTR_ENDS_WITH(str4, suffix);
    ASSUME_NOT_CSTR_ENDS_WITH(str1, suffix);
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_contains) {
    const char *str4 = "Hello, World!";
    const char *substr = "lo";
    const char *str3 = "World";

    // Test cases
    ASSUME_ITS_CSTR_CONTAINS(str4, substr);
    ASSUME_NOT_CSTR_CONTAINS(str3, substr);
} // end case

FOSSIL_TEST(c_assume_run_of_cstr_count) {
    const char *str4 = "Hello, World!";

    // Test cases
    ASSUME_ITS_CSTR_COUNT(str4, "o", 2);
    ASSUME_NOT_CSTR_COUNT(str4, "o", 3);
} // end case


FOSSIL_TEST(c_assume_run_of_zero_memory) {
    char buffer[10] = {0};

    // Test cases
    ASSUME_ITS_ZERO_MEMORY(buffer, sizeof(buffer));
} // end case

FOSSIL_TEST(c_assume_run_of_memory_equality) {
    char buffer1[10] = {0};
    char buffer2[10] = {0};
    char buffer3[10] = {1};

    // Test cases
    ASSUME_ITS_EQUAL_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_NOT_EQUAL_MEMORY(buffer1, buffer3, sizeof(buffer1));
} // end case

FOSSIL_TEST(c_assume_run_of_memory_comparison) {
    char buffer1[10] = {1, 2, 3};
    char buffer2[10] = {1, 2, 4};
    char buffer3[10] = {1, 2, 3};

    // Test cases
    ASSUME_ITS_LESS_THAN_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_ITS_MORE_THAN_MEMORY(buffer2, buffer1, sizeof(buffer1));
    ASSUME_ITS_MORE_OR_EQUAL_MEMORY(buffer2, buffer1, sizeof(buffer1));
    ASSUME_ITS_LESS_OR_EQUAL_MEMORY(buffer1, buffer3, sizeof(buffer1));
} // end case

FOSSIL_TEST(c_assume_run_of_memory_validity) {
    char buffer[10];
    char *valid_ptr = buffer;
    char *invalid_ptr = NULL;

    // Test cases
    ASSUME_ITS_VALID_MEMORY(valid_ptr);
    ASSUME_NOT_VALID_MEMORY(invalid_ptr);
} // end case

FOSSIL_TEST(c_assume_run_of_memory_range) {
    char buffer1[10] = {1, 2, 3};
    char buffer2[10] = {1, 2, 4};

    // Test cases
    ASSUME_ITS_MORE_THAN_MEMORY(buffer2, buffer1, sizeof(buffer1));
    ASSUME_NOT_MORE_THAN_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_ITS_LESS_THAN_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_NOT_LESS_THAN_MEMORY(buffer2, buffer1, sizeof(buffer1));
    ASSUME_ITS_MORE_OR_EQUAL_MEMORY(buffer2, buffer1, sizeof(buffer1));
    ASSUME_NOT_MORE_OR_EQUAL_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_ITS_LESS_OR_EQUAL_MEMORY(buffer1, buffer2, sizeof(buffer1));
    ASSUME_NOT_LESS_OR_EQUAL_MEMORY(buffer2, buffer1, sizeof(buffer1));
} // end case

FOSSIL_TEST(c_assume_run_of_pointer_nullability) {
    void *ptr1 = NULL;
    void *ptr2 = (void *)0x1;

    // Test cases
    ASSUME_ITS_CNULLABLE(ptr1);
    ASSUME_NOT_CNULLABLE(ptr2);
    ASSUME_ITS_CNONNULL(ptr2);
    ASSUME_NOT_CNONNULL(ptr1);
} // end case

FOSSIL_TEST(c_assume_run_of_likely_conditions) {
    int a = 5;
    int b = 10;

    // Test cases
    ASSUME_ITS_LIKELY(a < b);
    ASSUME_NOT_LIKELY(a > b);
} // end case

FOSSIL_TEST(c_assume_run_of_unlikely_conditions) {
    int a = 5;
    int b = 10;

    // Test cases
    ASSUME_ITS_UNLIKELY(a < b);
    ASSUME_NOT_UNLIKELY(a > b);
} // end case

FOSSIL_TEST(c_assume_run_of_pointer_nullability_complex) {
    int a = 42;
    int *ptr1 = &a;
    int *ptr2 = NULL;

    // Test cases
    ASSUME_ITS_CNONNULL(ptr1);
    ASSUME_NOT_CNULLABLE(ptr1);
    ASSUME_ITS_CNULLABLE(ptr2);
    ASSUME_NOT_CNONNULL(ptr2);
} // end case

FOSSIL_TEST(c_assume_run_of_likely_unlikely_combination) {
    int a = 5;
    int b = 10;

    // Test cases
    ASSUME_ITS_LIKELY(a < b);
    ASSUME_ITS_UNLIKELY(a < b);
    ASSUME_NOT_LIKELY(a > b);
    ASSUME_NOT_UNLIKELY(a > b);
} // end case


FOSSIL_TEST(c_assume_run_of_char_equality) {
    char x = 'A';
    char z = 'A';

    // Test cases
    ASSUME_ITS_EQUAL_CHAR(x, z);
} // end case

FOSSIL_TEST(c_assume_run_of_char_inequality) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_EQUAL_CHAR(x, y);
} // end case

FOSSIL_TEST(c_assume_run_of_char_less_than) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_ITS_LESS_THAN_CHAR(x, y);
} // end case

FOSSIL_TEST(c_assume_run_of_char_more_than) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_ITS_MORE_THAN_CHAR(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_char_less_or_equal) {
    char x = 'A';
    char z = 'A';

    // Test cases
    ASSUME_ITS_LESS_OR_EQUAL_CHAR(x, z);
} // end case

FOSSIL_TEST(c_assume_run_of_char_more_or_equal) {
    char x = 'A';
    char z = 'A';

    // Test cases
    ASSUME_ITS_MORE_OR_EQUAL_CHAR(x, z);
} // end case

FOSSIL_TEST(c_assume_run_of_char_not_less_than) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_LESS_THAN_CHAR(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_char_not_more_than) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_MORE_THAN_CHAR(x, y);
} // end case

FOSSIL_TEST(c_assume_run_of_char_not_less_or_equal) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_LESS_OR_EQUAL_CHAR(y, x);
} // end case

FOSSIL_TEST(c_assume_run_of_char_not_more_or_equal) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_MORE_OR_EQUAL_CHAR(x, y);
} // end case

FOSSIL_TEST(c_assume_run_of_char_not_equal) {
    char x = 'A';
    char y = 'B';

    // Test cases
    ASSUME_NOT_EQUAL_CHAR(x, y);
} // end case


// Test for rot-brain words (should be detected)
FOSSIL_TEST(c_assume_run_of_its_soap_rot_brain) {
    const char *rot_brain_words[] = {
        "u", "gonna", "ppl", "funny", "lol", "idk", "wanna", "rizz", "skibidi", "yeet", "sus", "vibe", "lit", "no cap", "bet", "fam", "bruh", "flex", "ghost", "goat", "gucci", "hype", "janky", "lowkey", "mood", "salty", "shade", "slay", "snatched", "stan", "tea", "thirsty", "woke", "yolo", "zaddy", "drip", "fire", "omg", "brb", "imo", "lmao", "nvm", "tbh", "tldr", "ttyl", "wyd", "wtf", "rot-brain", "rot brain", "rotbrain", "smh", "fomo", "bff", "irl", "afaik", "btw", "omw", "ikr", "tgif", "np", "rofl", "lmk", "dm", "rn", "yw", "af", "ftw", "gg", "pov", "omfg", "tl;dr", "fwiw", "bday", "gr8", "hmu", "jk", "k", "l8r", "msg", "pls", "plz", "thx", "tho", "w/", "w/o", "xoxo", "y", "b/c", "cuz", "coz", "dunno", "g2g", "hbu", "idc", "ily", "l8", "n/a", "nvm", "omw", "ppl", "qt", "sup", "tba", "tbc", "w/e", "wth"
    };
    for (size_t i = 0; i < sizeof(rot_brain_words)/sizeof(rot_brain_words[0]); ++i) {
        char buf[64];
        snprintf(buf, sizeof(buf), "This is %s.", rot_brain_words[i]);
        ASSUME_ITS_SOAP_ROT_BRAIN(buf);
    }
} // end case

// Test for non-rot-brain (should NOT be detected)
FOSSIL_TEST(c_assume_run_of_not_soap_rot_brain) {
    const char *normal_sentences[] = {
        "This is a normal sentence.",
        "The quick brown fox jumps over the lazy dog.",
        "Software engineering is fun.",
        "I like pizza.",
        "Let's write some tests."
    };
    for (size_t i = 0; i < sizeof(normal_sentences)/sizeof(normal_sentences[0]); ++i) {
        ASSUME_NOT_SOAP_ROT_BRAIN(normal_sentences[i]);
    }
} // end case

// Test for formal phrases
FOSSIL_TEST(c_assume_run_of_soap_formal) {
    const char *formal_phrases[] = {
        "Dear Sir or Madam", "To whom it may concern", "Yours sincerely", "Yours faithfully", "Best regards", "Respectfully",
        "I would like to", "I am writing to", "Please find attached", "Thank you for your consideration", "I look forward to your response"
    };
    for (size_t i = 0; i < sizeof(formal_phrases)/sizeof(formal_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_FORMAL(formal_phrases[i]);
    }
} // end case

// Test for sarcasm phrases
FOSSIL_TEST(c_assume_run_of_soap_sarcasm) {
    const char *sarcasm_phrases[] = {
        "Oh, great", "Yeah, right", "Nice job", "Well done", "Good luck with that", "Sure, why not", "Fantastic", "Brilliant", "Wonderful", "Perfect"
    };
    for (size_t i = 0; i < sizeof(sarcasm_phrases)/sizeof(sarcasm_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_SARCASM(sarcasm_phrases[i]);
    }
} // end case

// Test for ragebait
FOSSIL_TEST(c_assume_run_of_soap_ragebait) {
    const char *ragebait_phrases[] = {
        "You won't believe what happened next!", "outrageous", "infuriating", "makes me angry", "how dare they", "ridiculous"
    };
    for (size_t i = 0; i < sizeof(ragebait_phrases)/sizeof(ragebait_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_RAGEBAIT(ragebait_phrases[i]);
    }
    ASSUME_NOT_SOAP_RAGEBAIT("This is a calm and informative statement.");
} // end case

// Test for clickbait
FOSSIL_TEST(c_assume_run_of_soap_clickbait) {
    const char *clickbait_phrases[] = {
        "10 shocking secrets they don't want you to know!", "top 10", "must see", "life changing", "secret revealed"
    };
    for (size_t i = 0; i < sizeof(clickbait_phrases)/sizeof(clickbait_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_CLICKBAIT(clickbait_phrases[i]);
    }
    ASSUME_NOT_SOAP_CLICKBAIT("This article provides a summary of the topic.");
} // end case

// Test for spam
FOSSIL_TEST(c_assume_run_of_soap_spam) {
    const char *spam_phrases[] = {
        "Congratulations! You've won a free iPhone. Click here!", "free money", "work from home", "act now", "earn cash fast"
    };
    for (size_t i = 0; i < sizeof(spam_phrases)/sizeof(spam_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_SPAM(spam_phrases[i]);
    }
    ASSUME_NOT_SOAP_SPAM("Thank you for your feedback.");
} // end case

// Test for woke
FOSSIL_TEST(c_assume_run_of_soap_woke) {
    const char *woke_phrases[] = {
        "We must challenge systemic injustice and promote equity.", "safe space", "microaggression", "check your privilege", "diversity and inclusion"
    };
    for (size_t i = 0; i < sizeof(woke_phrases)/sizeof(woke_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_WOKE(woke_phrases[i]);
    }
    ASSUME_NOT_SOAP_WOKE("This is a technical documentation.");
} // end case

// Test for bot
FOSSIL_TEST(c_assume_run_of_soap_bot) {
    const char *bot_phrases[] = {
        "Hello, I am an automated assistant. How can I help you?", "ai generated", "auto reply", "automated message", "bot detected"
    };
    for (size_t i = 0; i < sizeof(bot_phrases)/sizeof(bot_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_BOT(bot_phrases[i]);
    }
    ASSUME_NOT_SOAP_BOT("Hi, this is John from support.");
} // end case

// Test for snowflake
FOSSIL_TEST(c_assume_run_of_soap_snowflake) {
    const char *snowflake_phrases[] = {
        "I'm offended by your words and need a safe space.", "snowflake", "triggered", "fragile ego", "offended easily"
    };
    for (size_t i = 0; i < sizeof(snowflake_phrases)/sizeof(snowflake_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_SNOWFLAKE(snowflake_phrases[i]);
    }
    ASSUME_NOT_SOAP_SNOWFLAKE("Let's discuss the facts objectively.");
} // end case

// Test for offensive
FOSSIL_TEST(c_assume_run_of_soap_offensive) {
    const char *offensive_phrases[] = {
        "You are so stupid!", "idiot", "moron", "loser", "jerk", "trash"
    };
    for (size_t i = 0; i < sizeof(offensive_phrases)/sizeof(offensive_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_OFFENSIVE(offensive_phrases[i]);
    }
    ASSUME_NOT_SOAP_OFFENSIVE("That was an interesting point.");
} // end case

// Test for neutral
FOSSIL_TEST(c_assume_run_of_soap_neutral) {
    const char *neutral_phrases[] = {
        "The sky is blue.", "as expected", "no problem", "all good", "fine", "okay"
    };
    for (size_t i = 0; i < sizeof(neutral_phrases)/sizeof(neutral_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_NEUTRAL(neutral_phrases[i]);
    }
    ASSUME_NOT_SOAP_NEUTRAL("This is the worst product ever!");
} // end case

// Test for hype
FOSSIL_TEST(c_assume_run_of_soap_hype) {
    const char *hype_phrases[] = {
        "This is the most amazing thing ever!", "game-changing", "revolutionary", "cutting-edge", "disruptive"
    };
    for (size_t i = 0; i < sizeof(hype_phrases)/sizeof(hype_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_HYPE(hype_phrases[i]);
    }
    ASSUME_NOT_SOAP_HYPE("The results were as expected.");
} // end case

// Test for quality
FOSSIL_TEST(c_assume_run_of_soap_quality) {
    const char *quality_phrases[] = {
        "This product is built with premium materials.", "premium", "best-in-class", "outstanding", "top-tier"
    };
    for (size_t i = 0; i < sizeof(quality_phrases)/sizeof(quality_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_QUALITY(quality_phrases[i]);
    }
    ASSUME_NOT_SOAP_QUALITY("The item is available in the store.");
} // end case

// Test for political
FOSSIL_TEST(c_assume_run_of_soap_political) {
    const char *political_phrases[] = {
        "The government should lower taxes.", "left-wing", "right-wing", "liberal agenda", "conservative values"
    };
    for (size_t i = 0; i < sizeof(political_phrases)/sizeof(political_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_POLITICAL(political_phrases[i]);
    }
    ASSUME_NOT_SOAP_POLITICAL("This is a recipe for apple pie.");
} // end case

// Test for conspiracy
FOSSIL_TEST(c_assume_run_of_soap_conspiracy) {
    const char *conspiracy_phrases[] = {
        "The moon landing was faked by the government.", "hidden truth", "cover up", "shadow government", "mind control"
    };
    for (size_t i = 0; i < sizeof(conspiracy_phrases)/sizeof(conspiracy_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_CONSPIRACY(conspiracy_phrases[i]);
    }
    ASSUME_NOT_SOAP_CONSPIRACY("The earth revolves around the sun.");
} // end case

// Test for marketing
FOSSIL_TEST(c_assume_run_of_soap_marketing) {
    const char *marketing_phrases[] = {
        "Unlock your potential with our revolutionary solution!", "limited time offer", "act now", "don’t miss out", "guaranteed results"
    };
    for (size_t i = 0; i < sizeof(marketing_phrases)/sizeof(marketing_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_MARKETING(marketing_phrases[i]);
    }
    ASSUME_NOT_SOAP_MARKETING("The software is open source and free to use.");
} // end case

// Test for technobabble
FOSSIL_TEST(c_assume_run_of_soap_technobabble) {
    const char *technobabble_phrases[] = {
        "The quantum flux capacitor enables hyperdimensional throughput.", "synergy", "blockchain-enabled", "AI-powered", "machine learning solution"
    };
    for (size_t i = 0; i < sizeof(technobabble_phrases)/sizeof(technobabble_phrases[0]); ++i) {
        ASSUME_ITS_SOAP_TECHNOBABBLE(technobabble_phrases[i]);
    }
    ASSUME_NOT_SOAP_TECHNOBABBLE("The CPU executes instructions sequentially.");
} // end case

// Test for formal tone detection (tone argument)
FOSSIL_TEST(c_assume_run_of_its_soap_tone_detected) {
    const char *text = "Respectfully, I am writing to inform you.";
    const char *expected_tone = "formal";
    ASSUME_ITS_SOAP_TONE_DETECTED(text, expected_tone);
} // end case

FOSSIL_TEST(c_assume_run_of_not_soap_tone_detected) {
    const char *text = "Hey, what's up?";
    const char *expected_tone = "formal";
    ASSUME_NOT_SOAP_TONE_DETECTED(text, expected_tone);
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_tdd_test_cases) {
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int8);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int16);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int8_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int16_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int32_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_int64_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint8);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint16);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint8_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint16_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint32_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_uint64_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex8);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex16);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex8_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex16_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex32_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_hex64_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_octal8_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_octal16_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_octal32_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_octal64_shortcut);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_float32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_float64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_true);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_false);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_expression);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_expression_negation);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_complex_expression);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_boolean_complex_expression_negation);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_null_pointer);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_pointer_equality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_size_equality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_size_comparison);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_u8);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_u16);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_u32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_u64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_i8);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_i16);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_i32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_i64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_f32);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_f64);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_bchar);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_within_range_cchar);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_equality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_length);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_prefix);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_suffix);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_contains);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr_count);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_zero_memory);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_memory_equality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_memory_comparison);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_memory_validity);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_memory_range);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_pointer_nullability);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_likely_conditions);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_unlikely_conditions);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_pointer_nullability_complex);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_likely_unlikely_combination);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_equality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_inequality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_less_than);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_more_than);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_less_or_equal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_more_or_equal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_not_less_than);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_not_more_than);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_not_less_or_equal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_not_more_or_equal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_char_not_equal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_not_soap_rot_brain);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_its_soap_rot_brain);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_its_soap_tone_detected);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_not_soap_tone_detected);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_ragebait);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_clickbait);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_spam);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_woke);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_bot);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_sarcasm);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_formal);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_snowflake);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_offensive);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_neutral);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_hype);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_quality);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_political);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_conspiracy);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_marketing);
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_soap_technobabble);

    FOSSIL_TEST_REGISTER(c_tdd_suite);
} // end of group
