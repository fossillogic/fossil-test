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
#ifndef FOSSIL_TEST_EXPECT_CHARS_TYPE_H
#define FOSSIL_TEST_EXPECT_CHARS_TYPE_H

#include <fossil/unittest/framework.h> // using assurt rules from Fossil Test
#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C"
{
#endif

// Unsigned char type assertions (uint8_t)

#define EXPECT_ITS_EQUAL_BCHAR(value, expected) \
    TEST_EXPECT((uint8_t)(value) == (uint8_t)(expected), "Expected " #value " to be equal to " #expected)

#define EXPECT_NOT_EQUAL_BCHAR(value, expected) \
    TEST_EXPECT((uint8_t)(value) != (uint8_t)(expected), "Expected " #value " to not be equal to " #expected)

// Char type assertions (char)

#define EXPECT_ITS_EQUAL_CHAR(value, expected) \
    TEST_EXPECT((char)(value) == (char)(expected), "Expected " #value " to be equal to " #expected)

#define EXPECT_NOT_EQUAL_CHAR(value, expected) \
    TEST_EXPECT((char)(value) != (char)(expected), "Expected " #value " to not be equal to " #expected)

// Wide char type assertions (wchar_t)

#define EXPECT_ITS_EQUAL_WCHAR(value, expected) \
    TEST_EXPECT((wchar_t)(value) == (wchar_t)(expected), "Expected " #value " to be equal to " #expected)

#define EXPECT_NOT_EQUAL_WCHAR(value, expected) \
    TEST_EXPECT((wchar_t)(value) != (wchar_t)(expected), "Expected " #value " to not be equal to " #expected)

#ifdef __cplusplus
}
#endif

#endif
