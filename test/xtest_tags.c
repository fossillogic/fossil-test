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

FOSSIL_TEST(testing_slow_tags) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSERT(x == 42, "Should have passed the test case");
    TEST_ASSERT(y == 20, "Should have passed the test case");
    TEST_ASSERT(x != y, "Should have passed the test case");
    TEST_ASSERT(y < x, "Should have passed the test case");
    TEST_ASSERT(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(testing_fast_tags) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSERT(x == 42, "Should have passed the test case");
    TEST_ASSERT(y == 20, "Should have passed the test case");
    TEST_ASSERT(x != y, "Should have passed the test case");
    TEST_ASSERT(y < x, "Should have passed the test case");
    TEST_ASSERT(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(testing_no_tags) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSERT(x == 42, "Should have passed the test case");
    TEST_ASSERT(y == 20, "Should have passed the test case");
    TEST_ASSERT(x != y, "Should have passed the test case");
    TEST_ASSERT(y < x, "Should have passed the test case");
    TEST_ASSERT(y <= x, "Should have passed the test case");
} // end case

FOSSIL_TEST(testing_fake_tags) {
    int x = 42;
    int y = 20;

    // Test cases
    TEST_ASSERT(x == 42, "Should have passed the test case");
    TEST_ASSERT(y == 20, "Should have passed the test case");
    TEST_ASSERT(x != y, "Should have passed the test case");
    TEST_ASSERT(y < x, "Should have passed the test case");
    TEST_ASSERT(y <= x, "Should have passed the test case");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(tags_test_group) {
    // Should do nothing beyond show an error message that the tag does not exist
    APPLY_XTAG(testing_fake_tags, "pizza pizza pizza");
    ADD_TEST(testing_fake_tags);
    APPLY_XTAG(testing_slow_tags, "slow");
    ADD_TEST(testing_slow_tags);
    APPLY_XTAG(testing_fast_tags, "fast");
    ADD_TEST(testing_fast_tags);

    // No tags should affect this test case
    ADD_TEST(testing_no_tags);
} // end of group
