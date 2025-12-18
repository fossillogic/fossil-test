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
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/pizza/mock.h"

// *****************************************************************************
// Function declarations
// *****************************************************************************

void fossil_mock_init(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->global_ai_context = NULL;
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
            pizza_sys_memory_free(current->arguments[i].value.data);
            pizza_sys_memory_free(current->arguments[i].attribute.name);
            pizza_sys_memory_free(current->arguments[i].attribute.description);
            pizza_sys_memory_free(current->arguments[i].attribute.id);
        }
        pizza_sys_memory_free(current->arguments);

        if (current->ai_context) {
            pizza_sys_memory_free(current->ai_context->context_info);
            pizza_sys_memory_free(current->ai_context->expected_behavior);
            pizza_sys_memory_free(current->ai_context->ai_notes);
            pizza_sys_memory_free(current->ai_context);
        }

        pizza_sys_memory_free(current);
        current = next;
    }

    if (list->global_ai_context) {
        pizza_sys_memory_free(list->global_ai_context->context_info);
        pizza_sys_memory_free(list->global_ai_context->expected_behavior);
        pizza_sys_memory_free(list->global_ai_context->ai_notes);
        pizza_sys_memory_free(list->global_ai_context);
        list->global_ai_context = NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, fossil_mock_pizza_t *arguments, int num_args) {
    if (!list || !function_name || (num_args > 0 && !arguments)) {
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

    if (num_args > 0) {
        call->arguments = (fossil_mock_pizza_t *)pizza_sys_memory_alloc(num_args * sizeof(fossil_mock_pizza_t));
        if (!call->arguments) {
            pizza_sys_memory_free(call->function_name);
            pizza_sys_memory_free(call);
            return;
        }

        for (int i = 0; i < num_args; ++i) {
            call->arguments[i].type = arguments[i].type;
            call->arguments[i].value.data = arguments[i].value.data ? pizza_io_cstr_dup(arguments[i].value.data) : NULL;
            call->arguments[i].value.mutable_flag = arguments[i].value.mutable_flag;
            call->arguments[i].attribute.name = arguments[i].attribute.name ? pizza_io_cstr_dup(arguments[i].attribute.name) : NULL;
            call->arguments[i].attribute.description = arguments[i].attribute.description ? pizza_io_cstr_dup(arguments[i].attribute.description) : NULL;
            call->arguments[i].attribute.id = arguments[i].attribute.id ? pizza_io_cstr_dup(arguments[i].attribute.id) : NULL;

            // AI trick: If argument type is string and value is NULL, auto-fill with "AI_NULL"
            if ((call->arguments[i].type == FOSSIL_MOCK_PIZZA_TYPE_CSTR ||
                 call->arguments[i].type == FOSSIL_MOCK_PIZZA_TYPE_WSTR) &&
                !call->arguments[i].value.data) {
                call->arguments[i].value.data = pizza_io_cstr_dup("AI_NULL");
            }

            if ((arguments[i].value.data && !call->arguments[i].value.data) ||
                (arguments[i].attribute.name && !call->arguments[i].attribute.name) ||
                (arguments[i].attribute.description && !call->arguments[i].attribute.description) ||
                (arguments[i].attribute.id && !call->arguments[i].attribute.id)) {
                for (int j = 0; j <= i; ++j) {
                    pizza_sys_memory_free(call->arguments[j].value.data);
                    pizza_sys_memory_free(call->arguments[j].attribute.name);
                    pizza_sys_memory_free(call->arguments[j].attribute.description);
                    pizza_sys_memory_free(call->arguments[j].attribute.id);
                }
                pizza_sys_memory_free(call->arguments);
                pizza_sys_memory_free(call->function_name);
                pizza_sys_memory_free(call);
                return;
            }
        }
    } else {
        call->arguments = NULL;
    }

    call->num_args = num_args;
    call->ai_context = NULL;

    // AI trick: If global_ai_context exists, auto-attach to call if not set
    if (list->global_ai_context) {
        call->ai_context = (fossil_mock_ai_context_t *)pizza_sys_memory_alloc(sizeof(fossil_mock_ai_context_t));
        if (call->ai_context) {
            call->ai_context->context_info = list->global_ai_context->context_info ? pizza_io_cstr_dup(list->global_ai_context->context_info) : NULL;
            call->ai_context->expected_behavior = list->global_ai_context->expected_behavior ? pizza_io_cstr_dup(list->global_ai_context->expected_behavior) : NULL;
            call->ai_context->ai_notes = list->global_ai_context->ai_notes ? pizza_io_cstr_dup(list->global_ai_context->ai_notes) : NULL;
        }
    }

    call->next = NULL;

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
    int call_index = 0;
    while (current) {
        pizza_io_printf("{cyan,bold}[%d] Function:{normal} {yellow}%s{reset}\n", call_index, current->function_name);

        // If AI context is present, print AI context info
        if (current->ai_context) {
            pizza_io_printf("  {green}AI Context:{reset}\n");
            pizza_io_printf("    {blue}Info:{reset} %s\n", current->ai_context->context_info ? current->ai_context->context_info : "NULL");
            pizza_io_printf("    {blue}Expected:{reset} %s\n", current->ai_context->expected_behavior ? current->ai_context->expected_behavior : "NULL");
            pizza_io_printf("    {blue}Notes:{reset} %s\n", current->ai_context->ai_notes ? current->ai_context->ai_notes : "NULL");
        } else if (list->global_ai_context) {
            pizza_io_printf("  {green}Global AI Context:{reset}\n");
            pizza_io_printf("    {blue}Info:{reset} %s\n", list->global_ai_context->context_info ? list->global_ai_context->context_info : "NULL");
            pizza_io_printf("    {blue}Expected:{reset} %s\n", list->global_ai_context->expected_behavior ? list->global_ai_context->expected_behavior : "NULL");
            pizza_io_printf("    {blue}Notes:{reset} %s\n", list->global_ai_context->ai_notes ? list->global_ai_context->ai_notes : "NULL");
        }

        pizza_io_printf("{magenta}Arguments:{reset}\n");
        for (int i = 0; i < current->num_args; ++i) {
            pizza_io_printf("  {blue}Type:{reset} %d\n", current->arguments[i].type);

            // Print value based on type
            switch (current->arguments[i].type) {
                case FOSSIL_MOCK_PIZZA_TYPE_I8:
                case FOSSIL_MOCK_PIZZA_TYPE_I16:
                case FOSSIL_MOCK_PIZZA_TYPE_I32:
                case FOSSIL_MOCK_PIZZA_TYPE_I64:
                case FOSSIL_MOCK_PIZZA_TYPE_U8:
                case FOSSIL_MOCK_PIZZA_TYPE_U16:
                case FOSSIL_MOCK_PIZZA_TYPE_U32:
                case FOSSIL_MOCK_PIZZA_TYPE_U64:
                case FOSSIL_MOCK_PIZZA_TYPE_HEX:
                case FOSSIL_MOCK_PIZZA_TYPE_OCTAL:
                case FOSSIL_MOCK_PIZZA_TYPE_SIZE:
                    pizza_io_printf("  {blue}Value:{reset} %s\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
                case FOSSIL_MOCK_PIZZA_TYPE_FLOAT:
                case FOSSIL_MOCK_PIZZA_TYPE_DOUBLE:
                    pizza_io_printf("  {blue}Value:{reset} %s\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
                case FOSSIL_MOCK_PIZZA_TYPE_WSTR:
                case FOSSIL_MOCK_PIZZA_TYPE_CSTR:
                    pizza_io_printf("  {blue}Value:{reset} \"%s\"\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
                case FOSSIL_MOCK_PIZZA_TYPE_CCHAR:
                case FOSSIL_MOCK_PIZZA_TYPE_WCHAR:
                    pizza_io_printf("  {blue}Value:{reset} '%s'\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
                case FOSSIL_MOCK_PIZZA_TYPE_BOOL:
                    pizza_io_printf("  {blue}Value:{reset} %s\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
                case FOSSIL_MOCK_PIZZA_TYPE_ANY:
                default:
                    pizza_io_printf("  {blue}Value:{reset} %s\n", current->arguments[i].value.data ? current->arguments[i].value.data : "NULL");
                    break;
            }

            pizza_io_printf("  {red}Mutable:{reset} %s\n", current->arguments[i].value.mutable_flag ? "{green}true{reset}" : "{yellow}false{reset}");
            pizza_io_printf("  {cyan}Attribute Name:{reset} %s\n", current->arguments[i].attribute.name ? current->arguments[i].attribute.name : "NULL");
            pizza_io_printf("  {cyan}Attribute Description:{reset} %s\n", current->arguments[i].attribute.description ? current->arguments[i].attribute.description : "NULL");
            pizza_io_printf("  {cyan}Attribute ID:{reset} %s\n", current->arguments[i].attribute.id ? current->arguments[i].attribute.id : "NULL");
        }
        ++call_index;
        current = current->next;
    }
}

void fossil_mock_set_ai_context(fossil_mock_call_t *call, fossil_mock_ai_context_t *ai_context) {
    if (!call) return;
    if (call->ai_context) {
        fossil_mock_destroy_ai_context(call->ai_context);
    }
    call->ai_context = NULL;
    if (ai_context) {
        call->ai_context = (fossil_mock_ai_context_t *)pizza_sys_memory_alloc(sizeof(fossil_mock_ai_context_t));
        if (call->ai_context) {
            call->ai_context->context_info = ai_context->context_info ? pizza_io_cstr_dup(ai_context->context_info) : NULL;
            call->ai_context->expected_behavior = ai_context->expected_behavior ? pizza_io_cstr_dup(ai_context->expected_behavior) : NULL;
            // AI trick: Clamp confidence to [0.0, 1.0] and print a warning if out of range
            if (ai_context->confidence < 0.0) {
                pizza_io_printf("{yellow}AI Trick:{reset} Confidence below 0.0, clamped to 0.0\n");
                call->ai_context->confidence = 0.0;
            } else if (ai_context->confidence > 1.0) {
                pizza_io_printf("{yellow}AI Trick:{reset} Confidence above 1.0, clamped to 1.0\n");
                call->ai_context->confidence = 1.0;
            } else {
                call->ai_context->confidence = ai_context->confidence;
            }
            // AI trick: If ai_notes is NULL, auto-fill with "No notes provided"
            call->ai_context->ai_notes = ai_context->ai_notes ? pizza_io_cstr_dup(ai_context->ai_notes) : pizza_io_cstr_dup("No notes provided");
        }
    }
}

// AI trick: If confidence is not in [0.0, 1.0], clamp it and print a warning.
fossil_mock_ai_context_t *fossil_mock_create_ai_context(const char *context_info, const char *expected_behavior, double confidence, const char *ai_notes) {
    fossil_mock_ai_context_t *ctx = (fossil_mock_ai_context_t *)pizza_sys_memory_alloc(sizeof(fossil_mock_ai_context_t));
    if (!ctx) return NULL;
    ctx->context_info = context_info ? pizza_io_cstr_dup(context_info) : NULL;
    ctx->expected_behavior = expected_behavior ? pizza_io_cstr_dup(expected_behavior) : NULL;
    // Clamp confidence to [0.0, 1.0]
    if (confidence < 0.0) {
        pizza_io_printf("{yellow}AI Trick:{reset} Confidence below 0.0, clamped to 0.0\n");
        ctx->confidence = 0.0;
    } else if (confidence > 1.0) {
        pizza_io_printf("{yellow}AI Trick:{reset} Confidence above 1.0, clamped to 1.0\n");
        ctx->confidence = 1.0;
    } else {
        ctx->confidence = confidence;
    }
    // AI trick: If ai_notes is NULL, auto-fill with "No notes provided"
    ctx->ai_notes = ai_notes ? pizza_io_cstr_dup(ai_notes) : pizza_io_cstr_dup("No notes provided");
    return ctx;
}

void fossil_mock_destroy_ai_context(fossil_mock_ai_context_t *ai_context) {
    if (!ai_context) return;
    pizza_sys_memory_free(ai_context->context_info);
    pizza_sys_memory_free(ai_context->expected_behavior);
    pizza_sys_memory_free(ai_context->ai_notes);
    pizza_sys_memory_free(ai_context);
}

// AI trick: Print a warning if confidence is below a threshold (e.g., 0.5)
void fossil_mock_print_ai_context(const fossil_mock_ai_context_t *ai_context) {
    if (!ai_context) return;
    pizza_io_printf("  {green}AI Context:{reset}\n");
    pizza_io_printf("    {blue}Info:{reset} %s\n", ai_context->context_info ? ai_context->context_info : "NULL");
    pizza_io_printf("    {blue}Expected:{reset} %s\n", ai_context->expected_behavior ? ai_context->expected_behavior : "NULL");
    pizza_io_printf("    {blue}Confidence:{reset} %.2f\n", ai_context->confidence);
    if (ai_context->confidence < 0.5) {
        pizza_io_printf("    {red,bold}Warning:{reset} Confidence is low!\n");
    }
    pizza_io_printf("    {blue}Notes:{reset} %s\n", ai_context->ai_notes ? ai_context->ai_notes : "NULL");
}

int fossil_mock_capture_output(char *buffer, size_t size, void (*function)(void)) {
    if (!buffer || size == 0 || !function) {
        return -1;
    }

    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return -1;
    }

    int original_stdout_fd = dup(STDOUT_FILENO);
    if (original_stdout_fd == -1) {
        fclose(temp_file);
        return -1;
    }
    fflush(stdout);
    if (dup2(fileno(temp_file), STDOUT_FILENO) == -1) {
        fclose(temp_file);
        close(original_stdout_fd);
        return -1;
    }

    function(); // no arguments passed

    fflush(stdout);
    dup2(original_stdout_fd, STDOUT_FILENO);
    close(original_stdout_fd);

    rewind(temp_file);
    size_t read_size = fread(buffer, 1, size - 1, temp_file);
    buffer[read_size] = '\0';

    fclose(temp_file);
    return (int)read_size;
}

bool fossil_mock_compare_output(const char *captured, const char *expected) {
    if (!captured || !expected) {
        return false;
    }
    return strcmp(captured, expected) == 0;
}
