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
#ifndef FOSSIL_TEST_ASSUME_STRING_TYPE_H
#define FOSSIL_TEST_ASSUME_STRING_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test
#include <wchar.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif

#endif
