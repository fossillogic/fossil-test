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
#include <fossil/unittest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

#include <fossil/mockup/behavior.h> // library under test

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

FOSSIL_TEST(fossil_mockup_behavior_create_and_erase) {
    // Create a behavior object
    fossil_mockup_behavior_t *behavior = fossil_mockup_behavior_create("test_function", 2);
    ASSUME_NOT_CNULL(behavior);

    // Erase the behavior object
    fossil_mockup_behavior_erase(behavior);
}

FOSSIL_TEST(fossil_mockup_behavior_record_and_verify_call) {
    // Create a behavior object
    fossil_mockup_behavior_t *behavior = fossil_mockup_behavior_create("test_function", 2);
    ASSUME_NOT_CNULL(behavior);

    // Record a function call
    int arg1 = 42;
    const char *arg2 = "test";
    fossil_mockup_behavior_record_call(behavior, &arg1, arg2);

    // Verify the function call
    bool result = fossil_mockup_behavior_verify_call(behavior, 2, &arg1, arg2);
    ASSUME_ITS_TRUE(result);

    // Erase the behavior object
    fossil_mockup_behavior_erase(behavior);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_behav_group) {
    ADD_TEST(fossil_mockup_behavior_create_and_erase);
    ADD_TEST(fossil_mockup_behavior_record_and_verify_call);
} // end of fixture
