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
#ifndef FOSSIL_TEST_COMMANDS_H
#define FOSSIL_TEST_COMMANDS_H

#include "fossil/_common/common.h"
#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Define the structure to hold parsed options
typedef struct {
    bool show_version;
    bool show_help;
    bool show_tip;
    bool show_info;
    bool show_author;
    bool only_tags;
    char only_tags_value[256];
    bool reverse;
    bool repeat_enabled;
    int repeat_count;
    bool shuffle_enabled;
    bool verbose_enabled;
    int verbose_level; // 0 for cutback, 1 for normal, 2 for verbose
    bool list_tests;
    bool summary_enabled;
    bool color_enabled;
    bool sanity_enabled;
} fossil_options_t;

extern fossil_options_t _CLI;

/**
 * Function to initialize the options structure.
 * 
 * @return The options structure
 */
fossil_options_t fossil_options_parse(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
