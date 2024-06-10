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
#include <fossil/xassume/string.h> // library under test

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

// Test cases for wide char string equality check
XTEST(test_wstr_equal_success) {
    const wchar_t* actual = L"Hello";
    const wchar_t* expected = L"Hello";
    ASSUME_ITS_EQUAL_WSTR(actual, expected);
}

// Test cases for wide char string inequality check
XTEST(test_wstr_not_equal_success) {
    const wchar_t* actual = L"Hello";
    const wchar_t* expected = L"World";
    ASSUME_NOT_EQUAL_WSTR(actual, expected);
}

// Test cases for wide char string length comparison
XTEST(test_wstr_length_equal_success) {
    const wchar_t* str = L"Hello";
    const size_t expected_len = 5;
    ASSUME_ITS_LENGTH_EQUAL_WSTR(str, expected_len);
}

// Test cases for byte string equality check
XTEST(test_bstr_equal_success) {
    const uint8_t* actual = (const uint8_t*)"Hello";
    const uint8_t* expected = (const uint8_t*)"Hello";
    ASSUME_ITS_EQUAL_BSTR(actual, expected);
}

// Test cases for byte string inequality check
XTEST(test_bstr_not_equal_success) {
    const uint8_t* actual = (const uint8_t*)"Hello";
    const uint8_t* expected = (const uint8_t*)"World";
    ASSUME_NOT_EQUAL_BSTR(actual, expected);
}

// Test cases for byte string length comparison
XTEST(test_bstr_length_equal_success) {
    const uint8_t* str = (const uint8_t*)"Hello";
    const size_t expected_len = 5;
    ASSUME_ITS_LENGTH_EQUAL_BSTR(str, expected_len);
}

// Test cases for classic C string equality check
XTEST(test_cstr_equal_success) {
    const char* actual = "Hello";
    const char* expected = "Hello";
    ASSUME_ITS_EQUAL_CSTR(actual, expected);
}

// Test cases for classic C string inequality check
XTEST(test_cstr_not_equal_success) {
    const char* actual = "Hello";
    const char* expected = "World";
    ASSUME_NOT_EQUAL_CSTR(actual, expected);
}

// Test cases for classic C string length comparison
XTEST(test_cstr_length_equal_success) {
    const char* str = "Hello";
    const size_t expected_len = 5;
    ASSUME_ITS_LENGTH_EQUAL_CSTR(str, expected_len);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(string_asserts_group) {
    ADD_TEST(test_wstr_equal_success);
    ADD_TEST(test_wstr_not_equal_success);
    ADD_TEST(test_wstr_length_equal_success);
    ADD_TEST(test_bstr_equal_success);
    ADD_TEST(test_bstr_not_equal_success);
    ADD_TEST(test_bstr_length_equal_success);
    ADD_TEST(test_cstr_equal_success);
    ADD_TEST(test_cstr_not_equal_success);
    ADD_TEST(test_cstr_length_equal_success);
} // end of fixture
