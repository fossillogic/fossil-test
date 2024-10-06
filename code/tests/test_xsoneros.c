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
#include <fossil/unittest/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_DATA(sample_block) {
    int x;
    int y;
} sample_block;

// Fixture setup and teardown procedures
FOSSIL_FEATURE(sample_feature);

FOSSIL_SETUP(sample_feature) {
    sample_block.x = 42;
    sample_block.y = 20;
} // end of setup

FOSSIL_TEARDOWN(sample_feature) {
    // Teardown code goes here
} // end of teardown

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_SONERO(xbdd_logic_within_feature_test) {
    GIVEN("a valid statement is passed") {
        // Set up the context
        bool givenExecuted = true;

        WHEN("a statement is true") {
            // Perform the login action
            bool whenExecuted = true;
            
            THEN("we validate everything was worked") {
                // Check the expected outcome
                bool thenExecuted = true;

                TEST_EXPECT(givenExecuted, "Given statement should have executed");
                TEST_EXPECT(whenExecuted, "When statement should have executed");
                TEST_EXPECT(thenExecuted, "Then statement should have executed");
            }
        }
    }
} // end of case

FOSSIL_SONERO(xbdd_user_account_within_feature) {
    GIVEN("a user's account with sufficient balance") {
        // Set up the context
        float accountBalance = 500.0;
        float withdrawalAmount = 200.0;

        WHEN("the user requests a withdrawal of $200") {
            // Perform the withdrawal action
            if (accountBalance >= withdrawalAmount) {
                accountBalance -= withdrawalAmount;
            } // end if
            THEN("the withdrawal amount should be deducted from the account balance") {
                // Check the expected outcome

                // Simulate the scenario
                float compareBalance = 500.0;
                TEST_EXPECT(accountBalance == (compareBalance - withdrawalAmount), "Account balance should have been deducted by $200");
            }
        }
    }
} // end of case

FOSSIL_SONERO(xbdd_empty_cart_within_feature) {
    GIVEN("a user with an empty shopping cart") {
        // Set up the context
        int cartItemCount = 0;

        WHEN("the user adds a product to the cart") {
            // Perform the action of adding a product

            THEN("the cart item count should increase by 1") {
                // Check the expected outcome
                cartItemCount++;

                TEST_EXPECT(cartItemCount == 1, "Cart item count should have increased by 1");
            }
        }
    }
} // end of case

FOSSIL_SONERO(xbdd_valid_login_within_feature) {
    GIVEN("a registered user with valid credentials") {
        // Set up the context
        const char* validUsername = "user123";
        const char* validPassword = "pass456";

        WHEN("the user provides correct username and password") {
            // Perform the action of user login
            const char* inputUsername = "user123";
            const char* inputPassword = "pass456";

            THEN("the login should be successful") {
                // Check the expected outcome
                // Simulate login validation
                TEST_EXPECT(strcmp(inputUsername, validUsername) == 0, "Username should match");
                TEST_EXPECT(strcmp(inputPassword, validPassword) == 0, "Password should match");
            }
        }

        WHEN("the user provides incorrect password") {
            // Perform the action of user login
            const char* inputUsername = "user123";
            const char* inputPassword = "wrongpass";

            THEN("the login should fail with an error message") {
                // Check the expected outcome
                // Simulate login validation
                TEST_EXPECT(strcmp(inputUsername, validUsername) == 0, "Username should match");
                TEST_EXPECT(strcmp(inputPassword, validPassword) != 0, "Password should not match");
            }
        }
    }
} // end of case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(feature_test_group) {
    ADD_TESTF(xbdd_logic_within_feature_test, sample_feature);
    ADD_TESTF(xbdd_user_account_within_feature, sample_feature);
    ADD_TESTF(xbdd_empty_cart_within_feature, sample_feature);
    ADD_TESTF(xbdd_valid_login_within_feature, sample_feature);
} // end of group
