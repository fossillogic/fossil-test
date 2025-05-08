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
#include "fossil/pizza/mock.h"
#include "fossil/pizza/common.h"

// *****************************************************************************
// Function declarations
// *****************************************************************************

void fossil_mock_init(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }
    list->head = null;
    list->tail = null;
    list->size = 0;
}

void fossil_mock_destroy(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }

    fossil_mock_call_t *current = list->head;
    while (current) {
        fossil_mock_call_t *next = current->next;
        pizza_sys_memory_free(current->function_name);
        for (int i = 0; i < current->num_args; ++i) {
            pizza_sys_memory_free(current->arguments[i]);
        }
        pizza_sys_memory_free(current->arguments);
        pizza_sys_memory_free(current);
        current = next;
    }
    list->head = null;
    list->tail = null;
    list->size = 0;
}

void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, char **arguments, int num_args) {
    if (!list || !function_name || !arguments) {
        return;
    }

    fossil_mock_call_t *call = (fossil_mock_call_t *)pizza_sys_memory_alloc(sizeof(fossil_mock_call_t));
    if (!call) {
        return;
    }

    call->function_name = pizza_io_cstr_dup(function_name);
    if (!call->function_name) {
        pizza_sys_memory_free(call);
        return;
    }

    call->arguments = (char **)malloc(num_args * sizeof(char *));
    if (!call->arguments) {
        pizza_sys_memory_free(call->function_name);
        pizza_sys_memory_free(call);
        return;
    }

    for (int i = 0; i < num_args; ++i) {
        call->arguments[i] = pizza_io_cstr_dup(arguments[i]);
        if (!call->arguments[i]) {
            for (int j = 0; j < i; ++j) {
                pizza_sys_memory_free(call->arguments[j]);
            }
            pizza_sys_memory_free(call->arguments);
            pizza_sys_memory_free(call->function_name);
            pizza_sys_memory_free(call);
            return;
        }
    }

    call->num_args = num_args;
    call->next = null;

    if (list->tail) {
        list->tail->next = call;
    } else {
        list->head = call;
    }
    list->tail = call;
    list->size++;
}

void fossil_mock_print(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }

    fossil_mock_call_t *current = list->head;
    while (current) {
        pizza_io_printf("Function: %s\n", current->function_name);
        pizza_io_printf("Arguments: ");
        for (int i = 0; i < current->num_args; ++i) {
            pizza_io_printf("%s", current->arguments[i]);
            if (i < current->num_args - 1) {
                pizza_io_printf(", ");
            }
        }
        pizza_io_printf("\n");
        current = current->next;
    }
}
