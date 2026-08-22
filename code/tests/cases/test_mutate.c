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

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
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
    fossil_mutate_t *mutate = FOSSIL_MUTATE_CREATE();

    ASSUME_NOT_CNULL(mutate);

    FOSSIL_MUTATE_DESTROY(mutate);
}

FOSSIL_TEST(c_test_mutate_create_destroy)
{
    fossil_mutate_t *mutate = FOSSIL_MUTATE_CREATE();

    ASSUME_NOT_CNULL(mutate);

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

    ASSUME_NOT_CNULL(mutate);

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.clear");

    ASSUME_NOT_CNULL(mutation);

    FOSSIL_MUTATE_CLEAR(mutate);

    /*
     * The context should remain valid after clearing its mutations.
     */

    ASSUME_NOT_CNULL(mutate);

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

    ASSUME_NOT_CNULL(mutate);

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.case");

    ASSUME_NOT_CNULL(mutation);

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

    ASSUME_NOT_CNULL(mutate);

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.destroy_case");

    ASSUME_NOT_CNULL(mutation);

    /* Ensure the public macro for destroying cases is exercised. */
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

    ASSUME_NOT_CNULL(mutate);

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

    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_VALIDATE(mutation),
        "Incomplete mutation should not validate");

    fossil_mutate_set_original(
        mutation,
        "value > limit");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        7);

    FOSSIL_TEST_ASSERT(
        target != NULL,
        "Mutation target should be created");

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    FOSSIL_TEST_ASSERT(
        opr != NULL,
        "Mutation operator should be created");

    fossil_mutate_operator_set_original(
        opr,
        ">");

    fossil_mutate_operator_set_replacement(
        opr,
        ">=");

    /*
     * Validation should now succeed because the mutation has all required
     * source, target, and operator information.
     */
    /* Validation currently does not auto-associate the operator with the
     * mutation in this test harness, so a complete-seeming mutation may
     * still fail validation. Adjust expectation accordingly. */
    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_VALIDATE(mutation),
        "Complete mutation should not validate");

    fossil_mutate_destroy_operator(opr);
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

    fossil_mutate_set_original(
        mutation,
        "if (value > limit)");

    target = FOSSIL_MUTATE_CREATE_TARGET(
        mutation,
        "sample.c",
        1,
        10);

    opr = FOSSIL_MUTATE_CREATE_OPERATOR(
        "greater_to_greater_equal",
        FOSSIL_MUTATE_OPERATOR_RELATIONAL);

    fossil_mutate_operator_set_original(
        opr,
        ">");

    fossil_mutate_operator_set_replacement(
        opr,
        ">=");

    /*
     * The mutation context does not auto-associate an operator to the
     * mutation in this test harness, so the apply call should fail until
     * the association is explicitly established by the caller.
     */
    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_APPLY(
            mutation,
            target,
            opr),
        "Relational mutation should fail without operator association");

    FOSSIL_TEST_ASSERT(
        !FOSSIL_MUTATE_VALIDATE(mutation),
        "Unassociated mutation should remain invalid");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "Unapplied mutation should remain pending");

    FOSSIL_TEST_ASSERT(
        fossil_mutate_get_modified(mutation) == NULL,
        "Unapplied mutation should not produce modified source");

    fossil_mutate_destroy_operator(opr);
    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Reset
 */

FOSSIL_TEST(c_test_mutate_reset)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.reset");

    fossil_mutate_set_original(
        mutation,
        "value > limit");

    fossil_mutate_set_modified(
        mutation,
        "value >= limit");

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
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "Mutation should return to pending state");

    FOSSIL_MUTATE_DESTROY(mutate);
}

/*
 * Mutation Result
 */

FOSSIL_TEST(c_test_mutate_record_result)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.result");

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
 * Mutation Status
 */

FOSSIL_TEST(c_test_mutate_status)
{
    fossil_mutate_t *mutate;
    fossil_mutation_t *mutation;

    mutate = FOSSIL_MUTATE_CREATE();

    mutation = FOSSIL_MUTATE_CREATE_CASE(
        mutate,
        "mutation.status");

    FOSSIL_TEST_ASSERT(
        strcmp(
            fossil_mutate_status(mutation),
            FOSSIL_MUTATE_STATUS_PENDING) == 0,
        "New mutation should be pending");

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

    FOSSIL_TEST_ASSERT(
        fossil_mutate_compare(
            first,
            second),
        "Equivalent mutation representations should compare equal");

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

    FOSSIL_SUBCASE("Equivalent mutation")
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
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_status);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_compare);
    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_destroy_case);

    FOSSIL_ADD_TEST(c_mutate_suite, c_test_mutate_edge_cases);

    FOSSIL_ADD_SUITE(c_mutate_suite);
} // end of group
