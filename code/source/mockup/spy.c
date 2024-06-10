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
#include "fossil/mockup/spy.h"
#include <stdarg.h>

fossil_mockup_spy_t* fossil_mockup_spy_create(const char *function_name, int32_t num_args) {
    fossil_mockup_spy_t *spy = (fossil_mockup_spy_t *)malloc(sizeof(fossil_mockup_spy_t));
    if (spy == NULL) {
        perror("Failed to allocate memory for spy");
        exit(EXIT_FAILURE);
    }
    spy->function_name = _custom_fossil_test_strdup(function_name);
    spy->num_args = num_args;
    spy->recorded_args = (void **)malloc(num_args * sizeof(void *));
    spy->call_count = 0;
    spy->next = NULL;
    return spy;
}

void fossil_mockup_spy_record_call(fossil_mockup_spy_t *spy, ...) {
    va_list args;
    va_start(args, spy);
    for (int32_t i = 0; i < spy->num_args; i++) {
        spy->recorded_args[i] = va_arg(args, void *);
    }
    va_end(args);
    spy->call_count++;
}

void** fossil_mockup_spy_get_call_args(fossil_mockup_spy_t *spy, int32_t call_index) {
    if (call_index < 0 || call_index >= spy->call_count) {
        fprintf(stderr, "Invalid call index %d for spy function '%s'\n", call_index, spy->function_name);
        return NULL;
    }
    return spy->recorded_args;
}

bool fossil_mockup_spy_verify_call_count(fossil_mockup_spy_t *spy, int32_t expected_call_count) {
    if (spy->call_count != expected_call_count) {
        fprintf(stderr, "Spy function '%s' was called %d times, expected %d times\n",
                spy->function_name, spy->call_count, expected_call_count);
        return false;
    }
    return true;
}

void fossil_mockup_spy_reset(fossil_mockup_spy_t *spy) {
    spy->call_count = 0;
}

void fossil_mockup_spy_erase(fossil_mockup_spy_t *spy) {
    free(spy->function_name);
    free(spy->recorded_args);
    free(spy);
}
