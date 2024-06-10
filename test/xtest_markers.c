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
#include <fossil/unittest.h>

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


FOSSIL_TEST(testing_marker_fake) {
    TEST_ASSERT(true, "This test case should have passeed");
} // end case

// Test case using testing_marker_skip:
// This test case is for simulating a cross-platform scenario,
// applicable to systems such as ARM, AVR, iOS, Adafruit, etc.
// One use case of skipping is to separate low-level cases from high-level cases
// that might run in a non-bare-metal environment, such as the STM32L475 IoT Node.
// Skipping a test case can be useful when certain conditions or prerequisites are not met,
// or when the test is not applicable to the current environment or configuration.
// It allows testers to focus on relevant test cases and avoid unnecessary execution
// of tests that may not provide meaningful results in a particular context.
FOSSIL_TEST(testing_marker_skip) {
    bool skip = true; // the condtion is false but the skip marker prevents this test from running
    TEST_ASSERT(false == skip, "This shouldn't have run because of the marker 'skip'");
} // end case

FOSSIL_TEST(testing_marker_pass) {
    TEST_ASSERT(true, "This test case should have passeed");
} // end case

FOSSIL_TEST(testing_marker_fail) {
   bool sky_is_blue = true;
   TEST_ASSUME(sky_is_blue == false, "This test case should have passeed");
} // end case

FOSSIL_TEST(testing_marker_none) {
    TEST_ASSERT(true, "This test case should have passeed");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(markers_test_group) {
    // Should do nothing beyond show an error message that the marker does not exist
    APPLY_MARK(testing_marker_fake, "does not exist");
    ADD_TEST(testing_marker_fake);
    APPLY_MARK(testing_marker_skip, "skip");
    ADD_TEST(testing_marker_skip);
    APPLY_MARK(testing_marker_fail, "fail"); // This should fail without crashing the runner
    ADD_TEST(testing_marker_fail);
    APPLY_MARK(testing_marker_pass, "pass");
    ADD_TEST(testing_marker_pass);

    // Markers should not affect the test case
    ADD_TEST(testing_marker_none);
} // end of group
