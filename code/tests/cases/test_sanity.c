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
#include <fossil/pizza/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_sanity_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_sanity_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_sanity_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_sanity_sys_execute) {
    const char *command = "echo Hello, Fossil!";
    int result = FOSSIL_SANITY_SYS_EXECUTE(command);

    // Test cases
    ASSUME_ITS_EQUAL_I32(result, 0); // Assuming the command executes successfully
} // end case

FOSSIL_TEST(c_sanity_sys_getpid) {
    int pid = FOSSIL_SANITY_SYS_GETPID();

    // Test cases
    ASSUME_NOT_EQUAL_I32(pid, 0); // Process ID should not be 0
} // end case

FOSSIL_TEST(c_sanity_sys_create_file) {
    const char *filename = "test_file.txt";
    int result = FOSSIL_SANITY_SYS_CREATE_FILE(filename);

    // Test cases
    ASSUME_ITS_EQUAL_I32(result, 0); // File creation should succeed
    ASSUME_ITS_EQUAL_I32(FOSSIL_SANITY_SYS_FILE_EXISTS(filename), 1); // File should exist

    // Cleanup
    remove(filename);
} // end case

FOSSIL_TEST(c_sanity_sys_file_exists) {
    const char *filename = "test_file_exists.txt";

    // Ensure file does not exist initially
    ASSUME_ITS_EQUAL_I32(FOSSIL_SANITY_SYS_FILE_EXISTS(filename), 0);

    // Create the file
    FILE *file = fopen(filename, "w");
    ASSUME_NOT_CNULL(file);
    fclose(file);

    // Test cases
    ASSUME_ITS_EQUAL_I32(FOSSIL_SANITY_SYS_FILE_EXISTS(filename), 1);

    // Cleanup
    remove(filename);
} // end case



// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_sanity_test_cases) {
    FOSSIL_TEST_ADD(c_sanity_suite, c_sanity_sys_execute);
    FOSSIL_TEST_ADD(c_sanity_suite, c_sanity_sys_getpid);
    FOSSIL_TEST_ADD(c_sanity_suite, c_sanity_sys_create_file);
    FOSSIL_TEST_ADD(c_sanity_suite, c_sanity_sys_file_exists);

    FOSSIL_TEST_REGISTER(c_sanity_suite);
} // end of group
