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

#include <fossil/mockup/output.h> // library under test

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

FOSSIL_TEST(fossil_mockup_try_output_create_and_erase) {
    // Create an output mock object
    fossil_mockup_output_t *output = fossil_mockup_output_create("test_function");
    ASSUME_NOT_CNULL(output);

    // Check the function name
    ASSUME_ITS_EQUAL_CSTR("test_function", output->function_name);

    // Erase the output mock object
    fossil_mockup_output_erase(output);
}

FOSSIL_TEST(fossil_mockup_try_output_capture) {
    // Create an output mock object
    fossil_mockup_output_t *output = fossil_mockup_output_create("test_function");
    ASSUME_NOT_CNULL(output);

    // Capture output
    fossil_mockup_output_capture(output, "output1");
    ASSUME_ITS_EQUAL_I32(1, output->call_count);
    ASSUME_ITS_EQUAL_CSTR("output1", output->captured_outputs[0]);

    // Capture another output
    fossil_mockup_output_capture(output, "output2");
    ASSUME_ITS_EQUAL_I32(2, output->call_count);
    ASSUME_ITS_EQUAL_CSTR("output2", output->captured_outputs[1]);

    // Erase the output mock object
    fossil_mockup_output_erase(output);
}

FOSSIL_TEST(fossil_mockup_try_output_verify) {
    // Create an output mock object
    fossil_mockup_output_t *output = fossil_mockup_output_create("test_function");
    ASSUME_NOT_CNULL(output);

    // Capture output
    fossil_mockup_output_capture(output, "output1");

    // Verify output
    ASSUME_ITS_TRUE(fossil_mockup_output_verify(output, "output1", 0));

    // Verify non-existent output
    ASSUME_ITS_FALSE(fossil_mockup_output_verify(output, "nonexistent", 0));

    // Erase the output mock object
    fossil_mockup_output_erase(output);
}

FOSSIL_TEST(fossil_mockup_try_output_verify_call_count) {
    // Create an output mock object
    fossil_mockup_output_t *output = fossil_mockup_output_create("test_function");
    ASSUME_NOT_CNULL(output);

    // Capture outputs
    fossil_mockup_output_capture(output, "output1");
    fossil_mockup_output_capture(output, "output2");

    // Verify call count
    ASSUME_ITS_TRUE(fossil_mockup_output_verify_call_count(output, 2));

    // Erase the output mock object
    fossil_mockup_output_erase(output);
}

FOSSIL_TEST(fossil_mockup_try_output_reset) {
    // Create an output mock object
    fossil_mockup_output_t *output = fossil_mockup_output_create("test_function");
    ASSUME_NOT_CNULL(output);

    // Capture outputs
    fossil_mockup_output_capture(output, "output1");
    fossil_mockup_output_capture(output, "output2");

    // Verify call count
    ASSUME_ITS_TRUE(fossil_mockup_output_verify_call_count(output, 2));

    // Reset the output mock object
    fossil_mockup_output_reset(output);

    // Verify reset
    ASSUME_ITS_EQUAL_I32(0, output->call_count);
    ASSUME_ITS_EQUAL_I32(0, output->output_count);

    // Erase the output mock object
    fossil_mockup_output_erase(output);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_output_group) {
    ADD_TEST(fossil_mockup_try_output_create_and_erase);
    ADD_TEST(fossil_mockup_try_output_capture);
    ADD_TEST(fossil_mockup_try_output_verify);
    ADD_TEST(fossil_mockup_try_output_verify_call_count);
    ADD_TEST(fossil_mockup_try_output_reset);
} // end of fixture
