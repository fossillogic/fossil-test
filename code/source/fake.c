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

xmock_fake_t* xmock_fake_create(const char *function_name, void (*fake_function)(void)) {
    xmock_fake_t *fake = (xmock_fake_t *)malloc(sizeof(xmock_fake_t));
    if (fake == NULL) {
        perror("Failed to allocate memory for fake");
        exit(EXIT_FAILURE);
    }
    fake->function_name = _custom_xmock_core_strdup(function_name);
    fake->fake_function = fake_function;
    fake->next = NULL;
    return fake;
}

void xmock_fake_call(xmock_fake_t *fake) {
    if (fake->fake_function) {
        fake->fake_function();
    } else {
        fprintf(stderr, "Fake function '%s' has no implementation\n", fake->function_name);
    }
}

void xmock_fake_erase(xmock_fake_t *fake) {
    free(fake->function_name);
    free(fake);
}
