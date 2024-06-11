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
#include "fossil/unittest/internal.h"
#include "fossil/_common/common.h"
#include "fossil/unittest/console.h"
#include "fossil/unittest/commands.h"
#include <stdarg.h>

fossil_env_t _TEST_ENV;
xassert_info _xassert_info;

// // Function to add a test to the front of the queue
// void fossil_test_queue_push_front(fossil_test_t *test, fossil_test_queue_t *queue);

// // Function to add a test to the rear of the queue
// void fossil_test_queue_push_back(fossil_test_t *test, fossil_test_queue_t *queue);

// // Function to remove and return the test from the front of the queue
// fossil_test_t* fossil_test_queue_pop_front(fossil_test_queue_t *queue);

// // Function to remove and return the test from the rear of the queue
// fossil_test_t* fossil_test_queue_pop_back(fossil_test_queue_t *queue);

// // Function to clear the queue
// void fossil_test_queue_clear(fossil_test_queue_t *queue);

//
// Double ended priority queue functions

void fossil_test_queue_create(fossil_test_queue_t** queue) {
    *queue = (fossil_test_queue_t*)malloc(sizeof(fossil_test_queue_t));
    if (*queue != xnullptr) {
        (*queue)->front = xnullptr;
        (*queue)->rear = xnullptr;
    } else {
        // Handle memory allocation failure
        // You might want to log an error message here
        exit(EXIT_FAILURE);
    }
}

void fossil_test_queue_erase(fossil_test_queue_t* queue) {
    fossil_test_t* current = queue->front;
    fossil_test_t* next;

    while (current != xnullptr) {
        next = current->next;
        free(current);
        current = next;
    }

    queue->front = xnullptr;
    queue->rear = xnullptr;
}//

// Function to add a test to the front of the queue
void fossil_test_queue_push_front(fossil_test_t *test, fossil_test_queue_t *queue) {
    if (test == xnullptr || queue == xnullptr) {
        return;
    }

    if (queue->front == xnullptr) {
        // The queue is empty
        queue->front = test;
        queue->rear = test;
    } else {
        // Insert test at the front
        test->next = queue->front;
        queue->front->prev = test;
        queue->front = test;
    }
}

// Function to add a test to the rear of the queue
void fossil_test_queue_push_back(fossil_test_t *test, fossil_test_queue_t *queue) {
    if (test == xnullptr || queue == xnullptr) {
        return;
    }

    if (queue->rear == xnullptr) {
        // The queue is empty
        queue->front = test;
        queue->rear = test;
    } else {
        // Insert test at the rear
        queue->rear->next = test;
        test->prev = queue->rear;
        queue->rear = test;
    }
}

// Function to remove and return the test from the front of the queue
fossil_test_t* fossil_test_queue_pop_front(fossil_test_queue_t *queue) {
    if (queue == xnullptr || queue->front == xnullptr) {
        return xnullptr;
    }

    fossil_test_t *front_test = queue->front;

    if (queue->front == queue->rear) {
        // The queue has only one test
        queue->front = xnullptr;
        queue->rear = xnullptr;
    } else {
        // Remove test from the front
        queue->front = queue->front->next;
        queue->front->prev = xnullptr;
    }

    return front_test;
}

// Function to remove and return the test from the rear of the queue
fossil_test_t* fossil_test_queue_pop_back(fossil_test_queue_t *queue) {
    if (queue == xnullptr || queue->rear == xnullptr) {
        return xnullptr;
    }

    fossil_test_t *rear_test = queue->rear;

    if (queue->front == queue->rear) {
        // The queue has only one test
        queue->front = xnullptr;
        queue->rear = xnullptr;
    } else {
        // Remove test from the rear
        queue->rear = queue->rear->prev;
        queue->rear->next = xnullptr;
    }

    return rear_test;
}

// Function to clear the queue
void fossil_test_queue_clear(fossil_test_queue_t *queue) {
    if (queue == xnullptr) {
        return;
    }

    // Free memory occupied by the tests in the queue
    fossil_test_t *current_test = queue->front;
    while (current_test != xnullptr) {
        fossil_test_t *temp = current_test;
        current_test = current_test->next;
        free(temp);
    }

    // Reset queue pointers
    queue->front = xnullptr;
    queue->rear = xnullptr;
}

// Function to add a test to the queue based on priority
void add_test_to_queue(fossil_test_t *test, fossil_test_queue_t *queue) {
    _TEST_ENV.stats.untested_count++;
    fossil_test_queue_push_back(test, queue);
}

// Function to remove and return the test with the highest priority from the queue
fossil_test_t* get_highest_priority_test(fossil_test_queue_t *queue) {
    // In this implementation, the test with the highest priority is the one at the front of the queue
    return fossil_test_queue_pop_front(queue);
}

// Function to remove and return the test with the lowest priority from the queue
fossil_test_t* get_lowest_priority_test(fossil_test_queue_t *queue) {
    // In this implementation, the test with the lowest priority is the one at the rear of the queue
    return fossil_test_queue_pop_back(queue);
}


//
// Fossil Test Environment functions
//

void fossil_test_environment_erase(void) {
    if (_TEST_ENV.queue != xnullptr) {
        fossil_test_queue_erase(_TEST_ENV.queue);
        free(_TEST_ENV.queue);
    }
}

fossil_env_t fossil_test_environment_create(int argc, char **argv) {
    fossil_test_cli_parse(argc, argv, commands);
    
    fossil_env_t env;

    // Initialize test statistics
    env.stats.expected_passed_count = 0;
    env.stats.expected_failed_count = 0;
    env.stats.unexpected_passed_count = 0;
    env.stats.unexpected_failed_count = 0;
    env.stats.expected_skipped_count = 0;
    env.stats.expected_empty_count = 0;
    env.stats.expected_timeout_count = 0;
    env.stats.expected_total_count = 0;
    env.stats.untested_count = 0;

    // Initialize test timer
    env.timer.start = 0;
    env.timer.end = 0;
    env.timer.elapsed = 0;
    env.timer.detail.minutes = 0;
    env.timer.detail.seconds = 0;
    env.timer.detail.milliseconds = 0;
    env.timer.detail.microseconds = 0;
    env.timer.detail.nanoseconds = 0;

    // Initialize test queue
    fossil_test_queue_create(&env.queue);
    atexit(fossil_test_environment_erase); // ensure memory leaks do not occur

    // Initialize exception and assumption counts
    env.current_except_count = 0;
    env.current_assume_count = 0;

    fossil_test_io_summary_start();
    
    return env;
}

void _fossil_test_scoreboard_update(void) {
    // here we just update the scoreboard count
    // add one to total tested cases and remove
    // one from untested ghost cases.
    //
    // The main goal is to ensure ghost cases are removed
    // accordingly and the total tested cases are updated.
    //
    // However in the event exit is called we will have
    // record of test that are tested and those that are
    // not tested.
    _TEST_ENV.stats.untested_count--;
    _TEST_ENV.stats.expected_total_count++;
}

void _fossil_test_scoreboard_expected_rules(void) {
    // nothing crazy here just updating the expected passed and failed
    // counts based on the test case results.
    if (!_xassert_info.has_assert) {
        _TEST_ENV.stats.expected_empty_count++;
    }

    if (!_TEST_ENV.rule.should_pass) {
        _TEST_ENV.stats.expected_failed_count++;
        _TEST_ENV.rule.should_pass = false;
    } else {
        _TEST_ENV.stats.expected_passed_count++;
    }
}

void _fossil_test_scoreboard_unexpected_rules(void) {
    // here we handle unexpected rules for cases that play
    // the UNO reverse card on us.
    if (!_xassert_info.has_assert) {
        _TEST_ENV.stats.expected_empty_count++;
    }

    if (_TEST_ENV.rule.should_pass) {
        _TEST_ENV.stats.unexpected_failed_count++;
        _TEST_ENV.rule.should_pass = false;
    } else {
        _TEST_ENV.stats.unexpected_passed_count++;
        _TEST_ENV.rule.should_pass = false;

    }
}

void _fossil_test_scoreboard_feature_rules(fossil_test_t *test_case) {
    // handling features for skip and timeouts
    if (_TEST_ENV.rule.skipped == true && strcmp(test_case->marks, "skip") == 0) {
        _TEST_ENV.stats.expected_skipped_count++;
        _TEST_ENV.rule.skipped = false;
    } else if (!_xassert_info.has_assert && strcmp(test_case->marks, "ghost") == 0) {
        _TEST_ENV.stats.expected_empty_count++;
    } else if (_TEST_ENV.rule.should_timeout == true) {
        _TEST_ENV.stats.expected_timeout_count++;
        _TEST_ENV.rule.should_timeout = false; // Reset timeout flag
    } else if (!_TEST_ENV.rule.should_pass && strcmp(test_case->marks, "fail") == 0) {
        if (_xassert_info.should_fail) {
            _TEST_ENV.stats.expected_passed_count++;
            _TEST_ENV.rule.should_pass = true;
        } else {
            _TEST_ENV.stats.expected_failed_count++;
        }
    } else {
        _TEST_ENV.stats.expected_passed_count++;
    }
}

void _fossil_test_scoreboard(fossil_test_t *test_case) {
    // here we handle the scoreboard logic for the test cases
    // based on the rules and features that are set.
    if (strcmp(test_case->marks, "fossil") != 0 || strcmp(test_case->tags, "fossil") != 0) {
        // Simply handling unique cases using marks and tags first
        // to ensure I catch the added features.
        _fossil_test_scoreboard_feature_rules(test_case);
    } else if (_TEST_ENV.rule.result) {
        // here we handle the expected and unexpected rules
        // using normal flow without worrying about the features
        // as used in marks and tags.
        _fossil_test_scoreboard_expected_rules();
    } else if (!_TEST_ENV.rule.result) {
        // here we handle unexpected rules for cases that play
        // the UNO reverse card on us.
        _fossil_test_scoreboard_unexpected_rules();
    }

    // here we just update the scoreboard count
    // add one to total tested cases and remove
    // one from untested ghost cases.
    _fossil_test_scoreboard_update();
}

void fossil_test_environment_scoareboard(fossil_test_t *test) {
    _fossil_test_scoreboard(test);
}

void fossil_test_run_testcase(fossil_test_t *test) {
    if (test == xnullptr) {
        return;
    }

    if (_TEST_ENV.rule.skipped && strcmp(test->marks, "skip") == 0) {
        return;
    } else if (_TEST_ENV.rule.skipped && strcmp(test->marks, "fail") == 0) {
        _TEST_ENV.rule.should_pass = false;
    }

    fossil_test_io_unittest_start(test);
    if (test->fixture.setup != xnullptr) {
        test->fixture.setup();
    }

    // Run the test function
    test->test_function();
    fossil_test_io_unittest_step(&_xassert_info);

    if (test->fixture.teardown != xnullptr) {
        test->fixture.teardown();
    }

    fossil_test_io_unittest_ended(test);
    fossil_test_environment_scoareboard(test);
}

// Function to run the test environment
void fossil_test_environment_run(fossil_env_t *env) {
    if (env == xnullptr) {
        return;
    }

    // Start the timer
    env->timer.start = clock();

    // Iterate through the test queue and run each test
    fossil_test_t *current_test = env->queue->front;
    while (current_test != xnullptr) {
        // Run the test function
        fossil_test_run_testcase(current_test);

        // Move to the next test
        current_test = current_test->next;
    }

    // Stop the timer
    env->timer.end = clock();
    env->timer.elapsed = env->timer.end - env->timer.start;
}

// Function to summarize the test environment
int fossil_test_environment_summary(fossil_env_t *env) {
    if (env == xnullptr) {
        return -1;
    }
    int result = (env->stats.expected_failed_count + env->stats.unexpected_failed_count + env->stats.unexpected_passed_count + env->stats.expected_timeout_count + env->stats.untested_count);

    fossil_test_io_summary_ended(env);
    fossil_test_environment_erase();

    return result;
}

// Function to add a test to the test environment
void fossil_test_environment_add(fossil_env_t *env, fossil_test_t *test, fossil_fixture_t *fixture) {
    if (test == xnullptr || env == xnullptr || env->queue == xnullptr) {
        return;
    }

    if (fixture != xnullptr) {
        test->fixture.setup = fixture->setup;
        test->fixture.teardown = fixture->teardown;
    }

    // Update test statistics
    add_test_to_queue(test, env->queue);
}

//
// Feature function implementations
//

// Function to apply a mark to a test case
void fossil_test_apply_mark(fossil_test_t *test, const char *mark) {
    if (!test) {
        return;
    } else if (!mark) {
        return;
    }

    // we handle any rules for marks
    if (strcmp(mark, "skip") == 0) {
        test->marks = "skip";
        _TEST_ENV.rule.skipped = true;
    } else if (strcmp(mark, "ghost") == 0) {
        test->marks = "ghost"; // remember to call the ghostbusters whena team member marks an empty case.
    } else if (strcmp(mark, "error") == 0) {
        test->marks = "error";
        _TEST_ENV.rule.should_pass = false;
    } else if (strcmp(mark, "fail") == 0){
        test->marks = "fail";
        _TEST_ENV.rule.should_pass = false;
    } else if (strcmp(mark, "none") == 0) {
        test->marks = "none";
    } else if (strcmp(mark, "only") == 0) {
        test->marks = "only";
    } else {
        fossil_test_cout("red", "Error: Invalid marker %s\n", mark);
    }
}

// Function to apply an extended tag to a test case
void fossil_test_apply_xtag(fossil_test_t *test, const char *tag) {
    if (!test) {
        return;
    } else if (!tag) {
        return;
    }

    // we handle any rules for tags
    // to be used in a run via tag feature.
    if (strcmp(tag, "fast") == 0) {
        test->tags = "fast";
    } else if (strcmp(tag, "slow") == 0) {
        test->tags = "slow";
    } else if (strcmp(tag, "bug") == 0) {
        test->tags = "bug";
    } else if (strcmp(tag, "feature") == 0) {
        test->tags = "feature";
    } else if (strcmp(tag, "security") == 0) {
        test->tags = "security";
    } else if (strcmp(tag, "performance") == 0) {
        test->tags = "performance";
    } else if (strcmp(tag, "stress") == 0) {
        test->tags = "stress";
    } else if (strcmp(tag, "regression") == 0) {
        test->tags = "regression";
    } else if (strcmp(tag, "compatibility") == 0) {
        test->tags = "compatibility";
    } else if (strcmp(tag, "usability") == 0) {
        test->tags = "usability";
    } else if (strcmp(tag, "robustness") == 0) {
        test->tags = "robustness";
    } else if (strcmp(tag, "corner case") == 0) {
        test->tags = "corner case";
    } else {
        fossil_test_cout("red", "Error: Invalid xtag %s\n", tag);
    }
}

// Function to apply a priority to a test case
void fossil_test_apply_priority(fossil_test_t *test, const char *priority) {
   if (!test) {
        return;
    } else if (!priority) {
        return;
    }

    if (strcmp(priority, "lowest") == 0) {
        test->priority = 0;
    } else if (strcmp(priority, "very low") == 0) {
        test->priority = 10;
    } else if (strcmp(priority, "low") == 0) {
        test->priority = 20;
    } else if (strcmp(priority, "medium") == 0) {
        test->priority = 50;
    } else if (strcmp(priority, "high") == 0) {
        test->priority = 70;
    } else if (strcmp(priority, "very high") == 0) {
        test->priority = 90;
    } else if (strcmp(priority, "highest") == 0) {
        test->priority = 100;
    } else if (strcmp(priority, "urgent") == 0) {
        test->priority = 95;
    } else if (strcmp(priority, "critical") == 0) {
        test->priority = 100;
    } else if (strcmp(priority, "normal") == 0) {
        test->priority = 50;
    } else {
        int priority_value = atoi(priority);
        if (priority_value < 0 || priority_value > 100) {
            return;
        }

        test->priority = priority_value;
    }
}

//
// Assertion function implementations
//

// Custom assumptions function with optional message.
void fossil_test_assert_impl_assume(bool expression, xassert_info *assume) {
    if (_TEST_ENV.current_assume_count == FOSSIL_TEST_ASSUME_MAX) {
        exit(FOSSIL_TEST_ABORT_FAIL);
        return;
    }

    if (!_xassert_info.should_fail) {
        if (!expression) {
            _TEST_ENV.rule.should_pass = false;
            _TEST_ENV.current_assume_count++;
            fossil_test_io_asserted(assume);
        }
    } else {
        if (!expression) {
            _TEST_ENV.rule.should_pass = true;
        } else if (expression) {
            _TEST_ENV.rule.should_pass = false;
            _TEST_ENV.current_assume_count++;
            fossil_test_io_asserted(assume);
        }
    }
} // end of func

// Custom assertion function with optional message.
void fossil_test_assert_impl_assert(bool expression, xassert_info *assume) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _TEST_ENV.rule.should_pass = true;
        } else if (expression) {
            _TEST_ENV.rule.should_pass = false;
            fossil_test_io_asserted(assume);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    } else {
        if (!expression) {
            _TEST_ENV.rule.should_pass = false;
            fossil_test_io_asserted(assume);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    }
} // end of func

// Custom expectation function with optional message.
void fossil_test_assert_impl_expect(bool expression, xassert_info *assume) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _TEST_ENV.rule.should_pass = true;
        } else if (expression) {
            _TEST_ENV.rule.should_pass = false;
            fossil_test_io_asserted(assume);
        }
    } else {
        if (!expression) {
            _TEST_ENV.rule.should_pass = false;
            fossil_test_io_asserted(assume);
        }
    }
} // end of func

void _fossil_test_assert_class(bool expression, xassert_type_t behavor, char* message, char* file, int line, char* func) {
    _xassert_info.func = func;
    _xassert_info.file = file;
    _xassert_info.line = line;
    _xassert_info.message = message;

    if (behavor == TEST_ASSERT_AS_CLASS_ASSUME) {
        fossil_test_assert_impl_assume(expression, &_xassert_info);
    } else if (behavor == TEST_ASSERT_AS_CLASS_ASSERT) {
        fossil_test_assert_impl_assert(expression, &_xassert_info);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXPECT) {
        fossil_test_assert_impl_expect(expression, &_xassert_info);
    }
    _xassert_info.has_assert = true; // Make note of an assert being added in a given test case
}
