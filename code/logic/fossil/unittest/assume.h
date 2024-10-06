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
#ifndef FOSSIL_TEST_ASSUME_TYPE_H
#define FOSSIL_TEST_ASSUME_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test

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

// **************************************************
//
// Boolean ASSUMEions
//
// **************************************************

// Boolean ITS ASSUMEions
#define ASSUME_ITS_TRUE(actual) \
    TEST_ASSUME((actual), "Expected " #actual " to be true")

#define ASSUME_ITS_FALSE(actual) \
    TEST_ASSUME(!(actual), "Expected " #actual " to be false")

// Boolean NOT ASSUMEions
#define ASSUME_NOT_TRUE(actual) \
    TEST_ASSUME(!(actual), "Expected " #actual " to not be true")

#define ASSUME_NOT_FALSE(actual) \
    TEST_ASSUME((actual), "Expected " #actual " to not be false")

// **************************************************
//
// Floating point ASSUMEions
//
// **************************************************

// Double equality check with tolerance
#define ASSUME_ITS_EQUAL_F64(actual, expected, tol) \
    TEST_ASSUME(fabs((actual) - (expected)) <= (tol), "Expected " #actual " to be equal to " #expected " within tolerance " #tol)

#define ASSUME_ITS_LESS_THAN_F64(actual, expected) \
    TEST_ASSUME((actual) < (expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_F64(actual, expected) \
    TEST_ASSUME((actual) > (expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_F64(actual, expected) \
    TEST_ASSUME((actual) <= (expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_F64(actual, expected) \
    TEST_ASSUME((actual) >= (expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_F64(actual, expected, tol) \
    TEST_ASSUME(fabs((actual) - (expected)) > (tol), "Expected " #actual " to not be equal to " #expected " within tolerance " #tol)

#define ASSUME_NOT_LESS_THAN_F64(actual, expected) \
    TEST_ASSUME((actual) >= (expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_F64(actual, expected) \
    TEST_ASSUME((actual) <= (expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_F64(actual, expected) \
    TEST_ASSUME((actual) > (expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_F64(actual, expected) \
    TEST_ASSUME((actual) < (expected), "Expected " #actual " to not be more than or equal to " #expected)

// Float equality check with tolerance
#define ASSUME_ITS_EQUAL_F32(actual, expected, tol) \
    TEST_ASSUME(fabsf((actual) - (expected)) <= (tol), "Expected " #actual " to be equal to " #expected " within tolerance " #tol)

#define ASSUME_ITS_LESS_THAN_F32(actual, expected) \
    TEST_ASSUME((actual) < (expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_F32(actual, expected) \
    TEST_ASSUME((actual) > (expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_F32(actual, expected) \
    TEST_ASSUME((actual) <= (expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_F32(actual, expected) \
    TEST_ASSUME((actual) >= (expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_F32(actual, expected, tol) \
    TEST_ASSUME(fabsf((actual) - (expected)) > (tol), "Expected " #actual " to not be equal to " #expected " within tolerance " #tol)

#define ASSUME_NOT_LESS_THAN_F32(actual, expected) \
    TEST_ASSUME((actual) >= (expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_F32(actual, expected) \
    TEST_ASSUME((actual) <= (expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_F32(actual, expected) \
    TEST_ASSUME((actual) > (expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_F32(actual, expected) \
    TEST_ASSUME((actual) < (expected), "Expected " #actual " to not be more than or equal to " #expected)

// Float NaN and Infinity checks
#define ASSUME_ITS_NAN_F32(actual) \
    TEST_ASSUME(isnan(actual), "Expected " #actual " to be NaN")

#define ASSUME_ITS_INF_F32(actual) \
    TEST_ASSUME(isinf(actual), "Expected " #actual " to be infinity")

// Double NaN and Infinity checks
#define ASSUME_ITS_NAN_F64(actual) \
    TEST_ASSUME(isnan(actual), "Expected " #actual " to be NaN")

#define ASSUME_ITS_INF_F64(actual) \
    TEST_ASSUME(isinf(actual), "Expected " #actual " to be infinity")

// **************************************************
//
// Numaric ASSUMEions
//
// **************************************************

// Octal ASSUMEions

// O8 ASSUMEions
#define ASSUME_ITS_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_O8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// O16 ASSUMEions
#define ASSUME_ITS_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_O16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// O32 ASSUMEions
#define ASSUME_ITS_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_O32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// OI64 ASSUMEions
#define ASSUME_ITS_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_O64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// Hexadecimal ASSUMEions

// H8 ASSUMEions
#define ASSUME_ITS_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_H8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// H16 ASSUMEions
#define ASSUME_ITS_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_H16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// H32 ASSUMEions
#define ASSUME_ITS_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_H32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// H64 ASSUMEions
#define ASSUME_ITS_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_H64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// I8 ASSUMEions
#define ASSUME_ITS_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) == (int8_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) != (int8_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) >= (int8_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) <= (int8_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) > (int8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_I8(actual, expected) \
    TEST_ASSUME((int8_t)(actual) < (int8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// I16 ASSUMEions
#define ASSUME_ITS_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) == (int16_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) != (int16_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) >= (int16_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) <= (int16_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) > (int16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_I16(actual, expected) \
    TEST_ASSUME((int16_t)(actual) < (int16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// I32 ASSUMEions
#define ASSUME_ITS_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) == (int32_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) != (int32_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) >= (int32_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) <= (int32_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) > (int32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_I32(actual, expected) \
    TEST_ASSUME((int32_t)(actual) < (int32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// I64 ASSUMEions
#define ASSUME_ITS_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) == (int64_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) != (int64_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) >= (int64_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) <= (int64_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) > (int64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_I64(actual, expected) \
    TEST_ASSUME((int64_t)(actual) < (int64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// U8 ASSUMEions
#define ASSUME_ITS_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) == (uint8_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) != (uint8_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) >= (uint8_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) <= (uint8_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) > (uint8_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_U8(actual, expected) \
    TEST_ASSUME((uint8_t)(actual) < (uint8_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// U16 ASSUMEions
#define ASSUME_ITS_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) == (uint16_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) != (uint16_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) >= (uint16_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) <= (uint16_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) > (uint16_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_U16(actual, expected) \
    TEST_ASSUME((uint16_t)(actual) < (uint16_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// U32 ASSUMEions
#define ASSUME_ITS_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) == (uint32_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) != (uint32_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) >= (uint32_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) <= (uint32_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) > (uint32_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_U32(actual, expected) \
    TEST_ASSUME((uint32_t)(actual) < (uint32_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// U64 ASSUMEions
#define ASSUME_ITS_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) == (uint64_t)(expected), "Expected " #actual " to be equal to " #expected)

#define ASSUME_ITS_LESS_THAN_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to be less than " #expected)

#define ASSUME_ITS_MORE_THAN_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to be more than " #expected)

#define ASSUME_ITS_LESS_OR_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

#define ASSUME_ITS_MORE_OR_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

#define ASSUME_NOT_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) != (uint64_t)(expected), "Expected " #actual " to not be equal to " #expected)

#define ASSUME_NOT_LESS_THAN_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) >= (uint64_t)(expected), "Expected " #actual " to not be less than " #expected)

#define ASSUME_NOT_MORE_THAN_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) <= (uint64_t)(expected), "Expected " #actual " to not be more than " #expected)

#define ASSUME_NOT_LESS_OR_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) > (uint64_t)(expected), "Expected " #actual " to not be less than or equal to " #expected)

#define ASSUME_NOT_MORE_OR_EQUAL_U64(actual, expected) \
    TEST_ASSUME((uint64_t)(actual) < (uint64_t)(expected), "Expected " #actual " to not be more than or equal to " #expected)

// **************************************************
//
// Null pointer ASSUMEions (_CNULL)
//
// **************************************************

// ITS set
#define ASSUME_ITS_CNULL(actual) \
    TEST_ASSUME((actual) == xnull, "Expected " #actual " to be xnull")

#define ASSUME_NOT_CNULL(actual) \
    TEST_ASSUME((actual) != xnull, "Expected " #actual " to not be xnull")

// General pointer ASSUMEions (_PTR)

// ITS set
#define ASSUME_ITS_EQUAL_PTR(actual, expected) \
    TEST_ASSUME((actual) == (expected), "Expected pointer " #actual " to be equal to pointer " #expected " ")

#define ASSUME_NOT_EQUAL_PTR(actual, expected) \
    TEST_ASSUME((actual) != (expected), "Expected pointer " #actual " to not be equal to pointer " #expected " ")

// Size_t ASSUMEions

// Equal
#define ASSUME_ITS_EQUAL_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) == (size_t)(expected), "Expected " #actual " to be equal to " #expected)

// Less than
#define ASSUME_ITS_LESS_THAN_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) < (size_t)(expected), "Expected " #actual " to be less than " #expected)

// More than
#define ASSUME_ITS_MORE_THAN_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) > (size_t)(expected), "Expected " #actual " to be more than " #expected)

// Less or equal
#define ASSUME_ITS_LESS_OR_EQUAL_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) <= (size_t)(expected), "Expected " #actual " to be less than or equal to " #expected)

// More or equal
#define ASSUME_ITS_MORE_OR_EQUAL_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) >= (size_t)(expected), "Expected " #actual " to be more than or equal to " #expected)

// Not equal
#define ASSUME_NOT_EQUAL_SIZE(actual, expected) \
    TEST_ASSUME((size_t)(actual) != (size_t)(expected), "Expected " #actual " to not be equal to " #expected)

// **************************************************
//
// Range ASSUMEions
//
// **************************************************

// ASSUMEion for checking if a value is within a specified range
#define ASSUME_ITS_WITHIN_RANGE(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Unsigned integer type ASSUMEions

#define ASSUME_ITS_WITHIN_RANGE_U8(value, min, max) \
    TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_U8(value, min, max) \
    TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_U16(value, min, max) \
    TEST_ASSUME((uint16_t)(value) >= (uint16_t)(min) && (uint16_t)(value) <= (uint16_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_U16(value, min, max) \
    TEST_ASSUME((uint16_t)(value) < (uint16_t)(min) || (uint16_t)(value) > (uint16_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_U32(value, min, max) \
    TEST_ASSUME((uint32_t)(value) >= (uint32_t)(min) && (uint32_t)(value) <= (uint32_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_U32(value, min, max) \
    TEST_ASSUME((uint32_t)(value) < (uint32_t)(min) || (uint32_t)(value) > (uint32_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_U64(value, min, max) \
    TEST_ASSUME((uint64_t)(value) >= (uint64_t)(min) && (uint64_t)(value) <= (uint64_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_U64(value, min, max) \
    TEST_ASSUME((uint64_t)(value) < (uint64_t)(min) || (uint64_t)(value) > (uint64_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// Signed integer type ASSUMEions

#define ASSUME_ITS_WITHIN_RANGE_I8(value, min, max) \
    TEST_ASSUME((int8_t)(value) >= (int8_t)(min) && (int8_t)(value) <= (int8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_I8(value, min, max) \
    TEST_ASSUME((int8_t)(value) < (int8_t)(min) || (int8_t)(value) > (int8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_I16(value, min, max) \
    TEST_ASSUME((int16_t)(value) >= (int16_t)(min) && (int16_t)(value) <= (int16_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_I16(value, min, max) \
    TEST_ASSUME((int16_t)(value) < (int16_t)(min) || (int16_t)(value) > (int16_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_I32(value, min, max) \
    TEST_ASSUME((int32_t)(value) >= (int32_t)(min) && (int32_t)(value) <= (int32_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_I32(value, min, max) \
    TEST_ASSUME((int32_t)(value) < (int32_t)(min) || (int32_t)(value) > (int32_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_I64(value, min, max) \
    TEST_ASSUME((int64_t)(value) >= (int64_t)(min) && (int64_t)(value) <= (int64_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_I64(value, min, max) \
    TEST_ASSUME((int64_t)(value) < (int64_t)(min) || (int64_t)(value) > (int64_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// Floating point type ASSUMEions

#define ASSUME_ITS_WITHIN_RANGE_F32(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_F32(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_F64(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_F64(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Byte char type ASSUMEions (uint8_t)

#define ASSUME_ITS_WITHIN_RANGE_BCHAR(value, min, max) \
    TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_BCHAR(value, min, max) \
    TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// Char type ASSUMEions (char)

#define ASSUME_ITS_WITHIN_RANGE_CCHAR(value, min, max) \
    TEST_ASSUME((char)(value) >= (char)(min) && (char)(value) <= (char)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_CCHAR(value, min, max) \
    TEST_ASSUME((char)(value) < (char)(min) || (char)(value) > (char)(max), "Value " #value " is within range [" #min ", " #max "]")

// Wide char type ASSUMEions (wchar_t)

#define ASSUME_ITS_WITHIN_RANGE_WCHAR(value, min, max) \
    TEST_ASSUME((wchar_t)(value) >= (wchar_t)(min) && (wchar_t)(value) <= (wchar_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_WCHAR(value, min, max) \
    TEST_ASSUME((wchar_t)(value) < (wchar_t)(min) || (wchar_t)(value) > (wchar_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// **************************************************
//
// String ASSUMEions
//
// **************************************************

// Wide char string equality check
#define ASSUME_ITS_EQUAL_WSTR(actual, expected) \
    TEST_ASSUME(wcscmp((actual), (expected)) == 0, "Expected wide string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_WSTR(actual, expected) \
    TEST_ASSUME(wcscmp((actual), (expected)) != 0, "Expected wide string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_WSTR(actual, expected_len) \
    TEST_ASSUME(wcslen((actual)) == (expected_len), "Expected length of wide string " #actual " to be equal to " #expected_len)

// Byte string equality check
#define ASSUME_ITS_EQUAL_BSTR(actual, expected) \
    TEST_ASSUME(strcmp((const char*)(actual), (const char*)(expected)) == 0, "Expected byte string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_BSTR(actual, expected) \
    TEST_ASSUME(strcmp((const char*)(actual), (const char*)(expected)) != 0, "Expected byte string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_BSTR(actual, expected_len) \
    TEST_ASSUME(strlen((const char*)(actual)) == (expected_len), "Expected length of byte string " #actual " to be equal to " #expected_len)

// Classic C string equality check
#define ASSUME_ITS_EQUAL_CSTR(actual, expected) \
    TEST_ASSUME(strcmp((actual), (expected)) == 0, "Expected C string " #actual " to be equal to " #expected)

#define ASSUME_NOT_EQUAL_CSTR(actual, expected) \
    TEST_ASSUME(strcmp((actual), (expected)) != 0, "Expected C string " #actual " to not be equal to " #expected)

// For length comparison
#define ASSUME_ITS_LENGTH_EQUAL_CSTR(actual, expected_len) \
    TEST_ASSUME(strlen((actual)) == (expected_len), "Expected length of C string " #actual " to be equal to " #expected_len)

// **************************************************
//
// Array ASSUMEions
//
// **************************************************

// Array equality check
#define ASSUME_ITS_EQUAL_ARRAY(actual, expected, length) \
    for (size_t i = 0; i < (length); i++) { \
        TEST_ASSUME((actual)[i] == (expected)[i], "Expected array element " #actual " to be equal to " #expected); \
    }

// Array inequality check
#define ASSUME_NOT_EQUAL_ARRAY(actual, expected, length) \
    for (size_t i = 0; i < (length); i++) { \
        TEST_ASSUME((actual)[i] != (expected)[i], "Expected array element " #actual " to not be equal to " #expected); \
    }

// Array length check
#define ASSUME_ITS_LENGTH_EQUAL_ARRAY(actual_length, expected_length) \
    TEST_ASSUME((actual_length) == (expected_length), "Expected array length " #actual_length " to be equal to " #expected_length)

// Array element within range check
#define ASSUME_ITS_WITHIN_RANGE_ARRAY(array, min, max, length) \
    for (size_t i = 0; i < (length); i++) { \
        TEST_ASSUME((array)[i] >= (min) && (array)[i] <= (max), "Expected array element " #array " to be within range [" #min ", " #max "]"); \
    }

// Array element not within range check
#define ASSUME_NOT_WITHIN_RANGE_ARRAY(array, min, max, length) \
    for (size_t i = 0; i < (length); i++) { \
        TEST_ASSUME((array)[i] < (min) || (array)[i] > (max), "Expected array element " #array " to not be within range [" #min ", " #max "]"); \
    }

#ifdef __cplusplus
}
#endif

#endif