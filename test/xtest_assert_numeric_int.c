/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include <fossil/xassert/numeric.h> // library under test

#include <fossil/xtest.h>   // basic test tools

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

// I8 Assertions
XTEST(test_assert_i8_equal) {
    int8_t actual = 50;
    int8_t expected = 50;
    ASSERT_ITS_EQUAL_I8(actual, expected);
}

XTEST(test_assert_i8_less_than) {
    int8_t actual = 10;
    int8_t expected = 20;
    ASSERT_ITS_LESS_THAN_I8(actual, expected);
}

XTEST(test_assert_i8_more_than) {
    int8_t actual = 30;
    int8_t expected = 20;
    ASSERT_ITS_MORE_THAN_I8(actual, expected);
}

XTEST(test_assert_i8_less_or_equal) {
    int8_t actual = 10;
    int8_t expected = 20;
    ASSERT_ITS_LESS_OR_EQUAL_I8(actual, expected);
}

XTEST(test_assert_i8_more_or_equal) {
    int8_t actual = 30;
    int8_t expected = 20;
    ASSERT_ITS_MORE_OR_EQUAL_I8(actual, expected);
}

XTEST(test_assert_i8_not_equal) {
    int8_t actual = 50;
    int8_t expected = 20;
    ASSERT_NOT_EQUAL_I8(actual, expected);
}

XTEST(test_assert_i8_not_less_than) {
    int8_t actual = 30;
    int8_t expected = 20;
    ASSERT_NOT_LESS_THAN_I8(actual, expected);
}

XTEST(test_assert_i8_not_more_than) {
    int8_t actual = 10;
    int8_t expected = 20;
    ASSERT_NOT_MORE_THAN_I8(actual, expected);
}

XTEST(test_assert_i8_not_less_or_equal) {
    int8_t actual = 30;
    int8_t expected = 20;
    ASSERT_NOT_LESS_OR_EQUAL_I8(actual, expected);
}

XTEST(test_assert_i8_not_more_or_equal) {
    int8_t actual = 10;
    int8_t expected = 20;
    ASSERT_NOT_MORE_OR_EQUAL_I8(actual, expected);
}

// I16 Assertions - similar test cases as I8
XTEST(test_assert_i16_equal) {
    int16_t actual = 500;
    int16_t expected = 500;
    ASSERT_ITS_EQUAL_I16(actual, expected);
}

XTEST(test_assert_i16_less_than) {
    int16_t actual = 100;
    int16_t expected = 200;
    ASSERT_ITS_LESS_THAN_I16(actual, expected);
}

XTEST(test_assert_i16_more_than) {
    int16_t actual = 300;
    int16_t expected = 200;
    ASSERT_ITS_MORE_THAN_I16(actual, expected);
}

XTEST(test_assert_i16_less_or_equal) {
    int16_t actual = 100;
    int16_t expected = 200;
    ASSERT_ITS_LESS_OR_EQUAL_I16(actual, expected);
}

XTEST(test_assert_i16_more_or_equal) {
    int16_t actual = 300;
    int16_t expected = 200;
    ASSERT_ITS_MORE_OR_EQUAL_I16(actual, expected);
}

XTEST(test_assert_i16_not_equal) {
    int16_t actual = 500;
    int16_t expected = 200;
    ASSERT_NOT_EQUAL_I16(actual, expected);
}

XTEST(test_assert_i16_not_less_than) {
    int16_t actual = 300;
    int16_t expected = 200;
    ASSERT_NOT_LESS_THAN_I16(actual, expected);
}

XTEST(test_assert_i16_not_more_than) {
    int16_t actual = 100;
    int16_t expected = 200;
    ASSERT_NOT_MORE_THAN_I16(actual, expected);
}

XTEST(test_assert_i16_not_less_or_equal) {
    int16_t actual = 300;
    int16_t expected = 200;
    ASSERT_NOT_LESS_OR_EQUAL_I16(actual, expected);
}

XTEST(test_assert_i16_not_more_or_equal) {
    int16_t actual = 100;
    int16_t expected = 200;
    ASSERT_NOT_MORE_OR_EQUAL_I16(actual, expected);
}

// I32 Assertions - similar test cases as I8
XTEST(test_assert_i32_equal) {
    int32_t actual = 5000;
    int32_t expected = 5000;
    ASSERT_ITS_EQUAL_I32(actual, expected);
}

XTEST(test_assert_i32_less_than) {
    int32_t actual = 1000;
    int32_t expected = 2000;
    ASSERT_ITS_LESS_THAN_I32(actual, expected);
}

XTEST(test_assert_i32_more_than) {
    int32_t actual = 3000;
    int32_t expected = 2000;
    ASSERT_ITS_MORE_THAN_I32(actual, expected);
}

XTEST(test_assert_i32_less_or_equal) {
    int32_t actual = 1000;
    int32_t expected = 2000;
    ASSERT_ITS_LESS_OR_EQUAL_I32(actual, expected);
}

XTEST(test_assert_i32_more_or_equal) {
    int32_t actual = 3000;
    int32_t expected = 2000;
    ASSERT_ITS_MORE_OR_EQUAL_I32(actual, expected);
}

XTEST(test_assert_i32_not_equal) {
    int32_t actual = 5000;
    int32_t expected = 2000;
    ASSERT_NOT_EQUAL_I32(actual, expected);
}

XTEST(test_assert_i32_not_less_than) {
    int32_t actual = 3000;
    int32_t expected = 2000;
    ASSERT_NOT_LESS_THAN_I32(actual, expected);
}

XTEST(test_assert_i32_not_more_than) {
    int32_t actual = 1000;
    int32_t expected = 2000;
    ASSERT_NOT_MORE_THAN_I32(actual, expected);
}

XTEST(test_assert_i32_not_less_or_equal) {
    int32_t actual = 3000;
    int32_t expected = 2000;
    ASSERT_NOT_LESS_OR_EQUAL_I32(actual, expected);
}

XTEST(test_assert_i32_not_more_or_equal) {
    int32_t actual = 1000;
    int32_t expected = 2000;
    ASSERT_NOT_MORE_OR_EQUAL_I32(actual, expected);
}

// I64 Assertions - similar test cases as I8
XTEST(test_assert_i64_equal) {
    int64_t actual = 50000;
    int64_t expected = 50000;
    ASSERT_ITS_EQUAL_I64(actual, expected);
}

XTEST(test_assert_i64_less_than) {
    int64_t actual = 10000;
    int64_t expected = 20000;
    ASSERT_ITS_LESS_THAN_I64(actual, expected);
}

XTEST(test_assert_i64_more_than) {
    int64_t actual = 30000;
    int64_t expected = 20000;
    ASSERT_ITS_MORE_THAN_I64(actual, expected);
}

XTEST(test_assert_i64_less_or_equal) {
    int64_t actual = 10000;
    int64_t expected = 20000;
    ASSERT_ITS_LESS_OR_EQUAL_I64(actual, expected);
}

XTEST(test_assert_i64_more_or_equal) {
    int64_t actual = 30000;
    int64_t expected = 20000;
    ASSERT_ITS_MORE_OR_EQUAL_I64(actual, expected);
}

XTEST(test_assert_i64_not_equal) {
    int64_t actual = 50000;
    int64_t expected = 20000;
    ASSERT_NOT_EQUAL_I64(actual, expected);
}

XTEST(test_assert_i64_not_less_than) {
    int64_t actual = 30000;
    int64_t expected = 20000;
    ASSERT_NOT_LESS_THAN_I64(actual, expected);
}

XTEST(test_assert_i64_not_more_than) {
    int64_t actual = 10000;
    int64_t expected = 20000;
    ASSERT_NOT_MORE_THAN_I64(actual, expected);
}

XTEST(test_assert_i64_not_less_or_equal) {
    int64_t actual = 30000;
    int64_t expected = 20000;
    ASSERT_NOT_LESS_OR_EQUAL_I64(actual, expected);
}

XTEST(test_assert_i64_not_more_or_equal) {
    int64_t actual = 10000;
    int64_t expected = 20000;
    ASSERT_NOT_MORE_OR_EQUAL_I64(actual, expected);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(numeric_int_asserts_assert_group) {
    ADD_TEST(test_assert_i8_equal);
    ADD_TEST(test_assert_i8_less_than);
    ADD_TEST(test_assert_i8_more_than);
    ADD_TEST(test_assert_i8_less_or_equal);
    ADD_TEST(test_assert_i8_more_or_equal);
    ADD_TEST(test_assert_i8_not_equal);
    ADD_TEST(test_assert_i8_not_less_than);
    ADD_TEST(test_assert_i8_not_more_than);
    ADD_TEST(test_assert_i8_not_less_or_equal);
    ADD_TEST(test_assert_i8_not_more_or_equal);
    ADD_TEST(test_assert_i16_equal);
    ADD_TEST(test_assert_i16_less_than);
    ADD_TEST(test_assert_i16_more_than);
    ADD_TEST(test_assert_i16_less_or_equal);
    ADD_TEST(test_assert_i16_more_or_equal);
    ADD_TEST(test_assert_i16_not_equal);
    ADD_TEST(test_assert_i16_not_less_than);
    ADD_TEST(test_assert_i16_not_more_than);
    ADD_TEST(test_assert_i16_not_less_or_equal);
    ADD_TEST(test_assert_i16_not_more_or_equal);
    ADD_TEST(test_assert_i32_equal);
    ADD_TEST(test_assert_i32_less_than);
    ADD_TEST(test_assert_i32_more_than);
    ADD_TEST(test_assert_i32_less_or_equal);
    ADD_TEST(test_assert_i32_more_or_equal);
    ADD_TEST(test_assert_i32_not_equal);
    ADD_TEST(test_assert_i32_not_less_than);
    ADD_TEST(test_assert_i32_not_more_than);
    ADD_TEST(test_assert_i32_not_less_or_equal);
    ADD_TEST(test_assert_i32_not_more_or_equal);
    ADD_TEST(test_assert_i64_equal);
    ADD_TEST(test_assert_i64_less_than);
    ADD_TEST(test_assert_i64_more_than);
    ADD_TEST(test_assert_i64_less_or_equal);
    ADD_TEST(test_assert_i64_more_or_equal);
    ADD_TEST(test_assert_i64_not_equal);
    ADD_TEST(test_assert_i64_not_less_than);
    ADD_TEST(test_assert_i64_not_more_than);
    ADD_TEST(test_assert_i64_not_less_or_equal);
    ADD_TEST(test_assert_i64_not_more_or_equal);
} // end of fixture
