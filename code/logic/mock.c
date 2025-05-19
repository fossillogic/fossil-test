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
#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include "fossil/pizza/mock.h"

// *****************************************************************************
// Function declarations
// *****************************************************************************

void fossil_mock_init(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_destroy(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }

    fossil_mock_call_t *current = list->head;
    while (current) {
        fossil_mock_call_t *next = current->next;
        pizza_sys_memory_free(current->function_name);
        for (int i = 0; i < current->num_args; ++i) {
            pizza_sys_memory_free(current->arguments[i].value.data);
            pizza_sys_memory_free(current->arguments[i].attribute.name);
            pizza_sys_memory_free(current->arguments[i].attribute.description);
            pizza_sys_memory_free(current->arguments[i].attribute.id);
        }
        pizza_sys_memory_free(current->arguments);
        pizza_sys_memory_free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, fossil_mock_pizza_t *arguments, int num_args) {
    if (!list || !function_name || (!arguments && num_args > 0)) {
        return;
    }

    fossil_mock_call_t *call = (fossil_mock_call_t *)pizza_sys_memory_alloc(sizeof(fossil_mock_call_t));
    if (!call) {
        return;
    }

    call->function_name = pizza_io_cstr_dup(function_name);
    if (!call->function_name) {
        pizza_sys_memory_free(call);
        return;
    }

    if (num_args > 0) {
        call->arguments = (fossil_mock_pizza_t *)pizza_sys_memory_alloc(num_args * sizeof(fossil_mock_pizza_t));
        if (!call->arguments) {
            pizza_sys_memory_free(call->function_name);
            pizza_sys_memory_free(call);
            return;
        }

        for (int i = 0; i < num_args; ++i) {
            call->arguments[i].type = arguments[i].type;
            call->arguments[i].value.data = pizza_io_cstr_dup(arguments[i].value.data);
            call->arguments[i].value.mutable_flag = arguments[i].value.mutable_flag;
            call->arguments[i].attribute.name = pizza_io_cstr_dup(arguments[i].attribute.name);
            call->arguments[i].attribute.description = pizza_io_cstr_dup(arguments[i].attribute.description);
            call->arguments[i].attribute.id = pizza_io_cstr_dup(arguments[i].attribute.id);

            if (!call->arguments[i].value.data || !call->arguments[i].attribute.name ||
                !call->arguments[i].attribute.description || !call->arguments[i].attribute.id) {
                for (int j = 0; j <= i; ++j) {
                    pizza_sys_memory_free(call->arguments[j].value.data);
                    pizza_sys_memory_free(call->arguments[j].attribute.name);
                    pizza_sys_memory_free(call->arguments[j].attribute.description);
                    pizza_sys_memory_free(call->arguments[j].attribute.id);
                }
                pizza_sys_memory_free(call->arguments);
                pizza_sys_memory_free(call->function_name);
                pizza_sys_memory_free(call);
                return;
            }
        }
    } else {
        call->arguments = NULL;
    }

    call->num_args = num_args;
    call->next = NULL;

    if (list->tail) {
        list->tail->next = call;
    } else {
        list->head = call;
    }
    list->tail = call;
    list->size++;
}

void fossil_mock_print(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }

    fossil_mock_call_t *current = list->head;
    while (current) {
        pizza_io_printf("Function: %s\n", current->function_name);
        pizza_io_printf("Arguments:\n");
        for (int i = 0; i < current->num_args; ++i) {
            pizza_io_printf("  Type: %d\n", current->arguments[i].type);
            pizza_io_printf("  Value: %s\n", current->arguments[i].value.data);
            pizza_io_printf("  Mutable: %s\n", current->arguments[i].value.mutable_flag ? "true" : "false");
            pizza_io_printf("  Attribute Name: %s\n", current->arguments[i].attribute.name);
            pizza_io_printf("  Attribute Description: %s\n", current->arguments[i].attribute.description);
            pizza_io_printf("  Attribute ID: %s\n", current->arguments[i].attribute.id);
        }
        current = current->next;
    }
}

/**
 * Captures the output of a function to a buffer for testing purposes.
 *
 * @param buffer The buffer to store the captured output.
 * @param size The size of the buffer.
 * @param function The function whose output is to be captured.
 * @param ... The arguments to pass to the function.
 * @return The number of characters captured.
 */
int fossil_mock_capture_output(char *buffer, size_t size, void (*function)(void), ...) {
    if (!buffer || size == 0 || !function) {
        return -1;
    }

    // Create a temporary file to capture stdout
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return -1;
    }

    // Redirect stdout to the temporary file
    int original_stdout_fd = dup(STDOUT_FILENO);
    if (original_stdout_fd == -1) {
        fclose(temp_file);
        return -1;
    }
    fflush(stdout);
    if (dup2(fileno(temp_file), STDOUT_FILENO) == -1) {
        fclose(temp_file);
        close(original_stdout_fd);
        return -1;
    }

    // Call the function with variable arguments
    va_list args;
    va_start(args, function);
    function();
    va_end(args);

    // Restore stdout
    fflush(stdout);
    dup2(original_stdout_fd, STDOUT_FILENO);
    close(original_stdout_fd);

    // Rewind the temporary file and read its contents into the buffer
    rewind(temp_file);
    size_t read_size = fread(buffer, 1, size - 1, temp_file);
    buffer[read_size] = '\0'; // Null-terminate the buffer

    // Close the temporary file
    fclose(temp_file);

    return (int)read_size;
}

/**
 * Compares the captured output with the expected output.
 *
 * @param captured The captured output.
 * @param expected The expected output.
 * @return True if the captured output matches the expected output, false otherwise.
 */
bool fossil_mock_compare_output(const char *captured, const char *expected) {
    if (!captured || !expected) {
        return false;
    }
    return strcmp(captured, expected) == 0;
}
