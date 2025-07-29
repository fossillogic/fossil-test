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

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <float.h>
#include <stdio.h>
#include <float.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #include <sys/stat.h>
#elif defined(__APPLE__)
    #define _DARWIN_C_SOURCE
    #include <sys/utsname.h>
    #include <sys/types.h>   // Before sysctl.h
    #include <sys/sysctl.h>
    #include <sys/stat.h>
    #include <mach/mach_time.h>
#else
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/time.h>
#endif

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define FOSSIL_PIZZA_HASH_SIZE 16

/* Type definitions */
typedef char* cstr;
typedef const char* ccstr;

// *****************************************************************************
// Safe operations
// *****************************************************************************

// Ensure null pointer definitions across C and C++ environments
#ifndef FOSSIL_CNULL

/**
 * @brief Safe and consistent null pointer definition for modern C++ and C standards.
 *
 * This section defines `null` for both C and C++ environments. 
 * The definitions ensure compatibility across different language versions, providing 
 * a clear and consistent way to represent null pointers. 
 *
 * - **C23 and Later:** In C23 (`__STDC_VERSION__ >= 202311L`), `null` is introduced 
 *   as a type-safe null pointer constant. The `null` macro directly maps to this 
 *   standard definition.
 *
 * - **Older C Standards (C11 and Below):** If C23 is not detected, `null` is defined 
 *   using `((void*)0)`, which is the traditional representation of a null pointer.
 *   and portable representation of a null pointer in C.
 *
 * This abstraction guarantees that null pointer values are handled consistently 
 * across different compilers and platforms, reducing the risk of undefined behavior 
 * in pointer operations.
 */
#if __cplusplus >= 201103L || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
    #define null    nullptr
#else
    #define null    ((void*)0)
#endif

#endif // FOSSIL_CNULL

/**
 * @brief Nullify a pointer safely.
 * 
 * Ensures that the pointer is explicitly set to `null`.
 */
#define nullify(ptr) ((ptr) = null)

/**
 * @brief Check if a pointer is not null safely.
 *
 * Prevents misuse of potentially null pointers.
 */
#define notnull(ptr) ((ptr) != null)

/**
 * @brief Safely casts one pointer type to another with null-checking.
 *
 * Mimics Rust's `as` with additional null safety. If the input is `null`,
 * it returns `null` instead of attempting an invalid cast.
 *
 * @param type The target type for the cast.
 * @param ptr The pointer to cast.
 * @return The casted pointer or `null` if the input pointer is null.
 */
#ifdef __cplusplus
    #define safe_cast(type, ptr) ((notnull(ptr)) ? (static_cast<type>(ptr)) : null)
#else
    #define safe_cast(type, ptr) ((notnull(ptr)) ? ((type)(ptr)) : null)
#endif

/**
 * @brief Marks a variable as intentionally unused to prevent warnings.
 */
#ifndef unused
    #if defined(__GNUC__) || defined(__clang__)
        #define unused(x) (void)(x)
    #else
        #define unused(x) /* no-op */
    #endif
#endif

/**
 * @brief Compiler hints for nullable and nonnull values.
 *
 * Provides stronger safety checks at compile time.
 */
#if defined(__clang__) || defined(__GNUC__)
    #define nullable __attribute__((nullable))
    #define nonnull  __attribute__((nonnull))
#elif defined(_MSC_VER)
    #define nullable _Null_terminated_
    #define nonnull  _In_
#else
    #define nullable
    #define nonnull
#endif

/**
 * @brief Compiler branch prediction hints for likely and unlikely conditions.
 *
 * Helps the compiler optimize branches based on expected conditions.
 */
#if defined(__GNUC__) || defined(__clang__)
    #define likely(x)   __builtin_expect(!!(x), 1)
    #define unlikely(x) __builtin_expect(!!(x), 0)
#else
    #define likely(x)   (x)
    #define unlikely(x) (x)
#endif

// Safe string and character constants

/**
 * @brief Null terminators for C and wide strings.
 */
#define term '\0'

/**
 * @brief Newline constants for C and wide strings.
 */
#define newline '\n'

/**
 * @brief Empty string constants for C and wide strings.
 */
#define cempty ""

// *****************************************************************************
// Hashing algorithm
// *****************************************************************************

/**
 * @brief Computes a hash for the given input string.
 *
 * This function implements a simple hashing algorithm that combines the input
 * string with an output string to produce a fixed-size hash.
 *
 * @param input The input string to hash.
 * @param output The output string to combine with the input.
 * @param hash_out Pointer to an array where the resulting hash will be stored.
 */
void fossil_pizza_hash(const char *input, const char *output, uint8_t *hash_out);

// *****************************************************************************
// Command Pallet
// *****************************************************************************

typedef enum {
    PIZZA_THEME_FOSSIL,      // C,C++ Fossil Test Framework
    PIZZA_THEME_CATCH,       // C++   Test Framework
    PIZZA_THEME_DOCTEST,     // C++   Test Framework
    PIZZA_THEME_CPPUTEST,    // C     Test Framework
    PIZZA_THEME_TAP,         // C     Test Framework
    PIZZA_THEME_GOOGLETEST,  // C++   Test Framework
    PIZZA_THEME_UNITY        // C     Test Framework
} fossil_pizza_cli_theme_t;

typedef enum {
    PIZZA_VERBOSE_PLAIN,
    PIZZA_VERBOSE_CI,
    PIZZA_VERBOSE_DOGE
} fossil_pizza_cli_verbose_t;

typedef struct {
    int dry_run;               // Flag for dry run mode
    const char* config_file;        // Path to the configuration file
    struct {
        int fail_fast;         // Flag for --fail-fast
        const char* only;      // Value for --only
        cstr *only_cases;      // Array of test case names (split by ',')
        size_t only_count;     // Number of test cases in only_cases
        int only_has_wildcard; // 1 if any test case contains '*', 0 otherwise
        const char* skip;      // Value for --skip
        int repeat;            // Value for --repeat
    } run;                     // Run command flags

    struct {
        const char* test_name; // Value for --test-name
        cstr *test_name_list;  // Array of test names (split by ',')
        size_t test_name_count;// Number of test names
        int test_name_has_wildcard; // 1 if any test name contains '*', 0 otherwise

        const char* suite_name;// Value for --suite-name
        cstr *suite_name_list; // Array of suite names (split by ',')
        size_t suite_name_count;// Number of suite names
        int suite_name_has_wildcard; // 1 if any suite name contains '*', 0 otherwise

        const char* tag;       // Value for --tag
        cstr *tag_list;        // Array of tags (split by ',')
        size_t tag_count;      // Number of tags
        int tag_has_wildcard;  // 1 if any tag contains '*', 0 otherwise
    } filter;                  // Filter command flags

    struct {
        const char* by;        // Value for --by
        const char* order;     // Value for --order
    } sort;                    // Sort command flags

    struct {
        const char* seed;      // Value for --seed
        int count;             // Value for --count
        const char* by;        // Value for --by
    } shuffle;                 // Shuffle command flags

    struct {
        const char* test_name;   // Name of the test case to show
        const char* suite_name;  // Name of the suite to show
        const char* tag;         // Tag to filter which test cases to show
        const char* result;      // Result to filter which test cases to show
        const char* mode;        // Mode to filter which test cases to show (e.g., tree, list, graph)
        const char* verbose;     // Verbosity level (plain, ci, doge)
        int enabled;             // Flag to enable showing test cases
    } show;                  // Show command flags

    fossil_pizza_cli_theme_t theme;  // Theme option
} fossil_pizza_pallet_t;

// *****************************************************************************
// exported flags
// *****************************************************************************

extern uint64_t G_PIZZA_TIMEOUT;
extern int G_PIZZA_DRY_RUN;
extern int G_PIZZA_FAIL_FAST;
extern int G_PIZZA_SKIP;
extern const char* G_PIZZA_ONLY;
extern int G_PIZZA_REPEAT;
extern fossil_pizza_cli_theme_t G_PIZZA_THEME;

/**
 * @brief Parses command line arguments and populates the pallet structure.
 *
 * This function processes command line arguments and fills the pallet structure
 * with the parsed commands, flags, options, and configurations.
 *
 * @param pallet Pointer to the pallet structure to populate.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 */
fossil_pizza_pallet_t fossil_pizza_pallet_create(int argc, char** argv);

// *****************************************************************************
// INI Parser
// *****************************************************************************

// INI Parser Implementation

/**
 * @brief Parses an INI file and populates the provided pallet structure.
 *
 * This function reads an INI file and extracts key-value pairs to populate
 * the fossil_pizza_pallet_t structure. It assumes a simple INI format with
 * sections and key-value pairs.
 *
 * @param filename The path to the INI file.
 * @param pallet Pointer to the pallet structure to populate.
 * @return 0 on success, or a negative error code on failure.
 */
int fossil_pizza_ini_parse(const char *filename, fossil_pizza_pallet_t *pallet);

// *****************************************************************************
// Host information
// *****************************************************************************

// Memory information structure
typedef struct {
    uint64_t total_memory; // in bytes
    uint64_t free_memory;  // in bytes
} pizza_sys_hostinfo_memory_t;

// Endianness information structure
typedef struct {
    int is_little_endian; // 1 if little-endian, 0 if big-endian
} pizza_sys_hostinfo_endianness_t;

// System information structure
typedef struct {
    char os_name[128];
    char os_version[128];
    char os_arch[64];
    char os_build[64];
    char os_release[64];
    char os_codename[64];
    char os_description[256];
    char os_vendor[128];
    char os_family[64];
    char os_type[64];
    char os_platform[64];
    char os_machine[64];
    char kernel_version[128];
} pizza_sys_hostinfo_system_t;

/**
 * Retrieve system information.
 *
 * @param info A pointer to a structure that will be filled with system information.
 * @return 0 on success, or a negative error code on failure.
 */
int pizza_sys_hostinfo_get_system(pizza_sys_hostinfo_system_t *info);

/**
 * Retrieve memory information.
 *
 * @param info A pointer to a structure that will be filled with memory information.
 * @return 0 on success, or a negative error code on failure.
 */
int pizza_sys_hostinfo_get_memory(pizza_sys_hostinfo_memory_t *info);

/**
 * Retrieve endianness information.
 *
 * @param info A pointer to a structure that will be filled with endianness information.
 * @return 0 on success, or a negative error code on failure.
 */
int pizza_sys_hostinfo_get_endianness(pizza_sys_hostinfo_endianness_t *info);

// *****************************************************************************
// Soap sanitizer
// *****************************************************************************

/**
 * @brief Sanitize input text by removing or replacing "rot-brain" and meme-based language.
 *
 * @param text The input text to sanitize.
 * @return A dynamically allocated sanitized string (must be freed by the caller).
 */
char *pizza_io_soap_sanitize(const char *text);

/**
 * @brief Suggest proper alternatives for rot-brain words or grammar fixes.
 *
 * @param text The input text.
 * @return A dynamically allocated string with suggestions (must be freed by the caller).
 */
char *pizza_io_soap_suggest(const char *text);

/**
 * @brief Add a custom word or phrase to the filter.
 *
 * @param phrase The phrase to add.
 * @return 0 on success, nonzero on failure.
 */
int pizza_io_soap_add_custom_filter(const char *phrase);

/**
 * @brief Clear all custom filters.
 */
void pizza_io_soap_clear_custom_filters(void);

/**
 * @brief Detect the tone of a sentence.
 *
 * @param text The input text.
 * @return A string representing the detected tone ("formal", "casual", "sarcastic", etc.).
 */
const char *pizza_io_soap_detect_tone(const char *text);

/**
 * @brief Checks if the given text contains "rot-brain" language.
 *
 * @param text The input text to check.
 * @return 1 if the text contains "rot-brain" language, 0 otherwise.
 */
int pizza_io_is_rot_brain(const char *text);

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
pizza_sys_memory_t pizza_sys_memory_zero(pizza_sys_memory_t ptr, size_t size);

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
 * Prints a formatted string to a buffer using a va_list.
 *
 * This function is similar to `vsnprintf`, but it allows for custom formatting
 * markers enclosed in curly braces `{}`, such as `{red}` for color or `{bold}` for
 * text attributes. The formatted string is written to the provided buffer.
 *
 * Example usage:
 * ```c
 * char buffer[100];
 * va_list args;
 * va_start(args, format);
 * pizza_io_vsnprintf(buffer, sizeof(buffer), format, args);
 * va_end(args);
 * ```
 *
 * @param buffer The buffer where the formatted string will be written.
 * @param size The size of the buffer.
 * @param format The format string, which contains the text to be formatted, along with format specifiers.
 * @param args The variable argument list containing the values to be formatted.
 * @return The number of characters written (excluding the null terminator), or a negative value if an error occurs.
 */
int pizza_io_vsnprintf(char *buffer, size_t size, const char *format, va_list args);

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
