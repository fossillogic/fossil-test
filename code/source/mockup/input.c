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
#include "fossil/mockup/input.h"
#include <stdarg.h>

fossil_mockup_input_t* fossil_mockup_input_create(const char *function_name) {
    fossil_mockup_input_t *input = (fossil_mockup_input_t *)malloc(sizeof(fossil_mockup_input_t));
    if (input == NULL) {
        perror("Failed to allocate memory for input mock");
        exit(EXIT_FAILURE);
    }
    input->function_name = _custom_fossil_test_strdup(function_name);
    input->mocked_inputs = NULL;
    input->input_count = 0;
    input->call_count = 0;
    input->next = NULL;
    return input;
}

void fossil_mockup_input_set_inputs(fossil_mockup_input_t *input, int32_t count, ...) {
    input->mocked_inputs = (void **)malloc(count * sizeof(void *));
    va_list args;
    va_start(args, count);
    for (int32_t i = 0; i < count; i++) {
        input->mocked_inputs[i] = va_arg(args, void *);
    }
    va_end(args);
    input->input_count = count;
}

void* fossil_mockup_input_get(fossil_mockup_input_t *input) {
    if (input->input_count > 0) {
        input->call_count++;
        return input->mocked_inputs[(input->call_count - 1) % input->input_count];
    }
    return NULL;
}

bool fossil_mockup_input_verify_call_count(fossil_mockup_input_t *input, int32_t expected_call_count) {
    if (input->call_count != expected_call_count) {
        fprintf(stderr, "Input function '%s' was called %d times, expected %d times\n",
                input->function_name, input->call_count, expected_call_count);
        return false;
    }
    return true;
}

void fossil_mockup_input_reset(fossil_mockup_input_t *input) {
    input->call_count = 0;
}

void fossil_mockup_input_erase(fossil_mockup_input_t *input) {
    free(input->function_name);
    if (input->mocked_inputs) {
        free(input->mocked_inputs);
    }
    free(input);
}
