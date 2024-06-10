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
#ifndef FSCL_XMOCK_INTERNAL_H
#define FSCL_XMOCK_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef bool (*xmock_comparator_t)(void *expected, void *actual);

// Mock object type
typedef struct xmock {
    char *function_name;
    void **expected_args;
    xmock_comparator_t *comparators;
    void **actual_args;
    int32_t num_args;
    void **return_values;
    int32_t return_count;
    int32_t call_count;
    bool called;
    struct xmock *next; // for chaining mocks
} xmock_t;

// Create a new mock object
/**
 * @brief Creates a new mock object with the specified function name and number of arguments.
 * 
 * @param function_name The name of the function being mocked.
 * @param num_args      The number of arguments expected by the function being mocked.
 * @return A pointer to the newly created mock object.
 */
xmock_t* xmock_create(const char *function_name, int32_t num_args);

// Set expected arguments for the mock
/**
 * @brief Sets the expected arguments for the specified mock object.
 * 
 * @param mock The mock object for which to set the expected arguments.
 * @param ...  The expected arguments in the format: arg1, arg2, ...
 */
void xmock_set_expected_args(xmock_t *mock, ...);

// Set a custom comparator for an argument
/**
 * @brief Sets a custom comparator for the specified argument of the mock object.
 * 
 * @param mock       The mock object for which to set the custom comparator.
 * @param arg_index  The index of the argument for which to set the custom comparator.
 * @param comparator The custom comparator function.
 */
void xmock_set_comparator(xmock_t *mock, int32_t arg_index, xmock_comparator_t comparator);

// Set the return values for the mock
/**
 * @brief Sets the return values for the specified mock object.
 * 
 * @param mock  The mock object for which to set the return values.
 * @param count The number of return values.
 * @param ...   The return values in the format: value1, value2, ...
 */
void xmock_set_return_values(xmock_t *mock, int32_t count, ...);

// Simulate calling the mock function
/**
 * @brief Simulates calling the specified mock object with the given arguments.
 * 
 * @param mock The mock object to call.
 * @param ...  The arguments to pass to the mock function.
 * @return The return value of the mock function.
 */
void* xmock_call(xmock_t *mock, ...);

// Verify that the mock was called with the expected arguments
/**
 * @brief Verifies that the specified mock object was called with the expected arguments.
 * 
 * @param mock The mock object to verify.
 * @return true if the mock was called with the expected arguments, false otherwise.
 */
bool xmock_verify(xmock_t *mock);

// Verify the number of times the mock function was called
/**
 * @brief Verifies the number of times the specified mock object was called.
 * 
 * @param mock               The mock object to verify.
 * @param expected_call_count The expected number of times the mock function should have been called.
 * @return true if the mock was called the expected number of times, false otherwise.
 */
bool xmock_verify_call_count(xmock_t *mock, int32_t expected_call_count);

// Reset the mock object for reuse
/**
 * @brief Resets the specified mock object for reuse.
 * 
 * @param mock The mock object to reset.
 */
void xmock_reset(xmock_t *mock);

// Erase the mock object
/**
 * @brief Erases the specified mock object.
 * 
 * @param mock The mock object to erase.
 */
void xmock_erase(xmock_t *mock);

// Built-in comparators for common data types
/**
 * @brief Comparator function for comparing two int32_t values.
 * 
 * @param expected The expected int32_t value.
 * @param actual   The actual int32_t value.
 * @return true if the values are equal, false otherwise.
 */
bool xmock_i32_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two C-style strings.
 * 
 * @param expected The expected C-style string.
 * @param actual   The actual C-style string.
 * @return true if the strings are equal, false otherwise.
 */
bool xmock_cstr_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two pointers.
 * 
 * @param expected The expected pointer.
 * @param actual   The actual pointer.
 * @return true if the pointers are equal, false otherwise.
 */
bool xmock_ptr_comparator(void *expected, void *actual);

/**
 * @brief Comparator function for comparing two pointers.
 * 
 * @param expected The expected pointer.
 * @param actual   The actual pointer.
 * @return true if the pointers are equal, false otherwise.
 */
void xmock_log(const char *format, ...);

// Custom implementation of strdup
static inline char* _custom_xmock_core_strdup(const char* str) {
    if (!str) return NULL; // Handle NULL pointer gracefully

    size_t len = 0;
    while (str[len] != '\0') len++; // Calculate the length of the string

    char* dup = (char*)malloc((len + 1) * sizeof(char)); // Allocate memory for the duplicate string
    if (!dup) return NULL; // Check if malloc failed

    for (size_t i = 0; i < len; i++) {
        dup[i] = str[i]; // Copy each character from the original string to the duplicate
    }
    dup[len] = '\0'; // Add null terminator to the end of the duplicate string

    return dup;
}

/**
 * @def _XMOCK_FUNC_DEF
 * @brief Macro for creating a mock function with the specified return type, name, and parameters.
 * 
 * This macro simplifies the creation of mock functions by defining a function with the given return
 * type, name, and parameters. The function name will be prefixed with "xmock_" to clearly indicate
 * that it is a mock function.
 * 
 * @param return_type   The return type of the mock function.
 * @param name          The name of the mock function.
 * @param ...           The parameters of the mock function in the format: (type1 param1, type2 param2, ...).
 * @return The return type specified for the mock function.
 */
#define _XMOCK_FUNC_DEF(return_type, name, ...) \
    return_type xmock_##name(__VA_ARGS__)

/**
 * @def _XMOCK_TYPE_ALIAS
 * @brief Macro for creating a type alias based on an existing type.
 * 
 * This macro creates a type alias for a given existing type.
 * 
 * @param new_type       The name of the new type alias.
 * @param existing_type  The existing type to create an alias for.
 */
#define _XMOCK_TYPE_ALIAS(new_type, existing_type) \
    typedef existing_type xmock_##new_type##_type; \
    xmock_##new_type##_type xmock_##new_type(void)

/**
 * @def _XMOCK_STRUCT_DEF
 * @brief Macro for creating a mock struct with the specified name and members.
 * 
 * This macro simplifies the creation of mock structs by defining a struct with the given name
 * and members.
 * 
 * @param name  The name of the mock struct.
 * @param ...   The members of the mock struct in the format: type1 member1; type2 member2; ...
 */
#define _XMOCK_STRUCT_DEF(name, ...) \
    typedef struct { \
        __VA_ARGS__ \
    } xmock_##name;

#ifdef __cplusplus
}
#endif

#endif
