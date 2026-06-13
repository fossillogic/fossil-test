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
#include "fossil/maip/common.h"
#include <stdio.h>

// *****************************************************************************
// macro definitions
// *****************************************************************************

#define FOSSIL_MAIP_VERSION "2.0.0"
#define FOSSIL_MAIP_AUTHOR "Fossil Logic"
#define FOSSIL_MAIP_WEBSITE "https://fossillogic.com"

// *****************************************************************************
// exported flags
// *****************************************************************************

fossil_maip_cli_theme_t G_MAIP_THEME = MAIP_THEME_FOSSIL;

// *****************************************************************************
// Hashing algorithm
// *****************************************************************************

// HASH Algorithm magic

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
uint64_t get_maip_time_microseconds(void)
{
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    uint64_t t = ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    return t / 10; // 100-nanosecond intervals to microseconds
}
#else
#include <sys/time.h>
uint64_t get_maip_time_microseconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + tv.tv_usec;
}
#endif

static uint64_t get_maip_device_salt(void)
{
    // FNV-1a 64-bit base offset
    uint64_t hash = 0xcbf29ce484222325ULL;

    // Cross-platform user and home detection
#if defined(_WIN32) || defined(_WIN64)
    const char *vars[] = {
        getenv("USERNAME"),
        getenv("USERPROFILE"),
        getenv("COMPUTERNAME")};
#else
    const char *vars[] = {
        getenv("USER"),
        getenv("HOME"),
        getenv("SHELL"),
        getenv("HOSTNAME")};
#endif

    // Mix in each variable if it exists
    for (size_t v = 0; v < sizeof(vars) / sizeof(vars[0]); ++v)
    {
        const char *val = vars[v];
        if (val)
        {
            for (size_t i = 0; val[i]; ++i)
            {
                hash ^= (uint8_t)val[i];
                hash *= 0x100000001b3ULL;
            }
        }
    }

    return hash;
}

void fossil_maip_hash(const char *input, const char *output, uint8_t *hash_out)
{
    const uint64_t PRIME = 0x100000001b3ULL;
    static uint64_t SALT = 0;
    if (SALT == 0)
        SALT = get_maip_device_salt(); // Initialize salt once

    uint64_t state1 = 0xcbf29ce484222325ULL ^ SALT;
    uint64_t state2 = 0x84222325cbf29ce4ULL ^ ~SALT;

    size_t in_len = strlen(input);
    size_t out_len = strlen(output);

    uint64_t nonce = get_maip_time_microseconds(); // Microsecond resolution

    for (size_t i = 0; i < in_len; ++i)
    {
        state1 ^= (uint8_t)input[i];
        state1 *= PRIME;
        state1 ^= (state1 >> 27);
        state1 ^= (state1 << 33);
    }

    for (size_t i = 0; i < out_len; ++i)
    {
        state2 ^= (uint8_t)output[i];
        state2 *= PRIME;
        state2 ^= (state2 >> 29);
        state2 ^= (state2 << 31);
    }

    // Nonce and length entropy
    state1 ^= nonce ^ ((uint64_t)in_len << 32);
    state2 ^= ~nonce ^ ((uint64_t)out_len << 16);

    // Mixing rounds
    for (int i = 0; i < 6; ++i)
    {
        state1 += (state2 ^ (state1 >> 17));
        state2 += (state1 ^ (state2 >> 13));
        state1 ^= (state1 << 41);
        state2 ^= (state2 << 37);
        state1 *= PRIME;
        state2 *= PRIME;
    }

    for (size_t i = 0; i < FOSSIL_MAIP_HASH_SIZE; ++i)
    {
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

typedef struct
{
    int argc;
    char **argv;

    const char *command; // run/filter/sort/etc
    int command_index;

    // global flags
    int show_version;
    int show_help;
    int show_info;

    const char *color_mode;
    const char *theme;
    int timeout;
} fossil_maip_scan_t;

typedef struct
{
    const char *name;
    const char *value;
} maip_kv_t;

typedef struct
{
    maip_kv_t *items;
    size_t count;
} maip_arg_list_t;

typedef struct
{
    const char *name;
    maip_arg_list_t args;
} fossil_maip_command_t;

static void _show_help(void)
{
    maip_io_printf("{blue}Usage: maip [options] [command]{reset}\n");
    maip_io_printf("{blue}Options:{reset}\n");
    maip_io_printf("{cyan}  --version -v       {white}Show version information{reset}\n");
    maip_io_printf("{cyan}  --help    -h       {white}Show this help message{reset}\n");
    maip_io_printf("{blue}Commands:{reset}\n");
    maip_io_printf("{cyan}  run                {white}Execute tests with optional parameters{reset}\n");
    maip_io_printf("{cyan}  filter             {white}Filter tests based on criteria{reset}\n");
    maip_io_printf("{cyan}  sort               {white}Sort tests by specified criteria{reset}\n");
    maip_io_printf("{cyan}  shuffle            {white}Shuffle tests with optional parameters{reset}\n");
    maip_io_printf("{cyan}  show               {white}Show test cases with optional parameters{reset}\n");
    maip_io_printf("{cyan}  color <mode>       {white}Set color mode (enable, disable, auto){reset}\n");
    maip_io_printf("{cyan}  theme <name>       {white}Set the theme (fossil, catch, doctest, etc.){reset}\n");
    maip_io_printf("{cyan}  info               {white}Show detailed information about the environment{reset}\n");
    maip_io_printf("{cyan}  timeout=<seconds>  {white}Set the timeout for commands (default: 60 seconds){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_info(void)
{
    maip_io_printf("{blue}Info command options:{reset}\n");
    maip_io_printf("{cyan}  --os               {white}Filter by operating system{reset}\n");
    maip_io_printf("{cyan}  --arch             {white}Filter by architecture{reset}\n");
    maip_io_printf("{cyan}  --memory            {white}Show memory information{reset}\n");
    maip_io_printf("{cyan}  --endian            {white}Show endianness information{reset}\n");
    maip_io_printf("{cyan}  --self              {white}Show information about the test runner itself{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_run(void)
{
    maip_io_printf("{blue}Run command options:{reset}\n");
    maip_io_printf("{cyan}  --fail-fast        {white}Stop on the first failure{reset}\n");
    maip_io_printf("{cyan}  --only <test>      {white}Run only the specified test{reset}\n");
    maip_io_printf("{cyan}  --skip <test>      {white}Skip the specified test{reset}\n");
    maip_io_printf("{cyan}  --repeat <count>   {white}Repeat the test a specified number of times{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_filter(void)
{
    maip_io_printf("{blue}Filter command options:{reset}\n");
    maip_io_printf("{cyan}  --test-name <name> {white}Filter by test name{reset}\n");
    maip_io_printf("{cyan}  --suite-name <name> {white}Filter by suite name{reset}\n");
    maip_io_printf("{cyan}  --tag <tag>        {white}Filter by tag{reset}\n");
    maip_io_printf("{cyan}  --help             {white}Show help for filter command{reset}\n");
    maip_io_printf("{cyan}  --options          {white}Show all valid tags{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_report(void)
{
    maip_io_printf("{blue}Report command options:{reset}\n");
    maip_io_printf("{cyan}  --format <json/fson/yaml/csv>       {white}Set the output format{reset}\n");
    maip_io_printf("{cyan}  --destination <file/stdout>        {white}Set the output destination (default: stdout){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_sort(void)
{
    maip_io_printf("{blue}Sort command options:{reset}\n");
    maip_io_printf("{cyan}  --by <criteria>    {white}Sort by specified criteria{reset}\n");
    maip_io_printf("{cyan}  --order <asc|desc> {white}Sort in ascending or descending order{reset}\n");
    maip_io_printf("{cyan}  --help             {white}Show help for sort command{reset}\n");
    maip_io_printf("{cyan}  --options          {white}Show all valid criteria{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_shuffle(void)
{
    maip_io_printf("{blue}Shuffle command options:{reset}\n");
    maip_io_printf("{cyan}  --seed <seed>      {white}Specify the seed for shuffling{reset}\n");
    maip_io_printf("{cyan}  --count <count>    {white}Number of items to shuffle{reset}\n");
    maip_io_printf("{cyan}  --by <criteria>    {white}Shuffle by specified criteria{reset}\n");
    maip_io_printf("{cyan}  --help             {white}Show help for shuffle command{reset}\n");
    maip_io_printf("{cyan}  --options          {white}Show all valid criteria for shuffling{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_color(void)
{
    maip_io_printf("{blue}Color command options:{reset}\n");
    maip_io_printf("{cyan}  enable            {white}Enable color output{reset}\n");
    maip_io_printf("{cyan}  disable           {white}Disable color output{reset}\n");
    maip_io_printf("{cyan}  auto              {white}Auto-detect color support{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_theme(void)
{
    maip_io_printf("{blue}Theme command options:{reset}\n");
    maip_io_printf("{cyan}  fossil            {white}Fossil theme{reset}\n");
    maip_io_printf("{cyan}  light             {white}Light theme{reset}\n");
    maip_io_printf("{cyan}  dark              {white}Dark theme{reset}\n");
    maip_io_printf("{cyan}  maga              {white}MAGA theme{reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_subhelp_show(void)
{
    maip_io_printf("{blue}Show command options:{reset}\n");
    maip_io_printf("{cyan}  --test-name <name>   {white}Filter by test name{reset}\n");
    maip_io_printf("{cyan}  --suite-name <name>  {white}Filter by suite name{reset}\n");
    maip_io_printf("{cyan}  --tag <tag>          {white}Filter by tag{reset}\n");
    maip_io_printf("{cyan}  --result <result>    {white}Filter by result (pass, fail, timeout, skipped, unexpected){reset}\n");
    maip_io_printf("{cyan}  --verbose <level>    {white}Set verbosity level (plain, ci, doge){reset}\n");
    maip_io_printf("{cyan}  --mode <mode>        {white}Show mode (list, tree, graph){reset}\n");
    exit(EXIT_SUCCESS);
}

static void _show_info(fossil_maip_pallet_t *pallet)
{

    if (pallet->info.self)
    {
        maip_io_printf("{blue}Fossil Test Runner Information:{reset}\n");
        maip_io_printf("{cyan}  Version: {green}%s{reset}\n", FOSSIL_MAIP_VERSION);
        maip_io_printf("{cyan}  Author: {green}%s{reset}\n", FOSSIL_MAIP_AUTHOR);
        maip_io_printf("{cyan}  Website: {green}%s{reset}\n", FOSSIL_MAIP_WEBSITE);
        return;
    }

    if (pallet->info.os)
    {
        maip_sys_hostinfo_system_t system_info;
        if (maip_sys_hostinfo_get_system(&system_info) == 0)
        {
            maip_io_printf("{blue}Operating System: {cyan}%s{reset}\n", system_info.os_name);
            maip_io_printf("{blue}OS Version: {cyan}%s{reset}\n", system_info.os_version);
            maip_io_printf("{blue}Kernel Version: {cyan}%s{reset}\n", system_info.kernel_version);
            maip_io_printf("{blue}Hostname: {cyan}%s{reset}\n", system_info.hostname);
            maip_io_printf("{blue}Username: {cyan}%s{reset}\n", system_info.username);
            maip_io_printf("{blue}Domain Name: {cyan}%s{reset}\n", system_info.domain_name);
            maip_io_printf("{blue}Machine Type: {cyan}%s{reset}\n", system_info.machine_type);
            maip_io_printf("{blue}Platform: {cyan}%s{reset}\n", system_info.platform);
        }
        else
        {
            maip_io_printf("{red}Error retrieving system information.{reset}\n");
        }
    }

    if (pallet->info.arch)
    {
        maip_sys_hostinfo_architecture_t arch_info;
        if (maip_sys_hostinfo_get_architecture(&arch_info) == 0)
        {
            maip_io_printf("{blue}Architecture: {cyan}%s{reset}\n", arch_info.architecture);
            maip_io_printf("{blue}CPU: {cyan}%s{reset}\n", arch_info.cpu);
            maip_io_printf("{blue}CPU Cores: {cyan}%s{reset}\n", arch_info.cpu_cores);
            maip_io_printf("{blue}CPU Threads: {cyan}%s{reset}\n", arch_info.cpu_threads);
            maip_io_printf("{blue}CPU Frequency: {cyan}%s{reset}\n", arch_info.cpu_frequency);
            maip_io_printf("{blue}CPU Architecture: {cyan}%s{reset}\n", arch_info.cpu_architecture);
        }
        else
        {
            maip_io_printf("{red}Error retrieving architecture information.{reset}\n");
        }
    }

    if (pallet->info.memory)
    {
        maip_sys_hostinfo_memory_t memory_info;
        if (maip_sys_hostinfo_get_memory(&memory_info) == 0)
        {
            maip_io_printf("{blue}Total Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.total_memory);
            maip_io_printf("{blue}Free Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.free_memory);
            maip_io_printf("{blue}Used Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.used_memory);
            maip_io_printf("{blue}Available Memory: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.available_memory);
            maip_io_printf("{blue}Total Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.total_swap);
            maip_io_printf("{blue}Free Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.free_swap);
            maip_io_printf("{blue}Used Swap: {cyan}%llu bytes{reset}\n", (unsigned long long)memory_info.used_swap);
        }
        else
        {
            maip_io_printf("{red}Error retrieving memory information .{reset}\n");
        }
    }

    if (pallet->info.endian)
    {
        maip_sys_hostinfo_endianness_t endianness_info;
        if (maip_sys_hostinfo_get_endianness(&endianness_info) == 0)
        {
            maip_io_printf("{blue}Endianness: {cyan}%s{reset}\n",
                           endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
        }
        else
        {
            maip_io_printf("{red}Error retrieving endianness information.{reset}\n");
        }
    }
    exit(EXIT_SUCCESS);
}

static void _show_version(void)
{
    maip_io_printf("{blue}Fossil Test Version: {cyan}%s{reset}\n", FOSSIL_MAIP_VERSION);
    exit(EXIT_SUCCESS);
}

typedef enum
{
    MAIP_CMD_NONE,
    MAIP_CMD_RUN,
    MAIP_CMD_FILTER,
    MAIP_CMD_SORT,
    MAIP_CMD_SHUFFLE,
    MAIP_CMD_SHOW,
    MAIP_CMD_REPORT,
    MAIP_CMD_HELP,
    MAIP_CMD_COLOR,
    MAIP_CMD_THEME,
    MAIP_CMD_INFO
} fossil_maip_cmd_t;

typedef struct
{
    fossil_maip_cmd_t cmd;
    const char *name;
} fossil_cmd_map_t;

static fossil_cmd_map_t CMD_MAP[] = {
    {MAIP_CMD_RUN, "run"},
    {MAIP_CMD_FILTER, "filter"},
    {MAIP_CMD_SORT, "sort"},
    {MAIP_CMD_SHUFFLE, "shuffle"},
    {MAIP_CMD_SHOW, "show"},
    {MAIP_CMD_REPORT, "report"},
    {MAIP_CMD_HELP, "help"},
    {MAIP_CMD_COLOR, "color"},
    {MAIP_CMD_THEME, "theme"},
    {MAIP_CMD_INFO, "info"},
    {MAIP_CMD_NONE, NULL}};

static int fossil_maip_parse_run(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for run command
    p->run.only_cases = null;
    p->run.only_count = 0;
    p->run.repeat = 1;
    p->run.fail_fast = 0;

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--fail-fast") == 0)
        {
            p->run.fail_fast = 1;
        }
        else if (maip_io_cstr_compare(arg, "--repeat") == 0 && j + 1 < argc)
        {
            p->run.repeat = atoi(argv[++j]);
        }
        else if (maip_io_cstr_compare(arg, "--only") == 0 && j + 1 < argc)
        {
            j++;
            size_t count = 0;
            p->run.only_cases = maip_io_cstr_split(argv[j], ',', &count);
            p->run.only_count = count;
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_run();
        }
    }

    return argc;
}

static int fossil_maip_parse_filter(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for filter command
    p->filter.test_name = null;
    p->filter.suite_name = null;
    p->filter.tag = "fossil"; // default tag

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--test-name") == 0 && j + 1 < argc)
        {
            p->filter.test_name = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--suite-name") == 0 && j + 1 < argc)
        {
            p->filter.suite_name = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--tag") == 0 && j + 1 < argc)
        {
            p->filter.tag = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_filter();
        }
    }

    return argc;
}

static int fossil_maip_parse_sort(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for sort command
    p->sort.by = "name";
    p->sort.order = "asc";

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--by") == 0 && j + 1 < argc)
        {
            p->sort.by = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--order") == 0 && j + 1 < argc)
        {
            p->sort.order = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_sort();
        }
    }

    return argc;
}

static int fossil_maip_parse_shuffle(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for shuffle command
    p->shuffle.seed = 0;    // default seed (0 means use time/device entropy)
    p->shuffle.count = 0;   // default to shuffle all items
    p->shuffle.by = "name"; // default shuffle criteria

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--seed") == 0 && j + 1 < argc)
        {
            p->shuffle.seed = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--count") == 0 && j + 1 < argc)
        {
            p->shuffle.count = atoi(argv[++j]);
        }
        else if (maip_io_cstr_compare(arg, "--by") == 0 && j + 1 < argc)
        {
            p->shuffle.by = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_shuffle();
        }
    }

    return argc;
}

static int fossil_maip_parse_show(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for show command
    p->show.enabled = 1;
    p->show.verbose = "plain";
    p->show.mode = "list";
    p->show.result = "all";
    p->show.test_name = null;
    p->show.suite_name = null;
    p->show.tag = null;

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--test-name") == 0 && j + 1 < argc)
        {
            p->show.test_name = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--suite-name") == 0 && j + 1 < argc)
        {
            p->show.suite_name = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--tag") == 0 && j + 1 < argc)
        {
            p->show.tag = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--result") == 0 && j + 1 < argc)
        {
            p->show.result = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--verbose") == 0 && j + 1 < argc)
        {
            p->show.verbose = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--mode") == 0 && j + 1 < argc)
        {
            p->show.mode = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_show();
        }
    }

    return argc;
}

static int fossil_maip_parse_report(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--format") == 0 && j + 1 < argc)
        {
            p->report.format = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--destination") == 0 && j + 1 < argc)
        {
            p->report.destination = argv[++j];
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_report();
        }
    }

    return argc;
}

static int fossil_maip_parse_help(int argc, char **argv, int i)
{
    if (i + 1 < argc)
    {
        const char *subcmd = argv[i + 1];
        if (maip_io_cstr_compare(subcmd, "run") == 0)
        {
            _show_subhelp_run();
        }
        else if (maip_io_cstr_compare(subcmd, "filter") == 0)
        {
            _show_subhelp_filter();
        }
        else if (maip_io_cstr_compare(subcmd, "sort") == 0)
        {
            _show_subhelp_sort();
        }
        else if (maip_io_cstr_compare(subcmd, "shuffle") == 0)
        {
            _show_subhelp_shuffle();
        }
        else if (maip_io_cstr_compare(subcmd, "show") == 0)
        {
            _show_subhelp_show();
        }
        else if (maip_io_cstr_compare(subcmd, "report") == 0)
        {
            _show_subhelp_report();
        }
        else if (maip_io_cstr_compare(subcmd, "color") == 0)
        {
            _show_subhelp_color();
        }
        else if (maip_io_cstr_compare(subcmd, "theme") == 0)
        {
            _show_subhelp_theme();
        }
        else if (maip_io_cstr_compare(subcmd, "info") == 0)
        {
            _show_subhelp_info();
        }
    }
    else
    {
        _show_help();
    }
    return argc; // This will never be reached
}

static int fossil_maip_parse_color(int argc, char **argv, int i)
{
    if (i + 1 < argc)
    {
        const char *mode = argv[i + 1];
        if (maip_io_cstr_compare(mode, "enable") == 0)
        {
            MAIP_IO_COLOR_ENABLE = 1;
        }
        else if (maip_io_cstr_compare(mode, "disable") == 0)
        {
            MAIP_IO_COLOR_ENABLE = 0;
        }
        else if (maip_io_cstr_compare(mode, "auto") == 0)
        {
            if (isatty(fileno(stdout)))
            {
                MAIP_IO_COLOR_ENABLE = 1;
            }
            else
            {
                MAIP_IO_COLOR_ENABLE = 0;
            }
        }
        else
        {
            maip_io_printf("{red}Invalid color mode: %s{reset}\n", mode);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        maip_io_printf("{red}Color command requires a mode argument (enable, disable, auto){reset}\n");
        exit(EXIT_FAILURE);
    }
    return i + 1; // Skip the mode argument
}

static int fossil_maip_parse_theme(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    if (i + 1 < argc)
    {
        const char *theme = argv[i + 1];
        if (maip_io_cstr_compare(theme, "fossil") == 0)
        {
            G_MAIP_THEME = MAIP_THEME_FOSSIL;
            p->theme = MAIP_THEME_FOSSIL;
        }
        else if (maip_io_cstr_compare(theme, "light") == 0)
        {
            G_MAIP_THEME = MAIP_THEME_LIGHT;
            p->theme = MAIP_THEME_LIGHT;
        }
        else if (maip_io_cstr_compare(theme, "dark") == 0)
        {
            G_MAIP_THEME = MAIP_THEME_DARK;
            p->theme = MAIP_THEME_DARK;
        }
        else if (maip_io_cstr_compare(theme, "maga") == 0)
        {
            G_MAIP_THEME = MAIP_THEME_MAGA;
            p->theme = MAIP_THEME_MAGA;
        }
        else if (maip_io_cstr_compare(theme, "mint") == 0)
        {
            G_MAIP_THEME = MAIP_THEME_MINT;
            p->theme = MAIP_THEME_MINT;
        }
        else
        {
            maip_io_printf("{red}Invalid theme: %s{reset}\n", theme);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        maip_io_printf("{red}Theme command requires a theme argument (fossil, light, dark, maga){reset}\n");
        exit(EXIT_FAILURE);
    }
    return i + 1; // Skip the theme argument
}

static int fossil_maip_parse_info(fossil_maip_pallet_t *p, int argc, char **argv, int i)
{
    // set defaults for info command
    p->info.os = 0;
    p->info.arch = 0;
    p->info.memory = 0;
    p->info.endian = 0;
    p->info.self = 0;

    for (int j = i + 1; j < argc; j++)
    {
        const char *arg = argv[j];

        if (arg[0] != '-')
        {
            return j - 1; // stop when next command starts
        }

        if (maip_io_cstr_compare(arg, "--os") == 0)
        {
            p->info.os = 1;
        }
        else if (maip_io_cstr_compare(arg, "--arch") == 0)
        {
            p->info.arch = 1;
        }
        else if (maip_io_cstr_compare(arg, "--memory") == 0)
        {
            p->info.memory = 1;
        }
        else if (maip_io_cstr_compare(arg, "--endian") == 0)
        {
            p->info.endian = 1;
        }
        else if (maip_io_cstr_compare(arg, "--self") == 0)
        {
            p->info.self = 1;
        }
        else if (maip_io_cstr_compare(arg, "--help") == 0)
        {
            _show_subhelp_info();
        }
    }

    return argc;
}

static int levenshtein_distance(const char *s1, const char *s2)
{
    size_t len1 = 0, len2 = 0;
    while (s1[len1]) len1++;
    while (s2[len2]) len2++;

    if (len1 == 0) return len2;
    if (len2 == 0) return len1;

    int *d0 = malloc((len2 + 1) * sizeof(int));
    int *d1 = malloc((len2 + 1) * sizeof(int));

    for (size_t i = 0; i <= len2; i++)
        d0[i] = i;

    for (size_t i = 1; i <= len1; i++)
    {
        d1[0] = i;
        for (size_t j = 1; j <= len2; j++)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            int m_v = d1[j - 1] + 1;
            if (d0[j] + 1 < m_v) m_v = d0[j] + 1;
            if (d0[j - 1] + cost < m_v) m_v = d0[j - 1] + cost;
            d1[j] = m_v;
        }
        int *tmp = d0;
        d0 = d1;
        d1 = tmp;
    }

    int result = d0[len2];
    free(d0);
    free(d1);
    return result;
}

static const char* find_best_match(const char *input, const char **candidates, size_t count, int max_distance)
{
    int best_distance = max_distance + 1;
    const char *best_match = NULL;

    for (size_t i = 0; i < count; i++)
    {
        int dist = levenshtein_distance(input, candidates[i]);
        if (dist < best_distance)
        {
            best_distance = dist;
            best_match = candidates[i];
        }
    }
    return best_match;
}

static fossil_maip_cmd_t fossil_maip_resolve_cmd(const char *name)
{
    for (size_t i = 0; CMD_MAP[i].name != NULL; i++)
    {
        if (maip_io_cstr_compare(name, CMD_MAP[i].name) == 0)
        {
            return CMD_MAP[i].cmd;
        }
    }
    return MAIP_CMD_NONE;
}

fossil_maip_pallet_t fossil_maip_pallet_create(int argc, char **argv)
{
    fossil_maip_pallet_t pallet = {0};

    for (int i = 1; i < argc; i++)
    {
        const char *arg = argv[i];

        // global flags first
        if (maip_io_cstr_compare(arg, "--version") == 0 || maip_io_cstr_compare(arg, "-v") == 0)
        {
            _show_version();
            continue;
        }

        if (maip_io_cstr_compare(arg, "--help") == 0 || maip_io_cstr_compare(arg, "-h") == 0)
        {
            _show_help();
            continue;
        }

        if (arg[0] == '-')
        {
            /* Unknown global flag: report and exit */
            maip_io_printf("{red}Unknown flag: %s{reset}\n", arg);
            exit(EXIT_FAILURE);
        }

        fossil_maip_cmd_t cmd = fossil_maip_resolve_cmd(arg);

        switch (cmd)
        {
        case MAIP_CMD_RUN:
            i = fossil_maip_parse_run(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_FILTER:
            i = fossil_maip_parse_filter(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_SORT:
            i = fossil_maip_parse_sort(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_SHUFFLE:
            i = fossil_maip_parse_shuffle(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_SHOW:
            i = fossil_maip_parse_show(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_REPORT:
            i = fossil_maip_parse_report(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_HELP:
            i = fossil_maip_parse_help(argc, argv, i);
            break;

        case MAIP_CMD_COLOR:
            i = fossil_maip_parse_color(argc, argv, i);
            break;

        case MAIP_CMD_THEME:
            i = fossil_maip_parse_theme(&pallet, argc, argv, i);
            break;

        case MAIP_CMD_INFO:
            i = fossil_maip_parse_info(&pallet, argc, argv, i);
            _show_info(&pallet);
            break;

        default:
        {
            /* Try to detect possible intended command using fuzzy matching */
            size_t cmd_count = 0;
            for (size_t j = 0; CMD_MAP[j].name != NULL; j++)
            {
                cmd_count++;
            }
            
            const char **cmd_names = (const char **)malloc(cmd_count * sizeof(const char *));
            if (cmd_names)
            {
                for (size_t j = 0; j < cmd_count; j++)
                {
                    cmd_names[j] = CMD_MAP[j].name;
                }
                
                const char *suggest = find_best_match(arg, cmd_names, cmd_count, 2);
                
                if (suggest)
                {
                    maip_io_printf("{red}Unknown command: %s{reset}\n{red}Did you mean:{reset} '%s'{red}?{reset}\n", arg, suggest);
                }
                else
                {
                    maip_io_printf("{red}Unknown command: %s{reset}\n", arg);
                }
                
                free(cmd_names);
            }
            else
            {
                maip_io_printf("{red}Unknown command: %s{reset}\n", arg);
            }
            exit(EXIT_FAILURE);
        }
        }
    }

    return pallet;
}

// *****************************************************************************
// Host information
// *****************************************************************************

int maip_sys_hostinfo_get_system(maip_sys_hostinfo_system_t *info)
{
    if (!info)
        return -1;
#ifdef _WIN32
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osvi))
        return -1;
    snprintf(info->os_name, sizeof(info->os_name), "Windows");
    snprintf(info->os_version, sizeof(info->os_version), "%lu.%lu", osvi.dwMajorVersion, osvi.dwMinorVersion);
    snprintf(info->kernel_version, sizeof(info->kernel_version), "%lu", osvi.dwBuildNumber);

    DWORD size = sizeof(info->hostname);
    GetComputerNameA(info->hostname, &size);

    size = sizeof(info->username);
    GetUserNameA(info->username, &size);

    // Domain name
    size = sizeof(info->domain_name);
    if (!GetEnvironmentVariableA("USERDOMAIN", info->domain_name, size))
    {
        strncpy(info->domain_name, "Unknown", sizeof(info->domain_name) - 1);
        info->domain_name[sizeof(info->domain_name) - 1] = '\0';
    }

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    snprintf(info->machine_type, sizeof(info->machine_type), "%u", sysinfo.wProcessorArchitecture);
    snprintf(info->platform, sizeof(info->platform), "Win32");

#elif defined(__APPLE__)
    struct utsname sysinfo;
    if (uname(&sysinfo) != 0)
        return -1;
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
    if (uname(&sysinfo) != 0)
        return -1;
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

int maip_sys_hostinfo_get_architecture(maip_sys_hostinfo_architecture_t *info)
{
    if (!info)
        return -1;

#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    // Architecture
    switch (sysinfo.wProcessorArchitecture)
    {
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
    if (uname(&sysinfo) != 0)
        return -1;

    strncpy(info->architecture, sysinfo.machine, sizeof(info->architecture) - 1);
    info->architecture[sizeof(info->architecture) - 1] = '\0';

    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp)
    {
        char line[256];
        while (fgets(line, sizeof(line), fp))
        {
            if (strncmp(line, "model name", 10) == 0)
            {
                char *colon = strchr(line, ':');
                if (colon)
                {
                    colon++;
                    while (*colon == ' ')
                        colon++;
                    strncpy(info->cpu, colon, sizeof(info->cpu) - 1);
                    info->cpu[sizeof(info->cpu) - 1] = '\0';
                }
            }
            else if (strncmp(line, "cpu cores", 9) == 0)
            {
                char *colon = strchr(line, ':');
                if (colon)
                {
                    colon++;
                    while (*colon == ' ')
                        colon++;
                    strncpy(info->cpu_cores, colon, sizeof(info->cpu_cores) - 1);
                    info->cpu_cores[sizeof(info->cpu_cores) - 1] = '\0';
                }
            }
            else if (strncmp(line, "siblings", 8) == 0)
            {
                char *colon = strchr(line, ':');
                if (colon)
                {
                    colon++;
                    while (*colon == ' ')
                        colon++;
                    strncpy(info->cpu_threads, colon, sizeof(info->cpu_threads) - 1);
                    info->cpu_threads[sizeof(info->cpu_threads) - 1] = '\0';
                }
            }
            else if (strncmp(line, "cpu MHz", 7) == 0)
            {
                char *colon = strchr(line, ':');
                if (colon)
                {
                    colon++;
                    while (*colon == ' ')
                        colon++;
                    strncpy(info->cpu_frequency, colon, sizeof(info->cpu_frequency) - 1);
                    info->cpu_frequency[sizeof(info->cpu_frequency) - 1] = '\0';
                }
            }
        }
        fclose(fp);
    }
    else
    {
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

int maip_sys_hostinfo_get_memory(maip_sys_hostinfo_memory_t *info)
{
    if (!info)
        return -1;
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (!GlobalMemoryStatusEx(&statex))
        return -1;
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
    if (sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0)
        return -1;
    info->total_memory = memsize;
    info->free_memory = 0; // macOS does not provide free memory info in the same way
    info->used_memory = 0;
    info->available_memory = 0;
    info->total_swap = 0;
    info->free_swap = 0;
    info->used_swap = 0;
#else
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) != 0)
        return -1;
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

int maip_sys_hostinfo_get_endianness(maip_sys_hostinfo_endianness_t *info)
{
    if (!info)
        return -1;
    uint16_t test = 0x0001;
    info->is_little_endian = (*(uint8_t *)&test) ? 1 : 0;
    return 0;
}

// *****************************************************************************
// soap sanitizer
// *****************************************************************************

#define MAX_CUSTOM_FILTERS 64

/** Lookup table for rot-brain words and their suggested replacements */
static const struct
{
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
static const struct
{
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
static const char *SARCASTIcpp_PHRASES[] = {
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
static void maip_io_soap_normalize_leetspeak(char *word)
{
    for (size_t i = 0; word[i] != '\0'; i++)
    {
        switch (word[i])
        {
        case '0':
            word[i] = 'o';
            break;
        case '1':
            word[i] = 'i';
            break;
        case '3':
            word[i] = 'e';
            break;
        case '4':
            word[i] = 'a';
            break;
        case '5':
            word[i] = 's';
            break;
        case '7':
            word[i] = 't';
            break;
        case '$':
            word[i] = 's';
            break;
        }
    }
}

/**
 * @brief Fuzzy matching using Levenshtein distance.
 * Optimized for short words, early exit if distance > 2.
 */
static int fuzzy_match(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 == 0 || len2 == 0)
        return (int)(len1 + len2);
    if (abs((int)len1 - (int)len2) > 2)
        return 3; // AI trick: early exit for big length diff

    int prev[65], curr[65];
    if (len2 > 64)
        return 3; // AI trick: limit for stack buffer

    for (size_t j = 0; j <= len2; j++)
        prev[j] = (int)j;
    for (size_t i = 1; i <= len1; i++)
    {
        curr[0] = (int)i;
        int min_row = curr[0];
        for (size_t j = 1; j <= len2; j++)
        {
            int cost = (tolower((unsigned char)str1[i - 1]) == tolower((unsigned char)str2[j - 1])) ? 0 : 1;
            curr[j] = fmin(fmin(prev[j] + 1, curr[j - 1] + 1), prev[j - 1] + cost);
            if (curr[j] < min_row)
                min_row = curr[j];
        }
        if (min_row > 2)
            return 3; // AI trick: early exit if row min > 2
        memcpy(prev, curr, (len2 + 1) * sizeof(int));
    }
    return curr[len2];
}

/**
 * @brief Check if a word should be skipped.
 */
static int should_skip_word(const char *word)
{
    for (size_t i = 0; SKIP_WORDS[i] != null; i++)
    {
        if (maip_io_cstr_compare(word, SKIP_WORDS[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Case-insensitive string comparison.
 */
static int custom_strcasecmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
        {
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
static const char *custom_strcasestr(const char *haystack, const char *needle)
{
    if (!*needle)
        return haystack;

    for (; *haystack; haystack++)
    {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle))
        {
            const char *h = haystack, *n = needle;
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n))
            {
                h++;
                n++;
            }
            if (!*n)
                return haystack;
        }
    }
    return null;
}

/**
 * @brief Look up a suggested alternative for a given word, checking both custom filters and predefined suggestions.
 * AI trick: fuzzy match with threshold, prefer exact, then fuzzy, then grammar.
 */
static const char *maip_io_soap_get_suggestion(const char *word)
{
    if (should_skip_word(word))
    {
        return null;
    }

    // Check in custom filters first
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS && custom_filters[i] != null; i++)
    {
        if (custom_strcasecmp(word, custom_filters[i]) == 0)
        {
            return custom_filters[i]; // Use the custom filter word itself as suggestion
        }
        if (fuzzy_match(word, custom_filters[i]) <= 2)
        {
            return custom_filters[i]; // Return fuzzy match result
        }
    }

    // Check in predefined suggestions
    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != null; i++)
    {
        if (custom_strcasecmp(word, FOSSIL_SOAP_SUGGESTIONS[i].bad) == 0)
        {
            return FOSSIL_SOAP_SUGGESTIONS[i].suggested;
        }
        // AI trick: fuzzy match for slang, but only if word is at least 4 chars
        if (strlen(word) >= 4 && fuzzy_match(word, FOSSIL_SOAP_SUGGESTIONS[i].bad) == 1)
        {
            return FOSSIL_SOAP_SUGGESTIONS[i].suggested;
        }
    }

    // Check in grammar suggestions
    for (size_t i = 0; FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect != null; i++)
    {
        if (custom_strcasecmp(word, FOSSIL_SOAP_GRAMMAR_SUGGESTIONS[i].incorrect) == 0)
        {
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
char *maip_io_soap_sanitize(const char *text)
{
    if (!text)
        return null;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 1); // Allocate more space to handle replacements
    if (!output)
        return null;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-')
        {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1)
                word_idx = sizeof(word) - 2;
        }
        else
        {
            word[word_idx] = '\0';
            if (word_idx > 0)
            {
                maip_io_soap_normalize_leetspeak(word);
                const char *suggested = maip_io_soap_get_suggestion(word);
                if (suggested && !should_skip_word(word))
                {
                    for (size_t j = 0; j < strlen(suggested); j++)
                    {
                        output[out_idx++] = suggested[j];
                    }
                }
                else
                {
                    for (size_t j = 0; j < word_idx; j++)
                    {
                        output[out_idx++] = word[j];
                    }
                }
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    if (word_idx > 0)
    {
        maip_io_soap_normalize_leetspeak(word);
        const char *suggested = maip_io_soap_get_suggestion(word);
        if (suggested && !should_skip_word(word))
        {
            for (size_t j = 0; j < strlen(suggested); j++)
            {
                output[out_idx++] = suggested[j];
            }
        }
        else
        {
            for (size_t j = 0; j < word_idx; j++)
            {
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
char *maip_io_soap_suggest(const char *text)
{
    if (!text)
        return null;

    size_t len = strlen(text);
    char *output = (char *)malloc(len * 2 + 64); // Allocate more space to handle replacements
    if (!output)
        return null;

    size_t out_idx = 0;
    char word[64];
    size_t word_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'' || text[i] == '-')
        {
            word[word_idx++] = text[i];
            if (word_idx >= sizeof(word) - 1)
                word_idx = sizeof(word) - 2;
        }
        else
        {
            word[word_idx] = '\0';
            if (word_idx > 0)
            {
                maip_io_soap_normalize_leetspeak(word);
                const char *suggested = maip_io_soap_get_suggestion(word);
                if (suggested && !should_skip_word(word))
                {
                    strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
                    out_idx += strlen(suggested);
                }
                else
                {
                    strncpy(&output[out_idx], word, len * 2 + 64 - out_idx);
                    out_idx += word_idx;
                }
            }
            output[out_idx++] = text[i];
            word_idx = 0;
        }
    }
    word[word_idx] = '\0';
    if (word_idx > 0)
    {
        maip_io_soap_normalize_leetspeak(word);
        const char *suggested = maip_io_soap_get_suggestion(word);
        if (suggested && !should_skip_word(word))
        {
            strncpy(&output[out_idx], suggested, len * 2 + 64 - out_idx);
            out_idx += strlen(suggested);
        }
        else
        {
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
int maip_io_soap_add_custom_filter(const char *phrase)
{
    // Deduplicate
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS; i++)
    {
        if (custom_filters[i] && custom_strcasecmp(custom_filters[i], phrase) == 0)
        {
            return 0;
        }
    }
    for (size_t i = 0; i < MAX_CUSTOM_FILTERS; i++)
    {
        if (custom_filters[i] == null)
        {
            size_t j = 0;
            while (phrase[j] != '\0' && j < sizeof(custom_storage[i]) - 1)
            {
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
void maip_io_soap_clear_custom_filters(void)
{
    memset(custom_filters, 0, sizeof(custom_filters));
}

/**
 * @brief Detect tone of the text using phrase lookup.
 * AI trick: prioritize sarcastic, then formal, else casual.
 */
const char *maip_io_soap_detect_tone(const char *text)
{
    for (size_t i = 0; SARCASTIcpp_PHRASES[i] != null; i++)
    {
        if (custom_strcasestr(text, SARCASTIcpp_PHRASES[i]))
        {
            return "sarcastic";
        }
    }

    for (size_t i = 0; FORMAL_PHRASES[i] != null; i++)
    {
        if (custom_strcasestr(text, FORMAL_PHRASES[i]))
        {
            return "formal";
        }
    }

    return "casual";
}

/**
 * @brief Detect if text contains rot-brain language.
 * AI trick: use substring search for slang.
 */
int maip_io_is_rot_brain(const char *text)
{
    if (!text)
        return 0;

    for (size_t i = 0; FOSSIL_SOAP_SUGGESTIONS[i].bad != null; i++)
    {
        if (custom_strcasestr(text, FOSSIL_SOAP_SUGGESTIONS[i].bad))
        {
            return 1;
        }
    }
    return 0;
}

// *****************************************************************************
// memory management
// *****************************************************************************

maip_sys_memory_t maip_sys_memory_alloc(size_t size)
{
    if (size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_alloc() - Cannot allocate zero bytes.\n");
        return null;
    }

    maip_sys_memory_t ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_alloc() - Memory allocation failed.\n");
        return null;
    }
    return ptr;
}

maip_sys_memory_t maip_sys_memory_realloc(maip_sys_memory_t ptr, size_t size)
{
    maip_sys_memory_t new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_realloc() - Memory reallocation failed.\n");
        return null;
    }
    return new_ptr;
}

maip_sys_memory_t maip_sys_memory_calloc(size_t num, size_t size)
{
    if (num == 0 || size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_calloc() - Cannot allocate zero elements or zero bytes.\n");
        return null;
    }

    maip_sys_memory_t ptr = calloc(num, size);
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_calloc() - Memory allocation failed.\n");
        return null;
    }
    return ptr;
}

maip_sys_memory_t maip_sys_memory_init(maip_sys_memory_t ptr, size_t size, int32_t value)
{
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_init() - Pointer is null.\n");
        return null;
    }

    if (size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_init() - Cannot initialize zero bytes.\n");
        return null;
    }

    return memset(ptr, value, size);
}

void maip_sys_memory_free(maip_sys_memory_t ptr)
{
    if (!ptr)
    {
        return;
    }
    free(ptr); // No need for null check, free() already handles null.
}

maip_sys_memory_t maip_sys_memory_copy(maip_sys_memory_t dest, const maip_sys_memory_t src, size_t size)
{
    if (!dest || !src)
    {
        fprintf(stderr, "Error: maip_sys_memory_copy() - Source or destination is null.\n");
        return null;
    }

    if (size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_copy() - Cannot copy zero bytes.\n");
        return null;
    }

    return memcpy(dest, src, size);
}

maip_sys_memory_t maip_sys_memory_set(maip_sys_memory_t ptr, int32_t value, size_t size)
{
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_set() - Pointer is null.\n");
        return null;
    }

    if (size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_set() - Cannot set zero bytes.\n");
        return null;
    }

    return memset(ptr, value, size);
}

maip_sys_memory_t maip_sys_memory_dup(const maip_sys_memory_t src, size_t size)
{
    if (!src || size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_dup() - Invalid source or zero size.\n");
        return null;
    }

    maip_sys_memory_t dest = maip_sys_memory_alloc(size);
    if (!dest)
    {
        return null; // Error already handled in maip_sys_memory_alloc
    }

    return memcpy(dest, src, size);
}

maip_sys_memory_t maip_sys_memory_zero(maip_sys_memory_t ptr, size_t size)
{
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_zero() - Pointer is null.\n");
        return null;
    }

    if (size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_zero() - Cannot zero out zero bytes.\n");
        return null;
    }

    return memset(ptr, 0, size);
}

int maip_sys_memory_compare(const maip_sys_memory_t ptr1, const maip_sys_memory_t ptr2, size_t size)
{
    if (!ptr1 || !ptr2 || size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_compare() - Invalid pointers or zero size.\n");
        return -1; // Return -1 for invalid input
    }

    return memcmp(ptr1, ptr2, size);
}

maip_sys_memory_t maip_sys_memory_move(maip_sys_memory_t dest, const maip_sys_memory_t src, size_t size)
{
    if (!dest || !src || size == 0)
    {
        fprintf(stderr, "Error: maip_sys_memory_move() - Invalid source or destination pointers, or zero size.\n");
        return null;
    }

    return memmove(dest, src, size);
}

maip_sys_memory_t maip_sys_memory_resize(maip_sys_memory_t ptr, size_t old_size, size_t new_size)
{
    if (!ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_resize() - Pointer is null.\n");
        return NULL;
    }

    if (new_size == 0)
    {
        maip_sys_memory_free(ptr);
        return NULL;
    }

    if (new_size <= old_size)
    {
        // Shrinking, just realloc (no data copy needed)
        maip_sys_memory_t new_ptr = maip_sys_memory_realloc(ptr, new_size);
        if (!new_ptr)
        {
            fprintf(stderr, "Error: maip_sys_memory_resize() - Memory shrink failed, original preserved.\n");
            return ptr;
        }
        return new_ptr;
    }

    // Allocate new memory manually to preserve old data
    maip_sys_memory_t new_ptr = maip_sys_memory_alloc(new_size);
    if (!new_ptr)
    {
        fprintf(stderr, "Error: maip_sys_memory_resize() - Allocation failed.\n");
        return ptr;
    }

    // Copy old data
    memcpy(new_ptr, ptr, old_size);

    // Free old memory
    maip_sys_memory_free(ptr);

    return new_ptr;
}

bool maip_sys_memory_is_valid(const maip_sys_memory_t ptr)
{
    if (!ptr)
    {
        return false;
    }
    // Optional: Add more validation logic if needed, but normally you'd rely on the caller to manage validity.
    return true;
}

// *****************************************************************************
// output management
// *****************************************************************************

maip_fstream_t *MAIP_STDIN;
maip_fstream_t *MAIP_STDOUT;
maip_fstream_t *MAIP_STDERR;

int32_t MAIP_IO_COLOR_ENABLE = 1; // Flag to enable/disable color output

// ================================================================
// RESET
// ================================================================
#define FOSSIL_IO_COLOR_RESET "\033[0m"

// ================================================================
// DARK (STANDARD) COLORS
// ================================================================
#define FOSSIL_IO_COLOR_BLACK "\033[30m"
#define FOSSIL_IO_COLOR_RED "\033[31m"
#define FOSSIL_IO_COLOR_GREEN "\033[32m"
#define FOSSIL_IO_COLOR_YELLOW "\033[33m"
#define FOSSIL_IO_COLOR_BLUE "\033[34m"
#define FOSSIL_IO_COLOR_MAGENTA "\033[35m"
#define FOSSIL_IO_COLOR_CYAN "\033[36m"
#define FOSSIL_IO_COLOR_WHITE "\033[37m"
#define FOSSIL_IO_COLOR_GRAY "\033[90m"
#define FOSSIL_IO_COLOR_ORANGE "\033[38;5;208m"
#define FOSSIL_IO_COLOR_PINK "\033[38;5;205m"
#define FOSSIL_IO_COLOR_PURPLE "\033[38;5;93m"
#define FOSSIL_IO_COLOR_BROWN "\033[38;5;94m"
#define FOSSIL_IO_COLOR_TEAL "\033[38;5;30m"
#define FOSSIL_IO_COLOR_SILVER "\033[38;5;7m"

// ================================================================
// BRIGHT COLORS
// ================================================================
#define FOSSIL_IO_COLOR_BRIGHT_BLACK "\033[90m"
#define FOSSIL_IO_COLOR_BRIGHT_RED "\033[91m"
#define FOSSIL_IO_COLOR_BRIGHT_GREEN "\033[92m"
#define FOSSIL_IO_COLOR_BRIGHT_YELLOW "\033[93m"
#define FOSSIL_IO_COLOR_BRIGHT_BLUE "\033[94m"
#define FOSSIL_IO_COLOR_BRIGHT_MAGENTA "\033[95m"
#define FOSSIL_IO_COLOR_BRIGHT_CYAN "\033[96m"
#define FOSSIL_IO_COLOR_BRIGHT_WHITE "\033[97m"

// ================================================================
// BACKGROUND COLORS
// ================================================================
#define FOSSIL_IO_BG_BLACK "\033[40m"
#define FOSSIL_IO_BG_RED "\033[41m"
#define FOSSIL_IO_BG_GREEN "\033[42m"
#define FOSSIL_IO_BG_YELLOW "\033[43m"
#define FOSSIL_IO_BG_BLUE "\033[44m"
#define FOSSIL_IO_BG_MAGENTA "\033[45m"
#define FOSSIL_IO_BG_CYAN "\033[46m"
#define FOSSIL_IO_BG_WHITE "\033[47m"
#define FOSSIL_IO_BG_GRAY "\033[100m"
#define FOSSIL_IO_BG_ORANGE "\033[48;5;208m"
#define FOSSIL_IO_BG_PINK "\033[48;5;205m"
#define FOSSIL_IO_BG_PURPLE "\033[48;5;93m"
#define FOSSIL_IO_BG_BROWN "\033[48;5;94m"
#define FOSSIL_IO_BG_TEAL "\033[48;5;30m"
#define FOSSIL_IO_BG_SILVER "\033[48;5;7m"

// Bright background colors
#define FOSSIL_IO_BG_BRIGHT_BLACK "\033[100m"
#define FOSSIL_IO_BG_BRIGHT_RED "\033[101m"
#define FOSSIL_IO_BG_BRIGHT_GREEN "\033[102m"
#define FOSSIL_IO_BG_BRIGHT_YELLOW "\033[103m"
#define FOSSIL_IO_BG_BRIGHT_BLUE "\033[104m"
#define FOSSIL_IO_BG_BRIGHT_MAGENTA "\033[105m"
#define FOSSIL_IO_BG_BRIGHT_CYAN "\033[106m"
#define FOSSIL_IO_BG_BRIGHT_WHITE "\033[107m"

// ================================================================
// TEXT ATTRIBUTES
// ================================================================
// Standard attributes
#define FOSSIL_IO_ATTR_BOLD "\033[1m"
#define FOSSIL_IO_ATTR_DIM "\033[2m"
#define FOSSIL_IO_ATTR_ITALIC "\033[3m"
#define FOSSIL_IO_ATTR_UNDERLINE "\033[4m"
#define FOSSIL_IO_ATTR_BLINK "\033[5m"
#define FOSSIL_IO_ATTR_REVERSE "\033[7m"
#define FOSSIL_IO_ATTR_HIDDEN "\033[8m"
#define FOSSIL_IO_ATTR_STRIKETHROUGH "\033[9m"
#define FOSSIL_IO_ATTR_NORMAL "\033[22;23;24;25;27;28m" // Reset all attributes
#define FOSSIL_IO_ATTR_REVERSED "\033[7m"

// Bright background colors
#define FOSSIL_IO_BG_BRIGHT_BLACK "\033[100m"
#define FOSSIL_IO_BG_BRIGHT_RED "\033[101m"
#define FOSSIL_IO_BG_BRIGHT_GREEN "\033[102m"
#define FOSSIL_IO_BG_BRIGHT_YELLOW "\033[103m"
#define FOSSIL_IO_BG_BRIGHT_BLUE "\033[104m"
#define FOSSIL_IO_BG_BRIGHT_MAGENTA "\033[105m"
#define FOSSIL_IO_BG_BRIGHT_CYAN "\033[106m"
#define FOSSIL_IO_BG_BRIGHT_WHITE "\033[107m"

// Reset specific attributes
#define FOSSIL_IO_ATTR_RESET_BOLD "\033[22m"
#define FOSSIL_IO_ATTR_RESET_DIM "\033[22m"
#define FOSSIL_IO_ATTR_RESET_ITALIC "\033[23m"
#define FOSSIL_IO_ATTR_RESET_UNDERLINE "\033[24m"
#define FOSSIL_IO_ATTR_RESET_BLINK "\033[25m"
#define FOSSIL_IO_ATTR_RESET_REVERSE "\033[27m"
#define FOSSIL_IO_ATTR_RESET_HIDDEN "\033[28m"
#define FOSSIL_IO_ATTR_RESET_STRIKE "\033[29m"

// Additional attributes
#define FOSSIL_IO_ATTR_ITALIC "\033[3m"
#define FOSSIL_IO_ATTR_STRIKETHROUGH "\033[9m"

#define FOSSIL_IO_BUFFER_SIZE 1000

// Function to apply color
void maip_io_apply_color(const char *color)
{
    if (maip_io_cstr_compare(color, "red") == 0)
    {
        printf(FOSSIL_IO_COLOR_RED);
    }
    else if (maip_io_cstr_compare(color, "green") == 0)
    {
        printf(FOSSIL_IO_COLOR_GREEN);
    }
    else if (maip_io_cstr_compare(color, "yellow") == 0)
    {
        printf(FOSSIL_IO_COLOR_YELLOW);
    }
    else if (maip_io_cstr_compare(color, "blue") == 0)
    {
        printf(FOSSIL_IO_COLOR_BLUE);
    }
    else if (maip_io_cstr_compare(color, "magenta") == 0)
    {
        printf(FOSSIL_IO_COLOR_MAGENTA);
    }
    else if (maip_io_cstr_compare(color, "cyan") == 0)
    {
        printf(FOSSIL_IO_COLOR_CYAN);
    }
    else if (maip_io_cstr_compare(color, "white") == 0)
    {
        printf(FOSSIL_IO_COLOR_WHITE);
    }
    else if (maip_io_cstr_compare(color, "black") == 0)
    {
        printf(FOSSIL_IO_COLOR_BLACK);
    }
    else if (maip_io_cstr_compare(color, "orange") == 0)
    {
        printf(FOSSIL_IO_COLOR_ORANGE);
    }
    else if (maip_io_cstr_compare(color, "gray") == 0)
    {
        printf(FOSSIL_IO_COLOR_GRAY);
    }
    else if (maip_io_cstr_compare(color, "pink") == 0)
    {
        printf(FOSSIL_IO_COLOR_PINK);
    }
    else if (maip_io_cstr_compare(color, "purple") == 0)
    {
        printf(FOSSIL_IO_COLOR_PURPLE);
    }
    else if (maip_io_cstr_compare(color, "brown") == 0)
    {
        printf(FOSSIL_IO_COLOR_BROWN);
    }
    else if (maip_io_cstr_compare(color, "teal") == 0)
    {
        printf(FOSSIL_IO_COLOR_TEAL);
    }
    else if (maip_io_cstr_compare(color, "silver") == 0)
    {
        printf(FOSSIL_IO_COLOR_SILVER);
    }

    // Bright colors
    else if (maip_io_cstr_compare(color, "bright_red") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_RED);
    }
    else if (maip_io_cstr_compare(color, "bright_green") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_GREEN);
    }
    else if (maip_io_cstr_compare(color, "bright_yellow") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_YELLOW);
    }
    else if (maip_io_cstr_compare(color, "bright_blue") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_BLUE);
    }
    else if (maip_io_cstr_compare(color, "bright_magenta") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_MAGENTA);
    }
    else if (maip_io_cstr_compare(color, "bright_cyan") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_CYAN);
    }
    else if (maip_io_cstr_compare(color, "bright_white") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_WHITE);
    }
    else if (maip_io_cstr_compare(color, "bright_black") == 0)
    {
        printf(FOSSIL_IO_COLOR_BRIGHT_BLACK);
    }
    else
    {
        printf(FOSSIL_IO_COLOR_RESET); // Reset to default if color not recognized
    }
}

// Function to apply text attributes (e.g., bold, underline)
void maip_io_apply_attribute(const char *attribute)
{
    if (maip_io_cstr_compare(attribute, "bold") == 0)
    {
        printf(FOSSIL_IO_ATTR_BOLD);
    }
    else if (maip_io_cstr_compare(attribute, "underline") == 0)
    {
        printf(FOSSIL_IO_ATTR_UNDERLINE);
    }
    else if (maip_io_cstr_compare(attribute, "reversed") == 0)
    {
        printf(FOSSIL_IO_ATTR_REVERSED);
    }
    else if (maip_io_cstr_compare(attribute, "blink") == 0)
    {
        printf(FOSSIL_IO_ATTR_BLINK);
    }
    else if (maip_io_cstr_compare(attribute, "hidden") == 0)
    {
        printf(FOSSIL_IO_ATTR_HIDDEN);
    }
    else if (maip_io_cstr_compare(attribute, "normal") == 0)
    {
        printf(FOSSIL_IO_ATTR_NORMAL);
    }
    else if (maip_io_cstr_compare(attribute, "italic") == 0)
    {
        printf(FOSSIL_IO_ATTR_ITALIC);
    }
    else if (maip_io_cstr_compare(attribute, "strikethrough") == 0)
    {
        printf(FOSSIL_IO_ATTR_STRIKETHROUGH);
    }
    else if (maip_io_cstr_compare(attribute, "dim") == 0)
    {
        printf(FOSSIL_IO_ATTR_DIM);
    }
    else if (maip_io_cstr_compare(attribute, "reset") == 0)
    {
        printf(FOSSIL_IO_ATTR_NORMAL); // Reset to normal if attribute not recognized
    }
}

// Function to handle named positions (like top, bottom, left, right)
void maip_io_apply_position(const char *pos)
{
    if (maip_io_cstr_compare(pos, "top") == 0)
    {
        // Apply position logic for top
        printf("\033[H"); // Move cursor to the top
    }
    else if (maip_io_cstr_compare(pos, "bottom") == 0)
    {
        // Apply position logic for bottom
        printf("\033[999;1H"); // Move cursor to the bottom (example within reasonable bounds)
    }
    else if (maip_io_cstr_compare(pos, "left") == 0)
    {
        // Apply position logic for left
        printf("\033[1;1H"); // Move cursor to the top-left corner
    }
    else if (maip_io_cstr_compare(pos, "right") == 0)
    {
        // Apply position logic for right
        printf("\033[1;999H"); // Move cursor to the top-right corner (example within reasonable bounds)
    }
    else if (maip_io_cstr_compare(pos, "center") == 0)
    {
        // Apply position logic for center
        printf("\033[12;40H"); // Move cursor to the center (example within reasonable bounds)
    }
}

// Function to print text with attributes, colors, positions, and format specifiers
void maip_io_print_with_attributes(const char *format, ...)
{
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
    while ((start = strchr(current_pos, '{')) != null)
    {
        // Print text before '{'
        printf("%.*s", (int)(start - current_pos), current_pos);

        // Find the matching '}'
        end = strchr(start, '}');
        if (end)
        {
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
            if (comma_pos)
            {
                *comma_pos = '\0';         // null-terminate the first part
                color = attributes;        // Color or position part
                attribute = comma_pos + 1; // Attribute part
            }
            else
            {
                color = attributes; // Only one part (could be color, attribute, or position)
            }

            // Handle positions (like {pos:name})
            if (strstr(color, "pos:") == color)
            {
                pos = color + 4; // Skip the "pos:" prefix
                maip_io_apply_position(pos);
            }
            else
            {
                // Apply color and/or attribute based on flags
                if (MAIP_IO_COLOR_ENABLE && color)
                {
                    maip_io_apply_color(color);
                }
                maip_io_apply_attribute(attribute);
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
void maip_io_fprint_with_attributes(maip_fstream_t *stream, const char *str)
{
    if (str != null && stream != null)
    {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color and attribute logic (same as the print version)
        maip_io_print_with_attributes(sanitized_str);

        // Write the sanitized string to the stream
        fputs(sanitized_str, stream->file);
    }
    else
    {
        fputs("cnullptr\n", stderr);
    }
}

//
// OUTPUT FUNCTIONS
//

// Function to print a sanitized string with attributes inside {}
void maip_io_puts(const char *str)
{
    if (str != null)
    {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Print the sanitized string with attributes
        maip_io_print_with_attributes(sanitized_str);
    }
    else
    {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a single character
void maip_io_putchar(char c)
{
    putchar(c);
}

// Function to print sanitized formatted output with attributes
void maip_io_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized output with attributes
    maip_io_print_with_attributes(buffer);

    va_end(args);
}

int maip_io_vsnprintf(char *buffer, size_t size, const char *format, va_list args)
{
    if (buffer == null || size == 0 || format == null)
    {
        return -1; // Invalid input
    }

    // Create a temporary buffer to hold the formatted string
    char temp_buffer[FOSSIL_IO_BUFFER_SIZE];
    int formatted_length = vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);

    if (formatted_length < 0 || (size_t)formatted_length >= size)
    {
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
void maip_io_fputs(maip_fstream_t *stream, const char *str)
{
    if (str != null && stream != null)
    {
        char sanitized_str[FOSSIL_IO_BUFFER_SIZE];
        strncpy(sanitized_str, str, sizeof(sanitized_str));
        sanitized_str[sizeof(sanitized_str) - 1] = '\0'; // Ensure null termination

        // Apply color/attributes and sanitize the string before printing
        maip_io_fprint_with_attributes(stream, sanitized_str);
    }
    else
    {
        fputs("cnullptr\n", stderr);
    }
}

// Function to print a sanitized formatted string to a specific file stream
void maip_io_fprintf(maip_fstream_t *stream, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Create a buffer to hold the formatted string
    char buffer[FOSSIL_IO_BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);

    // Print the sanitized formatted string with attributes to the specified stream
    maip_io_fprint_with_attributes(stream, buffer);

    va_end(args);
}

// TUI PART

void maip_io_clear_screen(void)
{
    maip_io_printf("\033[2J\033[H");
}

void maip_io_move_cursor(int row, int col)
{
    maip_io_printf("\033[%d;%dH", row, col);
}

void maip_io_hide_cursor(void)
{
    maip_io_printf("\033[?25l");
}

void maip_io_show_cursor(void)
{
    maip_io_printf("\033[?25h");
}

void maip_io_draw_horizontal_line(int length, char ch)
{
    for (int i = 0; i < length; ++i)
    {
        putchar(ch);
    }
    putchar('\n');
}

void maip_io_draw_vertical_line(int length, char ch)
{
    for (int i = 0; i < length; ++i)
    {
        putchar(ch);
        putchar('\n');
    }
}

void maip_io_flush(void)
{
    fflush(stdout);
}

// *****************************************************************************
// string management
// *****************************************************************************
/*
#ifndef HAVE_STRNLEN
static size_t strnlen(const char *s, size_t maxlen) {
    size_t i;
    for (i = 0; i < maxlen && s[i]; i++);
    return i;
}
#endif

#ifndef HAVE_STRNCASECMP
static int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n && s1[i] && s2[i]; i++) {
        int diff = tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[i]);
        if (diff != 0) return diff;
    }
    return 0;
}
#endif
*/
// ============================================================================
// C String Functions
// ============================================================================

cstr maip_io_cstr_create(const char *init)
{
    if (!init)
        return null;
    size_t length = strlen(init);
    cstr str = (cstr)malloc(length + 1);
    if (str)
    {
        strcpy(str, init);
    }
    return str;
}

void maip_io_cstr_free(cstr str)
{
    if (str)
    {
        free(str);
    }
}

cstr maip_io_cstr_copy(ccstr str)
{
    if (!str)
        return null;
    return maip_io_cstr_create(str);
}

cstr maip_io_cstr_dup(ccstr str)
{
    if (!str)
        return null;
    size_t length = strlen(str);
    cstr new_str = (cstr)malloc(length + 1);
    if (new_str)
    {
        strcpy(new_str, str);
    }
    return new_str;
}

cstr maip_io_cstr_concat(ccstr s1, ccstr s2)
{
    if (!s1 || !s2)
        return null;
    size_t length1 = strlen(s1);
    size_t length2 = strlen(s2);
    cstr str = (cstr)malloc(length1 + length2 + 1);
    if (str)
    {
        strcpy(str, s1);
        strcpy(str + length1, s2);
    }
    return str;
}

size_t maip_io_cstr_length(ccstr str)
{
    if (!str)
        return 0;
    return strlen(str);
}

int maip_io_cstr_compare_prefix(ccstr str, ccstr prefix)
{
    if (!str || !prefix)
        return -1;
    size_t prefix_length = strlen(prefix);
    return strncmp(str, prefix, prefix_length);
}

int maip_io_cstr_compare(ccstr s1, ccstr s2)
{
    if (!s1 || !s2)
        return -1;
    return strcmp(s1, s2);
}

void maip_io_cstr_trim(cstr str)
{
    if (!str)
        return;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && isspace(str[start]))
    {
        start++;
    }
    while (end > start && isspace(str[end]))
    {
        end--;
    }
    size_t count = end - start + 1;
    if (start > 0)
    {
        memmove(str, str + start, count);
    }
    str[count] = '\0';
}

cstr *maip_io_cstr_split(ccstr str, char delimiter, size_t *count)
{
    if (!str || !count)
        return null;
    size_t length = strlen(str);
    size_t num_delimiters = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == delimiter)
        {
            num_delimiters++;
        }
    }
    *count = num_delimiters + 1;
    cstr *result = (cstr *)malloc(*count * sizeof(cstr));
    if (result)
    {
        size_t start = 0;
        size_t index = 0;
        for (size_t i = 0; i < length; i++)
        {
            if (str[i] == delimiter)
            {
                size_t count = i - start;
                result[index] = (cstr)malloc(count + 1);
                if (result[index])
                {
                    memcpy(result[index], str + start, count);
                    result[index][count] = '\0';
                    start = i + 1;
                    index++;
                }
                else
                {
                    // Free previously allocated memory on error
                    for (size_t j = 0; j < index; j++)
                    {
                        free(result[j]);
                    }
                    free(result);
                    return null;
                }
            }
        }
        size_t count = length - start;
        result[index] = (cstr)malloc(count + 1);
        if (result[index])
        {
            memcpy(result[index], str + start, count);
            result[index][count] = '\0';
        }
        else
        {
            // Free previously allocated memory on error
            for (size_t j = 0; j < index; j++)
            {
                free(result[j]);
            }
            free(result);
            return null;
        }
    }
    return result;
}

cstr maip_io_cstr_replace(ccstr str, ccstr old, ccstr new_str)
{
    if (!str || !old || !new_str)
        return null;
    size_t old_length = strlen(old);
    size_t new_length = strlen(new_str);
    size_t count = 0;
    size_t index = 0;
    size_t length = strlen(str);
    while (index < length)
    {
        if (strstr(str + index, old) == str + index)
        {
            count++;
            index += old_length;
        }
        else
        {
            index++;
        }
    }
    cstr result = (cstr)malloc(length + count * (new_length - old_length) + 1);
    if (result)
    {
        index = 0;
        size_t start = 0;
        while (index < length)
        {
            if (strstr(str + index, old) == str + index)
            {
                strcpy(result + start, new_str);
                start += new_length;
                index += old_length;
            }
            else
            {
                result[start] = str[index];
                start++;
                index++;
            }
        }
        result[start] = '\0';
    }
    return result;
}

cstr maip_io_cstr_to_upper(cstr str)
{
    if (!str)
        return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result)
    {
        for (size_t i = 0; i < length; i++)
        {
            result[i] = toupper(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

cstr maip_io_cstr_to_lower(cstr str)
{
    if (!str)
        return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result)
    {
        for (size_t i = 0; i < length; i++)
        {
            result[i] = tolower(str[i]);
        }
        result[length] = '\0';
    }
    return result;
}

int maip_io_cstr_starts_with(ccstr str, ccstr prefix)
{
    if (!str || !prefix)
        return 0;
    size_t str_length = strlen(str);
    size_t prefix_length = strlen(prefix);
    if (prefix_length > str_length)
    {
        return 0;
    }
    return strncmp(str, prefix, prefix_length) == 0;
}

int maip_io_cstr_ends_with(ccstr str, ccstr suffix)
{
    if (!str || !suffix)
        return 0;
    size_t str_length = strlen(str);
    size_t suffix_length = strlen(suffix);
    if (suffix_length > str_length)
    {
        return 0;
    }
    return strncmp(str + str_length - suffix_length, suffix, suffix_length) == 0;
}

cstr maip_io_cstr_substring(ccstr str, size_t start, size_t length)
{
    if (!str)
        return null;
    size_t str_length = strlen(str);
    if (start >= str_length)
    {
        return null;
    }
    cstr result = (cstr)malloc(length + 1);
    if (result)
    {
        size_t count = str_length - start;
        if (length < count)
        {
            count = length;
        }
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

cstr maip_io_cstr_reverse(cstr str)
{
    if (!str)
        return null;
    size_t length = strlen(str);
    cstr result = (cstr)malloc(length + 1);
    if (result)
    {
        for (size_t i = 0; i < length; i++)
        {
            result[i] = str[length - i - 1];
        }
        result[length] = '\0';
    }
    return result;
}

int maip_io_cstr_contains(ccstr str, ccstr substr)
{
    if (!str || !substr)
        return 0;
    return strstr(str, substr) != null;
}

cstr maip_io_cstr_repeat(ccstr str, size_t count)
{
    if (!str || count == 0)
        return null;
    size_t length = strlen(str);
    size_t new_length = length * count;
    cstr result = (cstr)malloc(new_length + 1);
    if (result)
    {
        for (size_t i = 0; i < count; i++)
        {
            memcpy(result + i * length, str, length);
        }
        result[new_length] = '\0';
    }
    return result;
}

cstr maip_io_cstr_strip(ccstr str, char ch)
{
    if (!str)
        return null;
    size_t length = strlen(str);
    size_t start = 0;
    size_t end = length - 1;
    while (start < length && str[start] == ch)
    {
        start++;
    }
    while (end > start && str[end] == ch)
    {
        end--;
    }
    size_t count = end - start + 1;
    cstr result = (cstr)malloc(count + 1);
    if (result)
    {
        memcpy(result, str + start, count);
        result[count] = '\0';
    }
    return result;
}

size_t maip_io_cstr_count(ccstr str, ccstr substr)
{
    if (!str || !substr)
        return 0;
    size_t count = 0;
    size_t length = strlen(substr);
    while ((str = strstr(str, substr)) != null)
    {
        count++;
        str += length;
    }
    return count;
}

cstr maip_io_cstr_pad_left(ccstr str, size_t total_length, char pad_char)
{
    if (!str || total_length == 0)
        return null;
    size_t length = strlen(str);
    if (length >= total_length)
    {
        return maip_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result)
    {
        memset(result, pad_char, pad_length);
        strcpy(result + pad_length, str);
        result[total_length] = '\0';
    }
    return result;
}

cstr maip_io_cstr_pad_right(ccstr str, size_t total_length, char pad_char)
{
    if (!str || total_length == 0)
        return null;
    size_t length = strlen(str);
    if (length >= total_length)
    {
        return maip_io_cstr_copy(str);
    }
    size_t pad_length = total_length - length;
    cstr result = (cstr)malloc(total_length + 1);
    if (result)
    {
        strcpy(result, str);
        memset(result + length, pad_char, pad_length);
        result[total_length] = '\0';
    }
    return result;
}

bool maip_io_cstr_append(cstr dest, size_t max_len, cstr src)
{
    if (!dest || !src || max_len == 0)
        return false;

    // Find current length of dest up to max_len
    size_t dest_len = 0;
    while (dest_len < max_len && dest[dest_len] != '\0')
    {
        ++dest_len;
    }

    // If no null-terminator found in range, dest is not safe
    if (dest_len == max_len)
        return false;

    size_t srcpp_len = strlen(src);

    // Make sure there's enough space (including null terminator)
    if (dest_len + srcpp_len >= max_len)
        return false;

    memcpy(dest + dest_len, src, srcpp_len);
    dest[dest_len + srcpp_len] = '\0';

    return true;
}
