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
#include "fossil/xtest/internal.h"
#include <stdarg.h>

// Define thread pool size
enum {
    XTEST_MAX_FILTER_LENGTH = 50,
    XTEST_ASSUME_MAX  = 5,
    XTEST_EXCEPT_MAX  = 5,
    XTEST_MAX_REPEATS = 100,
    XTEST_MIN_REPEATS = 1,
    XTEST_MAX_PRIORITY = 100,
    XTEST_MIN_PRIORITY = 1,
    MAX_EXPECTED_TIME_FAST = 1000, // Example value: 1000 milliseconds (1 second)
    MAX_EXPECTED_TIME_SLOW = 2000, // 2000 milliseconds (2 seconds)
    XTEST_DEFAULT_PRIORITY_THRESHOLD = 50,
    XTEST_ABORT_FAIL = -1,
};

typedef enum {
    XTEST_IO_AS_HUMAN,
    XTEST_IO_AS_CUTBACK,
    XTEST_IO_AS_TURBO
} xtest_mode;

typedef struct {
    xtest_mode mode;
    bool dry_run;
    bool color;
    bool repeat;
    int32_t priority_threshold;
    uint8_t iter_repeat;
    uint8_t thread_count; // Number of threads for parallel execution
} xparser;

// Global xparser variable
xparser xcli;

xenv _xtest_env;
xassert_info _xassert_info;

// Running tests in a queue
void xtest_run_queue(xenv* test_env);

// ==============================================================================
// Xtest internal console stream logic
// ==============================================================================

// to make strdup work on multable platforms and be C23, C18 compatabliity
// a custom strdup has been written to soul purpose of using strdup.
static xstring xstrdup(const xstring str) {
    if (str == xnullptr) {
        return xnullptr;
    }
    size_t len = strlen(str) + 1;
    xstring copy = (xstring )malloc(len);
    if (copy != xnullptr) {
        memcpy(copy, str, len);
    }
    return copy;
}

xstring current_datetime(void) {
    time_t rawtime;
    struct tm* timeinfo;
    static char datetime[20];  // Buffer to hold the formatted date and time

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);

    char* copy = xstrdup(datetime);  // Return a dynamically allocated copy of the datetime
    if (!copy) {
        return xnullptr; // Check for memory allocation failure
    }

    xstring result = xstrdup(datetime);  // Return a dynamically allocated copy of the datetime
    free(copy);  // Free the temporary copy

    return result;
}

static xstring replace_underscore(const xstring str) {
    if (!str) {
        return xnullptr; // Check for xnull input
    }

    xstring result = xstrdup(str);
    if (!result) {
        return xnullptr; // Check for memory allocation failure
    }

    for (xstring ptr = result; *ptr; ptr++) {
        if (*ptr == '_') {
            *ptr = ' ';
        }
    }

    xstring copy = xstrdup(result);  // Create a copy to free the original
    free(result);  // Free the original

    return copy;
}

// Define color codes
#define COLOR_RED        "\033[1;31m"
#define COLOR_GREEN      "\033[1;32m"
#define COLOR_YELLOW     "\033[1;33m"
#define COLOR_BLUE       "\033[1;34m"
#define COLOR_BRIGHT_BLUE "\033[1;94m"
#define COLOR_DARK_BLUE  "\033[0;34m"
#define COLOR_RESET      "\033[0m"

// Define a structure to map color names to their corresponding codes
typedef struct {
    const char* name;
    const char* code;
} ColorMap;

// printf has its use cases but to handle multable general purpose features without
// forgetting to change a printf this would servse as the internal prinf with color
// and potintal for additnal output releated functionality.
static void xconsole_out(const char* color_name, const char* format, ...) {
    static const ColorMap color_map[] = {
        {"red", COLOR_RED},
        {"green", COLOR_GREEN},
        {"yellow", COLOR_YELLOW},
        {"blue", COLOR_BLUE},
        {"bright blue", COLOR_BRIGHT_BLUE},
        {"dark blue", COLOR_DARK_BLUE},
        {xnullptr, COLOR_RESET} // Default color
    };

    va_list args;
    va_start(args, format);

    // Check if color output is enabled
    if (xcli.color) {
        // Default color code
        const char* color_code = COLOR_RESET;

        // Find the corresponding color code
        for (int i = 0; color_map[i].name != xnull; i++) {
            if (strcmp(color_name, color_map[i].name) == 0) {
                color_code = color_map[i].code;
                break;
            }
        }

        // Print color code and formatted string
        printf("%s", color_code);
        vprintf(format, args);
        printf("%s", COLOR_RESET); // Reset color
    } else {
        // Color output disabled, print formatted string directly
        vprintf(format, args);
    }

    va_end(args);
}

// ==============================================================================
// Output functions
// ==============================================================================

//
// minimize output to for only three IO modes [human/cutback/turbo]

// Formats and displays information about the start/end of a test case.
static void output_start_test(xtest *test_case, xenv* test_env) {
    if (xcli.mode == XTEST_IO_AS_HUMAN) {
        xconsole_out("blue", "[...start case...] ");
        xconsole_out("dark blue", "- %s\n", replace_underscore(test_case->name));
        xconsole_out("dark blue", "- > xtest_case: - %.4i\n", test_env->stats.expected_total_count + 1);
        xconsole_out("dark blue", "- > priority: - %.3i\n", test_case->priority);
    } else if (xcli.mode == XTEST_IO_AS_CUTBACK) {
        xconsole_out("blue", "[START] > case: %.4i name: - %s\n", test_env->stats.expected_total_count + 1, replace_underscore(test_case->name));
    }
} // end of func

static void output_end_test(xtest *test_case) {
    test_case->timer.end = clock();
    test_case->timer.elapsed = test_case->timer.end - test_case->timer.start;

    double elapsed_seconds = (double)test_case->timer.elapsed / CLOCKS_PER_SEC;

    test_case->timer.detail.minutes = (int64_t)(elapsed_seconds / 60);
    test_case->timer.detail.seconds = (int64_t)(elapsed_seconds) % 60;
    test_case->timer.detail.milliseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000);
    test_case->timer.detail.microseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000000);
    test_case->timer.detail.nanoseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000000000);

    if (xcli.mode == XTEST_IO_AS_HUMAN) {
        xconsole_out("dark blue", "- > mark: %s\n", test_case->marks->name);
        xconsole_out("dark blue", "- > xtag: %s\n", test_case->tags->name);
        xconsole_out("dark blue", "- > time: (%2.2lld:%2.2lld:%2.3lld:%2.6lld:%2.9lld)\n",
            test_case->timer.detail.minutes, test_case->timer.detail.seconds,
            test_case->timer.detail.milliseconds, test_case->timer.detail.microseconds,
            test_case->timer.detail.nanoseconds);
        xconsole_out("blue", "[...end case.....]\n\n");
    } else if (xcli.mode == XTEST_IO_AS_CUTBACK) {
        xconsole_out("blue", "[ENDED] > tag: %s mark: %s time: %2lld:%2lld:%3lld\n\n",
            test_case->tags->name, test_case->marks->name,
            test_case->timer.detail.minutes,
            test_case->timer.detail.seconds,
            test_case->timer.detail.milliseconds);
    }
} // end of func

// Output for XUnit Test Case Report
static void output_summary_format(xenv* test_env) {
    test_env->timer.end = clock();
    test_env->timer.elapsed = test_env->timer.end - test_env->timer.start;

    double elapsed_seconds = (double)test_env->timer.elapsed / CLOCKS_PER_SEC;

    test_env->timer.detail.minutes = (int64_t)(elapsed_seconds / 60);
    test_env->timer.detail.seconds = (int64_t)(elapsed_seconds) % 60;
    test_env->timer.detail.milliseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000);
    test_env->timer.detail.microseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000000);
    test_env->timer.detail.nanoseconds = (int64_t)((elapsed_seconds - (int64_t)elapsed_seconds) * 1000000000);

    xconsole_out("blue", "%s\n", "****************************************************************************************:");
    xconsole_out("blue", "%s\n", "****************************************************************************************:");
    xconsole_out("blue", "[%s Runner] version:(%6s) host:(%s) timestamp:(%2.2lld:%2.2lld:%3.3lld:%6.6lld:%9.9lld)\n",
        FOSSIL_TEST_NAME, FOSSIL_TEST_VERSION, _xtest_get_os_name(),
        test_env->timer.detail.minutes, test_env->timer.detail.seconds,
        test_env->timer.detail.milliseconds, test_env->timer.detail.microseconds, 
        test_env->timer.detail.nanoseconds);
    xconsole_out("blue", "%s\n", "****************************************************************************************:");
    xconsole_out("blue", "%s\n", "****************************************************************************************:");

    if (test_env->stats.expected_total_count > 0 || test_env->stats.untested_count != 0) {
        xconsole_out("bright blue", "> - Passed           : - %3d\n", test_env->stats.expected_passed_count);
        xconsole_out("dark blue",   "> - Failed           : - %3d\n", test_env->stats.expected_failed_count);
        xconsole_out("bright blue", "> - Skipped          : - %3d\n", test_env->stats.expected_skipped_count);
        xconsole_out("dark blue",   "> - Timeout          : - %3d\n", test_env->stats.expected_timeout_count);
        xconsole_out("bright blue", "> - Unexpected Passed: - %3d\n", test_env->stats.unexpected_passed_count);
        xconsole_out("dark blue",   "> - Unexpected Failed: - %3d\n", test_env->stats.unexpected_failed_count);
        xconsole_out("bright blue", "> - Total Cases      : - %3d\n", test_env->stats.expected_total_count);
        xconsole_out("bright blue", "> - Ghost Cases      : - %3d\n", test_env->stats.untested_count);
    } else {
        xconsole_out("bright blue", "\n\n\n%s\n\n\n\n", empty_runner_comment());
    }
    xconsole_out("blue", "******: arch:(%s) memory:(%.4i) cpus:(%.2i) endian:(%s) time:(%s)\n",
        _xtest_get_architecture(), _xtest_get_memory_size(), _xtest_get_num_cpus(),
        _xtest_assert_is_big_endian()? "big" : "small", current_datetime());
    xconsole_out("blue", "%s\n", "****************************************************************************************:");
    xconsole_out("blue", "%s\n", "****************************************************************************************:");
} // end of func

void output_assume_format(const xstring message, const xstring file, int line, const xstring func) {
    if (xcli.mode == XTEST_IO_AS_HUMAN) {
        xconsole_out("red", "******************************************************:\n");
        xconsole_out("red", " -> In Function: %s\n - > In File: %s\n - > At Line: %d\n", replace_underscore(func), file, line);
        xconsole_out("red", " -> Assert failed: %s\n", message);
        xconsole_out("red", "******************************************************:\n");
    } else if (xcli.mode == XTEST_IO_AS_CUTBACK) {
        xconsole_out("red", "assert: %s\n", message);
        xconsole_out("red", "func: %s, file: %s, line: %d\n", func, file, line);
    }
    _xtest_env.rule.should_pass = false;
}

void output_benchmark_format(uint64_t elapsed, double max) {
    if (xcli.mode == XTEST_IO_AS_HUMAN) {
        xconsole_out("red", "[...benchmark...]\n");
        xconsole_out("red", ".\t> Elapsed time (%.2f time)\n", elapsed);
        xconsole_out("red", ".\t> Exceeds limit (%.2f time)\n", max);
    } else if (xcli.mode == XTEST_IO_AS_CUTBACK) {
        xconsole_out("red", "> benchmark failed: elapsed time (%.2f time) exceeds limit (%.2f time)\n", elapsed, max);
    }
    _xtest_env.rule.should_pass = false;
}

// Prints usage instructions, including custom options, for a command-line program.
static void output_usage_format(void) {
    xconsole_out("blue", "Usage: xcli [options] %s\n", current_datetime());
    xconsole_out("blue", "Options: ");
    xconsole_out("yellow",   "{help,version,tip,console,priority,color,dry-run,repeat}\n\n");
    xconsole_out("bright blue", "\t-h, --help       : Display this help message                                       :\n");
    xconsole_out("dark blue",   "\t-v, --version    : Display program version                                         :\n");
    xconsole_out("bright blue", "\t-t, --tip        : Display a helpful tip                                           :\n");
    xconsole_out("dark blue",   "\t-c, --console    : Set IO mode for runner ('human'/cutback/turbo)                  :\n");
    xconsole_out("bright blue", "\t-p, --priority N : Set priority threshold for test cases (1-100)                   :\n");
    xconsole_out("dark blue",   "\t-r, --repeat   N : Set a given repeat for a number of times (1-100)                :\n");
    xconsole_out("bright blue", "\t-c, --color      : Enable colored output                                           :\n");
    xconsole_out("dark blue",   "\t--dry-run        : Do a simple pass of the test runner to ensure it works          :\n");
} // end of func

// ==============================================================================
// Xtest internal argument parser logic
// ==============================================================================

static void xparser_parse_args(int argc, xstring argv[]) {
    // Existing options initialization
    xcli.mode      = XTEST_IO_AS_HUMAN;// set to human by default as humans are expected to run this nativly
    xcli.iter_repeat = 1;
    xcli.dry_run = false;
    xcli.repeat  = false;
    xcli.color   = false;
    xcli.priority_threshold = XTEST_DEFAULT_PRIORITY_THRESHOLD; // Set default priority threshold

    for (int32_t i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--dry-run") == 0) {
            xcli.dry_run = true;
        } else if (strcmp(argv[i], "--color") == 0 || strcmp(argv[i], "-c") == 0) {
            xcli.color = true;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            xconsole_out("blue", "3.0.0\n");
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--tip") == 0 || strcmp(argv[i], "-t") == 0) {
            xconsole_out("blue", "%s\n", helpful_tester_tip());
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            output_usage_format();
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "--repeat") == 0 || strcmp(argv[i], "-r") == 0) {
            xcli.repeat = true;
            if (++i < argc) {
                int iter_repeat = atoi(argv[i]);
                if (iter_repeat >= XTEST_MIN_REPEATS && iter_repeat <= XTEST_MAX_REPEATS) {
                    xcli.iter_repeat = iter_repeat;
                } else {
                    xconsole_out("red", "Error: --repeat value must be between 1 and 100.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                xconsole_out("red", "Error: --repeat option requires a numeric argument.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "--console") == 0 || strcmp(argv[i], "-o") == 0) {
            if (++i < argc) {
                if (strcmp(argv[i], "turbo") == 0) {
                    xcli.mode = XTEST_IO_AS_TURBO;
                } else if (strcmp(argv[i], "cutback") == 0) {
                    xcli.mode = XTEST_IO_AS_CUTBACK;
                } else if (strcmp(argv[i], "human") == 0) {
                    xcli.mode = XTEST_IO_AS_HUMAN;
                } else {
                    xconsole_out("red", "Error: Invalid run_as option. Use 'human', 'cutback', or 'turbo'.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                xconsole_out("red", "Error: --console option requires an argument.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "--priority") == 0 || strcmp(argv[i], "-p") == 0) {
            if (++i < argc) {
                int priority_threshold = atoi(argv[i]);
                if (priority_threshold >= XTEST_MIN_PRIORITY && priority_threshold <= XTEST_MAX_PRIORITY) {
                    xcli.priority_threshold = priority_threshold;
                } else {
                    xconsole_out("red", "Error: --priority value must be between 1 and 100.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                xconsole_out("red", "Error: --priority option requires a numeric argument.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// ==============================================================================
// Xtest internal argument parser logic
// ==============================================================================

xqueue* xqueue_create(void) {
    xqueue* queue = (xqueue*)malloc(sizeof(xqueue));
    if (!queue) {
        xconsole_out("red", "Failed to allocate memory for queue\n");
        return xnullptr;
    }
    queue->front = xnullptr;
    queue->rear = xnullptr;
    return queue;
}

bool xqueue_is_empty(xqueue* queue) {
    if (!queue) {
        xconsole_out("red", "Queue pointer is xnullptr\n");
        return true; // Consider an invalid queue as empty
    }
    return queue->front == xnullptr;
}

xtest* xqueue_peek_front(xqueue* queue) {
    if (xqueue_is_empty(queue)) {
        return xnullptr;
    }
    return queue->front;
}

bool xqueue_remove_by_name(xqueue* queue, const char* name) {
    if (!queue || xqueue_is_empty(queue) || !name) {
        return false;
    }

    xtest* current = queue->front;
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

xtest* xqueue_find_by_name(xqueue* queue, const char* name) {
    if (!queue || xqueue_is_empty(queue) || !name) {
        return xnullptr;
    }

    xtest* current = queue->front;
    while (current != xnullptr) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return xnullptr; // Name not found
}

xtest* xqueue_peek_rear(xqueue* queue) {
    if (xqueue_is_empty(queue)) {
        return xnullptr;
    }
    return queue->rear;
}

void xqueue_enqueue(xqueue* queue, xtest* test) {
    if (!queue || !test) {
        xconsole_out("red", "Queue or test pointer is xnullptr\n");
        return;
    }

    if (xqueue_is_empty(queue)) {
        queue->front = test;
        queue->rear = test;
        test->prev = xnullptr;
        test->next = xnullptr;
    } else {
        xtest* current = queue->front;

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

xtest* xqueue_dequeue(xqueue* queue) {
    if (xqueue_is_empty(queue)) {
        return xnullptr;
    }
    xtest* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == xnullptr) {
        queue->rear = xnullptr;
    } else {
        queue->front->prev = xnullptr;
    }
    temp->next = xnullptr;
    return temp;
}

void xqueue_erase(xqueue* queue) {
    if (!queue) {
        xconsole_out("red", "Queue pointer is xnullptr\n");
        return;
    }

    while (!xqueue_is_empty(queue)) {
        xtest* current_test = xqueue_dequeue(queue);
        if (current_test != xnullptr) {
            free(current_test); // Free memory allocated for dequeued test case
        }
    }
    free(queue); // Free the queue structure itself
}

// ==============================================================================
// Xtest score board rule functions
// ==============================================================================

void _xtest_scoreboard_update(xenv* test_env) {
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

void _xtest_scoreboard_expected_rules(xenv* test_env) {
    // nothing crazy here just updating the expected passed and failed
    // counts based on the test case results.
    if (!_xtest_env.rule.should_pass) {
        test_env->stats.expected_failed_count++;
    } else {
        test_env->stats.expected_passed_count++;
    }
}

void _xtest_scoreboard_unexpected_rules(xenv* test_env) {
    // here we handle unexpected rules for cases that play
    // the UNO reverse card on us.
    if (_xtest_env.rule.should_pass) {
        test_env->stats.unexpected_failed_count++;
    } else {
        test_env->stats.unexpected_passed_count++;
    }
}

void _xtest_scoreboard_feature_rules(xenv* test_env, xtest* test_case) {
    // handling features for skip and timeouts
    if (_xtest_env.rule.skipped == true && strcmp(test_case->marks->name, "skip") == 0) {
        test_env->stats.expected_skipped_count++;
        _xtest_env.rule.skipped = false;
    } else if (strcmp(test_case->tags->name, "fast") == 0 && _xtest_env.rule.should_timeout == true) {
        test_env->stats.expected_timeout_count++;
        _xtest_env.rule.should_timeout = false; // Reset timeout flag
    } else if (strcmp(test_case->tags->name, "slow") == 0 && _xtest_env.rule.should_timeout == true) {
        test_env->stats.expected_timeout_count++;
        _xtest_env.rule.timeout = false; // Reset timeout flag
    } else if (!_xtest_env.rule.should_pass) {
        if (_xassert_info.should_fail) {
            test_env->stats.expected_passed_count++;
            _xtest_env.rule.should_pass = true;
        } else {
            test_env->stats.expected_failed_count++;
        }
    } else {
        test_env->stats.expected_passed_count++;
    }
}

void _xtest_scoreboard(xenv* test_env, xtest* test_case) {
    // here we handle the scoreboard logic for the test cases
    // based on the rules and features that are set.
    if (strcmp(test_case->marks->name, "default") != 0 || strcmp(test_case->tags->name, "default") != 0) {
        // Simply handling unique cases using marks and tags first
        // to ensure I catch the added features.
        _xtest_scoreboard_feature_rules(test_env, test_case);
    } else if (_xtest_env.rule.result) {
        // here we handle the expected and unexpected rules
        // using normal flow without worrying about the features
        // as used in marks and tags.
        _xtest_scoreboard_expected_rules(test_env);
    } else if (!_xtest_env.rule.result) {
        // here we handle unexpected rules for cases that play
        // the UNO reverse card on us.
        _xtest_scoreboard_unexpected_rules(test_env);
    }

    // here we just update the scoreboard count
    // add one to total tested cases and remove
    // one from untested ghost cases.
    _xtest_scoreboard_update(test_env);
}

// ==============================================================================
// Xtest internal handlers for tags and markers
// ==============================================================================

static void _xtest_assert_handle_tag_slow(xtest* test_case) {
    clock_t end = clock();
    test_case->timer.elapsed = end - test_case->timer.start;
    test_case->timer.detail.milliseconds = (int64_t)((test_case->timer.elapsed - (int64_t)test_case->timer.elapsed) * 1000);

    if (test_case->timer.detail.milliseconds > MAX_EXPECTED_TIME_SLOW) {
        xconsole_out("red", "Test case exceeded the expected time for slow tag\n");
        _xtest_env.rule.should_timeout = false;
        _xtest_env.rule.should_pass    = false;
    }
}

static void _xtest_assert_handle_tag_fast(xtest* test_case) {
    clock_t end = clock();
    test_case->timer.elapsed = end - test_case->timer.start;
    test_case->timer.detail.milliseconds = (int64_t)((test_case->timer.elapsed - (int64_t)test_case->timer.elapsed) * 1000);

    if (test_case->timer.detail.milliseconds > MAX_EXPECTED_TIME_FAST) {
        xconsole_out("red", "Test case exceeded the expected time for fast tag\n");
        _xtest_env.rule.should_timeout = false;
        _xtest_env.rule.should_pass    = false;
    }
}

// features to be added in a next release.
static void _xtest_assert_handle_tag_bug(xtest* test_case) {
    // Handle bug tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_feature(xtest* test_case) {
    // Handle feature tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_security(xtest* test_case) {
    // Handle security tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_performance(xtest* test_case) {
    // Handle performance tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_stress(xtest* test_case) {
    // Handle stress tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_regression(xtest* test_case) {
    // Handle regression tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_compatibility(xtest* test_case) {
    // Handle compatibility tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_usability(xtest* test_case) {
    // Handle usability tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_robustness(xtest* test_case) {
    // Handle robustness tag logic here
    (void)test_case;
}

static void _xtest_assert_handle_tag_corner_case(xtest* test_case) {
    // Handle corner case tag logic here
    (void)test_case;
}


// ==============================================================================
// Xtest basic utility functions
// ==============================================================================

void _xtest_assume_unit_apply_xtags(xtest* test_case) {
     if (strcmp(test_case->tags->name, "default") != 0) {
        if (strcmp(test_case->tags->name, "bug") == 0) {
            _xtest_assert_handle_tag_bug(test_case);
        } else if (strcmp(test_case->tags->name, "feature") == 0) {
            _xtest_assert_handle_tag_feature(test_case);
        } else if (strcmp(test_case->tags->name, "security") == 0) {
            _xtest_assert_handle_tag_security(test_case);
        } else if (strcmp(test_case->tags->name, "performance") == 0) {
            _xtest_assert_handle_tag_performance(test_case);
        } else if (strcmp(test_case->tags->name, "stress") == 0) {
            _xtest_assert_handle_tag_stress(test_case);
        } else if (strcmp(test_case->tags->name, "regression") == 0) {
            _xtest_assert_handle_tag_regression(test_case);
        } else if (strcmp(test_case->tags->name, "compatibility") == 0) {
            _xtest_assert_handle_tag_compatibility(test_case);
        } else if (strcmp(test_case->tags->name, "usability") == 0) {
            _xtest_assert_handle_tag_usability(test_case);
        } else if (strcmp(test_case->tags->name, "robustness") == 0) {
            _xtest_assert_handle_tag_robustness(test_case);
        } else if (strcmp(test_case->tags->name, "corner case") == 0) {
            _xtest_assert_handle_tag_corner_case(test_case);
        }
    }
}

void _xtest_assume_unit_apply_marks(xtest* test_case) {
    if (strcmp(test_case->marks->name, "default") != 0) {
        if (strcmp(test_case->marks->name, "skip") == 0) {
            _xtest_env.rule.skipped = true;
        } else if (strcmp(test_case->marks->name, "fail") == 0) {
            _xtest_env.rule.result = false;
            _xassert_info.should_fail = true; // based on rules applyed from 'fail' mark
        } else if (strcmp(test_case->marks->name, "pass") == 0) {
            _xtest_env.rule.result = true;
        } else if (strcmp(test_case->marks->name, "timeout") == 0) {
            _xtest_env.rule.timeout = true;
            _xtest_env.rule.timeout = true;
        } else if (strcmp(test_case->marks->name, "error") == 0) {
            _xtest_env.rule.error = true;
        } else if (strcmp(test_case->marks->name, "none") == 0) {
            // Do nothing
        } else if (strcmp(test_case->marks->name, "only") == 0) {
            // Do nothing
        }
    }
}

void _xtest_assume_unit_check_xtags(xtest* test_case) {
    if (strcmp(test_case->tags->name, "default") != 0) {
        if (strcmp(test_case->tags->name, "fast") == 0) {
            _xtest_assert_handle_tag_fast(test_case);
        } else if (strcmp(test_case->tags->name, "slow") == 0) {
            _xtest_assert_handle_tag_slow(test_case);
        }
    }
}

void _xtest_assume_unit(xtest* test_case) {
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

void _xtest_assume_unit_runner(xtest* test_case) {
    test_case->timer.start = clock();
    output_start_test(test_case, &_xtest_env);

    // setting and restting the assert info
    _xassert_info.has_assert  = false; // Never assume the tester added an assert EVER!
    _xassert_info.expression  = true;  // Assume the expression is true until proven false
    _xassert_info.should_fail = false; // Assume the expression should pass until proven false

    _xtest_assume_unit_apply_marks(test_case);
    _xtest_assume_unit_apply_xtags(test_case);

    if (!_xtest_env.rule.skipped) {
        if (!xcli.dry_run) {
            _xtest_assume_unit(test_case);
        } else {
            xconsole_out("blue", "Simulating test case...\n");
        }
        _xtest_assume_unit_check_xtags(test_case); // Check tags
    }

    output_end_test(test_case);
    _xtest_scoreboard(&_xtest_env, test_case);
}

// ==============================================================================
// Xtest create and erase
// ==============================================================================

xenv _xtest_environment_create(int argc, xstring *argv) {
    xparser_parse_args(argc, argv);
    xenv new_env;

    new_env.stats = (xstats){0, 0, 0, 0, 0, 0, 0, 0};
    new_env.timer = (xtime){0, 0, 0, {0, 0, 0, 0, 0}};
    new_env.rule  = (xrule){false, true, false, true, false, false, false, false};
    new_env.queue = xqueue_create(); // Create priority queue

    new_env.timer.start = clock(); // Start the timer

    // as a safty mesure we provide an atexit handler to avoid memory leaks
    atexit(_xtest_environment_erase); // Register cleanup function
    
    return new_env;
}

void _xtest_environment_erase(void) {
    xqueue_erase(_xtest_env.queue);

    // ensure summary dosent print twice if we happen to call exit
    if (!_xtest_env.rule.should_pass) {
        _xtest_environment_summary();
    }
}

void _xtest_environment_add(xenv* test_env, xtest* test_case, xfixture* fixture) {
    if (fixture != xnullptr && fixture->setup != xnullptr && fixture->teardown != xnullptr) {
        test_case->fixture.setup = fixture->setup;
        test_case->fixture.teardown = fixture->teardown;
    } else {
        test_case->fixture.setup = xnullptr;
        test_case->fixture.teardown = xnullptr;
    }

    // here we count up the untested cases
    test_env->stats.untested_count++;
    xqueue_enqueue(test_env->queue, test_case);
}

void _xtest_environment_run(void) {
    while (!xqueue_is_empty(_xtest_env.queue)) {
        xtest* current_test = xqueue_dequeue(_xtest_env.queue);
        if (current_test != xnullptr) {
            _xtest_assume_unit_runner(current_test);
        }
    }
}

int _xtest_environment_summary(void) {
    int result = (_xtest_env.stats.untested_count          + // Count of untested cases
                  _xtest_env.stats.expected_failed_count   + // Count of expected failed cases
                  _xtest_env.stats.unexpected_passed_count + // Count of unexpected passed cases
                  _xtest_env.stats.expected_timeout_count  + // Count of expected timeout cases
                  _xtest_env.stats.unexpected_failed_count); // Count of unexpected failed cases
    output_summary_format(&_xtest_env);
    return result;
}

// ==============================================================================
// Xmark functions for benchmarks
// ==============================================================================

//
// local types
//
static uint64_t start_time;

#if defined(_WIN32)
static double frequency; // Variable to store the frequency for Windows
#endif

void xtest_start_benchmark(void) {
#if defined(_WIN32)
    LARGE_INTEGER freq;
    if (!QueryPerformanceFrequency(&freq)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceFrequency failed\n");
        exit(EXIT_FAILURE);
    }
    frequency = (double)freq.QuadPart;
    if (!QueryPerformanceCounter((LARGE_INTEGER*)&start_time)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceCounter failed\n");
        exit(EXIT_FAILURE);
    }
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        // Handle error
        perror("Error: clock_gettime failed");
        exit(EXIT_FAILURE);
    }
    start_time = ts.tv_sec * 1e9 + ts.tv_nsec;
#endif
}

uint64_t xtest_stop_benchmark(void) {
#if defined(_WIN32)
    LARGE_INTEGER end_time;
    if (!QueryPerformanceCounter(&end_time)) {
        // Handle error
        fprintf(stderr, "Error: QueryPerformanceCounter failed\n");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)((end_time.QuadPart - start_time) * 1e9 / frequency);
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        // Handle error
        perror("Error: clock_gettime failed");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)((ts.tv_sec * 1e9 + ts.tv_nsec) - start_time);
#endif
}

static void assume_duration(double expected, double actual, double unit) {
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / ((double)CLOCKS_PER_SEC / unit);
    if (elapsed_time < expected) {
        output_benchmark_format(expected, actual);
    }
}

// Marks a test case as timeout with a specified time and prints it to stderr.
void xbenchmark(xstring duration_type, double expected, double actual) {
    if (strcmp(duration_type, "minutes") == 0) {
        assume_duration(expected, actual, 60.0);
    } else if (strcmp(duration_type, "seconds") == 0) {
        assume_duration(expected, actual, 1.0);
    } else if (strcmp(duration_type, "milliseconds") == 0) {
        assume_duration(expected, actual, 0.001);
    } else if (strcmp(duration_type, "microseconds") == 0) {
        assume_duration(expected, actual, 1e-6);
    } else if (strcmp(duration_type, "nanoseconds") == 0) {
        assume_duration(expected, actual, 1e-9);
    } else if (strcmp(duration_type, "picoseconds") == 0) {
        assume_duration(expected, actual, 1e-12);
    } else if (strcmp(duration_type, "femtoseconds") == 0) {
        assume_duration(expected, actual, 1e-15);
    } else if (strcmp(duration_type, "attoseconds") == 0) {
        assume_duration(expected, actual, 1e-18);
    } else if (strcmp(duration_type, "zeptoseconds") == 0) {
        assume_duration(expected, actual, 1e-21);
    } else if (strcmp(duration_type, "yoctoseconds") == 0) {
        assume_duration(expected, actual, 1e-24);
    } else {
        xconsole_out("red", "Unknown option: %s\n", duration_type);
    }
} // end of func

// ==============================================================================
// Xtest functions for markers and tags
// ==============================================================================

// Function to apply priority to the test case based on a keyword
void _xtest_apply_priority(xtest *test_case, xstring priority) {
    if (!test_case) {
        xconsole_out("red", "Error: Test case pointer is xnullptr\n");
        return;
    } else if (!priority) {
        xconsole_out("red", "Error: Invalid priority\n");
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

void _xtest_apply_xtag(xtest* test_case, xstring tag) {
    if (!test_case) {
        xconsole_out("red", "Test case pointer is xnullptr\n");
        return;
    } else if (!tag) {
        xconsole_out("red", "Error: Invalid xtag %s\n", tag);
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
        xconsole_out("red", "Error: Invalid xtag %s\n", tag);
    }
}

void _xtest_apply_mark(xtest* test_case, xstring mark) {
    if (!test_case) {
        xconsole_out("red", "Test case pointer is xnullptr\n");
        return;
    } else if (!mark) {
        xconsole_out("red", "Error: Invalid marker %s\n", mark);
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
        xconsole_out("red", "Error: Invalid marker %s\n", mark);
    }
}

// ==============================================================================
// Xtest functions for asserts
// ==============================================================================

// assertion classes should abort like normal without memory leaks

// Custom assumptions function with optional message.
void xtest_assert_impl_assume(bool expression, const xstring message, const xstring file, int line, const xstring func) {
    if (_xtest_env.current_assume_count == XTEST_ASSUME_MAX) {
        exit(XTEST_ABORT_FAIL);
        return;
    }

    if (!_xassert_info.should_fail) {
        if (!expression) {
            _xtest_env.rule.should_pass = false;
            _xtest_env.current_assume_count++;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _xtest_env.rule.should_pass = true;
        } else if (expression) {
            _xtest_env.rule.should_pass = false;
            _xtest_env.current_assume_count++;
            output_assume_format(message, file, line, func);
        }
    }
} // end of func

// Custom assertion function with optional message.
void xtest_assert_impl_assert(bool expression, const xstring message, const xstring file, int line, const xstring func) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _xtest_env.rule.should_pass = true;
        } else if (expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(XTEST_ABORT_FAIL);
        }
    } else {
        if (!expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(XTEST_ABORT_FAIL);
        }
    }
} // end of func

// Custom assertion function with optional message.
void xtest_assert_impl_sanity(bool expression, const xstring message, const xstring file, int line, const xstring func) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _xtest_env.rule.should_pass = true;
        } else if (expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(XTEST_ABORT_FAIL);
        }
    } else {
        if (!expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
            exit(XTEST_ABORT_FAIL);
        }
    }
} // end of func

// Custom expectation function with optional message.
void xtest_assert_impl_expect(bool expression, const xstring message, const xstring file, int line, const xstring func) {
    if (_xassert_info.should_fail) {
        if (!expression) {
            _xtest_env.rule.should_pass = true;
        } else if (expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _xtest_env.rule.should_pass = false;
            output_assume_format(message, file, line, func);
        }
    }
} // end of func

// Custom expectation function with optional message.
void xtest_assert_impl_except(bool expression, const xstring message, const xstring file, int line, const xstring func) {
    if (_xtest_env.current_except_count == XTEST_EXCEPT_MAX) {
        return;
    }

    if (_xassert_info.should_fail) {
        if (!expression) {
            _xtest_env.rule.should_pass = true;
        } else {
            _xtest_env.rule.should_pass = false;
            _xtest_env.current_except_count++;
            output_assume_format(message, file, line, func);
        }
    } else {
        if (!expression) {
            _xtest_env.rule.should_pass = false;
            _xtest_env.current_except_count++;
            output_assume_format(message, file, line, func);
        }
    }
} // end of func

void _xtest_assert_class(bool expression, xassert_type_rule behavor, xstring message, xstring file, int line, xstring func) {
    if (behavor == TEST_ASSERT_AS_CLASS_ASSUME) {
        xtest_assert_impl_assume(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_ASSERT) {
        xtest_assert_impl_assert(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXPECT) {
        xtest_assert_impl_expect(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_SANITY) {
        xtest_assert_impl_sanity(expression, message, file, line, func);
    } else if (behavor == TEST_ASSERT_AS_CLASS_EXCEPT) {
        xtest_assert_impl_except(expression, message, file, line, func);
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
