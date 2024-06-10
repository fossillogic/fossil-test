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

// Running tests in a queue
void fossil_test_run_queue(fossil_env_t* test_env);

// ==============================================================================
// Xtest internal argument parser logic
// ==============================================================================

fossil_test_queue_t* fossil_test_queue_t_create(void) {
    fossil_test_queue_t* queue = (fossil_test_queue_t*)malloc(sizeof(fossil_test_queue_t));
    if (!queue) {
        fossil_test_cout("red", "Failed to allocate memory for queue\n");
        return xnullptr;
    }
    queue->front = xnullptr;
    queue->rear = xnullptr;
    return queue;
}

bool fossil_test_queue_t_is_empty(fossil_test_queue_t* queue) {
    if (!queue) {
        fossil_test_cout("red", "Queue pointer is xnullptr\n");
        return true; // Consider an invalid queue as empty
    }
    return queue->front == xnullptr;
}

fossil_test_t* fossil_test_queue_t_peek_front(fossil_test_queue_t* queue) {
    if (fossil_test_queue_t_is_empty(queue)) {
        return xnullptr;
    }
    return queue->front;
}

bool fossil_test_queue_t_remove_by_name(fossil_test_queue_t* queue, const char* name) {
    if (!queue || fossil_test_queue_t_is_empty(queue) || !name) {
        return false;
    }

    fossil_test_t* current = queue->front;
    while (current != xnullptr) {
        if (strcmp(current->name, name) == 0) {
            // Remove the current node
            if (current->prev != xnullptr) {
                current->prev->next = current->next;
            } else {
                queue->front = current->next;
            }

            if (current->next != xnullptr) {
                current->next->prev = current->prev;
            } else {
                queue->rear = current->prev;
            }

            free(current);
            return true;
        }
        current = current->next;
    }

    return false; // Name not found
}

fossil_test_t* fossil_test_queue_t_find_by_name(fossil_test_queue_t* queue, const char* name) {
    if (!queue || fossil_test_queue_t_is_empty(queue) || !name) {
        return xnullptr;
    }

    fossil_test_t* current = queue->front;
    while (current != xnullptr) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return xnullptr; // Name not found
}

fossil_test_t* fossil_test_queue_t_peek_rear(fossil_test_queue_t* queue) {
    if (fossil_test_queue_t_is_empty(queue)) {
        return xnullptr;
    }
    return queue->rear;
}

void fossil_test_queue_t_enqueue(fossil_test_queue_t* queue, fossil_test_t* test) {
    if (!queue || !test) {
        fossil_test_cout("red", "Queue or test pointer is xnullptr\n");
        return;
    }

    if (fossil_test_queue_t_is_empty(queue)) {
        queue->front = test;
        queue->rear = test;
        test->prev = xnullptr;
        test->next = xnullptr;
    } else {
        fossil_test_t* current = queue->front;

        // Traverse to find the correct position based on priority
        while (current != xnullptr && current->priority >= test->priority) {
            current = current->next;
        }

        if (current == queue->front) {
            // Insert at the front
            test->next = queue->front;
            queue->front->prev = test;
            queue->front = test;
            test->prev = xnullptr;
        } else if (current == xnullptr) {
            // Insert at the rear
            test->prev = queue->rear;
            queue->rear->next = test;
            queue->rear = test;
            test->next = xnullptr;
        } else {
            // Insert in the middle
            test->next = current;
            test->prev = current->prev;
            current->prev->next = test;
            current->prev = test;
        }
    }
}

fossil_test_t* fossil_test_queue_t_dequeue(fossil_test_queue_t* queue) {
    if (fossil_test_queue_t_is_empty(queue)) {
        return xnullptr;
    }
    fossil_test_t* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == xnullptr) {
        queue->rear = xnullptr;
    } else {
        queue->front->prev = xnullptr;
    }
    temp->next = xnullptr;
    return temp;
}

void fossil_test_queue_t_erase(fossil_test_queue_t* queue) {
    if (!queue) {
        fossil_test_cout("red", "Queue pointer is xnullptr\n");
        return;
    }

    while (!fossil_test_queue_t_is_empty(queue)) {
        fossil_test_t* current_test = fossil_test_queue_t_dequeue(queue);
        if (current_test != xnullptr) {
            free(current_test); // Free memory allocated for dequeued test case
        }
    }
    free(queue); // Free the queue structure itself
}

// ==============================================================================
// Xtest score board rule functions
// ==============================================================================

void _fossil_test_scoreboard_update(fossil_env_t* test_env) {
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
    test_env->stats.untested_count--;
    test_env->stats.expected_total_count++;
}

void _fossil_test_scoreboard_expected_rules(fossil_env_t* test_env) {
    // nothing crazy here just updating the expected passed and failed
    // counts based on the test case results.
    if (!_fossil_test_env.rule.should_pass) {
        test_env->stats.expected_failed_count++;
    } else {
        test_env->stats.expected_passed_count++;
    }
}

void _fossil_test_scoreboard_unexpected_rules(fossil_env_t* test_env) {
    // here we handle unexpected rules for cases that play
    // the UNO reverse card on us.
    if (_fossil_test_env.rule.should_pass) {
        test_env->stats.unexpected_failed_count++;
    } else {
        test_env->stats.unexpected_passed_count++;
    }
}

void _fossil_test_scoreboard_feature_rules(fossil_env_t* test_env, fossil_test_t* test_case) {
    // handling features for skip and timeouts
    if (_fossil_test_env.rule.skipped == true && strcmp(test_case->marks->name, "skip") == 0) {
        test_env->stats.expected_skipped_count++;
        _fossil_test_env.rule.skipped = false;
    } else if (strcmp(test_case->tags->name, "fast") == 0 && _fossil_test_env.rule.should_timeout == true) {
        test_env->stats.expected_timeout_count++;
        _fossil_test_env.rule.should_timeout = false; // Reset timeout flag
    } else if (strcmp(test_case->tags->name, "slow") == 0 && _fossil_test_env.rule.should_timeout == true) {
        test_env->stats.expected_timeout_count++;
        _fossil_test_env.rule.timeout = false; // Reset timeout flag
    } else if (!_fossil_test_env.rule.should_pass) {
        if (_xassert_info.should_fail) {
            test_env->stats.expected_passed_count++;
            _fossil_test_env.rule.should_pass = true;
        } else {
            test_env->stats.expected_failed_count++;
        }
    } else {
        test_env->stats.expected_passed_count++;
    }
}

void _fossil_test_scoreboard(fossil_env_t* test_env, fossil_test_t* test_case) {
    // here we handle the scoreboard logic for the test cases
    // based on the rules and features that are set.
    if (strcmp(test_case->marks->name, "default") != 0 || strcmp(test_case->tags->name, "default") != 0) {
        // Simply handling unique cases using marks and tags first
        // to ensure I catch the added features.
        _fossil_test_scoreboard_feature_rules(test_env, test_case);
    } else if (_fossil_test_env.rule.result) {
        // here we handle the expected and unexpected rules
        // using normal flow without worrying about the features
        // as used in marks and tags.
        _fossil_test_scoreboard_expected_rules(test_env);
    } else if (!_fossil_test_env.rule.result) {
        // here we handle unexpected rules for cases that play
        // the UNO reverse card on us.
        _fossil_test_scoreboard_unexpected_rules(test_env);
    }

    // here we just update the scoreboard count
    // add one to total tested cases and remove
    // one from untested ghost cases.
    _fossil_test_scoreboard_update(test_env);
}

// ==============================================================================
// Xtest create and erase
// ==============================================================================

fossil_env_t _fossil_test_environment_create(int argc, char* *argv) {
    fossil_test_cli_parse(argc, argv, commands); // Parse command line arguments
    fossil_env_t new_env;

    new_env.stats = (fossil_test_score_t){0, 0, 0, 0, 0, 0, 0, 0};
    new_env.timer = (fossil_test_timer_t){0, 0, 0, {0, 0, 0, 0, 0}};
    new_env.rule  = (fossil_test_rule_t){false, true, false, true, false, false, false, false};
    new_env.queue = fossil_test_queue_t_create(); // Create priority queue

    new_env.timer.start = clock(); // Start the timer

    // as a safty mesure we provide an atexit handler to avoid memory leaks
    atexit(_fossil_test_environment_erase); // Register cleanup function
    
    return new_env;
}

void _fossil_test_environment_erase(void) {
    fossil_test_queue_t_erase(_fossil_test_env.queue);

    // ensure summary dosent print twice if we happen to call exit
    if (!_fossil_test_env.rule.should_pass) {
        _fossil_test_environment_summary();
    }
}

void _fossil_test_environment_add(fossil_env_t* test_env, fossil_test_t* test_case, fossil_fixture_t* fixture) {
    if (fixture != xnullptr && fixture->setup != xnullptr && fixture->teardown != xnullptr) {
        test_case->fixture.setup = fixture->setup;
        test_case->fixture.teardown = fixture->teardown;
    } else {
        test_case->fixture.setup = xnullptr;
        test_case->fixture.teardown = xnullptr;
    }

    // here we count up the untested cases
    test_env->stats.untested_count++;
    fossil_test_queue_t_enqueue(test_env->queue, test_case);
}

void _fossil_test_environment_run(void) {
    while (!fossil_test_queue_t_is_empty(_fossil_test_env.queue)) {
        fossil_test_t* current_test = fossil_test_queue_t_dequeue(_fossil_test_env.queue);
        if (current_test != xnullptr) {
            _fossil_test_assume_unit_runner(current_test);
        }
    }
}

int _fossil_test_environment_summary(void) {
    int result = (_fossil_test_env.stats.untested_count          + // Count of untested cases
                  _fossil_test_env.stats.expected_failed_count   + // Count of expected failed cases
                  _fossil_test_env.stats.unexpected_passed_count + // Count of unexpected passed cases
                  _fossil_test_env.stats.expected_timeout_count  + // Count of expected timeout cases
                  _fossil_test_env.stats.unexpected_failed_count); // Count of unexpected failed cases
    output_summary_format(&_fossil_test_env);
    return result;
}

// ==============================================================================
// Xtest functions for asserts
// ==============================================================================

// assertion classes should abort like normal without memory leaks

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

// Custom assertion function with optional message.
void fossil_test_assert_impl_sanity(bool expression, const char* message, const char* file, int line, const char* func) {
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

// Custom expectation function with optional message.
void fossil_test_assert_impl_except(bool expression, const char* message, const char* file, int line, const char* func) {
    if (_fossil_test_env.current_except_count == FOSSIL_TEST_EXCEPT_MAX) {
        return;
    }

    if (_xassert_info.should_fail) {
        if (!expression) {
            _fossil_test_env.rule.should_pass = true;
        } else {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_except_count++;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _fossil_test_env.rule.should_pass = false;
            _fossil_test_env.current_except_count++;
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
    } else if (behavor == TEST_ASSERT_AS_CLASS_SANITY) {
        fossil_test_assert_impl_sanity(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXCEPT) {
        fossil_test_assert_impl_except(expression, message, file, line, func);
    }
    _xassert_info.has_assert = true; // Make note of an assert being added in a given test case
}

// regex_match function for use in regular expressions assertions
bool _assume_regex_match(const char *pattern, const char *str) {
    while (*pattern) {
        if (*pattern == '*') {
            while (*str) {
                if (_assume_regex_match(pattern + 1, str)) {
                    return true;
                }
                str++;
            }
            return _assume_regex_match(pattern + 1, str);
        }
        
        if (*str == '\0' || (*pattern != '?' && *pattern != *str)) {
            return false;
        }
        
        pattern++;
        str++;
    }
    
    return *str == '\0';
}
