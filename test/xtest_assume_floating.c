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
#include <fossil/xassume/floating.h> // library under test

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

XTEST(test_assume_f64_equal) {
    ASSUME_ITS_EQUAL_F64(3.5, 3.5, 0.001);
}

XTEST(test_assume_f64_less_than) {
    ASSUME_ITS_LESS_THAN_F64(3.5, 4.0);
}

XTEST(test_assume_f64_more_than) {
    ASSUME_ITS_MORE_THAN_F64(4.0, 3.5);
}

XTEST(test_assume_f64_less_or_equal) {
    ASSUME_ITS_LESS_OR_EQUAL_F64(3.5, 3.5);
}

XTEST(test_assume_f64_more_or_equal) {
    ASSUME_ITS_MORE_OR_EQUAL_F64(3.5, 3.5);
}

XTEST(test_assume_f64_not_equal) {
    ASSUME_NOT_EQUAL_F64(3.5, 4.0, 0.001);
}

XTEST(test_assume_f64_not_less_than) {
    ASSUME_NOT_LESS_THAN_F64(4.0, 3.5);
}

XTEST(test_assume_f64_not_more_than) {
    ASSUME_NOT_MORE_THAN_F64(3.5, 4.0);
}

XTEST(test_assume_f64_not_less_or_equal) {
    ASSUME_NOT_LESS_OR_EQUAL_F64(4.0, 3.5);
}

XTEST(test_assume_f64_not_more_or_equal) {
    ASSUME_NOT_MORE_OR_EQUAL_F64(3.5, 4.0);
}

XTEST(test_assume_f32_equal) {
    ASSUME_ITS_EQUAL_F32(3.5f, 3.5f, 0.001f);
}

XTEST(test_assume_f32_less_than) {
    ASSUME_ITS_LESS_THAN_F32(3.5f, 4.0f);
}

XTEST(test_assume_f32_more_than) {
    ASSUME_ITS_MORE_THAN_F32(4.0f, 3.5f);
}

XTEST(test_assume_f32_less_or_equal) {
    ASSUME_ITS_LESS_OR_EQUAL_F32(3.5f, 3.5f);
}

XTEST(test_assume_f32_more_or_equal) {
    ASSUME_ITS_MORE_OR_EQUAL_F32(3.5f, 3.5f);
}

XTEST(test_assume_f32_not_equal) {
    ASSUME_NOT_EQUAL_F32(3.5f, 4.0f, 0.001f);
}

XTEST(test_assume_f32_not_less_than) {
    ASSUME_NOT_LESS_THAN_F32(4.0f, 3.5f);
}

XTEST(test_assume_f32_not_more_than) {
    ASSUME_NOT_MORE_THAN_F32(3.5f, 4.0f);
}

XTEST(test_assume_f32_not_less_or_equal) {
    ASSUME_NOT_LESS_OR_EQUAL_F32(4.0f, 3.5f);
}

XTEST(test_assume_f32_not_more_or_equal) {
    ASSUME_NOT_MORE_OR_EQUAL_F32(3.5f, 4.0f);
}

XTEST(test_assume_f32_nan) {
    float nan_value = sqrtf(-1.0f); // Generate NaN
    ASSUME_ITS_NAN_F32(nan_value);
}

XTEST(test_assume_f32_inf) {
    float inf_value = 1.0f / 0.0f; // Generate Infinity
    ASSUME_ITS_INF_F32(inf_value);
}

XTEST(test_assume_f64_nan) {
    double nan_value = sqrt(-1.0); // Generate NaN
    ASSUME_ITS_NAN_F64(nan_value);
}

XTEST(test_assume_f64_inf) {
    double inf_value = 1.0 / 0.0; // Generate Infinity
    ASSUME_ITS_INF_F64(inf_value);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(floating_assume_asserts_group) {
    ADD_TEST(test_assume_f64_equal);
    ADD_TEST(test_assume_f64_less_than);
    ADD_TEST(test_assume_f64_more_than);
    ADD_TEST(test_assume_f64_less_or_equal);
    ADD_TEST(test_assume_f64_more_or_equal);
    ADD_TEST(test_assume_f64_not_equal);
    ADD_TEST(test_assume_f64_not_less_than);
    ADD_TEST(test_assume_f64_not_more_than);
    ADD_TEST(test_assume_f64_not_less_or_equal);
    ADD_TEST(test_assume_f64_not_more_or_equal);
    ADD_TEST(test_assume_f32_equal);
    ADD_TEST(test_assume_f32_less_than);
    ADD_TEST(test_assume_f32_more_than);
    ADD_TEST(test_assume_f32_less_or_equal);
    ADD_TEST(test_assume_f32_more_or_equal);
    ADD_TEST(test_assume_f32_not_equal);
    ADD_TEST(test_assume_f32_not_less_than);
    ADD_TEST(test_assume_f32_not_more_than);
    ADD_TEST(test_assume_f32_not_less_or_equal);
    ADD_TEST(test_assume_f32_not_more_or_equal);
    ADD_TEST(test_assume_f32_nan);
    ADD_TEST(test_assume_f32_inf);
    ADD_TEST(test_assume_f64_nan);
    ADD_TEST(test_assume_f64_inf);
} // end of fixture
