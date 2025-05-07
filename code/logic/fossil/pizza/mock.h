/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_MOCK_MOCKUP_H
#define FOSSIL_MOCK_MOCKUP_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Type declarations
// *****************************************************************************

typedef struct fossil_mock_call_t {
    char *function_name;
    char **arguments;
    int num_args;
    struct fossil_mock_call_t *next;
} fossil_mock_call_t;

typedef struct {
    fossil_mock_call_t *head;
    fossil_mock_call_t *tail;
    int size;
} fossil_mock_calllist_t;

// *****************************************************************************
// Function declarations
// *****************************************************************************

/**
 * Initializes a fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to initialize.
 */
void fossil_mock_init(fossil_mock_calllist_t *list);

/**
 * Destroys a fossil_mock_calllist_t and frees all associated memory.
 * 
 * @param list The fossil_mock_calllist_t to destroy.
 */
void fossil_mock_destroy(fossil_mock_calllist_t *list);

/**
 * Adds a fossil_mock_call_t to the fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to add the fossil_mock_call_t to.
 * @param function_name The name of the function being called.
 * @param arguments The arguments passed to the function.
 * @param num_args The number of arguments.
 */
void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, char **arguments, int num_args);

/**
 * Prints the contents of a fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to print.
 */
void fossil_mock_print(fossil_mock_calllist_t *list);

#ifdef __cplusplus
}
#endif

/**
 * @brief Macro for initializing the mock list.
 *
 * This macro initializes the mock list by calling the fossil_mock_init function.
 *
 * @param list The mock list to initialize.
 */
#define _MOCK_INIT(list) fossil_mock_init(&list)

/**
 * @brief Macro for destroying the mock list.
 *
 * This macro destroys the mock list by calling the fossil_mock_destroy function.
 *
 * @param list The mock list to destroy.
 */
#define _MOCK_DESTROY(list) fossil_mock_destroy(&list)

/**
 * @brief Macro for adding a mock function call to the mock list.
 *
 * This macro adds a mock function call to the mock list by calling the fossil_mock_add_call function.
 *
 * @param list     The mock list to add the call to.
 * @param func     The mock function to add the call for.
 * @param args     The arguments of the mock function call.
 * @param num_args The number of arguments in the mock function call.
 */
#define _MOCK_ADD_CALL(list, func, args, num_args) fossil_mock_add_call(&list, func, args, num_args)

/**
 * @brief Macro for printing the mock list.
 *
 * This macro prints the mock list by calling the fossil_mock_print function.
 *
 * @param list The mock list to print.
 */
#define _MOCK_PRINT(list) fossil_mock_print(&list)

/**
 * @def _FOSSIL_MOCK_FUNC
 * @brief Macro for creating a mock function with the specified return type, name, and parameters.
 * 
 * This macro simplifies the creation of mock functions by defining a function with the given return
 * type, name, and parameters. The function name will be prefixed with "fossil_mockup_" to clearly indicate
 * that it is a mock function.
 * 
 * @param return_type   The return type of the mock function.
 * @param name          The name of the mock function.
 * @param ...           The parameters of the mock function in the format: (type1 param1, type2 param2, ...).
 * @return The return type specified for the mock function.
 */
#ifdef _WIN32
#define _FOSSIL_MOCK_FUNC(return_type, name, ...) \
    __declspec(dllexport) return_type fossil_mockup_##name(__VA_ARGS__)
#else
#define _FOSSIL_MOCK_FUNC(return_type, name, ...) \
    return_type fossil_mockup_##name(__VA_ARGS__)
#endif

/**
 * @def _FOSSIL_MOCK_ALIAS
 * @brief Macro for creating a type alias based on an existing type.
 * 
 * This macro creates a type alias for a given existing type.
 * 
 * @param new_type       The name of the new type alias.
 * @param existing_type  The existing type to create an alias for.
 */
#define _FOSSIL_MOCK_ALIAS(new_type, existing_type) \
    typedef existing_type new_type; \
    new_type fossil_mockup_##new_type(void)

/**
 * @def _FOSSIL_MOCK_STRUCT
 * @brief Macro for creating a mock struct with the specified name and members.
 * 
 * This macro simplifies the creation of mock structs by defining a struct with the given name
 * and members. The struct name will be prefixed with "fossil_mockup_" to clearly indicate that it is a mock struct.
 * 
 * @param name     The name of the mock struct.
 */
#ifdef __cplusplus
#define _FOSSIL_MOCK_STRUCT(name) \
    struct name
#else
#define _FOSSIL_MOCK_STRUCT(name) \
    typedef struct name
#endif

// *****************************************************************************
// Public API Macros
// *****************************************************************************

// *****************************************************************************
// Mocking framework
// *****************************************************************************

/**
 * @brief Macro for initializing the mock list.
 *
 * This macro initializes the mock list by calling the fossil_mock_init function.
 *
 * @param list The mock list to initialize.
 */
#define MOCK_INIT(list) \
    _MOCK_INIT(list)

/**
 * @brief Macro for destroying the mock list.
 *
 * This macro destroys the mock list by calling the fossil_mock_destroy function.
 *
 * @param list The mock list to destroy.
 */
#define MOCK_DESTROY(list) \
    _MOCK_DESTROY(list)

/**
 * @brief Macro for adding a mock function call to the mock list.
 *
 * This macro adds a mock function call to the mock list by calling the fossil_mock_add_call function.
 *
 * @param list     The mock list to add the call to.
 * @param func     The mock function to add the call for.
 * @param args     The arguments of the mock function call.
 * @param num_args The number of arguments in the mock function call.
 */
#define MOCK_ADD_CALL(list, func, args, num_args) \
    _MOCK_ADD_CALL(list, func, args, num_args)

/**
 * @brief Macro for printing the mock list.
 *
 * This macro prints the mock list by calling the fossil_mock_print function.
 *
 * @param list The mock list to print.
 */
#define MOCK_PRINT(list) \
    _MOCK_PRINT(list)

/**
 * @def FOSSIL_MOCK_FUNC
 * @brief Macro for creating a mock function with the specified return type, name, and parameters.
 *
 * This macro simplifies the creation of mock functions by defining a function with the given return
 * type, name, and parameters. The function name will be prefixed with "fossil_mockup_" to clearly indicate
 * that it is a mock function.
 *
 * @param return_type   The return type of the mock function.
 * @param name          The name of the mock function.
 * @param ...           The parameters of the mock function in the format: (type1 param1, type2 param2, ...).
 * @return The return type specified for the mock function.
 */
#define FOSSIL_MOCK_FUNC(return_type, name, ...) \
    _FOSSIL_MOCK_FUNC(return_type, name, __VA_ARGS__)

/**
 * @def FOSSIL_MOCK_ALIAS
 * @brief Macro for creating a type alias based on an existing type.
 *
 * This macro creates a type alias for a given existing type.
 *
 * @param new_type       The name of the new type alias.
 * @param existing_type  The existing type to create an alias for.
 */
#define FOSSIL_MOCK_ALIAS(new_type, existing_type) \
    _FOSSIL_MOCK_ALIAS(new_type, existing_type)

/**
 * @def FOSSIL_MOCK_STRUCT
 * 
 * @brief Macro for creating a mock struct with the specified name and members.
 * 
 * This macro simplifies the creation of mock structs by defining a struct with the given name
 * and members. The struct name will be prefixed with "fossil_mockup_" to clearly indicate that it is a mock struct.
 * 
 * @param name     The name of the mock struct.
 */
#define FOSSIL_MOCK_STRUCT(name) \
    _FOSSIL_MOCK_STRUCT(name)

#endif // FOSSIL_MOCK_FRAMEWORK_H
