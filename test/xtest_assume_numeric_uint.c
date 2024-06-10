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
#include <fossil/xassume/numeric.h> // library under test

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

// U8 Assertions
XTEST(test_assume_u8_equal) {
    uint8_t actual = 50;
    uint8_t expected = 50;
    ASSUME_ITS_EQUAL_U8(actual, expected);
}

XTEST(test_assume_u8_less_than) {
    uint8_t actual = 10;
    uint8_t expected = 20;
    ASSUME_ITS_LESS_THAN_U8(actual, expected);
}

XTEST(test_assume_u8_more_than) {
    uint8_t actual = 30;
    uint8_t expected = 20;
    ASSUME_ITS_MORE_THAN_U8(actual, expected);
}

XTEST(test_assume_u8_less_or_equal) {
    uint8_t actual = 10;
    uint8_t expected = 20;
    ASSUME_ITS_LESS_OR_EQUAL_U8(actual, expected);
}

XTEST(test_assume_u8_more_or_equal) {
    uint8_t actual = 30;
    uint8_t expected = 20;
    ASSUME_ITS_MORE_OR_EQUAL_U8(actual, expected);
}

XTEST(test_assume_u8_not_equal) {
    uint8_t actual = 50;
    uint8_t expected = 20;
    ASSUME_NOT_EQUAL_U8(actual, expected);
}

XTEST(test_assume_u8_not_less_than) {
    uint8_t actual = 30;
    uint8_t expected = 20;
    ASSUME_NOT_LESS_THAN_U8(actual, expected);
}

XTEST(test_assume_u8_not_more_than) {
    uint8_t actual = 10;
    uint8_t expected = 20;
    ASSUME_NOT_MORE_THAN_U8(actual, expected);
}

XTEST(test_assume_u8_not_less_or_equal) {
    uint8_t actual = 30;
    uint8_t expected = 20;
    ASSUME_NOT_LESS_OR_EQUAL_U8(actual, expected);
}

XTEST(test_assume_u8_not_more_or_equal) {
    uint8_t actual = 10;
    uint8_t expected = 20;
    ASSUME_NOT_MORE_OR_EQUAL_U8(actual, expected);
}

// U16 Assertions - similar test cases as U8
XTEST(test_assume_u16_equal) {
    uint16_t actual = 500;
    uint16_t expected = 500;
    ASSUME_ITS_EQUAL_U16(actual, expected);
}

XTEST(test_assume_u16_less_than) {
    uint16_t actual = 100;
    uint16_t expected = 200;
    ASSUME_ITS_LESS_THAN_U16(actual, expected);
}

XTEST(test_assume_u16_more_than) {
    uint16_t actual = 300;
    uint16_t expected = 200;
    ASSUME_ITS_MORE_THAN_U16(actual, expected);
}

XTEST(test_assume_u16_less_or_equal) {
    uint16_t actual = 100;
    uint16_t expected = 200;
    ASSUME_ITS_LESS_OR_EQUAL_U16(actual, expected);
}

XTEST(test_assume_u16_more_or_equal) {
    uint16_t actual = 300;
    uint16_t expected = 200;
    ASSUME_ITS_MORE_OR_EQUAL_U16(actual, expected);
}

XTEST(test_assume_u16_not_equal) {
    uint16_t actual = 500;
    uint16_t expected = 200;
    ASSUME_NOT_EQUAL_U16(actual, expected);
}

XTEST(test_assume_u16_not_less_than) {
    uint16_t actual = 300;
    uint16_t expected = 200;
    ASSUME_NOT_LESS_THAN_U16(actual, expected);
}

XTEST(test_assume_u16_not_more_than) {
    uint16_t actual = 100;
    uint16_t expected = 200;
    ASSUME_NOT_MORE_THAN_U16(actual, expected);
}

XTEST(test_assume_u16_not_less_or_equal) {
    uint16_t actual = 300;
    uint16_t expected = 200;
    ASSUME_NOT_LESS_OR_EQUAL_U16(actual, expected);
}

XTEST(test_assume_u16_not_more_or_equal) {
    uint16_t actual = 100;
    uint16_t expected = 200;
    ASSUME_NOT_MORE_OR_EQUAL_U16(actual, expected);
}

// U32 Assertions - similar test cases as U8
XTEST(test_assume_u32_equal) {
    uint32_t actual = 5000;
    uint32_t expected = 5000;
    ASSUME_ITS_EQUAL_U32(actual, expected);
}

XTEST(test_assume_u32_less_than) {
    uint32_t actual = 1000;
    uint32_t expected = 2000;
    ASSUME_ITS_LESS_THAN_U32(actual, expected);
}

XTEST(test_assume_u32_more_than) {
    uint32_t actual = 3000;
    uint32_t expected = 2000;
    ASSUME_ITS_MORE_THAN_U32(actual, expected);
}

XTEST(test_assume_u32_less_or_equal) {
    uint32_t actual = 1000;
    uint32_t expected = 2000;
    ASSUME_ITS_LESS_OR_EQUAL_U32(actual, expected);
}

XTEST(test_assume_u32_more_or_equal) {
    uint32_t actual = 3000;
    uint32_t expected = 2000;
    ASSUME_ITS_MORE_OR_EQUAL_U32(actual, expected);
}

XTEST(test_assume_u32_not_equal) {
    uint32_t actual = 5000;
    uint32_t expected = 2000;
    ASSUME_NOT_EQUAL_U32(actual, expected);
}

XTEST(test_assume_u32_not_less_than) {
    uint32_t actual = 3000;
    uint32_t expected = 2000;
    ASSUME_NOT_LESS_THAN_U32(actual, expected);
}

XTEST(test_assume_u32_not_more_than) {
    uint32_t actual = 1000;
    uint32_t expected = 2000;
    ASSUME_NOT_MORE_THAN_U32(actual, expected);
}

XTEST(test_assume_u32_not_less_or_equal) {
    uint32_t actual = 3000;
    uint32_t expected = 2000;
    ASSUME_NOT_LESS_OR_EQUAL_U32(actual, expected);
}

XTEST(test_assume_u32_not_more_or_equal) {
    uint32_t actual = 1000;
    uint32_t expected = 2000;
    ASSUME_NOT_MORE_OR_EQUAL_U32(actual, expected);
}

// U64 Assertions - similar test cases as U8
XTEST(test_assume_u64_equal) {
    uint64_t actual = 50000;
    uint64_t expected = 50000;
    ASSUME_ITS_EQUAL_U64(actual, expected);
}

XTEST(test_assume_u64_less_than) {
    uint64_t actual = 10000;
    uint64_t expected = 20000;
    ASSUME_ITS_LESS_THAN_U64(actual, expected);
}

XTEST(test_assume_u64_more_than) {
    uint64_t actual = 30000;
    uint64_t expected = 20000;
    ASSUME_ITS_MORE_THAN_U64(actual, expected);
}

XTEST(test_assume_u64_less_or_equal) {
    uint64_t actual = 10000;
    uint64_t expected = 20000;
    ASSUME_ITS_LESS_OR_EQUAL_U64(actual, expected);
}

XTEST(test_assume_u64_more_or_equal) {
    uint64_t actual = 30000;
    uint64_t expected = 20000;
    ASSUME_ITS_MORE_OR_EQUAL_U64(actual, expected);
}

XTEST(test_assume_u64_not_equal) {
    uint64_t actual = 50000;
    uint64_t expected = 20000;
    ASSUME_NOT_EQUAL_U64(actual, expected);
}

XTEST(test_assume_u64_not_less_than) {
    uint64_t actual = 30000;
    uint64_t expected = 20000;
    ASSUME_NOT_LESS_THAN_U64(actual, expected);
}

XTEST(test_assume_u64_not_more_than) {
    uint64_t actual = 10000;
    uint64_t expected = 20000;
    ASSUME_NOT_MORE_THAN_U64(actual, expected);
}

XTEST(test_assume_u64_not_less_or_equal) {
    uint64_t actual = 30000;
    uint64_t expected = 20000;
    ASSUME_NOT_LESS_OR_EQUAL_U64(actual, expected);
}

XTEST(test_assume_u64_not_more_or_equal) {
    uint64_t actual = 10000;
    uint64_t expected = 20000;
    ASSUME_NOT_MORE_OR_EQUAL_U64(actual, expected);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(numeric_assume_uint_asserts_group) {
    ADD_TEST(test_assume_u8_equal);
    ADD_TEST(test_assume_u8_less_than);
    ADD_TEST(test_assume_u8_more_than);
    ADD_TEST(test_assume_u8_less_or_equal);
    ADD_TEST(test_assume_u8_more_or_equal);
    ADD_TEST(test_assume_u8_not_equal);
    ADD_TEST(test_assume_u8_not_less_than);
    ADD_TEST(test_assume_u8_not_more_than);
    ADD_TEST(test_assume_u8_not_less_or_equal);
    ADD_TEST(test_assume_u8_not_more_or_equal);
    ADD_TEST(test_assume_u16_equal);
    ADD_TEST(test_assume_u16_less_than);
    ADD_TEST(test_assume_u16_more_than);
    ADD_TEST(test_assume_u16_less_or_equal);
    ADD_TEST(test_assume_u16_more_or_equal);
    ADD_TEST(test_assume_u16_not_equal);
    ADD_TEST(test_assume_u16_not_less_than);
    ADD_TEST(test_assume_u16_not_more_than);
    ADD_TEST(test_assume_u16_not_less_or_equal);
    ADD_TEST(test_assume_u16_not_more_or_equal);
    ADD_TEST(test_assume_u32_equal);
    ADD_TEST(test_assume_u32_less_than);
    ADD_TEST(test_assume_u32_more_than);
    ADD_TEST(test_assume_u32_less_or_equal);
    ADD_TEST(test_assume_u32_more_or_equal);
    ADD_TEST(test_assume_u32_not_equal);
    ADD_TEST(test_assume_u32_not_less_than);
    ADD_TEST(test_assume_u32_not_more_than);
    ADD_TEST(test_assume_u32_not_less_or_equal);
    ADD_TEST(test_assume_u32_not_more_or_equal);
    ADD_TEST(test_assume_u64_equal);
    ADD_TEST(test_assume_u64_less_than);
    ADD_TEST(test_assume_u64_more_than);
    ADD_TEST(test_assume_u64_less_or_equal);
    ADD_TEST(test_assume_u64_more_or_equal);
    ADD_TEST(test_assume_u64_not_equal);
    ADD_TEST(test_assume_u64_not_less_than);
    ADD_TEST(test_assume_u64_not_more_than);
    ADD_TEST(test_assume_u64_not_less_or_equal);
    ADD_TEST(test_assume_u64_not_more_or_equal);
} // end of fixture
