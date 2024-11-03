/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/test/framework.h>   // basic test tools
#include <fossil/unittest/assume.h>      // assertion tools
#include <fossil/benchmark/framework.h>  // benchmark tools

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
FOSSIL_TEST_CASE(bubble_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(bubble_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(bubble_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    bubble_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// Test cases for Insertion Sort
FOSSIL_TEST_CASE(insertion_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8, 6, 3, 7};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(insertion_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1, 5, 2, 4};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(insertion_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7, 5, 9, 3};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    insertion_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// Test cases for Selection Sort
FOSSIL_TEST_CASE(selection_sort_case_1) {
    // Test case 1
    int data[] = {5, 1, 4, 2, 8, 6, 3, 7, 9};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(selection_sort_case_2) {
    // Test case 2
    int data[] = {9, 6, 7, 3, 1, 5, 2, 4, 8};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

FOSSIL_TEST_CASE(selection_sort_case_3) {
    // Test case 3
    int data[] = {8, 2, 4, 1, 7, 5, 9, 3, 6};
    size_t size = sizeof(data) / sizeof(data[0]);
    TEST_BENCHMARK();
    selection_sort(data, size);
    TEST_DURATION_SEC(TEST_CURRENT_TIME(), 1.0);
}

// Test Case for Bubble Sort with Small Input
FOSSIL_TEST_CASE(benchmark_bubble_sort_small) {
    const int size = 100;
    int arr[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    
    MARK_BENCHMARK(bench_bubble_sort_small);
    {
        MARK_SCOPED(bench_bubble_sort_small);
        bubble_sort(arr, size);
    }
    MARK_REPORT(bench_bubble_sort_small);

    for (int i = 0; i < size - 1; ++i) {
        ASSUME_ITS_TRUE(arr[i] <= arr[i + 1]);
    }
}

// Test Case for Bubble Sort with Medium Input
FOSSIL_TEST_CASE(benchmark_bubble_sort_medium) {
    const int size = 1000;
    int arr[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    
    MARK_BENCHMARK(bench_bubble_sort_medium);
    {
        MARK_SCOPED(bench_bubble_sort_medium);
        bubble_sort(arr, size);
    }
    MARK_REPORT(bench_bubble_sort_medium);

    for (int i = 0; i < size - 1; ++i) {
        ASSUME_ITS_TRUE(arr[i] <= arr[i + 1]);
    }
}

// Test Case for Bubble Sort with Large Input
FOSSIL_TEST_CASE(benchmark_bubble_sort_large) {
    const int size = 10000;
    int arr[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    
    MARK_BENCHMARK(bench_bubble_sort_large);
    {
        MARK_SCOPED(bench_bubble_sort_large);
        bubble_sort(arr, size);
    }
    MARK_REPORT(bench_bubble_sort_large);

    for (int i = 0; i < size - 1; ++i) {
        ASSUME_ITS_TRUE(arr[i] <= arr[i + 1]);
    }
}

// XUNIT-GROUP
FOSSIL_TEST_GROUP(benchmark_group) {
    APPLY_MARK(bubble_sort_case_1, "ghost");
    ADD_TEST(bubble_sort_case_1);
    APPLY_MARK(bubble_sort_case_2, "ghost");
    ADD_TEST(bubble_sort_case_2);
    APPLY_MARK(bubble_sort_case_3, "ghost");
    ADD_TEST(bubble_sort_case_3);

    APPLY_MARK(insertion_sort_case_1, "ghost");
    ADD_TEST(insertion_sort_case_1);
    APPLY_MARK(insertion_sort_case_2, "ghost");
    ADD_TEST(insertion_sort_case_2);
    APPLY_MARK(insertion_sort_case_3, "ghost");
    ADD_TEST(insertion_sort_case_3);

    APPLY_MARK(selection_sort_case_1, "ghost");
    ADD_TEST(selection_sort_case_1);
    APPLY_MARK(selection_sort_case_2, "ghost");
    ADD_TEST(selection_sort_case_2);
    APPLY_MARK(selection_sort_case_3, "ghost");
    ADD_TEST(selection_sort_case_3);

    ADD_TEST(benchmark_bubble_sort_small);
    ADD_TEST(benchmark_bubble_sort_medium);
    ADD_TEST(benchmark_bubble_sort_large);
}
