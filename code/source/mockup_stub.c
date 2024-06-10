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
#include "fossil/mockup/stub.h"
#include <stdarg.h>

fossil_mockup_stub_t* fossil_mockup_stub_create(const char *function_name) {
    fossil_mockup_stub_t *stub = (fossil_mockup_stub_t *)malloc(sizeof(fossil_mockup_stub_t));
    if (stub == NULL) {
        perror("Failed to allocate memory for stub");
        exit(EXIT_FAILURE);
    }
    stub->function_name = _custom_fossil_mockup_core_strdup(function_name);
    stub->return_values = NULL;
    stub->return_count = 0;
    stub->call_count = 0;
    stub->next = NULL;
    return stub;
}

void fossil_mockup_stub_set_return_values(fossil_mockup_stub_t *stub, int32_t count, ...) {
    stub->return_values = (void **)malloc(count * sizeof(void *));
    va_list args;
    va_start(args, count);
    for (int32_t i = 0; i < count; i++) {
        stub->return_values[i] = va_arg(args, void *);
    }
    va_end(args);
    stub->return_count = count;
}

void* fossil_mockup_stub_call(fossil_mockup_stub_t *stub) {
    stub->call_count++;

    if (stub->return_count > 0) {
        return stub->return_values[(stub->call_count - 1) % stub->return_count];
    }
    return NULL;
}

bool fossil_mockup_stub_verify_call_count(fossil_mockup_stub_t *stub, int32_t expected_call_count) {
    if (stub->call_count != expected_call_count) {
        fprintf(stderr, "Stub function '%s' was called %d times, expected %d times\n",
                stub->function_name, stub->call_count, expected_call_count);
        return false;
    }
    return true;
}

void fossil_mockup_stub_reset(fossil_mockup_stub_t *stub) {
    stub->call_count = 0;
}

void fossil_mockup_stub_erase(fossil_mockup_stub_t *stub) {
    free(stub->function_name);
    if (stub->return_values) {
        free(stub->return_values);
    }
    free(stub);
}
