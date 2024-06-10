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

FOSSIL_TEST_DATA(sample_data) {
    int x;
    int y;
} sample_data;

// Fixture setup and teardown procedures
FOSSIL_FIXTURE(sample_fixture);

FOSSIL_SETUP(sample_fixture) {
    sample_data.x = 42;
    sample_data.y = 20;
} // end of setup

FOSSIL_TEARDOWN(sample_fixture) {
    // Teardown code goes here
} // end of teardown

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(xassert_with_fixture_run_of_int) {
    // Test cases
    TEST_ASSERT(sample_data.x == 42, "Should have passed the test case");
    TEST_ASSERT(sample_data.y == 20, "Should have passed the test case");
    TEST_ASSERT(sample_data.x != sample_data.y, "Should have passed the test case");
    TEST_ASSERT(sample_data.y < sample_data.x, "Should have passed the test case");
    TEST_ASSERT(sample_data.y <= sample_data.x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_with_fixture_run_of_int8) {
    TEST_ASSERT((int8_t)sample_data.x == 42, "Should have passed the test case");
    TEST_ASSERT((int8_t)sample_data.y == 20, "Should have passed the test case");
    TEST_ASSERT((int8_t)sample_data.x != (int8_t)sample_data.y, "Should have passed the test case");
    TEST_ASSERT((int8_t)sample_data.y < (int8_t)sample_data.x, "Should have passed the test case");
    TEST_ASSERT((int8_t)sample_data.y <= (int8_t)sample_data.x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_with_fixture_run_of_int16) {
    TEST_ASSERT((int16_t)sample_data.x == 42, "Should have passed the test case");
    TEST_ASSERT((int16_t)sample_data.y == 20, "Should have passed the test case");
    TEST_ASSERT((int16_t)sample_data.x != (int16_t)sample_data.y, "Should have passed the test case");
    TEST_ASSERT((int16_t)sample_data.y < (int16_t)sample_data.x, "Should have passed the test case");
    TEST_ASSERT((int16_t)sample_data.y <= (int16_t)sample_data.x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_with_fixture_run_of_int32) {
    TEST_ASSERT((int32_t)sample_data.x == 42, "Should have passed the test case");
    TEST_ASSERT((int32_t)sample_data.y == 20, "Should have passed the test case");
    TEST_ASSERT((int32_t)sample_data.x != (int32_t)sample_data.y, "Should have passed the test case");
    TEST_ASSERT((int32_t)sample_data.y < (int32_t)sample_data.x, "Should have passed the test case");
    TEST_ASSERT((int32_t)sample_data.y <= (int32_t)sample_data.x, "Should have passed the test case");
} // end case

FOSSIL_TEST(xassert_with_fixture_run_of_int64) {
    TEST_ASSERT((int64_t)sample_data.x == 42, "Should have passed the test case");
    TEST_ASSERT((int64_t)sample_data.y == 20, "Should have passed the test case");
    TEST_ASSERT((int64_t)sample_data.x != (int64_t)sample_data.y, "Should have passed the test case");
    TEST_ASSERT((int64_t)sample_data.y < (int64_t)sample_data.x, "Should have passed the test case");
    TEST_ASSERT((int64_t)sample_data.y <= (int64_t)sample_data.x, "Should have passed the test case");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fixture_test_group) {
    ADD_TESTF(xassert_with_fixture_run_of_int, sample_fixture);
    ADD_TESTF(xassert_with_fixture_run_of_int8, sample_fixture);
    ADD_TESTF(xassert_with_fixture_run_of_int16, sample_fixture);
    ADD_TESTF(xassert_with_fixture_run_of_int32, sample_fixture);
    ADD_TESTF(xassert_with_fixture_run_of_int64, sample_fixture);
} // end of group
