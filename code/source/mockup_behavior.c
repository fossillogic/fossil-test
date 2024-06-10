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
#include "fossil/mockup/behavior.h"
#include <stdarg.h>
#include <string.h>

fossil_mockup_behavior_t* fossil_mockup_behavior_create(const char *function_name, int32_t arg_count) {
    fossil_mockup_behavior_t *behavior = (fossil_mockup_behavior_t *)malloc(sizeof(fossil_mockup_behavior_t));
    if (behavior == NULL) {
        perror("Failed to allocate memory for behavior");
        exit(EXIT_FAILURE);
    }
    behavior->function_name = _custom_fossil_mockup_core_strdup(function_name);
    behavior->arg_count = arg_count;
    behavior->args = (void **)malloc(arg_count * sizeof(void *));
    behavior->next = NULL;
    return behavior;
}

void fossil_mockup_behavior_record_call(fossil_mockup_behavior_t *behavior, ...) {
    va_list args;
    va_start(args, behavior);
    for (int32_t i = 0; i < behavior->arg_count; i++) {
        behavior->args[i] = va_arg(args, void *);
    }
    va_end(args);
}

bool fossil_mockup_behavior_verify_call(fossil_mockup_behavior_t *behavior, int32_t arg_count, ...) {
    if (arg_count != behavior->arg_count) {
        fprintf(stderr, "Argument count mismatch for function '%s'\n", behavior->function_name);
        return false;
    }

    va_list args;
    va_start(args, arg_count);
    for (int32_t i = 0; i < arg_count; i++) {
        void *expected_arg = va_arg(args, void *);
        if (behavior->args[i] != expected_arg) {
            fprintf(stderr, "Argument mismatch for function '%s' at position %d\n", behavior->function_name, i);
            va_end(args);
            return false;
        }
    }
    va_end(args);

    return true;
}

void fossil_mockup_behavior_erase(fossil_mockup_behavior_t *behavior) {
    free(behavior->function_name);
    free(behavior->args);
    free(behavior);
}
