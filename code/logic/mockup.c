/*
 * -----------------------------------------------------------------------------
 * File: framework.hpp
 * Project: Fossil Logic
 * Description: This file implments the framework for mockup testing.
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
#include "fossil/test/mockup.h"

void fossil_mock_init(MockCallList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_destroy(MockCallList *list) {
    MockCall *current = list->head;
    while (current) {
        MockCall *next = current->next;
        free(current->function_name);
        for (int i = 0; i < current->num_args; ++i) {
            free(current->arguments[i]);
        }
        free(current->arguments);
        free(current);
        current = next;
    }
}

void fossil_mock_add_call(MockCallList *list, const char *function_name, char **arguments, int num_args) {
    MockCall *call = (MockCall *)malloc(sizeof(MockCall));
    call->function_name = _custom_fossil_test_strdup(function_name);
    call->arguments = (char **)malloc(num_args * sizeof(char *));
    for (int i = 0; i < num_args; ++i) {
        call->arguments[i] = _custom_fossil_test_strdup(arguments[i]);
    }
    call->num_args = num_args;
    call->next = NULL;

    if (list->tail) {
        list->tail->next = call;
    } else {
        list->head = call;
    }
    list->tail = call;
    list->size++;
}

void fossil_mock_print(MockCallList *list) {
    MockCall *current = list->head;
    while (current) {
        printf("Function: %s\n", current->function_name);
        printf("Arguments: ");
        for (int i = 0; i < current->num_args; ++i) {
            printf("%s", current->arguments[i]);
            if (i < current->num_args - 1) {
                printf(", ");
            }
        }
        printf("\n");
        current = current->next;
    }
}
