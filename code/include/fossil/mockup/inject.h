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
#ifndef FOSSIL_MOCK_INJECT_H
#define FOSSIL_MOCK_INJECT_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Injected dependency type
typedef struct fossil_mockup_inject {
    char *dependency_name;
    void *replacement_object;
    struct fossil_mockup_inject *next; // for chaining injected dependencies
} fossil_mockup_inject_t;

/**
 * Create a new injected dependency object
 * 
 * @param dependency_name The name of the dependency
 * @param replacement_object The replacement object for the dependency
 * @return The created injected dependency object
 */
fossil_mockup_inject_t* fossil_mockup_inject_create(const char *dependency_name, void *replacement_object);

/**
 * Get the replacement object for the injected dependency
 * 
 * @param inject The injected dependency object
 * @return The replacement object
 */
void* fossil_mockup_inject_get_replacement(fossil_mockup_inject_t *inject);

/**
 * Erase the injected dependency object
 * 
 * @param inject The injected dependency object to erase
 */
void fossil_mockup_inject_erase(fossil_mockup_inject_t *inject);

#ifdef __cplusplus
}
#endif

#endif
