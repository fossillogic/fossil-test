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

fossil_mockup_t* fossil_mockup_create(const char *function_name, int32_t num_args) {
    fossil_mockup_t *mock = (fossil_mockup_t *)malloc(sizeof(fossil_mockup_t));
    if (mock == NULL) {
        perror("Failed to allocate memory for mock");
        exit(EXIT_FAILURE);
    }

    mock->function_name = _custom_fossil_test_strdup(function_name);
    if (mock->function_name == NULL) {
        perror("Failed to duplicate function name");
        free(mock);
        exit(EXIT_FAILURE);
    }

    mock->num_args = num_args;
    mock->expected_args = (void **)malloc(num_args * sizeof(void *));
    if (mock->expected_args == NULL) {
        perror("Failed to allocate memory for expected args");
        free(mock->function_name);
        free(mock);
        exit(EXIT_FAILURE);
    }

    mock->comparators = (fossil_mockup_comparator_t *)calloc(num_args, sizeof(fossil_mockup_comparator_t));
    if (mock->comparators == NULL) {
        perror("Failed to allocate memory for comparators");
        free(mock->expected_args);
        free(mock->function_name);
        free(mock);
        exit(EXIT_FAILURE);
    }

    mock->actual_args = (void **)malloc(num_args * sizeof(void *));
    if (mock->actual_args == NULL) {
        perror("Failed to allocate memory for actual args");
        free(mock->comparators);
        free(mock->expected_args);
        free(mock->function_name);
        free(mock);
        exit(EXIT_FAILURE);
    }

    mock->return_values = NULL;
    mock->return_count = 0;
    mock->call_count = 0;
    mock->called = false;
    mock->next = NULL;
    return mock;
}

void fossil_mockup_set_expected_args(fossil_mockup_t *mock, ...) {
    va_list args;
    va_start(args, mock);
    for (int32_t i = 0; i < mock->num_args; i++) {
        mock->expected_args[i] = va_arg(args, void *);
    }
    va_end(args);
}

void fossil_mockup_set_comparator(fossil_mockup_t *mock, int32_t arg_index, fossil_mockup_comparator_t comparator) {
    if (arg_index >= 0 && arg_index < mock->num_args) {
        mock->comparators[arg_index] = comparator;
    }
}

void fossil_mockup_set_return_values(fossil_mockup_t *mock, int32_t count, ...) {
    if (mock->return_values) {
        free(mock->return_values);
    }
    mock->return_values = (void **)malloc(count * sizeof(void *));
    if (mock->return_values == NULL) {
        perror("Failed to allocate memory for return values");
        exit(EXIT_FAILURE);
    }
    va_list args;
    va_start(args, count);
    for (int32_t i = 0; i < count; i++) {
        mock->return_values[i] = va_arg(args, void *);
    }
    va_end(args);
    mock->return_count = count;
}

void* fossil_mockup_call(fossil_mockup_t *mock, ...) {
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

bool fossil_mockup_verify(fossil_mockup_t *mock) {
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

bool fossil_mockup_verify_call_count(fossil_mockup_t *mock, int32_t expected_call_count) {
    if (mock->call_count != expected_call_count) {
        fprintf(stderr, "Mock function '%s' was called %d times, expected %d times\n",
                mock->function_name, mock->call_count, expected_call_count);
        return false;
    }
    return true;
}

void fossil_mockup_reset(fossil_mockup_t *mock) {
    mock->call_count = 0;
    mock->called = false;
}

void fossil_mockup_erase(fossil_mockup_t *mock) {
    free(mock->function_name);
    free(mock->expected_args);
    free(mock->comparators);
    free(mock->actual_args);
    if (mock->return_values) {
        free(mock->return_values);
    }
    free(mock);
}

bool fossil_mockup_i32_comparator(void *expected, void *actual) {
    return *(int32_t *)expected == *(int32_t *)actual;
}

bool fossil_mockup_cstr_comparator(void *expected, void *actual) {
    return strcmp((char *)expected, (char *)actual) == 0;
}

bool fossil_mockup_ptr_comparator(void *expected, void *actual) {
    return expected == actual;
}

void fossil_mockup_log(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}
