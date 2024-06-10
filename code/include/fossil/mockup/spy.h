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
#ifndef FOSSIL_MOCK_SPY_H
#define FOSSIL_MOCK_SPY_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Spy object type
typedef struct fossil_mockup_spy {
    char *function_name;
    void **recorded_args;
    int32_t num_args;
    int32_t call_count;
    struct fossil_mockup_spy *next; // for chaining spies
} fossil_mockup_spy_t;

// Create a new spy object
/**
 * @brief Creates a new spy object.
 *
 * @param function_name The name of the function being spied on.
 * @param num_args The number of arguments the function takes.
 * @return A pointer to the newly created spy object.
 */
fossil_mockup_spy_t* fossil_mockup_spy_create(const char *function_name, int32_t num_args);

// Record the arguments of a function call
/**
 * @brief Records the arguments of a function call.
 *
 * @param spy The spy object.
 * @param ... The arguments of the function call.
 */
void fossil_mockup_spy_record_call(fossil_mockup_spy_t *spy, ...);

// Retrieve the recorded arguments for a specific call
/**
 * @brief Retrieves the recorded arguments for a specific call.
 *
 * @param spy The spy object.
 * @param call_index The index of the call.
 * @return A pointer to the recorded arguments.
 */
void** fossil_mockup_spy_get_call_args(fossil_mockup_spy_t *spy, int32_t call_index);

// Verify the number of times the spy function was called
/**
 * @brief Verifies the number of times the spy function was called.
 *
 * @param spy The spy object.
 * @param expected_call_count The expected number of calls.
 * @return true if the number of calls matches the expected count, false otherwise.
 */
bool fossil_mockup_spy_verify_call_count(fossil_mockup_spy_t *spy, int32_t expected_call_count);

// Reset the spy object for reuse
/**
 * @brief Resets the spy object for reuse.
 *
 * @param spy The spy object.
 */
void fossil_mockup_spy_reset(fossil_mockup_spy_t *spy);

// Erase the spy object
/**
 * @brief Erases the spy object.
 *
 * @param spy The spy object.
 */
void fossil_mockup_spy_erase(fossil_mockup_spy_t *spy);

#ifdef __cplusplus
}
#endif

#endif
