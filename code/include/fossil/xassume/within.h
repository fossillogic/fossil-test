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
#ifndef FSCL_XTEST_ASSUME_WITHIN_TYPE_H
#define FSCL_XTEST_ASSUME_WITHIN_TYPE_H

#include <fossil/xtest.h> // using assurt rules from Fossil Test
#include <stddef.h> // for size_t
#include <stdint.h> // for integer types
#include <wchar.h> // for wide char types
#include <wctype.h> // for wide char types
#include <ctype.h> // for char types

#ifdef __cplusplus
extern "C"
{
#endif

// Assertion for checking if a value is within a specified range
#define ASSUME_ITS_WITHIN_RANGE(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Unsigned integer type assertions

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

// Signed integer type assertions

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

// Floating point type assertions

#define ASSUME_ITS_WITHIN_RANGE_F32(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_F32(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

#define ASSUME_ITS_WITHIN_RANGE_F64(value, min, max) \
    TEST_ASSUME((value) >= (min) && (value) <= (max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_F64(value, min, max) \
    TEST_ASSUME((value) < (min) || (value) > (max), "Value " #value " is within range [" #min ", " #max "]")

// Byte char type assertions (uint8_t)

#define ASSUME_ITS_WITHIN_RANGE_BCHAR(value, min, max) \
    TEST_ASSUME((uint8_t)(value) >= (uint8_t)(min) && (uint8_t)(value) <= (uint8_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_BCHAR(value, min, max) \
    TEST_ASSUME((uint8_t)(value) < (uint8_t)(min) || (uint8_t)(value) > (uint8_t)(max), "Value " #value " is within range [" #min ", " #max "]")

// Char type assertions (char)

#define ASSUME_ITS_WITHIN_RANGE_CCHAR(value, min, max) \
    TEST_ASSUME((char)(value) >= (char)(min) && (char)(value) <= (char)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_CCHAR(value, min, max) \
    TEST_ASSUME((char)(value) < (char)(min) || (char)(value) > (char)(max), "Value " #value " is within range [" #min ", " #max "]")

// Wide char type assertions (wchar_t)

#define ASSUME_ITS_WITHIN_RANGE_WCHAR(value, min, max) \
    TEST_ASSUME((wchar_t)(value) >= (wchar_t)(min) && (wchar_t)(value) <= (wchar_t)(max), "Value " #value " is not within range [" #min ", " #max "]")

#define ASSUME_NOT_WITHIN_RANGE_WCHAR(value, min, max) \
    TEST_ASSUME((wchar_t)(value) < (wchar_t)(min) || (wchar_t)(value) > (wchar_t)(max), "Value " #value " is within range [" #min ", " #max "]")

#ifdef __cplusplus
}
#endif

#endif
