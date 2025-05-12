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

FOSSIL_TEST(c_assume_run_of_cstr) {
    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";

    // Test cases
    ASSUME_ITS_EQUAL_CSTR(str1, str2);
    ASSUME_NOT_EQUAL_CSTR(str1, str3);
    ASSUME_ITS_LENGTH_EQUAL_CSTR(str1, 5);
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
    FOSSIL_TEST_ADD(c_tdd_suite, c_assume_run_of_cstr);

    FOSSIL_TEST_REGISTER(c_tdd_suite);
} // end of group
