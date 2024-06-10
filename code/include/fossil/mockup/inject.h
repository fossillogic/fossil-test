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
#ifndef FSCL_XMOCK_INJECT_H
#define FSCL_XMOCK_INJECT_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Injected dependency type
typedef struct xmock_inject {
    char *dependency_name;
    void *replacement_object;
    struct xmock_inject *next; // for chaining injected dependencies
} xmock_inject_t;

/**
 * Create a new injected dependency object
 * 
 * @param dependency_name The name of the dependency
 * @param replacement_object The replacement object for the dependency
 * @return The created injected dependency object
 */
xmock_inject_t* xmock_inject_create(const char *dependency_name, void *replacement_object);

/**
 * Get the replacement object for the injected dependency
 * 
 * @param inject The injected dependency object
 * @return The replacement object
 */
void* xmock_inject_get_replacement(xmock_inject_t *inject);

/**
 * Erase the injected dependency object
 * 
 * @param inject The injected dependency object to erase
 */
void xmock_inject_erase(xmock_inject_t *inject);

#ifdef __cplusplus
}
#endif

#endif
