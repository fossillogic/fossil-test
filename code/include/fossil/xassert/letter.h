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
#ifndef FOSSIL_TEST_ASSERT_CHARS_TYPE_H
#define FOSSIL_TEST_ASSERT_CHARS_TYPE_H

#include <fossil/unittest.h> // using assurt rules from Fossil Test
#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C"
{
#endif

// Unsigned char type assertions (uint8_t)

#define ASSERT_ITS_EQUAL_BCHAR(value, expected) \
    TEST_ASSERT((uint8_t)(value) == (uint8_t)(expected), "Expected " #value " to be equal to " #expected)

#define ASSERT_NOT_EQUAL_BCHAR(value, expected) \
    TEST_ASSERT((uint8_t)(value) != (uint8_t)(expected), "Expected " #value " to not be equal to " #expected)

// Char type assertions (char)

#define ASSERT_ITS_EQUAL_CHAR(value, expected) \
    TEST_ASSERT((char)(value) == (char)(expected), "Expected " #value " to be equal to " #expected)

#define ASSERT_NOT_EQUAL_CHAR(value, expected) \
    TEST_ASSERT((char)(value) != (char)(expected), "Expected " #value " to not be equal to " #expected)

// Wide char type assertions (wchar_t)

#define ASSERT_ITS_EQUAL_WCHAR(value, expected) \
    TEST_ASSERT((wchar_t)(value) == (wchar_t)(expected), "Expected " #value " to be equal to " #expected)

#define ASSERT_NOT_EQUAL_WCHAR(value, expected) \
    TEST_ASSERT((wchar_t)(value) != (wchar_t)(expected), "Expected " #value " to not be equal to " #expected)

#ifdef __cplusplus
}
#endif

#endif
