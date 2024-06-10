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
#include <fossil/xassume/within.h> // library under test

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

// Test case for general range assertions
XTEST(test_general_assume_within_range_success) {
    int value = 5;
    ASSUME_ITS_WITHIN_RANGE(value, 1, 10);
}

XTEST(test_general_not_assume_within_range_success) {
    int value = 11;
    ASSUME_NOT_WITHIN_RANGE(value, 1, 10);
}

// Test cases for uint8_t range assertions
XTEST(test_assume_uint8_assume_within_range_success) {
    uint8_t value = 5;
    ASSUME_ITS_WITHIN_RANGE_U8(value, 1, 10);
}

XTEST(test_assume_uint8_not_assume_within_range_success) {
    uint8_t value = 11;
    ASSUME_NOT_WITHIN_RANGE_U8(value, 1, 10);
}

// Test cases for uint16_t range assertions
XTEST(test_assume_uint16_assume_within_range_success) {
    uint16_t value = 500;
    ASSUME_ITS_WITHIN_RANGE_U16(value, 100, 1000);
}

XTEST(test_assume_uint16_not_assume_within_range_success) {
    uint16_t value = 1500;
    ASSUME_NOT_WITHIN_RANGE_U16(value, 100, 1000);
}

// Test cases for uint32_t range assertions
XTEST(test_assume_uint32_assume_within_range_success) {
    uint32_t value = 500000;
    ASSUME_ITS_WITHIN_RANGE_U32(value, 100000, 1000000);
}

XTEST(test_assume_uint32_not_assume_within_range_success) {
    uint32_t value = 1500000;
    ASSUME_NOT_WITHIN_RANGE_U32(value, 100000, 1000000);
}

// Test cases for uint64_t range assertions
XTEST(test_assume_uint64_assume_within_range_success) {
    uint64_t value = 5000000000;
    ASSUME_ITS_WITHIN_RANGE_U64(value, 1000000000, 10000000000);
}

XTEST(test_assume_uint64_not_assume_within_range_success) {
    uint64_t value = 15000000000;
    ASSUME_NOT_WITHIN_RANGE_U64(value, 1000000000, 10000000000);
}

// Test cases for int8_t range assertions
XTEST(test_assume_int8_assume_within_range_success) {
    int8_t value = 5;
    ASSUME_ITS_WITHIN_RANGE_I8(value, 1, 10);
}

XTEST(test_assume_int8_not_assume_within_range_success) {
    int8_t value = 11;
    ASSUME_NOT_WITHIN_RANGE_I8(value, 1, 10);
}

// Test cases for int16_t range assertions
XTEST(test_assume_int16_assume_within_range_success) {
    int16_t value = 500;
    ASSUME_ITS_WITHIN_RANGE_I16(value, 100, 1000);
}

XTEST(test_assume_int16_not_assume_within_range_success) {
    int16_t value = 1500;
    ASSUME_NOT_WITHIN_RANGE_I16(value, 100, 1000);
}

// Test cases for int32_t range assertions
XTEST(test_assume_int32_assume_within_range_success) {
    int32_t value = 500000;
    ASSUME_ITS_WITHIN_RANGE_I32(value, 100000, 1000000);
}

XTEST(test_assume_int32_not_assume_within_range_success) {
    int32_t value = 1500000;
    ASSUME_NOT_WITHIN_RANGE_I32(value, 100000, 1000000);
}

// Test cases for int64_t range assertions
XTEST(test_assume_int64_assume_within_range_success) {
    int64_t value = 5000000000;
    ASSUME_ITS_WITHIN_RANGE_I64(value, 1000000000, 10000000000);
}

XTEST(test_assume_int64_not_assume_within_range_success) {
    int64_t value = 15000000000;
    ASSUME_NOT_WITHIN_RANGE_I64(value, 1000000000, 10000000000);
}

// Test cases for uint8_t range assertions
XTEST(test_bchar_assume_within_range_success) {
    uint8_t value = 65; // ASCII for 'A'
    ASSUME_ITS_WITHIN_RANGE_BCHAR(value, 65, 90); // 'A' to 'Z'
}

XTEST(test_bchar_not_assume_within_range_success) {
    uint8_t value = 97; // ASCII for 'a'
    ASSUME_NOT_WITHIN_RANGE_BCHAR(value, 65, 90); // 'A' to 'Z'
}

// Test cases for char range assertions
XTEST(test_char_assume_within_range_success) {
    char value = 'A';
    ASSUME_ITS_WITHIN_RANGE_CCHAR(value, 'A', 'Z');
}

// Test cases for wchar_t range assertions
XTEST(test_wchar_assume_within_range_success) {
    wchar_t value = L'A';
    ASSUME_ITS_WITHIN_RANGE_WCHAR(value, L'A', L'Z');
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(within_assume_asserts_group) {
    ADD_TEST(test_general_assume_within_range_success);
    ADD_TEST(test_general_not_assume_within_range_success);
    ADD_TEST(test_bchar_assume_within_range_success);
    ADD_TEST(test_bchar_not_assume_within_range_success);
    ADD_TEST(test_assume_uint16_assume_within_range_success);
    ADD_TEST(test_assume_uint16_not_assume_within_range_success);
    ADD_TEST(test_assume_uint32_assume_within_range_success);
    ADD_TEST(test_assume_uint32_not_assume_within_range_success);
    ADD_TEST(test_assume_uint64_assume_within_range_success);
    ADD_TEST(test_assume_uint64_not_assume_within_range_success);
    ADD_TEST(test_assume_int8_assume_within_range_success);
    ADD_TEST(test_assume_int8_not_assume_within_range_success);
    ADD_TEST(test_assume_int16_assume_within_range_success);
    ADD_TEST(test_assume_int16_not_assume_within_range_success);
    ADD_TEST(test_assume_int32_assume_within_range_success);
    ADD_TEST(test_assume_int32_not_assume_within_range_success);
    ADD_TEST(test_assume_int64_assume_within_range_success);
    ADD_TEST(test_assume_int64_not_assume_within_range_success);
    ADD_TEST(test_assume_uint8_assume_within_range_success);
    ADD_TEST(test_assume_uint8_not_assume_within_range_success);
    ADD_TEST(test_char_assume_within_range_success);
    ADD_TEST(test_wchar_assume_within_range_success);
} // end of fixture
