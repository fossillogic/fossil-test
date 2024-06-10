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
#include "fossil/mockup/inject.h"
#include <stdarg.h>

xmock_inject_t* xmock_inject_create(const char *dependency_name, void *replacement_object) {
    xmock_inject_t *inject = (xmock_inject_t *)malloc(sizeof(xmock_inject_t));
    if (inject == NULL) {
        perror("Failed to allocate memory for injected dependency");
        exit(EXIT_FAILURE);
    }
    inject->dependency_name = _custom_xmock_core_strdup(dependency_name);
    inject->replacement_object = replacement_object;
    inject->next = NULL;
    return inject;
}

void* xmock_inject_get_replacement(xmock_inject_t *inject) {
    return inject->replacement_object;
}

void xmock_inject_erase(xmock_inject_t *inject) {
    free(inject->dependency_name);
    free(inject);
}
