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
#include <fossil/xassume/boolean.h> // library under test

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

XTEST(test_assume_boolean_true) {
    int value = 42;

    ASSUME_ITS_TRUE(value == 42);
}

XTEST(test_assume_boolean_false) {
    int value = 42;

    ASSUME_ITS_FALSE(value == 43);
}

XTEST(test_assume_not_boolean_true) {
    int value = 42;

    ASSUME_NOT_TRUE(value == 43);
}

XTEST(test_assume_not_boolean_false) {
    int value = 42;

    ASSUME_NOT_FALSE(value == 42);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(bool_asserts_assume_group) {
    ADD_TEST(test_assume_boolean_true);
    ADD_TEST(test_assume_boolean_false);
    ADD_TEST(test_assume_not_boolean_true);
    ADD_TEST(test_assume_not_boolean_false);
} // end of fixture
