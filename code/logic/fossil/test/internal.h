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
#ifndef FOSSIL_TEST_CORE_H
#define FOSSIL_TEST_CORE_H

#define MAX_NAME_LENGTH 256

// Define color codes for output
#define FOSSIL_TEST_COLOR_RESET       "\033[0m"
#define FOSSIL_TEST_COLOR_RED         "\033[31m"
#define FOSSIL_TEST_COLOR_GREEN       "\033[32m"
#define FOSSIL_TEST_COLOR_YELLOW      "\033[33m"
#define FOSSIL_TEST_COLOR_BLUE        "\033[34m"
#define FOSSIL_TEST_COLOR_MAGENTA     "\033[35m"
#define FOSSIL_TEST_COLOR_CYAN        "\033[36m"
#define FOSSIL_TEST_COLOR_WHITE       "\033[37m"

// Define text attributes
#define FOSSIL_TEST_ATTR_BOLD         "\033[1m"
#define FOSSIL_TEST_ATTR_UNDERLINE    "\033[4m"
#define FOSSIL_TEST_ATTR_REVERSED     "\033[7m"
#define FOSSIL_TEST_ATTR_BLINK        "\033[5m"
#define FOSSIL_TEST_ATTR_HIDDEN       "\033[8m"
#define FOSSIL_TEST_ATTR_NORMAL       "\033[22m"

#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define data structures for Jellyfish AI
typedef struct {
    char key[MAX_INPUT_SIZE];
    char value[MAX_MEMORY_SIZE];
} jellyfish_memory_t;

typedef struct {
    char user_input[MAX_INPUT_SIZE];
    char ai_response[MAX_RESPONSE_SIZE];
} jellyfish_interaction_t;

typedef struct {
    char hypothesis[MAX_RESPONSE_SIZE];
    char evidence[MAX_RESPONSE_SIZE];
} jellyfish_reasoning_t;

typedef struct {
    char concepts[MAX_INPUT_SIZE];
    char details[MAX_RESPONSE_SIZE];
} jellyfish_learning_t;

typedef struct {
    jellyfish_memory_t *memory; // Dynamic memory
    jellyfish_interaction_t *interactions; // Dynamic memory
    jellyfish_reasoning_t *reasoning; // Dynamic memory
    jellyfish_learning_t *learning; // Dynamic memory
    int memory_count;
    int interaction_count;
    int reasoning_count;
    int learning_count;
    char context[MAX_INPUT_SIZE];
    char personality[MAX_INPUT_SIZE];
    bool is_initialized;
} jellyfish_ai_t;



typedef enum {
    FOSSIL_TEST_FORMAT_PLAIN,    // Plain text format
    FOSSIL_TEST_FORMAT_CHART,    // Chart format
    FOSSIL_TEST_FORMAT_TABLE,    // Table format
    FOSSIL_TEST_FORMAT_MARKDOWN, // Markdown format
    FOSSIL_TEST_FORMAT_JELLYFISH // Jellyfish format
} fossil_test_format_t;

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
 * @var fossil_test_options_t::color_output
 * Flag to enable or disable colorized output in the console.
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
    bool fail_fast;
    bool quiet;
    bool color_output;
    fossil_test_format_t format; // Store the format type
} fossil_test_options_t;


/**
 * Prints a string to the output.
 *
 * @param str The string to be printed.
 */
void internal_test_puts(const char *str);

/**
 * Prints a formatted string to the output.
 *
 * @param format The format string.
 * @param ... The additional arguments to be formatted.
 */
void internal_test_printf(const char *format, ...);

/**
 * Prints a string to the output with a specified color.
 *
 * @param color The color code to be applied.
 * @param format The format string.
 * @param ... The additional arguments to be formatted.
 */
void internal_test_print_color(const char *color, const char *format, ...);

/**
 * Prints a character to the output.
 *
 * @param c The character to be printed.
 */
void internal_test_putchar(char c);

/**
 * Prints a character to the output with a specified color.
 *
 * @param c The character to be printed.
 * @param color The color code to be applied.
 */
void internal_test_putchar_color(char c, const char *color);

// Function declarations
void jellyfish_ai_init(jellyfish_ai_t *ai);
void jellyfish_ai_cleanup(jellyfish_ai_t *ai);
// Fossil Test integration
void jellyfish_ai_log_interaction(jellyfish_ai_t *ai, const char *input, const char *response);
void jellyfish_ai_log_memory(jellyfish_ai_t *ai, const char *key, const char *value);
void jellyfish_ai_log_reasoning(jellyfish_ai_t *ai, const char *hypothesis, const char *evidence);
void jellyfish_ai_log_learning(jellyfish_ai_t *ai, const char *concept, const char *details);

// Optional utility for test result analysis
const char* jellyfish_ai_generate_response(jellyfish_ai_t *ai, const char *input);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_TEST_CORE_H
