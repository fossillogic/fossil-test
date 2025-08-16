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
    FOSSIL_TEST_ASSUME((actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %s to be true", (actual) ? "true" : "false"))

/**
 * @brief Assumes that the given boolean expression is false.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_ITS_FALSE(actual) \
    FOSSIL_TEST_ASSUME(!(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %s to be false", (actual) ? "true" : "false"))

/**
 * @brief Assumes that the given boolean expression is not true.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_NOT_TRUE(actual) \
    FOSSIL_TEST_ASSUME(!(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %s to not be true", (actual) ? "true" : "false"))

/**
 * @brief Assumes that the given boolean expression is not false.
 *
 * @param actual The boolean expression to be evaluated.
 */
#define ASSUME_NOT_FALSE(actual) \
    FOSSIL_TEST_ASSUME((actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %s to not be false", (actual) ? "true" : "false"))

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
    FOSSIL_TEST_ASSUME(fabs((actual) - (expected)) <= (tol), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be equal to " #expected " of value %f within tolerance " #tol " of value %f", (actual), (expected), (tol)))

/**
 * @brief Assumes that the given double value is less than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_LESS_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be less than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is more than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_MORE_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be more than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is less than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be less than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is more than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be more than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double values are not equal within a specified tolerance.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 * @param tol The tolerance within which the values should not be considered equal.
 */
#define ASSUME_NOT_EQUAL_F64(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabs((actual) - (expected)) > (tol), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be equal to " #expected " of value %f within tolerance " #tol " of value %f", (actual), (expected), (tol)))

/**
 * @brief Assumes that the given double value is not less than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_LESS_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be less than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is not more than the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_MORE_THAN_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be more than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is not less than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be less than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given double value is not more than or equal to the expected value.
 *
 * @param actual The actual double value.
 * @param expected The expected double value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_F64(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be more than or equal to " #expected " of value %f", (actual), (expected)))

// Float equality check with tolerance
/**
 * @brief Assumes that the given float values are equal within a specified tolerance.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 * @param tol The tolerance within which the values should be considered equal.
 */
#define ASSUME_ITS_EQUAL_F32(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabsf((actual) - (expected)) <= (tol), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be equal to " #expected " of value %f within tolerance " #tol " of value %f", (actual), (expected), (tol)))

/**
 * @brief Assumes that the given float value is less than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_LESS_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be less than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is more than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_MORE_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be more than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is less than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be less than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is more than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be more than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float values are not equal within a specified tolerance.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 * @param tol The tolerance within which the values should not be considered equal.
 */
#define ASSUME_NOT_EQUAL_F32(actual, expected, tol) \
    FOSSIL_TEST_ASSUME(fabsf((actual) - (expected)) > (tol), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be equal to " #expected " of value %f within tolerance " #tol " of value %f", (actual), (expected), (tol)))

/**
 * @brief Assumes that the given float value is not less than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_LESS_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) >= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be less than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is not more than the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_MORE_THAN_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) <= (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be more than " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is not less than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) > (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be less than or equal to " #expected " of value %f", (actual), (expected)))

/**
 * @brief Assumes that the given float value is not more than or equal to the expected value.
 *
 * @param actual The actual float value.
 * @param expected The expected float value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_F32(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) < (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to not be more than or equal to " #expected " of value %f", (actual), (expected)))

// Float NaN and Infinity checks
/**
 * @brief Assumes that the given float value is NaN (Not a Number).
 *
 * @param actual The actual float value.
 */
#define ASSUME_ITS_NAN_F32(actual) \
    FOSSIL_TEST_ASSUME(isnan(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be NaN", (actual)))

/**
 * @brief Assumes that the given float value is infinity.
 *
 * @param actual The actual float value.
 */
#define ASSUME_ITS_INF_F32(actual) \
    FOSSIL_TEST_ASSUME(isinf(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be infinity", (actual)))

// Double NaN and Infinity checks
/**
 * @brief Assumes that the given double value is NaN (Not a Number).
 *
 * @param actual The actual double value.
 */
#define ASSUME_ITS_NAN_F64(actual) \
    FOSSIL_TEST_ASSUME(isnan(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be NaN", (actual)))

/**
 * @brief Assumes that the given double value is infinity.
 *
 * @param actual The actual double value.
 */
#define ASSUME_ITS_INF_F64(actual) \
    FOSSIL_TEST_ASSUME(isinf(actual), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %f to be infinity", (actual)))

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
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is less than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is more than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal values are not equal.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is not less than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is not more than the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit octal value.
 * @param expected The expected 8-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal values are equal.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is less than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is more than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal values are not equal.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is not less than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is not more than the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit octal value.
 * @param expected The expected 16-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal values are equal.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is less than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is more than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal values are not equal.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is not less than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is not more than the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit octal value.
 * @param expected The expected 32-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal values are equal.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is less than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_LESS_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is more than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_MORE_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal values are not equal.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is not less than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_LESS_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is not more than the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_MORE_THAN_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit octal value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit octal value.
 * @param expected The expected 64-bit octal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_O64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

// Hexadecimal assumptions

/**
 * @brief Assumes that the given 8-bit hexadecimal values are equal.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal values are not equal.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit hexadecimal value.
 * @param expected The expected 8-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal values are equal.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal values are not equal.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit hexadecimal value.
 * @param expected The expected 16-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal values are equal.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal values are not equal.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit hexadecimal value.
 * @param expected The expected 32-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal values are equal.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is less than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is more than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal values are not equal.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not less than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not more than the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_THAN_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit hexadecimal value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit hexadecimal value.
 * @param expected The expected 64-bit hexadecimal value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_H64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer values are equal.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) == (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is less than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is more than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than or equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than or equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer values are not equal.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) != (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is not less than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is not more than the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than or equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit integer value.
 * @param expected The expected 8-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I8(actual, expected) \
    FOSSIL_TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than or equal to " #expected " of value %d", (int8_t)(actual), (int8_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer values are equal.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) == (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is less than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is more than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than or equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than or equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer values are not equal.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) != (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is not less than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is not more than the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than or equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit integer value.
 * @param expected The expected 16-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I16(actual, expected) \
    FOSSIL_TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than or equal to " #expected " of value %d", (int16_t)(actual), (int16_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer values are equal.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) == (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is less than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is more than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be less than or equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to be more than or equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer values are not equal.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) != (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is not less than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is not more than the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be less than or equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit integer value.
 * @param expected The expected 32-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I32(actual, expected) \
    FOSSIL_TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %d to not be more than or equal to " #expected " of value %d", (int32_t)(actual), (int32_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer values are equal.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) == (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to be equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is less than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_LESS_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to be less than " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is more than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_MORE_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to be more than " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to be less than or equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to be more than or equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer values are not equal.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) != (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to not be equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is not less than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_LESS_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to not be less than " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is not more than the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_MORE_THAN_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to not be more than " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to not be less than or equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit integer value.
 * @param expected The expected 64-bit integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_I64(actual, expected) \
    FOSSIL_TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %lld to not be more than or equal to " #expected " of value %lld", (int64_t)(actual), (int64_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer values are equal.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer values are not equal.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 8-bit unsigned integer value.
 * @param expected The expected 8-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U8(actual, expected) \
    FOSSIL_TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint8_t)(actual), (uint8_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer values are equal.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer values are not equal.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 16-bit unsigned integer value.
 * @param expected The expected 16-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U16(actual, expected) \
    FOSSIL_TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint16_t)(actual), (uint16_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer values are equal.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer values are not equal.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be less than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 32-bit unsigned integer value.
 * @param expected The expected 32-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U32(actual, expected) \
    FOSSIL_TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %u to not be more than or equal to " #expected " of value %u", (uint32_t)(actual), (uint32_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer values are equal.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is less than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is more than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is less than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is more than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer values are not equal.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not less than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not more than the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_THAN_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not less than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be less than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not more than or equal to the expected value.
 *
 * @param actual The actual 64-bit unsigned integer value.
 * @param expected The expected 64-bit unsigned integer value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_U64(actual, expected) \
    FOSSIL_TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %llu to not be more than or equal to " #expected " of value %llu", (uint64_t)(actual), (uint64_t)(expected)))

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
    FOSSIL_TEST_ASSUME(pizza_sys_memory_zero((ptr), (size)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory at " #ptr " of size %zu to be zeroed", (size)))

/**
 * @brief Assumes that the given memory is not zeroed.
 *
 * @param ptr A pointer to the memory to check.
 * @param size The size of the memory to check.
 */
#define ASSUME_NOT_ZERO_MEMORY(ptr, size) \
    FOSSIL_TEST_ASSUME(!pizza_sys_memory_zero((ptr), (size)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory at " #ptr " of size %zu to not be zeroed", (size)))

/**
 * @brief Assumes that the given memory regions are equal.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) == 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory regions " #ptr1 " and " #ptr2 " of size %zu to be equal", (size)))

/**
 * @brief Assumes that the given memory regions are not equal.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) != 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory regions " #ptr1 " and " #ptr2 " of size %zu to not be equal", (size)))

/**
 * @brief Assumes that the given memory region is more than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_MORE_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) > 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to be more than " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is less than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_LESS_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) < 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to be less than " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is more than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) >= 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to be more than or equal to " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is less than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) <= 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to be less than or equal to " #ptr2 " for size %zu", (size)))
    
/**
 * @brief Assumes that the given memory region is not more than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_MORE_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) <= 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to not be more than " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is not less than the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_LESS_THAN_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) >= 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to not be less than " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is not more than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) < 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to not be more than or equal to " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory region is not less than or equal to the expected memory region.
 *
 * @param ptr1 A pointer to the first memory region.
 * @param ptr2 A pointer to the second memory region.
 * @param size The size of the memory regions to compare.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_MEMORY(ptr1, ptr2, size) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_compare((ptr1), (ptr2), (size)) > 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory region " #ptr1 " to not be less than or equal to " #ptr2 " for size %zu", (size)))

/**
 * @brief Assumes that the given memory pointer is valid.
 *
 * @param ptr A pointer to the memory to check.
 */
#define ASSUME_ITS_VALID_MEMORY(ptr) \
    FOSSIL_TEST_ASSUME(pizza_sys_memory_is_valid((ptr)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory pointer " #ptr " to be valid", null))

/**
 * @brief Assumes that the given memory pointer is not valid.
 *
 * @param ptr A pointer to the memory to check.
 */
#define ASSUME_NOT_VALID_MEMORY(ptr) \
    FOSSIL_TEST_ASSUME(!pizza_sys_memory_is_valid((ptr)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected memory pointer " #ptr " to not be valid", null))

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
    FOSSIL_TEST_ASSUME((actual) == null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given pointer is not cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to not be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given pointer is cnull.
 * 
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNULLABLE(actual) \
    FOSSIL_TEST_ASSUME((actual) == null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given pointer is not cnull.
 * 
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNULLABLE(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to not be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given pointer is cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_ITS_CNONNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) != null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to not be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given pointer is not cnull.
 *
 * @param actual The pointer to be evaluated.
 */
#define ASSUME_NOT_CNONNULL(actual) \
    FOSSIL_TEST_ASSUME((actual) == null, _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " to be cnull, but got %p", (actual)))

/**
 * @brief Assumes that the given condition is likely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_ITS_LIKELY(x) \
    FOSSIL_TEST_ASSUME(likely(x), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #x " to be likely, but got %d", (x)))

/**
 * @brief Assumes that the given condition is not likely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_NOT_LIKELY(x) \
    FOSSIL_TEST_ASSUME(!likely(x), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #x " to not be likely, but got %d", (x)))

/**
 * @brief Assumes that the given condition is unlikely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_ITS_UNLIKELY(x) \
    FOSSIL_TEST_ASSUME(unlikely(x), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #x " to be unlikely, but got %d", (x)))

/**
 * @brief Assumes that the given condition is not unlikely.
 *
 * @param x The condition to be evaluated.
 */
#define ASSUME_NOT_UNLIKELY(x) \
    FOSSIL_TEST_ASSUME(!unlikely(x), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #x " to not be unlikely, but got %d", (x)))

/**
 * @brief Assumes that the given pointers are equal.
 *
 * @param actual The actual pointer.
 * @param expected The expected pointer.
 */
#define ASSUME_ITS_EQUAL_PTR(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) == (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected pointer " #actual " of value %p to be equal to pointer " #expected " of value %p", (actual), (expected)))

/**
 * @brief Assumes that the given pointers are not equal.
 *
 * @param actual The actual pointer.
 * @param expected The expected pointer.
 */
#define ASSUME_NOT_EQUAL_PTR(actual, expected) \
    FOSSIL_TEST_ASSUME((actual) != (expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected pointer " #actual " of value %p to not be equal to pointer " #expected " of value %p", (actual), (expected)))

/**
 * @brief Assumes that the given size_t values are equal.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) == (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to be equal to " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

/**
 * @brief Assumes that the given size_t value is less than the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_LESS_THAN_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) < (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to be less than " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

/**
 * @brief Assumes that the given size_t value is more than the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_MORE_THAN_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) > (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to be more than " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

/**
 * @brief Assumes that the given size_t value is less than or equal to the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) <= (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to be less than or equal to " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

/**
 * @brief Assumes that the given size_t value is more than or equal to the expected value.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) >= (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to be more than or equal to " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

/**
 * @brief Assumes that the given size_t values are not equal.
 *
 * @param actual The actual size_t value.
 * @param expected The expected size_t value.
 */
#define ASSUME_NOT_EQUAL_SIZE(actual, expected) \
    FOSSIL_TEST_ASSUME((size_t)(actual) != (size_t)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected " #actual " of value %zu to not be equal to " #expected " of value %zu", (size_t)(actual), (size_t)(expected)))

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
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is not within range [" #min " of value %d, " #max " of value %d]", (value), (min), (max)))

/**
 * @brief Assumes that the given value is not within the specified range.
 *
 * @param value The value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is within range [" #min " of value %d, " #max " of value %d]", (value), (min), (max)))

// Unsigned integer type assumptions

/**
 * @brief Assumes that the given 8-bit unsigned integer value is within the specified range.
 *
 * @param value The 8-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U8(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is not within range [" #min " of value %u, " #max " of value %u]", (uint8_t)(value), (uint8_t)(min), (uint8_t)(max)))

/**
 * @brief Assumes that the given 8-bit unsigned integer value is not within the specified range.
 *
 * @param value The 8-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U8(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is within range [" #min " of value %u, " #max " of value %u]", (uint8_t)(value), (uint8_t)(min), (uint8_t)(max)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is within the specified range.
 *
 * @param value The 16-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U16(value, min, max) \
    FOSSIL_TEST_ASSUME((uint16_t)(value) >= (uint16_t)(min) && (uint16_t)(value) <= (uint16_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is not within range [" #min " of value %u, " #max " of value %u]", (uint16_t)(value), (uint16_t)(min), (uint16_t)(max)))

/**
 * @brief Assumes that the given 16-bit unsigned integer value is not within the specified range.
 *
 * @param value The 16-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U16(value, min, max) \
    FOSSIL_TEST_ASSUME((uint16_t)(value) < (uint16_t)(min) || (uint16_t)(value) > (uint16_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is within range [" #min " of value %u, " #max " of value %u]", (uint16_t)(value), (uint16_t)(min), (uint16_t)(max)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is within the specified range.
 *
 * @param value The 32-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U32(value, min, max) \
    FOSSIL_TEST_ASSUME((uint32_t)(value) >= (uint32_t)(min) && (uint32_t)(value) <= (uint32_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is not within range [" #min " of value %u, " #max " of value %u]", (uint32_t)(value), (uint32_t)(min), (uint32_t)(max)))

/**
 * @brief Assumes that the given 32-bit unsigned integer value is not within the specified range.
 *
 * @param value The 32-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U32(value, min, max) \
    FOSSIL_TEST_ASSUME((uint32_t)(value) < (uint32_t)(min) || (uint32_t)(value) > (uint32_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is within range [" #min " of value %u, " #max " of value %u]", (uint32_t)(value), (uint32_t)(min), (uint32_t)(max)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is within the specified range.
 *
 * @param value The 64-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_U64(value, min, max) \
    FOSSIL_TEST_ASSUME((uint64_t)(value) >= (uint64_t)(min) && (uint64_t)(value) <= (uint64_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %llu is not within range [" #min " of value %llu, " #max " of value %llu]", (uint64_t)(value), (uint64_t)(min), (uint64_t)(max)))

/**
 * @brief Assumes that the given 64-bit unsigned integer value is not within the specified range.
 *
 * @param value The 64-bit unsigned integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_U64(value, min, max) \
    FOSSIL_TEST_ASSUME((uint64_t)(value) < (uint64_t)(min) || (uint64_t)(value) > (uint64_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %llu is within range [" #min " of value %llu, " #max " of value %llu]", (uint64_t)(value), (uint64_t)(min), (uint64_t)(max)))

/**
 * @brief Assumes that the given 8-bit integer value is within the specified range.
 *
 * @param value The 8-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I8(value, min, max) \
    FOSSIL_TEST_ASSUME((int8_t)(value) >= (int8_t)(min) && (int8_t)(value) <= (int8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is not within range [" #min " of value %d, " #max " of value %d]", (int8_t)(value), (int8_t)(min), (int8_t)(max)))

/**
 * @brief Assumes that the given 8-bit integer value is not within the specified range.
 *
 * @param value The 8-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I8(value, min, max) \
    FOSSIL_TEST_ASSUME((int8_t)(value) < (int8_t)(min) || (int8_t)(value) > (int8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is within range [" #min " of value %d, " #max " of value %d]", (int8_t)(value), (int8_t)(min), (int8_t)(max)))

/**
 * @brief Assumes that the given 16-bit integer value is within the specified range.
 *
 * @param value The 16-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I16(value, min, max) \
    FOSSIL_TEST_ASSUME((int16_t)(value) >= (int16_t)(min) && (int16_t)(value) <= (int16_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is not within range [" #min " of value %d, " #max " of value %d]", (int16_t)(value), (int16_t)(min), (int16_t)(max)))

/**
 * @brief Assumes that the given 16-bit integer value is not within the specified range.
 *
 * @param value The 16-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I16(value, min, max) \
    FOSSIL_TEST_ASSUME((int16_t)(value) < (int16_t)(min) || (int16_t)(value) > (int16_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is within range [" #min " of value %d, " #max " of value %d]", (int16_t)(value), (int16_t)(min), (int16_t)(max)))

/**
 * @brief Assumes that the given 32-bit integer value is within the specified range.
 *
 * @param value The 32-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I32(value, min, max) \
    FOSSIL_TEST_ASSUME((int32_t)(value) >= (int32_t)(min) && (int32_t)(value) <= (int32_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is not within range [" #min " of value %d, " #max " of value %d]", (int32_t)(value), (int32_t)(min), (int32_t)(max)))

/**
 * @brief Assumes that the given 32-bit integer value is not within the specified range.
 *
 * @param value The 32-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I32(value, min, max) \
    FOSSIL_TEST_ASSUME((int32_t)(value) < (int32_t)(min) || (int32_t)(value) > (int32_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %d is within range [" #min " of value %d, " #max " of value %d]", (int32_t)(value), (int32_t)(min), (int32_t)(max)))

/**
 * @brief Assumes that the given 64-bit integer value is within the specified range.
 *
 * @param value The 64-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_I64(value, min, max) \
    FOSSIL_TEST_ASSUME((int64_t)(value) >= (int64_t)(min) && (int64_t)(value) <= (int64_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %lld is not within range [" #min " of value %lld, " #max " of value %lld]", (int64_t)(value), (int64_t)(min), (int64_t)(max)))

/**
 * @brief Assumes that the given 64-bit integer value is not within the specified range.
 *
 * @param value The 64-bit integer value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_I64(value, min, max) \
    FOSSIL_TEST_ASSUME((int64_t)(value) < (int64_t)(min) || (int64_t)(value) > (int64_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %lld is within range [" #min " of value %lld, " #max " of value %lld]", (int64_t)(value), (int64_t)(min), (int64_t)(max)))

/**
 * @brief Assumes that the given float value is within the specified range.
 *
 * @param value The float value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_F32(value, min, max) \
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %f is not within range [" #min " of value %f, " #max " of value %f]", (value), (min), (max)))

/**
 * @brief Assumes that the given float value is not within the specified range.
 *
 * @param value The float value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_F32(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %f is within range [" #min " of value %f, " #max " of value %f]", (value), (min), (max)))

/**
 * @brief Assumes that the given double value is within the specified range.
 *
 * @param value The double value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_F64(value, min, max) \
    FOSSIL_TEST_ASSUME((value) >= (min) && (value) <= (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %f is not within range [" #min " of value %f, " #max " of value %f]", (value), (min), (max)))

/**
 * @brief Assumes that the given double value is not within the specified range.
 *
 * @param value The double value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_F64(value, min, max) \
    FOSSIL_TEST_ASSUME((value) < (min) || (value) > (max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %f is within range [" #min " of value %f, " #max " of value %f]", (value), (min), (max)))

// Byte char type assumptions (uint8_t)

/**
 * @brief Assumes that the given byte char value is within the specified range.
 *
 * @param value The byte char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_BCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is not within range [" #min " of value %u, " #max " of value %u]", (uint8_t)(value), (uint8_t)(min), (uint8_t)(max)))

/**
 * @brief Assumes that the given byte char value is not within the specified range.
 *
 * @param value The byte char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_BCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %u is within range [" #min " of value %u, " #max " of value %u]", (uint8_t)(value), (uint8_t)(min), (uint8_t)(max)))

// Char type assumptions (char)

/**
 * @brief Assumes that the given char value is within the specified range.
 *
 * @param value The char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_ITS_WITHIN_RANGE_CCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((char)(value) >= (char)(min) && (char)(value) <= (char)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %c is not within range [" #min " of value %c, " #max " of value %c]", (char)(value), (char)(min), (char)(max)))

/**
 * @brief Assumes that the given char value is not within the specified range.
 *
 * @param value The char value to be evaluated.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 */
#define ASSUME_NOT_WITHIN_RANGE_CCHAR(value, min, max) \
    FOSSIL_TEST_ASSUME((char)(value) < (char)(min) || (char)(value) > (char)(max), _FOSSIL_TEST_ASSUME_MESSAGE("Value " #value " of value %c is within range [" #min " of value %c, " #max " of value %c]", (char)(value), (char)(min), (char)(max)))

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
    FOSSIL_TEST_ASSUME(strcmp((actual), (expected)) == 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected C string " #actual " of value \"%s\" to be equal to " #expected " of value \"%s\"", (actual), (expected)))

/**
 * @brief Assumes that the given C strings are not equal.
 *
 * @param actual The actual C string.
 * @param expected The expected C string.
 */
#define ASSUME_NOT_EQUAL_CSTR(actual, expected) \
    FOSSIL_TEST_ASSUME(strcmp((actual), (expected)) != 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected C string " #actual " of value \"%s\" to not be equal to " #expected " of value \"%s\"", (actual), (expected)))

/**
 * @brief Assumes that the length of the given C string is equal to the expected length.
 *
 * @param actual The actual C string.
 * @param expected_len The expected length of the C string.
 */
#define ASSUME_ITS_LENGTH_EQUAL_CSTR(actual, expected_len) \
    FOSSIL_TEST_ASSUME(strlen((actual)) == (expected_len), _FOSSIL_TEST_ASSUME_MESSAGE("Expected length of C string " #actual " of value \"%s\" to be equal to " #expected_len " of value %zu", (actual), (expected_len)))

/**
 * @brief Assumes that the length of the given C string is not equal to the expected length.
 *
 * @param actual The actual C string.
 * @param expected_len The expected length of the C string.
 */
#define ASSUME_NOT_LENGTH_EQUAL_CSTR(actual, expected_len) \
    FOSSIL_TEST_ASSUME(strlen((actual)) != (expected_len), _FOSSIL_TEST_ASSUME_MESSAGE("Expected length of C string " #actual " of value \"%s\" to not be equal to " #expected_len " of value %zu", (actual), (expected_len)))

/**
 * @brief Assumes that the given cstr starts with the specified prefix.
 *
 * @param str The cstr to be checked.
 * @param prefix The prefix to check for.
 */
#define ASSUME_ITS_CSTR_STARTS_WITH(str, prefix) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_starts_with((str), (prefix)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to start with prefix " #prefix " of value \"%s\"", (str), (prefix)))

/**
 * @brief Assumes that the given cstr does not start with the specified prefix.
 *
 * @param str The cstr to be checked.
 * @param prefix The prefix to check for.
 */
#define ASSUME_NOT_CSTR_STARTS_WITH(str, prefix) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_starts_with((str), (prefix)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to not start with prefix " #prefix " of value \"%s\"", (str), (prefix)))

/**
 * @brief Assumes that the given cstr ends with the specified suffix.
 *
 * @param str The cstr to be checked.
 * @param suffix The suffix to check for.
 */
#define ASSUME_ITS_CSTR_ENDS_WITH(str, suffix) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_ends_with((str), (suffix)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to end with suffix " #suffix " of value \"%s\"", (str), (suffix)))

/**
 * @brief Assumes that the given cstr does not end with the specified suffix.
 *
 * @param str The cstr to be checked.
 * @param suffix The suffix to check for.
 */
#define ASSUME_NOT_CSTR_ENDS_WITH(str, suffix) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_ends_with((str), (suffix)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to not end with suffix " #suffix " of value \"%s\"", (str), (suffix)))

/**
 * @brief Assumes that the given cstr contains the specified substring.
 *
 * @param str The cstr to be checked.
 * @param substr The substring to check for.
 */
#define ASSUME_ITS_CSTR_CONTAINS(str, substr) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_contains((str), (substr)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to contain substring " #substr " of value \"%s\"", (str), (substr)))

/**
 * @brief Assumes that the given cstr does not contain the specified substring.
 *
 * @param str The cstr to be checked.
 * @param substr The substring to check for.
 */
#define ASSUME_NOT_CSTR_CONTAINS(str, substr) \
    FOSSIL_TEST_ASSUME(!pizza_io_cstr_contains((str), (substr)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to not contain substring " #substr " of value \"%s\"", (str), (substr)))

/**
 * @brief Assumes that the given cstr contains the specified number of occurrences of a substring.
 *
 * @param str The cstr to be searched.
 * @param substr The substring to search for.
 * @param count The expected number of occurrences.
 */
#define ASSUME_ITS_CSTR_COUNT(str, substr, count) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_count((str), (substr)) == (count), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to contain " #count " occurrences of substring " #substr " of value \"%s\"", (str), (substr), (count)))

/**
 * @brief Assumes that the given cstr does not contain the specified number of occurrences of a substring.
 *
 * @param str The cstr to be searched.
 * @param substr The substring to search for.
 * @param count The expected number of occurrences.
 */
#define ASSUME_NOT_CSTR_COUNT(str, substr, count) \
    FOSSIL_TEST_ASSUME(pizza_io_cstr_count((str), (substr)) != (count), _FOSSIL_TEST_ASSUME_MESSAGE("Expected cstr " #str " of value \"%s\" to not contain " #count " occurrences of substring " #substr " of value \"%s\"", (str), (substr), (count)))

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
    FOSSIL_TEST_ASSUME((char)(actual) == (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to be equal to " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char values are not equal.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) != (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to not be equal to " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is less than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_LESS_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) < (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to be less than " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is more than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_MORE_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) > (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to be more than " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is less than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_LESS_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) <= (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to be less than or equal to " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is more than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_ITS_MORE_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) >= (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to be more than or equal to " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is not less than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_LESS_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) >= (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to not be less than " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is not more than the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_MORE_THAN_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) <= (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to not be more than " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is not less than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_LESS_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) > (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to not be less than or equal to " #expected " of value %c", (char)(actual), (char)(expected)))

/**
 * @brief Assumes that the given char value is not more than or equal to the expected value.
 *
 * @param actual The actual char value.
 * @param expected The expected char value.
 */
#define ASSUME_NOT_MORE_OR_EQUAL_CHAR(actual, expected) \
    FOSSIL_TEST_ASSUME((char)(actual) < (char)(expected), _FOSSIL_TEST_ASSUME_MESSAGE("Expected char " #actual " of value %c to not be more than or equal to " #expected " of value %c", (char)(actual), (char)(expected)))

// **************************************************
// SOAP assumptions
// ************************************************

/**
 * @brief Assumes that the given text does not contain "rot-brain" language.
 *
 * @param text The input text to check.
 */
#define ASSUME_NOT_SOAP_ROT_BRAIN(text) \
    FOSSIL_TEST_ASSUME(!pizza_io_is_rot_brain((text)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected text " #text " of value \"%s\" to not contain 'rot-brain' language", (text)))

/**
 * @brief Assumes that the given text contains "rot-brain" language.
 *
 * @param text The input text to check.
 */
#define ASSUME_ITS_SOAP_ROT_BRAIN(text) \
    FOSSIL_TEST_ASSUME(pizza_io_is_rot_brain((text)), _FOSSIL_TEST_ASSUME_MESSAGE("Expected text " #text " of value \"%s\" to contain 'rot-brain' language", (text)))

/**
 * @brief Assumes that the tone of the given sentence is detected correctly.
 *
 * @param text The input text.
 * @param expected_tone The expected tone ("formal", "casual", "sarcastic", etc.).
 */
#define ASSUME_ITS_SOAP_TONE_DETECTED(text, expected_tone) \
    FOSSIL_TEST_ASSUME(strcmp(pizza_io_soap_detect_tone((text)), (expected_tone)) == 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected tone of text " #text " of value \"%s\" to be " #expected_tone " of value \"%s\"", (text), (expected_tone)))

/**
 * @brief Assumes that the tone of the given sentence is not detected correctly.
 *
 * @param text The input text.
 * @param expected_tone The expected tone ("formal", "casual", "sarcastic", etc.).
 */
#define ASSUME_NOT_SOAP_TONE_DETECTED(text, expected_tone) \
    FOSSIL_TEST_ASSUME(strcmp(pizza_io_soap_detect_tone((text)), (expected_tone)) != 0, _FOSSIL_TEST_ASSUME_MESSAGE("Expected tone of text " #text " of value \"%s\" to not be " #expected_tone " of value \"%s\"", (text), (expected_tone)))

#ifdef __cplusplus
}
#endif

#endif
