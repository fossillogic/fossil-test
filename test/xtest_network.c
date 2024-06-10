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

#include <fossil/mockup/network.h> // library under test

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

XTEST(xmock_try_network_create_and_erase) {
    // Create a network mock object
    xmock_network_t *network = xmock_network_create("test_assume_host", "GET /", "200 OK");
    ASSUME_NOT_CNULL(network);

    // Check the host, request, and response
    ASSUME_ITS_EQUAL_CSTR("test_assume_host", network->host);
    ASSUME_ITS_EQUAL_CSTR("GET /", network->request);
    ASSUME_ITS_EQUAL_CSTR("200 OK", network->response);

    // Erase the network mock object
    xmock_network_erase(network);
}

XTEST(xmock_try_network_request) {
    // Create a network mock object
    xmock_network_t *network = xmock_network_create("test_assume_host", "GET /", "200 OK");
    ASSUME_NOT_CNULL(network);

    // Perform a network request
    const char *response = xmock_network_request(network, "GET /");
    ASSUME_ITS_EQUAL_CSTR("200 OK", response);

    // Erase the network mock object
    xmock_network_erase(network);
}

XTEST(xmock_try_network_request_with_different_request) {
    // Create a network mock object
    xmock_network_t *network = xmock_network_create("test_assume_host", "POST /", "201 Created");
    ASSUME_NOT_CNULL(network);

    // Perform a network request
    const char *response = xmock_network_request(network, "POST /");
    ASSUME_ITS_EQUAL_CSTR("201 Created", response);

    // Erase the network mock object
    xmock_network_erase(network);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
XTEST_DEFINE_POOL(xmock_network_group) {
    ADD_TEST(xmock_try_network_create_and_erase);
    ADD_TEST(xmock_try_network_request);
    ADD_TEST(xmock_try_network_request_with_different_request);
} // end of fixture
