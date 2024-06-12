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
xassert_info _ASSERT_INFO;

fossil_test_queue_t* fossil_test_queue_create(void) {
    fossil_test_queue_t* queue = (fossil_test_queue_t*)malloc(sizeof(fossil_test_queue_t));
    if (queue != xnullptr) {
        queue->front = xnullptr;
        queue->rear = xnullptr;
    } else {
        // Handle memory allocation failure
        perror("Failed to allocate memory for queue");
        return xnullptr;
    }
    return queue;
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
}

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
    test->prev = xnullptr; // Ensure previous pointer of new front is NULL
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
    test->next = xnullptr; // Ensure next pointer of new rear is NULL
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

// Function to search for a test by tag in the queue
fossil_test_t* fossil_test_queue_search_by_tag(fossil_test_queue_t *queue, const char *tag) {
    if (queue == xnullptr || tag == xnullptr) {
        return xnullptr;
    }

    fossil_test_t *current = queue->front;
    while (current != xnullptr) {
        if (strcmp(current->tag, tag) == 0) {
            return current;
        }
        current = current->next;
    }
    return xnullptr;
}

// Function to search for a test by name in the queue
fossil_test_t* fossil_test_queue_search_by_name(fossil_test_queue_t *queue, const char *name) {
    if (queue == xnullptr || name == xnullptr) {
        return xnullptr;
    }

    fossil_test_t *current = queue->front;
    while (current != xnullptr) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return xnullptr;
}

void fossil_test_queue_reverse(fossil_test_queue_t *queue) {
    if (queue == xnullptr) {
        return;
    }

    fossil_test_t *current = queue->front;
    fossil_test_t *temp = xnullptr;

    // Swap the next and prev pointers for each node
    while (current != xnullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Swap the front and rear pointers of the queue
    if (temp != xnullptr) {
        temp = queue->front;
        queue->front = queue->rear;
        queue->rear = temp;
    }
}

// Function to convert queue to an array
fossil_test_t** queue_to_array(fossil_test_queue_t *queue, int *size) {
    if (queue == xnullptr) {
        return xnullptr;
    }

    int count = 0;
    fossil_test_t *current = queue->front;
    while (current != xnullptr) {
        count++;
        current = current->next;
    }

    fossil_test_t **array = (fossil_test_t**)malloc(count * sizeof(fossil_test_t*));
    current = queue->front;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    *size = count;
    return array;
}

// Function to convert array to a queue
void array_to_queue(fossil_test_t **array, int size, fossil_test_queue_t *queue) {
    if (queue == xnullptr || array == xnullptr) {
        return;
    }

    queue->front = xnullptr;
    queue->rear = xnullptr;

    for (int i = 0; i < size; i++) {
        array[i]->next = xnullptr;
        array[i]->prev = xnullptr;
        fossil_test_queue_push_back(array[i], queue);
    }
}

// Fisher-Yates shuffle algorithm
void fossil_test_queue_shuffle(fossil_test_queue_t *queue) {
    if (queue == xnullptr) {
        return;
    }

    int size;
    fossil_test_t **array = queue_to_array(queue, &size);
    if (array == xnullptr) {
        return;
    }

    srand(time(xnullptr));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        fossil_test_t *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    array_to_queue(array, size, queue);
    free(array);
}

//
// Fossil Test Environment functions
//

void fossil_test_environment_erase(void) {
    if (_TEST_ENV.queue != xnullptr) {
        free(_TEST_ENV.queue);  // Fix memory leak by uncommenting free statement
    }
}

fossil_env_t fossil_test_environment_create(int argc, char **argv) {
    _CLI = fossil_options_parse(argc, argv);
    fossil_test_io_information(); // checkpoint for simple commands
    
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

    // Initialize test rules
    env.rule.should_pass = true;
    env.rule.skipped     = false;
    env.rule.timeout     = false;
    env.rule.error       = false;

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
    env.queue = fossil_test_queue_create();
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
    if (!_TEST_ENV.rule.should_pass) {
        _TEST_ENV.stats.expected_failed_count++;
        _TEST_ENV.rule.should_pass = false;
    } else {
        _TEST_ENV.stats.expected_passed_count++;
    }
}

void _fossil_test_scoreboard_unexpected_rules(void) {
    if (_TEST_ENV.rule.should_pass) {
        _TEST_ENV.stats.unexpected_failed_count++;
    } else {
        _TEST_ENV.stats.unexpected_passed_count++;
    }
}

void _fossil_test_scoreboard_feature_rules(fossil_test_t *test_case) {
    if (_TEST_ENV.rule.skipped && strcmp(test_case->marks, "skip") == 0) {
        _TEST_ENV.stats.expected_skipped_count++;
        _TEST_ENV.rule.skipped = false;
    }
    if (!_ASSERT_INFO.has_assert && strcmp(test_case->marks, "tofu") != 0) {
        _TEST_ENV.stats.expected_empty_count++;
    }

    // handling features for skip and timeouts
    if (!_TEST_ENV.rule.should_pass && strcmp(test_case->marks, "fail") == 0) {
        if (_ASSERT_INFO.should_fail) {
            _fossil_test_scoreboard_expected_rules();
        } else {
            _fossil_test_scoreboard_unexpected_rules();
        }
    } else {
        _TEST_ENV.stats.expected_passed_count++;
    }
}

void fossil_test_environment_scoreboard(fossil_test_t *test) {
    // for the first part we check if the given test case
    // has any feature flags or rules triggered.
    if (strcmp(test->marks, "fossil") != 0) {
        _fossil_test_scoreboard_feature_rules(test);
    } else {
        _fossil_test_scoreboard_expected_rules();
    }
    
    // we just need to update the total scoreboard
    // so it is accurate for the fossil test.
    _fossil_test_scoreboard_update();
}

void fossil_test_run_testcase(fossil_test_t *test) {
    if (test == xnullptr) {
        return;
    }
    // set and reset step for assert scanning
    _ASSERT_INFO.has_assert     = false;
    _ASSERT_INFO.should_fail    = false;
    _ASSERT_INFO.shoudl_timeout = false;

    if (_TEST_ENV.rule.skipped && strcmp(test->marks, "skip") == 0) {
        return;
    } else if (_TEST_ENV.rule.skipped && strcmp(test->marks, "fail") == 0) {
        _ASSERT_INFO.should_fail = false;
    }

    fossil_test_io_unittest_start(test);
    if (test->fixture.setup != xnullptr) {
        test->fixture.setup();
    }

    // Run the test function
    for (int32_t iter = 0; iter < _CLI.repeat_count; iter++) {
        test->test_function();
    }
    fossil_test_io_unittest_step(&_ASSERT_INFO);

    if (test->fixture.teardown != xnullptr) {
        test->fixture.teardown();
    }

    fossil_test_io_unittest_ended(test);
    fossil_test_environment_scoreboard(test);
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
int fossil_test_environment_summary(void) {
    fossil_test_io_summary_ended();
    int result = (_TEST_ENV.stats.expected_failed_count   +
                  _TEST_ENV.stats.unexpected_failed_count +
                  _TEST_ENV.stats.unexpected_passed_count +
                  _TEST_ENV.stats.expected_timeout_count  +
                  _TEST_ENV.stats.untested_count);

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
    _TEST_ENV.stats.untested_count++;
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
    } else if (strcmp(tag, "edge case") == 0) {
        test->tags = "edge case";
    } else if (strcmp(tag, "boundary case") == 0) {
        test->tags = "boundary case";
    } else if (strcmp(tag, "negative case") == 0) {
        test->tags = "negative case";
    } else if (strcmp(tag, "positive case") == 0) {
        test->tags = "positive case";
    } else if (strcmp(tag, "sanity") == 0) {
        test->tags = "sanity";
    } else if (strcmp(tag, "smoke") == 0) {
        test->tags = "smoke";
    } else if (strcmp(tag, "acceptance") == 0) {
        test->tags = "acceptance";
    } else if (strcmp(tag, "regression") == 0) {
        test->tags = "regression";
    } else if (strcmp(tag, "functional") == 0) {
        test->tags = "functional";
    } else if (strcmp(tag, "integration") == 0) {
        test->tags = "integration";
    } else if (strcmp(tag, "system") == 0) {
        test->tags = "system";
    } else if (strcmp(tag, "end-to-end") == 0) {
        test->tags = "end-to-end";
    } else if (strcmp(tag, "unit") == 0) {
        test->tags = "unit";
    } else if (strcmp(tag, "component") == 0) {
        test->tags = "component";
    } else if (strcmp(tag, "module") == 0) {
        test->tags = "module";
    } else if (strcmp(tag, "api") == 0) {
        test->tags = "api";
    } else if (strcmp(tag, "ui") == 0) {
        test->tags = "ui";
    } else if (strcmp(tag, "usability") == 0) {
        test->tags = "usability";
    } else if (strcmp(tag, "performance") == 0) {
        test->tags = "performance";
    } else if (strcmp(tag, "security") == 0) {
        test->tags = "security";
    } else if (strcmp(tag, "stress") == 0) {
        test->tags = "stress";
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

    if (!_ASSERT_INFO.should_fail) {
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
    if (_ASSERT_INFO.should_fail) {
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
    if (_ASSERT_INFO.should_fail) {
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
    _ASSERT_INFO.func = func;
    _ASSERT_INFO.file = file;
    _ASSERT_INFO.line = line;
    _ASSERT_INFO.message = message;

    if (behavor == TEST_ASSERT_AS_CLASS_ASSUME) {
        fossil_test_assert_impl_assume(expression, &_ASSERT_INFO);
    } else if (behavor == TEST_ASSERT_AS_CLASS_ASSERT) {
        fossil_test_assert_impl_assert(expression, &_ASSERT_INFO);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXPECT) {
        fossil_test_assert_impl_expect(expression, &_ASSERT_INFO);
    }
    _ASSERT_INFO.has_assert = true; // Make note of an assert being added in a given test case
}
