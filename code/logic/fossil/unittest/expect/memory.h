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
#ifndef FOSSIL_TEST_EXPECT_MEMORY_TYPE_H
#define FOSSIL_TEST_EXPECT_MEMORY_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Null pointer assertions (_CNULL)

// ITS set
#define EXPECT_ITS_CNULL(actual) \
    TEST_EXPECT((actual) == xnull, "Expected " #actual " to be xnull")

#define EXPECT_NOT_CNULL(actual) \
    TEST_EXPECT((actual) != xnull, "Expected " #actual " to not be xnull")

// General pointer assertions (_PTR)

// ITS set
#define EXPECT_ITS_EQUAL_PTR(actual, expected) \
    TEST_EXPECT((actual) == (expected), "Expected pointer " #actual " to be equal to pointer " #expected " ")

#define EXPECT_NOT_EQUAL_PTR(actual, expected) \
    TEST_EXPECT((actual) != (expected), "Expected pointer " #actual " to not be equal to pointer " #expected " ")

// Size_t assertions

// Equal
#define EXPECT_ITS_EQUAL_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) == (size_t)(expected), "Expected " #actual " to be equal to " #expected)

// Less than
#define EXPECT_ITS_LESS_THAN_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) < (size_t)(expected), "Expected " #actual " to be less than " #expected)

// More than
#define EXPECT_ITS_MORE_THAN_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) > (size_t)(expected), "Expected " #actual " to be more than " #expected)

// Less or equal
#define EXPECT_ITS_LESS_OR_EQUAL_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) <= (size_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

// More or equal
#define EXPECT_ITS_MORE_OR_EQUAL_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) >= (size_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

// Not equal
#define EXPECT_NOT_EQUAL_SIZE(actual, expected) \
    TEST_EXPECT((size_t)(actual) != (size_t)(expected), "Expected " #actual " to not be equal to " #expected)

#ifdef __cplusplus
}
#endif

#endif
