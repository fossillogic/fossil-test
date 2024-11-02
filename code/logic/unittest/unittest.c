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

// Color Helper Function
void fossil_test_print_color(const char *text, fossil_test_color_t color) {
    switch (color) {
        case FOSSIL_COLOR_GREEN:  printf("\033[0;32m%s\033[0m", text); break;
        case FOSSIL_COLOR_RED:    printf("\033[0;31m%s\033[0m", text); break;
        case FOSSIL_COLOR_YELLOW: printf("\033[0;33m%s\033[0m", text); break;
        case FOSSIL_COLOR_BLUE:   printf("\033[0;34m%s\033[0m", text); break;
        default:                  printf("%s", text); break;
    }
}

fossil_test_runner_t *fossil_test_create_runner() {
    fossil_test_runner_t *runner = (fossil_test_runner_t*)malloc(sizeof(fossil_test_runner_t));
    if (!runner) return NULL;
    runner->suite_head = NULL;
    runner->log_head = NULL;
    runner->pass_count = runner->fail_count = runner->skip_count = runner->unexpected_count = 0;
    return runner;
}

void fossil_test_add_case(fossil_test_suite_t *suite, const char *name, void (*test_func)(void)) {
    fossil_test_case_t *test_case = (fossil_test_case_t*)malloc(sizeof(fossil_test_case_t));
    test_case->name = name;
    test_case->test_func = test_func;
    test_case->result = FOSSIL_TEST_UNEXPECTED;
    test_case->next = suite->test_head;
    suite->test_head = test_case;
}

fossil_test_suite_t *fossil_test_create_suite(fossil_test_runner_t *runner, const char *name) {
    fossil_test_suite_t *suite = (fossil_test_suite_t*)malloc(sizeof(fossil_test_suite_t));
    suite->name = name;
    suite->test_head = NULL;
    suite->next = runner->suite_head;
    runner->suite_head = suite;
    return suite;
}

void fossil_test_log(fossil_test_runner_t *runner, const char *message, fossil_test_result_t result) {
    fossil_test_log_t *log = (fossil_test_log_t*)malloc(sizeof(fossil_test_log_t));
    log->message = message;
    log->result = result;
    log->prev = NULL;
    log->next = runner->log_head;
    if (runner->log_head) runner->log_head->prev = log;
    runner->log_head = log;
}

void fossil_test_run_suite(fossil_test_runner_t *runner, fossil_test_suite_t *suite) {
    fossil_test_case_t *current = suite->test_head;
    while (current) {
        printf("  Running test: %s\n", current->name);
        if (setjmp(runner->jump_env) == 0) {
            current->test_func();
            current->result = FOSSIL_TEST_PASS;
        } else {
            current->result = FOSSIL_TEST_FAIL;
        }
        current = current->next;
    }
}

void fossil_test_run(fossil_test_runner_t *runner) {
    fossil_test_suite_t *suite = runner->suite_head;
    while (suite) {
        printf("\nRunning suite: ");
        fossil_test_print_color(suite->name, FOSSIL_COLOR_BLUE);
        printf("\n");

        fossil_test_run_suite(runner, suite);
        suite = suite->next;
    }
}

void fossil_test_report(fossil_test_runner_t *runner) {
    printf("\nTest Summary:\n");
    fossil_test_print_color("Pass: ", FOSSIL_COLOR_GREEN); printf("%d\n", runner->pass_count);
    fossil_test_print_color("Fail: ", FOSSIL_COLOR_RED);   printf("%d\n", runner->fail_count);
    fossil_test_print_color("Skip: ", FOSSIL_COLOR_YELLOW); printf("%d\n", runner->skip_count);
    printf("Unexpected: %d\n", runner->unexpected_count);

    printf("\nDetailed Log:\n");
    fossil_test_log_t *log = runner->log_head;
    while (log) {
        switch (log->result) {
            case FOSSIL_TEST_PASS: fossil_test_print_color("[PASS] ", FOSSIL_COLOR_GREEN); break;
            case FOSSIL_TEST_FAIL: fossil_test_print_color("[FAIL] ", FOSSIL_COLOR_RED); break;
            case FOSSIL_TEST_SKIP: fossil_test_print_color("[SKIP] ", FOSSIL_COLOR_YELLOW); break;
            default: printf("[UNEXPECTED] "); break;
        }
        printf("%s\n", log->message);
        log = log->next;
    }
}

void fossil_test_free_runner(fossil_test_runner_t *runner) {
    fossil_test_suite_t *suite = runner->suite_head;
    while (suite) {
        fossil_test_case_t *test_case = suite->test_head;
        while (test_case) {
            fossil_test_case_t *temp = test_case;
            test_case = test_case->next;
            free(temp);
        }
        fossil_test_suite_t *temp_suite = suite;
        suite = suite->next;
        free(temp_suite);
    }
    fossil_test_log_t *log = runner->log_head;
    while (log) {
        fossil_test_log_t *temp = log;
        log = log->next;
        free(temp);
    }
    free(runner);
}
