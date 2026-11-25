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
#include "fossil/maip/mock.h"

// *****************************************************************************
// Function declarations
// *****************************************************************************

static void fossil_mock_free_arguments(fossil_mock_maip_t *arguments, int num_args) {
    if (!arguments) {
        return;
    }

    for (int i = 0; i < num_args; ++i) {
        switch (arguments[i].type) {
            case FOSSIL_MOCK_MAIP_TYPE_CSTR:
                maip_sys_memory_free((void *)arguments[i].value.as.cstr);
                break;
            case FOSSIL_MOCK_MAIP_TYPE_WSTR:
                maip_sys_memory_free((void *)arguments[i].value.as.wstr);
                break;
            default:
                break;
        }
    }
    maip_sys_memory_free(arguments);
}

static void fossil_mock_free_call(fossil_mock_call_t *call) {
    if (!call) {
        return;
    }
    maip_sys_memory_free(call->function_name);
    fossil_mock_free_arguments(call->arguments, call->num_args);
    maip_sys_memory_free(call);
}

static bool fossil_mock_values_equal(fossil_mock_maip_type_t type,
                                     fossil_mock_maip_value_t left,
                                     fossil_mock_maip_value_t right) {
    switch (type) {
        case FOSSIL_MOCK_MAIP_TYPE_I8: return left.as.i8 == right.as.i8;
        case FOSSIL_MOCK_MAIP_TYPE_I16: return left.as.i16 == right.as.i16;
        case FOSSIL_MOCK_MAIP_TYPE_I32: return left.as.i32 == right.as.i32;
        case FOSSIL_MOCK_MAIP_TYPE_I64: return left.as.i64 == right.as.i64;
        case FOSSIL_MOCK_MAIP_TYPE_U8: return left.as.u8 == right.as.u8;
        case FOSSIL_MOCK_MAIP_TYPE_U16: return left.as.u16 == right.as.u16;
        case FOSSIL_MOCK_MAIP_TYPE_U32: return left.as.u32 == right.as.u32;
        case FOSSIL_MOCK_MAIP_TYPE_U64: return left.as.u64 == right.as.u64;
        case FOSSIL_MOCK_MAIP_TYPE_HEX: return left.as.hex == right.as.hex;
        case FOSSIL_MOCK_MAIP_TYPE_OCTAL: return left.as.octal == right.as.octal;
        case FOSSIL_MOCK_MAIP_TYPE_FLOAT: return left.as.f32 == right.as.f32;
        case FOSSIL_MOCK_MAIP_TYPE_DOUBLE: return left.as.f64 == right.as.f64;
        case FOSSIL_MOCK_MAIP_TYPE_WSTR:
            if (!left.as.wstr || !right.as.wstr) return left.as.wstr == right.as.wstr;
            return wcscmp(left.as.wstr, right.as.wstr) == 0;
        case FOSSIL_MOCK_MAIP_TYPE_CSTR:
            if (!left.as.cstr || !right.as.cstr) return left.as.cstr == right.as.cstr;
            return strcmp(left.as.cstr, right.as.cstr) == 0;
        case FOSSIL_MOCK_MAIP_TYPE_CCHAR: return left.as.cchar == right.as.cchar;
        case FOSSIL_MOCK_MAIP_TYPE_WCHAR: return left.as.wchar == right.as.wchar;
        case FOSSIL_MOCK_MAIP_TYPE_BOOL: return left.as.boolean == right.as.boolean;
        case FOSSIL_MOCK_MAIP_TYPE_SIZE: return left.as.size == right.as.size;
        case FOSSIL_MOCK_MAIP_TYPE_ANY: return left.as.any == right.as.any;
        default: return false;
    }
}

void fossil_mock_init(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_destroy(fossil_mock_calllist_t *list) {
    if (!list) {
        return;
    }

    fossil_mock_call_t *current = list->head;
    while (current) {
        fossil_mock_call_t *next = current->next;
        fossil_mock_free_call(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void fossil_mock_add_call(fossil_mock_calllist_t *list, const char *function_name, fossil_mock_maip_t *arguments, int num_args) {
    if (!list || !function_name || num_args < 0 || (num_args > 0 && !arguments)) {
        return;
    }

    fossil_mock_call_t *call = (fossil_mock_call_t *)maip_sys_memory_alloc(sizeof(fossil_mock_call_t));
    if (!call) {
        return;
    }

    call->function_name = maip_io_cstr_dup(function_name);
    call->arguments = NULL;
    call->num_args = num_args;
    call->return_value = (fossil_mock_maip_value_t){0};
    call->stub = NULL;
    call->stub_user_data = NULL;
    call->next = NULL;

    if (!call->function_name) {
        maip_sys_memory_free(call);
        return;
    }

    if (num_args > 0) {
        call->arguments = (fossil_mock_maip_t *)maip_sys_memory_alloc((size_t)num_args * sizeof(fossil_mock_maip_t));
        if (!call->arguments) {
            maip_sys_memory_free(call->function_name);
            maip_sys_memory_free(call);
            return;
        }

        memcpy(call->arguments, arguments, (size_t)num_args * sizeof(*arguments));
        for (int i = 0; i < num_args; ++i) {
            if (call->arguments[i].type == FOSSIL_MOCK_MAIP_TYPE_CSTR && arguments[i].value.as.cstr) {
                char *copy = maip_io_cstr_dup(arguments[i].value.as.cstr);
                if (!copy) {
                    fossil_mock_free_arguments(call->arguments, i);
                    maip_sys_memory_free(call->function_name);
                    maip_sys_memory_free(call);
                    return;
                }
                call->arguments[i].value.as.cstr = copy;
            } else if (call->arguments[i].type == FOSSIL_MOCK_MAIP_TYPE_WSTR && arguments[i].value.as.wstr) {
                size_t length = wcslen(arguments[i].value.as.wstr);
                wchar_t *copy = (wchar_t *)maip_sys_memory_alloc((length + 1) * sizeof(*copy));
                if (!copy) {
                    fossil_mock_free_arguments(call->arguments, i);
                    maip_sys_memory_free(call->function_name);
                    maip_sys_memory_free(call);
                    return;
                }
                wcscpy(copy, arguments[i].value.as.wstr);
                call->arguments[i].value.as.wstr = copy;
            }
        }
    }

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
        maip_io_printf("{cyan,bold}[%d] Function:{normal} {yellow}%s{reset}\n", call_index, current->function_name);

        maip_io_printf("{magenta}Arguments:{reset}\n");
        for (int i = 0; i < current->num_args; ++i) {
            maip_io_printf("  {blue}Type:{reset} %d\n", current->arguments[i].type);
            fossil_mock_maip_value_t value = current->arguments[i].value;
            switch (current->arguments[i].type) {
                case FOSSIL_MOCK_MAIP_TYPE_I8: maip_io_printf("  {blue}Value:{reset} %d\n", (int)value.as.i8); break;
                case FOSSIL_MOCK_MAIP_TYPE_I16: maip_io_printf("  {blue}Value:{reset} %d\n", (int)value.as.i16); break;
                case FOSSIL_MOCK_MAIP_TYPE_I32: maip_io_printf("  {blue}Value:{reset} %d\n", value.as.i32); break;
                case FOSSIL_MOCK_MAIP_TYPE_I64: maip_io_printf("  {blue}Value:{reset} %lld\n", (long long)value.as.i64); break;
                case FOSSIL_MOCK_MAIP_TYPE_U8: maip_io_printf("  {blue}Value:{reset} %u\n", (unsigned)value.as.u8); break;
                case FOSSIL_MOCK_MAIP_TYPE_U16: maip_io_printf("  {blue}Value:{reset} %u\n", (unsigned)value.as.u16); break;
                case FOSSIL_MOCK_MAIP_TYPE_U32: maip_io_printf("  {blue}Value:{reset} %u\n", (unsigned)value.as.u32); break;
                case FOSSIL_MOCK_MAIP_TYPE_U64: maip_io_printf("  {blue}Value:{reset} %llu\n", (unsigned long long)value.as.u64); break;
                case FOSSIL_MOCK_MAIP_TYPE_HEX: maip_io_printf("  {blue}Value:{reset} 0x%llx\n", (unsigned long long)value.as.hex); break;
                case FOSSIL_MOCK_MAIP_TYPE_OCTAL: maip_io_printf("  {blue}Value:{reset} 0%llo\n", (unsigned long long)value.as.octal); break;
                case FOSSIL_MOCK_MAIP_TYPE_FLOAT: maip_io_printf("  {blue}Value:{reset} %g\n", (double)value.as.f32); break;
                case FOSSIL_MOCK_MAIP_TYPE_DOUBLE: maip_io_printf("  {blue}Value:{reset} %g\n", value.as.f64); break;
                case FOSSIL_MOCK_MAIP_TYPE_WSTR: maip_io_printf("  {blue}Value:{reset} \"%ls\"\n", value.as.wstr ? value.as.wstr : L"NULL"); break;
                case FOSSIL_MOCK_MAIP_TYPE_CSTR: maip_io_printf("  {blue}Value:{reset} \"%s\"\n", value.as.cstr ? value.as.cstr : "NULL"); break;
                case FOSSIL_MOCK_MAIP_TYPE_CCHAR: maip_io_printf("  {blue}Value:{reset} '%c'\n", value.as.cchar); break;
                case FOSSIL_MOCK_MAIP_TYPE_WCHAR: maip_io_printf("  {blue}Value:{reset} '%lc'\n", value.as.wchar); break;
                case FOSSIL_MOCK_MAIP_TYPE_BOOL: maip_io_printf("  {blue}Value:{reset} %s\n", value.as.boolean ? "true" : "false"); break;
                case FOSSIL_MOCK_MAIP_TYPE_SIZE: maip_io_printf("  {blue}Value:{reset} %zu\n", value.as.size); break;
                case FOSSIL_MOCK_MAIP_TYPE_ANY: maip_io_printf("  {blue}Value:{reset} %p\n", value.as.any); break;
                default:
                    maip_io_printf("  {blue}Value:{reset} <invalid>\n");
                    break;
            }

            maip_io_printf("  {red}Mutable:{reset} %s\n", current->arguments[i].value.mutable_flag ? "{green}true{reset}" : "{yellow}false{reset}");
            maip_io_printf("  {cyan}Attribute Name:{reset} %s\n", current->arguments[i].attribute.name ? current->arguments[i].attribute.name : "NULL");
            maip_io_printf("  {cyan}Attribute Description:{reset} %s\n", current->arguments[i].attribute.description ? current->arguments[i].attribute.description : "NULL");
            maip_io_printf("  {cyan}Attribute ID:{reset} %s\n", current->arguments[i].attribute.id ? current->arguments[i].attribute.id : "NULL");
        }
        ++call_index;
        current = current->next;
    }
}

void fossil_mock_set_stub(fossil_mock_call_t *call, fossil_mock_stub_fn stub, void *user_data) {
    if (!call) return;
    call->stub = stub;
    call->stub_user_data = user_data;
}

void fossil_mock_set_return_value(fossil_mock_call_t *call, fossil_mock_maip_value_t value) {
    if (!call) return;
    call->return_value = value;
}

int fossil_mock_count_calls(const fossil_mock_calllist_t *list, const char *function_name) {
    if (!list || !function_name) return 0;
    int count = 0;
    for (const fossil_mock_call_t *call = list->head; call; call = call->next) {
        if (call->function_name && strcmp(call->function_name, function_name) == 0) ++count;
    }
    return count;
}

bool fossil_mock_verify_call(const fossil_mock_call_t *call, const fossil_mock_maip_t *arguments, int num_args) {
    if (!call || num_args < 0 || call->num_args != num_args || (num_args > 0 && (!arguments || !call->arguments))) return false;
    for (int i = 0; i < num_args; ++i) {
        if (call->arguments[i].type != arguments[i].type ||
            call->arguments[i].value.mutable_flag != arguments[i].value.mutable_flag ||
            !fossil_mock_values_equal(call->arguments[i].type, call->arguments[i].value, arguments[i].value)) {
            return false;
        }
    }
    return true;
}

bool fossil_mock_verify_order(const fossil_mock_calllist_t *list, const char *const *function_names, int count) {
    if (!list || count < 0 || (count > 0 && !function_names) || list->size != count) return false;
    const fossil_mock_call_t *call = list->head;
    for (int i = 0; i < count; ++i, call = call->next) {
        if (!call || !call->function_name || !function_names[i] || strcmp(call->function_name, function_names[i]) != 0) return false;
    }
    return call == NULL;
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
