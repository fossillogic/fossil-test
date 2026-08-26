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
#include "fossil/maip/mutate.h"

#include <stdlib.h>
#include <string.h>

/*
 * *****************************************************************************
 * Internal Structures
 * *****************************************************************************
 */

struct fossil_mutate_s
{
    fossil_mutation_t **mutations;
    size_t count;
    size_t capacity;
};

struct fossil_mutation_s
{
    fossil_mutate_t *context;

    char *id;
    char *name;
    char *description;

    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    char *original;
    char *modified;

    char *status;

    size_t tests;
    size_t failures;

    bool applied;
};

struct fossil_mutate_target_s
{
    fossil_mutation_t *mutation;

    char *file;
    size_t line;
    size_t column;
};

struct fossil_mutate_operator_s
{
    char *id;
    char *type;

    char *original;
    char *replacement;
};

struct fossil_mutate_result_s
{
    char *status;
    size_t tests;
    size_t failures;
};

/*
 * *****************************************************************************
 * Internal Helpers
 * *****************************************************************************
 */

static bool
fossil_mutate_replace_string(
    char **destination,
    const char *value)
{
    char *copy;

    if (!destination)
    {
        return false;
    }

    copy = NULL;

    if (value)
    {
        copy = maip_io_cstr_dup(value);

        if (!copy)
        {
            return false;
        }
    }

    free(*destination);

    *destination = copy;

    return true;
}

static bool
fossil_mutate_reserve(
    fossil_mutate_t *mutate,
    size_t capacity)
{
    fossil_mutation_t **mutations;
    size_t next;

    if (!mutate)
    {
        return false;
    }

    if (capacity <= mutate->capacity)
    {
        return true;
    }

    next = mutate->capacity ? mutate->capacity : 8;

    while (next < capacity)
    {
        if (next > SIZE_MAX / 2)
        {
            next = capacity;
            break;
        }

        next *= 2;
    }

    mutations = maip_sys_memory_realloc(
        mutate->mutations,
        next * sizeof(*mutations));

    if (!mutations)
    {
        return false;
    }

    mutate->mutations = mutations;
    mutate->capacity = next;

    return true;
}

static void
fossil_mutate_free_target(
    fossil_mutate_target_t *target)
{
    if (!target)
    {
        return;
    }

    maip_sys_memory_free(target->file);
    maip_sys_memory_free(target);
}

static void
fossil_mutate_free_operator(
    fossil_mutate_operator_t *op)
{
    if (!op)
    {
        return;
    }

    maip_sys_memory_free(op->id);
    maip_sys_memory_free(op->type);
    maip_sys_memory_free(op->original);
    maip_sys_memory_free(op->replacement);

    maip_sys_memory_free(op);
}

static void
fossil_mutate_free_case(
    fossil_mutation_t *mutation)
{
    if (!mutation)
    {
        return;
    }

    maip_sys_memory_free(mutation->id);
    maip_sys_memory_free(mutation->name);
    maip_sys_memory_free(mutation->description);

    maip_sys_memory_free(mutation->original);
    maip_sys_memory_free(mutation->modified);

    maip_sys_memory_free(mutation->status);

    fossil_mutate_free_target(mutation->target);
    fossil_mutate_free_operator(mutation->opr);

    maip_sys_memory_free(mutation);
}

static bool
fossil_mutate_status_valid(
    const char *status)
{
    if (!status)
    {
        return false;
    }

    return strcmp(status, FOSSIL_MUTATE_STATUS_PENDING) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_APPLIED) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_KILLED) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_SURVIVED) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_EQUIVALENT) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_INVALID) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_TIMEOUT) == 0 ||
           strcmp(status, FOSSIL_MUTATE_STATUS_ERROR) == 0;
}

static size_t
fossil_mutate_source_offset(
    const char *source,
    size_t line,
    size_t column)
{
    size_t current_line;
    size_t current_column;
    size_t offset;

    if (!source || line == 0 || column == 0)
    {
        return SIZE_MAX;
    }

    current_line = 1;
    current_column = 1;
    offset = 0;

    while (source[offset] != '\0')
    {
        if (current_line == line &&
            current_column == column)
        {
            return offset;
        }

        if (source[offset] == '\n')
        {
            current_line++;
            current_column = 1;
        }
        else
        {
            current_column++;
        }

        offset++;
    }

    if (current_line == line &&
        current_column == column)
    {
        return offset;
    }

    return SIZE_MAX;
}

static bool
fossil_mutate_apply_operator(
    fossil_mutation_t *mutation,
    fossil_mutate_target_t *target,
    fossil_mutate_operator_t *op)
{
    size_t offset;
    size_t original_length;
    size_t replacement_length;
    size_t source_length;
    size_t result_length;

    char *result;

    if (!mutation || !target || !op)
    {
        return false;
    }

    if (!mutation->original ||
        !op->original ||
        !op->replacement)
    {
        return false;
    }

    offset = fossil_mutate_source_offset(
        mutation->original,
        target->line,
        target->column);

    if (offset == SIZE_MAX)
    {
        return false;
    }

    original_length = strlen(op->original);
    replacement_length = strlen(op->replacement);
    source_length = strlen(mutation->original);

    if (offset > source_length)
    {
        return false;
    }

    if (original_length > source_length - offset)
    {
        return false;
    }

    if (strncmp(
            mutation->original + offset,
            op->original,
            original_length) != 0)
    {
        return false;
    }

    result_length =
        source_length -
        original_length +
        replacement_length;

    result = maip_sys_memory_alloc(result_length + 1);

    if (!result)
    {
        return false;
    }

    maip_sys_memory_copy(result, mutation->original, offset);

    maip_sys_memory_copy(result + offset, op->replacement, replacement_length);

    maip_sys_memory_copy(result + offset + replacement_length,
                         mutation->original + offset + original_length,
                         source_length - offset - original_length);

    result[result_length] = '\0';

    maip_sys_memory_free(mutation->modified);

    mutation->modified = result;

    return true;
}

/*
 * *****************************************************************************
 * Mutation Context
 * *****************************************************************************
 */

fossil_mutate_t *
fossil_mutate_create(
    void)
{
    fossil_mutate_t *mutate;

    mutate = calloc(1, sizeof(*mutate));

    if (!mutate)
    {
        return NULL;
    }

    return mutate;
}

void fossil_mutate_destroy(
    fossil_mutate_t *mutate)
{
    size_t i;

    if (!mutate)
    {
        return;
    }

    for (i = 0; i < mutate->count; ++i)
    {
        fossil_mutate_free_case(mutate->mutations[i]);
    }

    free(mutate->mutations);
    free(mutate);
}

void fossil_mutate_clear(
    fossil_mutate_t *mutate)
{
    size_t i;

    if (!mutate)
    {
        return;
    }

    for (i = 0; i < mutate->count; ++i)
    {
        fossil_mutate_free_case(mutate->mutations[i]);
    }

    mutate->count = 0;
}

/*
 * *****************************************************************************
 * Mutation Cases
 * *****************************************************************************
 */

fossil_mutation_t *
fossil_mutate_create_case(
    fossil_mutate_t *mutate,
    const char *id)
{
    fossil_mutation_t *mutation;

    if (!mutate || !id || id[0] == '\0')
    {
        return NULL;
    }

    if (!fossil_mutate_reserve(
            mutate,
            mutate->count + 1))
    {
        return NULL;
    }

    mutation = calloc(1, sizeof(*mutation));

    if (!mutation)
    {
        return NULL;
    }

    mutation->context = mutate;
    mutation->id = maip_io_cstr_dup(id);
    mutation->status =
        maip_io_cstr_dup(FOSSIL_MUTATE_STATUS_PENDING);

    if (!mutation->id || !mutation->status)
    {
        fossil_mutate_free_case(mutation);
        return NULL;
    }

    mutate->mutations[mutate->count++] = mutation;

    return mutation;
}

void fossil_mutate_destroy_case(
    fossil_mutation_t *mutation)
{
    fossil_mutate_t *mutate;
    size_t i;

    if (!mutation)
    {
        return;
    }

    mutate = mutation->context;

    if (mutate)
    {
        for (i = 0; i < mutate->count; ++i)
        {
            if (mutate->mutations[i] == mutation)
            {
                if (i + 1 < mutate->count)
                {
                    memmove(
                        &mutate->mutations[i],
                        &mutate->mutations[i + 1],
                        (mutate->count - i - 1) *
                            sizeof(*mutate->mutations));
                }

                mutate->count--;
                break;
            }
        }
    }

    fossil_mutate_free_case(mutation);
}

const char *
fossil_mutate_get_id(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->id : NULL;
}

bool fossil_mutate_set_name(
    fossil_mutation_t *mutation,
    const char *name)
{
    return mutation &&
           fossil_mutate_replace_string(
               &mutation->name,
               name);
}

const char *
fossil_mutate_get_name(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->name : NULL;
}

bool fossil_mutate_set_description(
    fossil_mutation_t *mutation,
    const char *description)
{
    return mutation &&
           fossil_mutate_replace_string(
               &mutation->description,
               description);
}

const char *
fossil_mutate_get_description(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->description : NULL;
}

/*
 * *****************************************************************************
 * Mutation Targets
 * *****************************************************************************
 */

fossil_mutate_target_t *
fossil_mutate_create_target(
    fossil_mutation_t *mutation,
    const char *file,
    size_t line,
    size_t column)
{
    fossil_mutate_target_t *target;

    if (!mutation || !file || file[0] == '\0')
    {
        return NULL;
    }

    if (line == 0 || column == 0)
    {
        return NULL;
    }

    target = calloc(1, sizeof(*target));

    if (!target)
    {
        return NULL;
    }

    target->mutation = mutation;
    target->file = maip_io_cstr_dup(file);
    target->line = line;
    target->column = column;

    if (!target->file)
    {
        fossil_mutate_free_target(target);
        return NULL;
    }

    if (mutation->target)
    {
        fossil_mutate_free_target(mutation->target);
    }

    mutation->target = target;

    return target;
}

void fossil_mutate_destroy_target(
    fossil_mutate_target_t *target)
{
    fossil_mutation_t *mutation;

    if (!target)
    {
        return;
    }

    mutation = target->mutation;

    if (mutation &&
        mutation->target == target)
    {
        mutation->target = NULL;
    }

    fossil_mutate_free_target(target);
}

bool fossil_mutate_set_target_file(
    fossil_mutate_target_t *target,
    const char *file)
{
    return target &&
           file &&
           file[0] != '\0' &&
           fossil_mutate_replace_string(
               &target->file,
               file);
}

const char *
fossil_mutate_get_target_file(
    const fossil_mutate_target_t *target)
{
    return target ? target->file : NULL;
}

bool fossil_mutate_set_target_line(
    fossil_mutate_target_t *target,
    size_t line)
{
    if (!target || line == 0)
    {
        return false;
    }

    target->line = line;

    return true;
}

size_t
fossil_mutate_get_target_line(
    const fossil_mutate_target_t *target)
{
    return target ? target->line : 0;
}

bool fossil_mutate_set_target_column(
    fossil_mutate_target_t *target,
    size_t column)
{
    if (!target || column == 0)
    {
        return false;
    }

    target->column = column;

    return true;
}

size_t
fossil_mutate_get_target_column(
    const fossil_mutate_target_t *target)
{
    return target ? target->column : 0;
}

/*
 * *****************************************************************************
 * Source Values
 * *****************************************************************************
 */

bool fossil_mutate_set_original(
    fossil_mutation_t *mutation,
    const char *source)
{
    if (!mutation || !source)
    {
        return false;
    }

    if (!fossil_mutate_replace_string(
            &mutation->original,
            source))
    {
        return false;
    }

    free(mutation->modified);

    mutation->modified = NULL;
    mutation->applied = false;

    free(mutation->status);

    mutation->status =
        maip_io_cstr_dup(FOSSIL_MUTATE_STATUS_PENDING);

    return mutation->status != NULL;
}

const char *
fossil_mutate_get_original(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->original : NULL;
}

bool fossil_mutate_set_modified(
    fossil_mutation_t *mutation,
    const char *source)
{
    if (!mutation || !source)
    {
        return false;
    }

    return fossil_mutate_replace_string(
        &mutation->modified,
        source);
}

const char *
fossil_mutate_get_modified(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->modified : NULL;
}

/*
 * *****************************************************************************
 * Mutation Operators
 * *****************************************************************************
 */

fossil_mutate_operator_t *
fossil_mutate_create_operator(
    const char *id,
    const char *type)
{
    fossil_mutate_operator_t *op;

    if (!id || !type ||
        id[0] == '\0' ||
        type[0] == '\0')
    {
        return NULL;
    }

    op = calloc(1, sizeof(*op));

    if (!op)
    {
        return NULL;
    }

    op->id = maip_io_cstr_dup(id);
    op->type = maip_io_cstr_dup(type);

    if (!op->id || !op->type)
    {
        fossil_mutate_free_operator(op);
        return NULL;
    }

    return op;
}

void fossil_mutate_destroy_operator(
    fossil_mutate_operator_t *opr)
{
    fossil_mutate_free_operator(opr);
}

const char *
fossil_mutate_operator_id(
    const fossil_mutate_operator_t *opr)
{
    return opr ? opr->id : NULL;
}

const char *
fossil_mutate_operator_type(
    const fossil_mutate_operator_t *opr)
{
    return opr ? opr->type : NULL;
}

bool fossil_mutate_operator_set_original(
    fossil_mutate_operator_t *opr,
    const char *value)
{
    if (!opr || !value || value[0] == '\0')
    {
        return false;
    }

    return fossil_mutate_replace_string(
        &opr->original,
        value);
}

bool fossil_mutate_operator_set_replacement(
    fossil_mutate_operator_t *opr,
    const char *value)
{
    if (!opr || !value)
    {
        return false;
    }

    return fossil_mutate_replace_string(
        &opr->replacement,
        value);
}

const char *
fossil_mutate_operator_original(
    const fossil_mutate_operator_t *opr)
{
    return opr ? opr->original : NULL;
}

const char *
fossil_mutate_operator_replacement(
    const fossil_mutate_operator_t *opr)
{
    return opr ? opr->replacement : NULL;
}

/*
 * *****************************************************************************
 * Mutation Application
 * *****************************************************************************
 */

bool fossil_mutate_apply(
    fossil_mutation_t *mutation,
    fossil_mutate_target_t *target,
    fossil_mutate_operator_t *opr)
{
    if (!mutation || !target || !opr)
    {
        return false;
    }

    if (!mutation->id ||
        !mutation->original ||
        !target->file ||
        target->line == 0 ||
        target->column == 0 ||
        !opr->original ||
        !opr->replacement)
    {
        return false;
    }

    if (target->mutation != mutation)
    {
        return false;
    }

    if (!fossil_mutate_apply_operator(
            mutation,
            target,
            opr))
    {
        fossil_mutate_replace_string(
            &mutation->status,
            FOSSIL_MUTATE_STATUS_INVALID);

        mutation->applied = false;

        return false;
    }

    if (mutation->target &&
        mutation->target != target)
    {
        fossil_mutate_free_target(mutation->target);
    }

    if (mutation->opr &&
        mutation->opr != opr)
    {
        fossil_mutate_free_operator(mutation->opr);
    }

    mutation->target = target;
    mutation->opr = opr;
    mutation->applied = true;

    mutation->tests = 0;
    mutation->failures = 0;

    return fossil_mutate_replace_string(
        &mutation->status,
        FOSSIL_MUTATE_STATUS_APPLIED);
}

bool fossil_mutate_reset(
    fossil_mutation_t *mutation)
{
    if (!mutation)
    {
        return false;
    }

    free(mutation->modified);

    mutation->modified = NULL;
    mutation->applied = false;
    mutation->tests = 0;
    mutation->failures = 0;

    return fossil_mutate_replace_string(
        &mutation->status,
        FOSSIL_MUTATE_STATUS_PENDING);
}

bool fossil_mutate_validate(
    const fossil_mutation_t *mutation)
{
    if (!mutation)
    {
        return false;
    }

    if (!mutation->id ||
        !mutation->original ||
        !mutation->target ||
        !mutation->opr)
    {
        return false;
    }

    if (!mutation->target->file ||
        mutation->target->line == 0 ||
        mutation->target->column == 0)
    {
        return false;
    }

    if (!mutation->opr->original ||
        !mutation->opr->replacement)
    {
        return false;
    }

    return true;
}

/*
 * *****************************************************************************
 * Mutation State
 * *****************************************************************************
 */

const char *
fossil_mutate_status(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->status : NULL;
}

bool fossil_mutate_is_applied(
    const fossil_mutation_t *mutation)
{
    return mutation &&
           mutation->status &&
           strcmp(
               mutation->status,
               FOSSIL_MUTATE_STATUS_APPLIED) == 0;
}

bool fossil_mutate_is_survived(
    const fossil_mutation_t *mutation)
{
    return mutation &&
           mutation->status &&
           strcmp(
               mutation->status,
               FOSSIL_MUTATE_STATUS_SURVIVED) == 0;
}

bool fossil_mutate_is_killed(
    const fossil_mutation_t *mutation)
{
    return mutation &&
           mutation->status &&
           strcmp(
               mutation->status,
               FOSSIL_MUTATE_STATUS_KILLED) == 0;
}

bool fossil_mutate_is_equivalent(
    const fossil_mutation_t *mutation)
{
    return mutation &&
           mutation->status &&
           strcmp(
               mutation->status,
               FOSSIL_MUTATE_STATUS_EQUIVALENT) == 0;
}

/*
 * *****************************************************************************
 * Mutation Results
 * *****************************************************************************
 */

bool fossil_mutate_record_result(
    fossil_mutation_t *mutation,
    const char *status,
    size_t tests,
    size_t failures)
{
    if (!mutation ||
        !mutation->applied ||
        !mutation->modified ||
        !fossil_mutate_status_valid(status))
    {
        return false;
    }

    if (failures > tests)
    {
        return false;
    }

    if (!fossil_mutate_replace_string(
            &mutation->status,
            status))
    {
        return false;
    }

    mutation->tests = tests;
    mutation->failures = failures;

    return true;
}

size_t
fossil_mutate_tests(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->tests : 0;
}

size_t
fossil_mutate_failures(
    const fossil_mutation_t *mutation)
{
    return mutation ? mutation->failures : 0;
}

/*
 * *****************************************************************************
 * Mutation Comparison
 * *****************************************************************************
 */

bool fossil_mutate_changed(
    const fossil_mutation_t *mutation)
{
    if (!mutation ||
        !mutation->original ||
        !mutation->modified)
    {
        return false;
    }

    return strcmp(
               mutation->original,
               mutation->modified) != 0;
}

bool fossil_mutate_compare(
    const fossil_mutation_t *first,
    const fossil_mutation_t *second)
{
    if (!first || !second)
    {
        return false;
    }

    if (first == second)
    {
        return true;
    }

    if (!first->id || !second->id)
    {
        return false;
    }

    if (strcmp(first->id, second->id) != 0)
    {
        return false;
    }

    if (first->target && second->target)
    {
        if (!first->target->file ||
            !second->target->file ||
            strcmp(
                first->target->file,
                second->target->file) != 0 ||
            first->target->line != second->target->line ||
            first->target->column != second->target->column)
        {
            return false;
        }
    }
    else if (first->target != second->target)
    {
        return false;
    }

    if (first->opr && second->opr)
    {
        if (!first->opr->id ||
            !second->opr->id ||
            strcmp(
                first->opr->id,
                second->opr->id) != 0)
        {
            return false;
        }
    }
    else if (first->opr != second->opr)
    {
        return false;
    }

    if (first->original && second->original)
    {
        if (strcmp(
                first->original,
                second->original) != 0)
        {
            return false;
        }
    }
    else if (first->original != second->original)
    {
        return false;
    }

    if (first->modified && second->modified)
    {
        return strcmp(
                   first->modified,
                   second->modified) == 0;
    }

    return first->modified == second->modified;
}
