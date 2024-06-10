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
#ifndef FSCL_XMOCK_BEHAVIOR_H
#define FSCL_XMOCK_BEHAVIOR_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Behavior object type
typedef struct xmock_behavior {
    char *function_name;
    void **args;
    int32_t arg_count;
    struct xmock_behavior *next; // for chaining behaviors
} xmock_behavior_t;

/**
 * Create a new behavior object
 * 
 * @param function_name The name of the function
 * @param arg_count The number of arguments
 * @return A pointer to the newly created behavior object
 */
xmock_behavior_t* xmock_behavior_create(const char *function_name, int32_t arg_count);

/**
 * Record a function call and its arguments
 * 
 * @param behavior The behavior object
 * @param ... The arguments of the function call
 */
void xmock_behavior_record_call(xmock_behavior_t *behavior, ...);

/**
 * Verify if a specific function was called with the given arguments
 * 
 * @param behavior The behavior object
 * @param arg_count The number of arguments
 * @param ... The arguments to verify
 * @return true if the function was called with the given arguments, false otherwise
 */
bool xmock_behavior_verify_call(xmock_behavior_t *behavior, int32_t arg_count, ...);

/**
 * Erase the behavior object
 * 
 * @param behavior The behavior object to erase
 */
void xmock_behavior_erase(xmock_behavior_t *behavior);

#ifdef __cplusplus
}
#endif

#endif
