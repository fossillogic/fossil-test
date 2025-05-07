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
#ifndef FOSSIL_TEST_COMMON_H
#define FOSSIL_TEST_COMMON_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Memory management
// *****************************************************************************

// Define pizza_sys_memory_t as void*
typedef void* pizza_sys_memory_t;

/**
 * Allocate memory.
 *
 * @param size The size of the memory to allocate.
 * @return A pointer to the allocated memory.
 * @throws Error message and exits if allocation fails.
 */
pizza_sys_memory_t pizza_sys_memory_alloc(size_t size);

/**
 * Reallocate memory.
 *
 * @param ptr A pointer to the previously allocated memory.
 * @param size The new size of the memory to allocate.
 * @return A pointer to the reallocated memory.
 * @throws Error message and exits if reallocation fails or if the pointer is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_realloc(pizza_sys_memory_t ptr, size_t size);

/**
 * Allocate and zero memory.
 *
 * @param num The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated and zeroed memory.
 * @throws Error message and exits if allocation fails.
 */
pizza_sys_memory_t pizza_sys_memory_calloc(size_t num, size_t size);

/**
 * Initialize allocated memory to a known state.
 *
 * @param ptr A pointer to the allocated memory.
 * @param size The size of the memory.
 * @param value The value to initialize the memory with (e.g., zero).
 * @return A pointer to the initialized memory.
 */
pizza_sys_memory_t pizza_sys_memory_init(pizza_sys_memory_t ptr, size_t size, int32_t value);

/**
 * Free memory.
 *
 * @param ptr A pointer to the memory to free.
 * @throws Error message and exits if the pointer is NULL.
 */
void pizza_sys_memory_free(pizza_sys_memory_t ptr);

/**
 * Copy memory.
 *
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param size The size of the memory to copy.
 * @return A pointer to the destination memory.
 * @throws Error message and exits if copying fails or if either source or destination is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_copy(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size);

/**
 * Set memory.
 *
 * @param ptr A pointer to the memory to set.
 * @param value The value to set.
 * @param size The size of the memory to set.
 * @return A pointer to the memory.
 * @throws Error message and exits if setting fails or if the pointer is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_set(pizza_sys_memory_t ptr, int32_t value, size_t size);

/**
 * Duplicate memory.
 *
 * @param src A pointer to the memory to duplicate.
 * @param size The size of the memory to duplicate.
 * @return A pointer to the duplicated memory.
 * @throws Error message and exits if duplication fails or if the source is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_dup(const pizza_sys_memory_t src, size_t size);

/**
 * Zero memory.
 *
 * @param ptr A pointer to the memory to zero.
 * @param size The size of the memory to zero.
 * @throws Error message and exits if the pointer is NULL.
 */
void pizza_sys_memory_zero(pizza_sys_memory_t ptr, size_t size);

/**
 * Compare memory.
 *
 * @param ptr1 A pointer to the first memory.
 * @param ptr2 A pointer to the second memory.
 * @param size The size of the memory to compare.
 * @return The result of the comparison.
 * @throws Error message and exits if the pointers are NULL or if the size is zero.
 */
int pizza_sys_memory_compare(const pizza_sys_memory_t ptr1, const pizza_sys_memory_t ptr2, size_t size);

/**
 * Move memory.
 *
 * @param dest A pointer to the destination memory.
 * @param src A pointer to the source memory.
 * @param size The size of the memory to move.
 * @return A pointer to the destination memory.
 * @throws Error message and exits if moving fails or if either source or destination is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_move(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size);

/**
 * Resize memory.
 *
 * @param ptr A pointer to the memory to resize.
 * @param old_size The old size of the memory.
 * @param new_size The new size of the memory.
 * @return A pointer to the resized memory.
 * @throws Error message and exits if resizing fails or if the pointer is NULL.
 */
pizza_sys_memory_t pizza_sys_memory_resize(pizza_sys_memory_t ptr, size_t old_size, size_t new_size);

/**
 * Check if a memory pointer is valid.
 *
 * @param ptr A pointer to the memory.
 * @return 1 if the memory is valid, 0 otherwise.
 */
bool pizza_sys_memory_is_valid(const pizza_sys_memory_t ptr);

// *****************************************************************************
// output management
// *****************************************************************************

/**
 * Structure representing a file stream.
 */
typedef struct {
    FILE *file;         // Pointer to the FILE structure for the stream
    char filename[500]; // Array to store the filename
} pizza_fstream_t;

extern pizza_fstream_t *PIZZA_STDIN;
extern pizza_fstream_t *PIZZA_STDOUT;
extern pizza_fstream_t *PIZZA_STDERR;

#define PIZZA_STDIN  (PIZZA_STDIN)
#define PIZZA_STDOUT (PIZZA_STDOUT)
#define PIZZA_STDERR (PIZZA_STDERR)

extern int32_t PIZZA_IO_COLOR_ENABLE; // Flag to enable/disable color output

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
void pizza_io_redirect_output(pizza_fstream_t *stream);

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
void pizza_io_fputs(pizza_fstream_t *stream, const char *str);

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
void pizza_io_fprintf(pizza_fstream_t *stream, const char *format, ...);

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

// *****************************************************************************
// string management
// *****************************************************************************

/* Type definitions */
typedef char* cstr;
typedef const char* ccstr;

/**
 * @brief Creates a new cstr with the given initial value.
 * 
 * @param init The initial value for the cstr.
 * @return A new cstr initialized with the given value.
 */
cstr pizza_io_cstr_create(const char *init);

/**
 * @brief Frees the memory allocated for the given cstr.
 * 
 * @param str The cstr to be freed.
 */
void pizza_io_cstr_free(cstr str);

/**
 * @brief Creates a copy of the given cstr.
 * 
 * @param str The cstr to be copied.
 * @return A new cstr that is a copy of the given cstr.
 */
cstr pizza_io_cstr_copy(ccstr str);

/**
 * @brief Duplicates the given cstr.
 * 
 * @param str The cstr to be duplicated.
 * @return A new cstr that is a duplicate of the given cstr.
 */
cstr pizza_io_cstr_dup(ccstr str);

/**
 * @brief Concatenates two cstrings into a new cstr.
 * 
 * @param s1 The first cstr.
 * @param s2 The second cstr.
 * @return A new cstr that is the concatenation of s1 and s2.
 */
cstr pizza_io_cstr_concat(ccstr s1, ccstr s2);

/**
 * @brief Returns the length of the given cstr.
 * 
 * @param str The cstr whose length is to be determined.
 * @return The length of the given cstr.
 */
size_t pizza_io_cstr_length(ccstr str);

/**
 * @brief Compares two cstrings.
 * 
 * @param s1 The first cstr.
 * @param s2 The second cstr.
 * @return An integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
int pizza_io_cstr_compare(ccstr s1, ccstr s2);

/**
 * @brief Trims whitespace from the beginning and end of the given cstr.
 * 
 * @param str The cstr to be trimmed.
 */
void pizza_io_cstr_trim(cstr str);

/**
 * @brief Splits the given cstr by the specified delimiter.
 * 
 * @param str The cstr to be split.
 * @param delimiter The character to split the cstr by.
 * @param count Pointer to a size_t variable where the number of resulting substrings will be stored.
 * @return An array of cstrings resulting from the split operation.
 */
cstr *pizza_io_cstr_split(ccstr str, char delimiter, size_t *count);

/**
 * @brief Replaces all occurrences of a substring within a cstr with another substring.
 * 
 * @param str The original cstr.
 * @param old The substring to be replaced.
 * @param new_str The substring to replace with.
 * @return A new cstr with the replacements made.
 */
cstr pizza_io_cstr_replace(ccstr str, ccstr old, ccstr new_str);

/**
 * @brief Converts all characters in the given cstr to uppercase.
 * 
 * @param str The cstr to be converted.
 * @return The cstr with all characters converted to uppercase.
 */
cstr pizza_io_cstr_to_upper(cstr str);

/**
 * @brief Converts all characters in the given cstr to lowercase.
 * 
 * @param str The cstr to be converted.
 * @return The cstr with all characters converted to lowercase.
 */
cstr pizza_io_cstr_to_lower(cstr str);

/**
 * @brief Checks if the given cstr starts with the specified prefix.
 * 
 * @param str The cstr to be checked.
 * @param prefix The prefix to check for.
 * @return 1 if the cstr starts with the prefix, 0 otherwise.
 */
int pizza_io_cstr_starts_with(ccstr str, ccstr prefix);

/**
 * @brief Checks if the given cstr ends with the specified suffix.
 * 
 * @param str The cstr to be checked.
 * @param suffix The suffix to check for.
 * @return 1 if the cstr ends with the suffix, 0 otherwise.
 */
int pizza_io_cstr_ends_with(ccstr str, ccstr suffix);

/**
 * @brief Extracts a substring from the given cstr.
 * 
 * @param str The original cstr.
 * @param start The starting index of the substring.
 * @param length The length of the substring.
 * @return A new cstr that is the specified substring of the original cstr.
 */
cstr pizza_io_cstr_substring(ccstr str, size_t start, size_t length);

/**
 * @brief Reverses the given cstr.
 * 
 * @param str The cstr to be reversed.
 * @return A new cstr that is the reverse of the given cstr.
 */
cstr pizza_io_cstr_reverse(cstr str);

/**
 * @brief Checks if the given cstr contains the specified substring.
 * 
 * @param str The cstr to be checked.
 * @param substr The substring to check for.
 * @return 1 if the cstr contains the substring, 0 otherwise.
 */
int pizza_io_cstr_contains(ccstr str, ccstr substr);

/**
 * @brief Repeats the given cstr the specified number of times.
 * 
 * @param str The cstr to be repeated.
 * @param count The number of times to repeat the cstr.
 * @return A new cstr that is the original cstr repeated the specified number of times.
 */
cstr pizza_io_cstr_repeat(ccstr str, size_t count);

/**
 * @brief Strips the given character from the beginning and end of the cstr.
 * 
 * @param str The cstr to be stripped.
 * @param ch The character to strip.
 * @return A new cstr that is the original cstr with the specified character stripped from the beginning and end.
 */
cstr pizza_io_cstr_strip(ccstr str, char ch);

/**
 * @brief Counts the number of occurrences of a substring within the given cstr.
 * 
 * @param str The cstr to be searched.
 * @param substr The substring to search for.
 * @return The number of occurrences of the substring within the cstr.
 */
size_t pizza_io_cstr_count(ccstr str, ccstr substr);

/**
 * @brief Pads the given cstr with the specified character on the left side.
 * 
 * @param str The cstr to be padded.
 * @param total_length The total length of the resulting cstr.
 * @param pad_char The character to pad with.
 * @return A new cstr that is the original cstr padded on the left side.
 */
cstr pizza_io_cstr_pad_left(ccstr str, size_t total_length, char pad_char);

/**
 * @brief Pads the given cstr with the specified character on the right side.
 * 
 * @param str The cstr to be padded.
 * @param total_length The total length of the resulting cstr.
 * @param pad_char The character to pad with.
 * @return A new cstr that is the original cstr padded on the right side.
 */
cstr pizza_io_cstr_pad_right(ccstr str, size_t total_length, char pad_char);

#ifdef __cplusplus
}
#endif

#endif
