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

XTEST(test_assume_octal_equal_O8) {
    uint8_t actual = 07;
    uint8_t expected = 07;
    ASSUME_ITS_EQUAL_O8(actual, expected);
}

XTEST(test_assume_octal_not_equal_O8) {
    uint8_t actual = 07;
    uint8_t expected = 06;
    ASSUME_NOT_EQUAL_O8(actual, expected);
}

XTEST(test_assume_octal_less_than_O8) {
    uint8_t actual = 06;
    uint8_t expected = 07;
    ASSUME_ITS_LESS_THAN_O8(actual, expected);
}

XTEST(test_assume_octal_more_than_O8) {
    uint8_t actual = 07;
    uint8_t expected = 06;
    ASSUME_ITS_MORE_THAN_O8(actual, expected);
}

XTEST(test_assume_octal_less_or_equal_O8) {
    uint8_t actual = 07;
    uint8_t expected = 07;
    ASSUME_ITS_LESS_OR_EQUAL_O8(actual, expected);
}

XTEST(test_assume_octal_more_or_equal_O8) {
    uint8_t actual = 07;
    uint8_t expected = 07;
    ASSUME_ITS_MORE_OR_EQUAL_O8(actual, expected);
}

XTEST(test_assume_octal_not_less_than_O8) {
    uint8_t actual = 07;
    uint8_t expected = 07;
    ASSUME_NOT_LESS_THAN_O8(actual, expected);
}

XTEST(test_assume_octal_not_more_than_O8) {
    uint8_t actual = 07;
    uint8_t expected = 07;
    ASSUME_NOT_MORE_THAN_O8(actual, expected);
}

XTEST(test_assume_octal_not_less_or_equal_O8) {
    uint8_t actual = 07;
    uint8_t expected = 06;
    ASSUME_NOT_LESS_OR_EQUAL_O8(actual, expected);
}

XTEST(test_assume_octal_not_more_or_equal_O8) {
    uint8_t actual = 06;
    uint8_t expected = 07;
    ASSUME_NOT_MORE_OR_EQUAL_O8(actual, expected);
}

// O16 Assertions
XTEST(test_assume_octal_equal_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0777;
    ASSUME_ITS_EQUAL_O16(actual, expected);
}

XTEST(test_assume_octal_not_equal_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0776;
    ASSUME_NOT_EQUAL_O16(actual, expected);
}

XTEST(test_assume_octal_less_than_O16) {
    uint16_t actual = 0776;
    uint16_t expected = 0777;
    ASSUME_ITS_LESS_THAN_O16(actual, expected);
}

XTEST(test_assume_octal_more_than_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0776;
    ASSUME_ITS_MORE_THAN_O16(actual, expected);
}

XTEST(test_assume_octal_less_or_equal_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0777;
    ASSUME_ITS_LESS_OR_EQUAL_O16(actual, expected);
}

XTEST(test_assume_octal_more_or_equal_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0777;
    ASSUME_ITS_MORE_OR_EQUAL_O16(actual, expected);
}

XTEST(test_assume_octal_not_less_than_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0777;
    ASSUME_NOT_LESS_THAN_O16(actual, expected);
}

XTEST(test_assume_octal_not_more_than_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0777;
    ASSUME_NOT_MORE_THAN_O16(actual, expected);
}

XTEST(test_assume_octal_not_less_or_equal_O16) {
    uint16_t actual = 0777;
    uint16_t expected = 0776;
    ASSUME_NOT_LESS_OR_EQUAL_O16(actual, expected);
}

XTEST(test_assume_octal_not_more_or_equal_O16) {
    uint16_t actual = 0776;
    uint16_t expected = 0777;
    ASSUME_NOT_MORE_OR_EQUAL_O16(actual, expected);
}

// O32 Assertions
XTEST(test_assume_octal_equal_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777777;
    ASSUME_ITS_EQUAL_O32(actual, expected);
}

XTEST(test_assume_octal_not_equal_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777776;
    ASSUME_NOT_EQUAL_O32(actual, expected);
}

XTEST(test_assume_octal_less_than_O32) {
    uint32_t actual = 077777776;
    uint32_t expected = 077777777;
    ASSUME_ITS_LESS_THAN_O32(actual, expected);
}

XTEST(test_assume_octal_more_than_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777776;
    ASSUME_ITS_MORE_THAN_O32(actual, expected);
}

XTEST(test_assume_octal_less_or_equal_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777777;
    ASSUME_ITS_LESS_OR_EQUAL_O32(actual, expected);
}

XTEST(test_assume_octal_more_or_equal_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777777;
    ASSUME_ITS_MORE_OR_EQUAL_O32(actual, expected);
}

XTEST(test_assume_octal_not_less_than_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777777;
    ASSUME_NOT_LESS_THAN_O32(actual, expected);
}

XTEST(test_assume_octal_not_more_than_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777777;
    ASSUME_NOT_MORE_THAN_O32(actual, expected);
}

XTEST(test_assume_octal_not_less_or_equal_O32) {
    uint32_t actual = 077777777;
    uint32_t expected = 077777776;
    ASSUME_NOT_LESS_OR_EQUAL_O32(actual, expected);
}

XTEST(test_assume_octal_not_more_or_equal_O32) {
    uint32_t actual = 077777776;
    uint32_t expected = 077777777;
    ASSUME_NOT_MORE_OR_EQUAL_O32(actual, expected);
}

// O64 Assertions
XTEST(test_assume_octal_equal_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777777;
    ASSUME_ITS_EQUAL_O64(actual, expected);
}

XTEST(test_assume_octal_not_equal_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777776;
    ASSUME_NOT_EQUAL_O64(actual, expected);
}

XTEST(test_assume_octal_less_than_O64) {
    uint64_t actual = 07777777777777776;
    uint64_t expected = 07777777777777777;
    ASSUME_ITS_LESS_THAN_O64(actual, expected);
}

XTEST(test_assume_octal_more_than_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777776;
    ASSUME_ITS_MORE_THAN_O64(actual, expected);
}

XTEST(test_assume_octal_less_or_equal_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777777;
    ASSUME_ITS_LESS_OR_EQUAL_O64(actual, expected);
}

XTEST(test_assume_octal_more_or_equal_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777777;
    ASSUME_ITS_MORE_OR_EQUAL_O64(actual, expected);
}

XTEST(test_assume_octal_not_less_than_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777777;
    ASSUME_NOT_LESS_THAN_O64(actual, expected);
}

XTEST(test_assume_octal_not_more_than_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777777;
    ASSUME_NOT_MORE_THAN_O64(actual, expected);
}

XTEST(test_assume_octal_not_less_or_equal_O64) {
    uint64_t actual = 07777777777777777;
    uint64_t expected = 07777777777777776;
    ASSUME_NOT_LESS_OR_EQUAL_O64(actual, expected);
}

XTEST(test_assume_octal_not_more_or_equal_O64) {
    uint64_t actual = 07777777777777776;
    uint64_t expected = 07777777777777777;
    ASSUME_NOT_MORE_OR_EQUAL_O64(actual, expected);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(numeric_assume_oct_asserts_group) {
    ADD_TEST(test_assume_octal_equal_O8);
    ADD_TEST(test_assume_octal_not_equal_O8);
    ADD_TEST(test_assume_octal_less_than_O8);
    ADD_TEST(test_assume_octal_more_than_O8);
    ADD_TEST(test_assume_octal_less_or_equal_O8);
    ADD_TEST(test_assume_octal_more_or_equal_O8);
    ADD_TEST(test_assume_octal_not_less_than_O8);
    ADD_TEST(test_assume_octal_not_more_than_O8);
    ADD_TEST(test_assume_octal_not_less_or_equal_O8);
    ADD_TEST(test_assume_octal_not_more_or_equal_O8);

    ADD_TEST(test_assume_octal_equal_O16);
    ADD_TEST(test_assume_octal_not_equal_O16);
    ADD_TEST(test_assume_octal_less_than_O16);
    ADD_TEST(test_assume_octal_more_than_O16);
    ADD_TEST(test_assume_octal_less_or_equal_O16);
    ADD_TEST(test_assume_octal_more_or_equal_O16);
    ADD_TEST(test_assume_octal_not_less_than_O16);
    ADD_TEST(test_assume_octal_not_more_than_O16);
    ADD_TEST(test_assume_octal_not_less_or_equal_O16);
    ADD_TEST(test_assume_octal_not_more_or_equal_O16);

    ADD_TEST(test_assume_octal_equal_O32);
    ADD_TEST(test_assume_octal_not_equal_O32);
    ADD_TEST(test_assume_octal_less_than_O32);
    ADD_TEST(test_assume_octal_more_than_O32);
    ADD_TEST(test_assume_octal_less_or_equal_O32);
    ADD_TEST(test_assume_octal_more_or_equal_O32);
    ADD_TEST(test_assume_octal_not_less_than_O32);
    ADD_TEST(test_assume_octal_not_more_than_O32);
    ADD_TEST(test_assume_octal_not_less_or_equal_O32);
    ADD_TEST(test_assume_octal_not_more_or_equal_O32);

    ADD_TEST(test_assume_octal_equal_O64);
    ADD_TEST(test_assume_octal_not_equal_O64);
    ADD_TEST(test_assume_octal_less_than_O64);
    ADD_TEST(test_assume_octal_more_than_O64);
    ADD_TEST(test_assume_octal_less_or_equal_O64);
    ADD_TEST(test_assume_octal_more_or_equal_O64);
    ADD_TEST(test_assume_octal_not_less_than_O64);
    ADD_TEST(test_assume_octal_not_more_than_O64);
    ADD_TEST(test_assume_octal_not_less_or_equal_O64);
    ADD_TEST(test_assume_octal_not_more_or_equal_O64);
} // end of fixture
