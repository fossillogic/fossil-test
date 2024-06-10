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
#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

#include <fossil/mockup/fake.h> // library under test
#include <fossil/xmock.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Mocked function to be replaced by the fake
XMOCK_FUNC_DEF(void, mocked_function, void) {
    // Some mocked behavior
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST(xmock_fake_create_and_erase) {
    // Create a fake object
    xmock_fake_t *fake = xmock_fake_create("mocked_function", xmock_mocked_function);
    ASSUME_NOT_CNULL(fake);

    // Erase the fake object
    xmock_fake_erase(fake);
}

XTEST(xmock_fake_called) {
    // Create a fake object
    xmock_fake_t *fake = xmock_fake_create("mocked_function", xmock_mocked_function);
    ASSUME_NOT_CNULL(fake);

    // Call the fake function
    xmock_fake_call(fake);

    // Additional asserts can be added to verify the behavior

    // Erase the fake object
    xmock_fake_erase(fake);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
XTEST_DEFINE_POOL(xmock_fake_group) {
    ADD_TEST(xmock_fake_create_and_erase);
    ADD_TEST(xmock_fake_called);
} // end of fixture
