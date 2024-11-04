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
#include <fossil/test/framework.h>

FOSSIL_TEST_EXPORT(sample_test_group);

int main(void) {
    FOSSIL_TEST_START();

    FOSSIL_TEST_IMPORT(sample_test_group);

    FOSSIL_TEST_RUN();

    FOSSIL_TEST_SUMMARY();
    FOSSIL_TEST_END();
} // end of macro