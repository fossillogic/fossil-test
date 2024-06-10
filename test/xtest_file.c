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

#include <fossil/mockup/file.h> // library under test

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

XTEST(xmock_try_file_create_and_erase) {
    // Create a file mock object
    xmock_file_t *file = xmock_file_create("test_file.txt", "Hello, World!");
    ASSUME_NOT_CNULL(file);

    // Check the filename and content
    ASSUME_ITS_EQUAL_CSTR("test_file.txt", file->filename);
    ASSUME_ITS_EQUAL_CSTR("Hello, World!", file->content);

    // Erase the file mock object
    xmock_file_erase(file);
}

XTEST(xmock_try_file_read) {
    // Create a file mock object
    xmock_file_t *file = xmock_file_create("test_file.txt", "Hello, World!");
    ASSUME_NOT_CNULL(file);

    char buffer[20];
    size_t read_size = xmock_file_read(buffer, 1, 5, file);
    buffer[read_size] = '\0'; // Null-terminate the read string

    // Verify the read content
    ASSUME_ITS_EQUAL_SIZE(5, read_size);
    ASSUME_ITS_EQUAL_CSTR("Hello", buffer);

    // Erase the file mock object
    xmock_file_erase(file);
}

XTEST(xmock_try_file_write) {
    // Create a file mock object
    xmock_file_t *file = xmock_file_create("test_file.txt", "");
    ASSUME_NOT_CNULL(file);

    const char *write_content = "Hello";
    size_t write_size = xmock_file_write(write_content, 1, strlen(write_content), file);

    // Verify the written content
    ASSUME_ITS_EQUAL_SIZE(strlen(write_content), write_size);
    ASSUME_ITS_EQUAL_CSTR("Hello", file->content);

    // Erase the file mock object
    xmock_file_erase(file);
}

XTEST(xmock_try_file_seek_and_read) {
    // Create a file mock object
    xmock_file_t *file = xmock_file_create("test_file.txt", "Hello, World!");
    ASSUME_NOT_CNULL(file);

    // Seek to position 7 (after "Hello, ")
    int seek_result = xmock_file_seek(file, 7, SEEK_SET);
    ASSUME_ITS_EQUAL_I32(0, seek_result);

    char buffer[20];
    size_t read_size = xmock_file_read(buffer, 1, 5, file);
    buffer[read_size] = '\0'; // Null-terminate the read string

    // Verify the read content
    ASSUME_ITS_EQUAL_SIZE(5, read_size);
    ASSUME_ITS_EQUAL_CSTR("World", buffer);

    // Erase the file mock object
    xmock_file_erase(file);
}

XTEST(xmock_try_file_reset) {
    // Create a file mock object
    xmock_file_t *file = xmock_file_create("test_file.txt", "Hello, World!");
    ASSUME_NOT_CNULL(file);

    char buffer[20];
    size_t read_size = xmock_file_read(buffer, 1, 5, file);
    buffer[read_size] = '\0'; // Null-terminate the read string

    // Verify the read content
    ASSUME_ITS_EQUAL_SIZE(5, read_size);
    ASSUME_ITS_EQUAL_CSTR("Hello", buffer);

    // Reset the file object
    xmock_file_reset(file);

    // Verify that the file position is reset
    read_size = xmock_file_read(buffer, 1, 5, file);
    buffer[read_size] = '\0'; // Null-terminate the read string
    ASSUME_ITS_EQUAL_SIZE(5, read_size);
    ASSUME_ITS_EQUAL_CSTR("Hello", buffer);

    // Erase the file mock object
    xmock_file_erase(file);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
XTEST_DEFINE_POOL(xmock_file_group) {
    ADD_TEST(xmock_try_file_create_and_erase);
    ADD_TEST(xmock_try_file_read);
    ADD_TEST(xmock_try_file_write);
    ADD_TEST(xmock_try_file_seek_and_read);
    ADD_TEST(xmock_try_file_reset);
} // end of fixture
