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
#include "fossil/mockup/fake.h"

fossil_mockup_fake_t* fossil_mockup_fake_create(const char *function_name, void (*fake_function)(void)) {
    fossil_mockup_fake_t *fake = (fossil_mockup_fake_t *)malloc(sizeof(fossil_mockup_fake_t));
    if (fake == NULL) {
        perror("Failed to allocate memory for fake");
        exit(EXIT_FAILURE);
    }
    fake->function_name = _custom_fossil_mockup_core_strdup(function_name);
    fake->fake_function = fake_function;
    fake->next = NULL;
    return fake;
}

void fossil_mockup_fake_call(fossil_mockup_fake_t *fake) {
    if (fake->fake_function) {
        fake->fake_function();
    } else {
        fprintf(stderr, "Fake function '%s' has no implementation\n", fake->function_name);
    }
}

void fossil_mockup_fake_erase(fossil_mockup_fake_t *fake) {
    free(fake->function_name);
    free(fake);
}
