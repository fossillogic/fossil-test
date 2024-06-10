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

XTEST(test_assert_h8_equal) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x0F;
    ASSERT_ITS_EQUAL_H8(actual, expected);
}

XTEST(test_assert_h8_less_than) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x10;
    ASSERT_ITS_LESS_THAN_H8(actual, expected);
}

XTEST(test_assert_h8_more_than) {
    uint8_t actual = 0x10;
    uint8_t expected = 0x0F;
    ASSERT_ITS_MORE_THAN_H8(actual, expected);
}

XTEST(test_assert_h8_less_or_equal) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x10;
    ASSERT_ITS_LESS_OR_EQUAL_H8(actual, expected);
}

XTEST(test_assert_h8_more_or_equal) {
    uint8_t actual = 0x10;
    uint8_t expected = 0x0F;
    ASSERT_ITS_MORE_OR_EQUAL_H8(actual, expected);
}

XTEST(test_assert_h8_not_equal) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x10;
    ASSERT_NOT_EQUAL_H8(actual, expected);
}

XTEST(test_assert_h8_not_less_than) {
    uint8_t actual = 0x10;
    uint8_t expected = 0x0F;
    ASSERT_NOT_LESS_THAN_H8(actual, expected);
}

XTEST(test_assert_h8_not_more_than) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x10;
    ASSERT_NOT_MORE_THAN_H8(actual, expected);
}

XTEST(test_assert_h8_not_less_or_equal) {
    uint8_t actual = 0x10;
    uint8_t expected = 0x0F;
    ASSERT_NOT_LESS_OR_EQUAL_H8(actual, expected);
}

XTEST(test_assert_h8_not_more_or_equal) {
    uint8_t actual = 0x0F;
    uint8_t expected = 0x10;
    ASSERT_NOT_MORE_OR_EQUAL_H8(actual, expected);
}

// H16 Assertions
XTEST(test_assert_h16_equal) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0xFFFF;
    ASSERT_ITS_EQUAL_H16(actual, expected);
}

XTEST(test_assert_h16_less_than) {
    uint16_t actual = 0x0000;
    uint16_t expected = 0xFFFF;
    ASSERT_ITS_LESS_THAN_H16(actual, expected);
}

XTEST(test_assert_h16_more_than) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0x0000;
    ASSERT_ITS_MORE_THAN_H16(actual, expected);
}

XTEST(test_assert_h16_less_or_equal) {
    uint16_t actual = 0x0000;
    uint16_t expected = 0xFFFF;
    ASSERT_ITS_LESS_OR_EQUAL_H16(actual, expected);
}

XTEST(test_assert_h16_more_or_equal) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0x0000;
    ASSERT_ITS_MORE_OR_EQUAL_H16(actual, expected);
}

XTEST(test_assert_h16_not_equal) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0x0000;
    ASSERT_NOT_EQUAL_H16(actual, expected);
}

XTEST(test_assert_h16_not_less_than) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0x0000;
    ASSERT_NOT_LESS_THAN_H16(actual, expected);
}

XTEST(test_assert_h16_not_more_than) {
    uint16_t actual = 0x0000;
    uint16_t expected = 0xFFFF;
    ASSERT_NOT_MORE_THAN_H16(actual, expected);
}

XTEST(test_assert_h16_not_less_or_equal) {
    uint16_t actual = 0xFFFF;
    uint16_t expected = 0x0000;
    ASSERT_NOT_LESS_OR_EQUAL_H16(actual, expected);
}

XTEST(test_assert_h16_not_more_or_equal) {
    uint16_t actual = 0x0000;
    uint16_t expected = 0xFFFF;
    ASSERT_NOT_MORE_OR_EQUAL_H16(actual, expected);
}

// H32 Assertions
XTEST(test_assert_h32_equal) {
    uint32_t actual = 0xFFFFFFFF;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_ITS_EQUAL_H32(actual, expected);
}

XTEST(test_assert_h32_less_than) {
    uint32_t actual = 0xFFFFFFFF;
    uint32_t expected = 0x00000000;
    ASSERT_ITS_LESS_THAN_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_more_than) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_ITS_MORE_THAN_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_less_or_equal) {
    uint32_t actual = 0xFFFFFFFF;
    uint32_t expected = 0x00000000;
    ASSERT_ITS_LESS_OR_EQUAL_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_more_or_equal) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_ITS_MORE_OR_EQUAL_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_not_equal) {
    uint32_t actual = 0xFFFFFFFF;
    uint32_t expected = 0x00000000;
    ASSERT_NOT_EQUAL_H32(actual, expected);
}

XTEST(test_assert_h32_not_less_than) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_NOT_LESS_THAN_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_not_more_than) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_NOT_MORE_THAN_H32(actual, expected);
}

XTEST(test_assert_h32_not_less_or_equal) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_NOT_LESS_OR_EQUAL_H32(expected, actual); // Switched actual and expected
}

XTEST(test_assert_h32_not_more_or_equal) {
    uint32_t actual = 0x00000000;
    uint32_t expected = 0xFFFFFFFF;
    ASSERT_NOT_MORE_OR_EQUAL_H32(actual, expected);
}

// H64 Assertions
XTEST(test_assert_h64_equal) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0xFFFFFFFFFFFFFFFF;
    ASSERT_ITS_EQUAL_H64(actual, expected);
}

XTEST(test_assert_h64_less_than) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0x0000000000000000;
    ASSERT_ITS_LESS_THAN_H64(actual, expected);
}

XTEST(test_assert_h64_more_than) {
    uint64_t actual = 0x0000000000000000;
    uint64_t expected = 0xFFFFFFFFFFFFFFFF;
    ASSERT_ITS_MORE_THAN_H64(actual, expected);
}

XTEST(test_assert_h64_less_or_equal) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0x0000000000000000;
    ASSERT_ITS_LESS_OR_EQUAL_H64(actual, expected);
}

XTEST(test_assert_h64_more_or_equal) {
    uint64_t actual = 0x0000000000000000;
    uint64_t expected = 0xFFFFFFFFFFFFFFFF;
    ASSERT_ITS_MORE_OR_EQUAL_H64(actual, expected);
}

XTEST(test_assert_h64_not_equal) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0x0000000000000000;
    ASSERT_NOT_EQUAL_H64(actual, expected);
}

XTEST(test_assert_h64_not_less_than) {
    uint64_t actual = 0x0000000000000000;
    uint64_t expected = 0xFFFFFFFFFFFFFFFF;
    ASSERT_NOT_LESS_THAN_H64(actual, expected);
}

XTEST(test_assert_h64_not_more_than) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0x0000000000000000;
    ASSERT_NOT_MORE_THAN_H64(actual, expected);
}

XTEST(test_assert_h64_not_less_or_equal) {
    uint64_t actual = 0x0000000000000000;
    uint64_t expected = 0xFFFFFFFFFFFFFFFF;
    ASSERT_NOT_LESS_OR_EQUAL_H64(actual, expected);
}

XTEST(test_assert_h64_not_more_or_equal) {
    uint64_t actual = 0xFFFFFFFFFFFFFFFF;
    uint64_t expected = 0x0000000000000000;
    ASSERT_NOT_MORE_OR_EQUAL_H64(actual, expected);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(numeric_hex_asserts_assert_group) {
    ADD_TEST(test_assert_h8_equal);
    ADD_TEST(test_assert_h8_less_than);
    ADD_TEST(test_assert_h8_more_than);
    ADD_TEST(test_assert_h8_less_or_equal);
    ADD_TEST(test_assert_h8_more_or_equal);
    ADD_TEST(test_assert_h8_not_equal);
    ADD_TEST(test_assert_h8_not_less_than);
    ADD_TEST(test_assert_h8_not_more_than);
    ADD_TEST(test_assert_h8_not_less_or_equal);
    ADD_TEST(test_assert_h8_not_more_or_equal);
    ADD_TEST(test_assert_h16_equal);
    ADD_TEST(test_assert_h16_less_than);
    ADD_TEST(test_assert_h16_more_than);
    ADD_TEST(test_assert_h16_less_or_equal);
    ADD_TEST(test_assert_h16_more_or_equal);
    ADD_TEST(test_assert_h16_not_equal);
    ADD_TEST(test_assert_h16_not_less_than);
    ADD_TEST(test_assert_h16_not_more_than);
    ADD_TEST(test_assert_h16_not_less_or_equal);
    ADD_TEST(test_assert_h16_not_more_or_equal);
    ADD_TEST(test_assert_h32_equal);
    ADD_TEST(test_assert_h32_less_than);
    ADD_TEST(test_assert_h32_more_than);
    ADD_TEST(test_assert_h32_less_or_equal);
    ADD_TEST(test_assert_h32_more_or_equal);
    ADD_TEST(test_assert_h32_not_equal);
    ADD_TEST(test_assert_h32_not_less_than);
    ADD_TEST(test_assert_h32_not_more_than);
    ADD_TEST(test_assert_h32_not_less_or_equal);
    ADD_TEST(test_assert_h32_not_more_or_equal);
    ADD_TEST(test_assert_h64_equal);
    // ADD_TEST(test_assert_h64_less_than);
    // ADD_TEST(test_assert_h64_more_than);
    // ADD_TEST(test_assert_h64_less_or_equal);
    // ADD_TEST(test_assert_h64_more_or_equal);
    // ADD_TEST(test_assert_h64_not_equal);
    // ADD_TEST(test_assert_h64_not_less_than);
    // ADD_TEST(test_assert_h64_not_more_than);
    // ADD_TEST(test_assert_h64_not_less_or_equal);
    // ADD_TEST(test_assert_h64_not_more_or_equal);
} // end of fixture
