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
#ifndef FOSSIL_TEST_ASSUME_NUMERIC_TYPE_H
#define FOSSIL_TEST_ASSUME_NUMERIC_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Octal assertions

// O8 Assertions
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

// O16 Assertions
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

// O32 Assertions
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

// OI64 Assertions
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

// Hexadecimal assertions

// H8 Assertions
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

// H16 Assertions
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

// H32 Assertions
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

// H64 Assertions
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

// I8 Assertions
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

// I16 Assertions
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

// I32 Assertions
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

// I64 Assertions
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

// U8 Assertions
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

// U16 Assertions
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

// U32 Assertions
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

// U64 Assertions
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

#ifdef __cplusplus
}
#endif

#endif
