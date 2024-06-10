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

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Algorithm 1: Bubble Sort
void bubble_sort(int *array, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (*(array + j) > *(array + j + 1)) {
                int temp = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = temp;
            }
        }
    }
}

// Algorithm 2: Insertion Sort
void insertion_sort(int *array, size_t size) {
    int key, j;
    for (size_t i = 1; i < size; ++i) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// Algorithm 3: Selection Sort
void selection_sort(int *array, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        int temp = array[min_index];
        array[min_index] = array[i];
        array[i] = temp;
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Test cases for Bubble Sort
XTEST(bubble_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(bubble_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(bubble_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// Test cases for Insertion Sort
XTEST(insertion_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8, 6, 3, 7};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(insertion_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1, 5, 2, 4};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(insertion_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7, 5, 9, 3};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// Test cases for Selection Sort
XTEST(selection_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8, 6, 3, 7, 9};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(selection_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1, 5, 2, 4, 8};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

XTEST(selection_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7, 5, 9, 3, 6};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// XUNIT-GROUP
XTEST_DEFINE_POOL(benchmark_group) {
    ADD_TEST(bubble_sort_case_1);
    ADD_TEST(bubble_sort_case_2);
    ADD_TEST(bubble_sort_case_3);

    ADD_TEST(insertion_sort_case_1);
    ADD_TEST(insertion_sort_case_2);
    ADD_TEST(insertion_sort_case_3);

    ADD_TEST(selection_sort_case_1);
    ADD_TEST(selection_sort_case_2);
    ADD_TEST(selection_sort_case_3);
}
