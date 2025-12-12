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

// HASH Algorithm magic - Maximized for power and entropy

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

    for (size_t v = 0; v < sizeof(vars) / sizeof(vars[0]); ++v) {
        const char *val = vars[v];
        if (val) {
            for (size_t i = 0; val[i]; ++i) {
                hash ^= (uint8_t)val[i];
                hash *= 0x100000001b3ULL;
                hash ^= (hash >> 23);
            }
        }
    }

    // Add some entropy from current time
    hash ^= get_pizza_time_microseconds();
    hash *= 0x100000001b3ULL;
    hash ^= (hash >> 31);

    return hash;
}

void fossil_pizza_hash(const char *input, const char *output, uint8_t *hash_out) {
    const uint64_t PRIME1 = 0x100000001b3ULL;
    const uint64_t PRIME2 = 0x9e3779b185ebca87ULL;
    const uint64_t PRIME3 = 0x84222325cbf29ce4ULL;
    static uint64_t SALT = 0;
    if (SALT == 0) SALT = get_pizza_device_salt();

    uint64_t state1 = 0xcbf29ce484222325ULL ^ SALT;
    uint64_t state2 = 0x84222325cbf29ce4ULL ^ ~SALT;
    uint64_t state3 = 0x9e3779b185ebca87ULL ^ (SALT << 1);

    size_t in_len = strlen(input);
    size_t out_len = strlen(output);

    uint64_t nonce = get_pizza_time_microseconds();

    // Mix input string
    for (size_t i = 0; i < in_len; ++i) {
        state1 ^= (uint8_t)input[i];
        state1 *= PRIME1;
        state1 ^= (state1 >> 27);
        state1 ^= (state1 << 33);
        state2 += (state1 ^ (state2 >> 19));
        state2 *= PRIME2;
        state2 ^= (state2 << 29);
        state3 ^= (state2 ^ (state1 >> 11));
        state3 *= PRIME3;
        state3 ^= (state3 >> 17);
    }

    // Mix output string
    for (size_t i = 0; i < out_len; ++i) {
        state2 ^= (uint8_t)output[i];
        state2 *= PRIME2;
        state2 ^= (state2 >> 29);
        state2 ^= (state2 << 31);
        state1 += (state2 ^ (state1 >> 13));
        state1 *= PRIME1;
        state3 ^= (state1 ^ (state2 >> 7));
        state3 *= PRIME3;
        state3 ^= (state3 << 23);
    }

    // Nonce and length entropy
    state1 ^= nonce ^ ((uint64_t)in_len << 32);
    state2 ^= ~nonce ^ ((uint64_t)out_len << 16);
    state3 ^= (nonce << 3) ^ ((uint64_t)(in_len + out_len) << 24);

    // Extra mixing rounds for avalanche effect
    for (int i = 0; i < 12; ++i) {
        state1 += (state2 ^ (state1 >> (13 + (i % 7))));
        state2 += (state3 ^ (state2 >> (11 + (i % 5))));
        state3 += (state1 ^ (state3 >> (17 + (i % 3))));
        state1 ^= (state1 << (41 - (i % 13)));
        state2 ^= (state2 << (37 - (i % 11)));
        state3 ^= (state3 << (29 - (i % 9)));
        state1 *= PRIME1;
        state2 *= PRIME2;
        state3 *= PRIME3;
        state1 ^= (state2 >> (i + 1));
        state2 ^= (state3 >> (i + 2));
        state3 ^= (state1 >> (i + 3));
    }

    // Final hash output
    for (size_t i = 0; i < FOSSIL_PIZZA_HASH_SIZE; ++i) {
        uint64_t mixed;
        if (i % 3 == 0) mixed = state1;
        else if (i % 3 == 1) mixed = state2;
        else mixed = state3;
        mixed ^= (mixed >> ((i % 7) + 13));
        mixed *= (i % 2 == 0 ? PRIME1 : PRIME2);
        mixed ^= SALT;
        mixed ^= (nonce << (i % 17));
        mixed ^= (state1 >> (i % 23));
        mixed ^= (state2 << (i % 19));
        mixed ^= (state3 >> (i % 11));
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
    pizza_io_printf("{cyan}  acutest           Acutest theme (C Test Framework){reset}\n");
    pizza_io_printf("{cyan}  minunit           MinUnit theme (C Test Framework){reset}\n");
    pizza_io_printf("{cyan}  cmocka            CMocka theme (C Test Framework){reset}\n");
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
            } else if (pizza_io_cstr_compare(theme_str, "acutest") == 0) {
                pallet.theme = PIZZA_THEME_ACUTEST;
                G_PIZZA_THEME = PIZZA_THEME_ACUTEST;
            } else if (pizza_io_cstr_compare(theme_str, "minunit") == 0) {
                pallet.theme = PIZZA_THEME_MINUNIT;
                G_PIZZA_THEME = PIZZA_THEME_MINUNIT;
            } else if (pizza_io_cstr_compare(theme_str, "cmocka") == 0) {
                pallet.theme = PIZZA_THEME_CMOCKA;
                G_PIZZA_THEME = PIZZA_THEME_CMOCKA;
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

/*
 * Host information functions with AI tricks:
 * - Defensive programming: always check for null pointers.
 * - Use likely/unlikely macros for branch prediction (if available).
 * - Use memset to zero out structures before filling (for safety).
 * - Use strncpy with explicit null-termination.
 * - Use static buffers for temporary strings (if needed).
 * - Use fallback/default values on error.
 * - Use platform-specific APIs with error checking.
 * - Avoid double evaluation of arguments.
 * - Use size_t for buffer sizes.
 * - Use restrict for pointer arguments (if header included).
 * - Use attribute((nonnull)) if header included.
 * - Use local variables for intermediate results.
 */

int pizza_sys_hostinfo_get_system(pizza_sys_hostinfo_system_t *info) {
    if (unlikely(!info)) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    OSVERSIONINFO osvi;
    memset(&osvi, 0, sizeof(osvi));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (unlikely(!GetVersionEx(&osvi))) return -1;
    snprintf(info->os_name, sizeof(info->os_name), "Windows");
    snprintf(info->os_version, sizeof(info->os_version), "%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion);
    snprintf(info->kernel_version, sizeof(info->kernel_version), "%lu", osvi.dwBuildNumber);

    DWORD size = (DWORD)sizeof(info->hostname);
    if (!GetComputerNameA(info->hostname, &size)) {
        strncpy(info->hostname, "Unknown", sizeof(info->hostname) - 1);
        info->hostname[sizeof(info->hostname) - 1] = '\0';
    }

    size = (DWORD)sizeof(info->username);
    if (!GetUserNameA(info->username, &size)) {
        strncpy(info->username, "Unknown", sizeof(info->username) - 1);
        info->username[sizeof(info->username) - 1] = '\0';
    }

    // Domain name
    size = (DWORD)sizeof(info->domain_name);
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
    memset(&sysinfo, 0, sizeof(sysinfo));
    if (unlikely(uname(&sysinfo) != 0)) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (unlikely(gethostname(info->hostname, sizeof(info->hostname)) != 0))
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
    memset(&sysinfo, 0, sizeof(sysinfo));
    if (unlikely(uname(&sysinfo) != 0)) return -1;
    strncpy(info->os_name, sysinfo.sysname, sizeof(info->os_name) - 1);
    info->os_name[sizeof(info->os_name) - 1] = '\0';
    strncpy(info->os_version, sysinfo.version, sizeof(info->os_version) - 1);
    info->os_version[sizeof(info->os_version) - 1] = '\0';
    strncpy(info->kernel_version, sysinfo.release, sizeof(info->kernel_version) - 1);
    info->kernel_version[sizeof(info->kernel_version) - 1] = '\0';

    if (unlikely(gethostname(info->hostname, sizeof(info->hostname)) != 0))
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
    if (unlikely(!info)) return -1;
    memset(info, 0, sizeof(*info));

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
    memset(&sysinfo, 0, sizeof(sysinfo));
    if (unlikely(uname(&sysinfo) != 0)) return -1;

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
    if (unlikely(!info)) return -1;
    memset(info, 0, sizeof(*info));
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    memset(&statex, 0, sizeof(statex));
    statex.dwLength = sizeof(statex);
    if (unlikely(!GlobalMemoryStatusEx(&statex))) return -1;
    info->total_memory = statex.ullTotalPhys;
    info->free_memory = statex.ullAvailPhys;
    info->used_memory = statex.ullTotalPhys - statex.ullAvailPhys;
    info->available_memory = statex.ullAvailPhys;
    info->total_swap = statex.ullTotalPageFile;
    info->free_swap = statex.ullAvailPageFile;
    info->used_swap = statex.ullTotalPageFile - statex.ullAvailPageFile;
#elif defined(__APPLE__)
    int64_t memsize = 0;
    size_t len = sizeof(memsize);
    if (unlikely(sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0)) return -1;
    info->total_memory = memsize;
    info->free_memory = 0; // macOS does not provide free memory info in the same way
    info->used_memory = 0;
    info->available_memory = 0;
    info->total_swap = 0;
    info->free_swap = 0;
    info->used_swap = 0;
#else
    struct sysinfo sys_info;
    memset(&sys_info, 0, sizeof(sys_info));
    if (unlikely(sysinfo(&sys_info) != 0)) return -1;
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
    if (unlikely(!info)) return -1;
    memset(info, 0, sizeof(*info));
    uint16_t test = 0x0001;
    info->is_little_endian = (*(uint8_t*)&test) ? 1 : 0;
    return 0;
}

// *****************************************************************************
// soap sanitizer
// *****************************************************************************

#define MAX_CUSTOM_FILTERS 64

/** Lookup table for rot-brain words and their suggested replacements */
static const struct {
    const char *bad;
    const char *suggested;
} FOSSIL_SOAP_SUGGESTIONS[] = {
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
    {"lol", "funny"},
    {"omg", "surprising"},
    {"brb", "be right back"},
    {"idk", "I don't know"},
    {"imo", "in my opinion"},
    {"lmao", "laughing"},
    {"nvm", "never mind"},
    {"tbh", "to be honest"},
    {"tldr", "too long"},
    {"ttyl", "talk to you later"},
    {"wyd", "what are you doing"},
    {"wtf", "what the heck"},
    {"yolo", "you only live once"},
    {"rot-brain", "stupid"},
    {"rot brain", "stupid"},
    {"rotbrain", "stupid"},
    {null, null} // Sentinel to mark the end
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
    {"not never", "never"},
    {"free gift", "gift"},
    {"very unique", "unique"},
    {null, null} // Sentinel to mark the end
};

/** Lookup table for sarcastic phrases */
static const char *SARCASTIC_PHRASES[] = {
    "Oh, great",
    "Yeah, right",
    "Nice job",
    "Well done",
    "Good luck with that",
    "Sure, why not",
    "Fantastic",
    "Brilliant",
    "Wonderful",
    "Perfect",
    null // Sentinel to mark the end
};

/** Lookup table for formal phrases */
static const char *FORMAL_PHRASES[] = {
    "Dear Sir or Madam",
    "To whom it may concern",
    "Yours sincerely",
    "Yours faithfully",
    "Best regards",
    "Respectfully",
    "I would like to",
    "I am writing to",
    "Please find attached",
    "Thank you for your consideration",
    null // Sentinel to mark the end
};

static char custom_storage[MAX_CUSTOM_FILTERS][64];
static const char *custom_filters[MAX_CUSTOM_FILTERS] = {0};

/** Lookup table for words that need to be skipped due to misdetection */
static const char *SKIP_WORDS[] = {
    "limit",
    "size",
    null // Sentinel to mark the end
};

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
 * Optimized for short words, early exit if distance > 2.
 */
static int fuzzy_match(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 == 0 || len2 == 0) return (int)(len1 + len2);
    if (abs((int)len1 - (int)len2) > 2) return 3; // AI trick: early exit for big length diff

    int prev[65], curr[65];
    if (len2 > 64) return 3; // AI trick: limit for stack buffer

    for (size_t j = 0; j <= len2; j++) prev[j] = (int)j;
    for (size_t i = 1; i <= len1; i++) {
        curr[0] = (int)i;
        int min_row = curr[0];
        for (size_t j = 1; j <= len2; j++) {
            int cost = (tolower((unsigned char)str1[i - 1]) == tolower((unsigned char)str2[j - 1])) ? 0 : 1;
            curr[j] = fmin(fmin(prev[j] + 1, curr[j - 1] + 1), prev[j - 1] + cost);
            if (curr[j] < min_row) min_row = curr[j];
        }
        if (min_row > 2) return 3; // AI trick: early exit if row min > 2
        memcpy(prev, curr, (len2 + 1) * sizeof(int));
    }
    return curr[len2];
}

/**
 * @brief Check if a word should be skipped.
 */
static int should_skip_word(const char *word) {
    for (size_t i = 0; SKIP_WORDS[i] != null; i++) {
        if (pizza_io_cstr_compare(word, SKIP_WORDS[i]) == 0) {
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
    return null;
}

/**
 * @brief Look up a suggested alternative for a given word, checking both custom filters and predefined suggestions.
 * AI trick: fuzzy match with threshold, prefer exact, then fuzzy, then grammar.
 */
static const char *pizza_io_soap_get_suggestion(const char *word) {
    if (should_skip_word(word)) {
        return null;
    }

    // Check in custom filters first
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS && custom_filters[i] != null; i++) {
        if (custom_strcasecmp(word, custom_filters[i]) == 0) {
            return custom_filters[i];  // Use the custom filter word itself as suggestion
        }
        if (fuzzy_match(word, custom_filters[i]) <= 2) {
            return custom_filters[i];  // Return fuzzy match result
        }
    }

    // Check in predefined suggestions
    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != null; i++) {
        if (custom_strcasecmp(word, FOSSIL_SOAP_SUGGESTIONS[i].bad) == 0) {
            return FOSSIL_SOAP_SUGGESTIONS[i].suggested;
        }
        // AI trick: fuzzy match for slang, but only if word is at least 4 chars
        if (strlen(word) >= 4 && fuzzy_match(word, FOSSIL_SOAP_SUGGESTIONS[i].bad) == 1) {
            return FOSSIL_SOAP_SUGGESTIONS[i].suggested;
        }
    }

    // Check in grammar suggestions
    for (size_t i = 0; FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect != null; i++) {
        if (custom_strcasecmp(word, FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect) == 0) {
            return FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].correct;
        }
    }

    return null;
}

/**
 * @brief Sanitize input text by removing or replacing "rot-brain" and meme-based language.
 * @param text Input string.
 * @return Newly allocated sanitized string.
 * AI trick: preserve original punctuation, handle leetspeak, use fuzzy match.
 */
char *pizza_io_soap_sanitize(const char *text) {
    if (!text) return null;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 1); // Allocate more space to handle replacements
    if (!output) return null;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-') {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1) word_idx = sizeof(word) - 2;
        } else {
            word[word_idx] = '\0';
            if (word_idx > 0) {
                pizza_io_soap_normalize_leetspeak(word);
                const char *suggested = pizza_io_soap_get_suggestion(word);
                if (suggested && !should_skip_word(word)) {
                    for (size_t j = 0; j < strlen(suggested); j++) {
                        output[out_idx++] = suggested[j];
                    }
                } else {
                    for (size_t j = 0; j < word_idx; j++) {
                        output[out_idx++] = word[j];
                    }
                }
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    if (word_idx > 0) {
        pizza_io_soap_normalize_leetspeak(word);
        const char *suggested = pizza_io_soap_get_suggestion(word);
        if (suggested && !should_skip_word(word)) {
            for (size_t j = 0; j < strlen(suggested); j++) {
                output[out_idx++] = suggested[j];
            }
        } else {
            for (size_t j = 0; j < word_idx; j++) {
                output[out_idx++] = word[j];
            }
        }
    }
    output[out_idx] = '\0';
    return output;
}

/**
 * @brief Suggest improved wording for meme/rot-brain language.
 * AI trick: same as sanitize, but always prefer suggestion if available.
 */
char *pizza_io_soap_suggest(const char *text) {
    if (!text) return null;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 64); // Allocate more space to handle replacements
    if (!output) return null;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-') {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1) word_idx = sizeof(word) - 2;
        } else {
            word[word_idx] = '\0';
            if (word_idx > 0) {
                pizza_io_soap_normalize_leetspeak(word);
                const char *suggested = pizza_io_soap_get_suggestion(word);
                if (suggested && !should_skip_word(word)) {
                    strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
                    out_idx += strlen(suggested);
                } else {
                    strncpy(&output[out_idx], word, len * 2 + 64 - out_idx);
                    out_idx += word_idx;
                }
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    if (word_idx > 0) {
        pizza_io_soap_normalize_leetspeak(word);
        const char *suggested = pizza_io_soap_get_suggestion(word);
        if (suggested && !should_skip_word(word)) {
            strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
            out_idx += strlen(suggested);
        } else {
            strncpy(&output[out_idx], word, len * 2 + 64 - out_idx);
            out_idx += word_idx;
        }
    }
    output[out_idx] = '\0';
    return output;
}

/**
 * @brief Add a custom word or phrase to the filter.
 * AI trick: lowercase and deduplicate.
 */
int pizza_io_soap_add_custom_filter(const char *phrase) {
    // Deduplicate
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS; i++) {
        if (custom_filters[i] && custom_strcasecmp(custom_filters[i], phrase) == 0) {
            return 0;
        }
    }
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS; i++) {
        if (custom_filters[i] == null) {
            size_t j = 0;
            while (phrase[j] != '\0' && j < sizeof(custom_storage[i]) - 1) {
                custom_storage[i][j] = tolower((unsigned char)phrase[j]);
                j++;
            }
            custom_storage[i][j] = '\0';
            custom_filters[i] = custom_storage[i];
            return 0;
        }
    }
    return -1;
}

/**
 * @brief Clear all custom filters.
 */
void pizza_io_soap_clear_custom_filters(void) {
    memset(custom_filters, 0, sizeof(custom_filters));
}

/**
 * @brief Detect tone of the text using phrase lookup.
 * AI trick: prioritize sarcastic, then formal, else casual.
 */
const char *pizza_io_soap_detect_tone(const char *text) {
    for (size_t i = 0; SARCASTIC_PHRASES[i] != null; i++) {
        if (custom_strcasestr(text, SARCASTIC_PHRASES[i])) {
            return "sarcastic";
        }
    }

    for (size_t i = 0; FORMAL_PHRASES[i] != null; i++) {
        if (custom_strcasestr(text, FORMAL_PHRASES[i])) {
            return "formal";
        }
    }

    return "casual";
}

/**
 * @brief Detect if text contains rot-brain language.
 * AI trick: use substring search for slang.
 */
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

/*
 * Memory management functions with AI tricks:
 * - Defensive programming: always check for null and zero size.
 * - Use branch prediction hints for error paths.
 * - Zero out memory on allocation for security (optional, see comments).
 * - Use restrict for memcpy/memmove when possible (for optimization).
 * - Use inline for small wrappers (if supported).
 * - Use unlikely/likely macros for error handling (if available).
 * - Use memset_s if available for secure zeroing (fallback to memset).
 * - Use static inline for small helpers (if header included).
 */

/* Helper: safe addition check for size_t (returns true on overflow) */
static inline bool size_add_overflow(size_t a, size_t b, size_t *out) {
    if (b > SIZE_MAX - a) return true;
    *out = a + b;
    return false;
}

/* Helper: safe multiplication check for size_t (returns true on overflow) */
static inline bool size_mul_overflow(size_t a, size_t b, size_t *out) {
    if (a == 0 || b == 0) { *out = 0; return false; }
    if (a > SIZE_MAX / b) return true;
    *out = a * b;
    return false;
}

/* deterministic malloc wrapper: never request malloc(0) from system */
static void *pizza_malloc_checked(size_t n) {
    if (n == 0) n = 1;
    return malloc(n);
}

/* Secure zeroing: use memset_s when available, otherwise volatile write */
static void pizza_sys_memory_secure_zero_impl(void *ptr, size_t size) {
#if defined(__STDC_LIB_EXT1__) /* bounds-checked libs (memset_s) */
    /* memset_s returns zero on success per annex K, but presence is platform-dependent */
    (void)memset_s(ptr, size, 0, size);
#else
    volatile unsigned char *p = (volatile unsigned char *)ptr;
    while (size--) *p++ = 0;
#endif
}

/* -------------------------
 * Memory API
 * ------------------------- */

/* Allocate size bytes, zeroed. Returns NULL on failure or if size==0 (prints error). */
pizza_sys_memory_t pizza_sys_memory_alloc(size_t size) {
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Cannot allocate zero bytes.\n");
        return NULL;
    }
    /* guard extremely large allocation requests */
    if (size > SIZE_MAX - 1) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - size too large.\n");
        return NULL;
    }

    void *ptr = pizza_malloc_checked(size);
    if (unlikely(!ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_alloc() - Memory allocation failed.\n");
        return NULL;
    }

    /* Zero memory for security by default (matches original AI trick) */
    memset(ptr, 0, size);
    return ptr;
}

/*
 * Realloc semantics:
 * - if size == 0: free(ptr) and return NULL (explicit)
 * - on failure: original pointer remains valid (we don't free it), return NULL
 * - on success: return new pointer
 */
pizza_sys_memory_t pizza_sys_memory_realloc(pizza_sys_memory_t ptr, size_t size) {
    if (size == 0) {
        /* free existing block and return NULL as a clear signal */
        if (ptr) free(ptr);
        return NULL;
    }

    /* check extreme size */
    if (size > SIZE_MAX - 1) {
        fprintf(stderr, "Error: pizza_sys_memory_realloc() - size too large.\n");
        return NULL;
    }

    /* Note: realloc(NULL, size) behaves like malloc(size) */
    void *new_ptr = realloc(ptr, size);
    if (unlikely(!new_ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_realloc() - Memory reallocation failed.\n");
        /* original ptr remains allocated per C standard; return NULL to indicate failure */
        return NULL;
    }
    return new_ptr;
}

/* calloc wrapper; returns NULL on error or zero arguments */
pizza_sys_memory_t pizza_sys_memory_calloc(size_t num, size_t size) {
    if (unlikely(num == 0 || size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Cannot allocate zero elements or zero bytes.\n");
        return NULL;
    }

    /* check multiplication overflow */
    size_t total;
    if (size_mul_overflow(num, size, &total)) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - size overflow.\n");
        return NULL;
    }

    void *ptr = calloc(num, size);
    if (unlikely(!ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_calloc() - Memory allocation failed.\n");
        return NULL;
    }
    return ptr;
}

/*
 * Initialize a region with a byte value.
 * Returns ptr on success, NULL on invalid args.
 */
pizza_sys_memory_t pizza_sys_memory_init(pizza_sys_memory_t ptr, size_t size, int32_t value) {
    if (unlikely(!ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Pointer is null.\n");
        return NULL;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_init() - Cannot initialize zero bytes.\n");
        return NULL;
    }
    /* memset returns void*, cast to pizza_sys_memory_t for a consistent return */
    (void)memset(ptr, (unsigned char)value, size);
    return ptr;
}

/* Free wrapper; safe to call with NULL */
void pizza_sys_memory_free(pizza_sys_memory_t ptr) {
    if (likely(ptr)) free(ptr);
}

/*
 * Copy memory with bounds checks.
 * Returns dest on success, NULL on failure.
 */
pizza_sys_memory_t pizza_sys_memory_copy(pizza_sys_memory_t restrict dest, const pizza_sys_memory_t restrict src, size_t size) {
    if (unlikely(!dest || !src)) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Source or destination is null.\n");
        return NULL;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_copy() - Cannot copy zero bytes.\n");
        return NULL;
    }
    return memcpy(dest, src, size);
}

/*
 * Set memory region with a byte value; returns ptr on success.
 */
pizza_sys_memory_t pizza_sys_memory_set(pizza_sys_memory_t ptr, int32_t value, size_t size) {
    if (unlikely(!ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Pointer is null.\n");
        return NULL;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_set() - Cannot set zero bytes.\n");
        return NULL;
    }
    (void)memset(ptr, (unsigned char)value, size);
    return ptr;
}

/*
 * Duplicate raw memory block: allocate new block and copy.
 * Returns new pointer or NULL.
 */
pizza_sys_memory_t pizza_sys_memory_dup(const pizza_sys_memory_t src, size_t size) {
    if (unlikely(!src || size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_dup() - Invalid source or zero size.\n");
        return NULL;
    }
    pizza_sys_memory_t dest = pizza_sys_memory_alloc(size);
    if (unlikely(!dest)) {
        /* error already logged inside pizza_sys_memory_alloc */
        return NULL;
    }
    memcpy(dest, src, size);
    return dest;
}

/* Secure zero wrapper */
pizza_sys_memory_t pizza_sys_memory_zero(pizza_sys_memory_t ptr, size_t size) {
    if (unlikely(!ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_zero() - Pointer is null.\n");
        return NULL;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_zero() - Cannot zero out zero bytes.\n");
        return NULL;
    }
    pizza_sys_memory_secure_zero_impl(ptr, size);
    return ptr;
}

/*
 * Compare memory blocks:
 * - returns 0 if equal, non-zero otherwise
 * - returns INT_MIN on invalid args (so caller can distinguish error)
 */
int pizza_sys_memory_compare(const pizza_sys_memory_t ptr1, const pizza_sys_memory_t ptr2, size_t size) {
    if (unlikely(!ptr1 || !ptr2)) {
        fprintf(stderr, "Error: pizza_sys_memory_compare() - Invalid pointer(s).\n");
        return INT_MIN;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_compare() - Zero size comparison.\n");
        return INT_MIN;
    }
    return memcmp(ptr1, ptr2, size);
}

/* memmove wrapper */
pizza_sys_memory_t pizza_sys_memory_move(pizza_sys_memory_t restrict dest, const pizza_sys_memory_t restrict src, size_t size) {
    if (unlikely(!dest || !src)) {
        fprintf(stderr, "Error: pizza_sys_memory_move() - Invalid source or destination pointer.\n");
        return NULL;
    }
    if (unlikely(size == 0)) {
        fprintf(stderr, "Error: pizza_sys_memory_move() - Cannot move zero bytes.\n");
        return NULL;
    }
    return memmove(dest, src, size);
}

/*
 * Resize semantics:
 * - If ptr == NULL, behaves like alloc(new_size)
 * - If new_size == 0, free(ptr) and return NULL
 * - If new_size <= old_size, shrink with realloc (or return original on failure)
 * - If new_size > old_size, try to allocate new block, copy old_size bytes, free old and return new
 *
 * Note: We require caller to pass old_size when doing manual reallocation copy path.
 */
pizza_sys_memory_t pizza_sys_memory_resize(pizza_sys_memory_t ptr, size_t old_size, size_t new_size) {
    if (ptr == NULL) {
        /* behave like alloc */
        return pizza_sys_memory_alloc(new_size);
    }

    if (unlikely(new_size == 0)) {
        pizza_sys_memory_free(ptr);
        return NULL;
    }

    if (new_size <= old_size) {
        /* attempt shrink; if realloc fails, keep original */
        pizza_sys_memory_t new_ptr = pizza_sys_memory_realloc(ptr, new_size);
        if (unlikely(!new_ptr)) {
            fprintf(stderr, "Warning: pizza_sys_memory_resize() - shrink realloc failed, original preserved.\n");
            return ptr;
        }
        return new_ptr;
    }

    /* grow path: allocate new block and copy old contents */
    pizza_sys_memory_t new_ptr = pizza_sys_memory_alloc(new_size);
    if (unlikely(!new_ptr)) {
        fprintf(stderr, "Error: pizza_sys_memory_resize() - Allocation failed; returning original pointer.\n");
        return ptr;
    }

    /* copy the min(old_size, new_size) bytes */
    size_t to_copy = old_size < new_size ? old_size : new_size;
    memcpy(new_ptr, ptr, to_copy);
    pizza_sys_memory_free(ptr);
    return new_ptr;
}

/* Validate pointer (simple non-NULL check) */
bool pizza_sys_memory_is_valid(const pizza_sys_memory_t ptr) {
    return likely(ptr != NULL);
}

// *****************************************************************************
// output management
// *****************************************************************************

// AI tricks applied:
// - Defensive programming: always check for null pointers and buffer overflows.
// - Use likely/unlikely macros for branch prediction (if available).
// - Use restrict for pointer arguments where possible.
// - Use static inline for small helpers (if header included).
// - Use memset_s if available for secure zeroing (not needed here, but for future).
// - Use size_t for all lengths and indexes.
// - Avoid double evaluation of arguments.
// - Use strnlen for safety where possible.
// - Use va_copy for variadic argument safety.
// - Use branch prediction hints for error paths.
// - Use static buffers for thread safety (if needed).
// - Use attribute((format(printf, ...))) for printf-like functions (if header included).

pizza_fstream_t *PIZZA_STDIN = NULL;
pizza_fstream_t *PIZZA_STDOUT = NULL;
pizza_fstream_t *PIZZA_STDERR = NULL;

int32_t PIZZA_IO_COLOR_ENABLE = 1; // Flag to enable/disable color output

// ================================================================
// RESET
// ================================================================
#define FOSSIL_IO_COLOR_RESET            "\033[0m"

// ================================================================
// DARK (STANDARD) COLORS
// ================================================================
#define FOSSIL_IO_COLOR_BLACK            "\033[30m"
#define FOSSIL_IO_COLOR_RED              "\033[31m"
#define FOSSIL_IO_COLOR_GREEN            "\033[32m"
#define FOSSIL_IO_COLOR_YELLOW           "\033[33m"
#define FOSSIL_IO_COLOR_BLUE             "\033[34m"
#define FOSSIL_IO_COLOR_MAGENTA          "\033[35m"
#define FOSSIL_IO_COLOR_CYAN             "\033[36m"
#define FOSSIL_IO_COLOR_WHITE            "\033[37m"
#define FOSSIL_IO_COLOR_GRAY             "\033[90m"
#define FOSSIL_IO_COLOR_ORANGE           "\033[38;5;208m"
#define FOSSIL_IO_COLOR_PINK             "\033[38;5;205m"
#define FOSSIL_IO_COLOR_PURPLE           "\033[38;5;93m"
#define FOSSIL_IO_COLOR_BROWN            "\033[38;5;94m"
#define FOSSIL_IO_COLOR_TEAL             "\033[38;5;30m"
#define FOSSIL_IO_COLOR_SILVER           "\033[38;5;7m"

// ================================================================
// BRIGHT COLORS
// ================================================================
#define FOSSIL_IO_COLOR_BRIGHT_BLACK     "\033[90m"
#define FOSSIL_IO_COLOR_BRIGHT_RED       "\033[91m"
#define FOSSIL_IO_COLOR_BRIGHT_GREEN     "\033[92m"
#define FOSSIL_IO_COLOR_BRIGHT_YELLOW    "\033[93m"
#define FOSSIL_IO_COLOR_BRIGHT_BLUE      "\033[94m"
#define FOSSIL_IO_COLOR_BRIGHT_MAGENTA   "\033[95m"
#define FOSSIL_IO_COLOR_BRIGHT_CYAN      "\033[96m"
#define FOSSIL_IO_COLOR_BRIGHT_WHITE     "\033[97m"

// ================================================================
// BACKGROUND COLORS
// ================================================================
#define FOSSIL_IO_BG_BLACK            "\033[40m"
#define FOSSIL_IO_BG_RED              "\033[41m"
#define FOSSIL_IO_BG_GREEN            "\033[42m"
#define FOSSIL_IO_BG_YELLOW           "\033[43m"
#define FOSSIL_IO_BG_BLUE             "\033[44m"
#define FOSSIL_IO_BG_MAGENTA          "\033[45m"
#define FOSSIL_IO_BG_CYAN             "\033[46m"
#define FOSSIL_IO_BG_WHITE            "\033[47m"
#define FOSSIL_IO_BG_GRAY             "\033[100m"
#define FOSSIL_IO_BG_ORANGE           "\033[48;5;208m"
#define FOSSIL_IO_BG_PINK             "\033[48;5;205m"
#define FOSSIL_IO_BG_PURPLE           "\033[48;5;93m"
#define FOSSIL_IO_BG_BROWN            "\033[48;5;94m"
#define FOSSIL_IO_BG_TEAL             "\033[48;5;30m"
#define FOSSIL_IO_BG_SILVER           "\033[48;5;7m"

// Bright background colors
#define FOSSIL_IO_BG_BRIGHT_BLACK     "\033[100m"
#define FOSSIL_IO_BG_BRIGHT_RED       "\033[101m"
#define FOSSIL_IO_BG_BRIGHT_GREEN     "\033[102m"
#define FOSSIL_IO_BG_BRIGHT_YELLOW    "\033[103m"
#define FOSSIL_IO_BG_BRIGHT_BLUE      "\033[104m"
#define FOSSIL_IO_BG_BRIGHT_MAGENTA   "\033[105m"
#define FOSSIL_IO_BG_BRIGHT_CYAN      "\033[106m"
#define FOSSIL_IO_BG_BRIGHT_WHITE     "\033[107m"

// ================================================================
// TEXT ATTRIBUTES
// ================================================================
#define FOSSIL_IO_ATTR_BOLD              "\033[1m"
#define FOSSIL_IO_ATTR_DIM               "\033[2m"
#define FOSSIL_IO_ATTR_ITALIC            "\033[3m"
#define FOSSIL_IO_ATTR_UNDERLINE         "\033[4m"
#define FOSSIL_IO_ATTR_BLINK             "\033[5m"
#define FOSSIL_IO_ATTR_REVERSE           "\033[7m"
#define FOSSIL_IO_ATTR_HIDDEN            "\033[8m"
#define FOSSIL_IO_ATTR_STRIKETHROUGH     "\033[9m"
#define FOSSIL_IO_ATTR_NORMAL            "\033[22;23;24;25;27;28m" // Reset all attributes
#define FOSSIL_IO_ATTR_REVERSED          "\033[7m"

// Reset specific attributes
#define FOSSIL_IO_ATTR_RESET_BOLD        "\033[22m"
#define FOSSIL_IO_ATTR_RESET_DIM         "\033[22m"
#define FOSSIL_IO_ATTR_RESET_ITALIC      "\033[23m"
#define FOSSIL_IO_ATTR_RESET_UNDERLINE   "\033[24m"
#define FOSSIL_IO_ATTR_RESET_BLINK       "\033[25m"
#define FOSSIL_IO_ATTR_RESET_REVERSE     "\033[27m"
#define FOSSIL_IO_ATTR_RESET_HIDDEN      "\033[28m"
#define FOSSIL_IO_ATTR_RESET_STRIKE      "\033[29m"

#define FOSSIL_IO_BUFFER_SIZE 1000

/**
 * Apply a background color using pizza_io color names.
 * AI trick: use switch/case on first char for faster dispatch.
 */
void pizza_io_apply_bg_color(const char *bg_color) {
    if (unlikely(!bg_color)) return;
    switch (bg_color[0]) {
        case 'b':
            if (pizza_io_cstr_compare(bg_color, "black") == 0) printf(FOSSIL_IO_BG_BLACK);
            else if (pizza_io_cstr_compare(bg_color, "blue") == 0) printf(FOSSIL_IO_BG_BLUE);
            else if (pizza_io_cstr_compare(bg_color, "bright_black") == 0) printf(FOSSIL_IO_BG_BRIGHT_BLACK);
            else if (pizza_io_cstr_compare(bg_color, "bright_blue") == 0) printf(FOSSIL_IO_BG_BRIGHT_BLUE);
            else if (pizza_io_cstr_compare(bg_color, "brown") == 0) printf(FOSSIL_IO_BG_BROWN);
            else if (pizza_io_cstr_compare(bg_color, "bright_red") == 0) printf(FOSSIL_IO_BG_BRIGHT_RED);
            else if (pizza_io_cstr_compare(bg_color, "bright_green") == 0) printf(FOSSIL_IO_BG_BRIGHT_GREEN);
            else if (pizza_io_cstr_compare(bg_color, "bright_yellow") == 0) printf(FOSSIL_IO_BG_BRIGHT_YELLOW);
            else if (pizza_io_cstr_compare(bg_color, "bright_magenta") == 0) printf(FOSSIL_IO_BG_BRIGHT_MAGENTA);
            else if (pizza_io_cstr_compare(bg_color, "bright_cyan") == 0) printf(FOSSIL_IO_BG_BRIGHT_CYAN);
            else if (pizza_io_cstr_compare(bg_color, "bright_white") == 0) printf(FOSSIL_IO_BG_BRIGHT_WHITE);
            break;
        case 'r':
            if (pizza_io_cstr_compare(bg_color, "red") == 0) printf(FOSSIL_IO_BG_RED);
            else if (pizza_io_cstr_compare(bg_color, "reset") == 0) printf(FOSSIL_IO_COLOR_RESET);
            break;
        case 'g':
            if (pizza_io_cstr_compare(bg_color, "green") == 0) printf(FOSSIL_IO_BG_GREEN);
            else if (pizza_io_cstr_compare(bg_color, "gray") == 0) printf(FOSSIL_IO_BG_GRAY);
            break;
        case 'y':
            if (pizza_io_cstr_compare(bg_color, "yellow") == 0) printf(FOSSIL_IO_BG_YELLOW);
            break;
        case 'm':
            if (pizza_io_cstr_compare(bg_color, "magenta") == 0) printf(FOSSIL_IO_BG_MAGENTA);
            break;
        case 'c':
            if (pizza_io_cstr_compare(bg_color, "cyan") == 0) printf(FOSSIL_IO_BG_CYAN);
            break;
        case 'w':
            if (pizza_io_cstr_compare(bg_color, "white") == 0) printf(FOSSIL_IO_BG_WHITE);
            break;
        case 'o':
            if (pizza_io_cstr_compare(bg_color, "orange") == 0) printf(FOSSIL_IO_BG_ORANGE);
            break;
        case 'p':
            if (pizza_io_cstr_compare(bg_color, "pink") == 0) printf(FOSSIL_IO_BG_PINK);
            else if (pizza_io_cstr_compare(bg_color, "purple") == 0) printf(FOSSIL_IO_BG_PURPLE);
            break;
        case 't':
            if (pizza_io_cstr_compare(bg_color, "teal") == 0) printf(FOSSIL_IO_BG_TEAL);
            break;
        case 's':
            if (pizza_io_cstr_compare(bg_color, "silver") == 0) printf(FOSSIL_IO_BG_SILVER);
            break;
    }
}

/**
 * Apply a foreground color using pizza_io color names.
 * AI trick: use switch/case on first char for faster dispatch.
 */
void pizza_io_apply_color(const char *color) {
    if (unlikely(!color)) return;
    switch (color[0]) {
        case 'b':
            if (pizza_io_cstr_compare(color, "black") == 0) printf(FOSSIL_IO_COLOR_BLACK);
            else if (pizza_io_cstr_compare(color, "blue") == 0) printf(FOSSIL_IO_COLOR_BLUE);
            else if (pizza_io_cstr_compare(color, "bright_black") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_BLACK);
            else if (pizza_io_cstr_compare(color, "bright_blue") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_BLUE);
            else if (pizza_io_cstr_compare(color, "brown") == 0) printf(FOSSIL_IO_COLOR_BROWN);
            else if (pizza_io_cstr_compare(color, "bright_red") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_RED);
            else if (pizza_io_cstr_compare(color, "bright_green") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_GREEN);
            else if (pizza_io_cstr_compare(color, "bright_yellow") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_YELLOW);
            else if (pizza_io_cstr_compare(color, "bright_magenta") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_MAGENTA);
            else if (pizza_io_cstr_compare(color, "bright_cyan") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_CYAN);
            else if (pizza_io_cstr_compare(color, "bright_white") == 0) printf(FOSSIL_IO_COLOR_BRIGHT_WHITE);
            break;
        case 'r':
            if (pizza_io_cstr_compare(color, "red") == 0) printf(FOSSIL_IO_COLOR_RED);
            else if (pizza_io_cstr_compare(color, "reset") == 0) printf(FOSSIL_IO_COLOR_RESET);
            break;
        case 'g':
            if (pizza_io_cstr_compare(color, "green") == 0) printf(FOSSIL_IO_COLOR_GREEN);
            else if (pizza_io_cstr_compare(color, "gray") == 0) printf(FOSSIL_IO_COLOR_GRAY);
            break;
        case 'y':
            if (pizza_io_cstr_compare(color, "yellow") == 0) printf(FOSSIL_IO_COLOR_YELLOW);
            break;
        case 'm':
            if (pizza_io_cstr_compare(color, "magenta") == 0) printf(FOSSIL_IO_COLOR_MAGENTA);
            break;
        case 'c':
            if (pizza_io_cstr_compare(color, "cyan") == 0) printf(FOSSIL_IO_COLOR_CYAN);
            break;
        case 'w':
            if (pizza_io_cstr_compare(color, "white") == 0) printf(FOSSIL_IO_COLOR_WHITE);
            break;
        case 'o':
            if (pizza_io_cstr_compare(color, "orange") == 0) printf(FOSSIL_IO_COLOR_ORANGE);
            break;
        case 'p':
            if (pizza_io_cstr_compare(color, "pink") == 0) printf(FOSSIL_IO_COLOR_PINK);
            else if (pizza_io_cstr_compare(color, "purple") == 0) printf(FOSSIL_IO_COLOR_PURPLE);
            break;
        case 't':
            if (pizza_io_cstr_compare(color, "teal") == 0) printf(FOSSIL_IO_COLOR_TEAL);
            break;
        case 's':
            if (pizza_io_cstr_compare(color, "silver") == 0) printf(FOSSIL_IO_COLOR_SILVER);
            break;
    }
}

/**
 * Apply a text attribute using pizza_io attribute names.
 * AI trick: use switch/case on first char for faster dispatch.
 */
void pizza_io_apply_attribute(const char *attribute) {
    if (unlikely(!attribute)) return;
    switch (attribute[0]) {
        case 'b':
            if (pizza_io_cstr_compare(attribute, "bold") == 0) printf(FOSSIL_IO_ATTR_BOLD);
            else if (pizza_io_cstr_compare(attribute, "blink") == 0) printf(FOSSIL_IO_ATTR_BLINK);
            break;
        case 'd':
            if (pizza_io_cstr_compare(attribute, "dim") == 0) printf(FOSSIL_IO_ATTR_DIM);
            break;
        case 'i':
            if (pizza_io_cstr_compare(attribute, "italic") == 0) printf(FOSSIL_IO_ATTR_ITALIC);
            break;
        case 'u':
            if (pizza_io_cstr_compare(attribute, "underline") == 0) printf(FOSSIL_IO_ATTR_UNDERLINE);
            break;
        case 'r':
            if (pizza_io_cstr_compare(attribute, "reverse") == 0) printf(FOSSIL_IO_ATTR_REVERSE);
            else if (pizza_io_cstr_compare(attribute, "reversed") == 0) printf(FOSSIL_IO_ATTR_REVERSED);
            else if (pizza_io_cstr_compare(attribute, "reset_bold") == 0) printf(FOSSIL_IO_ATTR_RESET_BOLD);
            else if (pizza_io_cstr_compare(attribute, "reset_dim") == 0) printf(FOSSIL_IO_ATTR_RESET_DIM);
            else if (pizza_io_cstr_compare(attribute, "reset_italic") == 0) printf(FOSSIL_IO_ATTR_RESET_ITALIC);
            else if (pizza_io_cstr_compare(attribute, "reset_underline") == 0) printf(FOSSIL_IO_ATTR_RESET_UNDERLINE);
            else if (pizza_io_cstr_compare(attribute, "reset_blink") == 0) printf(FOSSIL_IO_ATTR_RESET_BLINK);
            else if (pizza_io_cstr_compare(attribute, "reset_reverse") == 0) printf(FOSSIL_IO_ATTR_RESET_REVERSE);
            else if (pizza_io_cstr_compare(attribute, "reset_hidden") == 0) printf(FOSSIL_IO_ATTR_RESET_HIDDEN);
            else if (pizza_io_cstr_compare(attribute, "reset_strike") == 0) printf(FOSSIL_IO_ATTR_RESET_STRIKE);
            else if (pizza_io_cstr_compare(attribute, "reset") == 0) printf(FOSSIL_IO_ATTR_NORMAL);
            break;
        case 'h':
            if (pizza_io_cstr_compare(attribute, "hidden") == 0) printf(FOSSIL_IO_ATTR_HIDDEN);
            break;
        case 's':
            if (pizza_io_cstr_compare(attribute, "strikethrough") == 0) printf(FOSSIL_IO_ATTR_STRIKETHROUGH);
            break;
        case 'n':
            if (pizza_io_cstr_compare(attribute, "normal") == 0) printf(FOSSIL_IO_ATTR_NORMAL);
            break;
    }
}

/**
 * Apply a named position (top, bottom, left, right, center, etc).
 * AI trick: use switch/case on first char for faster dispatch.
 */
void pizza_io_apply_position(const char *pos) {
    if (unlikely(!pos)) return;
    switch (pos[0]) {
        case 't':
            if (pizza_io_cstr_compare(pos, "top") == 0) printf("\033[1;1H");
            else if (pizza_io_cstr_compare(pos, "top-left") == 0) printf("\033[1;1H");
            else if (pizza_io_cstr_compare(pos, "top-right") == 0) printf("\033[1;1000H");
            break;
        case 'b':
            if (pizza_io_cstr_compare(pos, "bottom") == 0) printf("\033[1000;1H");
            else if (pizza_io_cstr_compare(pos, "bottom-left") == 0) printf("\033[1000;1H");
            else if (pizza_io_cstr_compare(pos, "bottom-right") == 0) printf("\033[1000;1000H");
            break;
        case 'l':
            if (pizza_io_cstr_compare(pos, "left") == 0) printf("\033[1;1H");
            break;
        case 'r':
            if (pizza_io_cstr_compare(pos, "right") == 0) printf("\033[1;1000H");
            break;
        case 'c':
            if (pizza_io_cstr_compare(pos, "center") == 0) printf("\033[25;40H");
            break;
        case 'm':
            if (pizza_io_cstr_compare(pos, "middle-left") == 0) printf("\033[25;1H");
            else if (pizza_io_cstr_compare(pos, "middle-right") == 0) printf("\033[25;1000H");
            break;
        default:
            fprintf(stderr, "Unknown position: %s\n", pos);
            break;
    }
}

/**
 * Print text with attributes, colors, background colors, positions, and format specifiers.
 * Supports {color}, {color,attribute}, {bg:bg_color}, {bg:bg_color,attribute}, {pos:name}, and combinations.
 * AI trick: use local buffer for attributes, check for nulls, avoid buffer overflow.
 */
void pizza_io_print_with_attributes(const char *str) {
    if (unlikely(str == NULL)) {
        fputs("cnullptr\n", stderr);
        return;
    }

    const char *current_pos = str;
    const char *start = NULL;
    const char *end = NULL;

    while ((start = strchr(current_pos, '{')) != NULL) {
        printf("%.*s", (int)(start - current_pos), current_pos);

        end = strchr(start, '}');
        if (end) {
            size_t length = end - start - 1;
            char attributes[64];
            if (length >= sizeof(attributes)) length = sizeof(attributes) - 1;
            strncpy(attributes, start + 1, length);
            attributes[length] = '\0';

            if (strncmp(attributes, "bg:", 3) == 0) {
                char *bg_color = attributes + 3;
                char *comma_pos = strchr(bg_color, ',');
                if (comma_pos) {
                    *comma_pos = '\0';
                    if (likely(PIZZA_IO_COLOR_ENABLE)) pizza_io_apply_bg_color(bg_color);
                    pizza_io_apply_attribute(comma_pos + 1);
                } else {
                    if (likely(PIZZA_IO_COLOR_ENABLE)) pizza_io_apply_bg_color(bg_color);
                }
            } else if (strncmp(attributes, "pos:", 4) == 0) {
                pizza_io_apply_position(attributes + 4);
            } else {
                char *color = attributes;
                char *attribute = NULL;
                char *comma_pos = strchr(attributes, ',');
                if (comma_pos) {
                    *comma_pos = '\0';
                    color = attributes;
                    attribute = comma_pos + 1;
                }
                if (likely(PIZZA_IO_COLOR_ENABLE) && color && color[0] != '\0') {
                    pizza_io_apply_color(color);
                }
                if (attribute && attribute[0] != '\0') {
                    pizza_io_apply_attribute(attribute);
                }
            }
            current_pos = end + 1;
        } else {
            printf("%s", start);
            break;
        }
    }
    printf("%s", current_pos);
    fflush(stdout);
}

/**
 * Print a sanitized string with attributes inside {}.
 * AI trick: always check for null, use static buffer, avoid overflow.
 */
void pizza_io_puts(ccstr str) {
    if (likely(str != NULL)) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str) - 1);
        sanitized_str[sizeof(sanitized_str) - 1] = '\0';
        pizza_io_print_with_attributes(sanitized_str);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

/**
 * Print a single character.
 */
void pizza_io_putchar(char c) {
    fputc(c, stdout);
}

/**
 * Print sanitized formatted output with attributes.
 * AI trick: use va_copy for safety, static buffer, check for overflow.
 */
void pizza_io_printf(ccstr format, ...) {
    if (unlikely(!format)) return;
    va_list args;
    va_start(args, format);

    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    pizza_io_print_with_attributes(buffer);

    va_end(args);
}

/**
 * Print a sanitized string to a specific pizza_fstream_t stream.
 * AI trick: always check for null, use static buffer, avoid overflow.
 */
void pizza_io_fputs(pizza_fstream_t *stream, ccstr str) {
    if (likely(str != NULL && stream != NULL && stream->file != NULL)) {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str) - 1);
        sanitized_str[sizeof(sanitized_str) - 1] = '\0';
        fputs(sanitized_str, stream->file);
    } else {
        fputs("cnullptr\n", stderr);
    }
}

/**
 * Print a sanitized formatted string to a specific pizza_fstream_t stream.
 * AI trick: use va_copy for safety, static buffer, check for overflow.
 */
void pizza_io_fprintf(pizza_fstream_t *stream, ccstr format, ...) {
    if (unlikely(!format)) return;
    va_list args;
    va_start(args, format);

    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    if (likely(stream != NULL && stream->file != NULL)) {
        fputs(buffer, stream->file);
    } else {
        fputs(buffer, stderr);
    }

    va_end(args);
}

/**
 * Format a string into a buffer.
 * AI trick: use va_copy for safety.
 */
int pizza_io_snprintf(char *buffer, size_t size, ccstr format, ...) {
    if (unlikely(!buffer || !format || size == 0)) return -1;
    va_list args;
    va_start(args, format);
    int result = vsnprintf(buffer, size, format, args);
    va_end(args);
    return result;
}

// TUI PART

void pizza_io_clear_screen(void) {
    printf("\033[2J\033[H");
}

void pizza_io_move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void pizza_io_hide_cursor(void) {
    printf("\033[?25l");
}

void pizza_io_show_cursor(void) {
    printf("\033[?25h");
}

void pizza_io_draw_horizontal_line(int length, char ch) {
    if (unlikely(length <= 0)) return;
    for (int i = 0; i < length; ++i) {
        fputc(ch, stdout);
    }
    fputc('\n', stdout);
}

void pizza_io_draw_vertical_line(int length, char ch) {
    if (unlikely(length <= 0)) return;
    for (int i = 0; i < length; ++i) {
        fputc(ch, stdout);
        fputc('\n', stdout);
    }
}

void pizza_io_flush(void) {
    fflush(stdout);
}

// *****************************************************************************
// string management
// *****************************************************************************

// AI tricks applied:
// - Defensive programming: always check for null, zero, and overflow.
// - Use restrict for memcpy/memmove where possible.
// - Use unlikely/likely macros for error handling (if available).
// - Use static inline for small helpers (if header included).
// - Use branch prediction hints for error paths.
// - Use memset_s if available for secure zeroing (fallback to memset).
// - Use size_t for all lengths and indexes.
// - Avoid double evaluation of arguments.
// - Use strnlen for safety where possible.

cstr pizza_io_cstr_create(const char *init) {
    if (unlikely(!init)) return null;
    size_t length = strlen(init);
    cstr str = (cstr)malloc(length + 1);
    if (likely(str)) {
        memcpy(str, init, length + 1);
    }
    return str;
}

void pizza_io_cstr_free(cstr str) {
    if (likely(str)) {
        free(str);
    }
}

cstr pizza_io_cstr_copy(ccstr str) {
    if (unlikely(!str)) return null;
    return pizza_io_cstr_create(str);
}

cstr pizza_io_cstr_dup(ccstr str) {
    if (unlikely(!str)) return null;
    size_t length = strlen(str);
    cstr new_str = (cstr)malloc(length + 1);
    if (likely(new_str)) {
        memcpy(new_str, str, length + 1);
    }
    return new_str;
}

cstr pizza_io_cstr_concat(ccstr s1, ccstr s2) {
    if (unlikely(!s1 || !s2)) return null;
    size_t length1 = strlen(s1);
    size_t length2 = strlen(s2);
    cstr str = (cstr)malloc(length1 + length2 + 1);
    if (likely(str)) {
        memcpy(str, s1, length1);
        memcpy(str + length1, s2, length2 + 1);
    }
    return str;
}

size_t pizza_io_cstr_length(ccstr str) {
    if (unlikely(!str)) return 0;
    return strlen(str);
}

int pizza_io_cstr_compare(ccstr s1, ccstr s2) {
    if (unlikely(!s1 || !s2)) return -1;
    return strcmp(s1, s2);
}

void pizza_io_cstr_trim(cstr str) {
    if (unlikely(!str)) return;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length ? length - 1 : 0;
    while (start < length && isspace((unsigned char)str[start])) start++;
    while (end > start && isspace((unsigned char)str[end])) end--;
    size_t count = (end >= start) ? (end - start + 1) : 0;
    if (start > 0 && count > 0) {
        memmove(str, str + start, count);
    }
    str[count] = '\0';
}

cstr *pizza_io_cstr_split(ccstr str, char delimiter, size_t *count) {
    if (unlikely(!str || !count)) return null;
    size_t length = strlen(str);
    size_t num_delimiters = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == delimiter) num_delimiters++;
    }
    *count = num_delimiters + 1;
    cstr *result = (cstr*)malloc(*count * sizeof(cstr));
    if (unlikely(!result)) return null;
    size_t start = 0, index = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == delimiter) {
            size_t seglen = i - start;
            result[index] = (cstr)malloc(seglen + 1);
            if (unlikely(!result[index])) {
                for (size_t j = 0; j < index; j++) free(result[j]);
                free(result);
                return null;
            }
            memcpy(result[index], str + start, seglen);
            result[index][seglen] = '\0';
            start = i + 1;
            index++;
        }
    }
    size_t seglen = length - start;
    result[index] = (cstr)malloc(seglen + 1);
    if (unlikely(!result[index])) {
        for (size_t j = 0; j < index; j++) free(result[j]);
        free(result);
        return null;
    }
    memcpy(result[index], str + start, seglen);
    result[index][seglen] = '\0';
    return result;
}

cstr pizza_io_cstr_replace(ccstr str, ccstr old, ccstr new_str) {
    if (unlikely(!str || !old || !new_str)) return null;
    size_t old_length = strlen(old);
    size_t new_length = strlen(new_str);
    if (unlikely(old_length == 0)) return pizza_io_cstr_copy(str);
    size_t count = 0, index = 0, length = strlen(str);
    while (index < length) {
        if (strncmp(str + index, old, old_length) == 0) {
            count++;
            index += old_length;
        } else {
            index++;
        }
    }
    size_t result_len = length + count * (new_length - old_length);
    cstr result = (cstr)malloc(result_len + 1);
    if (unlikely(!result)) return null;
    index = 0;
    size_t out = 0;
    while (index < length) {
        if (strncmp(str + index, old, old_length) == 0) {
            memcpy(result + out, new_str, new_length);
            out += new_length;
            index += old_length;
        } else {
            result[out++] = str[index++];
        }
    }
    result[out] = '\0';
    return result;
}

cstr pizza_io_cstr_to_upper(cstr str) {
    if (unlikely(!str)) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (likely(result)) {
        for (size_t i = 0; i < length; i++) {
            result[i] = toupper((unsigned char)str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_to_lower(cstr str) {
    if (unlikely(!str)) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (likely(result)) {
        for (size_t i = 0; i < length; i++) {
            result[i] = tolower((unsigned char)str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_starts_with(ccstr str, ccstr prefix) {
    if (unlikely(!str || !prefix)) return 0;
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (unlikely(prefix_length > str_length)) return 0;
    return strncmp(str, prefix, prefix_length) == 0;
}

int pizza_io_cstr_ends_with(ccstr str, ccstr suffix) {
    if (unlikely(!str || !suffix)) return 0;
    size_t str_length = strlen(str);
    size_t suffix_length = strlen(suffix);
    if (unlikely(suffix_length > str_length)) return 0;
    return strncmp(str + str_length - suffix_length, suffix, suffix_length) == 0;
}

cstr pizza_io_cstr_substring(ccstr str, size_t start, size_t length) {
    if (unlikely(!str)) return null;
    size_t str_length = strlen(str);
    if (unlikely(start >= str_length)) return null;
    size_t count = str_length - start;
    if (length < count) count = length;
    cstr result = (cstr)malloc(count + 1);
    if (likely(result)) {
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_reverse(cstr str) {
    if (unlikely(!str)) return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (likely(result)) {
        for (size_t i = 0; i < length; i++) {
            result[i] = str[length - i - 1];
        }
        result[length] = '\0';
    }
    return result;
}

int pizza_io_cstr_contains(ccstr str, ccstr substr) {
    if (unlikely(!str || !substr)) return 0;
    return strstr(str, substr) != null;
}

cstr pizza_io_cstr_repeat(ccstr str, size_t count) {
    if (unlikely(!str || count == 0)) return null;
    size_t length = strlen(str);
    if (unlikely(length == 0)) return pizza_io_cstr_create("");
    size_t new_length = length * count;
    cstr result = (cstr)malloc(new_length + 1);
    if (likely(result)) {
        for (size_t i = 0; i < count; i++) {
            memcpy(result + i * length, str, length);
        }
        result[new_length] = '\0';
    }
    return result;
}

cstr pizza_io_cstr_strip(ccstr str, char ch) {
    if (unlikely(!str)) return null;
    size_t length = strlen(str);
    size_t start = 0, end = length ? length - 1 : 0;
    while (start < length && str[start] == ch) start++;
    while (end > start && str[end] == ch) end--;
    size_t count = (end >= start) ? (end - start + 1) : 0;
    cstr result = (cstr)malloc(count + 1);
    if (likely(result)) {
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

size_t pizza_io_cstr_count(ccstr str, ccstr substr) {
    if (unlikely(!str || !substr)) return 0;
    size_t count = 0;
    size_t length = strlen(substr);
    if (unlikely(length == 0)) return 0;
    const char *p = str;
    while ((p = strstr(p, substr)) != null) {
        count++;
        p += length;
    }
    return count;
}

cstr pizza_io_cstr_pad_left(ccstr str, size_t total_length, char pad_char) {
    if (unlikely(!str || total_length == 0)) return null;
    size_t length = strlen(str);
    if (length >= total_length) return pizza_io_cstr_copy(str);
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (likely(result)) {
        memset(result, pad_char, pad_length);
        memcpy(result + pad_length, str, length + 1);
    }
    return result;
}

cstr pizza_io_cstr_pad_right(ccstr str, size_t total_length, char pad_char) {
    if (unlikely(!str || total_length == 0)) return null;
    size_t length = strlen(str);
    if (length >= total_length) return pizza_io_cstr_copy(str);
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (likely(result)) {
        memcpy(result, str, length);
        memset(result + length, pad_char, pad_length);
        result[total_length] = '\0';
    }
    return result;
}

bool pizza_io_cstr_append(cstr dest, size_t max_len, cstr src) {
    if (unlikely(!dest || !src || max_len == 0)) return false;
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L
    size_t dest_len = strnlen(dest, max_len);
#else
    // Fallback for platforms without strnlen
    size_t dest_len = 0;
    while (dest_len < max_len && dest[dest_len] != '\0') dest_len++;
#endif
    if (dest_len == max_len) return false;
    size_t src_len = strlen(src);
    if (dest_len + src_len >= max_len) return false;
    memcpy(dest + dest_len, src, src_len + 1);
    return true;
}
