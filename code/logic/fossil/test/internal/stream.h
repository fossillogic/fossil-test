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
#ifndef FOSSIL_TEST_INTERNAL_STREAM_H
#define FOSSIL_TEST_INTERNAL_STREAM_H

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

/**
 * Structure representing a file stream.
 */
typedef struct {
    FILE *file;         // Pointer to the FILE structure for the stream
    char filename[500]; // Array to store the filename
} fossil_fstream_t;

extern fossil_fstream_t *FOSSIL_STDIN;
extern fossil_fstream_t *FOSSIL_STDOUT;
extern fossil_fstream_t *FOSSIL_STDERR;

#define FOSSIL_STDIN  (FOSSIL_STDIN)
#define FOSSIL_STDOUT (FOSSIL_STDOUT)
#define FOSSIL_STDERR (FOSSIL_STDERR)

extern int32_t FOSSIL_IO_COLOR_ENABLE; // Flag to enable/disable color output

/** 
 * This code provides a robust set of functions for formatting and manipulating terminal output, 
 * allowing developers to apply color, text attributes (like bold, underline, etc.), and cursor positioning 
 * to improve the visual appeal and functionality of text-based applications. The functionality is primarily 
 * based on ANSI escape sequences, which are widely supported in most terminal environments (such as Linux terminals, 
 * macOS Terminal, and Windows terminals that support ANSI escape codes).
 *
 * The core concept behind this system is a simple markup language that allows developers to specify formatting 
 * instructions within the text output. These instructions are enclosed in curly braces `{}` within the format string 
 * and are processed dynamically to change the appearance of the text. The markup supports various styles, such as:
 * 
 * 1. **Colors** - The code includes a set of predefined color codes for changing the foreground color of text. 
 *    Supported colors include basic colors (e.g., red, green, blue) and bright colors (e.g., bright red, bright green, etc.).
 *    The colors are implemented using ANSI escape sequences and can be easily extended to support more colors if needed.
 *
 * 2. **Attributes** - Text attributes can be applied to the text to change its appearance. These attributes include:
 *    - **Bold** (for making text bold)
 *    - **Underline** (for adding an underline to the text)
 *    - **Reversed** (for inverting the colors of the text and background)
 *    - **Blink** (for making text blink)
 *    - **Hidden** (for hiding the text)
 *    - **Normal** (for reverting text back to its normal form, removing any attributes)
 *
 * 3. **Positioning** - The code introduces a flexible way to manipulate the position of the text in the terminal using 
 *    named positions such as `top`, `bottom`, `left`, and `right`. These positions allow for text to be dynamically 
 *    placed at specific locations on the terminal screen, enhancing the user experience for applications requiring 
 *    more control over text layout and movement. The positions are marked with `pos:` followed by the desired 
 *    position name (e.g., `{pos:top}` or `{pos:left}`).
 * 
 * 4. **Flexibility and Extendability** - The markup language allows for the use of multiple color and attribute 
 *    specifications in a single string. The color and attribute specifications can be combined, for instance, 
 *    `{red,bold}` for red and bold text, or `{green,underline}` for green and underlined text. This allows for 
 *    fine-grained control over the text output. The system is flexible enough to be extended with more attributes, 
 *    colors, and positioning options as required.
 *
 * 5. **Implementation Details** - The function `pizza_io_print_with_attributes` processes the format string 
 *    provided to it, looking for `{}` markers. When it encounters a `{}`, it checks if the enclosed string specifies 
 *    a color, attribute, or position, and then calls the respective helper functions (`pizza_io_apply_color` and 
 *    `pizza_io_apply_attribute`) to modify the terminal output accordingly. If a position marker is found (e.g., 
 *    `{pos:top}`), it adjusts the cursor position in the terminal to the specified location. The code uses standard 
 *    C string manipulation functions like `strchr`, `strncpy`, and `vsnprintf` to process the format string and apply 
 *    the requested changes to the output.
 * 
 * In summary, this system provides a highly customizable and intuitive way to format terminal text with colors, 
 * attributes, and positions, making it ideal for developers who want to build visually rich and interactive 
 * command-line interfaces. The markup-based approach is simple to use and can be easily extended to meet the 
 * needs of more complex applications.
 */

/**
 * Redirects the output to a specified stream.
 *
 * This function allows you to change the default output destination to a custom stream.
 * It is useful when you want to redirect output to a file or another output stream.
 *
 * @param stream The output stream where subsequent output should be redirected.
 */
void pizza_io_redirect_output(fossil_fstream_t *stream);

/**
 * Prints a string to the output.
 * 
 * This function outputs the provided string `str` to the terminal or console. It is a simple utility function
 * that can be used for printing plain text to the screen. The string is printed as-is, with no formatting or
 * color modifications applied.
 *
 * @param str The string to be printed. This should be a null-terminated string.
 */
void pizza_io_puts(const char *str);

/** 
 * Prints a formatted string to the output.
 *
 * This function allows for formatted output, similar to `printf`. It takes a format string that can include
 * format specifiers (e.g., `%d`, `%s`, `%f`), and the additional arguments provided will be formatted accordingly.
 * The function uses a variable argument list (`...`) to handle a wide variety of format specifiers and argument types.
 * 
 * The format string can also include custom formatting markers enclosed in curly braces `{}`, such as `{red}` for
 * color or `{bold}` for text attributes, which will be processed and applied to the output.
 *
 * Example usage:
 * ```c
 * pizza_io_printf("Hello, %s! Your score is %d\n", "Alice", 95);
 * ```
 *
 * @param format The format string, which contains the text to be printed, along with format specifiers.
 * @param ... The additional arguments to be formatted. These arguments are inserted into the format string
 *            in the order they appear, based on the format specifiers.
 */
void pizza_io_printf(const char *format, ...);

/**
 * Prints a character to the output.
 * 
 * This function is a basic utility to print a single character to the output. It is especially useful when you
 * need to print individual characters rather than strings or formatted text.
 *
 * Example usage:
 * ```c
 * pizza_io_putchar('A');
 * ```
 *
 * @param c The character to be printed. This should be a single character.
 */
void pizza_io_putchar(char c);

/**
 * Prints a string to the specified output stream.
 * 
 * This function is similar to `pizza_io_puts`, but instead of printing to the standard output, it allows you
 * to specify an output stream (like a file or a custom output stream). This can be useful when writing to files
 * or other output destinations.
 *
 * Example usage:
 * ```c
 * FILE *file = fopen("output.txt", "w");
 * pizza_io_fputs(file, "Hello, File Output!\n");
 * fclose(file);
 * ```
 *
 * @param stream The output stream where the string should be printed. This should be a valid pointer to a `FILE` object.
 * @param str The string to be printed. This should be a null-terminated string.
 */
void pizza_io_fputs(fossil_fstream_t *stream, const char *str);

/**
 * Prints a formatted string to the specified output stream.
 * 
 * This function is similar to `pizza_io_printf`, but instead of printing to the standard output, it allows you
 * to specify an output stream. The format string can include format specifiers and custom formatting markers, just
 * like `pizza_io_printf`. This can be useful when writing formatted text to files or other output destinations.
 *
 * Example usage:
 * ```c
 * FILE *file = fopen("output.txt", "w");
 * pizza_io_fprintf(file, "Hello, %s! Your score is %d\n", "Alice", 95);
 * fclose(file);
 * ```
 *
 * @param stream The output stream where the formatted string should be printed. This should be a valid pointer to a `FILE` object.
 * @param format The format string, which contains the text to be printed, along with format specifiers.
 * @param ... The additional arguments to be formatted. These arguments are inserted into the format string
 *            in the order they appear, based on the format specifiers.
 */
void pizza_io_fprintf(fossil_fstream_t *stream, const char *format, ...);

// TUI part of the API

/**
 * Clears the terminal screen.
 *
 * This function sends the ANSI escape sequence to clear the terminal screen
 * and move the cursor to the top-left corner. It is useful when creating full-screen
 * terminal applications or refreshing the display.
 */
void pizza_io_clear_screen(void);

/**
 * Moves the cursor to a specific row and column on the terminal.
 *
 * @param row The row position (starting from 1).
 * @param col The column position (starting from 1).
 */
void pizza_io_move_cursor(int row, int col);

/**
 * Hides the cursor from the terminal screen.
 *
 * This is useful for creating cleaner UIs without a blinking cursor.
 */
void pizza_io_hide_cursor(void);

/**
 * Shows the cursor on the terminal screen.
 */
void pizza_io_show_cursor(void);

/**
 * Draws a horizontal line using a specified character.
 *
 * @param length The number of characters to draw.
 * @param ch The character to use for drawing.
 */
void pizza_io_draw_horizontal_line(int length, char ch);

/**
 * Draws a vertical line using a specified character.
 *
 * @param length The number of characters to draw.
 * @param ch The character to use for drawing.
 */
void pizza_io_draw_vertical_line(int length, char ch);

/**
 * Flushes the output stream, ensuring all buffered text is written.
 *
 * Useful when mixing multiple output functions or when printing from threads.
 */
void pizza_io_flush(void);

#ifdef __cplusplus
}
#endif

#endif // FOSSIL_TEST_CORE_H
