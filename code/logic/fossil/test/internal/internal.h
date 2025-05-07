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
#ifndef FOSSIL_TEST_CORE_H
#define FOSSIL_TEST_CORE_H

#define MAX_NAME_LENGTH 256

#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <float.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FOSSIL_TEST_FORMAT_PLAIN,
    FOSSIL_TEST_FORMAT_CI,
    FOSSIL_TEST_FORMAT_JELLYFISH
} fossil_test_format_t;

typedef enum {
    FOSSIL_TEST_SUMMARY_PLAIN,
    FOSSIL_TEST_SUMMARY_CI,
    FOSSIL_TEST_SUMMARY_JELLYFISH
} fossil_test_summary_t;

/**
 * @struct fossil_test_options_t
 * @brief Structure to hold various options for fossil testing.
 * 
 * This structure contains various flags and parameters that control the behavior of the fossil testing framework.
 * 
 * @var fossil_test_options_t::show_version
 * Flag to indicate if the version information should be displayed.
 * 
 * @var fossil_test_options_t::show_help
 * Flag to indicate if the help information should be displayed.
 * 
 * @var fossil_test_options_t::show_info
 * Flag to indicate if additional information should be displayed.
 * 
 * @var fossil_test_options_t::reverse
 * Flag to indicate if the order of tests should be reversed.
 * 
 * @var fossil_test_options_t::repeat_enabled
 * Flag to indicate if test repetition is enabled.
 * 
 * @var fossil_test_options_t::repeat_count
 * Number of times to repeat the tests if repetition is enabled.
 * 
 * @var fossil_test_options_t::shuffle_enabled
 * Flag to indicate if the tests should be shuffled.
 * 
 * @var fossil_test_options_t::dry_run
 * Flag to indicate if the tests should be run in dry-run mode (no actual execution).
 * 
 * @var fossil_test_options_t::fail_fast
 * Flag to enable fail-fast behavior, stopping test execution after the first failure.
 * 
 * @var fossil_test_options_t::quiet
 * Flag to suppress most non-essential output for minimal console logging.
 * 
 */
typedef struct {
    bool show_version;
    bool show_help;
    bool show_info;
    bool reverse;
    bool repeat_enabled;
    int32_t repeat_count;
    bool shuffle_enabled;
    bool dry_run;
    fossil_test_summary_t summary;     // Replaces 'quiet'
    fossil_test_format_t format;       // Store the format type
} fossil_test_options_t;


#ifdef __cplusplus
}
#endif

#endif // FOSSIL_TEST_CORE_H
