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
#ifndef FOSSIL_TEST_ASSUME_BOOLEAN_TYPE_H
#define FOSSIL_TEST_ASSUME_BOOLEAN_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Boolean ITS assertions
#define ASSUME_ITS_TRUE(actual) \
    TEST_ASSUME((actual), "Expected " #actual " to be true")

#define ASSUME_ITS_FALSE(actual) \
    TEST_ASSUME(!(actual), "Expected " #actual " to be false")

// Boolean NOT assertions
#define ASSUME_NOT_TRUE(actual) \
    TEST_ASSUME(!(actual), "Expected " #actual " to not be true")

#define ASSUME_NOT_FALSE(actual) \
    TEST_ASSUME((actual), "Expected " #actual " to not be false")

#ifdef __cplusplus
}
#endif

#endif
