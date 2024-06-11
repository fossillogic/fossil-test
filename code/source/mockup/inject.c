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

fossil_mockup_inject_t* fossil_mockup_inject_create(const char *dependency_name, void *replacement_object) {
    fossil_mockup_inject_t *inject = (fossil_mockup_inject_t *)malloc(sizeof(fossil_mockup_inject_t));
    if (inject == NULL) {
        perror("Failed to allocate memory for injected dependency");
        exit(EXIT_FAILURE);
    }
    
    inject->dependency_name = _custom_fossil_test_strdup(dependency_name);
    if (inject->dependency_name == NULL) {
        perror("Failed to duplicate dependency name");
        free(inject);
        exit(EXIT_FAILURE);
    }

    inject->replacement_object = replacement_object;
    inject->next = NULL;
    return inject;
}

void* fossil_mockup_inject_get_replacement(fossil_mockup_inject_t *inject) {
    return inject->replacement_object;
}

void fossil_mockup_inject_erase(fossil_mockup_inject_t *inject) {
    free(inject->dependency_name);
    free(inject);
}
