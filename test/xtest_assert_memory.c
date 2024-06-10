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
#include <fossil/xassert/memory.h> // library under test

#include <fossil/xtest.h>   // basic test tools

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

XTEST(test_null_pointer_its) {
    int* ptr = xnullptr;
    ASSERT_ITS_CNULL(ptr);
}

XTEST(test_not_null_pointer) {
    int* ptr = (int*)malloc(sizeof(int));
    ASSERT_NOT_CNULL(ptr);
    free(ptr);
}

XTEST(test_equal_pointers) {
    int* ptr1 = (int*)malloc(sizeof(int));
    int* ptr2 = ptr1;
    ASSERT_ITS_EQUAL_PTR(ptr1, ptr2);
    free(ptr1);
}

XTEST(test_not_equal_pointers) {
    int* ptr1 = (int*)malloc(sizeof(int));
    int* ptr2 = (int*)malloc(sizeof(int));
    ASSERT_NOT_EQUAL_PTR(ptr1, ptr2);
    free(ptr1);
    free(ptr2);
}

XTEST(test_size_equal) {
    size_t size1 = 10;
    size_t size2 = 10;
    ASSERT_ITS_EQUAL_SIZE(size1, size2);
}

XTEST(test_size_not_equal) {
    size_t size1 = 10;
    size_t size2 = 20;
    ASSERT_NOT_EQUAL_SIZE(size1, size2);
}

XTEST(test_size_less_than) {
    size_t size1 = 10;
    size_t size2 = 20;
    ASSERT_ITS_LESS_THAN_SIZE(size1, size2);
}

XTEST(test_size_more_than) {
    size_t size1 = 20;
    size_t size2 = 10;
    ASSERT_ITS_MORE_THAN_SIZE(size1, size2);
}

XTEST(test_size_less_or_equal) {
    size_t size1 = 10;
    size_t size2 = 10;
    ASSERT_ITS_LESS_OR_EQUAL_SIZE(size1, size2);
}

XTEST(test_size_more_or_equal) {
    size_t size1 = 10;
    size_t size2 = 10;
    ASSERT_ITS_MORE_OR_EQUAL_SIZE(size1, size2);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

XTEST_DEFINE_POOL(memory_asserts_assert_group) {
    ADD_TEST(test_null_pointer_its);
    ADD_TEST(test_not_null_pointer);
    ADD_TEST(test_equal_pointers);
    ADD_TEST(test_not_equal_pointers);
    ADD_TEST(test_size_equal);
    ADD_TEST(test_size_not_equal);
    ADD_TEST(test_size_less_than);
    ADD_TEST(test_size_more_than);
    ADD_TEST(test_size_less_or_equal);
    ADD_TEST(test_size_more_or_equal);
} // end of fixture
