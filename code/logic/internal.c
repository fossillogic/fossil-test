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
#include "fossil/test/internal.h"

#define BORDER_CHAR_TOP_BOTTOM '='
#define BORDER_CHAR_SIDE       '|'
#define BORDER_CORNER          '+'
#define TUI_MAX_WIDTH          80

static void tui_apply_color(fossil_test_env_t *env, const char *color) {
    if (env && env->options.color_output && color) {
        fputs(color, stdout);
    }
}

static void tui_reset_color(fossil_test_env_t *env) {
    if (env && env->options.color_output) {
        fputs(FOSSIL_TEST_COLOR_RESET, stdout);
    }
}

static void tui_draw_border(fossil_test_env_t *env, char ch) {
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CORNER);
    for (int i = 0; i < TUI_MAX_WIDTH - 2; ++i) {
        putchar(ch);
    }
    putchar(BORDER_CORNER);
    putchar('\n');
    tui_reset_color(env);
}

void fossil_test_tui_border(fossil_test_env_t *env) {
    if (env->options.color_output) {
        printf(FOSSIL_TEST_COLOR_BLUE FOSSIL_TEST_ATTR_BOLD);
    }
    for (int i = 0; i < 70; ++i) putchar(BORDER_CHAR_TOP_BOTTOM);
    printf(FOSSIL_TEST_COLOR_RESET "\n");
}

void fossil_test_tui_message(fossil_test_env_t *env, const char *title, const char *fmt, ...) {
    tui_draw_border(env, BORDER_CHAR_TOP_BOTTOM);

    // Print title
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    tui_apply_color(env, FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD);
    int padding = (TUI_MAX_WIDTH - 2 - (int)strlen(title)) / 2;
    for (int i = 0; i < padding; ++i) putchar(' ');
    fputs(title, stdout);
    for (int i = 0; i < TUI_MAX_WIDTH - 2 - padding - (int)strlen(title); ++i) putchar(' ');
    tui_reset_color(env);
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    putchar('\n');

    // Print message
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    tui_apply_color(env, FOSSIL_TEST_COLOR_CYAN);
    putchar(' ');
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    int printed = vsnprintf(NULL, 0, fmt, args);
    for (int i = printed + 1; i < TUI_MAX_WIDTH - 2; ++i) putchar(' ');
    tui_reset_color(env);
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    putchar('\n');

    tui_draw_border(env, BORDER_CHAR_TOP_BOTTOM);
}

void fossil_test_tui_widget(fossil_test_env_t *env, const char *label, const char *value) {
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    putchar(' ');

    tui_apply_color(env, FOSSIL_TEST_COLOR_CYAN);
    printf("%s", label);
    tui_apply_color(env, FOSSIL_TEST_COLOR_WHITE);
    printf(": %s", value);

    int padding = TUI_MAX_WIDTH - 4 - (int)(strlen(label) + 2 + strlen(value));
    for (int i = 0; i < padding; ++i) putchar(' ');

    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(' ');
    putchar(BORDER_CHAR_SIDE);
    putchar('\n');
    tui_reset_color(env);
}

void fossil_test_tui_title(fossil_test_env_t *env, const char *title) {
    int len = (int)strlen(title);
    int total = TUI_MAX_WIDTH - 4; // borders + spaces
    int padding = (total - len) / 2;

    // Top border
    tui_draw_border(env, BORDER_CHAR_TOP_BOTTOM);

    // Title line
    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(BORDER_CHAR_SIDE);
    putchar(' ');

    for (int i = 0; i < padding; ++i) putchar(' ');

    tui_apply_color(env, FOSSIL_TEST_COLOR_CYAN FOSSIL_TEST_ATTR_BOLD);
    fputs(title, stdout);
    tui_reset_color(env);

    for (int i = 0; i < total - padding - len; ++i) putchar(' ');

    tui_apply_color(env, FOSSIL_TEST_COLOR_BLUE);
    putchar(' ');
    putchar(BORDER_CHAR_SIDE);
    putchar('\n');

    // Bottom border
    tui_draw_border(env, BORDER_CHAR_TOP_BOTTOM);
}
