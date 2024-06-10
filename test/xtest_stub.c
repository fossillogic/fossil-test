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

#include <fossil/mockup/stub.h> // library under test

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

XTEST(xmock_try_stub_create_and_erase) {
    // Create a stub object
    xmock_stub_t *stub = xmock_stub_create("test_function");
    ASSUME_NOT_CNULL(stub);

    // Check the function name
    ASSUME_ITS_EQUAL_CSTR("test_function", stub->function_name);

    // Erase the stub object
    xmock_stub_erase(stub);
}

XTEST(xmock_try_stub_set_and_call) {
    // Create a stub object
    xmock_stub_t *stub = xmock_stub_create("test_function");
    ASSUME_NOT_CNULL(stub);

    // Set return values
    int return_val1 = 42;
    int return_val2 = 99;
    xmock_stub_set_return_values(stub, 2, &return_val1, &return_val2);

    // Simulate calling the stub function and verify return values
    int *ret_val = (int *)xmock_stub_call(stub);
    ASSUME_ITS_EQUAL_I32(return_val1, *ret_val);
    ret_val = (int *)xmock_stub_call(stub);
    ASSUME_ITS_EQUAL_I32(return_val2, *ret_val);

    // Erase the stub object
    xmock_stub_erase(stub);
}

XTEST(xmock_try_stub_verify_call_count) {
    // Create a stub object
    xmock_stub_t *stub = xmock_stub_create("test_function");
    ASSUME_NOT_CNULL(stub);

    // Set return values and call the stub function
    int return_val = 42;
    xmock_stub_set_return_values(stub, 1, &return_val);
    xmock_stub_call(stub);
    xmock_stub_call(stub);

    // Verify the call count
    ASSUME_ITS_TRUE(xmock_stub_verify_call_count(stub, 2));
    ASSUME_ITS_FALSE(xmock_stub_verify_call_count(stub, 1));

    // Erase the stub object
    xmock_stub_erase(stub);
}

XTEST(xmock_try_stub_reset) {
    // Create a stub object
    xmock_stub_t *stub = xmock_stub_create("test_function");
    ASSUME_NOT_CNULL(stub);

    // Set return values and call the stub function
    int return_val = 42;
    xmock_stub_set_return_values(stub, 1, &return_val);
    xmock_stub_call(stub);

    // Verify the call count
    ASSUME_ITS_TRUE(xmock_stub_verify_call_count(stub, 1));

    // Reset the stub object
    xmock_stub_reset(stub);

    // Verify the reset
    ASSUME_ITS_EQUAL_I32(0, stub->call_count);
    ASSUME_NOT_CNULL(stub->return_values);

    // Erase the stub object
    xmock_stub_erase(stub);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
XTEST_DEFINE_POOL(xmock_stub_group) {
    ADD_TEST(xmock_try_stub_create_and_erase);
    ADD_TEST(xmock_try_stub_set_and_call);
    ADD_TEST(xmock_try_stub_verify_call_count);
    ADD_TEST(xmock_try_stub_reset);
} // end of fixture
