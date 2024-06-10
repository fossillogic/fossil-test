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
#ifndef FOSSIL_MOCK_FAKE_H
#define FOSSIL_MOCK_FAKE_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Fake object type
typedef struct fossil_mockup_fake {
    char *function_name;
    void (*fake_function)(void);
    struct fossil_mockup_fake *next; // for chaining fakes
} fossil_mockup_fake_t;

/**
 * @brief Create a new fake object.
 *
 * This function creates a new fake object for a given function name and fake function.
 *
 * @param function_name The name of the function being faked.
 * @param fake_function A pointer to the fake function that will be called instead of the original function.
 *
 * @return A pointer to the newly created fake object.
 */
fossil_mockup_fake_t* fossil_mockup_fake_create(const char *function_name, void (*fake_function)(void));

/**
 * @brief Simulate calling the fake function.
 *
 * This function simulates calling the fake function associated with a fake object.
 *
 * @param fake A pointer to the fake object.
 */
void fossil_mockup_fake_call(fossil_mockup_fake_t *fake);

/**
 * @brief Erase the fake object.
 *
 * This function erases the fake object and frees the memory associated with it.
 *
 * @param fake A pointer to the fake object.
 */
void fossil_mockup_fake_erase(fossil_mockup_fake_t *fake);

#ifdef __cplusplus
}
#endif

#endif
