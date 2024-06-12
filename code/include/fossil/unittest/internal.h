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
#ifndef FOSSIL_TEST_INTERNAL_H
#define FOSSIL_TEST_INTERNAL_H

#include "fossil/_common/common.h"
#include "fossil/_common/platform.h"

/**
 * Introspection Data in Fossil Test
 *
 * Introspection, in the context of Fossil Test, refers to the process of gathering
 * detailed information about the testing environment. This information is crucial
 * for ensuring test stability, reliability, and portability across different
 * platforms and environments. Fossil Test relies heavily on introspection data to
 * adapt its behavior dynamically based on the characteristics of the system where
 * it runs.
 *
 * The importance of introspection data can be summarized as follows:
 *
 * 1. System Compatibility:
 *    Introspection data allows Fossil Test to identify the underlying architecture,
 *    operating system, CPU count, endianness, and memory size of the test environment.
 *    This information is vital for ensuring that tests execute correctly on diverse
 *    platforms, including ARM, Windows, macOS, and various POSIX-based systems.
 *
 * 2. Test Adaptation:
 *    By analyzing introspection data, Fossil Test can adapt its behavior and configuration
 *    to suit the characteristics of the current environment. For example, the console
 *    output may be adjusted based on the console width and height, and color support
 *    may be enabled or disabled depending on the capabilities of the terminal.
 *
 * 3. Performance Optimization:
 *    Introspection data helps Fossil Test optimize test execution performance by providing
 *    insights into system resources such as CPU count and memory size. This information
 *    allows Fossil Test to allocate resources efficiently and prioritize test execution
 *    based on available hardware resources.
 *
 * 4. Cross-Platform Testing:
 *    With introspection data, Fossil Test can facilitate cross-platform testing by
 *    identifying and handling platform-specific differences transparently. Whether
 *    running on Windows, macOS, Linux, or other operating systems, Fossil Test can
 *    leverage introspection data to ensure consistent test behavior and results.
 *
 * In conclusion, introspection data forms the foundation of Fossil Test's ability
 * to operate effectively in diverse testing environments. By gathering and analyzing
 * detailed information about the test environment, Fossil Test enhances compatibility,
 * adaptability, performance, and cross-platform testing capabilities, thereby
 * empowering developers to write robust and portable test suites.
 */

// Define thread pool size
enum {
    FOSSIL_TEST_MAX_FILTER_LENGTH = 50,
    FOSSIL_TEST_ASSUME_MAX  = 5,
    FOSSIL_TEST_EXCEPT_MAX  = 5,
    FOSSIL_TEST_MAX_REPEATS = 100,
    FOSSIL_TEST_MIN_REPEATS = 1,
    FOSSIL_TEST_MAX_PRIORITY = 100,
    FOSSIL_TEST_MIN_PRIORITY = 1,
    MAX_EXPECTED_TIME_FAST = 1000, // Example value: 1000 milliseconds (1 second)
    MAX_EXPECTED_TIME_SLOW = 2000, // 2000 milliseconds (2 seconds)
    FOSSIL_TESTAULT_PRIORITY_THRESHOLD = 50,
    FOSSIL_TEST_ABORT_FAIL = -1,
};

typedef enum {
    FOSSIL_TEST_IO_AS_HUMAN,
    FOSSIL_TEST_IO_AS_CUTBACK,
    FOSSIL_TEST_IO_AS_TURBO
} fossil_test_mode;

/**
 * @brief Enumeration representing different types of assertion rules.
 * 
 * This enum defines various types of assertion rules that can be applied to test cases.
 * Each value represents a specific type of assertion behavior.
 */
typedef enum {
    TEST_ASSERT_AS_CLASS_ASSERT, /**< Standard assert, used to enforce conditions that must be true. */
    TEST_ASSERT_AS_CLASS_EXPECT, /**< Expectation, used to define conditions that are expected but not mandatory. */
    TEST_ASSERT_AS_CLASS_ASSUME, /**< Assumption, used to specify assumptions that must hold true for the test to proceed. */
    TEST_ASSERT_AS_CLASS_EXCEPT, /**< Exception, used to handle conditions that are expected to raise exceptions. */
    TEST_ASSERT_AS_CLASS_SANITY  /**< Sanity check, used for basic checks to ensure the test environment is stable. */
} xassert_type_t;

/**
 * @brief Enumeration representing different priority rules for test assertions.
 * 
 * This enum defines various priority rules for test assertions, indicating the importance
 * or urgency of the tests. Tests with higher priority values are considered more critical.
 */
typedef enum {
    TEST_ASSERT_PRIORITY_RULE_LOW,    /**< Priority for tests with low importance. */
    TEST_ASSERT_PRIORITY_RULE_NORMAL, /**< Priority for tests with normal importance. */
    TEST_ASSERT_PRIORITY_RULE_HIGH,   /**< Priority for tests with high importance. */
    TEST_ASSERT_PRIORITY_RULE_CRITICAL /**< Priority for tests with critical importance. */
} xassert_priority_t;

/**
 * @brief Enumeration representing different mark rules for test assertions.
 * 
 * This enum defines various marking rules for test assertions, indicating the expected
 * outcome or behavior of the tests.
 */
typedef enum {
    TEST_ASSERT_MARK_RULE_SKIP,    /**< Mark for tests that should be skipped. */
    TEST_ASSERT_MARK_RULE_DEFAULT, /**< Default mark for tests with no specific expected outcome. */
    TEST_ASSERT_MARK_RULE_TIMEOUT, /**< Mark for tests that are expected to timeout. */
    TEST_ASSERT_MARK_RULE_ERROR,   /**< Mark for tests that are expected to throw an error. */
    TEST_ASSERT_MARK_RULE_NONE,    /**< Mark for tests with no specific expected outcome. */
    TEST_ASSERT_MARK_RULE_ONLY     /**< Mark for tests that are the only ones to be run. */
} xassert_mark_t;

/**
 * Structure representing rules or attributes of a test case.
 * This structure is used to track various states or characteristics of a test case,
 * such as whether it passed, was skipped, or was categorized as fast or slow.
 */
typedef struct {
    bool should_pass;    /**< Boolean indicating whether the test case passed. */
    bool skipped;  /**< Boolean indicating whether the test case was skipped. */
    bool timeout;  /**< Boolean indicating whether the test case timed out. */
    bool error;    /**< Boolean indicating whether the test case threw an error. */
} fossil_test_rule_t;

/**
 * @brief Structure to hold timing information for tests.
 * 
 * This structure stores the timing information for tests, including the start time,
 * end time, elapsed time, and detailed timing information in different units.
 * It is used to track the duration of test executions to provide performance metrics.
 */
typedef struct {
    clock_t start;   /**< Processor time at the start of tests. */
    clock_t end;     /**< Processor time at the end of tests. */
    clock_t elapsed; /**< Elapsed processor time for the tests. */
    struct {
        int64_t minutes;      /**< Elapsed time in minutes. */
        int64_t seconds;      /**< Elapsed time in seconds. */
        int64_t milliseconds; /**< Elapsed time in milliseconds. */
        int64_t microseconds; /**< Elapsed time in microseconds. */
        int64_t nanoseconds;  /**< Elapsed time in nanoseconds. */
    } detail; /**< Detailed timing information, providing a breakdown of elapsed time in various units. */
} fossil_test_timer_t;

/**
 * Structure representing fixture information with setup and teardown functions.
 * A fixture is used to set up any necessary environment or state before running a test
 * and to clean up afterward. This is useful for initializing resources or configurations
 * that multiple test cases share.
 */
typedef struct {
    void (*setup)(void);     /**< Function pointer to the setup function for the fixture. 
                                  This function is called before each test case to set up 
                                  the test environment. */
    void (*teardown)(void);  /**< Function pointer to the teardown function for the fixture. 
                                  This function is called after each test case to clean up 
                                  the test environment. */
} fossil_fixture_t;

/**
 * Structure representing a test case.
 * This structure contains all the necessary information for a test case, including its name,
 * the function implementing the test, priority, tags, and links to setup and teardown functions.
 */
typedef struct fossil_test_t fossil_test_t;
typedef struct fossil_test_t {
    const char* name;            /**< Name of the test case. */
    void (*test_function)(void); /**< Function pointer to the test case's implementation. */
    char* tags;                  /**< Array of tags associated with the test case. */
    char* marks;                 /**< Array of marks associated with the test case. */
    fossil_test_timer_t timer;   /**< Timer for tracking the duration of the test case. */
    fossil_fixture_t fixture;    /**< The fixture settings for setup and teardown functions. */
    int32_t priority;            /**< Priority of the test case (higher value indicates higher priority). */
    struct fossil_test_t *prev;  /**< Pointer to the previous fossil_test_t node in a linked list. */
    struct fossil_test_t *next;  /**< Pointer to the next fossil_test_t node in a linked list. */
} fossil_test_t;

/**
 * Structure representing a deque (double-ended queue) for managing test cases.
 * This structure allows for the addition and removal of test cases from both ends of the queue.
 */
typedef struct {
    fossil_test_t *front;   /**< Pointer to the front of the deque. */
    fossil_test_t *rear;    /**< Pointer to the rear of the deque. */
} fossil_test_queue_t;

/**
 * Structure representing statistics for tracking test results.
 * This structure keeps track of various counts related to the outcomes of test cases,
 * including passed, failed, skipped, and timed-out tests.
 */
typedef struct {
    uint16_t expected_passed_count;   /**< Number of expected passed tests. */
    uint16_t expected_failed_count;   /**< Number of expected failed tests. */
    uint16_t unexpected_passed_count; /**< Number of unexpected passed tests. */
    uint16_t unexpected_failed_count; /**< Number of unexpected failed tests. */
    uint16_t expected_skipped_count;  /**< Number of skipped tests. */
    uint16_t expected_empty_count;    /**< Number of empty tests. */
    uint16_t expected_timeout_count;  /**< Number of tests that timed out. */
    uint16_t expected_total_count;    /**< Total number of unit tests that were run. */
    uint16_t untested_count;          /**< Total number of untested cases when exit or abort is called 
                                           from an assert. */
} fossil_test_score_t;

/**
 * Structure representing information about an assertion.
 * This structure contains detailed information about an assertion, including the name of the test case,
 * the message associated with the assertion, the file name, line number, function name, timestamp, assertion type,
 * execution time, test case identifier, severity level, custom data, stack trace, and result of the test case.
 */
typedef struct {
    bool shoudl_timeout;   /**< Flag indicating whether the test case should timeout (1 for true, 0 for false). */
    bool should_fail;      /**< Flag indicating whether the test case should fail (1 for true, 0 for false). */
    bool has_assert;       /**< Flag indicating if an assertion occurred (1 for true, 0 for false). */
    int32_t line;          /**< Line number where the assertion occurred. */
    char *func;            /**< Function name where the assertion occurred. */
    char *file;            /**< File name where the assertion occurred. */
    char *message;         /**< Message associated with the assertion. */
} xassert_info;

/**
 * Structure representing the test environment, holding overall test statistics and timing information.
 * This structure is used to manage the state of the testing process, including the queue of test cases
 * and the timer for tracking the duration of the tests.
 */
typedef struct {
    fossil_test_score_t stats;                 /**< Test statistics, including counts of passed, failed, and skipped tests. */
    fossil_test_timer_t timer;                  /**< Timer for tracking the time taken to run the tests. */
    fossil_test_queue_t* queue;                /**< Queue to hold the test cases, allowing them to be managed and executed in order. */
    fossil_test_rule_t rule;                   /**< Rule for the test case, including whether it should pass, fail, or be skipped. */
    uint8_t current_except_count; /**< Counter for the number of exceptions that occurred during testing. */
    uint8_t current_assume_count; /**< Counter for the number of assumptions that occurred during testing. */
} fossil_env_t;

#ifdef __cplusplus
extern "C"
{
#endif

extern fossil_env_t _TEST_ENV;
extern xassert_info _ASSERT_INFO;

// =================================================================
// Initial implementation
// =================================================================

// Function prototypes
fossil_env_t fossil_test_environment_create(int argc, char **argv);
void fossil_test_environment_run(fossil_env_t *env);
void fossil_test_environment_add(fossil_env_t *env, fossil_test_t *test, fossil_fixture_t *fixture);
int  fossil_test_environment_summary(void);

void fossil_test_apply_mark(fossil_test_t *test, const char *mark);
void fossil_test_apply_xtag(fossil_test_t *test, const char *tag);
void fossil_test_apply_priority(fossil_test_t *test, const char *priority);

/**
 * @brief Internal function for handling test assertions.
 * 
 * @param expression The expression to evaluate.
 * @param behavior The behavior of the assertion (e.g., ASSERT, EXPECT, ASSUME).
 * @param message The message associated with the assertion.
 * @param file The file name where the assertion occurred.
 * @param line The line number where the assertion occurred.
 * @param func The function name where the assertion occurred.
 */
void _fossil_test_assert_class(bool expression, xassert_type_t behavior, char* message, char* file, int line, char* func);


/**
 * @brief Macro to apply a priority to a test case.
 * 
 * This macro is used to apply a priority to a test case. It is used in conjunction
 * with the _APPLY_PRIORITY macro to define the priority to be applied.
 * 
 * @param test_case The test case to which the priority is to be applied.
 * @param priority The priority to be applied.
 */
#define _APPLY_PRIORITY(test_case, priority) fossil_test_apply_priority(test_case, (char*)priority)

/**
 * @brief Macro to apply a tag to a test case.
 * 
 * This macro is used to apply a tag to a test case. It is used in conjunction
 * with the _APPLY_XTAG macro to define the tag to be applied.
 * 
 * @param test_case The test case to which the tag is to be applied.
 * @param xtag The tag to be applied.
 */
#define _APPLY_XTAG(test_case, xtag) fossil_test_apply_xtag(&test_case, (char*)xtag)

/**
 * @brief Macro to apply a mark to a test case.
 * 
 * This macro is used to apply a mark to a test case. It is used in conjunction
 * with the _APPLY_MARK macro to define the mark to be applied.
 * 
 * @param test_case The test case to which the mark is to be applied.
 * @param mark The mark to be applied.
 */
#define _APPLY_MARK(test_case, mark) fossil_test_apply_mark(&test_case, (char*)mark)

/**
 * @brief Macro to add a test case.
 * 
 * This macro is used to add a test case. It is used in conjunction with the
 * _ADD_TEST macro to define the test case function.
 * 
 * @param test_case The test case to be added.
 */
#define _ADD_TEST(test_case) fossil_test_environment_add(test_env, &test_case, xnullptr)

/**
 * @brief Macro to add a test case with a fixture.
 * 
 * This macro is used to add a test case with a fixture. It is used in conjunction
 * with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param test_case The test case to be added.
 * @param fixture The fixture to be added.
 */
#define _ADD_TESTF(test_case, fixture) fossil_test_environment_add(test_env, &test_case, &fixture)

/**
 * @brief Macro to define a fixture.
 * 
 * This macro is used to define a fixture. It is used in conjunction with the
 * _FOSSIL_SETUP and _FOSSIL_TEARDOWN macros to define the setup and teardown functions for
 * the fixture.
 * 
 * @param fixture_name The name of the fixture.
 * @param setup The setup function for the fixture.
 * @param teardown The teardown function for the fixture.
 */
#define _FOSSIL_FIXTURE(fixture_name) \
    void setup_##fixture_name(void); \
    void teardown_##fixture_name(void); \
    fossil_fixture_t fixture_name = { setup_##fixture_name, teardown_##fixture_name }

/**
 * @brief Macro to define a setup function for a fixture.
 * 
 * This macro is used to define a setup function for a fixture. It is used in
 * conjunction with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param fixture_name The name of the fixture.
 */
#define _FOSSIL_SETUP(fixture_name) void setup_##fixture_name(void)

/**
 * @brief Macro to define a teardown function for a fixture.
 * 
 * This macro is used to define a teardown function for a fixture. It is used in
 * conjunction with the _FOSSIL_FIXTURE macro to define the fixture structure.
 * 
 * @param fixture_name The name of the fixture.
 */
#define _FOSSIL_TEARDOWN(fixture_name) void teardown_##fixture_name(void)

/**
 * @brief Macro to define a test case.
 * 
 * This macro is used to define a test case. It is used in conjunction with the
 * _FOSSIL_TEST macro to define the test case function.
 * 
 * @param name The name of the test case.
 */
#define _FOSSIL_TEST(name)          \
    void name##_fossil_test(void);  \
    fossil_test_t name = {          \
        (char*)#name,               \
        name##_fossil_test,         \
        (char*)"fossil",            \
        (char*)"fossil",            \
        {0, 0, 0, {0, 0, 0, 0, 0}}, \
        {xnull, xnull},             \
        0,                          \
        xnull,                      \
        xnull                       \
    };                              \
    void name##_fossil_test(void)

/**
 * @brief Macro to define a test case with a priority.
 * 
 * This macro is used to define a test case with a priority. It is used in conjunction
 * with the _FOSSIL_TEST macro to define the test case function.
 * 
 * @param name The name of the test case.
 * @param priority The priority of the test case.
 */
#define _FOSSIL_TEST_ERASE() fossil_test_environment_summary()

/** Macro to create the test environment.
 * 
 * This macro is used to create the test environment by calling the _fossil_test_environment_create function.
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 */
#define _FOSSIL_TEST_CREATE(argc, argv) _TEST_ENV = fossil_test_environment_create(argc, argv)

/** Macro to run the test environment.
 * 
 * This macro is used to run the test environment by calling the fossil_test_environment_run function.
 */
#define _FOSSIL_TEST_RUN() fossil_test_environment_run(&_TEST_ENV)

/**
 * @brief Define macro for defining a test queue.
 * 
 * This macro is used to define a test queue function for a specific test group.
 * It creates a function definition with the given group name and accepts a pointer
 * to a TestRegistry structure as a parameter. This function typically registers
 * all tests within the specified test group to the provided test registry.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_GROUP(group_name) void group_name(fossil_env_t* test_env)

/**
 * @brief Define macro for declaring an external test queue.
 * 
 * This macro is used to declare an external test queue function for a specific
 * test group. It creates an external function declaration with the given group name
 * and accepts a pointer to a TestRegistry structure as a parameter. This declaration
 * allows the test queue function to be defined in a separate source file and linked
 * with the test framework.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_EXPORT(group_name) extern void group_name(fossil_env_t* test_env)

/**
 * @brief Define macro for importing and executing a test queue.
 * 
 * This macro is used to import and execute a test queue function for a specific
 * test group. It calls the test queue function with the provided TestRegistry
 * structure, typically registering all tests within the specified test group
 * to the test registry.
 * 
 * @param group_name The name of the test group.
 */
#define _FOSSIL_TEST_IMPORT(group_name) group_name(&_TEST_ENV)


#ifdef __cplusplus
}
#endif

#endif
