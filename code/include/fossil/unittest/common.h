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

#endif
