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
#ifndef FOSSIL_TEST_ASSUME_TYPE_H
#define FOSSIL_TEST_ASSUME_TYPE_H

#include "framework.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// Used in floating-point asserts
#define FOSSIL_TEST_FLOAT_EPSILON 1e-6
#define FOSSIL_TEST_DOUBLE_EPSILON 1e-9

// **************************************************
//
// Boolean assumtions
//
// **************************************************

/**
 * @brief Assumes that the given boolean expression is true.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_ITS_TRUE(actual) \
    FOSSIL_TEST_ASSUME((actual), "Expected " #actual " to be true")

/**
 * @brief Assumes that the given boolean expression is false.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_ITS_FALSE(actual) \
    FOSSIL_TEST_ASSUME(!(actual), "Expected " #actual " to be false")

/**
 * @brief Assumes that the given boolean expression is not true.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_NOT_TRUE(actual) \
    FOSSIL_TEST_ASSUME(!(actual), "Expected " #actual " to not be true")

/**
 * @brief Assumes that the given boolean expression is not false.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_NOT_FALSE(actual) \
    FOSSIL_TEST_ASSUME((actual), "Expected " #actual " to not be false")

// **************************************************
//
// Floating point assumtions
//
// **************************************************

// Double equality check with tolerance
/**
 * @brief Assumes that the given double values are equal within a specified tolerance.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 * @param tol The tolerance within which the values should be considered equal.
 */
#define ASSUME_ITS_EQUAL_F64(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabs((actual) - (expected)) <= (tol), "Expected " #actual " to be equal to " #expected " within tolerance " #tol)

/**
 * @brief Assumes that the given double value is less than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_LESS_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given double value is more than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_MORE_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given double value is less than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given double value is more than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given double values are not equal within a specified tolerance.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 * @param tol The tolerance within which the values should not be considered equal.
 */
#define ASSUME_NOT_EQUAL_F64(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabs((actual) - (expected)) > (tol), "Expected " #actual " to not be equal to " #expected " within tolerance " #tol)

/**
 * @brief Assumes that the given double value is not less than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_LESS_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given double value is not more than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_MORE_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given double value is not less than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given double value is not more than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), "Expected " #actual " to not be more than or equal to " #expected)

// Float equality check with tolerance
/**
 * @brief Assumes that the given float values are equal within a specified tolerance.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 * @param tol The tolerance within which the values should be considered equal.
 */
#define ASSUME_ITS_EQUAL_F32(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabsf((actual) - (expected)) <= (tol), "Expected " #actual " to be equal to " #expected " within tolerance " #tol)

/**
 * @brief Assumes that the given float value is less than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_LESS_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given float value is more than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_MORE_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given float value is less than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given float value is more than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given float values are not equal within a specified tolerance.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 * @param tol The tolerance within which the values should not be considered equal.
 */
#define ASSUME_NOT_EQUAL_F32(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabsf((actual) - (expected)) > (tol), "Expected " #actual " to not be equal to " #expected " within tolerance " #tol)

/**
 * @brief Assumes that the given float value is not less than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_LESS_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given float value is not more than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_MORE_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given float value is not less than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given float value is not more than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), "Expected " #actual " to not be more than or equal to " #expected)

// Float NaN and Infinity checks
/**
 * @brief Assumes that the given float value is NaN (Not a Number).
 *
 * @param actual The actual float value.
 */
#define ASSUME_ITS_NAN_F32(actual) \
    FOSSIL_TEST_ASSUME(isnan(actual), "Expected " #actual " to be NaN")

/**
 * @brief Assumes that the given float value is infinity.
 *
 * @param actual The actual float value.
 */
#define ASSUME_ITS_INF_F32(actual) \
    FOSSIL_TEST_ASSUME(isinf(actual), "Expected " #actual " to be infinity")

// Double NaN and Infinity checks
/**
 * @brief Assumes that the given double value is NaN (Not a Number).
 *
 * @param actual The actual double value.
 */
#define ASSUME_ITS_NAN_F64(actual) \
    FOSSIL_TEST_ASSUME(isnan(actual), "Expected " #actual " to be NaN")

/**
 * @brief Assumes that the given double value is infinity.
 *
 * @param actual The actual double value.
 */
#define ASSUME_ITS_INF_F64(actual) \
    FOSSIL_TEST_ASSUME(isinf(actual), "Expected " #actual " to be infinity")

// **************************************************
//
// Numaric assumtions
//
// **************************************************

/**
 * @brief Assumes that the given 8-bit octal values are equal.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is less than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is more than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit octal values are not equal.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is not less than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is not more than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal values are equal.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is less than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is more than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal values are not equal.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is not less than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is not more than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal values are equal.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is less than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is more than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal values are not equal.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is not less than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is not more than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal values are equal.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is less than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is more than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal values are not equal.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is not less than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is not more than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// Hexadecimal assumtions

/**
 * @brief Assumes that the given 8-bit hexadecimal values are equal.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal values are not equal.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal values are equal.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal values are not equal.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal values are equal.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal values are not equal.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal values are equal.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal values are not equal.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer values are equal.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) == (int8_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is less than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is more than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer values are not equal.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) != (int8_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is not less than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is not more than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer values are equal.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) == (int16_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is less than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is more than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer values are not equal.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) != (int16_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is not less than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is not more than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer values are equal.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) == (int32_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is less than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is more than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer values are not equal.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) != (int32_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is not less than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is not more than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer values are equal.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) == (int64_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is less than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is more than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer values are not equal.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) != (int64_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is not less than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is not more than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer values are equal.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer values are not equal.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer values are equal.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer values are not equal.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer values are equal.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer values are not equal.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer values are equal.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer values are not equal.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// **************************************************
//
// Memory allocation assumptions
//
// **************************************************

/**
 * @brief Assumes that the given memory is zeroed.
 *
 * @param ptr A pointer to the memory to check.
 * @param size The size of the memory to check.
 */
#define ASSUME_ITS_ZERO_MEMORY(ptr, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_zero((ptr), (size)), "Expected memory at " #ptr " to be zeroed")

/**
 * @brief Assumes that the given memory is not zeroed.
 *
 * @param ptr A pointer to the memory to check.
 * @param size The size of the memory to check.
 */
#define ASSUME_NOT_ZERO_MEMORY(ptr, size) \
    FOSSIL_TEST_ASSUME(!pizza_sys_memory_zero((ptr), (size)), "Expected memory at " #ptr " to not be zero")

/**
 * @brief Assumes that the given memory regions are equal.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) == 0, "Expected memory regions " #ptr1 " and " #ptr2 " to be equal")

/**
 * @brief Assumes that the given memory regions are not equal.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_NOT_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) != 0, "Expected memory regions " #ptr1 " and " #ptr2 " to not be equal")

/**
 * @brief Assumes that the given memory region is more than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_MORE_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) > 0, "Expected memory region " #ptr1 " to be more than " #ptr2)

/**
 * @brief Assumes that the given memory region is less than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_LESS_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) < 0, "Expected memory region " #ptr1 " to be less than " #ptr2)

/**
 * @brief Assumes that the given memory region is more than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) >= 0, "Expected memory region " #ptr1 " to be more than or equal to " #ptr2)

/**
 * @brief Assumes that the given memory region is less than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) <= 0, "Expected memory region " #ptr1 " to be less than or equal to " #ptr2)

/**
 * @brief Assumes that the given memory region is not more than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_MORE_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) <= 0, "Expected memory region " #ptr1 " to not be more than " #ptr2)

/**
 * @brief Assumes that the given memory region is not less than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_LESS_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) >= 0, "Expected memory region " #ptr1 " to not be less than " #ptr2)

/**
 * @brief Assumes that the given memory region is not more than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) < 0, "Expected memory region " #ptr1 " to not be more than or equal to " #ptr2)

/**
 * @brief Assumes that the given memory region is not less than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) > 0, "Expected memory region " #ptr1 " to not be less than or equal to " #ptr2)

/**
 * @brief Assumes that the given memory pointer is valid.
 *
 * @param ptr A pointer to the memory to check.
 */
#define ASSUME_ITS_VALID_MEMORY(ptr) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_is_valid((ptr)), "Expected memory pointer " #ptr " to be valid")

/**
 * @brief Assumes that the given memory pointer is not valid.
 *
 * @param ptr A pointer to the memory to check.
 */
#define ASSUME_NOT_VALID_MEMORY(ptr) \
    FOSSIL_TEST_ASSUME(!pizza_sys_memory_is_valid((ptr)), "Expected memory pointer " #ptr " to not be valid")

// **************************************************
//
// Null pointer assumtions (_CNULL)
//
// **************************************************

/**
 * @brief Assumes that the given pointer is cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) == null, "Expected " #actual " to be cnull")

/**
 * @brief Assumes that the given pointer is not cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, "Expected " #actual " to not be cnull")

/**
 * @brief Assumes that the given pointer is cnull.
 * 
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNULLABLE(actual) \
    FOSSIL_TEST_ASSUME((actual) == null, "Expected " #actual " to be cnull")

/**
 * @brief Assumes that the given pointer is not cnull.
 * 
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNULLABLE(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, "Expected " #actual " to not be cnull")

/**
 * @brief Assumes that the given pointer is cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNONNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, "Expected " #actual " to not be cnull")

/**
 * @brief Assumes that the given pointer is not cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNONNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) == null, "Expected " #actual " to be cnull")

/**
 * @brief Assumes that the given condition is likely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_ITS_LIKELY(x) \
    FOSSIL_TEST_ASSUME(likely(x), "Expected " #x " to be likely")

/**
 * @brief Assumes that the given condition is not likely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_NOT_LIKELY(x) \
    FOSSIL_TEST_ASSUME(!likely(x), "Expected " #x " to not be likely")

/**
 * @brief Assumes that the given condition is unlikely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_ITS_UNLIKELY(x) \
    FOSSIL_TEST_ASSUME(unlikely(x), "Expected " #x " to be unlikely")

/**
 * @brief Assumes that the given condition is not unlikely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_NOT_UNLIKELY(x) \
    FOSSIL_TEST_ASSUME(!unlikely(x), "Expected " #x " to not be unlikely")

/**
 * @brief Assumes that the given pointers are equal.
 *
 * @param actual The actual pointer.
 * @param expected The expected pointer.
 */
#define ASSUME_ITS_EQUAL_PTR(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) == (expected), "Expected pointer " #actual " to be equal to pointer " #expected " ")

/**
 * @brief Assumes that the given pointers are not equal.
 *
 * @param actual The actual pointer.
 * @param expected The expected pointer.
 */
#define ASSUME_NOT_EQUAL_PTR(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) != (expected), "Expected pointer " #actual " to not be equal to pointer " #expected " ")

/**
 * @brief Assumes that the given size_t values are equal.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) == (size_t)(expected), "Expected " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given size_t value is less than the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_LESS_THAN_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) < (size_t)(expected), "Expected " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given size_t value is more than the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_MORE_THAN_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) > (size_t)(expected), "Expected " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given size_t value is less than or equal to the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) <= (size_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given size_t value is more than or equal to the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) >= (size_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given size_t values are not equal.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_NOT_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) != (size_t)(expected), "Expected " #actual " to not be equal to " #expected)

// **************************************************
//
// Range assumtions
//
// **************************************************

/**
 * @brief Assumes that the given value is within the specified range.
 *
 * @param value The value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE(value, min, max) \
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given value is not within the specified range.
 *
 * @param value The value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Unsigned integer type assumptions

/**
 * @brief Assumes that the given 8-bit unsigned integer value is within the specified range.
 *
 * @param value The 8-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U8(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not within the specified range.
 *
 * @param value The 8-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U8(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 16-bit unsigned integer value is within the specified range.
 *
 * @param value The 16-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U16(value, min, max) \
    FOSSIL_TEST_ASSUME((uint16_t)(value) >= (uint16_t)(min) && (uint16_t)(value) <= (uint16_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not within the specified range.
 *
 * @param value The 16-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U16(value, min, max) \
    FOSSIL_TEST_ASSUME((uint16_t)(value) < (uint16_t)(min) || (uint16_t)(value) > (uint16_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 32-bit unsigned integer value is within the specified range.
 *
 * @param value The 32-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U32(value, min, max) \
    FOSSIL_TEST_ASSUME((uint32_t)(value) >= (uint32_t)(min) && (uint32_t)(value) <= (uint32_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not within the specified range.
 *
 * @param value The 32-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U32(value, min, max) \
    FOSSIL_TEST_ASSUME((uint32_t)(value) < (uint32_t)(min) || (uint32_t)(value) > (uint32_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 64-bit unsigned integer value is within the specified range.
 *
 * @param value The 64-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U64(value, min, max) \
    FOSSIL_TEST_ASSUME((uint64_t)(value) >= (uint64_t)(min) && (uint64_t)(value) <= (uint64_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not within the specified range.
 *
 * @param value The 64-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U64(value, min, max) \
    FOSSIL_TEST_ASSUME((uint64_t)(value) < (uint64_t)(min) || (uint64_t)(value) > (uint64_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 8-bit integer value is within the specified range.
 *
 * @param value The 8-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I8(value, min, max) \
    FOSSIL_TEST_ASSUME((int8_t)(value) >= (int8_t)(min) && (int8_t)(value) <= (int8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 8-bit integer value is not within the specified range.
 *
 * @param value The 8-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I8(value, min, max) \
    FOSSIL_TEST_ASSUME((int8_t)(value) < (int8_t)(min) || (int8_t)(value) > (int8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 16-bit integer value is within the specified range.
 *
 * @param value The 16-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I16(value, min, max) \
    FOSSIL_TEST_ASSUME((int16_t)(value) >= (int16_t)(min) && (int16_t)(value) <= (int16_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 16-bit integer value is not within the specified range.
 *
 * @param value The 16-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I16(value, min, max) \
    FOSSIL_TEST_ASSUME((int16_t)(value) < (int16_t)(min) || (int16_t)(value) > (int16_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 32-bit integer value is within the specified range.
 *
 * @param value The 32-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I32(value, min, max) \
    FOSSIL_TEST_ASSUME((int32_t)(value) >= (int32_t)(min) && (int32_t)(value) <= (int32_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 32-bit integer value is not within the specified range.
 *
 * @param value The 32-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I32(value, min, max) \
    FOSSIL_TEST_ASSUME((int32_t)(value) < (int32_t)(min) || (int32_t)(value) > (int32_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 64-bit integer value is within the specified range.
 *
 * @param value The 64-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I64(value, min, max) \
    FOSSIL_TEST_ASSUME((int64_t)(value) >= (int64_t)(min) && (int64_t)(value) <= (int64_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given 64-bit integer value is not within the specified range.
 *
 * @param value The 64-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I64(value, min, max) \
    FOSSIL_TEST_ASSUME((int64_t)(value) < (int64_t)(min) || (int64_t)(value) > (int64_t)(max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given float value is within the specified range.
 *
 * @param value The float value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_F32(value, min, max) \
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given float value is not within the specified range.
 *
 * @param value The float value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_F32(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given double value is within the specified range.
 *
 * @param value The double value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_F64(value, min, max) \
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given double value is not within the specified range.
 *
 * @param value The double value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_F64(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Byte char type assumtions (uint8_t)

/**
 * @brief Assumes that the given byte char value is within the specified range.
 *
 * @param value The byte char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_BCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given byte char value is not within the specified range.
 *
 * @param value The byte char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_BCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// Char type assumtions (char)

/**
 * @brief Assumes that the given char value is within the specified range.
 *
 * @param value The char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_CCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((char)(value) >= (char)(min) && (char)(value) <= (char)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given char value is not within the specified range.
 *
 * @param value The char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_CCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((char)(value) < (char)(min) || (char)(value) > (char)(max), "Value " #value " is within range [" #min ", " #max "]")

// **************************************************
//
// String assumtions
//
// **************************************************

/**
 * @brief Assumes that the given C strings are equal.
 *
 * @param actual The actual C string.
 * @param expected The expected C string.
 */
#define ASSUME_ITS_EQUAL_CSTR(actual, expected) \
    FOSSIL_TEST_ASSUME(strcmp((actual), (expected)) == 0, "Expected C string " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given C strings are not equal.
 *
 * @param actual The actual C string.
 * @param expected The expected C string.
 */
#define ASSUME_NOT_EQUAL_CSTR(actual, expected) \
    FOSSIL_TEST_ASSUME(strcmp((actual), (expected)) != 0, "Expected C string " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the length of the given C string is equal to the expected length.
 *
 * @param actual The actual C string.
 * @param expected_len The expected length of the C string.
 */
#define ASSUME_ITS_LENGTH_EQUAL_CSTR(actual, expected_len) \
    FOSSIL_TEST_ASSUME(strlen((actual)) == (expected_len), "Expected length of C string " #actual " to be equal to " #expected_len)

/**
 * @brief Assumes that the length of the given C string is not equal to the expected length.
 *
 * @param actual The actual C string.
 * @param expected_len The expected length of the C string.
 */
#define ASSUME_NOT_LENGTH_EQUAL_CSTR(actual, expected_len) \
    FOSSIL_TEST_ASSUME(strlen((actual)) != (expected_len), "Expected length of C string " #actual " to not be equal to " #expected_len)

/**
 * @brief Assumes that the given cstr starts with the specified prefix.
 *
 * @param str The cstr to be checked.
 * @param prefix The prefix to check for.
 */
#define ASSUME_ITS_CSTR_STARTS_WITH(str, prefix) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_starts_with((str), (prefix)), "Expected cstr " #str " to start with prefix " #prefix)

/**
 * @brief Assumes that the given cstr does not start with the specified prefix.
 *
 * @param str The cstr to be checked.
 * @param prefix The prefix to check for.
 */
#define ASSUME_NOT_CSTR_STARTS_WITH(str, prefix) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_starts_with((str), (prefix)), "Expected cstr " #str " to not start with prefix " #prefix)

/**
 * @brief Assumes that the given cstr ends with the specified suffix.
 *
 * @param str The cstr to be checked.
 * @param suffix The suffix to check for.
 */
#define ASSUME_ITS_CSTR_ENDS_WITH(str, suffix) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_ends_with((str), (suffix)), "Expected cstr " #str " to end with suffix " #suffix)

/**
 * @brief Assumes that the given cstr does not end with the specified suffix.
 *
 * @param str The cstr to be checked.
 * @param suffix The suffix to check for.
 */
#define ASSUME_NOT_CSTR_ENDS_WITH(str, suffix) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_ends_with((str), (suffix)), "Expected cstr " #str " to not end with suffix " #suffix)

/**
 * @brief Assumes that the given cstr contains the specified substring.
 *
 * @param str The cstr to be checked.
 * @param substr The substring to check for.
 */
#define ASSUME_ITS_CSTR_CONTAINS(str, substr) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_contains((str), (substr)), "Expected cstr " #str " to contain substring " #substr)

/**
 * @brief Assumes that the given cstr does not contain the specified substring.
 *
 * @param str The cstr to be checked.
 * @param substr The substring to check for.
 */
#define ASSUME_NOT_CSTR_CONTAINS(str, substr) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_contains((str), (substr)), "Expected cstr " #str " to not contain substring " #substr)

/**
 * @brief Assumes that the given cstr contains the specified number of occurrences of a substring.
 *
 * @param str The cstr to be searched.
 * @param substr The substring to search for.
 * @param count The expected number of occurrences.
 */
#define ASSUME_ITS_CSTR_COUNT(str, substr, count) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_count((str), (substr)) == (count), "Expected cstr " #str " to contain " #count " occurrences of substring " #substr)

/**
 * @brief Assumes that the given cstr does not contain the specified number of occurrences of a substring.
 *
 * @param str The cstr to be searched.
 * @param substr The substring to search for.
 * @param count The expected number of occurrences.
 */
#define ASSUME_NOT_CSTR_COUNT(str, substr, count) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_count((str), (substr)) != (count), "Expected cstr " #str " to not contain " #count " occurrences of substring " #substr)

// **************************************************
//
// Char assumtions
//
// **************************************************

/**
 * @brief Assumes that the given char values are equal.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) == (char)(expected), "Expected char " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given char values are not equal.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) != (char)(expected), "Expected char " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the given char value is less than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_LESS_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) < (char)(expected), "Expected char " #actual " to be less than " #expected)

/**
 * @brief Assumes that the given char value is more than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_MORE_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) > (char)(expected), "Expected char " #actual " to be more than " #expected)

/**
 * @brief Assumes that the given char value is less than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) <= (char)(expected), "Expected char " #actual " to be less than or equal to " #expected)

/**
 * @brief Assumes that the given char value is more than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) >= (char)(expected), "Expected char " #actual " to be more than or equal to " #expected)

/**
 * @brief Assumes that the given char value is not less than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_LESS_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) >= (char)(expected), "Expected char " #actual " to not be less than " #expected)

/**
 * @brief Assumes that the given char value is not more than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_MORE_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) <= (char)(expected), "Expected char " #actual " to not be more than " #expected)

/**
 * @brief Assumes that the given char value is not less than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) > (char)(expected), "Expected char " #actual " to not be less than or equal to " #expected)

/**
 * @brief Assumes that the given char value is not more than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) < (char)(expected), "Expected char " #actual " to not be more than or equal to " #expected)

// **************************************************
// SOAP assumptions
// ************************************************

/**
 * @brief Assumes that the given text does not contain "rot-brain" language.
 *
 * @param text The input text to check.
 */
#define ASSUME_NOT_SOAP_ROT_BRAIN(text) \
    FOSSIL_TEST_ASSUME(!pizza_io_is_rot_brain((text)), "Expected text " #text " to not contain 'rot-brain' language")

/**
 * @brief Assumes that the given text contains "rot-brain" language.
 *
 * @param text The input text to check.
 */
#define ASSUME_ITS_SOAP_ROT_BRAIN(text) \
    FOSSIL_TEST_ASSUME(pizza_io_is_rot_brain((text)), "Expected text " #text " to contain 'rot-brain' language")

/**
 * @brief Assumes that the tone of the given sentence is detected correctly.
 *
 * @param text The input text.
 * @param expected_tone The expected tone ("formal", "casual", "sarcastic", etc.).
 */
#define ASSUME_ITS_SOAP_TONE_DETECTED(text, expected_tone) \
    FOSSIL_TEST_ASSUME(strcmp(pizza_io_soap_detect_tone((text)), (expected_tone)) == 0, "Expected tone of text " #text " to be " #expected_tone)

/**
 * @brief Assumes that the tone of the given sentence is not detected correctly.
 *
 * @param text The input text.
 * @param expected_tone The expected tone ("formal", "casual", "sarcastic", etc.).
 */
#define ASSUME_NOT_SOAP_TONE_DETECTED(text, expected_tone) \
    FOSSIL_TEST_ASSUME(strcmp(pizza_io_soap_detect_tone((text)), (expected_tone)) != 0, "Expected tone of text " #text " to not be " #expected_tone)

#ifdef __cplusplus
}
#endif

#endif
