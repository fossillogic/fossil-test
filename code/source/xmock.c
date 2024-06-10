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
#include "fossil/mockup/internal.h"
#include <stdarg.h>

xmock_t* xmock_create(const char *function_name, int32_t num_args) {
    xmock_t *mock = (xmock_t *)malloc(sizeof(xmock_t));
    if (mock == NULL) {
        perror("Failed to allocate memory for mock");
        exit(EXIT_FAILURE);
    }
    mock->function_name = _custom_xmock_core_strdup(function_name);
    mock->num_args = num_args;
    mock->expected_args = (void **)malloc(num_args * sizeof(void *));
    mock->comparators = (xmock_comparator_t *)calloc(num_args, sizeof(xmock_comparator_t));
    mock->actual_args = (void **)malloc(num_args * sizeof(void *));
    mock->return_values = NULL;
    mock->return_count = 0;
    mock->call_count = 0;
    mock->called = false;
    mock->next = NULL;
    return mock;
}

void xmock_set_expected_args(xmock_t *mock, ...) {
    va_list args;
    va_start(args, mock);
    for (int32_t i = 0; i < mock->num_args; i++) {
        mock->expected_args[i] = va_arg(args, void *);
    }
    va_end(args);
}

void xmock_set_comparator(xmock_t *mock, int32_t arg_index, xmock_comparator_t comparator) {
    if (arg_index >= 0 && arg_index < mock->num_args) {
        mock->comparators[arg_index] = comparator;
    }
}

void xmock_set_return_values(xmock_t *mock, int32_t count, ...) {
    mock->return_values = (void **)malloc(count * sizeof(void *));
    va_list args;
    va_start(args, count);
    for (int32_t i = 0; i < count; i++) {
        mock->return_values[i] = va_arg(args, void *);
    }
    va_end(args);
    mock->return_count = count;
}

void* xmock_call(xmock_t *mock, ...) {
    va_list args;
    va_start(args, mock);
    for (int32_t i = 0; i < mock->num_args; i++) {
        mock->actual_args[i] = va_arg(args, void *);
    }
    va_end(args);
    mock->call_count++;
    mock->called = true;

    if (mock->return_count > 0) {
        return mock->return_values[(mock->call_count - 1) % mock->return_count];
    }
    return NULL;
}

bool xmock_verify(xmock_t *mock) {
    if (!mock->called) {
        fprintf(stderr, "Mock function '%s' was not called\n", mock->function_name);
        return false;
    }
    for (int32_t i = 0; i < mock->num_args; i++) {
        bool match = false;
        if (mock->comparators[i]) {
            match = mock->comparators[i](mock->expected_args[i], mock->actual_args[i]);
        } else {
            match = (mock->expected_args[i] == mock->actual_args[i]);
        }
        if (!match) {
            fprintf(stderr, "Argument %d mismatch in mock function '%s': expected %p, got %p\n",
                    i, mock->function_name, mock->expected_args[i], mock->actual_args[i]);
            return false;
        }
    }
    return true;
}

bool xmock_verify_call_count(xmock_t *mock, int32_t expected_call_count) {
    if (mock->call_count != expected_call_count) {
        fprintf(stderr, "Mock function '%s' was called %d times, expected %d times\n",
                mock->function_name, mock->call_count, expected_call_count);
        return false;
    }
    return true;
}

void xmock_reset(xmock_t *mock) {
    mock->call_count = 0;
    mock->called = false;
}

void xmock_erase(xmock_t *mock) {
    free(mock->function_name);
    free(mock->expected_args);
    free(mock->comparators);
    free(mock->actual_args);
    if (mock->return_values) {
        free(mock->return_values);
    }
    free(mock);
}

bool xmock_i32_comparator(void *expected, void *actual) {
    return *(int32_t *)expected == *(int32_t *)actual;
}

bool xmock_cstr_comparator(void *expected, void *actual) {
    return strcmp((char *)expected, (char *)actual) == 0;
}

bool xmock_ptr_comparator(void *expected, void *actual) {
    return expected == actual;
}

void xmock_log(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
