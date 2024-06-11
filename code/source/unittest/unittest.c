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

fossil_env_t _fossil_test_env;
xassert_info _xassert_info;

// Function to add a test to the front of the queue
void fossil_test_queue_push_front(fossil_test_t *test, fossil_test_queue_t *queue);

// Function to add a test to the rear of the queue
void fossil_test_queue_push_back(fossil_test_t *test, fossil_test_queue_t *queue);

// Function to remove and return the test from the front of the queue
fossil_test_t* fossil_test_queue_pop_front(fossil_test_queue_t *queue);

// Function to remove and return the test from the rear of the queue
fossil_test_t* fossil_test_queue_pop_back(fossil_test_queue_t *queue);

// Function to clear the queue
void fossil_test_queue_clear(fossil_test_queue_t *queue);

//
// Double ended priority queue functions

void fossil_test_queue_create(fossil_test_queue_t* queue) {
    queue->front = xnullptr;
    queue->rear = xnullptr;
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
    fossil_test_queue_erase(_fossil_test_env.queue);
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
    fossil_test_queue_create(env.queue);
    atexit(fossil_test_environment_erase); // ensure memory leaks do not occur

    // Initialize exception and assumption counts
    env.current_except_count = 0;
    env.current_assume_count = 0;

    fossil_test_io_summary_start();
    
    return env;
}

void fossil_test_run_testcase(fossil_test_t *test) {
    if (test == xnullptr) {
        return;
    }
    fossil_test_io_unittest_start(test);
    if (test->fixture.setup != xnullptr) {
        test->fixture.setup();
    }

    // Run the test function
    test->test_function();

    if (test->fixture.teardown != xnullptr) {
        test->fixture.teardown();
    }

    fossil_test_io_unittest_ended(test);
}

// Function to run the test environment
void fossil_test_environment_run(fossil_env_t *env) {
    if (env == xnullptr || env->queue == xnullptr || env->queue->front == xnullptr) {
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
    int result = (env->stats.expected_failed_count + env->stats.unexpected_failed_count + env->stats.expected_timeout_count + env->stats.untested_count);

    fossil_test_io_summary_ended(env);
    fossil_test_environment_erase();

    return result;
}

// Function to add a test to the test environment
void fossil_test_environment_add(fossil_env_t *env, fossil_test_t *test, fossil_fixture_t *fixture) {
    if (test == xnullptr || env == xnullptr || env->queue == xnullptr) {
        return;
    }

    // Add the test to the queue
    if (env->queue->front == xnullptr) {
        // The queue is empty
        env->queue->front = test;
        env->queue->rear = test;
    } else {
        // Append the test to the end of the queue
        env->queue->rear->next = test;
        test->prev = env->queue->rear;
        env->queue->rear = test;
    }

    if (fixture != xnullptr) {
        test->fixture.setup = fixture->setup;
        test->fixture.teardown = fixture->teardown;
    }

    // Update test statistics
    env->stats.untested_count++;
    fossil_test_queue_push_front(test, env->queue);
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
    } else if (strcmp(mark, "timeout") == 0) {
        test->marks = "timeout";
    } else if (strcmp(mark, "error") == 0) {
        test->marks = "error";
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
    if (_fossil_test_env.current_assume_count == FOSSIL_TEST_ASSUME_MAX) {
        exit(FOSSIL_TEST_ABORT_FAIL);
        return;
    }

    if (!_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_assume_count++;
            fossil_test_io_asserted(assume);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_assume_count++;
            fossil_test_io_asserted(assume);
        }
    }
} // end of func

// Custom assertion function with optional message.
void fossil_test_assert_impl_assert(bool expression, xassert_info *assume) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            fossil_test_io_asserted(assume);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            fossil_test_io_asserted(assume);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    }
} // end of func

// Custom expectation function with optional message.
void fossil_test_assert_impl_expect(bool expression, xassert_info *assume) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            fossil_test_io_asserted(assume);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
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
