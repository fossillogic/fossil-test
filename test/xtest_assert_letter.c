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
#include <fossil/xassert/letter.h> // library under test

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

XTEST(test_bchar_equal) {
    ASSERT_ITS_EQUAL_BCHAR('a', 'a');
}

XTEST(test_bchar_not_equal) {
    ASSERT_NOT_EQUAL_BCHAR('a', 'b');
}

XTEST(test_char_equal) {
    ASSERT_ITS_EQUAL_CHAR('a', 'a');
}

XTEST(test_char_not_equal) {
    ASSERT_NOT_EQUAL_CHAR('a', 'b');
}

XTEST(test_wchar_equal) {
    ASSERT_ITS_EQUAL_WCHAR(L'a', L'a');
}

XTEST(test_wchar_not_equal) {
    ASSERT_NOT_EQUAL_WCHAR(L'a', L'b');
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(letter_asserts_assert_group) {
    ADD_TEST(test_bchar_equal);
    ADD_TEST(test_bchar_not_equal);
    ADD_TEST(test_char_equal);
    ADD_TEST(test_char_not_equal);
    ADD_TEST(test_wchar_equal);
    ADD_TEST(test_wchar_not_equal);
} // end of fixture
