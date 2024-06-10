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
#ifndef FOSSIL_TEST_FEATURES_H
#define FOSSIL_TEST_FEATURES_H

/**
 * @brief Comprehensive overview of Fossil Test features.
 * 
 * Fossil Test is a robust testing framework designed to facilitate the testing process
 * by providing a variety of tools and mechanisms to define, categorize, prioritize, and 
 * mark test cases. The framework offers several key features to help ensure tests are
 * thorough, well-organized, and meaningful. Below is a detailed description of the major
 * components and features provided by Fossil Test:
 * 
 * 1. **Assertion Rules**:
 *    - `TEST_ASSERT_AS_CLASS_ASSERT`: Standard assertions used to enforce conditions that must be true.
 *    - `TEST_ASSERT_AS_CLASS_EXPECT`: Expectations used to define conditions that are anticipated but not mandatory.
 *    - `TEST_ASSERT_AS_CLASS_ASSUME`: Assumptions that must hold true for the test to proceed; otherwise, the test is skipped.
 *    - `TEST_ASSERT_AS_CLASS_EXCEPT`: Exception handling rules for conditions expected to raise exceptions.
 *    - `TEST_ASSERT_AS_CLASS_SANITY`: Basic sanity checks to ensure the test environment is stable before proceeding.
 * 
 * 2. **Tag Rules**:
 *    - `TEST_ASSERT_TAG_RULE_FAST`: Tags for tests expected to run quickly.
 *    - `TEST_ASSERT_TAG_RULE_SLOW`: Tags for tests anticipated to take longer to execute.
 *    - `TEST_ASSERT_TAG_RULE_DEFAULT`: Default tag for tests without a specific speed category.
 *    - `TEST_ASSERT_TAG_RULE_BUG`: Tags for tests expected to fail, often used to track known issues.
 *    - `TEST_ASSERT_TAG_RULE_FEATURE`: Tags for tests expected to pass, usually validating intended features.
 *    - `TEST_ASSERT_TAG_RULE_SECURITY`: Tags for tests aimed at validating security aspects.
 *    - `TEST_ASSERT_TAG_RULE_PERFORMANCE`: Tags for performance testing to measure efficiency and speed.
 *    - `TEST_ASSERT_TAG_RULE_STRESS`: Tags for stress testing to evaluate the system under extreme conditions.
 *    - `TEST_ASSERT_TAG_RULE_REGRESSION`: Tags for regression testing to ensure new changes do not break existing functionality.
 *    - `TEST_ASSERT_TAG_RULE_COMPATIBILITY`: Tags for tests verifying compatibility across different environments or versions.
 *    - `TEST_ASSERT_TAG_RULE_USABILITY`: Tags for tests focusing on the usability aspects of the software.
 *    - `TEST_ASSERT_TAG_RULE_ROBUSTNESS`: Tags for tests ensuring the system can handle invalid inputs or unexpected situations gracefully.
 *    - `TEST_ASSERT_TAG_RULE_CORNER_CASE`: Tags for tests that cover rare or unusual scenarios that might not be covered by regular tests.
 * 
 * 3. **Priority Rules**:
 *    - `TEST_ASSERT_PRIORITY_RULE_LOW`: Priority for tests of low importance.
 *    - `TEST_ASSERT_PRIORITY_RULE_NORMAL`: Priority for tests of normal, average importance.
 *    - `TEST_ASSERT_PRIORITY_RULE_HIGH`: Priority for tests of high importance, often critical to functionality.
 *    - `TEST_ASSERT_PRIORITY_RULE_CRITICAL`: Highest priority, for tests critical to the application's success and stability.
 * 
 * 4. **Mark Rules**:
 *    - `TEST_ASSERT_MARK_RULE_SKIP`: Marks tests that should be skipped.
 *    - `TEST_ASSERT_MARK_RULE_FAIL`: Marks tests that are expected to fail.
 *    - `TEST_ASSERT_MARK_RULE_PASS`: Marks tests that are expected to pass successfully.
 *    - `TEST_ASSERT_MARK_RULE_DEFAULT`: Default mark for tests with no specific expected outcome.
 *    - `TEST_ASSERT_MARK_RULE_TIMEOUT`: Marks tests that are expected to timeout if they exceed a certain duration.
 *    - `TEST_ASSERT_MARK_RULE_ERROR`: Marks tests that are expected to throw an error.
 *    - `TEST_ASSERT_MARK_RULE_NONE`: Marks tests with no specific expected outcome.
 *    - `TEST_ASSERT_MARK_RULE_ONLY`: Marks tests that should be the only ones executed, useful for isolating specific tests.
 * 
 * Together, these features enable comprehensive test management, allowing developers to 
 * create detailed and precise test cases, categorize them efficiently, prioritize their 
 * execution, and define expected outcomes. This results in a highly organized and 
 * effective testing process, enhancing software quality and reliability.
 */

#include "fossil/_common/common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void _fossil_test_apply_mark(fossil_test_t *test, const char *mark);
void _fossil_test_apply_xtag(fossil_test_t *test, const char *xtag);
void _fossil_test_apply_priority(fossil_test_t *test, const char *priority);

#ifdef __cplusplus
}
#endif

#endif
