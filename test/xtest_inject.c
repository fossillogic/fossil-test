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

#include <fossil/mockup/inject.h> // library under test

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

FOSSIL_TEST(fossil_mockup_try_inject_create_and_erase) {
    // Create an injected dependency object
    int replacement_object = 42;
    fossil_mockup_inject_t *inject = fossil_mockup_inject_create("test_dependency", &replacement_object);
    ASSUME_NOT_CNULL(inject);

    // Check the dependency name and replacement object
    ASSUME_ITS_EQUAL_CSTR("test_dependency", inject->dependency_name);
    ASSUME_ITS_EQUAL_PTR(&replacement_object, inject->replacement_object);

    // Erase the injected dependency object
    fossil_mockup_inject_erase(inject);
}

FOSSIL_TEST(fossil_mockup_try_inject_get_replacement) {
    // Create an injected dependency object
    int replacement_object = 42;
    fossil_mockup_inject_t *inject = fossil_mockup_inject_create("test_dependency", &replacement_object);
    ASSUME_NOT_CNULL(inject);

    // Get the replacement object
    void *retrieved_object = fossil_mockup_inject_get_replacement(inject);
    ASSUME_ITS_EQUAL_PTR(&replacement_object, retrieved_object);

    // Erase the injected dependency object
    fossil_mockup_inject_erase(inject);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_inject_group) {
    ADD_TEST(fossil_mockup_try_inject_create_and_erase);
    ADD_TEST(fossil_mockup_try_inject_get_replacement);
} // end of fixture
