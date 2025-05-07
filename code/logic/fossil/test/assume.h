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
 * Copyright (C) 2014 Fossil Logic. All rights reserved.
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
#include <wchar.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// becuase Microsoft had to be diffrent
#ifdef _WIN32
#define wcsncasecmp _wcsnicmp
#endif

// Used in floating-point asserts
#define FOSSIL_TEST_FLOAT_EPSILON 1e-6
#define FOSSIL_TEST_DOUBLE_EPSILON 1e-9

// **************************************************
//
// Boolean ASSUMEions
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
// Floating point ASSUMEions
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
// Numaric ASSUMEions
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

// Hexadecimal ASSUMEions

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
// Null pointer ASSUMEions (_CNULL)
//
// **************************************************

/**
 * @brief Assumes that the given pointer is NULL.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) == NULL, "Expected " #actual " to be NULL")

/**
 * @brief Assumes that the given pointer is not NULL.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) != NULL, "Expected " #actual " to not be NULL")

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
// Range ASSUMEions
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

// Byte char type ASSUMEions (uint8_t)

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

// Char type ASSUMEions (char)

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

// Wide char type ASSUMEions (wchar_t)

/**
 * @brief Assumes that the given wide char value is within the specified range.
 *
 * @param value The wide char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_WCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((wchar_t)(value) >= (wchar_t)(min) && (wchar_t)(value) <= (wchar_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

/**
 * @brief Assumes that the given wide char value is not within the specified range.
 *
 * @param value The wide char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_WCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((wchar_t)(value) < (wchar_t)(min) || (wchar_t)(value) > (wchar_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// **************************************************
//
// String ASSUMEions
//
// **************************************************

/**
 * @brief Assumes that the given wide char strings are equal.
 *
 * @param actual The actual wide char string.
 * @param expected The expected wide char string.
 */
#define ASSUME_ITS_EQUAL_WSTR(actual, expected) \
    FOSSIL_TEST_ASSUME(wcscmp((actual), (expected)) == 0, "Expected wide string " #actual " to be equal to " #expected)

/**
 * @brief Assumes that the given wide char strings are not equal.
 *
 * @param actual The actual wide char string.
 * @param expected The expected wide char string.
 */
#define ASSUME_NOT_EQUAL_WSTR(actual, expected) \
    FOSSIL_TEST_ASSUME(wcscmp((actual), (expected)) != 0, "Expected wide string " #actual " to not be equal to " #expected)

/**
 * @brief Assumes that the length of the given wide char string is equal to the expected length.
 *
 * @param actual The actual wide char string.
 * @param expected_len The expected length of the wide char string.
 */
#define ASSUME_ITS_LENGTH_EQUAL_WSTR(actual, expected_len) \
    FOSSIL_TEST_ASSUME(wcslen((actual)) == (expected_len), "Expected length of wide string " #actual " to be equal to " #expected_len)

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

#ifdef __cplusplus
}
#endif

#endif
