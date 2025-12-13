/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/pizza/common.h"
#include <stdio.h>

// *****************************************************************************
// macro definitions
// *****************************************************************************

#define FOSSIL_PIZZA_VERSION "1.3.1"
#define FOSSIL_PIZZA_AUTHOR "Fossil Logic"
#define FOSSIL_PIZZA_WEBSITE "https://fossillogic.com"

// *****************************************************************************
// exported flags
// *****************************************************************************

uint64_t G_PIZZA_TIMEOUT = 60; // Default timeout in seconds
int G_PIZZA_DRY_RUN = 0;
int G_PIZZA_FAIL_FAST = 0;
int G_PIZZA_SKIP = 0;
const char* G_PIZZA_ONLY = null;
int G_PIZZA_REPEAT = 0;
int G_PIZZA_THREADS = 1;
fossil_pizza_cli_theme_t G_PIZZA_THEME     = PIZZA_THEME_FOSSIL;

// *****************************************************************************
// Hashing algorithm
// *****************************************************************************

// HASH Algorithm magic

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
uint64_t get_pizza_time_microseconds(void) {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t t = ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    return t / 10; // 100-nanosecond intervals to microseconds
}
#else
#include <sys/time.h>
uint64_t get_pizza_time_microseconds(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + tv.tv_usec;
}
#endif

static uint64_t get_pizza_device_salt(void) {
    // FNV-1a 64-bit base offset
    uint64_t hash = 0xcbf29ce484222325ULL;

    // Cross-platform user and home detection
#if defined(_WIN32) || defined(_WIN64)
    const char *vars[] = {
        getenv("USERNAME"),
        getenv("USERPROFILE"),
        getenv("COMPUTERNAME")
    };
#else
    const char *vars[] = {
        getenv("USER"),
        getenv("HOME"),
        getenv("SHELL"),
        getenv("HOSTNAME")
    };
#endif

    // Mix in each variable if it exists
    for (size_t v = 0; v < sizeof(vars) / sizeof(vars[0]); ++v) {
        const char *val = vars[v];
        if (val) {
            for (size_t i = 0; val[i]; ++i) {
                hash ^= (uint8_t)val[i];
                hash *= 0x100000001b3ULL;
            }
        }
    }

    return hash;
}

void fossil_pizza_hash(const char *input, const char *output, uint8_t *hash_out) {
    const uint64_t PRIME = 0x100000001b3ULL;
    static uint64_t SALT = 0;
    if (SALT == 0) SALT = get_pizza_device_salt();  // Initialize salt once

    uint64_t state1 = 0xcbf29ce484222325ULL ^ SALT;
    uint64_t state2 = 0x84222325cbf29ce4ULL ^ ~SALT;

    size_t in_len = strlen(input);
    size_t out_len = strlen(output);

    uint64_t nonce = get_pizza_time_microseconds();  // Microsecond resolution

    for (size_t i = 0; i < in_len; ++i) {
        state1 ^= (uint8_t)input[i];
        state1 *= PRIME;
        state1 ^= (state1 >> 27);
        state1 ^= (state1 << 33);
    }

    for (size_t i = 0; i < out_len; ++i) {
        state2 ^= (uint8_t)output[i];
        state2 *= PRIME;
        state2 ^= (state2 >> 29);
        state2 ^= (state2 << 31);
    }

    // Nonce and length entropy
    state1 ^= nonce ^ ((uint64_t)in_len << 32);
    state2 ^= ~nonce ^ ((uint64_t)out_len << 16);

    // Mixing rounds
    for (int i = 0; i < 6; ++i) {
        state1 += (state2 ^ (state1 >> 17));
        state2 += (state1 ^ (state2 >> 13));
        state1 ^= (state1 << 41);
        state2 ^= (state2 << 37);
        state1 *= PRIME;
        state2 *= PRIME;
    }

    for (size_t i = 0; i < FOSSIL_PIZZA_HASH_SIZE; ++i) {
        uint64_t mixed = (i % 2 == 0) ? state1 : state2;
        mixed ^= (mixed >> ((i % 7) + 13));
        mixed *= PRIME;
        mixed ^= SALT;
        hash_out[i] = (uint8_t)((mixed >> (8 * (i % 8))) & 0xFF);
    }
}


// *****************************************************************************
// command pallet
// *****************************************************************************

// Lookup tables for valid tags and criteria
static const char* VALID_TAGS[] = {
    "fossil",       // default tag
    "ai",           // Jellyfish AI tag
    "network",      // Network-related tests
    "database",     // Database-related tests
    "ui",           // User Interface tests
    "api",          // API-related tests
    "critical",     // Critical tests
    "media",        // Media tests
    null // Sentinel to mark the end
};

static const char* VALID_CRITERIA[] = {
    "name",
    "time",
    "result",
    "priority",
    "hash",
    null // Sentinel to mark the end
};

static void _show_help(void) {
    pizza_io_printf("{blue}Usage: pizza [options] [command]{reset}\n");
    pizza_io_printf("{blue}Options:{reset}\n");
    pizza_io_printf("{cyan}  --version          Show version information{reset}\n");
    pizza_io_printf("{cyan}  --dry-run          Perform a dry run without executing commands{reset}\n");
    pizza_io_printf("{cyan}  --host             Show information about the current host{reset}\n");
    pizza_io_printf("{cyan}  --help             Show this help message{reset}\n");
    pizza_io_printf("{blue}Commands:{reset}\n");
    pizza_io_printf("{cyan}  run                Execute tests with optional parameters{reset}\n");
    pizza_io_printf("{cyan}  filter             Filter tests based on criteria{reset}\n");
    pizza_io_printf("{cyan}  sort               Sort tests by specified criteria{reset}\n");
    pizza_io_printf("{cyan}  shuffle            Shuffle tests with optional parameters{reset}\n");
    pizza_io_printf("{cyan}  show               Show test cases with optional parameters{reset}\n");
    pizza_io_printf("{cyan}  color=<mode>       Set color mode (enable, disable, auto){reset}\n");
    pizza_io_printf("{cyan}  config=<file>      Specify a configuration file (must be pizza_test.ini){reset}\n");
    pizza_io_printf("{cyan}  theme=<name>       Set the theme (fossil, catch, doctest, etc.){reset}\n");
    pizza_io_printf("{cyan}  timeout=<seconds>  Set the timeout for commands (default: 60 seconds){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_run(void) {
    pizza_io_printf("{blue}Run command options:{reset}\n");
    pizza_io_printf("{cyan}  --fail-fast        Stop on the first failure{reset}\n");
    pizza_io_printf("{cyan}  --only <test>      Run only the specified test{reset}\n");
    pizza_io_printf("{cyan}  --skip <test>      Skip the specified test{reset}\n");
    pizza_io_printf("{cyan}  --repeat <count>   Repeat the test a specified number of times{reset}\n");
    pizza_io_printf("{cyan}  --help             Show help for run command{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_filter(void) {
    pizza_io_printf("{blue}Filter command options:{reset}\n");
    pizza_io_printf("{cyan}  --test-name <name> Filter by test name{reset}\n");
    pizza_io_printf("{cyan}  --suite-name <name> Filter by suite name{reset}\n");
    pizza_io_printf("{cyan}  --tag <tag>        Filter by tag{reset}\n");
    pizza_io_printf("{cyan}  --help             Show help for filter command{reset}\n");
    pizza_io_printf("{cyan}  --options          Show all valid tags{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_sort(void) {
    pizza_io_printf("{blue}Sort command options:{reset}\n");
    pizza_io_printf("{cyan}  --by <criteria>    Sort by specified criteria{reset}\n");
    pizza_io_printf("{cyan}  --order <asc|desc> Sort in ascending or descending order{reset}\n");
    pizza_io_printf("{cyan}  --help             Show help for sort command{reset}\n");
    pizza_io_printf("{cyan}  --options          Show all valid criteria{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_shuffle(void) {
    pizza_io_printf("{blue}Shuffle command options:{reset}\n");
    pizza_io_printf("{cyan}  --seed <seed>      Specify the seed for shuffling{reset}\n");
    pizza_io_printf("{cyan}  --count <count>    Number of items to shuffle{reset}\n");
    pizza_io_printf("{cyan}  --by <criteria>    Shuffle by specified criteria{reset}\n");
    pizza_io_printf("{cyan}  --help             Show help for shuffle command{reset}\n");
    pizza_io_printf("{cyan}  --options          Show all valid criteria for shuffling{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_color(void) {
    pizza_io_printf("{blue}Color command options:{reset}\n");
    pizza_io_printf("{cyan}  enable            Enable color output{reset}\n");
    pizza_io_printf("{cyan}  disable           Disable color output{reset}\n");
    pizza_io_printf("{cyan}  auto              Auto-detect color support{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_theme(void) {
    pizza_io_printf("{blue}Theme command options:{reset}\n");
    pizza_io_printf("{cyan}  fossil            Fossil theme (C, C++ Fossil Test Framework){reset}\n");
    pizza_io_printf("{cyan}  catch             Catch theme (C++ Test Framework){reset}\n");
    pizza_io_printf("{cyan}  doctest           Doctest theme (C++ Test Framework){reset}\n");
    pizza_io_printf("{cyan}  cpputest          CppUTest theme (C Test Framework){reset}\n");
    pizza_io_printf("{cyan}  tap               TAP theme (C Test Framework){reset}\n");
    pizza_io_printf("{cyan}  gtest             GoogleTest theme (C++ Test Framework){reset}\n");
    pizza_io_printf("{cyan}  unity             Unity theme (C Test Framework){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_show(void) {
    pizza_io_printf("{blue}Show command options:{reset}\n");
    pizza_io_printf("{cyan}  --test-name <name>   Filter by test name{reset}\n");
    pizza_io_printf("{cyan}  --suite-name <name>  Filter by suite name{reset}\n");
    pizza_io_printf("{cyan}  --tag <tag>          Filter by tag{reset}\n");
    pizza_io_printf("{cyan}  --result <result>    Filter by result (pass, fail, timeout, skipped, unexpected){reset}\n");
    pizza_io_printf("{cyan}  --verbose <level>    Set verbosity level (plain, ci, doge){reset}\n");
    pizza_io_printf("{cyan}  --mode <mode>        Show mode (list, tree, graph){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_version(void) {
    pizza_io_printf("{blue}Pizza Test Version: {cyan}%s{reset}\n", FOSSIL_PIZZA_VERSION);
    exit(EXIT_SUCCESS);
}

static void _show_host(void) {
    pizza_sys_hostinfo_system_t system_info;
    pizza_sys_hostinfo_architecture_t arch_info;
    pizza_sys_hostinfo_memory_t memory_info;
    pizza_sys_hostinfo_endianness_t endianness_info;

    if (pizza_sys_hostinfo_get_system(&system_info) == 0) {
        pizza_io_printf("{blue}Operating System: {cyan}%s{reset}\n", system_info.os_name);
        pizza_io_printf("{blue}OS Version: {cyan}%s{reset}\n", system_info.os_version);
        pizza_io_printf("{blue}Kernel Version: {cyan}%s{reset}\n", system_info.kernel_version);
        pizza_io_printf("{blue}Hostname: {cyan}%s{reset}\n", system_info.hostname);
        pizza_io_printf("{blue}Username: {cyan}%s{reset}\n", system_info.username);
        pizza_io_printf("{blue}Domain Name: {cyan}%s{reset}\n", system_info.domain_name);
        pizza_io_printf("{blue}Machine Type: {cyan}%s{reset}\n", system_info.machine_type);
        pizza_io_printf("{blue}Platform: {cyan}%s{reset}\n", system_info.platform);
    } else {
        pizza_io_printf("{red}Error retrieving system information.{reset}\n");
    }

    if (pizza_sys_hostinfo_get_architecture(&arch_info) == 0) {
        pizza_io_printf("{blue}Architecture: {cyan}%s{reset}\n", arch_info.architecture);
        pizza_io_printf("{blue}CPU: {cyan}%s{reset}\n", arch_info.cpu);
        pizza_io_printf("{blue}CPU Cores: {cyan}%s{reset}\n", arch_info.cpu_cores);
        pizza_io_printf("{blue}CPU Threads: {cyan}%s{reset}\n", arch_info.cpu_threads);
        pizza_io_printf("{blue}CPU Frequency: {cyan}%s{reset}\n", arch_info.cpu_frequency);
        pizza_io_printf("{blue}CPU Architecture: {cyan}%s{reset}\n", arch_info.cpu_architecture);
    } else {
        pizza_io_printf("{red}Error retrieving architecture information.{reset}\n");
    }

    if (pizza_sys_hostinfo_get_memory(&memory_info) == 0) {
        pizza_io_printf("{blue}Total Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.total_memory);
        pizza_io_printf("{blue}Free Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.free_memory);
        pizza_io_printf("{blue}Used Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.used_memory);
        pizza_io_printf("{blue}Available Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.available_memory);
        pizza_io_printf("{blue}Total Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.total_swap);
        pizza_io_printf("{blue}Free Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.free_swap);
        pizza_io_printf("{blue}Used Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.used_swap);
    } else {
        pizza_io_printf("{red}Error retrieving memory information.{reset}\n");
    }

    if (pizza_sys_hostinfo_get_endianness(&endianness_info) == 0) {
        pizza_io_printf("{blue}Endianness: {cyan}%s{reset}\n", 
                        endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
    } else {
        pizza_io_printf("{red}Error retrieving endianness information.{reset}\n");
    }

    exit(EXIT_SUCCESS);
}

fossil_pizza_pallet_t fossil_pizza_pallet_create(int argc, char** argv) {
    fossil_pizza_pallet_t pallet = {0};
    int is_command = 0; // Variable to track if a command is being processed

    pallet.show.enabled = 0; // Initialize show command enabled flag

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (pizza_io_cstr_compare(argv[i], "--dry-run") == 0) {
            G_PIZZA_DRY_RUN = 1;
        } else if (pizza_io_cstr_compare(argv[i], "--version") == 0) {
            _show_version();
        } else if (pizza_io_cstr_compare(argv[i], "--help") == 0) {
            _show_help();
        } else if (pizza_io_cstr_compare(argv[i], "--host") == 0) {
            _show_host();
        } else if (pizza_io_cstr_compare(argv[i], "run") == 0) {
            is_command = 1;
            pallet.run.fail_fast = 0;
            pallet.run.only = null;
            pallet.run.skip = null;
            pallet.run.repeat = 1;

            for (int j = i + 1; j < argc; j++) {
                if (!is_command) break;
                if (pizza_io_cstr_compare(argv[j], "--fail-fast") == 0) {
                    pallet.run.fail_fast = 1;
                    G_PIZZA_FAIL_FAST = 1;
                } else if (pizza_io_cstr_compare(argv[j], "--only") == 0 && j + 1 < argc) {
                    // Support multiple test cases separated by comma, and wildcards
                    j++;
                    size_t count = 0;
                    cstr *test_cases = pizza_io_cstr_split(argv[j], ',', &count);
                    pallet.run.only = argv[j]; // Store raw string for now
                    pallet.run.only_cases = test_cases;
                    pallet.run.only_count = count;
                    // Wildcard support: mark if any test case contains '*'
                    pallet.run.only_has_wildcard = 0;
                    for (size_t k = 0; k < count; k++) {
                        if (strchr(test_cases[k], '*')) {
                            pallet.run.only_has_wildcard = 1;
                            break;
                        }
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--skip") == 0 && j + 1 < argc) {
                    pallet.run.skip = argv[++j];
                    G_PIZZA_SKIP = 1;
                } else if (pizza_io_cstr_compare(argv[j], "--repeat") == 0 && j + 1 < argc) {
                    pallet.run.repeat = atoi(argv[++j]);
                    G_PIZZA_REPEAT = pallet.run.repeat;
                } else if (pizza_io_cstr_compare(argv[j], "--threads") == 0 && j + 1 < argc) {
                    G_PIZZA_THREADS = atoi(argv[++j]);
                } else if (pizza_io_cstr_compare(argv[j], "--help") == 0) {
                    _show_subhelp_run();
                } else {
                    is_command = 0;
                }
            }
        } else if (pizza_io_cstr_compare(argv[i], "filter") == 0) {
            is_command = 1;
            pallet.filter.test_name = null;
            pallet.filter.suite_name = null;
            pallet.filter.tag = null;

            for (int j = i + 1; j < argc; j++) {
                if (!is_command) break;
                if (pizza_io_cstr_compare(argv[j], "--test-name") == 0 && j + 1 < argc) {
                    // Support multiple test names separated by comma, and wildcards
                    j++;
                    size_t count = 0;
                    cstr *test_names = pizza_io_cstr_split(argv[j], ',', &count);
                    pallet.filter.test_name = argv[j]; // Store raw string for now
                    pallet.filter.test_name_list = test_names;
                    pallet.filter.test_name_count = count;
                    // Wildcard support: mark if any test name contains '*'
                    pallet.filter.test_name_has_wildcard = 0;
                    for (size_t k = 0; k < count; k++) {
                        if (strchr(test_names[k], '*')) {
                            pallet.filter.test_name_has_wildcard = 1;
                            break;
                        }
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--suite-name") == 0 && j + 1 < argc) {
                    // Support multiple suite names separated by comma, and wildcards
                    j++;
                    size_t count = 0;
                    cstr *suite_names = pizza_io_cstr_split(argv[j], ',', &count);
                    pallet.filter.suite_name = argv[j]; // Store raw string for now
                    pallet.filter.suite_name_list = suite_names;
                    pallet.filter.suite_name_count = count;
                    // Wildcard support: mark if any suite name contains '*'
                    pallet.filter.suite_name_has_wildcard = 0;
                    for (size_t k = 0; k < count; k++) {
                        if (strchr(suite_names[k], '*')) {
                            pallet.filter.suite_name_has_wildcard = 1;
                            break;
                        }
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--tag") == 0 && j + 1 < argc) {
                    // Support multiple tags separated by comma, and wildcards
                    j++;
                    size_t count = 0;
                    cstr *tags = pizza_io_cstr_split(argv[j], ',', &count);
                    int valid_count = 0;
                    for (size_t k = 0; k < count; k++) {
                        int is_valid_tag = 0;
                        for (int t = 0; VALID_TAGS[t] != null; t++) {
                            if (pizza_io_cstr_compare(tags[k], VALID_TAGS[t]) == 0) {
                                is_valid_tag = 1;
                                break;
                            }
                        }
                        if (is_valid_tag || strchr(tags[k], '*')) {
                            valid_count++;
                        }
                    }
                    if (valid_count == (int)count) {
                        pallet.filter.tag = argv[j]; // Store raw string for now
                        pallet.filter.tag_list = tags;
                        pallet.filter.tag_count = count;
                        // Wildcard support: mark if any tag contains '*'
                        pallet.filter.tag_has_wildcard = 0;
                        for (size_t k = 0; k < count; k++) {
                            if (strchr(tags[k], '*')) {
                                pallet.filter.tag_has_wildcard = 1;
                                break;
                            }
                        }
                    } else {
                        pizza_io_printf("{red}Error: Invalid tag(s) in '%s'.{reset}\n", argv[j]);
                        exit(EXIT_FAILURE);
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--help") == 0) {
                    _show_subhelp_filter();
                } else if (pizza_io_cstr_compare(argv[j], "--options") == 0) {
                    pizza_io_printf("{blue}Valid tags:{reset}\n");
                    for (int k = 0; VALID_TAGS[k] != null; k++) {
                        pizza_io_printf("{cyan}  %s{reset}\n", VALID_TAGS[k]);
                    }
                    exit(EXIT_SUCCESS);
                } else {
                    is_command = 0;
                }
            }
        } else if (pizza_io_cstr_compare(argv[i], "sort") == 0) {
            is_command = 1;
            pallet.sort.by = null;
            pallet.sort.order = null;

            for (int j = i + 1; j < argc; j++) {
                if (!is_command) break;
                if (pizza_io_cstr_compare(argv[j], "--by") == 0 && j + 1 < argc) {
                    const char* criteria = argv[++j];
                    int is_valid_criteria = 0;
                    for (int k = 0; VALID_CRITERIA[k] != null; k++) {
                        if (pizza_io_cstr_compare(criteria, VALID_CRITERIA[k]) == 0) {
                            is_valid_criteria = 1;
                            break;
                        }
                    }
                    if (is_valid_criteria) {
                        pallet.sort.by = criteria;
                    } else {
                        pizza_io_printf("{red}Error: Invalid criteria '%s'.{reset}\n", criteria);
                        exit(EXIT_FAILURE);
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--order") == 0 && j + 1 < argc) {
                    pallet.sort.order = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--help") == 0) {
                    _show_subhelp_sort();
                } else if (pizza_io_cstr_compare(argv[j], "--options") == 0) {
                    pizza_io_printf("{blue}Valid criteria:{reset}\n");
                    for (int k = 0; VALID_CRITERIA[k] != null; k++) {
                        pizza_io_printf("{cyan}  %s{reset}\n", VALID_CRITERIA[k]);
                    }
                    exit(EXIT_SUCCESS);
                } else {
                    is_command = 0;
                }
            }
        } else if (pizza_io_cstr_compare(argv[i], "shuffle") == 0) {
            is_command = 1;
            pallet.shuffle.seed = null;
            pallet.shuffle.count = 0;
            pallet.shuffle.by = null;

            for (int j = i + 1; j < argc; j++) {
                if (!is_command) break;
                if (pizza_io_cstr_compare(argv[j], "--seed") == 0 && j + 1 < argc) {
                    pallet.shuffle.seed = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--count") == 0 && j + 1 < argc) {
                    pallet.shuffle.count = atoi(argv[++j]);
                } else if (pizza_io_cstr_compare(argv[j], "--by") == 0 && j + 1 < argc) {
                    pallet.shuffle.by = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--help") == 0) {
                    _show_subhelp_shuffle();
                } else if (pizza_io_cstr_compare(argv[j], "--options") == 0) {
                    pizza_io_printf("{blue}Valid criteria for shuffling:{reset}\n");
                    for (int k = 0; VALID_CRITERIA[k] != null; k++) {
                        pizza_io_printf("{cyan}  %s{reset}\n", VALID_CRITERIA[k]);
                    }
                    exit(EXIT_SUCCESS);
                } else {
                    is_command = 0;
                }
            }
        } else if (strncmp(argv[i], "color=", 6) == 0) {
            if (pizza_io_cstr_compare(argv[i] + 6, "enable") == 0) {
                PIZZA_IO_COLOR_ENABLE = 1;
            } else if (pizza_io_cstr_compare(argv[i] + 6, "disable") == 0) {
                PIZZA_IO_COLOR_ENABLE = 0;
            } else if (pizza_io_cstr_compare(argv[i] + 6, "auto") == 0) {
                if (isatty(STDOUT_FILENO)) {
                    PIZZA_IO_COLOR_ENABLE = 1;
                } else {
                    PIZZA_IO_COLOR_ENABLE = 0;
                }
            }
        } else if (pizza_io_cstr_compare(argv[i], "color") == 0) {
            if (i + 1 < argc && pizza_io_cstr_compare(argv[i + 1], "--help") == 0) {
                _show_subhelp_color();
            }
        } else if (strncmp(argv[i], "config=", 7) == 0) {
            const char* config_file = argv[i] + 7;
            const char* basename = strrchr(config_file, '/');
            if (!basename) {
                basename = config_file; // No '/' found, use the entire filename
            } else {
                basename++; // Skip the '/'
            }

            if (pizza_io_cstr_compare(basename, "pizza_test.ini") == 0) {
                pallet.config_file = config_file;
            } else {
                pizza_io_printf("{red}Error: Invalid configuration file name. Must be 'pizza_test.ini'.{reset}\n");
                exit(EXIT_FAILURE);
            }
        } else if (pizza_io_cstr_compare(argv[i], "config") == 0) {
            if (i + 1 < argc && pizza_io_cstr_compare(argv[i + 1], "--help") == 0) {
                _show_help();
            }
        } else if (strncmp(argv[i], "theme=", 6) == 0) {
            const char* theme_str = argv[i] + 6;
            if (pizza_io_cstr_compare(theme_str, "fossil") == 0) {
                pallet.theme = PIZZA_THEME_FOSSIL;
                G_PIZZA_THEME = PIZZA_THEME_FOSSIL;
            } else if (pizza_io_cstr_compare(theme_str, "catch") == 0) {
                pallet.theme = PIZZA_THEME_CATCH;
                G_PIZZA_THEME = PIZZA_THEME_CATCH;
            } else if (pizza_io_cstr_compare(theme_str, "doctest") == 0) {
                pallet.theme = PIZZA_THEME_DOCTEST;
                G_PIZZA_THEME = PIZZA_THEME_DOCTEST;
            } else if (pizza_io_cstr_compare(theme_str, "cpputest") == 0) {
                pallet.theme = PIZZA_THEME_CPPUTEST;
                G_PIZZA_THEME = PIZZA_THEME_CPPUTEST;
            } else if (pizza_io_cstr_compare(theme_str, "tap") == 0) {
                pallet.theme = PIZZA_THEME_TAP;
                G_PIZZA_THEME = PIZZA_THEME_TAP;
            } else if (pizza_io_cstr_compare(theme_str, "gtest") == 0) {
                pallet.theme = PIZZA_THEME_GOOGLETEST;
                G_PIZZA_THEME = PIZZA_THEME_GOOGLETEST;
            } else if (pizza_io_cstr_compare(theme_str, "unity") == 0) {
                pallet.theme = PIZZA_THEME_UNITY;
                G_PIZZA_THEME = PIZZA_THEME_UNITY;
            }
        } else if (pizza_io_cstr_compare(argv[i], "theme") == 0) {
            if (i + 1 < argc && pizza_io_cstr_compare(argv[i + 1], "--help") == 0) {
                _show_subhelp_theme();
            }
        } else if (strncmp(argv[i], "timeout=", 8) == 0) {
            G_PIZZA_TIMEOUT = atoi(argv[i] + 8);
        } else if (pizza_io_cstr_compare(argv[i], "timeout") == 0) {
            if (i + 1 < argc && pizza_io_cstr_compare(argv[i + 1], "--help") == 0) {
                _show_help();
                exit(EXIT_SUCCESS);
            }
        } else if (pizza_io_cstr_compare(argv[i], "show") == 0) {
            is_command = 1;
            pallet.show.test_name = null;
            pallet.show.suite_name = null;
            pallet.show.tag = null;
            pallet.show.result = "fail";
            pallet.show.mode = "list";
            pallet.show.verbose = "plain";
            pallet.show.enabled = 1; // Default to enabled

            for (int j = i + 1; j < argc; j++) {
                if (!is_command) break;
                if (pizza_io_cstr_compare(argv[j], "--test-name") == 0 && j + 1 < argc) {
                    pallet.show.test_name = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--suite-name") == 0 && j + 1 < argc) {
                    pallet.show.suite_name = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--tag") == 0 && j + 1 < argc) {
                    pallet.show.tag = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--result") == 0 && j + 1 < argc) {
                    pallet.show.result = argv[++j];
                } else if (pizza_io_cstr_compare(argv[j], "--mode") == 0 && j + 1 < argc) {
                    pallet.show.mode = argv[++j];
                    // Validate mode (should be one of: list, tree, graph)
                    if (pizza_io_cstr_compare(pallet.show.mode, "list") != 0 &&
                        pizza_io_cstr_compare(pallet.show.mode, "tree") != 0 &&
                        pizza_io_cstr_compare(pallet.show.mode, "graph") != 0) {
                        pizza_io_printf("{red}Error: Invalid mode '%s'. Valid modes are: list, tree, graph.{reset}\n", pallet.show.mode);
                        exit(EXIT_FAILURE);
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--verbose") == 0 && j + 1 < argc) {
                    pallet.show.verbose = argv[++j];
                    // Validate verbose (should be one of: plain, ci, doge)
                    if (pizza_io_cstr_compare(pallet.show.verbose, "plain") != 0 &&
                        pizza_io_cstr_compare(pallet.show.verbose, "ci") != 0 &&
                        pizza_io_cstr_compare(pallet.show.verbose, "doge") != 0) {
                        pizza_io_printf("{red}Error: Invalid verbose level '%s'. Valid levels are: plain, ci, doge.{reset}\n", pallet.show.verbose);
                        exit(EXIT_FAILURE);
                    }
                } else if (pizza_io_cstr_compare(argv[j], "--help") == 0) {
                    _show_subhelp_show();
                } else {
                    is_command = 0;
                }
            }
        }
    }

    return pallet;
}

// *****************************************************************************
// INI Parser
// *****************************************************************************

int fossil_pizza_ini_parse(const char *filename, fossil_pizza_pallet_t *pallet) {
    pizza_io_printf("{yellow}Warning: INI parser is experimental and in development.{reset}\n");
    const char *basename = strrchr(filename, '/');
    if (!basename) {
        basename = filename; // No '/' found, use the entire filename
    } else {
        basename++; // Skip the '/'
    }

    if (pizza_io_cstr_compare(basename, "pizza_test.ini") != 0) {
        fprintf(stderr, "Error: INI file must be named 'pizza_test.ini'.\n");
        return -1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open INI file: %s\n", basename);
        return -1;
    }

    char line[256];
    char section[64] = "";
    while (fgets(line, sizeof(line), file)) {
        // Trim whitespace
        char *start = line;
        while (isspace((unsigned char)*start)) start++;
        char *end = start + strlen(start) - 1;
        while (end > start && isspace((unsigned char)*end)) *end-- = '\0';

        // Skip comments and empty lines
        if (*start == ';' || *start == '#' || *start == '\0') continue;

        // Handle section headers
        if (*start == '[') {
            char *close = strchr(start, ']');
            if (close) {
                *close = '\0';
                strncpy(section, start + 1, sizeof(section) - 1);
                section[sizeof(section) - 1] = '\0';
            }
            continue;
        }

        // Handle key-value pairs
        char *equals = strchr(start, '=');
        if (equals) {
            *equals = '\0';
            char *key = start;
            char *value = equals + 1;

            // Trim whitespace around key and value
            while (isspace((unsigned char)*key)) key++;
            end = key + strlen(key) - 1;
            while (end > key && isspace((unsigned char)*end)) *end-- = '\0';

            while (isspace((unsigned char)*value)) value++;
            end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char)*end)) *end-- = '\0';

            // Handle inline comments
            char *comment = strchr(value, ';');
            if (!comment) comment = strchr(value, '#');
            if (comment) *comment = '\0';

            // Trim whitespace again after removing comments
            end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char)*end)) *end-- = '\0';

            // Populate the pallet structure based on the section and key
            if (pizza_io_cstr_compare(section, "general") == 0) {
                if (pizza_io_cstr_compare(key, "theme") == 0) {
                    if (pizza_io_cstr_compare(value, "fossil") == 0) {
                        pallet->theme = PIZZA_THEME_FOSSIL;
                    } else if (pizza_io_cstr_compare(value, "catch") == 0) {
                        pallet->theme = PIZZA_THEME_CATCH;
                    } else if (pizza_io_cstr_compare(value, "doctest") == 0) {
                        pallet->theme = PIZZA_THEME_DOCTEST;
                    } else if (pizza_io_cstr_compare(value, "cpputest") == 0) {
                        pallet->theme = PIZZA_THEME_CPPUTEST;
                    } else if (pizza_io_cstr_compare(value, "tap") == 0) {
                        pallet->theme = PIZZA_THEME_TAP;
                    } else if (pizza_io_cstr_compare(value, "gtest") == 0) {
                        pallet->theme = PIZZA_THEME_GOOGLETEST;
                    } else if (pizza_io_cstr_compare(value, "unity") == 0) {
                        pallet->theme = PIZZA_THEME_UNITY;
                    }
                }
            } else if (pizza_io_cstr_compare(section, "test") == 0) {
                if (pizza_io_cstr_compare(key, "run.fail_fast") == 0) {
                    pallet->run.fail_fast = atoi(value);
                } else if (pizza_io_cstr_compare(key, "run.only") == 0) {
                    pallet->run.only = pizza_io_cstr_dup(value);
                } else if (pizza_io_cstr_compare(key, "run.repeat") == 0) {
                    pallet->run.repeat = atoi(value);
                } else if (pizza_io_cstr_compare(key, "filter.test_name") == 0) {
                    pallet->filter.test_name = pizza_io_cstr_dup(value);
                } else if (pizza_io_cstr_compare(key, "filter.suite_name") == 0) {
                    pallet->filter.suite_name = pizza_io_cstr_dup(value);
                } else if (pizza_io_cstr_compare(key, "filter.tag") == 0) {
                    int is_valid_tag = 0;
                    for (int i = 0; VALID_TAGS[i] != null; i++) {
                        if (pizza_io_cstr_compare(value, VALID_TAGS[i]) == 0) {
                            is_valid_tag = 1;
                            break;
                        }
                    }
                    if (is_valid_tag) {
                        pallet->filter.tag = pizza_io_cstr_dup(value);
                    } else {
                        fprintf(stderr, "Error: Invalid tag '%s'.\n", value);
                        fclose(file);
                        return -1;
                    }
                } else if (pizza_io_cstr_compare(key, "sort.by") == 0) {
                    int is_valid_criteria = 0;
                    for (int i = 0; VALID_CRITERIA[i] != null; i++) {
                        if (pizza_io_cstr_compare(value, VALID_CRITERIA[i]) == 0) {
                            is_valid_criteria = 1;
                            break;
                        }
                    }
                    if (is_valid_criteria) {
                        pallet->sort.by = pizza_io_cstr_dup(value);
                    } else {
                        fprintf(stderr, "Error: Invalid sort criteria '%s'.\n", value);
                        fclose(file);
                        return -1;
                    }
                } else if (pizza_io_cstr_compare(key, "sort.order") == 0) {
                    pallet->sort.order = pizza_io_cstr_dup(value);
                } else if (pizza_io_cstr_compare(key, "shuffle.seed") == 0) {
                    pallet->shuffle.seed = pizza_io_cstr_dup(value);
                } else if (pizza_io_cstr_compare(key, "shuffle.count") == 0) {
                    pallet->shuffle.count = atoi(value);
                } else if (pizza_io_cstr_compare(key, "shuffle.by") == 0) {
                    pallet->shuffle.by = pizza_io_cstr_dup(value);
                }
            } else if (pizza_io_cstr_compare(section, "mock") == 0) {
                // Add mock-related parsing logic here
            } else if (pizza_io_cstr_compare(section, "mark") == 0) {
                // Add mark-related parsing logic here
            } else if (pizza_io_cstr_compare(section, "sanity") == 0) {
                // Add sanity-related parsing logic here
            }
        }
    }

    fclose(file);
    return 0;
}

// *****************************************************************************
// Host information
// *****************************************************************************

int pizza_sys_hostinfo_get_system(pizza_sys_hostinfo_system_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osvi)) return -1;
    snprintf(info->os_name, sizeof(info->os_name), "Windows");
    snprintf(info->os_version, sizeof(info->os_version), "%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion);
    snprintf(info->kernel_version, sizeof(info->kernel_version), "%lu", osvi.dwBuildNumber);

    DWORD size = sizeof(info->hostname);
    GetComputerNameA(info->hostname, &size);

    size = sizeof(info->username);
    GetUserNameA(info->username, &size);

    // Domain name
    size = sizeof(info->domain_name);
    if (!GetEnvironmentVariableA("USERDOMAIN", info->domain_name, size)) {
        strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
        info->domain_name[sizeof(info->domain_name) - 1] = '\0';
    }

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    snprintf(info->machine_type, sizeof(info->machine_type), "%u", sysinfo.wProcessorArchitecture);
    snprintf(info->platform, sizeof(info->platform), "Win32");

#elif defined(__APPLE__)
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (gethostname(info->hostname, sizeof(info->hostname)) != 0)
        strncpy(info->hostname, "Unknown", sizeof(info->hostname) - 1);
    info->hostname[sizeof(info->hostname) - 1] = '\0';

    const char *user = getenv("USER");
    if (user)
        strncpy(info->username, user, sizeof(info->username) - 1);
    else
        strncpy(info->username, "Unknown", sizeof(info->username) - 1);
    info->username[sizeof(info->username) - 1] = '\0';

    strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
    info->domain_name[sizeof(info->domain_name) - 1] = '\0';

    strncpy(info->machine_type, sysinfo.machine, sizeof(info->machine_type) - 1);
    info->machine_type[sizeof(info->machine_type) - 1] = '\0';

    strncpy(info->platform, "Apple", sizeof(info->platform) - 1);
    info->platform[sizeof(info->platform) - 1] = '\0';

#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (gethostname(info->hostname, sizeof(info->hostname)) != 0)
        strncpy(info->hostname, "Unknown", sizeof(info->hostname) - 1);
    info->hostname[sizeof(info->hostname) - 1] = '\0';

    const char *user = getenv("USER");
    if (user)
        strncpy(info->username, user, sizeof(info->username) - 1);
    else
        strncpy(info->username, "Unknown", sizeof(info->username) - 1);
    info->username[sizeof(info->username) - 1] = '\0';

    const char *domain = getenv("DOMAINNAME");
    if (domain)
        strncpy(info->domain_name, domain, sizeof(info->domain_name) - 1);
    else
        strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
    info->domain_name[sizeof(info->domain_name) - 1] = '\0';

    strncpy(info->machine_type, sysinfo.machine, sizeof(info->machine_type) - 1);
    info->machine_type[sizeof(info->machine_type) - 1] = '\0';

    strncpy(info->platform, "Unix", sizeof(info->platform) - 1);
    info->platform[sizeof(info->platform) - 1] = '\0';

#endif
    return 0;
}

int pizza_sys_hostinfo_get_architecture(pizza_sys_hostinfo_architecture_t *info) {
    if (!info) return -1;

#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    // Architecture
    switch (sysinfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            strncpy(info->architecture, "x86_64", sizeof(info->architecture) - 1);
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            strncpy(info->architecture, "x86", sizeof(info->architecture) - 1);
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            strncpy(info->architecture, "ARM", sizeof(info->architecture) - 1);
            break;
        default:
            strncpy(info->architecture, "Unknown", sizeof(info->architecture) - 1);
            break;
    }
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    // CPU info (limited on Windows)
    strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
    info->cpu[sizeof(info->cpu) - 1] = '\0';

    snprintf(info->cpu_cores, sizeof(info->cpu_cores), "%lu", sysinfo.dwNumberOfProcessors);
    strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
    strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';

#elif defined(__APPLE__)
    size_t size = sizeof(info->architecture);
    if (sysctlbyname("hw.machine", info->architecture, &size, NULL, 0) != 0)
        strncpy(info->architecture, "Unknown", sizeof(info->architecture) - 1);
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    size = sizeof(info->cpu);
    if (sysctlbyname("machdep.cpu.brand_string", info->cpu, &size, NULL, 0) != 0)
        strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
    info->cpu[sizeof(info->cpu) - 1] = '\0';

    int cores = 0;
    size = sizeof(cores);
    if (sysctlbyname("hw.physicalcpu", &cores, &size, NULL, 0) == 0)
        snprintf(info->cpu_cores, sizeof(info->cpu_cores), "%d", cores);
    else
        strncpy(info->cpu_cores, "Unknown", sizeof(info->cpu_cores) - 1);
    info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';

    int threads = 0;
    size = sizeof(threads);
    if (sysctlbyname("hw.logicalcpu", &threads, &size, NULL, 0) == 0)
        snprintf(info->cpu_threads, sizeof(info->cpu_threads), "%d", threads);
    else
        strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';

    uint64_t freq = 0;
    size = sizeof(freq);
    if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) == 0)
        snprintf(info->cpu_frequency, sizeof(info->cpu_frequency), "%llu", (unsigned long long)freq);
    else
        strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';

    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';

#else
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0) return -1;

    strncpy(info->architecture, sysinfo.machine, sizeof(info->architecture) - 1);
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "model name", 10) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu, colon, sizeof(info->cpu) - 1);
                    info->cpu[sizeof(info->cpu) - 1] = '\0';
                }
            } else if (strncmp(line, "cpu cores", 9) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_cores, colon, sizeof(info->cpu_cores) - 1);
                    info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';
                }
            } else if (strncmp(line, "siblings", 8) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_threads, colon, sizeof(info->cpu_threads) - 1);
                    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
                }
            } else if (strncmp(line, "cpu MHz", 7) == 0) {
                char *colon = strchr(line, ':');
                if (colon) {
                    colon++;
                    while (*colon == ' ') colon++;
                    strncpy(info->cpu_frequency, colon, sizeof(info->cpu_frequency) - 1);
                    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
                }
            }
        }
        fclose(fp);
    } else {
        strncpy(info->cpu, "Unknown", sizeof(info->cpu) - 1);
        info->cpu[sizeof(info->cpu) - 1] = '\0';
        strncpy(info->cpu_cores, "Unknown", sizeof(info->cpu_cores) - 1);
        info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';
        strncpy(info->cpu_threads, "Unknown", sizeof(info->cpu_threads) - 1);
        info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
        strncpy(info->cpu_frequency, "Unknown", sizeof(info->cpu_frequency) - 1);
        info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
    }

    strncpy(info->cpu_architecture, info->architecture, sizeof(info->cpu_architecture) - 1);
    info->cpu_architecture[sizeof(info->cpu_architecture) - 1] = '\0';
#endif

    return 0;
}

int pizza_sys_hostinfo_get_memory(pizza_sys_hostinfo_memory_t *info) {
    if (!info) return -1;
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (!GlobalMemoryStatusEx(&statex)) return -1;
    info->total_memory = statex.ullTotalPhys;
    info->free_memory = statex.ullAvailPhys;
    info->used_memory = statex.ullTotalPhys - statex.ullAvailPhys;
    info->available_memory = statex.ullAvailPhys;
    info->total_swap = statex.ullTotalPageFile;
    info->free_swap = statex.ullAvailPageFile;
    info->used_swap = statex.ullTotalPageFile - statex.ullAvailPageFile;
#elif defined(__APPLE__)
    int64_t memsize;
    size_t len = sizeof(memsize);
    if (sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0) return -1;
    info->total_memory = memsize;
    info->free_memory = 0; // macOS does not provide free memory info in the same way
    info->used_memory = 0;
    info->available_memory = 0;
    info->total_swap = 0;
    info->free_swap = 0;
    info->used_swap = 0;
#else
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0) return -1;
    info->total_memory = sys_info.totalram * sys_info.mem_unit;
    info->free_memory = sys_info.freeram * sys_info.mem_unit;
    info->used_memory = (sys_info.totalram - sys_info.freeram) * sys_info.mem_unit;
    info->available_memory = sys_info.freeram * sys_info.mem_unit;
    info->total_swap = sys_info.totalswap * sys_info.mem_unit;
    info->free_swap = sys_info.freeswap * sys_info.mem_unit;
    info->used_swap = (sys_info.totalswap - sys_info.freeswap) * sys_info.mem_unit;
#endif
    return 0;
}

int pizza_sys_hostinfo_get_endianness(pizza_sys_hostinfo_endianness_t *info) {
    if (!info) return -1;
    uint16_t test = 0x0001;
    info->is_little_endian = (*(uint8_t*)&test) ? 1 : 0;
    return 0;
}

// *****************************************************************************
// soap sanitizer
// *****************************************************************************

#define MAX_CUSTOM_FILTERS 64

// Optional: reasoning / TI metadata
typedef struct {
    const char *category_name;
    const char *matched_pattern;
    int confidence; // 0-100
} soap_ti_reason_t;

/** Lookup table for rot-brain words and their suggested replacements */
static const struct {
    const char *bad;
    const char *suggested;
} FOSSIL_SOAP_SUGGESTIONS[] = {
    {"u", "you"},
    {"gonna", "going to"},
    {"ppl", "people"},
    {"funny", "laugh out loud"},
    {"lol", "laugh out loud"},
    {"idk", "I don't know"},
    {"wanna", "want to"},
    {"rizz", "charisma"},
    {"skibidi", "dance"},
    {"yeet", "throw"},
    {"sus", "suspicious"},
    {"vibe", "atmosphere"},
    {"lit", "exciting"},
    {"no cap", "honestly"},
    {"bet", "okay"},
    {"fam", "family"},
    {"bruh", "brother"},
    {"flex", "show off"},
    {"ghost", "ignore"},
    {"goat", "legend"},
    {"gucci", "good"},
    {"hype", "exciting"},
    {"janky", "low-quality"},
    {"lowkey", "somewhat"},
    {"mood", "feeling"},
    {"salty", "bitter"},
    {"shade", "insult"},
    {"slay", "impress"},
    {"snatched", "stylish"},
    {"stan", "superfan"},
    {"tea", "gossip"},
    {"thirsty", "desperate"},
    {"woke", "aware"},
    {"yolo", "live once"},
    {"zaddy", "attractive man"},
    {"drip", "fashion"},
    {"fire", "amazing"},
    {"omg", "surprising"},
    {"brb", "be right back"},
    {"imo", "in my opinion"},
    {"lmao", "laughing"},
    {"nvm", "never mind"},
    {"tbh", "to be honest"},
    {"tldr", "too long; didn't read"},
    {"ttyl", "talk to you later"},
    {"wyd", "what are you doing"},
    {"wtf", "what the heck"},
    {"yolo", "you only live once"},
    {"rot-brain", "stupid"},
    {"rot brain", "stupid"},
    {"rotbrain", "stupid"},
    {"smh", "shaking my head"},
    {"fomo", "fear of missing out"},
    {"bff", "best friend forever"},
    {"irl", "in real life"},
    {"afaik", "as far as I know"},
    {"btw", "by the way"},
    {"omw", "on my way"},
    {"ikr", "I know right"},
    {"tgif", "thank goodness it's Friday"},
    {"np", "no problem"},
    {"rofl", "rolling on the floor laughing"},
    {"lmk", "let me know"},
    {"dm", "direct message"},
    {"rn", "right now"},
    {"yw", "you're welcome"},
    {"af", "very"},
    {"ftw", "for the win"},
    {"gg", "good game"},
    {"pov", "point of view"},
    {"omfg", "oh my goodness"},
    {"tl;dr", "too long; didn't read"},
    {"fwiw", "for what it's worth"},
    {"bday", "birthday"},
    {"gr8", "great"},
    {"hmu", "hit me up"},
    {"jk", "just kidding"},
    {"k", "okay"},
    {"l8r", "later"},
    {"msg", "message"},
    {"pls", "please"},
    {"plz", "please"},
    {"thx", "thanks"},
    {"tho", "though"},
    {"w/", "with"},
    {"w/o", "without"},
    {"xoxo", "hugs and kisses"},
    {"y", "why"},
    {"b/c", "because"},
    {"cuz", "because"},
    {"coz", "because"},
    {"dunno", "don't know"},
    {"g2g", "got to go"},
    {"hbu", "how about you"},
    {"idc", "I don't care"},
    {"ily", "I love you"},
    {"l8", "late"},
    {"n/a", "not applicable"},
    {"nvm", "never mind"},
    {"omw", "on my way"},
    {"ppl", "people"},
    {"qt", "cutie"},
    {"sup", "what's up"},
    {"tba", "to be announced"},
    {"tbc", "to be continued"},
    {"w/e", "whatever"},
    {"wth", "what the heck"},
    {NULL, NULL} // Sentinel to mark the end
};

/** Grammar suggestions for common mistakes */
static const struct {
    const char *incorrect;
    const char *correct;
} FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[] = {
    {"gonna", "going to"},
    {"ain't", "isn't"},
    {"should of", "should have"},
    {"could of", "could have"},
    {"would of", "would have"},
    {"not never", "never"},
    {"free gift", "gift"},
    {"very unique", "unique"},
    {"actually true", "true"},
    {"past history", "history"},
    {"future plans", "plans"},
    {"true fact", "fact"},
    {"basic fundamentals", "fundamentals"},
    {"completely destroyed", "destroyed"},
    {"revert back", "revert"},
    {"each and every", "each"},
    {"end result", "result"},
    {"final outcome", "outcome"},
    {"unexpected surprise", "surprise"},
    {"advance planning", "planning"},
    {"close proximity", "proximity"},
    {"ATM machine", "ATM"},
    {"PIN number", "PIN"},
    {"ISBN number", "ISBN"},
    {"LCD display", "LCD"},
    {"HIV virus", "HIV"},
    {"true facts", "facts"},
    {"past experiences", "experiences"},
    {"irregardless", "regardless"},
    {"supposably", "supposedly"},
    {"could care less", "couldn't care less"},
    {"for all intensive purposes", "for all intents and purposes"},
    {"escape goat", "scapegoat"},
    {"expresso", "espresso"},
    {"nucular", "nuclear"},
    {"pacifically", "specifically"},
    {"definately", "definitely"},
    {"probly", "probably"},
    {"prolly", "probably"},
    {"alot", "a lot"},
    {"could of", "could have"},
    {"should of", "should have"},
    {"would of", "would have"},
    {"wouldn't of", "wouldn't have"},
    {"shouldn't of", "shouldn't have"},
    {"couldn't of", "couldn't have"},
    {"less people", "fewer people"},
    {"less cars", "fewer cars"},
    {"less books", "fewer books"},
    {"less problems", "fewer problems"},
    {"less mistakes", "fewer mistakes"},
    {"between you and I", "between you and me"},
    {"me and him", "he and I"},
    {"me and her", "she and I"},
    {"me and them", "they and I"},
    {"me and John", "John and I"},
    {"I seen", "I saw"},
    {"I done", "I did"},
    {"I been", "I have been"},
    {"I had went", "I had gone"},
    {"I had ran", "I had run"},
    {"I had ate", "I had eaten"},
    {"I had wrote", "I had written"},
    {"I had broke", "I had broken"},
    {"I had spoke", "I had spoken"},
    {"I had took", "I had taken"},
    {"I had drank", "I had drunk"},
    {"I had drove", "I had driven"},
    {"I had froze", "I had frozen"},
    {"I had chose", "I had chosen"},
    {"I had gave", "I had given"},
    {"I had rode", "I had ridden"},
    {"I had stole", "I had stolen"},
    {"I had swam", "I had swum"},
    {"I had wore", "I had worn"},
    {"I had wrote", "I had written"},
    {"I had ate", "I had eaten"},
    {"I had spoke", "I had spoken"},
    {"I had broke", "I had broken"},
    {"I had took", "I had taken"},
    {"I had drank", "I had drunk"},
    {"I had drove", "I had driven"},
    {"I had froze", "I had frozen"},
    {"I had chose", "I had chosen"},
    {"I had gave", "I had given"},
    {"I had rode", "I had ridden"},
    {"I had stole", "I had stolen"},
    {"I had swam", "I had swum"},
    {"I had wore", "I had worn"},
    {"I had wrote", "I had written"},
    {"I had ate", "I had eaten"},
    {"I had spoke", "I had spoken"},
    {"I had broke", "I had broken"},
    {"I had took", "I had taken"},
    {"I had drank", "I had drunk"},
    {"I had drove", "I had driven"},
    {"I had froze", "I had frozen"},
    {"I had chose", "I had chosen"},
    {"I had gave", "I had given"},
    {"I had rode", "I had ridden"},
    {"I had stole", "I had stolen"},
    {"I had swam", "I had swum"},
    {"I had wore", "I had worn"},
    {NULL, NULL} // Sentinel to mark the end
};

/** Lookup table for sarcastic phrases */
static const char *SOAP_SARCASTIC_PATTERNS[] = {
    "Oh, great", "Yeah, right", "Nice job", "Well done", "Good luck with that", "Sure, why not", "Fantastic", "Brilliant", "Wonderful", "Perfect",
    "Oh, just what I needed", "Wow, amazing", "How original", "Incredible", "As if that will work", "Sure, that's smart", "Totally believable", "Oh, really?",
    "You're a genius", "Thanks a lot", "Couldn't be better", "That's exactly what I wanted", "Well, isn't that special", "Lovely", "Just perfect",
    "What could go wrong?", "Right, because that makes sense", "Great idea", "Absolutely flawless", "Marvelous", "Just wonderful", "Oh, that's helpful",
    "Just what I expected", "Couldn't ask for more", "That's not suspicious at all", "Oh, that's convincing", "What a surprise", "How unexpected",
    "Just my luck", "Of course, why wouldn't it", "That's so typical", "What a coincidence", "Just in time", "Couldn't be happier",
    "That's exactly what I needed", "Oh, that's rich", "How fortunate", "Just fantastic", "Oh, that's brilliant", "Couldn't be more obvious",
    "How convenient", NULL
};

/** Lookup table for formal phrases */
static const char *SOAP_FORMAL_PATTERNS[] = {
    "Dear Sir or Madam", "To whom it may concern", "Yours sincerely", "Yours faithfully", "Best regards", "Respectfully",
    "I would like to", "I am writing to", "Please find attached", "Thank you for your consideration", "I look forward to your response",
    "Kindly note", "Please be advised", "It is my pleasure to", "I would appreciate your assistance", "Should you require any further information",
    "I remain at your disposal", "With kind regards", "Thank you for your attention", "I am writing on behalf of", "Please accept my apologies",
    "I wish to inform you", "We would be grateful if", "I hope this message finds you well", "I would be obliged if", "Kindly consider",
    "I trust this finds you well", "Allow me to express", "With utmost respect", "Permit me to", "I am pleased to inform you",
    "I would like to request", "I am delighted to", "I am honored to", "I am grateful for", "I am reaching out to",
    "I am writing regarding", "I am contacting you to", "I am pleased to submit", "I am pleased to provide", "I am pleased to announce",
    "I am pleased to offer", "I am pleased to confirm", "I am pleased to accept", "I am pleased to acknowledge", "I am pleased to extend",
    "I am pleased to invite", "I am pleased to welcome", "I am pleased to recommend", "I am pleased to endorse", NULL
};

static const char *SOAP_RAGEBAIT_PATTERNS[] = {
    "you won't believe", "outrageous", "infuriating", "makes me angry", "how dare they", "ridiculous", "unbelievable", "trigger warning", "enraging", "shocking injustice",
    "furious", "disgusting", "outrage", "unacceptable", "appalling", "scandalous", "outraged", "angry reaction", "horrifying", "outrage alert",
    "infuriated", "rage induced", "madness", "shocking", "unthinkable", "angry outrage", "outrage fest", "provocative", "furious outrage", "triggered",
    "ragebait", "fuming", "explosive reaction", "heated debate", "controversial", "offensive", "insulting", "hate-filled", "hate speech", "unjust",
    "unfair", "disrespectful", "call to action", "raging", "storm of anger", "backlash", "public outrage", "viral outrage", "internet rage", "mass outrage",
    "social media outrage", NULL
};

static const char *SOAP_CLICKBAIT_PATTERNS[] = {
    "how to", "top 10", "amazing", "must see", "you won't believe what happened", "life changing", "secret revealed", "uncovered", "incredible", "mind blown",
    "you won't believe this", "shocking", "insane", "epic", "ultimate guide", "hidden truth", "never knew", "reveal", "best ever", "fantastic", "jaw dropping",
    "you must see", "exclusive", "surprising", "unreal", "best of", "amazing discovery", "life hack", "can't miss", "insider tips", "what happened next",
    "this will change your life", "the truth about", "watch until the end", "don't miss this", "the secret to", "revealed", "breakthrough", "the real reason",
    "you need to know", "must watch", "unbelievable", "game changer", "before and after", "biggest ever", "most shocking", "crazy story", "you won't believe your eyes",
    "the best kept secret", "what experts don't tell you", "the ultimate list", NULL
};

static const char *SOAP_SPAM_PATTERNS[] = {
    "free money", "work from home", "act now", "earn cash fast", "get rich quick", "limited time offer", "buy now", "exclusive deal",
    "instant results", "100% free", "click here", "apply now", "offer expires", "make money online", "risk free", "guaranteed",
    "easy income", "double your money", "urgent", "special promotion", "no investment", "limited offer", "win big", "free trial",
    "claim prize", "extra cash", "instant payout", "hot deal", "bonus", "cash bonus", "lowest price", "save big", "limited stock",
    "don't miss out", "order now", "get started today", "exclusive offer", "limited time only", "no obligation", "money back guarantee",
    "fast cash", "get paid today", "easy steps", "no experience needed", "start earning now", "unbelievable deal", "limited seats",
    "special discount", "win a prize", "free access", "limited availability", NULL
};

static const char *SOAP_WOKE_PATTERNS[] = {
    "safe space", "microaggression", "check your privilege", "diversity and inclusion", "equity over equality",
    "social justice", "systemic oppression", "cultural appropriation", "intersectionality", "allyship",
    "gender equality", "anti-racism", "inclusive language", "oppression", "privilege check",
    "marginalized voices", "bias awareness", "equity", "discrimination", "social activism",
    "representation matters", "critical race theory", "minority rights", "empowerment", "identity politics",
    "decolonize", "bias training", "social equity", "inclusive policy", "identity awareness",
    "gender neutral", "pronoun respect", "intersectional feminism", "diversity training", "racial justice",
    "gender fluidity", "safe environment", "trigger warning", "progressive values", "inclusive spaces",
    "anti-bias", "restorative justice", "affirmative action", "equitable access", "community empowerment",
    "inclusive curriculum", "representation equity", "social responsibility", "inclusive leadership",
    "gender inclusivity", "racial equity", NULL
};

/** Lookup table for bot-like patterns */
static const char *SOAP_BOT_PATTERNS[] = {
    "ai generated", "algorithmic message", "artificial response", "auto reply", "auto responder", "auto-generated",
    "automated comment", "automated message", "automated post", "automated reply", "automation bot", "automation detected",
    "autonomous post", "bot activity", "bot behavior", "bot comment", "bot detected", "bot follower", "bot interaction",
    "bot like", "bot moderator", "bot network", "bot retweet", "bot spam", "bot upvote", "bulk message", "copy-paste answer",
    "fake account", "fake bot", "fake user", "generated content", "generic message", "machine generated", "mass message",
    "mass posting", "mass produced content", "non-human reply", "predefined response", "programmed answer", "repetitive comment",
    "robot account", "robot post", "robotic message", "robotic reply", "scripted content", "scripted response", "spam account",
    "spam bot", "system generated", "synthetic post", "template reply", "unoriginal reply", NULL
};

/** Lookup table for snowflake patterns */
static const char *SOAP_SNOWFLAKE_PATTERNS[] = {
    "snowflake", "triggered", "fragile ego", "offended easily", "sensitive snowflake",
    "microaggression", "safe space", "special snowflake", "delicate", "thin-skinned",
    "overly sensitive", "crybaby", "tender feelings", "too sensitive", "emotionally fragile",
    "overreacting", "touchy", "soft-hearted", "extra sensitive", "hyper-sensitive",
    "prickly", "easily upset", "nervous nellie", "fragile personality", "highly sensitive",
    "overly emotional", "whiny", "melodramatic", "delicate flower", "fragile soul",
    "overprotected", "coddled", "pampered", "overly sheltered", "easily offended",
    "thin skin", "overly dramatic", "sheltered", "overly cautious", "emotionally weak",
    "overly anxious", "overly reactive", "overly sentimental", "easily disturbed",
    "overly nurturing", "emotionally unstable", "overly caring", "overly empathetic",
    "overly worried", "overly fearful", NULL
};

/** Lookup table for offensive content detection */
static const char *SOAP_OFFENSIVE_PATTERNS[] = {
    "idiot", "stupid", "dumb", "moron", "fool", "loser", "jerk", "trash", "garbage",
    "worthless", "pathetic", "ugly", "disgusting", "nonsense", "ridiculous", "absurd",
    "hate", "kill", "die", "sucks", "shut up", "dunce", "ignorant", "nasty",
    "offensive", "freak", "creep", "weirdo", "worthless", "imbecile", "retard",
    "scum", "vermin", "filth", "vile", "repulsive", "gross", "horrible", "evil",
    "abomination", "monster", "beast", "brainless", "airhead", "twit", "twat",
    "douche", "bastard", "maniac", "psycho", "lunatic", "savage", NULL
};

/** Lookup table for neutral tone patterns */
static const char *SOAP_NEUTRAL_PATTERNS[] = {
    "as expected", "according to plan", "no problem", "all good", "fine", "okay", "normal",
    "standard procedure", "routine", "average", "typical", "usual", "nothing special",
    "business as usual", "no issues", "no concerns", "no complaints", "acceptable",
    "satisfactory", "regular", "ordinary", "unremarkable", "moderate", "fair", "adequate",
    "sufficient", "reasonable", "not bad", "not great", "so-so", "meh", "neutral",
    "indifferent", "unbiased", "impartial", "objective", "even-handed", "middle ground",
    "balanced", "equitable", "nonpartisan", "detached", "reserved", "unemotional",
    "calm", "steady", "level-headed", "matter-of-fact", "plain", "straightforward",
    "clear", "direct", "simple", "uncomplicated", NULL
};

/** Lookup table for hype phrases */
static const char *SOAP_HYPE_PATTERNS[] = {
    "game-changing","revolutionary","cutting-edge","disruptive","never before seen",
    "unprecedented","the ultimate","next-level","life-changing","epic","legendary",
    "the best ever","mind-blowing","world-class","exclusive","groundbreaking","innovative",
    "unparalleled","must-have","hot new","phenomenal","incredible","jaw-dropping",
    "guaranteed","proven results","miracle","unstoppable","the future of","beyond belief",
    "state-of-the-art","amazing","once in a lifetime","extraordinary","unbeatable","elite",
    "remarkable","top-tier","exceptional","stellar","premium","best-in-class","outstanding",
    "next big thing","ultimate solution","transformative","game-changer","reimagined","breakthrough",
    "trailblazing","legendary product","redefining","NULL"
};

/** Political */
static const char *SOAP_POLITICAL_PATTERNS[] = { 
    "left-wing","right-wing","liberal agenda","conservative values","fake news media",
    "mainstream media","deep state","radical","extremist","social justice warrior","tax and spend",
    "big government","free market","personal freedom","authoritarian","totalitarian","censorship",
    "political correctness","cancel culture","big brother","elitist","grassroots movement",
    "identity politics","partisan","special interests","lobbyist","corrupt politicians","vote rigging",
    "rigged system","polarized nation","propaganda","electoral fraud","media bias","government overreach",
    "legislation","policy reform","constitutional","impeachment","regulatory capture","voter suppression",
    "political scandal","public office","government shutdown","state control","national security",
    "campaign finance","party platform","NULL"
};

/** Conspiracy */
static const char *SOAP_CONSPIRACY_PATTERNS[] = {
    "they don’t want you to know","hidden truth","cover up","shadow government","mind control",
    "secret society","illuminati","new world order","false flag","plandemic","chemtrails",
    "crisis actors","fabricated evidence","hollow earth","flat earth","alien cover-up",
    "government lies","deep underground base","suppressed technology","mass surveillance",
    "thought police","fabricated by the media","controlled opposition","secret labs",
    "fake moon landing","reptilian","massive hoax","in on it","they control everything",
    "behind closed doors","manipulation","hidden agenda","classified files","covert operations",
    "black ops","unexplained phenomena","shadowy figures","secret programs","disinformation",
    "conspiratorial","hidden messages","mind games","secret experiments","underground network",
    "NULL"
};

/** Marketing */
static const char *SOAP_MARKETING_PATTERNS[] = {
    "limited time offer","act now","don’t miss out","guaranteed results","risk free",
    "sign up today","exclusive deal","free trial","buy one get one","special promotion",
    "limited stock","save big","lowest price ever","best deal","offer ends soon",
    "only for today","unlock savings","no obligation","instant access","money back guarantee",
    "redeem now","hot deal","flash sale","discounted rate","claim your spot","exclusive offer",
    "limited edition","join thousands","be the first","special savings","new arrival",
    "get yours now","best value","exclusive bonus","early bird","special launch","today only",
    "final chance","bonus included","premium package","offer valid","special offer","don’t wait",
    "hurry up","exclusive access","deal of the day","NULL"
};

/** Technobabble */
static const char *SOAP_TECHNOBABBLE_PATTERNS[] = {
    "synergy","blockchain-enabled","AI-powered","machine learning solution",
    "next-gen","hyper scalable","paradigm shift","deep tech","seamless integration",
    "big data","cloud-native","cutting-edge platform","quantum leap","value proposition",
    "turnkey solution","innovative ecosystem","frictionless","low-hanging fruit",
    "mission critical","digital transformation","smart disruption","empower users",
    "end-to-end","future-proof","holistic approach","thought leadership","revolutionize",
    "strategic alignment","game-changer","intelligent automation","data-driven","disruptive innovation",
    "scalable architecture","AI-driven","cloud-first","next-generation","hyper convergence",
    "machine intelligence","tech stack","real-time analytics","dynamic workflow","intelligent design",
    "agile methodology","NULL"
};

/** Lookup table for low-quality signals */
static const char *SOAP_QUALITY_PATTERNS[] = {
    "just saying","you know","like literally","basically","whatever","stuff and things",
    "random nonsense","blah blah","and so on","thingy","meh","idk","not sure","somehow",
    "something like that","kind of","sort of","whatever works","in a way","obviously",
    "clearly","everyone knows","trust me","believe me","it is what it is","that kind of thing",
    "doesn’t matter","whatever you think","unimportant","insignificant","minor detail",
    "whatever floats your boat","trivial","meaningless","small stuff","irrelevant",
    "empty words","hollow statement","noise","filler","pointless","NULL"
};

/** Lookup table for words that need to be skipped due to misdetection */
static const char *SKIP_WORDS[] = {
    "limit", "size", "width", "height", "length", "depth", "volume", "capacity", "weight",
    "age", "year", "month", "day", "hour", "minute", "second", "ID", "serial", "version",
    "code", "label", "status", "level",
    NULL // Sentinel to mark the end
};

static char custom_storage[MAX_CUSTOM_FILTERS][64];
static const char *custom_filters[MAX_CUSTOM_FILTERS] = {0};

/**
 * @brief Convert leetspeak to normal letters.
 */
static void pizza_io_soap_normalize_leetspeak(char *word) {
    for (size_t i = 0; word[i] != '\0'; i++) {
        switch (word[i]) {
            case '0': word[i] = 'o'; break;
            case '1': word[i] = 'i'; break;
            case '3': word[i] = 'e'; break;
            case '4': word[i] = 'a'; break;
            case '5': word[i] = 's'; break;
            case '7': word[i] = 't'; break;
            case '$': word[i] = 's'; break;
        }
    }
}

/**
 * @brief Fuzzy matching using Levenshtein distance.
 */
static int fuzzy_match(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t dist[len1 + 1][len2 + 1];

    for (size_t i = 0; i <= len1; i++) dist[i][0] = i;
    for (size_t j = 0; j <= len2; j++) dist[0][j] = j;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dist[i][j] = fmin(fmin(dist[i - 1][j] + 1, dist[i][j - 1] + 1), dist[i - 1][j - 1] + cost);
        }
    }
    return dist[len1][len2];
}

/**
 * @brief Check if a word should be skipped.
 */
static int should_skip_word(const char *word) {
    for (size_t i = 0; SKIP_WORDS[i] != NULL; i++) {
        if (strcmp(word, SKIP_WORDS[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Case-insensitive string comparison.
 */
static int custom_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

/**
 * @brief Case-insensitive substring search.
 */
static const char *custom_strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return haystack;

    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack, *n = needle;
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            if (!*n) return haystack;
        }
    }
    return NULL;
}

/**
 * @brief Simple regex-like pattern matcher for phrase arrays.
 *        Supports '*' (matches any sequence) and '?' (matches any single char).
 *        Case-insensitive.
 */
static int pizza_io_soap_simple_regex_match(const char *text, const char *pattern) {
    // Case-insensitive matching
    while (*pattern) {
        if (*pattern == '*') {
            pattern++;
            if (!*pattern) return 1; // Trailing '*' matches everything
            while (*text) {
                if (pizza_io_soap_simple_regex_match(text, pattern)) return 1;
                text++;
            }
            return 0;
        } else if (*pattern == '?') {
            if (!*text) return 0;
            text++;
            pattern++;
        } else {
            if (tolower((unsigned char)*text) != tolower((unsigned char)*pattern)) return 0;
            text++;
            pattern++;
        }
    }
    return *text == '\0';
}

/**
 * @brief Checks if any pattern in the array matches the text using simple regex.
 */
static int pizza_io_soap_regex_patterns(const char *text, const char **patterns) {
    if (!text || !patterns) return 0;
    for (size_t i = 0; patterns[i] != NULL; i++) {
        if (pizza_io_soap_simple_regex_match(text, patterns[i])) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Look up a suggested alternative for a given word, checking both custom filters and predefined suggestions.
 */
static const char *pizza_io_soap_get_suggestion(const char *word) {
    if (should_skip_word(word)) {
        return NULL;
    }

    // Check in custom filters first
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS && custom_filters[i] != NULL; i++) {
        if (custom_strcasecmp(word, custom_filters[i]) == 0) {
            return custom_filters[i];  // Use the custom filter word itself as suggestion
        }
        if (fuzzy_match(word, custom_filters[i]) <= 2) {
            return custom_filters[i];  // Return fuzzy match result
        }
    }

    // Check in predefined suggestions
    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != NULL; i++) {
        if (custom_strcasecmp(word, FOSSIL_SOAP_SUGGESTIONS[i].bad) == 0) {
            return FOSSIL_SOAP_SUGGESTIONS[i].suggested;
        }
    }

    // Check in grammar suggestions
    for (size_t i = 0; FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect != NULL; i++) {
        if (custom_strcasecmp(word, FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect) == 0) {
            return FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].correct;
        }
    }

    return NULL;
}

/**
 * @brief Sanitize input text by removing or replacing "rot-brain" and meme-based language.
 *        Uses regex-like matching for phrase arrays.
 *        Censored words are replaced with '*'.
 */
char *pizza_io_soap_sanitize(const char *text) {
    if (!text) return NULL;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 1); // Allocate more space to handle replacements
    if (!output) return NULL;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-') {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1) word_idx = sizeof(word) - 2;
        } else {
            word[word_idx] = '\0';
            pizza_io_soap_normalize_leetspeak(word);

            int is_rotbrain = pizza_io_soap_regex_patterns(word, (const char *[]){"rot-brain", "rot brain", "rotbrain", NULL});
            int is_meme = pizza_io_soap_regex_patterns(word, (const char *[]){"skibidi", "rizz", "yeet", "sus", "vibe", "lit", NULL});

            if (word_idx > 0 && (is_rotbrain || is_meme) && !should_skip_word(word)) {
                for (size_t j = 0; j < word_idx; j++) {
                    output[out_idx++] = '*';
                }
            } else {
                for (size_t j = 0; j < word_idx; j++) {
                    output[out_idx++] = word[j];
                }
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    pizza_io_soap_normalize_leetspeak(word);

    int is_rotbrain = pizza_io_soap_regex_patterns(word, (const char *[]){"rot-brain", "rot brain", "rotbrain", NULL});
    int is_meme = pizza_io_soap_regex_patterns(word, (const char *[]){"skibidi", "rizz", "yeet", "sus", "vibe", "lit", NULL});

    if (word_idx > 0 && (is_rotbrain || is_meme) && !should_skip_word(word)) {
        for (size_t j = 0; j < word_idx; j++) {
            output[out_idx++] = '*';
        }
    } else {
        for (size_t j = 0; j < word_idx; j++) {
            output[out_idx++] = word[j];
        }
    }
    output[out_idx] = '\0';
    return output;
}

char *pizza_io_soap_suggest(const char *text) {
    if (!text) return NULL;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 64); // Allocate more space to handle replacements
    if (!output) return NULL;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-') {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1) word_idx = sizeof(word) - 2;
        } else {
            word[word_idx] = '\0';
            pizza_io_soap_normalize_leetspeak(word);
            const char *suggested = pizza_io_soap_get_suggestion(word);
            if (word_idx > 0 && suggested && !should_skip_word(word)) {
                strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
                out_idx += strlen(suggested);
            } else {
                strncpy(&output[out_idx], word, len * 2 + 64 - out_idx);
                out_idx += word_idx;
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    pizza_io_soap_normalize_leetspeak(word);
    const char *suggested = pizza_io_soap_get_suggestion(word);
    if (word_idx > 0 && suggested && !should_skip_word(word)) {
        strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
        out_idx += strlen(suggested);
    } else {
        strncpy(&output[out_idx], word, len * 2 + 64 - out_idx);
        out_idx += word_idx;
    }
    output[out_idx] = '\0';
    return output;
}

/**
 * @brief Detects the tone of the given text using regex-like pattern matching.
 *        Returns a comma-separated string of detected tones, or "casual" if none found.
 */
const char *pizza_io_soap_detect_tone(const char *text) {
    if (!text) return "unknown";

    static char tone_result[256];
    tone_result[0] = '\0';
    int found = 0;

    struct {
        const char **patterns;
        const char *label;
    } tone_checks[] = {
        {SOAP_RAGEBAIT_PATTERNS, "ragebait"},
        {SOAP_CLICKBAIT_PATTERNS, "clickbait"},
        {SOAP_SPAM_PATTERNS, "spam"},
        {SOAP_WOKE_PATTERNS, "woke"},
        {SOAP_BOT_PATTERNS,           "bot"},
        {SOAP_SARCASTIC_PATTERNS,     "sarcastic"},
        {SOAP_SNOWFLAKE_PATTERNS,     "snowflake"},
        {SOAP_FORMAL_PATTERNS,        "formal"},
        {SOAP_OFFENSIVE_PATTERNS,     "offensive"},
        {SOAP_NEUTRAL_PATTERNS,       "neutral"},
        { SOAP_QUALITY_PATTERNS,      "quality"     },
        { SOAP_HYPE_PATTERNS,         "hype"        },
        { SOAP_POLITICAL_PATTERNS,    "political"   },
        { SOAP_CONSPIRACY_PATTERNS,   "conspiracy"  },
        { SOAP_MARKETING_PATTERNS,    "marketing"   },
        { SOAP_TECHNOBABBLE_PATTERNS, "technobabble"},
        { NULL,                       NULL          }
    };

    // Split text into words for more accurate matching
    char temp[512];
    strncpy(temp, text, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';

    char *word = temp;
    for (size_t i = 0; tone_checks[i].patterns != NULL; i++) {
        int match = 0;
        char *ptr = word;
        while (*ptr) {
            // Skip leading non-alnum
            while (*ptr && !isalnum((unsigned char)*ptr)) ptr++;
            if (!*ptr) break;
            char *start = ptr;
            while (*ptr && (isalnum((unsigned char)*ptr) || *ptr == '\'' || *ptr == '-')) ptr++;
            char saved = *ptr;
            *ptr = '\0';

            // Normalize leetspeak for each word
            char norm[64];
            strncpy(norm, start, sizeof(norm) - 1);
            norm[sizeof(norm) - 1] = '\0';
            pizza_io_soap_normalize_leetspeak(norm);

            // Check word and full text for pattern match
            if (pizza_io_soap_regex_patterns(norm, tone_checks[i].patterns) ||
                pizza_io_soap_regex_patterns(text, tone_checks[i].patterns)) {
                match = 1;
                *ptr = saved;
                break;
            }
            *ptr = saved;
            if (*ptr) ptr++;
        }
        if (match) {
            if (found) strcat(tone_result, ",");
            strcat(tone_result, tone_checks[i].label);
            found = 1;
        }
    }

    if (!found) return "casual";
    return tone_result;
}

int pizza_io_soap_check_grammar(const char *text) {
    if (!text) return -1;
    int found = 0;
    for (size_t i = 0; FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect; i++) {
        const char *incorrect = FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect;
        const char *ptr = text;
        size_t ilen = strlen(incorrect);
        while ((ptr = custom_strcasestr(ptr, incorrect)) != NULL) {
            // Check word boundaries
            int before = (ptr == text) || !isalnum((unsigned char)ptr[-1]);
            int after = !isalnum((unsigned char)ptr[ilen]);
            if (before && after) {
                found = 1;
                break;
            }
            ptr += ilen;
        }
        if (found) break;
    }
    return found;
}

char *pizza_io_soap_correct_grammar(const char *text) {
    if (!text) return NULL;

    char *corrected = fossil_io_cstring_dup(text); // Create modifiable copy
    if (!corrected) return NULL;

    for (size_t i = 0; FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect; i++) {
        const char *incorrect = FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect;
        const char *correct = FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].correct;
        const char *ptr;
        while ((ptr = custom_strcasestr(corrected, incorrect))) {
            // Check word boundaries
            size_t prefix_len = ptr - corrected;
            size_t inc_len = strlen(incorrect);
            size_t cor_len = strlen(correct);
            int before = (ptr == corrected) || !isalnum((unsigned char)ptr[-1]);
            int after = !isalnum((unsigned char)ptr[inc_len]);
            if (!(before && after)) {
                ptr += inc_len;
                continue;
            }
            size_t new_len = strlen(corrected) - inc_len + cor_len + 1;
            char *temp = malloc(new_len);
            if (!temp) break;
            snprintf(temp, new_len, "%.*s%s%s",
                     (int)prefix_len, corrected, correct, ptr + inc_len);
            free(corrected);
            corrected = temp;
        }
    }

    return corrected;
}

char *pizza_io_soap_normalize_slang(const char *text) {
    if (!text) return NULL;

    char *result = fossil_io_cstring_dup(text);
    if (!result) return NULL;

    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != NULL; i++) {
        const char *bad = FOSSIL_SOAP_SUGGESTIONS[i].bad;
        const char *sugg = FOSSIL_SOAP_SUGGESTIONS[i].suggested;

        const char *found = NULL;
        while ((found = custom_strcasestr(result, bad)) != NULL) {
            // Check word boundaries for whole word replacement
            size_t offset = (size_t)(found - result);
            size_t bad_len = strlen(bad);
            size_t sugg_len = strlen(sugg);
            int before = (found == result) || !isalnum((unsigned char)found[-1]);
            int after = !isalnum((unsigned char)found[bad_len]);
            if (!(before && after)) {
                found += bad_len;
                continue;
            }

            size_t newlen = strlen(result) - bad_len + sugg_len + 1;
            char *temp = malloc(newlen);
            if (!temp) {
                free(result);
                return NULL;
            }

            snprintf(temp, newlen, "%.*s%s%s",
                     (int)offset, result, sugg, found + bad_len);
            free(result);
            result = temp;
        }
    }

    return result;
}

// detection helper

static int soap_detect_patterns(const char *text, const char **patterns) {
    if (!text || !patterns) return 0;

    for (size_t i = 0; patterns[i] != NULL; i++) {
        if (custom_strcasestr(text, patterns[i])) {
            return 1; // Pattern found
        }
    }
    return 0; // No match
}

int pizza_io_soap_detect_ragebait(const char *text) {
    return soap_detect_patterns(text, SOAP_RAGEBAIT_PATTERNS);
}

int pizza_io_soap_detect_clickbait(const char *text) {
    return soap_detect_patterns(text, SOAP_CLICKBAIT_PATTERNS);
}

int pizza_io_soap_detect_spam(const char *text) {
    return soap_detect_patterns(text, SOAP_SPAM_PATTERNS);
}

int pizza_io_soap_detect_woke(const char *text) {
    return soap_detect_patterns(text, SOAP_WOKE_PATTERNS);
}

int pizza_io_soap_detect_bot(const char *text) {
    return soap_detect_patterns(text, SOAP_BOT_PATTERNS);
}

int pizza_io_soap_detect_sarcasm(const char *text) {
    return soap_detect_patterns(text, SOAP_SARCASTIC_PATTERNS);
}

int pizza_io_soap_detect_formal(const char *text) {
    return soap_detect_patterns(text, SOAP_FORMAL_PATTERNS);
}

int pizza_io_soap_detect_snowflake(const char *text) {
    return soap_detect_patterns(text, SOAP_SNOWFLAKE_PATTERNS);
}

int pizza_io_soap_detect_offensive(const char *text) {
    return soap_detect_patterns(text, SOAP_OFFENSIVE_PATTERNS);
}

int pizza_io_soap_detect_neutral(const char *text) {
    return soap_detect_patterns(text, SOAP_NEUTRAL_PATTERNS);
}

int pizza_io_soap_detect_hype(const char *text) {
    return soap_detect_patterns(text, SOAP_HYPE_PATTERNS);
}

int pizza_io_soap_detect_quality(const char *text) {
    return soap_detect_patterns(text, SOAP_QUALITY_PATTERNS);
}

int pizza_io_soap_detect_political(const char *text) {
    return soap_detect_patterns(text, SOAP_POLITICAL_PATTERNS);
}

int pizza_io_soap_detect_conspiracy(const char *text) {
    return soap_detect_patterns(text, SOAP_CONSPIRACY_PATTERNS);
}

int pizza_io_soap_detect_marketing(const char *text) {
    return soap_detect_patterns(text, SOAP_MARKETING_PATTERNS);
}

int pizza_io_soap_detect_technobabble(const char *text) {
    return soap_detect_patterns(text, SOAP_TECHNOBABBLE_PATTERNS);
}

/**
 * @brief Filter text by replacing words/phrases matching any pattern (comma-separated) with '*'.
 *        Patterns support '*' and '?' wildcards, case-insensitive.
 */
char *pizza_io_soap_filter(const char *patterns, const char *text) {
    if (!patterns || !text) return NULL;

    // Copy patterns string to safely tokenize
    char patterns_buf[512];
    strncpy(patterns_buf, patterns, sizeof(patterns_buf) - 1);
    patterns_buf[sizeof(patterns_buf) - 1] = '\0';

    // Build pattern array
    const char *pattern_arr[MAX_CUSTOM_FILTERS + 1];
    size_t pat_count = 0;
    char *token = strtok(patterns_buf, ",");
    while (token && pat_count < MAX_CUSTOM_FILTERS) {
        // Trim leading/trailing spaces
        while (*token == ' ') token++;
        size_t len = strlen(token);
        while (len > 0 && token[len - 1] == ' ') token[--len] = '\0';
        pattern_arr[pat_count++] = token;
        token = strtok(NULL, ",");
    }
    pattern_arr[pat_count] = NULL;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 1);
    if (!output) return NULL;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-') {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1) word_idx = sizeof(word) - 2;
        } else {
            word[word_idx] = '\0';
            int matched = 0;
            if (word_idx > 0) {
                for (size_t j = 0; pattern_arr[j] != NULL; j++) {
                    if (pizza_io_soap_simple_regex_match(word, pattern_arr[j])) {
                        matched = 1;
                        break;
                    }
                }
            }
            if (matched) {
                for (size_t j = 0; j < word_idx; j++) output[out_idx++] = '*';
            } else {
                for (size_t j = 0; j < word_idx; j++) output[out_idx++] = word[j];
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    int matched = 0;
    if (word_idx > 0) {
        for (size_t j = 0; pattern_arr[j] != NULL; j++) {
            if (pizza_io_soap_simple_regex_match(word, pattern_arr[j])) {
                matched = 1;
                break;
            }
        }
    }
    if (matched) {
        for (size_t j = 0; j < word_idx; j++) output[out_idx++] = '*';
    } else {
        for (size_t j = 0; j < word_idx; j++) output[out_idx++] = word[j];
    }
    output[out_idx] = '\0';
    return output;
}

// ============================================================================
// Readability Analysis
// ============================================================================

int pizza_io_soap_readability_score(const char *text) {
    if (!text || !*text) return 0;

    int sentences = 0, words = 0, syllables = 0;
    const char *ptr = text;

    /* Count words + naive syllables */
    while (*ptr) {
        if (isalpha((unsigned char)*ptr)) {
            words++;
            int saw_vowel = 0;
            while (isalpha((unsigned char)*ptr)) {
                char c = tolower(*ptr);
                if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u' || c=='y') {
                    if (!saw_vowel) {
                        syllables++;
                        saw_vowel = 1;
                    }
                } else {
                    saw_vowel = 0;
                }
                ptr++;
            }
        } else {
            if (*ptr == '.' || *ptr == '!' || *ptr == '?')
                sentences++;
            ptr++;
        }
    }

    if (sentences == 0) sentences = 1;
    if (words == 0) words = 1;

    /* Flesch-Kincaid style formula */
    double score =
        206.835 - 1.015 * ((double)words / sentences) - 84.6 * ((double)syllables / words);

    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return (int)score;
}

const char *pizza_io_soap_readability_label(const char *text) {
    int s = pizza_io_soap_readability_score(text);
    if (s >= 70) return "easy";
    if (s >= 40) return "medium";
    return "complex";
}

// ============================================================================
// Summarization
// ============================================================================

/* Very small heuristic summary: extract first 2–3 sentences */
char *pizza_io_soap_summarize(const char *text) {
    if (!text) return NULL;

    char **sent = pizza_io_soap_split_sentences(text);
    if (!sent) return NULL;

    size_t cap = 1024;
    char *out = malloc(cap);
    if (!out) return NULL;
    out[0] = '\0';

    int count = 0;
    for (int i = 0; sent[i] && count < 3; i++, count++) {
        strncat(out, sent[i], cap - strlen(out) - 1);
        if (sent[i][strlen(sent[i])-1] != '.')
            strncat(out, ".", cap - strlen(out) - 1);
        strncat(out, " ", cap - strlen(out) - 1);
    }

    /* free sentence array */
    for (int i = 0; sent[i]; i++) free(sent[i]);
    free(sent);

    return out;
}

char *pizza_io_soap_extract_key_sentence(const char *text) {
    if (!text) return NULL;

    char **sent = pizza_io_soap_split_sentences(text);
    if (!sent) return NULL;

    /* Key sentence = longest non-clickbait sentence */
    int best = -1;
    size_t blen = 0;

    for (int i = 0; sent[i]; i++) {
        size_t len = strlen(sent[i]);
        if (len > blen) { best = i; blen = len; }
    }

    char *ret = best >= 0 ? fossil_io_cstring_dup(sent[best]) : fossil_io_cstring_dup("");
    for (int i = 0; sent[i]; i++) free(sent[i]);
    free(sent);

    return ret;
}

// ============================================================================
// Style Analysis
// ============================================================================

const char *pizza_io_soap_analyze_style(const char *text) {
    if (!text) return "unknown";

    size_t len = strlen(text);

    if (len < 40) return "concise";
    if (len > 300) return "verbose";
    if (custom_strcasestr(text, "algorithm") ||
        custom_strcasestr(text, "system") ||
        custom_strcasestr(text, "model"))
        return "technical";

    return "neutral";
}

int pizza_io_soap_passive_voice_ratio(const char *text) {
    if (!text) return 0;

    int passive = 0, total = 0;

    const char *verbs[] = {"was", "were", "is", "are", "be", "been", NULL};

    char **sent = pizza_io_soap_split_sentences(text);
    if (!sent) return 0;

    for (int i = 0; sent[i]; i++) {
        total++;
        for (int v = 0; verbs[v]; v++) {
            if (custom_strcasestr(sent[i], verbs[v]) &&
                custom_strcasestr(sent[i], " by ")) {
                passive++;
                break;
            }
        }
    }

    for (int i = 0; sent[i]; i++) free(sent[i]);
    free(sent);

    if (total == 0) return 0;
    return (passive * 100) / total;
}

// ============================================================================
// Quality & Clarity
// ============================================================================

int pizza_io_soap_clarity_score(const char *text) {
    if (!text) return 0;

    int score = pizza_io_soap_readability_score(text);

    // Penalize for excessive filler words, but only if not in a factual/neutral context
    int filler = 0;
    int neutral = pizza_io_soap_detect_neutral(text);

    for (int i = 0; SOAP_QUALITY_PATTERNS[i]; i++) {
        if (custom_strcasestr(text, SOAP_QUALITY_PATTERNS[i]))
            filler += 3;
    }

    // If the text is neutral/factual or contains factual keywords, do not penalize for filler
    if (neutral || custom_strcasestr(text, "according to") || custom_strcasestr(text, "standard procedure") || custom_strcasestr(text, "experiment") || custom_strcasestr(text, "boils at"))
        filler = 0;

    score -= filler;

    if (score < 0) score = 0;
    if (score > 100) score = 100;

    return score;
}

int pizza_io_soap_quality_score(const char *text) {
    if (!text) return 0;

    int clarity = pizza_io_soap_clarity_score(text);
    int passive = pizza_io_soap_passive_voice_ratio(text);

    // If the text is neutral/factual or contains factual keywords, do not penalize for passive voice
    int neutral = pizza_io_soap_detect_neutral(text);
    int factual = custom_strcasestr(text, "according to") || custom_strcasestr(text, "standard procedure") || custom_strcasestr(text, "experiment") || custom_strcasestr(text, "boils at");
    int q = clarity;
    if (!neutral && !factual)
        q -= (passive / 2);

    if (q < 0) q = 0;
    if (q > 100) q = 100;

    return q;
}

// ============================================================================
// Structural Tools
// ============================================================================

char **pizza_io_soap_split_sentences(const char *text) {
    if (!text) return NULL;

    size_t cap = 16;
    char **out = calloc(cap, sizeof(char *));
    if (!out) return NULL;

    const char *start = text;
    const char *p = text;
    int idx = 0;

    while (*p) {
        if (*p == '.' || *p == '?' || *p == '!') {
            size_t len = (p - start) + 1;
            char *s = malloc(len + 1);
            memcpy(s, start, len);
            s[len] = '\0';

            if (idx + 1 >= (int)cap) {
                cap *= 2;
                out = realloc(out, cap * sizeof(char *));
            }
            out[idx++] = s;

            start = p + 1;
        }
        p++;
    }

    /* last fragment */
    if (p != start) {
        char *s = fossil_io_cstring_dup(start);
        out[idx++] = s;
    }

    out[idx] = NULL;
    return out;
}

char *pizza_io_soap_reflow(const char *text, int width) {
    if (!text || width < 10) return NULL;

    char *buf = fossil_io_cstring_dup(text);
    char *tok = strtok(buf, " ");
    size_t cap = strlen(text) + 128;
    char *out = malloc(cap);
    out[0] = '\0';

    int col = 0;
    while (tok) {
        int w = strlen(tok);
        if (col + w + 1 > width) {
            strcat(out, "\n");
            col = 0;
        }
        strcat(out, tok);
        strcat(out, " ");
        col += w + 1;
        tok = strtok(NULL, " ");
    }

    free(buf);
    return out;
}

// ============================================================================
// Normalization
// ============================================================================

char *pizza_io_soap_normalize(const char *text) {
    if (!text) return NULL;

    char *out = malloc(strlen(text) * 2 + 1);
    size_t oi = 0;
    int ws = 0;

    for (size_t i = 0; text[i]; i++) {
        if (isspace((unsigned char)text[i])) {
            if (!ws) out[oi++] = ' ';
            ws = 1;
        } else {
            out[oi++] = text[i];
            ws = 0;
        }
    }
    out[oi] = '\0';
    return out;
}

char *pizza_io_soap_capitalize(const char *text, int mode) {
    if (!text) return NULL;
    char *out = fossil_io_cstring_dup(text);
    size_t n = strlen(out);

    switch (mode) {
        case 0: { /* sentence case */
            int cap = 1;
            for (size_t i = 0; i < n; i++) {
                if (cap && isalpha((unsigned char)out[i])) {
                    out[i] = toupper(out[i]);
                    cap = 0;
                } else out[i] = tolower(out[i]);

                if (out[i] == '.' || out[i] == '?' || out[i] == '!')
                    cap = 1;
            }
        } break;

        case 1: /* title case */
            for (size_t i = 0; i < n; i++) {
                if (i == 0 || out[i-1] == ' ')
                    out[i] = toupper(out[i]);
                else
                    out[i] = tolower(out[i]);
            }
            break;

        case 2: /* uppercase */
            for (size_t i = 0; i < n; i++) out[i] = toupper(out[i]);
            break;

        case 3: /* lowercase */
            for (size_t i = 0; i < n; i++) out[i] = tolower(out[i]);
            break;
    }

    return out;
}

int pizza_io_is_rot_brain(const char *text) {
    if (!text) return 0;

    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != null; i++) {
        if (custom_strcasestr(text, FOSSIL_SOAP_SUGGESTIONS[i].bad)) {
            return 1;
        }
    }
    return 0;
}

// *****************************************************************************
// memory management
// *****************************************************************************

pizza_sys_memory_t pizza_sys_memory_alloc(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Cannot allocate zero bytes.\n");
        return null;
    }
    
    pizza_sys_memory_t ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Memory allocation failed.\n");
        return null;
    }
    return ptr;
}

pizza_sys_memory_t pizza_sys_memory_realloc(pizza_sys_memory_t ptr, size_t size) {
    pizza_sys_memory_t new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0) {
        fprintf(stderr, "Error: pizza_sys_memory_realloc() - Memory reallocation failed.\n");
        return null;
    }
    return new_ptr;
}

pizza_sys_memory_t pizza_sys_memory_calloc(size_t num, size_t size) {
    if (num == 0 || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Cannot allocate zero elements or zero bytes.\n");
        return null;
    }

    pizza_sys_memory_t ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Memory allocation failed.\n");
        return null;
    }
    return ptr;
}

pizza_sys_memory_t pizza_sys_memory_init(pizza_sys_memory_t ptr, size_t size, int32_t value) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Pointer is null.\n");
        return null;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Cannot initialize zero bytes.\n");
        return null;
    }

    return memset(ptr, value, size);
}

void pizza_sys_memory_free(pizza_sys_memory_t ptr) {
    if (!ptr) {
        return;
    }
    free(ptr); // No need for null check, free() already handles null.
}

pizza_sys_memory_t pizza_sys_memory_copy(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size) {
    if (!dest || !src) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Source or destination is null.\n");
        return null;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Cannot copy zero bytes.\n");
        return null;
    }
    
    return memcpy(dest, src, size);
}

pizza_sys_memory_t pizza_sys_memory_set(pizza_sys_memory_t ptr, int32_t value, size_t size) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Pointer is null.\n");
        return null;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Cannot set zero bytes.\n");
        return null;
    }
    
    return memset(ptr, value, size);
}

pizza_sys_memory_t pizza_sys_memory_dup(const pizza_sys_memory_t src, size_t size) {
    if (!src || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_dup() - Invalid source or zero size.\n");
        return null;
    }

    pizza_sys_memory_t dest = pizza_sys_memory_alloc(size);
    if (!dest) {
        return null;  // Error already handled in pizza_sys_memory_alloc
    }

    return memcpy(dest, src, size);
}

pizza_sys_memory_t pizza_sys_memory_zero(pizza_sys_memory_t ptr, size_t size) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_zero() - Pointer is null.\n");
        return null;
    }

    if (size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_zero() - Cannot zero out zero bytes.\n");
        return null;
    }

    return memset(ptr, 0, size);
}

int pizza_sys_memory_compare(const pizza_sys_memory_t ptr1, const pizza_sys_memory_t ptr2, size_t size) {
    if (!ptr1 || !ptr2 || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_compare() - Invalid pointers or zero size.\n");
        return -1;  // Return -1 for invalid input
    }

    return memcmp(ptr1, ptr2, size);
}

pizza_sys_memory_t pizza_sys_memory_move(pizza_sys_memory_t dest, const pizza_sys_memory_t src, size_t size) {
    if (!dest || !src || size == 0) {
        fprintf(stderr, "Error: pizza_sys_memory_move() - Invalid source or destination pointers, or zero size.\n");
        return null;
    }

    return memmove(dest, src, size);
}

pizza_sys_memory_t pizza_sys_memory_resize(pizza_sys_memory_t ptr, size_t old_size, size_t new_size) {
    if (!ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_resize() - Pointer is null.\n");
        return NULL;
    }

    if (new_size == 0) {
        pizza_sys_memory_free(ptr);
        return NULL;
    }

    if (new_size <= old_size) {
        // Shrinking, just realloc (no data copy needed)
        pizza_sys_memory_t new_ptr = pizza_sys_memory_realloc(ptr, new_size);
        if (!new_ptr) {
            fprintf(stderr, "Error: pizza_sys_memory_resize() - Memory shrink failed, original preserved.\n");
            return ptr;
        }
        return new_ptr;
    }

    // Allocate new memory manually to preserve old data
    pizza_sys_memory_t new_ptr = pizza_sys_memory_alloc(new_size);
    if (!new_ptr) {
        fprintf(stderr, "Error: pizza_sys_memory_resize() - Allocation failed.\n");
        return ptr;
    }

    // Copy old data
    memcpy(new_ptr, ptr, old_size);

    // Free old memory
    pizza_sys_memory_free(ptr);

    return new_ptr;
}

bool pizza_sys_memory_is_valid(const pizza_sys_memory_t ptr) {
    if (!ptr) {
        return false;
    }
    // Optional: Add more validation logic if needed, but normally you'd rely on the caller to manage validity.
    return true;
}

// *****************************************************************************
// output management
// *****************************************************************************

pizza_fstream_t *PIZZA_STDIN;
pizza_fstream_t *PIZZA_STDOUT;
pizza_fstream_t *PIZZA_STDERR;

int32_t PIZZA_IO_COLOR_ENABLE = 1; // Flag to enable/disable color output

// Define color codes for output
#define FOSSIL_IO_COLOR_RESET         "\033[0m"
#define FOSSIL_IO_COLOR_RED           "\033[31m"
#define FOSSIL_IO_COLOR_GREEN         "\033[32m"
#define FOSSIL_IO_COLOR_YELLOW        "\033[33m"
#define FOSSIL_IO_COLOR_BLUE          "\033[34m"
#define FOSSIL_IO_COLOR_MAGENTA       "\033[35m"
#define FOSSIL_IO_COLOR_CYAN          "\033[36m"
#define FOSSIL_IO_COLOR_WHITE         "\033[37m"
#define FOSSIL_IO_COLOR_BLACK         "\033[30m"
#define FOSSIL_IO_COLOR_ORANGE         "\033[38;5;208m"
#define FOSSIL_IO_COLOR_GRAY           "\033[90m"

// Bright colors
#define FOSSIL_IO_COLOR_BRIGHT_RED     "\033[91m"
#define FOSSIL_IO_COLOR_BRIGHT_GREEN   "\033[92m"
#define FOSSIL_IO_COLOR_BRIGHT_YELLOW  "\033[93m"
#define FOSSIL_IO_COLOR_BRIGHT_BLUE    "\033[94m"
#define FOSSIL_IO_COLOR_BRIGHT_MAGENTA "\033[95m"
#define FOSSIL_IO_COLOR_BRIGHT_CYAN    "\033[96m"
#define FOSSIL_IO_COLOR_BRIGHT_WHITE   "\033[97m"

// Define text attributes
#define FOSSIL_IO_ATTR_BOLD         "\033[1m"
#define FOSSIL_IO_ATTR_UNDERLINE    "\033[4m"
#define FOSSIL_IO_ATTR_REVERSED     "\033[7m"
#define FOSSIL_IO_ATTR_BLINK        "\033[5m"
#define FOSSIL_IO_ATTR_HIDDEN       "\033[8m"
#define FOSSIL_IO_ATTR_NORMAL       "\033[22m" // For reverting to normal text

// Additional attributes
#define FOSSIL_IO_ATTR_ITALIC       "\033[3m"
#define FOSSIL_IO_ATTR_STRIKETHROUGH "\033[9m"

#define FOSSIL_IO_BUFFER_SIZE 1000

// Function to apply color
void pizza_io_apply_color(const char *color) {
    if (pizza_io_cstr_compare(color, "red") == 0) {
        printf(FOSSIL_IO_COLOR_RED);
    } else if (pizza_io_cstr_compare(color, "green") == 0) {
        printf(FOSSIL_IO_COLOR_GREEN);
    } else if (pizza_io_cstr_compare(color, "yellow") == 0) {
        printf(FOSSIL_IO_COLOR_YELLOW);
    } else if (pizza_io_cstr_compare(color, "blue") == 0) {
        printf(FOSSIL_IO_COLOR_BLUE);
    } else if (pizza_io_cstr_compare(color, "magenta") == 0) {
        printf(FOSSIL_IO_COLOR_MAGENTA);
    } else if (pizza_io_cstr_compare(color, "cyan") == 0) {
        printf(FOSSIL_IO_COLOR_CYAN);
    } else if (pizza_io_cstr_compare(color, "white") == 0) {
        printf(FOSSIL_IO_COLOR_WHITE);
    } else if (pizza_io_cstr_compare(color, "black") == 0) {
        printf(FOSSIL_IO_COLOR_BLACK);
    } else if (pizza_io_cstr_compare(color, "orange") == 0) {
        printf(FOSSIL_IO_COLOR_ORANGE);
    } else if (pizza_io_cstr_compare(color, "gray") == 0) {
        printf(FOSSIL_IO_COLOR_GRAY);
    }
    // Bright colors
    else if (pizza_io_cstr_compare(color, "bright_red") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_RED);
    } else if (pizza_io_cstr_compare(color, "bright_green") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_GREEN);
    } else if (pizza_io_cstr_compare(color, "bright_yellow") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_YELLOW);
    } else if (pizza_io_cstr_compare(color, "bright_blue") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_BLUE);
    } else if (pizza_io_cstr_compare(color, "bright_magenta") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_MAGENTA);
    } else if (pizza_io_cstr_compare(color, "bright_cyan") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_CYAN);
    } else if (pizza_io_cstr_compare(color, "bright_white") == 0) {
        printf(FOSSIL_IO_COLOR_BRIGHT_WHITE);
    } else {
        printf(FOSSIL_IO_COLOR_RESET); // Reset to default if color not recognized
    }
}

// Function to apply text attributes (e.g., bold, underline)
void pizza_io_apply_attribute(const char *attribute) {
    if (pizza_io_cstr_compare(attribute, "bold") == 0) {
        printf(FOSSIL_IO_ATTR_BOLD);
    } else if (pizza_io_cstr_compare(attribute, "underline") == 0) {
        printf(FOSSIL_IO_ATTR_UNDERLINE);
    } else if (pizza_io_cstr_compare(attribute, "reversed") == 0) {
        printf(FOSSIL_IO_ATTR_REVERSED);
    } else if (pizza_io_cstr_compare(attribute, "blink") == 0) {
        printf(FOSSIL_IO_ATTR_BLINK);
    } else if (pizza_io_cstr_compare(attribute, "hidden") == 0) {
        printf(FOSSIL_IO_ATTR_HIDDEN);
    } else if (pizza_io_cstr_compare(attribute, "normal") == 0) {
        printf(FOSSIL_IO_ATTR_NORMAL);
    } else if (pizza_io_cstr_compare(attribute, "italic") == 0) {
        printf(FOSSIL_IO_ATTR_ITALIC);
    } else if (pizza_io_cstr_compare(attribute, "strikethrough") == 0) {
        printf(FOSSIL_IO_ATTR_STRIKETHROUGH);
    } else {
        printf(FOSSIL_IO_ATTR_NORMAL); // Reset to normal if attribute not recognized
    }
}

// Function to handle named positions (like top, bottom, left, right)
void pizza_io_apply_position(const char *pos) {
    if (pizza_io_cstr_compare(pos, "top") == 0) {
        // Apply position logic for top
        printf("\033[H"); // Move cursor to the top
    } else if (pizza_io_cstr_compare(pos, "bottom") == 0) {
        // Apply position logic for bottom
        printf("\033[999;1H"); // Move cursor to the bottom (example within reasonable bounds)
    } else if (pizza_io_cstr_compare(pos, "left") == 0) {
        // Apply position logic for left
        printf("\033[1;1H"); // Move cursor to the top-left corner
    } else if (pizza_io_cstr_compare(pos, "right") == 0) {
        // Apply position logic for right
        printf("\033[1;999H"); // Move cursor to the top-right corner (example within reasonable bounds)
    }
    // Add more positions if needed
}

// Function to print text with attributes, colors, positions, and format specifiers
void pizza_io_print_with_attributes(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Variable to keep track of the current position in the buffer
    const char *current_pos = buffer;
    const char *start = null;
    const char *end = null;

    // Iterate over the buffer and process color/attribute/position inside `{}` and format specifiers
    while ((start = strchr(current_pos, '{')) != null) {
        // Print text before '{'
        printf("%.*s", (int)(start - current_pos), current_pos);
        
        // Find the matching '}'
        end = strchr(start, '}');
        if (end) {
            // Extract attributes inside '{}'
            size_t length = end - start - 1;
            char attributes[length + 1];
            strncpy(attributes, start + 1, length);
            attributes[length] = '\0';

            // Split by comma to separate color, attribute, or position
            char *color = null;
            char *attribute = null;
            char *pos = null;
            char *comma_pos = strchr(attributes, ',');
            if (comma_pos) {
                *comma_pos = '\0';  // null-terminate the first part
                color = attributes; // Color or position part
                attribute = comma_pos + 1; // Attribute part
            } else {
                color = attributes; // Only one part (could be color, attribute, or position)
            }

            // Handle positions (like {pos:name})
            if (strstr(color, "pos:") == color) {
                pos = color + 4; // Skip the "pos:" prefix
                pizza_io_apply_position(pos);
            } else {
                // Apply color and/or attribute based on flags
                if (PIZZA_IO_COLOR_ENABLE && color) {
                    pizza_io_apply_color(color);
                }
                pizza_io_apply_attribute(attribute);
            }

            // Move past '}' and continue processing
            current_pos = end + 1;
        }
    }

    // Print remaining text after last '}'
    printf("%s", current_pos);

    va_end(args);
}

// Function to print a sanitized formatted string to a specific file stream with attributes
void pizza_io_fprint_with_attributes(pizza_fstream_t *stream, const char *str) {
    if (str != null && stream != null) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color and attribute logic (same as the print version)
        pizza_io_print_with_attributes(sanitized_str);

        // Write the sanitized string to the stream
        fputs(sanitized_str, stream->file);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

//
// OUTPUT FUNCTIONS
//

// Function to print a sanitized string with attributes inside {}
void pizza_io_puts(const char *str) {
    if (str != null) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination
        
        // Print the sanitized string with attributes
        pizza_io_print_with_attributes(sanitized_str);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a single character
void pizza_io_putchar(char c) {
    putchar(c);
}

// Function to print sanitized formatted output with attributes
void pizza_io_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized output with attributes
    pizza_io_print_with_attributes(buffer);

    va_end(args);
}

int pizza_io_vsnprintf(char *buffer, size_t size, const char *format, va_list args) {
    if (buffer == null || size == 0 || format == null) {
        return -1; // Invalid input
    }

    // Create a temporary buffer to hold the formatted string
    char temp_buffer[FOSSIL_IO_BUFFER_SIZE];
    int formatted_length = vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);

    if (formatted_length < 0 || (size_t)formatted_length >= size) {
        // Truncate the string if it exceeds the provided buffer size
        strncpy(buffer, temp_buffer, size - 1);
        buffer[size - 1] = '\0'; // Ensure null termination
        return (formatted_length < 0) ? -1 : (int)(size - 1);
    }

    // Copy the formatted string to the provided buffer
    strncpy(buffer, temp_buffer, size);
    buffer[formatted_length] = '\0'; // Ensure null termination
    return formatted_length;
}

// Function to print a sanitized string to a specific file stream
void pizza_io_fputs(pizza_fstream_t *stream, const char *str) {
    if (str != null && stream != null) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color/attributes and sanitize the string before printing
        pizza_io_fprint_with_attributes(stream, sanitized_str);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a sanitized formatted string to a specific file stream
void pizza_io_fprintf(pizza_fstream_t *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized formatted string with attributes to the specified stream
    pizza_io_fprint_with_attributes(stream, buffer);

    va_end(args);
}

// TUI PART

void pizza_io_clear_screen(void) {
    pizza_io_printf("\033[2J\033[H");
}

void pizza_io_move_cursor(int row, int col) {
    pizza_io_printf("\033[%d;%dH", row, col);
}

void pizza_io_hide_cursor(void) {
    pizza_io_printf("\033[?25l");
}

void pizza_io_show_cursor(void) {
    pizza_io_printf("\033[?25h");
}

void pizza_io_draw_horizontal_line(int length, char ch) {
    for (int i = 0; i < length; ++i) {
        putchar(ch);
    }
    putchar('\n');
}

void pizza_io_draw_vertical_line(int length, char ch) {
    for (int i = 0; i < length; ++i) {
        putchar(ch);
        putchar('\n');
    }
}

void pizza_io_flush(void) {
    fflush(stdout);
}

// *****************************************************************************
// string management
// *****************************************************************************

#ifndef HAVE_STRNLEN
size_t strnlen(const char *s, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen && s[i]; i++);
    return i;
}
#endif

#ifndef HAVE_STRNCASECMP
int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n && s1[i] && s2[i]; i++) {
        int diff = tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[i]);
        if (diff != 0) return diff;
    }
    return 0;
}
#endif

// ============================================================================
// C String Functions
// ============================================================================

cstr pizza_io_cstr_create(const char *init) {
    if (!init) return null;
    size_t length = strlen(init);
    cstr str = (cstr)malloc(length + 1);
    if (str) {
        strcpy(str, init);
    }
    return str;
}

void pizza_io_cstr_free(cstr str) {
    if (str) {
        free(str);
    }
}

cstr pizza_io_cstr_copy(ccstr str) {
    if (!str) return null;
    return pizza_io_cstr_create(str);
}

cstr pizza_io_cstr_dup(ccstr str) {
    if (!str) return null;
    size_t length = strlen(str);
    cstr new_str = (cstr)malloc(length + 1);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

cstr pizza_io_cstr_concat(ccstr s1, ccstr s2) {
    if (!s1 || !s2) return null;
    size_t length1 = strlen(s1);
    size_t length2 = strlen(s2);
    cstr str = (cstr)malloc(length1 + length2 + 1);
    if (str) {
        strcpy(str, s1);
        strcpy(str + length1, s2);
    }
    return str;
}

size_t pizza_io_cstr_length(ccstr str) {
    if (!str) return 0;
    return strlen(str);
}

int pizza_io_cstr_compare(ccstr s1, ccstr s2) {
    if (!s1 || !s2) return -1;
    return strcmp(s1, s2);
}

void pizza_io_cstr_trim(cstr str) {
    if (!str) return;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && isspace(str[start])) {
        start++;
    }
    while (end > start && isspace(str[end])) {
        end--;
    }
    size_t count = end - start + 1;
    if (start > 0) {
        memmove(str, str + start, count);
    }
    str[count] = '\0';
}

cstr *pizza_io_cstr_split(ccstr str, char delimiter, size_t *count) {
    if (!str || !count) return null;
    size_t length = strlen(str);
    size_t num_delimiters = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == delimiter) {
            num_delimiters++;
        }
    }
    *count = num_delimiters + 1;
    cstr *result = (cstr*)malloc(*count * sizeof(cstr));
    if (result) {
        size_t start = 0;
        size_t index = 0;
        for (size_t i = 0; i < length; i++) {
            if (str[i] == delimiter) {
                size_t count = i - start;
                result[index] = (cstr)malloc(count + 1);
                if (result[index]) {
                    memcpy(result[index], str + start, count);
                    result[index][count] = '\0';
                    start = i + 1;
                    index++;
                } else {
                    // Free previously allocated memory on error
                    for (size_t j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return null;
                }
            }
        }
        size_t count = length - start;
        result[index] = (cstr)malloc(count + 1);
        if (result[index]) {
            memcpy(result[index], str + start, count);
            result[index][count] = '\0';
        } else {
            // Free previously allocated memory on error
            for (size_t j = 0; j < index; j++) {
                free(result[j]);
            }
            free(result);
            return null;
        }
    }
    return result;
}

cstr pizza_io_cstr_replace(ccstr str, ccstr old, ccstr new_str) {
    if (!str || !old || !new_str) return null;
    size_t old_length = strlen(old);
    size_t new_length = strlen(new_str);
    size_t count = 0;
    size_t index = 0;
    size_t length = strlen(str);
    while (index < length) {
        if (strstr(str + index, old) == str + index) {
            count++;
            index += old_length;
        } else {
            index++;
        }
    }
    cstr result = (cstr)malloc(length + count * (new_length - old_length) + 1);
    if (result) {
        index = 0;
        size_t start = 0;
        while (index < length) {
            if (strstr(str + index, old) == str + index) {
                strcpy(result + start, new_str);
                start += new_length;
                index += old_length;
            } else {
                result[start] = str[index];
                start++;
                index++;
            }
        }
        result[start] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_to_upper(cstr str) {
    if (!str) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = toupper(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_to_lower(cstr str) {
    if (!str) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = tolower(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_starts_with(ccstr str, ccstr prefix) {
    if (!str || !prefix) return 0;
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (prefix_length > str_length) {
        return 0;
    }
    return strncmp(str, prefix, prefix_length) == 0;
}

int pizza_io_cstr_ends_with(ccstr str, ccstr suffix) {
    if (!str || !suffix) return 0;
    size_t str_length = strlen(str);
    size_t suffix_length = strlen(suffix);
    if (suffix_length > str_length) {
        return 0;
    }
    return strncmp(str + str_length - suffix_length, suffix, suffix_length) == 0;
}

cstr pizza_io_cstr_substring(ccstr str, size_t start, size_t length) {
    if (!str) return null;
    size_t str_length = strlen(str);
    if (start >= str_length) {
        return null;
    }
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        size_t count = str_length - start;
        if (length < count) {
            count = length;
        }
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_reverse(cstr str) {
    if (!str) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result) {
        for (size_t i = 0; i < length; i++) {
            result[i] = str[length - i - 1];
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_contains(ccstr str, ccstr substr) {
    if (!str || !substr) return 0;
    return strstr(str, substr) != null;
}

cstr pizza_io_cstr_repeat(ccstr str, size_t count) {
    if (!str || count == 0) return null;
    size_t length = strlen(str);
    size_t new_length = length * count;
    cstr result = (cstr)malloc(new_length + 1);
    if (result) {
        for (size_t i = 0; i < count; i++) {
            memcpy(result + i * length, str, length);
        }
        result[new_length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_strip(ccstr str, char ch) {
    if (!str) return null;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && str[start] == ch) {
        start++;
    }
    while (end > start && str[end] == ch) {
        end--;
    }
    size_t count = end - start + 1;
    cstr result = (cstr)malloc(count + 1);
    if (result) {
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

size_t pizza_io_cstr_count(ccstr str, ccstr substr) {
    if (!str || !substr) return 0;
    size_t count = 0;
    size_t length = strlen(substr);
    while ((str = strstr(str, substr)) != null) {
        count++;
        str += length;
    }
    return count;
}

cstr pizza_io_cstr_pad_left(ccstr str, size_t total_length, char pad_char) {
    if (!str || total_length == 0) return null;
    size_t length = strlen(str);
    if (length >= total_length) {
        return pizza_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result) {
        memset(result, pad_char, pad_length);
        strcpy(result + pad_length, str);
        result[total_length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_pad_right(ccstr str, size_t total_length, char pad_char) {
    if (!str || total_length == 0) return null;
    size_t length = strlen(str);
    if (length >= total_length) {
        return pizza_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result) {
        strcpy(result, str);
        memset(result + length, pad_char, pad_length);
        result[total_length] = '\0';
    }
    return result;
}

bool pizza_io_cstr_append(cstr dest, size_t max_len, cstr src) {
    if (!dest || !src || max_len == 0) return false;

    // Find current length of dest up to max_len
    size_t dest_len = 0;
    while (dest_len < max_len && dest[dest_len] != '\0') {
        ++dest_len;
    }

    // If no null-terminator found in range, dest is not safe
    if (dest_len == max_len) return false;

    size_t src_len = strlen(src);

    // Make sure there's enough space (including null terminator)
    if (dest_len + src_len >= max_len) return false;

    memcpy(dest + dest_len, src, src_len);
    dest[dest_len + src_len] = '\0';

    return true;
}
