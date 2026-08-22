/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/maip/framework.h>

#include <string.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_SETUP(c_mutate_suite)
{
    /* Mutation setup */
}

FOSSIL_TEARDOWN(c_mutate_suite)
{
    /* Mutation teardown */
}

FOSSIL_SUITE(c_mutate_suite);

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

/*
 * Create / Destroy Context
 */

FOSSIL_TEST(c_test_mutate_create)
{
    fossil_mutate_t *mutate;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    FOSSIL_MUTATE_DESTROY(mutate);
}

FOSSIL_TEST(c_test_mutate_create_destroy)
{
    fossil_mutate_t *mutate;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Clear Context
 */

FOSSIL_TEST(c_test_mutate_clear)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.clear");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_MUTATE_CLEAR(mutate);

    /*
     * The context should remain valid after clearing its mutations.
     */

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should remain valid after clear");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Create Mutation Case
 */

FOSSIL_TEST(c_test_mutate_create_case)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.case");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_id(mutation),
            "mutation.case") == 0,
        "Mutation ID should match");

    FOSSIL_MUTATE_DESTROY(mutate);
}

FOSSIL_TEST(c_test_mutate_destroy_case)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.destroy_case");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_MUTATE_DESTROY_CASE(mutation);

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Create Mutation Target
 */

FOSSIL_TEST(c_test_mutate_create_target)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;

    mutate = FOSSIL_MUTATE_CREATE();

    FOSSIL_TEST_ASSERT(
        mutate != NULL,
        "Mutation context should be created");

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.target");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        10,
        5);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_target_file(target),
            "sample.c") == 0,
        "Mutation target file should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_target_line(target) == 10,
        "Mutation target line should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_target_column(target) == 5,
        "Mutation target column should match");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Target Setters
 */

FOSSIL_TEST(c_test_mutate_target_setters)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.target.set");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "original.c",
        1,
        1);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_target_file(
            target,
            "modified.c"),
        "Target file should be updated");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_target_line(
            target,
            25),
        "Target line should be updated");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_target_column(
            target,
            12),
        "Target column should be updated");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_target_file(target),
            "modified.c") == 0,
        "Updated target file should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_target_line(target) == 25,
        "Updated target line should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_target_column(target) == 12,
        "Updated target column should match");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Name / Description
 */

FOSSIL_TEST(c_test_mutate_case_metadata)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.metadata");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_name(
            mutation,
            "Greater Than Mutation"),
        "Mutation name should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_description(
            mutation,
            "Changes greater-than comparison to greater-than-or-equal"),
        "Mutation description should be set");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_name(mutation),
            "Greater Than Mutation") == 0,
        "Mutation name should match");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_description(mutation),
            "Changes greater-than comparison to greater-than-or-equal") == 0,
        "Mutation description should match");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Operator
 */

FOSSIL_TEST(c_test_mutate_create_operator)
{
    fossil_mutate_operator_t *opr;

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_operator_id(opr),
            "greater_to_greater_equal") == 0,
        "Operator ID should match");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_operator_type(opr),
            FOSSIL_MUTATE_OPERATOR_RELATIONAL) == 0,
        "Operator type should match");

    fossil_mutate_destroy_operator(opr);
}

/*
 * Operator Values
 */

FOSSIL_TEST(c_test_mutate_operator_values)
{
    fossil_mutate_operator_t *opr;

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_original(
            opr,
            ">"),
        "Original operator should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_replacement(
            opr,
            ">="),
        "Replacement operator should be set");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_operator_original(opr),
            ">") == 0,
        "Original operator should match");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_operator_replacement(opr),
            ">=") == 0,
        "Replacement operator should match");

    fossil_mutate_destroy_operator(opr);
}

/*
 * Original / Modified Source
 */

FOSSIL_TEST(c_test_mutate_source)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.source");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            mutation,
            "if (value > limit)"),
        "Original source should be set");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_original(mutation),
            "if (value > limit)") == 0,
        "Original source should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_modified(
            mutation,
            "if (value >= limit)"),
        "Modified source should be set");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_modified(mutation),
            "if (value >= limit)") == 0,
        "Modified source should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_changed(mutation),
        "Mutation should report changed source");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Validation
 */

FOSSIL_TEST(c_test_mutate_validate)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.validate");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    /*
     * A newly created mutation is incomplete.
     */

    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_VALIDATE(mutation),
        "Incomplete mutation should not validate");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            mutation,
            "if (value > limit)"),
        "Original source should be set");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        11);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_original(
            opr,
            ">"),
        "Operator original value should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_replacement(
            opr,
            ">="),
        "Operator replacement value should be set");

    /*
     * The target belongs to the mutation, but the operator has not yet
     * been applied and associated with it.
     */

    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_VALIDATE(mutation),
        "Mutation without an associated operator should not validate");

    /*
     * Applying the operator establishes the complete mutation state.
     */

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Complete mutation should apply successfully");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_VALIDATE(mutation),
        "Applied mutation should validate");

    /*
     * The mutation now owns its target and operator.
     */

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Apply Relational Mutation
 */

FOSSIL_TEST(c_test_mutate_apply_relational)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.relational");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            mutation,
            "if (value > limit)"),
        "Original source should be set");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        11);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_original(
            opr,
            ">"),
        "Operator original value should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_replacement(
            opr,
            ">="),
        "Operator replacement value should be set");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Relational mutation should apply successfully");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_is_applied(mutation),
        "Mutation should report applied status");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_APPLIED) == 0,
        "Mutation status should be applied");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_modified(mutation) != NULL,
        "Applied mutation should produce modified source");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_get_modified(mutation),
            "if (value >= limit)") == 0,
        "Modified source should contain the relational mutation");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_changed(mutation),
        "Applied mutation should report changed source");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_VALIDATE(mutation),
        "Applied mutation should validate");

    /*
     * The mutation owns target and operator after apply.
     */

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Reset
 */

FOSSIL_TEST(c_test_mutate_reset)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.reset");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            mutation,
            "if (value > limit)"),
        "Original source should be set");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        11);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_original(
            opr,
            ">"),
        "Operator original value should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_replacement(
            opr,
            ">="),
        "Operator replacement value should be set");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Mutation should apply successfully");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_changed(mutation),
        "Mutation should initially be changed");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_RESET(mutation),
        "Mutation should reset successfully");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_modified(mutation) == NULL,
        "Modified source should be cleared after reset");

    FOSSIL_TEST_ASSERT(
        !fossil_mutate_is_applied(mutation),
        "Mutation should no longer be applied after reset");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "Mutation should return to pending state");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_tests(mutation) == 0,
        "Mutation test count should reset");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_failures(mutation) == 0,
        "Mutation failure count should reset");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Result
 */

FOSSIL_TEST(c_test_mutate_record_result)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.result");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            mutation,
            "if (value > limit)"),
        "Original source should be set");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        11);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_original(
            opr,
            ">"),
        "Operator original value should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_operator_set_replacement(
            opr,
            ">="),
        "Operator replacement value should be set");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Mutation should apply before recording a result");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_record_result(
            mutation,
            FOSSIL_MUTATE_STATUS_KILLED,
            10,
            1),
        "Mutation result should be recorded");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_is_killed(mutation),
        "Mutation should report killed status");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_tests(mutation) == 10,
        "Mutation test count should match");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_failures(mutation) == 1,
        "Mutation failure count should match");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Invalid Mutation Result
 */

FOSSIL_TEST(c_test_mutate_invalid_result)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.invalid_result");

    FOSSIL_TEST_ASSERT(
        mutation != NULL,
        "Mutation case should be created");

    /*
     * A pending mutation cannot receive an execution result.
     */

    FOSSIL_TEST_ASSERT(
        !fossil_mutate_record_result(
            mutation,
            FOSSIL_MUTATE_STATUS_KILLED,
            10,
            1),
        "Pending mutation should not accept a result");

    /*
     * Failures cannot exceed executed tests.
     */

    FOSSIL_TEST_ASSERT(
        !fossil_mutate_record_result(
            mutation,
            FOSSIL_MUTATE_STATUS_KILLED,
            1,
            2),
        "Failures should not exceed test count");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "Invalid result attempts should leave mutation pending");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Status
 */

FOSSIL_TEST(c_test_mutate_status)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;
    fossil_mutate_target_t *target;
    fossil_mutate_operator_t *opr;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.status");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "New mutation should be pending");

    fossil_mutate_set_original(
        mutation,
        "if (value > limit)");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        11);

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    fossil_mutate_operator_set_original(
        opr,
        ">");

    fossil_mutate_operator_set_replacement(
        opr,
        ">=");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Mutation should apply before recording status");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_record_result(
            mutation,
            FOSSIL_MUTATE_STATUS_SURVIVED,
            5,
            0),
        "Mutation survived result should be recorded");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_is_survived(mutation),
        "Mutation should report survived");

    FOSSIL_TEST_ASSERT(
        !fossil_mutate_is_killed(mutation),
        "Surviving mutation should not report killed");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Comparison
 */

FOSSIL_TEST(c_test_mutate_compare)
{
    fossil_mutate_t *mutate;

    fossil_mutation_t *first;
    fossil_mutation_t *second;

    mutate = FOSSIL_MUTATE_CREATE();

    first = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.compare");

    second = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.compare");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            first,
            "if (value > limit)"),
        "First original source should be set");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_set_original(
            second,
            "if (value > limit)"),
        "Second original source should be set");

    /*
     * Create matching targets.
     */

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_CREATE_TARGET(
            first,
            "sample.c",
            1,
            11) != NULL,
        "First target should be created");

    FOSSIL_TEST_ASSERT(
        FOSSIL_MUTATE_CREATE_TARGET(
            second,
            "sample.c",
            1,
            11) != NULL,
        "Second target should be created");

    /*
     * Create matching operators.
     */

    {
        fossil_mutate_operator_t *first_opr;
        fossil_mutate_operator_t *second_opr;

        first_opr = FOSSIL_MUTATE_CREATE_OPERATOR(
            "greater_to_greater_equal",
            FOSSIL_MUTATE_OPERATOR_RELATIONAL);

        second_opr = FOSSIL_MUTATE_CREATE_OPERATOR(
            "greater_to_greater_equal",
            FOSSIL_MUTATE_OPERATOR_RELATIONAL);

        FOSSIL_TEST_ASSERT(
            first_opr != NULL,
            "First operator should be created");

        FOSSIL_TEST_ASSERT(
            second_opr != NULL,
            "Second operator should be created");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_operator_set_original(
                first_opr,
                ">"),
            "First operator original should be set");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_operator_set_replacement(
                first_opr,
                ">="),
            "First operator replacement should be set");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_operator_set_original(
                second_opr,
                ">"),
            "Second operator original should be set");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_operator_set_replacement(
                second_opr,
                ">="),
            "Second operator replacement should be set");

        FOSSIL_TEST_ASSERT(
            FOSSIL_MUTATE_APPLY(
                first,
                first->target,
                first_opr),
            "First mutation should apply");

        FOSSIL_TEST_ASSERT(
            FOSSIL_MUTATE_APPLY(
                second,
                second->target,
                second_opr),
            "Second mutation should apply");
    }

    FOSSIL_TEST_ASSERT(
        fossil_mutate_compare(
            first,
            second),
        "Equivalent mutation cases should compare equal");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Comparison Identity
 */

FOSSIL_TEST(c_test_mutate_compare_identity)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *first;
    fossil_mutation_t *second;

    mutate = FOSSIL_MUTATE_CREATE();

    first = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.first");

    second = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.second");

    fossil_mutate_set_original(
        first,
        "value > limit");

    fossil_mutate_set_modified(
        first,
        "value >= limit");

    fossil_mutate_set_original(
        second,
        "value > limit");

    fossil_mutate_set_modified(
        second,
        "value >= limit");

    /*
     * The source transformation is identical, but the mutation identities
     * differ. A stronger comparison must therefore reject them.
     */

    FOSSIL_TEST_ASSERT(
        !fossil_mutate_compare(
            first,
            second),
        "Different mutation identities should not compare equal");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Subcases
 */

FOSSIL_TEST(c_test_mutate_edge_cases)
{
    FOSSIL_SUBCASE("Pending mutation")
    {
        fossil_mutate_t *mutate;
        fossil_mutation_t *mutation;

        mutate = FOSSIL_MUTATE_CREATE();

        mutation = FOSSIL_MUTATE_CREATE_CASE(
            mutate,
            "mutation.pending");

        FOSSIL_TEST_ASSERT(
            mutation != NULL,
            "Pending mutation should be created");

        FOSSIL_TEST_ASSERT(
            strcmp(
                fossil_mutate_status(mutation),
                FOSSIL_MUTATE_STATUS_PENDING) == 0,
            "New mutation should be pending");

        FOSSIL_TEST_ASSERT(
            !fossil_mutate_is_applied(mutation),
            "New mutation should not be applied");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_tests(mutation) == 0,
            "New mutation should have zero tests");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_failures(mutation) == 0,
            "New mutation should have zero failures");

        FOSSIL_MUTATE_DESTROY(mutate);
    }

    FOSSIL_SUBCASE("Invalid mutation")
    {
        fossil_mutate_t *mutate;
        fossil_mutation_t *mutation;

        mutate = FOSSIL_MUTATE_CREATE();

        mutation = FOSSIL_MUTATE_CREATE_CASE(
            mutate,
            "mutation.invalid");

        FOSSIL_TEST_ASSERT(
            !FOSSIL_MUTATE_VALIDATE(mutation),
            "Incomplete mutation should be invalid");

        FOSSIL_MUTATE_DESTROY(mutate);
    }

    FOSSIL_SUBCASE("Equivalent source")
    {
        fossil_mutate_t *mutate;
        fossil_mutation_t *mutation;

        mutate = FOSSIL_MUTATE_CREATE();

        mutation = FOSSIL_MUTATE_CREATE_CASE(
            mutate,
            "mutation.equivalent");

        fossil_mutate_set_original(
            mutation,
            "value > limit");

        fossil_mutate_set_modified(
            mutation,
            "value > limit");

        FOSSIL_TEST_ASSERT(
            !fossil_mutate_changed(mutation),
            "Equivalent source should not report a change");

        FOSSIL_MUTATE_DESTROY(mutate);
    }

    FOSSIL_SUBCASE("Reset result state")
    {
        fossil_mutate_t *mutate;
        fossil_mutation_t *mutation;
        fossil_mutate_target_t *target;
        fossil_mutate_operator_t *opr;

        mutate = FOSSIL_MUTATE_CREATE();

        mutation = FOSSIL_MUTATE_CREATE_CASE(
            mutate,
            "mutation.reset_state");

        fossil_mutate_set_original(
            mutation,
            "if (value > limit)");

        target = FOSSIL_MUTATE_CREATE_TARGET(
            mutation,
            "sample.c",
            1,
            11);

        opr = FOSSIL_MUTATE_CREATE_OPERATOR(
            "greater_to_greater_equal",
            FOSSIL_MUTATE_OPERATOR_RELATIONAL);

        fossil_mutate_operator_set_original(
            opr,
            ">");

        fossil_mutate_operator_set_replacement(
            opr,
            ">=");

        FOSSIL_TEST_ASSERT(
            FOSSIL_MUTATE_APPLY(
                mutation,
                target,
                opr),
            "Mutation should apply");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_record_result(
                mutation,
                FOSSIL_MUTATE_STATUS_KILLED,
                10,
                2),
            "Mutation result should be recorded");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_tests(mutation) == 10,
            "Mutation should contain recorded test count");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_failures(mutation) == 2,
            "Mutation should contain recorded failure count");

        FOSSIL_TEST_ASSERT(
            FOSSIL_MUTATE_RESET(mutation),
            "Mutation should reset");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_tests(mutation) == 0,
            "Reset should clear test count");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_failures(mutation) == 0,
            "Reset should clear failure count");

        FOSSIL_TEST_ASSERT(
            fossil_mutate_get_modified(mutation) == NULL,
            "Reset should clear modified source");

        FOSSIL_MUTATE_DESTROY(mutate);
    }
}

/*
 * *****************************************************************************
 * Test Group
 * *****************************************************************************
 */

FOSSIL_TEST_GROUP(c_mutate_test_cases)
{
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_create);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_create_destroy);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_clear);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_create_case);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_destroy_case);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_create_target);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_target_setters);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_case_metadata);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_create_operator);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_operator_values);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_source);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_validate);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_apply_relational);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_reset);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_record_result);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_invalid_result);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_status);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_compare);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_compare_identity);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_edge_cases);

    FOSSIL_ADD_SUITE(c_mutate_suite);
}
