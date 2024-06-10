/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include "fossil/unittest/feature.h"
#include "fossil/unittest/internal.h"
#include <stdarg.h>

// ==============================================================================
// Xtest internal handlers for tags and markers
// ==============================================================================

void _fossil_test_assert_handle_tag_slow(fossil_test_t* test_case) {
    clock_t end = clock();
    test_case->timer.elapsed = end - test_case->timer.start;
    test_case->timer.detail.milliseconds = (int64_t)((test_case->timer.elapsed - (int64_t)test_case->timer.elapsed) * 1000);

    if (test_case->timer.detail.milliseconds > MAX_EXPECTED_TIME_SLOW) {
        fossil_test_cout("red", "Test case exceeded the expected time for slow tag\n");
        _fossil_test_env.rule.should_timeout = false;
        _fossil_test_env.rule.should_pass    = false;
    }
}

void _fossil_test_assert_handle_tag_fast(fossil_test_t* test_case) {
    clock_t end = clock();
    test_case->timer.elapsed = end - test_case->timer.start;
    test_case->timer.detail.milliseconds = (int64_t)((test_case->timer.elapsed - (int64_t)test_case->timer.elapsed) * 1000);

    if (test_case->timer.detail.milliseconds > MAX_EXPECTED_TIME_FAST) {
        fossil_test_cout("red", "Test case exceeded the expected time for fast tag\n");
        _fossil_test_env.rule.should_timeout = false;
        _fossil_test_env.rule.should_pass    = false;
    }
}

// features to be added in a next release.
void _fossil_test_assert_handle_tag_bug(fossil_test_t* test_case) {
    // Handle bug tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_feature(fossil_test_t* test_case) {
    // Handle feature tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_security(fossil_test_t* test_case) {
    // Handle security tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_performance(fossil_test_t* test_case) {
    // Handle performance tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_stress(fossil_test_t* test_case) {
    // Handle stress tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_regression(fossil_test_t* test_case) {
    // Handle regression tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_compatibility(fossil_test_t* test_case) {
    // Handle compatibility tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_usability(fossil_test_t* test_case) {
    // Handle usability tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_robustness(fossil_test_t* test_case) {
    // Handle robustness tag logic here
    (void)test_case;
}

void _fossil_test_assert_handle_tag_corner_case(fossil_test_t* test_case) {
    // Handle corner case tag logic here
    (void)test_case;
}

// ==============================================================================
// Xtest basic utility functions
// ==============================================================================

void _fossil_test_assume_unit_apply_xtags(fossil_test_t* test_case) {
     if (strcmp(test_case->tags->name, "default") != 0) {
        if (strcmp(test_case->tags->name, "bug") == 0) {
            _fossil_test_assert_handle_tag_bug(test_case);
        } else if (strcmp(test_case->tags->name, "feature") == 0) {
            _fossil_test_assert_handle_tag_feature(test_case);
        } else if (strcmp(test_case->tags->name, "security") == 0) {
            _fossil_test_assert_handle_tag_security(test_case);
        } else if (strcmp(test_case->tags->name, "performance") == 0) {
            _fossil_test_assert_handle_tag_performance(test_case);
        } else if (strcmp(test_case->tags->name, "stress") == 0) {
            _fossil_test_assert_handle_tag_stress(test_case);
        } else if (strcmp(test_case->tags->name, "regression") == 0) {
            _fossil_test_assert_handle_tag_regression(test_case);
        } else if (strcmp(test_case->tags->name, "compatibility") == 0) {
            _fossil_test_assert_handle_tag_compatibility(test_case);
        } else if (strcmp(test_case->tags->name, "usability") == 0) {
            _fossil_test_assert_handle_tag_usability(test_case);
        } else if (strcmp(test_case->tags->name, "robustness") == 0) {
            _fossil_test_assert_handle_tag_robustness(test_case);
        } else if (strcmp(test_case->tags->name, "corner case") == 0) {
            _fossil_test_assert_handle_tag_corner_case(test_case);
        }
    }
}

void _fossil_test_assume_unit_apply_marks(fossil_test_t* test_case) {
    if (strcmp(test_case->marks->name, "default") != 0) {
        if (strcmp(test_case->marks->name, "skip") == 0) {
            _fossil_test_env.rule.skipped = true;
        } else if (strcmp(test_case->marks->name, "fail") == 0) {
            _fossil_test_env.rule.result = false;
            _xassert_info.should_fail = true; // based on rules applyed from 'fail' mark
        } else if (strcmp(test_case->marks->name, "pass") == 0) {
            _fossil_test_env.rule.result = true;
        } else if (strcmp(test_case->marks->name, "timeout") == 0) {
            _fossil_test_env.rule.timeout = true;
            _fossil_test_env.rule.timeout = true;
        } else if (strcmp(test_case->marks->name, "error") == 0) {
            _fossil_test_env.rule.error = true;
        } else if (strcmp(test_case->marks->name, "none") == 0) {
            // Do nothing
        } else if (strcmp(test_case->marks->name, "only") == 0) {
            // Do nothing
        }
    }
}

void _fossil_test_assume_unit_check_xtags(fossil_test_t* test_case) {
    if (strcmp(test_case->tags->name, "default") != 0) {
        if (strcmp(test_case->tags->name, "fast") == 0) {
            _fossil_test_assert_handle_tag_fast(test_case);
        } else if (strcmp(test_case->tags->name, "slow") == 0) {
            _fossil_test_assert_handle_tag_slow(test_case);
        }
    }
}

void _fossil_test_assume_unit(fossil_test_t* test_case) {
    if (test_case->fixture.setup) {
        test_case->fixture.setup();
    }

    for (uint8_t iter = 0; iter < xcli.iter_repeat; iter++) {
        test_case->test_function();
    }

    if (test_case->fixture.teardown) {
        test_case->fixture.teardown();
    }
}

void _fossil_test_assume_unit_runner(fossil_test_t* test_case) {
    test_case->timer.start = clock();
    output_start_test(test_case, &_fossil_test_env);

    // setting and restting the assert info
    _xassert_info.has_assert  = false; // Never assume the tester added an assert EVER!
    _xassert_info.expression  = true;  // Assume the expression is true until proven false
    _xassert_info.should_fail = false; // Assume the expression should pass until proven false

    _fossil_test_assume_unit_apply_marks(test_case);
    _fossil_test_assume_unit_apply_xtags(test_case);

    if (!_fossil_test_env.rule.skipped) {
        if (!xcli.dry_run) {
            _fossil_test_assume_unit(test_case);
        } else {
            fossil_test_cout("blue", "Simulating test case...\n");
        }
        _fossil_test_assume_unit_check_xtags(test_case); // Check tags
    }

    output_end_test(test_case);
    _fossil_test_scoreboard(&_fossil_test_env, test_case);
}

// ==============================================================================
// Xtest functions for markers and tags
// ==============================================================================

// Function to apply priority to the test case based on a keyword
void _fossil_test_apply_priority(fossil_test_t *test_case, char* priority) {
    if (!test_case) {
        fossil_test_cout("red", "Error: Test case pointer is xnullptr\n");
        return;
    } else if (!priority) {
        fossil_test_cout("red", "Error: Invalid priority\n");
        return;
    }

    if (strcmp(priority, "lowest") == 0) {
        test_case->priority = 0;
    } else if (strcmp(priority, "very low") == 0) {
        test_case->priority = 10;
    } else if (strcmp(priority, "low") == 0) {
        test_case->priority = 20;
    } else if (strcmp(priority, "medium") == 0) {
        test_case->priority = 50;
    } else if (strcmp(priority, "high") == 0) {
        test_case->priority = 70;
    } else if (strcmp(priority, "very high") == 0) {
        test_case->priority = 90;
    } else if (strcmp(priority, "highest") == 0) {
        test_case->priority = 100;
    } else if (strcmp(priority, "urgent") == 0) {
        test_case->priority = 95;
    } else if (strcmp(priority, "critical") == 0) {
        test_case->priority = 100;
    } else if (strcmp(priority, "normal") == 0) {
        test_case->priority = 50;
    } else {
        int priority_value = atoi(priority);
        if (priority_value < 0 || priority_value > 100) {
            fprintf(stderr, "Error: Invalid priority %d\n", priority_value);
            return;
        }

        test_case->priority = priority_value;
    }
}

void _fossil_test_apply_xtag(fossil_test_t* test_case, char* tag) {
    if (!test_case) {
        fossil_test_cout("red", "Test case pointer is xnullptr\n");
        return;
    } else if (!tag) {
        fossil_test_cout("red", "Error: Invalid xtag %s\n", tag);
        return;
    }

    // we handle any rules for tags
    if (strcmp(tag, "fast") == 0) {
        test_case->tags->name = "fast";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_FAST;
    } else if (strcmp(tag, "slow") == 0) {
        test_case->tags->name = "slow";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_SLOW;
    } else if (strcmp(tag, "bug") == 0) {
        test_case->tags->name = "bug";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_BUG;
    } else if (strcmp(tag, "feature") == 0) {
        test_case->tags->name = "feature";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_FEATURE;
    } else if (strcmp(tag, "security") == 0) {
        test_case->tags->name = "security";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_SECURITY;
    } else if (strcmp(tag, "performance") == 0) {
        test_case->tags->name = "performance";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_PERFORMANCE;
    } else if (strcmp(tag, "stress") == 0) {
        test_case->tags->name = "stress";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_STRESS;
    } else if (strcmp(tag, "regression") == 0) {
        test_case->tags->name = "regression";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_REGRESSION;
    } else if (strcmp(tag, "compatibility") == 0) {
        test_case->tags->name = "compatibility";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_COMPATIBILITY;
    } else if (strcmp(tag, "usability") == 0) {
        test_case->tags->name = "usability";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_USABILITY;
    } else if (strcmp(tag, "robustness") == 0) {
        test_case->tags->name = "robustness";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_ROBUSTNESS;
    } else if (strcmp(tag, "corner case") == 0) {
        test_case->tags->name = "corner case";
        test_case->tags->rule = TEST_ASSERT_TAG_RULE_CORNER_CASE;
    } else {
        fossil_test_cout("red", "Error: Invalid xtag %s\n", tag);
    }
}

void _fossil_test_apply_mark(fossil_test_t* test_case, char* mark) {
    if (!test_case) {
        fossil_test_cout("red", "Test case pointer is xnullptr\n");
        return;
    } else if (!mark) {
        fossil_test_cout("red", "Error: Invalid marker %s\n", mark);
        return;
    }

    // we handle any rules for marks
    if (strcmp(mark, "skip") == 0) {
        test_case->marks->name = "skip";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_SKIP;
    } else if (strcmp(mark, "fail") == 0) {
        test_case->marks->name = "fail";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_FAIL;
    } else if (strcmp(mark, "pass") == 0) {
        test_case->marks->name = "pass";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_PASS;
    } else if (strcmp(mark, "timeout") == 0) {
        test_case->marks->name = "timeout";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_TIMEOUT;
    } else if (strcmp(mark, "error") == 0) {
        test_case->marks->name = "error";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_ERROR;
    } else if (strcmp(mark, "none") == 0) {
        test_case->marks->name = "none";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_NONE;
    } else if (strcmp(mark, "only") == 0) {
        test_case->marks->name = "only";
        test_case->marks->rule = TEST_ASSERT_MARK_RULE_ONLY;
    } else {
        fossil_test_cout("red", "Error: Invalid marker %s\n", mark);
    }
}
