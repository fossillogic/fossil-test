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


// Function prototypes for internal functions
static void calculate_elapsed_time(fossil_test_timer_t *timer);
static void print_elapsed_time(fossil_test_timer_t *timer);

//
// Double ended priority queue functions
//
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

// Function to create a new test environment
fossil_env_t* fossil_test_environment_create(int argc, char **argv) {
    fossil_test_cli_parse(argc, argv, commands);
    fossil_env_t *env = (fossil_env_t*)malloc(sizeof(fossil_env_t));
    if (env != xnullptr) {
        // Initialize test statistics
        env->stats.expected_passed_count = 0;
        env->stats.expected_failed_count = 0;
        env->stats.unexpected_passed_count = 0;
        env->stats.unexpected_failed_count = 0;
        env->stats.expected_skipped_count = 0;
        env->stats.expected_timeout_count = 0;
        env->stats.expected_total_count = 0;
        env->stats.untested_count = 0;

        // Initialize test timer
        env->timer.start = 0;
        env->timer.end = 0;
        env->timer.elapsed = 0;
        env->timer.detail.minutes = 0;
        env->timer.detail.seconds = 0;
        env->timer.detail.milliseconds = 0;
        env->timer.detail.microseconds = 0;
        env->timer.detail.nanoseconds = 0;

        // Initialize test queue
        env->queue = (fossil_test_queue_t*)malloc(sizeof(fossil_test_queue_t));
        if (env->queue != xnullptr) {
            env->queue->front = xnullptr;
            env->queue->rear = xnullptr;
        } else {
            // Handle memory allocation failure
            free(env);
            env = xnullptr;
        }

        // Initialize exception and assumption counts
        env->current_except_count = 0;
        env->current_assume_count = 0;
    }
    return env;
}

// Function to run the test environment
void fossil_test_environment_run(fossil_env_t *env) {
    if (env == xnullptr || env->queue == xnullptr || env->queue->front == xnullptr) {
        fossil_test_cout("blue", "No tests to run.\n");
        return;
    }

    // Start the timer
    env->timer.start = clock();

    // Iterate through the test queue and run each test
    fossil_test_t *current_test = env->queue->front;
    while (current_test != NULL) {
        // Run the test function
        current_test->test_function();

        // Calculate and print elapsed time for the test
        calculate_elapsed_time(&(current_test->timer));
        print_elapsed_time(&(current_test->timer));

        // Move to the next test
        current_test = current_test->next;
    }

    // Stop the timer
    env->timer.end = clock();
    env->timer.elapsed = env->timer.end - env->timer.start;
}

// Function to summarize the test environment
void fossil_test_environment_summary(fossil_env_t *env) {
    if (env == xnullptr) {
        return;
    }
    fossil_test_io_summary(env);

    // Print total elapsed time
    fossil_test_cout("blue", "Total Elapsed Time: %ld milliseconds\n", (long)env->timer.elapsed);
}

// Function to add a test to the test environment
void fossil_test_add(fossil_test_t *test, fossil_env_t *env) {
    if (test == xnullptr || env == xnullptr || env->queue == xnullptr) {
        return;
    }

    // Update test statistics
    env->stats.expected_total_count++;

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
}

// Function to apply a mark to a test case
void fossil_test_apply_mark(fossil_test_t *test, const char *mark) {
    _fossil_test_apply_mark(test, mark);
}

// Function to apply an extended tag to a test case
void fossil_test_apply_xtag(fossil_test_t *test, const char *xtag) {
    _fossil_test_apply_xtag(test, xtag);
}

// Function to apply a priority to a test case
void fossil_test_apply_priority(fossil_test_t *test, const char *priority) {
    _fossil_test_apply_priority(test, priority);
}

// Internal function to calculate elapsed time for a test
static void calculate_elapsed_time(fossil_test_timer_t *timer) {
    // Calculate elapsed time
    timer->elapsed = timer->end - timer->start;

    // Convert elapsed time to different units
    timer->detail.minutes = timer->elapsed / (CLOCKS_PER_SEC * 60);
    timer->detail.seconds = (timer->elapsed / CLOCKS_PER_SEC) % 60;
    timer->detail.milliseconds = (timer->elapsed * 1000) / CLOCKS_PER_SEC;
    timer->detail.microseconds = (timer->elapsed * 1000000) / CLOCKS_PER_SEC;
    timer->detail.nanoseconds = (timer->elapsed * 1000000000) / CLOCKS_PER_SEC;
}

// Internal function to print elapsed time for a test
static void print_elapsed_time(fossil_test_timer_t *timer) {
    fossil_test_cout("blue", "Elapsed Time: %ld minutes, %ld seconds, %ld milliseconds, %ld microseconds, %ld nanoseconds\n",
           timer->detail.minutes, timer->detail.seconds, timer->detail.milliseconds,
           timer->detail.microseconds, timer->detail.nanoseconds);
}

// Custom assumptions function with optional message.
void fossil_test_assert_impl_assume(bool expression, const char* message, const char* file, int line, const char* func) {
    if (_fossil_test_env.current_assume_count == FOSSIL_TEST_ASSUME_MAX) {
        exit(FOSSIL_TEST_ABORT_FAIL);
        return;
    }

    if (!_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_assume_count++;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_assume_count++;
            output_assume_format(message, file, line, func);
        }
    }
} // end of func

// Custom assertion function with optional message.
void fossil_test_assert_impl_assert(bool expression, const char* message, const char* file, int line, const char* func) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(FOSSIL_TEST_ABORT_FAIL);
        }
    }
} // end of func

// Custom expectation function with optional message.
void fossil_test_assert_impl_expect(bool expression, const char* message, const char* file, int line, const char* func) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else if (expression) {
            _fossil_test_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
        }
    }
} // end of func

void _fossil_test_assert_class(bool expression, xassert_type_t behavor, char* message, char* file, int line, char* func) {
    if (behavor == TEST_ASSERT_AS_CLASS_ASSUME) {
        fossil_test_assert_impl_assume(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_ASSERT) {
        fossil_test_assert_impl_assert(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXPECT) {
        fossil_test_assert_impl_expect(expression, message, file, line, func);
    }
    _xassert_info.has_assert = true; // Make note of an assert being added in a given test case
}