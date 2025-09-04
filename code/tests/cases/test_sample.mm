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
#import <Foundation/Foundation.h>
#include "fossil/pizza/framework.h"

// -----------------------------------------------------------------------------
// C struct (still supported in ObjC++)
// -----------------------------------------------------------------------------
FOSSIL_MOCK_STRUCT(ObjCppSampleTestData) {
    int input;
    int expected_output;
};

// -----------------------------------------------------------------------------
// C++ helper (available in Objective-C++)
// -----------------------------------------------------------------------------
class ObjCppHelper {
public:
    static int square(int x) { return x * x; }
    static int half(int x)   { return x / 2; }
};

// -----------------------------------------------------------------------------
// Objective-C wrapper class
// -----------------------------------------------------------------------------
@interface ObjCppWrapper : NSObject
- (BOOL)checkValue:(int)input equals:(int)expected;
@end

@implementation ObjCppWrapper
- (BOOL)checkValue:(int)input equals:(int)expected {
    return input == expected;
}
@end

// -----------------------------------------------------------------------------
// Fossil Logic Test Suite Setup/Teardown
// -----------------------------------------------------------------------------
FOSSIL_SETUP(objcpp_sample_suite) {
    // Setup for ObjC++ tests
}

FOSSIL_TEARDOWN(objcpp_sample_suite) {
    // Teardown for ObjC++ tests
}

FOSSIL_SUITE(objcpp_sample_suite);

// -----------------------------------------------------------------------------
// Fossil Logic Test Cases
// -----------------------------------------------------------------------------
FOSSIL_TEST(objcpp_test_input_increment) {
    ObjCppSampleTestData data = {5, 6};
    int actual_output = data.input + 1;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Increment test failed");
}

FOSSIL_TEST(objcpp_test_input_decrement) {
    ObjCppSampleTestData data = {5, 4};
    int actual_output = data.input - 1;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Decrement test failed");
}

FOSSIL_TEST(objcpp_test_input_double) {
    ObjCppSampleTestData data = {5, 10};
    int actual_output = data.input * 2;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Double test failed");
}

FOSSIL_TEST(objcpp_test_input_half) {
    ObjCppSampleTestData data = {10, 5};
    int actual_output = ObjCppHelper::half(data.input); // Using C++ helper
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Half test failed");
}

FOSSIL_TEST(objcpp_test_input_modulo) {
    ObjCppSampleTestData data = {5, 1};
    int actual_output = data.input % 2;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Modulo test failed");
}

FOSSIL_TEST(objcpp_test_input_square) {
    ObjCppSampleTestData data = {3, 9};
    int actual_output = ObjCppHelper::square(data.input); // Using C++ helper
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Square test failed");
}

FOSSIL_TEST(objcpp_test_input_equal) {
    ObjCppSampleTestData data = {7, 7};
    ObjCppWrapper *checker = [[ObjCppWrapper alloc] init];
    BOOL success = [checker checkValue:data.input equals:data.expected_output];
    FOSSIL_TEST_ASSUME(success, "Equality test failed");
}

// -----------------------------------------------------------------------------
// Grouping Tests
// -----------------------------------------------------------------------------
FOSSIL_TEST_GROUP(objcpp_sample_test_cases) {
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_increment);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_decrement);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_double);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_half);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_modulo);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_square);
    FOSSIL_TEST_ADD(objcpp_sample_suite, objcpp_test_input_equal);

    FOSSIL_TEST_REGISTER(objcpp_sample_suite);
}
