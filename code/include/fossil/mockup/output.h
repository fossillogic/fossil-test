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
#ifndef FSCL_XMOCK_OUTPUT_H
#define FSCL_XMOCK_OUTPUT_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Output mock object type
typedef struct xmock_output {
    char *function_name;
    char **captured_outputs;
    int32_t output_count;
    int32_t call_count;
    struct xmock_output *next; // for chaining outputs
} xmock_output_t;

/**
 * @brief Create a new output mock object.
 *
 * This function creates a new output mock object for capturing and verifying output
 * produced by a specific function.
 *
 * @param function_name The name of the function for which the output is being mocked.
 * @return A pointer to the newly created xmock_output_t object.
 */
xmock_output_t* xmock_output_create(const char *function_name);

/**
 * @brief Capture output for the function.
 *
 * This function captures the output produced by the mocked function and associates it
 * with the given output mock object.
 *
 * @param output The output mock object to capture the output for.
 * @param captured_output The captured output to associate with the output mock object.
 */
void xmock_output_capture(xmock_output_t *output, const char *captured_output);

/**
 * @brief Verify if a specific output was produced.
 *
 * This function verifies if the expected output was produced by the mocked function
 * at the specified call index.
 *
 * @param output The output mock object to verify the output for.
 * @param expected_output The expected output to verify against.
 * @param call_index The index of the function call to verify the output for.
 * @return true if the expected output was produced, false otherwise.
 */
bool xmock_output_verify(xmock_output_t *output, const char *expected_output, int32_t call_index);

/**
 * @brief Verify the number of times the output function was called.
 *
 * This function verifies if the mocked function was called the expected number of times.
 *
 * @param output The output mock object to verify the call count for.
 * @param expected_call_count The expected number of times the function was called.
 * @return true if the function was called the expected number of times, false otherwise.
 */
bool xmock_output_verify_call_count(xmock_output_t *output, int32_t expected_call_count);

/**
 * @brief Reset the output mock object for reuse.
 *
 * This function resets the output mock object, clearing any captured output and resetting
 * the call count.
 *
 * @param output The output mock object to reset.
 */
void xmock_output_reset(xmock_output_t *output);

/**
 * @brief Erase the output mock object.
 *
 * This function erases the output mock object, freeing any allocated memory.
 *
 * @param output The output mock object to erase.
 */
void xmock_output_erase(xmock_output_t *output);

#ifdef __cplusplus
}
#endif

#endif
