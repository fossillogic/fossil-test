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
#ifndef FOSSIL_TEST_COMMON_H
#define FOSSIL_TEST_COMMON_H

#ifdef _WIN32
#include <Windows.h>
#else
#define _GNU_SOURCE  // Define _GNU_SOURCE for C code
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/utsname.h>
#include <unistd.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#else
#include <sys/sysinfo.h>
#endif
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

// becuase Microsoft had to be diffrent
#ifdef _WIN32
#define wcsncasecmp _wcsnicmp
#endif

// Used in floating-point asserts
#define FOSSIL_TEST_FLOAT_EPSILON 1e-6
#define FOSSIL_TEST_DOUBLE_EPSILON 1e-9

#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
/**
 * @brief Definition for xnull pointers in C++11 and later or C23 and later.
 *
 * In C++11 or later, `xnullptr` is a keyword representing a xnull pointer constant.
 * In C23 or later, `_xnullptr` is recognized in the same way as C++.
 */
    #define xnull    nullptr
    #define xnullptr nullptr
    #define xterm '\0'
#else
    #if defined(_WIN64) || defined(_WIN32)
/**
 * @brief Definition for xnull pointers on Windows systems.
 *
 * For Windows (both 32-bit and 64-bit), we define `xnull` and `xnullptr` as 0.
 */
    #define xnull    0
    #define xnullptr 0
    #define xterm '\0'
    #else
/**
 * @brief Definition for xnull pointers on POSIX systems, macOS, and embedded systems.
 *
 * For POSIX, macOS, and embedded systems, we define `xnull` and `xnullptr` as a void pointer to 0.
 */
    #define xnull    (void *)(0)
    #define xnullptr (void *)(0)
    #define xterm '\0'
    #endif
#endif

// Custom implementation of strdup
static inline char* _custom_fossil_test_strdup(const char* str) {
    if (!str) return xnull; // Handle NULL pointer gracefully

    size_t len = 0;
    while (str[len] != '\0') len++; // Calculate the length of the string

    char* dup = (char*)malloc((len + 1) * sizeof(char)); // Allocate memory for the duplicate string
    if (!dup) return xnull; // Check if malloc failed

    for (size_t i = 0; i < len; i++) {
        dup[i] = str[i]; // Copy each character from the original string to the duplicate
    }
    dup[len] = '\0'; // Add null terminator to the end of the duplicate string

    return dup;
}

#endif
