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
// Objective-C Sample Test Data Class
// -----------------------------------------------------------------------------
@interface ObjCSampleTestData : NSObject
@property(nonatomic, assign) int input;
@property(nonatomic, assign) int expected_output;
- (instancetype)initWithInput:(int)input expected:(int)expected;
@end

@implementation ObjCSampleTestData
- (instancetype)initWithInput:(int)input expected:(int)expected {
    self = [super init];
    if (self) {
        _input = input;
        _expected_output = expected;
    }
    return self;
}
@end

// -----------------------------------------------------------------------------
// Fossil Logic Test Suite Setup/Teardown
// -----------------------------------------------------------------------------
FOSSIL_SETUP(objc_sample_suite) {
    // Setup code for Objective-C tests
}

FOSSIL_TEARDOWN(objc_sample_suite) {
    // Teardown code for Objective-C tests
}

FOSSIL_SUITE(objc_sample_suite);

// -----------------------------------------------------------------------------
// Fossil Logic Test Cases (Objective-C flavored)
// -----------------------------------------------------------------------------
FOSSIL_TEST(objc_test_input_increment) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:5 expected:6];
    int actual_output = data.input + 1;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Increment test failed");
}

FOSSIL_TEST(objc_test_input_decrement) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:5 expected:4];
    int actual_output = data.input - 1;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Decrement test failed");
}

FOSSIL_TEST(objc_test_input_double) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:5 expected:10];
    int actual_output = data.input * 2;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Double test failed");
}

FOSSIL_TEST(objc_test_input_half) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:10 expected:5];
    int actual_output = data.input / 2;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Half test failed");
}

FOSSIL_TEST(objc_test_input_modulo) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:5 expected:1];
    int actual_output = data.input % 2;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Modulo test failed");
}

FOSSIL_TEST(objc_test_input_square) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:3 expected:9];
    int actual_output = data.input * data.input;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Square test failed");
}

FOSSIL_TEST(objc_test_input_equal) {
    ObjCSampleTestData *data = [[ObjCSampleTestData alloc] initWithInput:7 expected:7];
    int actual_output = data.input;
    FOSSIL_TEST_ASSUME(actual_output == data.expected_output, "Equality test failed");
}

// -----------------------------------------------------------------------------
// Grouping Tests
// -----------------------------------------------------------------------------
FOSSIL_TEST_GROUP(objc_sample_test_cases) {
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_increment);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_decrement);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_double);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_half);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_modulo);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_square);
    FOSSIL_TEST_ADD(objc_sample_suite, objc_test_input_equal);

    FOSSIL_TEST_REGISTER(objc_sample_suite);
}
