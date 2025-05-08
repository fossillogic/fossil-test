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
#include "fossil/pizza/common.h"
#include <stdio.h>

// *****************************************************************************
// command pallet
// *****************************************************************************
// flags: --version, --help, --config, --verbose, --quiet, --no-color, --this
// catagories: general, mock, test, mock, sanity
pizza_cli_context_t *pizza_cli_create(void) {
    pizza_cli_context_t *ctx = (pizza_cli_context_t *)pizza_sys_memory_alloc(sizeof(pizza_cli_context_t));
    if (!ctx) {
        fprintf(stderr, "Error: Failed to create CLI context.\n");
        return NULL;
    }
    ctx->root = NULL;
    ctx->config_file = NULL;
    return ctx;
}

void pizza_cli_destroy(pizza_cli_context_t *ctx) {
    if (!ctx) {
        fprintf(stderr, "Error: Invalid context.\n");
        return;
    }

    // Free all commands and flags
    pizza_cli_command_t *cmd = ctx->root;
    while (cmd) {
        pizza_cli_command_t *next_cmd = cmd->next;
        pizza_sys_memory_free(cmd);
        cmd = next_cmd;
    }

    pizza_sys_memory_free(ctx);
}

pizza_cli_command_t *pizza_cli_add_command(pizza_cli_context_t *ctx, const char *name, const char *desc) {
    if (!ctx || !name || !desc) {
        fprintf(stderr, "Error: Invalid context, name, or description.\n");
        return NULL;
    }

    pizza_cli_command_t *cmd = (pizza_cli_command_t *)pizza_sys_memory_alloc(sizeof(pizza_cli_command_t));
    if (!cmd) {
        fprintf(stderr, "Error: Failed to create command.\n");
        return NULL;
    }

    cmd->name = name;
    cmd->description = desc;
    cmd->flags = NULL;
    cmd->subcommands = NULL;
    cmd->next = ctx->root;
    ctx->root = cmd;

    return cmd;
}

void pizza_cli_add_flag(pizza_cli_command_t *cmd, const char *name, const char *alias, pizza_cli_flag_type_t type, const char *default_val, const char *desc) {
    if (!cmd || !name || !desc) {
        fprintf(stderr, "Error: Invalid command, name, or description.\n");
        return;
    }

    pizza_cli_flag_t *flag = (pizza_cli_flag_t *)pizza_sys_memory_alloc(sizeof(pizza_cli_flag_t));
    if (!flag) {
        fprintf(stderr, "Error: Failed to create flag.\n");
        return;
    }

    flag->name = name;
    flag->alias = alias;
    flag->type = type;
    flag->value = NULL; // Initialize value to NULL
    flag->default_value = default_val;
    flag->description = desc;
    flag->next = cmd->flags;
    cmd->flags = flag;
}

int pizza_cli_parse_ini(const char *filename, pizza_cli_context_t *ctx) {
    if (!filename || !ctx) {
        fprintf(stderr, "Error: Invalid filename or context.\n");
        return -1;
    }

    // Implement INI parsing logic here
    // ...

    return 0; // Return 0 on success
}

int pizza_cli_parse(pizza_cli_context_t *ctx, int argc, char **argv) {
    unused(argc); // Unused parameter
    if (!ctx || !argv) {
        fprintf(stderr, "Error: Invalid context or arguments.\n");
        return -1;
    }

    // Implement command-line parsing logic here
    // ...

    return 0; // Return 0 on success
}

// *****************************************************************************
// memory management
// *****************************************************************************

pizza_sys_memory_t pizza_sys_memory_alloc(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Cannot allocate zero bytes.\n");
        return NULL;
    }
    
    pizza_sys_memory_t ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

pizza_sys_memory_t pizza_sys_memory_realloc(pizza_sys_memory_t ptr, size_t size) {
    pizza_sys_memory_t new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0) {
        fprintf(stderr, "Error: pizza_sys_memory_realloc() - Memory reallocation failed.\n");
        return NULL;
    }
    return new_ptr;
}

pizza_sys_memory_t pizza_sys_memory_calloc(size_t num, size_t size) {
    if (num == 0 || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Cannot allocate zero elements or zero bytes.\n");
        return NULL;
    }

    pizza_sys_memory_t ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

pizza_sys_memory_t pizza_sys_memory_init(pizza_sys_memory_t ptr, size_t size, int32_t value) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Pointer is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Cannot initialize zero bytes.\n");
        return NULL;
    }

    return memset(ptr, value, size);
}

void pizza_sys_memory_free(pizza_sys_memory_t ptr) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_free() - Pointer is NULL.\n");
        return;
    }
    free(ptr); // No need for NULL check, free() already handles NULL.
}

pizza_sys_memory_t pizza_sys_memory_copy(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size) {
    if (!dest || !src) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Source or destination is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Cannot copy zero bytes.\n");
        return NULL;
    }
    
    return memcpy(dest, src, size);
}

pizza_sys_memory_t pizza_sys_memory_set(pizza_sys_memory_t ptr, int32_t value, size_t size) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Pointer is NULL.\n");
        return NULL;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Cannot set zero bytes.\n");
        return NULL;
    }
    
    return memset(ptr, value, size);
}

pizza_sys_memory_t pizza_sys_memory_dup(const pizza_sys_memory_t src, size_t size) {
    if (!src || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_dup() - Invalid source or zero size.\n");
        return NULL;
    }

    pizza_sys_memory_t dest = pizza_sys_memory_alloc(size);
    if (!dest) {
        return NULL;  // Error already handled in pizza_sys_memory_alloc
    }

    return memcpy(dest, src, size);
}

void pizza_sys_memory_zero(pizza_sys_memory_t ptr, size_t size) {
    if (!ptr || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_zero() - Invalid pointer or zero size.\n");
        return;
    }
    
    memset(ptr, 0, size);
}

int pizza_sys_memory_compare(const pizza_sys_memory_t ptr1, const pizza_sys_memory_t ptr2, size_t size) {
    if (!ptr1 || !ptr2 || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_compare() - Invalid pointers or zero size.\n");
        return -1;  // Return -1 for invalid input
    }

    return memcmp(ptr1, ptr2, size);
}

pizza_sys_memory_t pizza_sys_memory_move(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size) {
    if (!dest || !src || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_move() - Invalid source or destination pointers, or zero size.\n");
        return NULL;
    }

    return memmove(dest, src, size);
}

pizza_sys_memory_t pizza_sys_memory_resize(pizza_sys_memory_t ptr, size_t old_size, size_t new_size) {
    if (ptr == NULL) {
        fprintf(stderr, "Error: pizza_sys_memory_resize() - Pointer is NULL.\n");
        return NULL;
    }

    if (new_size == 0) {
        pizza_sys_memory_free(ptr);
        return NULL;
    }

    // Allocate new memory
    pizza_sys_memory_t new_ptr = pizza_sys_memory_realloc(ptr, new_size);
    if (!new_ptr) {
        // Allocation failed; return the original memory block
        fprintf(stderr, "Error: pizza_sys_memory_resize() - Memory resize failed, original memory preserved.\n");
        return ptr;
    }

    // Check if new size is larger, and if so, preserve the old data
    if (new_size > old_size && ptr) {
        // Initialize new memory with old data (if necessary)
        memcpy(new_ptr, ptr, old_size);
    }

    return new_ptr;
}

bool pizza_sys_memory_is_valid(const pizza_sys_memory_t ptr) {
    if (!ptr) {
        return false;
    }
    // Optional: Add more validation logic if needed, but normally you'd rely on the caller to manage validity.
    return true;
}

// *****************************************************************************
// output management
// *****************************************************************************

int32_t PIZZA_IO_COLOR_ENABLE = 1; // Flag to enable/disable color output
int32_t FOSSIL_IO_ATTR_ENABLE = 1; // Flag to enable/disable attribute output

// Define color codes for output
#define FOSSIL_IO_COLOR_RESET       "\033[0m"
#define FOSSIL_IO_COLOR_RED         "\033[31m"
#define FOSSIL_IO_COLOR_GREEN       "\033[32m"
#define FOSSIL_IO_COLOR_YELLOW      "\033[33m"
#define FOSSIL_IO_COLOR_BLUE        "\033[34m"
#define FOSSIL_IO_COLOR_MAGENTA     "\033[35m"
#define FOSSIL_IO_COLOR_CYAN        "\033[36m"
#define FOSSIL_IO_COLOR_WHITE       "\033[37m"

// Bright colors
#define FOSSIL_IO_COLOR_BRIGHT_RED   "\033[91m"
#define FOSSIL_IO_COLOR_BRIGHT_GREEN "\033[92m"
#define FOSSIL_IO_COLOR_BRIGHT_YELLOW "\033[93m"
#define FOSSIL_IO_COLOR_BRIGHT_BLUE  "\033[94m"
#define FOSSIL_IO_COLOR_BRIGHT_MAGENTA "\033[95m"
#define FOSSIL_IO_COLOR_BRIGHT_CYAN  "\033[96m"
#define FOSSIL_IO_COLOR_BRIGHT_WHITE "\033[97m"

// Define text attributes
#define FOSSIL_IO_ATTR_BOLD         "\033[1m"
#define FOSSIL_IO_ATTR_UNDERLINE    "\033[4m"
#define FOSSIL_IO_ATTR_REVERSED     "\033[7m"
#define FOSSIL_IO_ATTR_BLINK        "\033[5m"
#define FOSSIL_IO_ATTR_HIDDEN       "\033[8m"
#define FOSSIL_IO_ATTR_NORMAL       "\033[22m" // For reverting to normal text

// Additional attributes
#define FOSSIL_IO_ATTR_ITALIC       "\033[3m"
#define FOSSIL_IO_ATTR_STRIKETHROUGH "\033[9m"

#define FOSSIL_IO_BUFFER_SIZE 1000

// Function to apply color
void pizza_io_apply_color(const char *color) {
    if (strcmp(color, "red") == 0) {
        printf(FOSSIL_IO_COLOR_RED);
    } else if (strcmp(color, "green") == 0) {
        printf(FOSSIL_IO_COLOR_GREEN);
    } else if (strcmp(color, "yellow") == 0) {
        printf(FOSSIL_IO_COLOR_YELLOW);
    } else if (strcmp(color, "blue") == 0) {
        printf(FOSSIL_IO_COLOR_BLUE);
    } else if (strcmp(color, "magenta") == 0) {
        printf(FOSSIL_IO_COLOR_MAGENTA);
    } else if (strcmp(color, "cyan") == 0) {
        printf(FOSSIL_IO_COLOR_CYAN);
    } else if (strcmp(color, "white") == 0) {
        printf(FOSSIL_IO_COLOR_WHITE);
    }
    // Bright colors
    else if (strcmp(color, "bright_red") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_RED);
    } else if (strcmp(color, "bright_green") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_GREEN);
    } else if (strcmp(color, "bright_yellow") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_YELLOW);
    } else if (strcmp(color, "bright_blue") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_BLUE);
    } else if (strcmp(color, "bright_magenta") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_MAGENTA);
    } else if (strcmp(color, "bright_cyan") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_CYAN);
    } else if (strcmp(color, "bright_white") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_WHITE);
    }
}

// Function to apply text attributes (e.g., bold, underline)
void pizza_io_apply_attribute(const char *attribute) {
    if (strcmp(attribute, "bold") == 0) {
        printf(FOSSIL_IO_ATTR_BOLD);
    } else if (strcmp(attribute, "underline") == 0) {
        printf(FOSSIL_IO_ATTR_UNDERLINE);
    } else if (strcmp(attribute, "reversed") == 0) {
        printf(FOSSIL_IO_ATTR_REVERSED);
    } else if (strcmp(attribute, "blink") == 0) {
        printf(FOSSIL_IO_ATTR_BLINK);
    } else if (strcmp(attribute, "hidden") == 0) {
        printf(FOSSIL_IO_ATTR_HIDDEN);
    } else if (strcmp(attribute, "normal") == 0) {
        printf(FOSSIL_IO_ATTR_NORMAL);
    } else if (strcmp(attribute, "italic") == 0) {
        printf(FOSSIL_IO_ATTR_ITALIC);
    } else if (strcmp(attribute, "strikethrough") == 0) {
        printf(FOSSIL_IO_ATTR_STRIKETHROUGH);
    }
}

// Function to handle named positions (like top, bottom, left, right)
void pizza_io_apply_position(const char *pos) {
    if (strcmp(pos, "top") == 0) {
        // Apply position logic for top
        printf("\033[H"); // Move cursor to the top
    } else if (strcmp(pos, "bottom") == 0) {
        // Apply position logic for bottom
        printf("\033[1000H"); // Move cursor to the bottom (just as an example)
    } else if (strcmp(pos, "left") == 0) {
        // Apply position logic for left
        printf("\033[1000;0H"); // Move cursor to the left
    } else if (strcmp(pos, "right") == 0) {
        // Apply position logic for right
        printf("\033[1000;1000H"); // Move cursor to the right
    }
    // Add more positions if needed
}

// Function to print text with attributes, colors, positions, and format specifiers
void pizza_io_print_with_attributes(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Variable to keep track of the current position in the buffer
    const char *current_pos = buffer;
    const char *start = NULL;
    const char *end = NULL;

    // Iterate over the buffer and process color/attribute/position inside `{}` and format specifiers
    while ((start = strchr(current_pos, '{')) != NULL) {
        // Print text before '{'
        printf("%.*s", (int)(start - current_pos), current_pos);
        
        // Find the matching '}'
        end = strchr(start, '}');
        if (end) {
            // Extract attributes inside '{}'
            size_t length = end - start - 1;
            char attributes[length + 1];
            strncpy(attributes, start + 1, length);
            attributes[length] = '\0';

            // Split by comma to separate color, attribute, or position
            char *color = NULL;
            char *attribute = NULL;
            char *pos = NULL;
            char *comma_pos = strchr(attributes, ',');
            if (comma_pos) {
                *comma_pos = '\0';  // Null-terminate the first part
                color = attributes; // Color or position part
                attribute = comma_pos + 1; // Attribute part
            } else {
                color = attributes; // Only one part (could be color, attribute, or position)
            }

            // Handle positions (like {pos:name})
            if (strstr(color, "pos:") == color) {
                pos = color + 4; // Skip the "pos:" prefix
                pizza_io_apply_position(pos);
            } else {
                // Apply color and/or attribute based on flags
                if (PIZZA_IO_COLOR_ENABLE && color) {
                    pizza_io_apply_color(color);
                }
                if (FOSSIL_IO_ATTR_ENABLE && attribute) {
                    pizza_io_apply_attribute(attribute);
                }
            }

            // Move past '}' and continue processing
            current_pos = end + 1;
        }
    }

    // Print remaining text after last '}'
    printf("%s", current_pos);

    va_end(args);
}

// Function to print a sanitized formatted string to a specific file stream with attributes
void pizza_io_fprint_with_attributes(pizza_fstream_t *stream, const char *str) {
    if (str != NULL && stream != NULL) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color and attribute logic (same as the print version)
        pizza_io_print_with_attributes(sanitized_str);

        // Write the sanitized string to the stream
        fputs(sanitized_str, stream->file);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

//
// OUTPUT FUNCTIONS
//

// Function to print a sanitized string with attributes inside {}
void pizza_io_puts(const char *str) {
    if (str != NULL) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination
        
        // Print the sanitized string with attributes
        pizza_io_print_with_attributes(sanitized_str);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a single character
void pizza_io_putchar(char c) {
    putchar(c);
}

// Function to print sanitized formatted output with attributes
void pizza_io_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized output with attributes
    pizza_io_print_with_attributes(buffer);

    va_end(args);
}

// Function to print a sanitized string to a specific file stream
void pizza_io_fputs(pizza_fstream_t *stream, const char *str) {
    if (str != NULL && stream != NULL) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color/attributes and sanitize the string before printing
        pizza_io_fprint_with_attributes(stream, sanitized_str);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a sanitized formatted string to a specific file stream
void pizza_io_fprintf(pizza_fstream_t *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized formatted string with attributes to the specified stream
    pizza_io_fprint_with_attributes(stream, buffer);

    va_end(args);
}

// TUI PART

void pizza_io_clear_screen(void) {
    printf("\033[2J\033[H");
}

void pizza_io_move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void pizza_io_hide_cursor(void) {
    printf("\033[?25l");
}

void pizza_io_show_cursor(void) {
    printf("\033[?25h");
}

void pizza_io_draw_horizontal_line(int length, char ch) {
    for (int i = 0; i < length; ++i) {
        putchar(ch);
    }
    putchar('\n');
}

void pizza_io_draw_vertical_line(int length, char ch) {
    for (int i = 0; i < length; ++i) {
        putchar(ch);
        putchar('\n');
    }
}

void pizza_io_flush(void) {
    fflush(stdout);
}

// *****************************************************************************
// string management
// *****************************************************************************

cstr pizza_io_cstr_create(const char *init) {
    if (!init) return NULL;
    size_t length = strlen(init);
    cstr str = (cstr)malloc(length + 1);
    if (str) {
        strcpy(str, init);
    }
    return str;
}

void pizza_io_cstr_free(cstr str) {
    if (str) {
        free(str);
    }
}

cstr pizza_io_cstr_copy(ccstr str) {
    if (!str) return NULL;
    return pizza_io_cstr_create(str);
}

cstr pizza_io_cstr_dup(ccstr str) {
    if (!str) return NULL;
    size_t length = strlen(str);
    cstr new_str = (cstr)malloc(length + 1);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

cstr pizza_io_cstr_concat(ccstr s1, ccstr s2) {
    if (!s1 || !s2) return NULL;
    size_t length1 = strlen(s1);
    size_t length2 = strlen(s2);
    cstr str = (cstr)malloc(length1 + length2 + 1);
    if (str) {
        strcpy(str, s1);
        strcpy(str + length1, s2);
    }
    return str;
}

size_t pizza_io_cstr_length(ccstr str) {
    if (!str) return 0;
    return strlen(str);
}

int pizza_io_cstr_compare(ccstr s1, ccstr s2) {
    if (!s1 || !s2) return -1;
    return strcmp(s1, s2);
}

void pizza_io_cstr_trim(cstr str) {
    if (!str) return;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && isspace(str[start])) {
        start++;
    }
    while (end > start && isspace(str[end])) {
        end--;
    }
    size_t count = end - start + 1;
    if (start > 0) {
        memmove(str, str + start, count);
    }
    str[count] = '\0';
}

cstr *pizza_io_cstr_split(ccstr str, char delimiter, size_t *count) {
    if (!str || !count) return NULL;
    size_t length = strlen(str);
    size_t num_delimiters = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == delimiter) {
            num_delimiters++;
        }
    }
    *count = num_delimiters + 1;
    cstr *result = (cstr*)malloc(*count * sizeof(cstr));
    if (result) {
        size_t start = 0;
        size_t index = 0;
        for (size_t i = 0; i < length; i++) {
            if (str[i] == delimiter) {
                size_t count = i - start;
                result[index] = (cstr)malloc(count + 1);
                if (result[index]) {
                    memcpy(result[index], str + start, count);
                    result[index][count] = '\0';
                    start = i + 1;
                    index++;
                } else {
                    // Free previously allocated memory on error
                    for (size_t j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
            }
        }
        size_t count = length - start;
        result[index] = (cstr)malloc(count + 1);
        if (result[index]) {
            memcpy(result[index], str + start, count);
            result[index][count] = '\0';
        } else {
            // Free previously allocated memory on error
            for (size_t j = 0; j < index; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
    }
    return result;
}

cstr pizza_io_cstr_replace(ccstr str, ccstr old, ccstr new_str) {
    if (!str || !old || !new_str) return NULL;
    size_t old_length = strlen(old);
    size_t new_length = strlen(new_str);
    size_t count = 0;
    size_t index = 0;
    size_t length = strlen(str);
    while (index < length) {
        if (strstr(str + index, old) == str + index) {
            count++;
            index += old_length;
        } else {
            index++;
        }
    }
    cstr result = (cstr)malloc(length + count * (new_length - old_length) + 1);
    if (result) {
        index = 0;
        size_t start = 0;
        while (index < length) {
            if (strstr(str + index, old) == str + index) {
                strcpy(result + start, new_str);
                start += new_length;
                index += old_length;
            } else {
                result[start] = str[index];
                start++;
                index++;
            }
        }
        result[start] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_to_upper(cstr str) {
    if (!str) return NULL;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = toupper(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_to_lower(cstr str) {
    if (!str) return NULL;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = tolower(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_starts_with(ccstr str, ccstr prefix) {
    if (!str || !prefix) return 0;
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (prefix_length > str_length) {
        return 0;
    }
    return strncmp(str, prefix, prefix_length) == 0;
}

int pizza_io_cstr_ends_with(ccstr str, ccstr suffix) {
    if (!str || !suffix) return 0;
    size_t str_length = strlen(str);
    size_t suffix_length = strlen(suffix);
    if (suffix_length > str_length) {
        return 0;
    }
    return strncmp(str + str_length - suffix_length, suffix, suffix_length) == 0;
}

cstr pizza_io_cstr_substring(ccstr str, size_t start, size_t length) {
    if (!str) return NULL;
    size_t str_length = strlen(str);
    if (start >= str_length) {
        return NULL;
    }
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        size_t count = str_length - start;
        if (length < count) {
            count = length;
        }
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_reverse(cstr str) {
    if (!str) return NULL;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = str[length - i - 1];
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_contains(ccstr str, ccstr substr) {
    if (!str || !substr) return 0;
    return strstr(str, substr) != NULL;
}

cstr pizza_io_cstr_repeat(ccstr str, size_t count) {
    if (!str || count == 0) return NULL;
    size_t length = strlen(str);
    size_t new_length = length * count;
    cstr result = (cstr)malloc(new_length + 1);
    if (result) {
        for (size_t i = 0; i < count; i++) {
            memcpy(result + i * length, str, length);
        }
        result[new_length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_strip(ccstr str, char ch) {
    if (!str) return NULL;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && str[start] == ch) {
        start++;
    }
    while (end > start && str[end] == ch) {
        end--;
    }
    size_t count = end - start + 1;
    cstr result = (cstr)malloc(count + 1);
    if (result) {
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

size_t pizza_io_cstr_count(ccstr str, ccstr substr) {
    if (!str || !substr) return 0;
    size_t count = 0;
    size_t length = strlen(substr);
    while ((str = strstr(str, substr)) != NULL) {
        count++;
        str += length;
    }
    return count;
}

cstr pizza_io_cstr_pad_left(ccstr str, size_t total_length, char pad_char) {
    if (!str || total_length == 0) return NULL;
    size_t length = strlen(str);
    if (length >= total_length) {
        return pizza_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result) {
        memset(result, pad_char, pad_length);
        strcpy(result + pad_length, str);
        result[total_length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_pad_right(ccstr str, size_t total_length, char pad_char) {
    if (!str || total_length == 0) return NULL;
    size_t length = strlen(str);
    if (length >= total_length) {
        return pizza_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result) {
        strcpy(result, str);
        memset(result + length, pad_char, pad_length);
        result[total_length] = '\0';
    }
    return result;
}
