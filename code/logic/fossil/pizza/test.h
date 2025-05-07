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
#ifndef FOSSIL_TEST_INTERNAL_H
#define FOSSIL_TEST_INTERNAL_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

// --- Return codes ---
enum {
    FOSSIL_PIZZA_SUCCESS = 0,
    FOSSIL_PIZZA_FAILURE = -1
};

typedef enum {
    FOSSIL_PIZZA_CASE_EMPTY = 0,
    FOSSIL_PIZZA_CASE_PASS,
    FOSSIL_PIZZA_CASE_FAIL,
    FOSSIL_PIZZA_CASE_TIMEOUT,
    FOSSIL_PIZZA_CASE_SKIPPED,
    FOSSIL_PIZZA_CASE_UNEXPECTED
} fossil_pizza_case_result_t;

// --- Pizza Data Types ---
typedef enum {
    FOSSIL_PIZZA_TYPE_I8,
    FOSSIL_PIZZA_TYPE_I16,
    FOSSIL_PIZZA_TYPE_I32,
    FOSSIL_PIZZA_TYPE_I64,
    FOSSIL_PIZZA_TYPE_U8,
    FOSSIL_PIZZA_TYPE_U16,
    FOSSIL_PIZZA_TYPE_U32,
    FOSSIL_PIZZA_TYPE_U64,
    FOSSIL_PIZZA_TYPE_HEX,
    FOSSIL_PIZZA_TYPE_OCTAL,
    FOSSIL_PIZZA_TYPE_FLOAT,
    FOSSIL_PIZZA_TYPE_DOUBLE,
    FOSSIL_PIZZA_TYPE_WSTR,
    FOSSIL_PIZZA_TYPE_CSTR,
    FOSSIL_PIZZA_TYPE_CCHAR,
    FOSSIL_PIZZA_TYPE_WCHAR,
    FOSSIL_PIZZA_TYPE_BOOL,
    FOSSIL_PIZZA_TYPE_SIZE,
    FOSSIL_PIZZA_TYPE_ANY
} fossil_pizza_type_t;

typedef struct {
    char *data;
    bool mutable_flag;
} fossil_pizza_value_t;

typedef struct {
    char* name;
    char* description;
    char* id;
} fossil_pizza_attribute_t;

typedef struct {
    fossil_pizza_type_t type;
    fossil_pizza_value_t value;
    fossil_pizza_attribute_t attribute;
} fossil_pizza_t;

// --- Score Struct ---
typedef struct {
    int passed;
    int failed;
    int skipped;
    int timeout;
    int unexpected;
    int empty;
} fossil_pizza_score_t;

// --- Test Case ---
typedef struct {
    char* name;
    void (*setup)(void);
    void (*teardown)(void);
    void (*run)(void);
    uint64_t elapsed_ns;
    fossil_pizza_case_result_t result;
} fossil_pizza_case_t;

// In fossil_pizza_suite_t
typedef struct {
    char* suite_name;
    fossil_pizza_case_t* cases;
    size_t count;
    size_t capacity;
    void (*setup)(void);
    void (*teardown)(void);
    uint64_t time_elapsed_ns;
    int total_score;
    int total_possible;
    fossil_pizza_score_t score;
} fossil_pizza_suite_t;

// In fossil_pizza_engine_t
typedef struct {
    fossil_pizza_suite_t* suites;
    size_t count;
    size_t capacity;
    int score_total;
    int score_possible;
    fossil_pizza_score_t score;
} fossil_pizza_engine_t;

// --- Initialization ---

/** * Initializes a new fossil_pizza_engine_t instance.
 * @param engine Pointer to the engine to initialize.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv);

// --- Adding Test Suites and Cases ---

/** Adds a test suite to the engine.
 * @param engine Pointer to the engine instance.
 * @param suite The suite to add.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite);

/** Adds a test case to a suite.
 * @param suite Pointer to the suite instance.
 * @param test_case Pointer to the test case to add.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case);

// --- Execution ---

/** Runs a single test suite.
 * @param suite Pointer to the suite instance.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_run_suite(fossil_pizza_suite_t* suite);

/** Runs all test suites in the engine.
 * @param engine Pointer to the engine instance.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_run_all(fossil_pizza_engine_t* engine);

// --- Summary + Teardown ---

/** Prints a summary of the test results.
 * @param engine Pointer to the engine instance.
 */
void fossil_pizza_summary(const fossil_pizza_engine_t* engine);

/** Cleans up and ends the test engine.
 * @param engine Pointer to the engine instance.
 */
void fossil_pizza_end(fossil_pizza_engine_t* engine);

#ifdef __cplusplus
}
#endif

/** @brief Macro to define a test case.
 * 
 * This macro is used to define a test case, which is a single unit of testing
 * that verifies a specific functionality or behavior. The test case can be
 * executed independently or as part of a test suite.
 * 
 * @param test_name The name of the test case to define.
 */
#define FOSSIL_TEST(test_name) \
    static fossil_pizza_case_t test_case_##test_name = { \
        .name = #test_name, \
        .setup = NULL, \
        .teardown = NULL, \
        .run = test_name##_run, \
        .elapsed_ns = 0, \
        .result = FOSSIL_PIZZA_CASE_EMPTY \
    }; \
    void test_name##_run(void)

/** @brief Macro to set a test case's setup function.
 * 
 * This macro is used to specify a setup function for a test case. The setup
 * function will be called before the test case is executed, allowing for any
 * necessary initialization or preparation.
 * 
 * @param test_name The name of the test case.
 * @param before The name of the setup function to call before the test case.
 */
#define FOSSIL_TEST_SET_BEFORE(test_name, before) \
    test_case_##test_name.setup = setup_##before

/** @brief Macro to set a test case's setup function.
 * 
 * This macro is used to specify a setup function for a test case. The setup
 * function will be called before the test case is executed, allowing for any
 * necessary initialization or preparation.
 * 
 * @param test_name The name of the test case.
 * @param before The name of the setup function to call before the test case.
 */
#define FOSSIL_TEST_SET_AFTER(test_name, after) \
    test_case_##test_name.teardown = teardown_##after

/** @brief Macro to define a test suite.
 * 
 * This macro is used to define a test suite, which is a collection of test cases
 * that are related to each other. The test suite can be executed as a whole to
 * verify the correctness of a group of functionalities.
 * 
 * @param suite_name The name of the suite to define.
 */
#define FOSSIL_SUITE(suite) \
    void setup_##suite(void); \
    void teardown_##suite(void); \
    static fossil_pizza_suite_t suite_##suite = { \
        .suite_name = #suite, \
        .cases = NULL, \
        .count = 0, \
        .capacity = 0, \
        .setup = setup_##suite, \
        .teardown = teardown_##suite, \
        .time_elapsed_ns = 0, \
        .total_score = 0, \
        .total_possible = 0, \
        .score = {0} \
    }

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_SETUP(test_setup) \
    void setup_##test_setup(void)

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_TEARDOWN(test_teardown) \
    void teardown_##test_teardown(void)

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_BEFORE(test_setup) \
    void setup_##test_setup(void)

/** @brief Macro to define a test teardown function.
 * 
 * This macro is used to define a teardown function for a test case or suite. The
 * teardown function will be called after the test case or suite has been executed, and
 * can be used to clean up resources or reset the test environment.
 *
 * @param test_teardown The name of the teardown function to define.
 */
#define FOSSIL_AFTER(test_teardown) \
    void teardown_##test_teardown(void)

/** @brief Macro to add a test case to a specific suite.
 * 
 * This macro is used to add a test case to a specific test suite that has been
 * defined in the test engine. It will link the test case to the suite and
 * ensure it is executed when the suite is run.
 * 
 * @param suite The name of the suite to which the test case will be added.
 * @param test_case The name of the test case to add.
 */
#define FOSSIL_TEST_ADD(suite, test_case) \
    fossil_pizza_add_case(&suite_##suite, test_case_##test_case)

/** @brief Macro to run a specific test suite.
 * 
 * This macro is used to run a specific test suite that has been defined in the
 * test engine. It will execute all test cases within the specified suite and
 * print the results.
 * 
 * @param suite The name of the suite to run.
 */
#define FOSSIL_RUN_SUITE(suite) \
    fossil_pizza_run_suite(&suite_##suite)

/** @brief Macro to run all test suites in the engine.
 * 
 * This macro is used to run all test suites that have been added to the test
 * engine. It will execute each suite and its associated test cases, collecting
 * results and printing a summary at the end.
 * 
 * @param engine The engine instance containing the test suites.
 */
#define FOSSIL_RUN_ALL(engine) \
    fossil_pizza_run_all(engine)

/** @brief Macro to start the test engine.
 * 
 * This macro is used to initialize and start the test engine. It should be called
 * at the beginning of the test execution to set up the environment for running
 * tests.
 * 
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 */
#define FOSSIL_TEST_START(argc, argv) \
    fossil_pizza_engine_t engine; \
    if (fossil_pizza_start(&engine, argc, argv) != FOSSIL_PIZZA_SUCCESS) { \
        return FOSSIL_PIZZA_FAILURE; \
    }

/** @brief Macro to print a summary of the test results.
 * 
 * This macro is used to print a summary of the test results after all tests have
 * been run. It provides an overview of the number of tests passed, failed, and
 * skipped.
 * 
 * @param engine The engine instance containing the test results.
 */
#define FOSSIL_SUMMARY(engine) \
    fossil_pizza_summary(&engine)

/** @brief Macro to end the test engine.
 * 
 * This macro is used to clean up and end the test engine after all tests have
 * been run. It should be called at the end of the test execution.
 * 
 * @param engine The engine instance to end.
 */
#define FOSSIL_END(engine) \
    fossil_pizza_end(&engine)

/**
 * @brief Macro to define a test group.
 * 
 * This macro is used to define a test group, which is a collection of test cases
 * that are related to each other. The test group can be executed as a whole to
 * verify the correctness of a group of functionalities.
 * 
 * @param name The name of the test group.
 */
#ifdef __cplusplus
#define FOSSIL_TEST_GROUP(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *_env)
#else
#define FOSSIL_TEST_GROUP(name) \
    void name##_test_group(fossil_pizza_engine_t *_env)
#endif

/**
 * @brief Macro to export a test group.
 * 
 * This macro is used to export a test group from a test file. The test group
 * will be available to other test files that import it.
 * 
 * @param name The name of the test group to export.
 */
#ifdef __cplusplus
#define FOSSIL_TEST_EXPORT(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *_env)
#else
#define FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(fossil_pizza_engine_t *_env)
#endif

/**
 * @brief Macro to import a test group.
 * 
 * This macro is used to import a test group into the test runner. The test group
 * will be executed when the test runner is run.
 * 
 * @param name The name of the test group to import.
 */
#ifdef __cplusplus
#define FOSSIL_TEST_IMPORT(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *_env)
#else
#define FOSSIL_TEST_IMPORT(name) \
    name##_test_group(&_env)
#endif



#endif
