/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/unittest/unittest.h"
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <time.h>

jmp_buf fossil_test_env;
fossil_test_stack_t fossil_test_stack; // Declare the stack for failure trace

static void (*setup_func)(void) = NULL;
static void (*teardown_func)(void) = NULL;

void fossil_test_queue_init(fossil_test_queue_t *queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;
}

void fossil_test_enqueue(fossil_test_queue_t *queue, fossil_test_case_t *test_case) {
    fossil_test_node_t *node = malloc(sizeof(fossil_test_node_t));
    node->test_case = test_case;
    node->next = NULL;
    node->prev = queue->tail;

    if (queue->tail) {
        queue->tail->next = node;
    }
    queue->tail = node;

    if (!queue->head) {
        queue->head = node;
    }
    queue->count++;
}

fossil_test_case_t *fossil_test_dequeue(fossil_test_queue_t *queue) {
    if (!queue->head) {
        return NULL;
    }

    fossil_test_node_t *node = queue->head;
    fossil_test_case_t *test_case = node->test_case;
    queue->head = node->next;

    if (queue->head) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;
    }

    free(node);
    queue->count--;
    return test_case;
}

void fossil_test_queue_free(fossil_test_queue_t *queue) {
    while (queue->head) {
        free(fossil_test_dequeue(queue));
    }
}

void fossil_test_stack_push(fossil_test_stack_t *stack, const char *trace) {
    if (stack->top < 255) {
        stack->stack[stack->top++] = trace;
    }
}

void fossil_test_stack_print(const fossil_test_stack_t *stack) {
    printf("Stack Trace:\n");
    for (int i = 0; i < stack->top; i++) {
        printf("  %s\n", stack->stack[i]);
    }
}

void fossil_test_catch(fossil_test_stack_t *stack, const char *error_msg) {
    printf(FOSSIL_TEST_COLOR_RED "Error: %s\n" FOSSIL_TEST_COLOR_RESET, error_msg);
    longjmp(fossil_test_env, 1);
}

void fossil_test_run(fossil_test_queue_t *queue, fossil_test_stack_t *stack, fossil_test_result_summary_t *summary, bool verbose) {
    fossil_test_case_t *test_case;
    while ((test_case = fossil_test_dequeue(queue))) {
        if (setup_func) setup_func(); // Call setup if defined

        clock_t start_time = clock();
        if (setjmp(fossil_test_env) == 0) {
            test_case->test_func();
            test_case->result = FOSSIL_TEST_PASS;
        } else {
            test_case->result = test_case->is_expected_fail ? FOSSIL_TEST_EXPECTED_FAIL : FOSSIL_TEST_FAIL;
        }
        clock_t end_time = clock();
        
        test_case->duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        if (verbose) {
            printf("%s: %s (%.2f seconds)\n", test_case->name,
                   test_case->result == FOSSIL_TEST_PASS ? FOSSIL_TEST_COLOR_GREEN "PASS" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_FAIL ? FOSSIL_TEST_COLOR_RED "FAIL" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_SKIP ? FOSSIL_TEST_COLOR_YELLOW "SKIP" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_EXPECTED_FAIL ? FOSSIL_TEST_COLOR_BLUE "EXPECTED FAIL" FOSSIL_TEST_COLOR_RESET :
                   FOSSIL_TEST_COLOR_YELLOW "IGNORED" FOSSIL_TEST_COLOR_RESET,
                   test_case->duration);
        }

        switch (test_case->result) {
            case FOSSIL_TEST_PASS: summary->passed++; break;
            case FOSSIL_TEST_FAIL: summary->failed++; break;
            case FOSSIL_TEST_SKIP: summary->skipped++; break;
            case FOSSIL_TEST_UNEXPECTED: summary->unexpected++; break;
            case FOSSIL_TEST_EXPECTED_FAIL: summary->expected_failed++; break;
            case FOSSIL_TEST_IGNORED: summary->ignored++; break;
        }

        if (teardown_func) teardown_func(); // Call teardown if defined
        free(test_case); // Free allocated test case
    }
}

void fossil_test_summary(const fossil_test_result_summary_t *summary) {
    printf("Test Summary:\n");
    printf("  Passed: %zu\n", summary->passed);
    printf("  Failed: %zu\n", summary->failed);
    printf("  Skipped: %zu\n", summary->skipped);
    printf("  Unexpected: %zu\n", summary->unexpected);
    printf("  Expected Failures: %zu\n", summary->expected_failed);
    printf("  Ignored: %zu\n", summary->ignored);
}

void fossil_test_add_suite(fossil_test_suite_t *suite, fossil_test_case_t *test_case) {
    suite->tests = realloc(suite->tests, sizeof(fossil_test_case_t *) * (suite->test_count + 1));
    suite->tests[suite->test_count++] = test_case;
}

void fossil_test_run_suite(fossil_test_suite_t *suite, fossil_test_stack_t *stack, fossil_test_result_summary_t *summary, bool verbose) {
    for (size_t i = 0; i < suite->test_count; i++) {
        fossil_test_case_t *test_case = suite->tests[i];
        if (setup_func) setup_func(); // Call setup if defined

        clock_t start_time = clock();
        if (setjmp(fossil_test_env) == 0) {
            test_case->test_func();
            test_case->result = FOSSIL_TEST_PASS;
        } else {
            test_case->result = test_case->is_expected_fail ? FOSSIL_TEST_EXPECTED_FAIL : FOSSIL_TEST_FAIL;
        }
        clock_t end_time = clock();
        
        test_case->duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        if (verbose) {
            printf("%s: %s (%.2f seconds)\n", test_case->name,
                   test_case->result == FOSSIL_TEST_PASS ? FOSSIL_TEST_COLOR_GREEN "PASS" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_FAIL ? FOSSIL_TEST_COLOR_RED "FAIL" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_SKIP ? FOSSIL_TEST_COLOR_YELLOW "SKIP" FOSSIL_TEST_COLOR_RESET :
                   test_case->result == FOSSIL_TEST_EXPECTED_FAIL ? FOSSIL_TEST_COLOR_BLUE "EXPECTED FAIL" FOSSIL_TEST_COLOR_RESET :
                   FOSSIL_TEST_COLOR_YELLOW "IGNORED" FOSSIL_TEST_COLOR_RESET,
                   test_case->duration);
        }

        switch (test_case->result) {
            case FOSSIL_TEST_PASS: summary->passed++; break;
            case FOSSIL_TEST_FAIL: summary->failed++; break;
            case FOSSIL_TEST_SKIP: summary->skipped++; break;
            case FOSSIL_TEST_UNEXPECTED: summary->unexpected++; break;
            case FOSSIL_TEST_EXPECTED_FAIL: summary->expected_failed++; break;
            case FOSSIL_TEST_IGNORED: summary->ignored++; break;
        }

        if (teardown_func) teardown_func(); // Call teardown if defined
    }
}

void fossil_test_setup(void (*setup_func_param)(void)) {
    setup_func = setup_func_param;
}

void fossil_test_teardown(void (*teardown_func_param)(void)) {
    teardown_func = teardown_func_param;
}
