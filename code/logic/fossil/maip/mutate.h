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
#ifndef FOSSIL_MUTATE_H
#define FOSSIL_MUTATE_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * *****************************************************************************
 * Fossil Mutate
 *
 * Mutation testing components for Fossil Test.
 *
 * Fossil Mutate provides the API for creating mutation cases, defining
 * mutation operators, identifying mutation targets, applying mutations,
 * restoring original source, and recording mutation results.
 *
 * Test execution remains the responsibility of Fossil Test.
 *
 * *****************************************************************************
 */


/*
 * Mutation Status
 */

#define FOSSIL_MUTATE_STATUS_PENDING      "pending"
#define FOSSIL_MUTATE_STATUS_APPLIED      "applied"
#define FOSSIL_MUTATE_STATUS_KILLED       "killed"
#define FOSSIL_MUTATE_STATUS_SURVIVED     "survived"
#define FOSSIL_MUTATE_STATUS_EQUIVALENT   "equivalent"
#define FOSSIL_MUTATE_STATUS_INVALID      "invalid"
#define FOSSIL_MUTATE_STATUS_TIMEOUT      "timeout"
#define FOSSIL_MUTATE_STATUS_ERROR        "error"


/*
 * Mutation Operator Types
 */

#define FOSSIL_MUTATE_OPERATOR_RELATIONAL   "relational"
#define FOSSIL_MUTATE_OPERATOR_ARITHMETIC   "arithmetic"
#define FOSSIL_MUTATE_OPERATOR_LOGICAL      "logical"
#define FOSSIL_MUTATE_OPERATOR_BITWISE      "bitwise"
#define FOSSIL_MUTATE_OPERATOR_CONSTANT     "constant"
#define FOSSIL_MUTATE_OPERATOR_NEGATION     "negation"
#define FOSSIL_MUTATE_OPERATOR_RETURN       "return"
#define FOSSIL_MUTATE_OPERATOR_CONDITIONAL  "conditional"
#define FOSSIL_MUTATE_OPERATOR_CUSTOM       "custom"


/*
 * Mutation Operators
 *
 * Relational:
 *
 *     >  -> >=
 *     >  -> <
 *     >= -> >
 *     <  -> <=
 *     <= -> <
 *     == -> !=
 *     != -> ==
 *
 * Arithmetic:
 *
 *     + -> -
 *     - -> +
 *     * -> /
 *     / -> *
 *
 * Logical:
 *
 *     && -> ||
 *     || -> &&
 *
 * Boolean:
 *
 *     true  -> false
 *     false -> true
 *
 * Negation:
 *
 *     condition -> !condition
 *
 * Return:
 *
 *     return value -> alternate value
 *
 * Conditional:
 *
 *     condition -> !condition
 */


/*
 * Opaque Types
 */

typedef struct fossil_mutate_s
    fossil_mutate_t;

typedef struct fossil_mutation_s
    fossil_mutation_t;

typedef struct fossil_mutate_target_s
    fossil_mutate_target_t;

typedef struct fossil_mutate_operator_s
    fossil_mutate_operator_t;

typedef struct fossil_mutate_result_s
    fossil_mutate_result_t;


/*
 * Mutation Context
 */

/**
 * @brief Creates a mutation context.
 *
 * @return Mutation context, or NULL on failure.
 */
FOSSIL_MAIP_API fossil_mutate_t*
fossil_mutate_create(void);


/**
 * @brief Destroys a mutation context.
 *
 * @param mutate Mutation context.
 */
FOSSIL_MAIP_API void
fossil_mutate_destroy(
    fossil_mutate_t* mutate
);


/**
 * @brief Clears all mutations from a mutation context.
 *
 * @param mutate Mutation context.
 */
FOSSIL_MAIP_API void
fossil_mutate_clear(
    fossil_mutate_t* mutate
);


/*
 * Mutation Cases
 */

/**
 * @brief Creates a mutation case.
 *
 * @param mutate Mutation context.
 * @param id String identifier for the mutation.
 *
 * @return Mutation case, or NULL on failure.
 */
FOSSIL_MAIP_API fossil_mutation_t*
fossil_mutate_create_case(
    fossil_mutate_t* mutate,
    const char* id
);


/**
 * @brief Destroys a mutation case.
 *
 * @param mutation Mutation case.
 */
FOSSIL_MAIP_API void
fossil_mutate_destroy_case(
    fossil_mutation_t* mutation
);


/**
 * @brief Gets the mutation identifier.
 *
 * @param mutation Mutation case.
 *
 * @return Mutation identifier, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_id(
    const fossil_mutation_t* mutation
);


/**
 * @brief Sets the mutation name.
 *
 * @param mutation Mutation case.
 * @param name Mutation name.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_name(
    fossil_mutation_t* mutation,
    const char* name
);


/**
 * @brief Gets the mutation name.
 *
 * @param mutation Mutation case.
 *
 * @return Mutation name, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_name(
    const fossil_mutation_t* mutation
);


/**
 * @brief Sets the mutation description.
 *
 * @param mutation Mutation case.
 * @param description Mutation description.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_description(
    fossil_mutation_t* mutation,
    const char* description
);


/**
 * @brief Gets the mutation description.
 *
 * @param mutation Mutation case.
 *
 * @return Mutation description, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_description(
    const fossil_mutation_t* mutation
);


/*
 * Mutation Targets
 */

/**
 * @brief Creates a mutation target.
 *
 * A mutation target identifies the source location to be mutated.
 *
 * @param mutation Mutation case.
 * @param file Source file.
 * @param line Source line.
 * @param column Source column.
 *
 * @return Mutation target, or NULL on failure.
 */
FOSSIL_MAIP_API fossil_mutate_target_t*
fossil_mutate_create_target(
    fossil_mutation_t* mutation,
    const char* file,
    size_t line,
    size_t column
);


/**
 * @brief Destroys a mutation target.
 *
 * @param target Mutation target.
 */
FOSSIL_MAIP_API void
fossil_mutate_destroy_target(
    fossil_mutate_target_t* target
);


/**
 * @brief Sets the source file for a mutation target.
 *
 * @param target Mutation target.
 * @param file Source file.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_target_file(
    fossil_mutate_target_t* target,
    const char* file
);


/**
 * @brief Gets the source file for a mutation target.
 *
 * @param target Mutation target.
 *
 * @return Source file, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_target_file(
    const fossil_mutate_target_t* target
);


/**
 * @brief Sets the source line for a mutation target.
 *
 * @param target Mutation target.
 * @param line Source line.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_target_line(
    fossil_mutate_target_t* target,
    size_t line
);


/**
 * @brief Gets the source line for a mutation target.
 *
 * @param target Mutation target.
 *
 * @return Source line.
 */
FOSSIL_MAIP_API size_t
fossil_mutate_get_target_line(
    const fossil_mutate_target_t* target
);


/**
 * @brief Sets the source column for a mutation target.
 *
 * @param target Mutation target.
 * @param column Source column.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_target_column(
    fossil_mutate_target_t* target,
    size_t column
);


/**
 * @brief Gets the source column for a mutation target.
 *
 * @param target Mutation target.
 *
 * @return Source column.
 */
FOSSIL_MAIP_API size_t
fossil_mutate_get_target_column(
    const fossil_mutate_target_t* target
);


/*
 * Source Values
 */

/**
 * @brief Sets the original source value for a mutation.
 *
 * @param mutation Mutation case.
 * @param source Original source value.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_original(
    fossil_mutation_t* mutation,
    const char* source
);


/**
 * @brief Gets the original source value.
 *
 * @param mutation Mutation case.
 *
 * @return Original source value, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_original(
    const fossil_mutation_t* mutation
);


/**
 * @brief Sets the mutated source value.
 *
 * @param mutation Mutation case.
 * @param source Mutated source value.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_set_modified(
    fossil_mutation_t* mutation,
    const char* source
);


/**
 * @brief Gets the mutated source value.
 *
 * @param mutation Mutation case.
 *
 * @return Mutated source value, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_get_modified(
    const fossil_mutation_t* mutation
);


/*
 * Mutation Operators
 */

/**
 * @brief Creates a mutation opr.
 *
 * @param id String identifier for the opr.
 * @param type Operator type.
 *
 * @return Mutation opr, or NULL on failure.
 */
FOSSIL_MAIP_API fossil_mutate_operator_t*
fossil_mutate_create_operator(
    const char* id,
    const char* type
);


/**
 * @brief Destroys a mutation opr.
 *
 * @param opr Mutation opr.
 */
FOSSIL_MAIP_API void
fossil_mutate_destroy_operator(
    fossil_mutate_operator_t* opr
);


/**
 * @brief Gets the opr identifier.
 *
 * @param opr Mutation opr.
 *
 * @return Operator identifier, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_operator_id(
    const fossil_mutate_operator_t* opr
);


/**
 * @brief Gets the opr type.
 *
 * @param opr Mutation opr.
 *
 * @return Operator type, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_operator_type(
    const fossil_mutate_operator_t* opr
);


/**
 * @brief Sets the original opr token.
 *
 * @param opr Mutation opr.
 * @param value Original opr.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_operator_set_original(
    fossil_mutate_operator_t* opr,
    const char* value
);


/**
 * @brief Sets the replacement opr token.
 *
 * @param opr Mutation opr.
 * @param value Replacement opr.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_operator_set_replacement(
    fossil_mutate_operator_t* opr,
    const char* value
);


/**
 * @brief Gets the original opr token.
 *
 * @param opr Mutation opr.
 *
 * @return Original opr, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_operator_original(
    const fossil_mutate_operator_t* opr
);


/**
 * @brief Gets the replacement opr token.
 *
 * @param opr Mutation opr.
 *
 * @return Replacement opr, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_operator_replacement(
    const fossil_mutate_operator_t* opr
);


/*
 * Mutation Application
 */

/**
 * @brief Applies a mutation opr to a mutation target.
 *
 * This function prepares the mutated representation. It does not execute
 * the Fossil Test runner.
 *
 * @param mutation Mutation case.
 * @param target Mutation target.
 * @param opr Mutation opr.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_apply(
    fossil_mutation_t* mutation,
    fossil_mutate_target_t* target,
    fossil_mutate_operator_t* opr
);


/**
 * @brief Restores the original mutation state.
 *
 * @param mutation Mutation case.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_reset(
    fossil_mutation_t* mutation
);


/**
 * @brief Validates whether a mutation can be applied.
 *
 * @param mutation Mutation case.
 *
 * @return true if valid, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_validate(
    const fossil_mutation_t* mutation
);


/*
 * Mutation State
 */

/**
 * @brief Gets the current mutation status.
 *
 * @param mutation Mutation case.
 *
 * @return Mutation status string, or NULL.
 */
FOSSIL_MAIP_API const char*
fossil_mutate_status(
    const fossil_mutation_t* mutation
);


/**
 * @brief Determines whether a mutation has been applied.
 *
 * @param mutation Mutation case.
 *
 * @return true if applied, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_is_applied(
    const fossil_mutation_t* mutation
);


/**
 * @brief Determines whether a mutation survived testing.
 *
 * @param mutation Mutation case.
 *
 * @return true if survived, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_is_survived(
    const fossil_mutation_t* mutation
);


/**
 * @brief Determines whether a mutation was killed by testing.
 *
 * @param mutation Mutation case.
 *
 * @return true if killed, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_is_killed(
    const fossil_mutation_t* mutation
);


/**
 * @brief Determines whether a mutation is equivalent to the original.
 *
 * @param mutation Mutation case.
 *
 * @return true if equivalent, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_is_equivalent(
    const fossil_mutation_t* mutation
);


/*
 * Mutation Results
 */

/**
 * @brief Records the result produced by Fossil Test.
 *
 * Fossil Test remains responsible for executing tests. This function only
 * records the resulting mutation state.
 *
 * @param mutation Mutation case.
 * @param status Mutation status.
 * @param tests Number of tests executed.
 * @param failures Number of failed tests.
 *
 * @return true on success, false on failure.
 */
FOSSIL_MAIP_API bool
fossil_mutate_record_result(
    fossil_mutation_t* mutation,
    const char* status,
    size_t tests,
    size_t failures
);


/**
 * @brief Gets the number of tests executed against a mutation.
 *
 * @param mutation Mutation case.
 *
 * @return Number of tests.
 */
FOSSIL_MAIP_API size_t
fossil_mutate_tests(
    const fossil_mutation_t* mutation
);


/**
 * @brief Gets the number of failed tests against a mutation.
 *
 * @param mutation Mutation case.
 *
 * @return Number of failed tests.
 */
FOSSIL_MAIP_API size_t
fossil_mutate_failures(
    const fossil_mutation_t* mutation
);


/*
 * Mutation Comparison
 */

/**
 * @brief Compares original and mutated source.
 *
 * @param mutation Mutation case.
 *
 * @return true if the mutation changes the source, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_changed(
    const fossil_mutation_t* mutation
);


/**
 * @brief Determines whether two mutation cases are equivalent.
 *
 * @param first First mutation.
 * @param second Second mutation.
 *
 * @return true if equivalent, false otherwise.
 */
FOSSIL_MAIP_API bool
fossil_mutate_compare(
    const fossil_mutation_t* first,
    const fossil_mutation_t* second
);


/*
 * *****************************************************************************
 * Private API Macros
 * *****************************************************************************
 */

/**
 * @brief Creates a mutation context.
 *
 * @return Mutation context, or NULL on failure.
 */
#define _FOSSIL_MUTATE_CREATE() \
    fossil_mutate_create()

/**
 * @brief Destroys a mutation context.
 *
 * @param mutate Mutation context.
 */
#define _FOSSIL_MUTATE_DESTROY(mutate) \
    fossil_mutate_destroy(mutate)

/**
 * @brief Clears all mutations from a mutation context.
 *
 * @param mutate Mutation context.
 */
#define _FOSSIL_MUTATE_CLEAR(mutate) \
    fossil_mutate_clear(mutate)

/**
 * @brief Creates a mutation case.
 *
 * @param mutate Mutation context.
 * @param id String identifier for the mutation.
 *
 * @return Mutation case, or NULL on failure.
 */
#define _FOSSIL_MUTATE_CREATE_CASE(mutate, id) \
    fossil_mutate_create_case(mutate, id)

/**
 * @brief Destroys a mutation case.
 *
 * @param mutation Mutation case.
 */
#define _FOSSIL_MUTATE_DESTROY_CASE(mutation) \
    fossil_mutate_destroy_case(mutation)

/**
 * @brief Creates a mutation target.
 *
 * A mutation target identifies the source location to be mutated.
 *
 * @param mutation Mutation case.
 * @param file Source file.
 * @param line Source line.
 * @param column Source column.
 *
 * @return Mutation target, or NULL on failure.
 */
#define _FOSSIL_MUTATE_CREATE_TARGET(mutation, file, line, column) \
    fossil_mutate_create_target(mutation, file, line, column)

/**
 * @brief Creates a mutation opr.
 *
 * @param id String identifier for the opr.
 * @param type Operator type.
 *
 * @return Mutation opr, or NULL on failure.
 */
#define _FOSSIL_MUTATE_CREATE_OPERATOR(id, type) \
    fossil_mutate_create_operator(id, type)

/**
 * @brief Applies a mutation opr to a mutation target.
 *
 * This function prepares the mutated representation. It does not execute
 * the Fossil Test runner.
 *
 * @param mutation Mutation case.
 * @param target Mutation target.
 * @param opr Mutation opr.
 *
 * @return true on success, false on failure.
 */
#define _FOSSIL_MUTATE_APPLY(mutation, target, opr) \
    fossil_mutate_apply(mutation, target, opr)

/**
 * @brief Restores the original mutation state.
 *
 * @param mutation Mutation case.
 *
 * @return true on success, false on failure.
 */
#define _FOSSIL_MUTATE_RESET(mutation) \
    fossil_mutate_reset(mutation)

/**
 * @brief Validates whether a mutation can be applied.
 *
 * @param mutation Mutation case.
 *
 * @return true if valid, false otherwise.
 */
#define _FOSSIL_MUTATE_VALIDATE(mutation) \
    fossil_mutate_validate(mutation)


#define _FOSSIL_MUTATE_KILLED(mutation) \
    (fossil_mutate_is_applied(mutation) && \
     strcmp(fossil_mutate_status(mutation), FOSSIL_MUTATE_STATUS_KILLED) == 0)

/*
 * *****************************************************************************
 * Public API Macros
 * *****************************************************************************
 */

/**
 * @brief Creates a mutation context.
 *
 * @return Mutation context, or NULL on failure.
 */
#define FOSSIL_MUTATE_CREATE() \
    _FOSSIL_MUTATE_CREATE()

/**
 * @brief Destroys a mutation context.
 *
 * @param mutate Mutation context.
 */
#define FOSSIL_MUTATE_DESTROY(mutate) \
    _FOSSIL_MUTATE_DESTROY(mutate)

/**
 * @brief Clears all mutations from a mutation context.
 *
 * @param mutate Mutation context.
 */
#define FOSSIL_MUTATE_CLEAR(mutate) \
    _FOSSIL_MUTATE_CLEAR(mutate)

/**
 * @brief Creates a mutation case.
 *
 * @param mutate Mutation context.
 * @param id String identifier for the mutation.
 *
 * @return Mutation case, or NULL on failure.
 */
#define FOSSIL_MUTATE_CREATE_CASE(mutate, id) \
    _FOSSIL_MUTATE_CREATE_CASE(mutate, id)

/**
 * @brief Destroys a mutation case.
 *
 * @param mutation Mutation case.
 */
#define FOSSIL_MUTATE_DESTROY_CASE(mutation) \
    _FOSSIL_MUTATE_DESTROY_CASE(mutation)

/**
 * @brief Creates a mutation target.
 *
 * A mutation target identifies the source location to be mutated.
 *
 * @param mutation Mutation case.
 * @param file Source file.
 * @param line Source line.
 * @param column Source column.
 *
 * @return Mutation target, or NULL on failure.
 */
#define FOSSIL_MUTATE_CREATE_TARGET(mutation, file, line, column) \
    _FOSSIL_MUTATE_CREATE_TARGET(mutation, file, line, column)

/**
 * @brief Creates a mutation opr.
 *
 * @param id String identifier for the opr.
 * @param type Operator type.
 *
 * @return Mutation opr, or NULL on failure.
 */
#define FOSSIL_MUTATE_CREATE_OPERATOR(id, type) \
    _FOSSIL_MUTATE_CREATE_OPERATOR(id, type)

/**
 * @brief Applies a mutation opr to a mutation target.
 *
 * This function prepares the mutated representation. It does not execute
 * the Fossil Test runner.
 *
 * @param mutation Mutation case.
 * @param target Mutation target.
 * @param opr Mutation opr.
 *
 * @return true on success, false on failure.
 */
#define FOSSIL_MUTATE_APPLY(mutation, target, opr) \
    _FOSSIL_MUTATE_APPLY(mutation, target, opr)

/**
 * @brief Restores the original mutation state.
 *
 * @param mutation Mutation case.
 *
 * @return true on success, false on failure.
 */
#define FOSSIL_MUTATE_RESET(mutation) \
    _FOSSIL_MUTATE_RESET(mutation)

/**
 * @brief Validates whether a mutation can be applied.
 *
 * @param mutation Mutation case.
 * @return true if valid, false otherwise.
 */
#define FOSSIL_MUTATE_VALIDATE(mutation) \
    _FOSSIL_MUTATE_VALIDATE(mutation)

#define FOSSIL_MUTATE_KILLED(mutation) \
    _FOSSIL_MUTATE_KILLED(mutation)

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_MUTATE_H */
