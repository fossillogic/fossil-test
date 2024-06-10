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
#ifndef FSCL_XMOCK_INPUT_H
#define FSCL_XMOCK_INPUT_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Input mock object type
typedef struct xmock_input {
    char *function_name;
    void **mocked_inputs;
    int32_t input_count;
    int32_t call_count;
    struct xmock_input *next; // for chaining inputs
} xmock_input_t;

/**
 * @brief Create a new input mock object.
 *
 * This function creates a new input mock object for a specific function.
 *
 * @param function_name The name of the function to mock inputs for.
 * @return A pointer to the newly created input mock object.
 */
xmock_input_t* xmock_input_create(const char *function_name);

/**
 * @brief Set the mocked inputs for the function.
 *
 * This function sets the mocked inputs for a specific function in the input mock object.
 *
 * @param input The input mock object.
 * @param count The number of inputs to set.
 * @param ... The variable number of inputs to set.
 */
void xmock_input_set_inputs(xmock_input_t *input, int32_t count, ...);

/**
 * @brief Simulate getting the mocked input for the function call.
 *
 * This function simulates getting the mocked input for a specific function call from the input mock object.
 *
 * @param input The input mock object.
 * @return A pointer to the mocked input.
 */
void* xmock_input_get(xmock_input_t *input);

/**
 * @brief Verify the number of times the input function was called.
 *
 * This function verifies the number of times the input function was called for a specific function.
 *
 * @param input The input mock object.
 * @param expected_call_count The expected number of times the input function should have been called.
 * @return true if the number of calls matches the expected count, false otherwise.
 */
bool xmock_input_verify_call_count(xmock_input_t *input, int32_t expected_call_count);

/**
 * @brief Reset the input mock object for reuse.
 *
 * This function resets the input mock object, clearing all the mocked inputs and call counts.
 *
 * @param input The input mock object to reset.
 */
void xmock_input_reset(xmock_input_t *input);

/**
 * @brief Erase the input mock object.
 *
 * This function erases the input mock object, freeing all the allocated memory.
 *
 * @param input The input mock object to erase.
 */
void xmock_input_erase(xmock_input_t *input);

#ifdef __cplusplus
}
#endif

#endif
