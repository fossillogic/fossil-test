/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_MOCK_H
#define FOSSIL_MOCK_H

#include "common.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Type declarations
// *****************************************************************************

// --- Typed mock argument values ---
typedef enum {
    FOSSIL_MOCK_MAIP_TYPE_I8,
    FOSSIL_MOCK_MAIP_TYPE_I16,
    FOSSIL_MOCK_MAIP_TYPE_I32,
    FOSSIL_MOCK_MAIP_TYPE_I64,
    FOSSIL_MOCK_MAIP_TYPE_U8,
    FOSSIL_MOCK_MAIP_TYPE_U16,
    FOSSIL_MOCK_MAIP_TYPE_U32,
    FOSSIL_MOCK_MAIP_TYPE_U64,
    FOSSIL_MOCK_MAIP_TYPE_HEX,
    FOSSIL_MOCK_MAIP_TYPE_OCTAL,
    FOSSIL_MOCK_MAIP_TYPE_FLOAT,
    FOSSIL_MOCK_MAIP_TYPE_DOUBLE,
    FOSSIL_MOCK_MAIP_TYPE_WSTR,
    FOSSIL_MOCK_MAIP_TYPE_CSTR,
    FOSSIL_MOCK_MAIP_TYPE_CCHAR,
    FOSSIL_MOCK_MAIP_TYPE_WCHAR,
    FOSSIL_MOCK_MAIP_TYPE_BOOL,
    FOSSIL_MOCK_MAIP_TYPE_SIZE,
    FOSSIL_MOCK_MAIP_TYPE_ANY
} fossil_mock_maip_type_t;

typedef struct {
    union {
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        uint64_t hex;
        uint64_t octal;
        float f32;
        double f64;
        const wchar_t *wstr;
        const char *cstr;
        char cchar;
        wchar_t wchar;
        bool boolean;
        size_t size;
        void *any;
    } as;
    bool mutable_flag;
} fossil_mock_maip_value_t;

/* Optional descriptive metadata is borrowed; the mock does not own these strings. */
typedef struct {
    const char *name;
    const char *description;
    const char *id;
} fossil_mock_maip_attribute_t;

typedef struct {
    fossil_mock_maip_type_t type;
    fossil_mock_maip_value_t value;
    fossil_mock_maip_attribute_t attribute;
} fossil_mock_maip_t;

// ******************************************************************************
// Mock call structure
// *****************************************************************************

typedef struct fossil_mock_call_t fossil_mock_call_t;
typedef bool (*fossil_mock_stub_fn)(const fossil_mock_call_t *call,
                                    fossil_mock_maip_value_t *return_value,
                                    void *user_data);

struct fossil_mock_call_t {
    char *function_name;
    fossil_mock_maip_t *arguments;
    int num_args;
    fossil_mock_maip_value_t return_value;
    fossil_mock_stub_fn stub;
    void *stub_user_data;
    struct fossil_mock_call_t *next;
};

typedef struct {
    fossil_mock_call_t *head;
    fossil_mock_call_t *tail;
    int size;
} fossil_mock_calllist_t;

// *****************************************************************************
// Function declarations
// *****************************************************************************

/**
 * @brief Initializes a fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to initialize.
 * 
 * @note This function must be called before using the fossil_mock_calllist_t.
 */
FOSSIL_MAIP_API void fossil_mock_init(fossil_mock_calllist_t *list);

/**
 * @brief Destroys a fossil_mock_calllist_t and frees all associated memory.
 * 
 * @param list The fossil_mock_calllist_t to destroy.
 * 
 * @note This function should be called when the fossil_mock_calllist_t is no longer needed to avoid memory leaks.
 */
FOSSIL_MAIP_API void fossil_mock_destroy(fossil_mock_calllist_t *list);

/**
 * @brief Adds a fossil_mock_call_t to the fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to add the fossil_mock_call_t to.
 * @param function_name The name of the function being called.
 * @param arguments The arguments passed to the function.
 * @param num_args The number of arguments.
 * 
 * @note This function allocates memory for the fossil_mock_call_t and its arguments. The caller is responsible for ensuring that the arguments are valid and that the list is properly initialized.
 */
FOSSIL_MAIP_API void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, fossil_mock_maip_t *arguments, int num_args);

/**
 * @brief Prints the contents of a fossil_mock_calllist_t.
 * 
 * @param list The fossil_mock_calllist_t to print.
 * 
 * @note This function prints the function names and their arguments in a human-readable format. It is useful for debugging and verifying the recorded calls.
 */
FOSSIL_MAIP_API void fossil_mock_print(fossil_mock_calllist_t *list);

/**
 * @brief Sets a stub function for a fossil_mock_call_t.
 * 
 * @param call The fossil_mock_call_t to set the stub for.
 * @param stub The stub function to set.
 * @param user_data User-defined data to pass to the stub function.
 * 
 * @note The stub function will be called when the mock function is invoked, allowing for custom behavior during testing.
 */
FOSSIL_MAIP_API void fossil_mock_set_stub(fossil_mock_call_t *call, fossil_mock_stub_fn stub, void *user_data);

/**
 * @brief Sets a typed return value for a call that has no stub.
 * 
 * @param call The fossil_mock_call_t to set the return value for.
 * @param value The typed return value to set.
 * 
 * @note This function allows for specifying a return value for a mock function call when no stub is provided. The return value will be used when the mock function is invoked.
 */
FOSSIL_MAIP_API void fossil_mock_set_return_value(fossil_mock_call_t *call, fossil_mock_maip_value_t value);

/**
 * @brief Counts the number of recorded calls to a function.
 * 
 * @param list The fossil_mock_calllist_t to search.
 * @param function_name The name of the function to count.
 * 
 * @return The number of recorded calls to the function.
 * 
 * @note This function is useful for verifying that a function was called the expected number of times during testing.
 */
FOSSIL_MAIP_API int fossil_mock_count_calls(const fossil_mock_calllist_t *list, const char *function_name);

/**
 * @brief Verifies that a recorded call matches the expected arguments.
 * 
 * @param call The fossil_mock_call_t to verify.
 * @param arguments The expected arguments.
 * @param num_args The number of expected arguments.
 * 
 * @return True if the recorded call matches the expected arguments, false otherwise.
 * 
 * @note This function is useful for verifying that a function was called with the correct arguments during testing.
 */
FOSSIL_MAIP_API bool fossil_mock_verify_call(const fossil_mock_call_t *call, const fossil_mock_maip_t *arguments, int num_args);

/**
 * @brief Verifies that recorded calls match the supplied function-name sequence exactly.
 * 
 * @param list The fossil_mock_calllist_t to verify.
 * @param function_names An array of function names to match.
 * @param count The number of function names in the array.
 * 
 * @return True if the recorded calls match the supplied function-name sequence exactly, false otherwise.
 * 
 * @note This function is useful for verifying that a sequence of function calls occurred in the expected order during testing.
 */
FOSSIL_MAIP_API bool fossil_mock_verify_order(const fossil_mock_calllist_t *list, const char *const *function_names, int count);

/**
 * @brief Captures the output of a function to a buffer for testing purposes.
 *
 * @param buffer The buffer to store the captured output.
 * @param size The size of the buffer.
 * @param function The function whose output is to be captured.
 * 
 * @return The number of characters captured.
 * 
 * @note This function redirects the standard output to a temporary buffer, allowing for the capture of output generated by the specified function. The captured output can then be compared against expected output for testing purposes.
 */
FOSSIL_MAIP_API int fossil_mock_capture_output(char *buffer, size_t size, void (*function)(void));

/**
 * @brief Compares the captured output with the expected output.
 * 
 * @param captured The captured output.
 * @param expected The expected output.
 * 
 * @return True if the captured output matches the expected output, false otherwise.
 * 
 * @note This function is useful for verifying that the output generated by a function matches the expected output during testing.
 */
FOSSIL_MAIP_API bool fossil_mock_compare_output(const char *captured, const char *expected);

#ifdef __cplusplus
}
#endif

#define _MOCK_INIT(list) fossil_mock_init(&list)

#define _MOCK_DESTROY(list) fossil_mock_destroy(&list)

#define _MOCK_ADD_CALL(list, func, args, num_args) fossil_mock_add_call(&list, func, args, num_args)

#define _MOCK_PRINT(list) fossil_mock_print(&list)

#ifdef _WIN32
#define _FOSSIL_MOCK_FUNC(return_type, name, ...) \
    __declspec(dllexport) return_type fossil_mockup_##name(__VA_ARGS__)
#else
#define _FOSSIL_MOCK_FUNC(return_type, name, ...) \
    return_type fossil_mockup_##name(__VA_ARGS__)
#endif

#define _FOSSIL_MOCK_ALIAS(new_type, existing_type) \
    typedef existing_type new_type; \
    new_type fossil_mockup_##new_type(void)

#ifdef __cplusplus
#define _FOSSIL_MOCK_STRUCT(name) \
    struct name
#else
#define _FOSSIL_MOCK_STRUCT(name) \
    typedef struct name
#endif

#define _MOCK_SET_STUB(call, stub, user_data) \
    fossil_mock_set_stub(call, stub, user_data)

#define _MOCK_SET_RETURN_VALUE(call, value) \
    fossil_mock_set_return_value(call, value)

#define _MOCK_COUNT_CALLS(list, function_name) \
    fossil_mock_count_calls(list, function_name)

#define _MOCK_VERIFY_CALL(call, arguments, num_args) \
    fossil_mock_verify_call(call, arguments, num_args)

#define _MOCK_VERIFY_ORDER(list, function_names, count) \
    fossil_mock_verify_order(list, function_names, count)

#define _FOSSIL_MOCK_CAPTURE_OUTPUT(buffer, size, function) \
    fossil_mock_capture_output(buffer, size, function)

#define _FOSSIL_MOCK_COMPARE_OUTPUT(captured, expected) \
    fossil_mock_compare_output(captured, expected)

#define _MOCK_FUNC_CALL(name) \
    fossil_mockup_##name

// *****************************************************************************
// Public API Macros
// *****************************************************************************

/**
 * @def MOCK_INIT
 * @brief Initializes a mock list.
 * @param list The mock list to initialize.
 * @return None.
 * @note Call this before using the mock list.
 */
#define MOCK_INIT(list) \
    _MOCK_INIT(list)

/**
 * @def MOCK_DESTROY
 * @brief Destroys a mock list.
 * @param list The mock list to destroy.
 * @return None.
 * @note Call this when the mock list is no longer needed to free associated memory.
 */
#define MOCK_DESTROY(list) \
    _MOCK_DESTROY(list)

/**
 * @def MOCK_ADD_CALL
 * @brief Adds a mock function call to a mock list.
 * @param list The mock list to add the call to.
 * @param func The mock function to record.
 * @param args The arguments of the mock function call.
 * @param num_args The number of arguments in the call.
 * @return None.
 * @note Records the function name and arguments for later verification.
 */
#define MOCK_ADD_CALL(list, func, args, num_args) \
    _MOCK_ADD_CALL(list, func, args, num_args)

/**
 * @def MOCK_PRINT
 * @brief Prints the contents of a mock list.
 * @param list The mock list to print.
 * @return None.
 * @note Useful for debugging and inspecting recorded calls.
 */
#define MOCK_PRINT(list) \
    _MOCK_PRINT(list)

/**
 * @def FOSSIL_MOCK_FUNC
 * @brief Defines a mock function.
 * @param return_type The return type of the mock function.
 * @param name The name of the mock function.
 * @param ... The mock function's parameters.
 * @return Defines a function that returns return_type when called.
 * @note The generated function name is prefixed with "fossil_mockup_".
 */
#define FOSSIL_MOCK_FUNC(return_type, name, ...) \
    _FOSSIL_MOCK_FUNC(return_type, name, __VA_ARGS__)

/**
 * @def FOSSIL_MOCK_ALIAS
 * @brief Creates a type alias for a mock function.
 * @param new_type The new type name for the alias.
 * @param existing_type The existing type to alias.
 * @return None.
 * @note The alias can provide a descriptive or context-specific name.
 */
#define FOSSIL_MOCK_ALIAS(new_type, existing_type) \
    _FOSSIL_MOCK_ALIAS(new_type, existing_type)

/**
 * @def FOSSIL_MOCK_STRUCT
 * @brief Declares a mock struct.
 * @param name The name of the mock struct.
 * @return Defines the named struct type.
 * @note Use this to define mock data structures for tests.
 */
#define FOSSIL_MOCK_STRUCT(name) \
    _FOSSIL_MOCK_STRUCT(name)

/**
 * @def MOCK_SET_STUB
 * @brief Sets a stub function for a mock call.
 * @param call The mock call to configure.
 * @param stub The stub function to set.
 * @param user_data User-defined data passed to the stub function.
 * @return None.
 * @note The stub runs when the mock function is invoked.
 */
#define MOCK_SET_STUB(call, stub, user_data) _MOCK_SET_STUB(call, stub, user_data)

/**
 * @def MOCK_SET_RETURN_VALUE
 * @brief Sets a return value for a mock call.
 * @param call The mock call to configure.
 * @param value The return value to set.
 * @return None.
 * @note The configured value is used when the mock function is invoked.
 */
#define MOCK_SET_RETURN_VALUE(call, value) _MOCK_SET_RETURN_VALUE(call, value)

/**
 * @def MOCK_COUNT_CALLS
 * @brief Counts calls to a mock function.
 * @param list The mock call list to search.
 * @param function_name The name of the mock function to count.
 * @return The number of calls to the specified function.
 * @note Use this to verify how often a function was called during a test.
 */
#define MOCK_COUNT_CALLS(list, function_name) _MOCK_COUNT_CALLS(list, function_name)

/**
 * @def MOCK_VERIFY_CALL
 * @brief Verifies a mock call's arguments.
 * @param call The mock call to verify.
 * @param arguments The expected arguments.
 * @param num_args The number of expected arguments.
 * @return The result of comparing the recorded call with the expected arguments.
 * @note Use this to validate function arguments during testing.
 */
#define MOCK_VERIFY_CALL(call, arguments, num_args) _MOCK_VERIFY_CALL(call, arguments, num_args)

/**
 * @def MOCK_VERIFY_ORDER
 * @brief Verifies the order of mock function calls.
 * @param list The mock call list to inspect.
 * @param function_names An array of expected function names in call order.
 * @param count The number of expected function names.
 * @return The result of comparing the recorded and expected call order.
 * @note The expected names must be ordered as the calls should have occurred.
 */
#define MOCK_VERIFY_ORDER(list, function_names, count) _MOCK_VERIFY_ORDER(list, function_names, count)

/**
 * @def FOSSIL_MOCK_REDIRECT_STDOUT
 * @brief Captures a function's stdout in a buffer.
 * @param buffer The buffer to capture the output.
 * @param size   The size of the buffer.
 * @param function The function whose stdout is captured.
 * @return The result of the output-capture operation.
 * @note The buffer must have room for the captured output.
 */
#define FOSSIL_MOCK_REDIRECT_STDOUT(buffer, size, function) \
    _FOSSIL_MOCK_CAPTURE_OUTPUT(buffer, size, function)

/**
 * @def FOSSIL_MOCK_COMPARE_OUTPUT
 * @brief Compares captured output with expected output.
 * @param captured The captured output.
 * @param expected The expected output.
 * @return True if the outputs match; otherwise, false.
 * @note The comparison is performed by the mock output-comparison helper.
 */
#define FOSSIL_MOCK_COMPARE_OUTPUT(captured, expected) \
    _FOSSIL_MOCK_COMPARE_OUTPUT(captured, expected)

/**
 * @def MOCK_FUNC_CALL
 * @brief Calls the mock function with the given name.
 * @param name The name of the mock function call.
 * @return The value returned by the corresponding mock function.
 * @note Expands the name to the corresponding "fossil_mockup_"-prefixed function.
 */
#define MOCK_FUNC_CALL(name) \
    _MOCK_FUNC_CALL(name)

#endif // FOSSIL_MOCK_FRAMEWORK_H
