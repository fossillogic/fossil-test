/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/pizza/test.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>


jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp
static int _ASSERT_COUNT = 0; // Counter for the number of assertions

// --- Internal helper for timing ---
static uint64_t fossil_pizza_now_ns(void) {
    struct timeval tv;
    gettimeofday(&tv, null);
    return (uint64_t)tv.tv_sec * 1000000000ULL + (uint64_t)tv.tv_usec * 1000ULL;
}

// --- Start ---
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv) {
    if (!engine || !argv) return FOSSIL_PIZZA_FAILURE;

    pizza_sys_memory_set(engine, 0, sizeof(*engine));
    engine->suites = null;
    engine->count = 0;
    engine->capacity = 0;
    engine->score_total = 0;
    engine->score_possible = 0;
    engine->pallet = fossil_pizza_pallet_create(argc, argv);
    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));

    // Parse configuration file if specified
    const char* config_file = engine->pallet.config_file;
    if (config_file && fossil_pizza_ini_parse(config_file, &engine->pallet) != FOSSIL_PIZZA_SUCCESS) {
        pizza_io_printf("Error: Failed to parse configuration file: %s\n", config_file);
        return FOSSIL_PIZZA_FAILURE;
    }

    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Suite ---
int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    if (engine->count >= engine->capacity) {
        size_t new_cap = engine->capacity ? engine->capacity * 2 : 4;
        fossil_pizza_suite_t* resized = pizza_sys_memory_realloc(engine->suites, new_cap * sizeof(*engine->suites));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        engine->suites = resized;
        engine->capacity = new_cap;
    }
    engine->suites[engine->count++] = suite;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Case ---
int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;
    if (suite->count >= suite->capacity) {
        size_t new_cap = suite->capacity ? suite->capacity * 2 : 4;
        fossil_pizza_case_t* resized = pizza_sys_memory_realloc(suite->cases, new_cap * sizeof(*suite->cases));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        suite->cases = resized;
        suite->capacity = new_cap;
    }
    suite->cases[suite->count++] = test_case;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Update Score ---
void fossil_pizza_update_score(fossil_pizza_case_t* test_case, fossil_pizza_suite_t* suite) {
    switch (test_case->result) {
        case FOSSIL_PIZZA_CASE_PASS:
            suite->score.passed++;
            suite->total_score++;
            break;
        case FOSSIL_PIZZA_CASE_FAIL:
            suite->score.failed++;
            break;
        case FOSSIL_PIZZA_CASE_TIMEOUT:
            suite->score.timeout++;
            break;
        case FOSSIL_PIZZA_CASE_SKIPPED:
            suite->score.skipped++;
            break;
        case FOSSIL_PIZZA_CASE_UNEXPECTED:
            suite->score.unexpected++;
            break;
        case FOSSIL_PIZZA_CASE_EMPTY:
        default:
            suite->score.empty++;
            break;
    }
    suite->total_possible++;
}

// --- Show Test Cases ---

// Formats nanoseconds into a string: "Xs Yus Zns" and returns a heap-allocated string
char *fossil_pizza_format_ns(uint64_t ns) {
    uint64_t sec = ns / 1000000000ULL;
    uint64_t usec = (ns % 1000000000ULL) / 1000ULL;
    uint64_t nsec = ns % 1000ULL;
    char *buffer = (char *)pizza_sys_memory_alloc(64);
    if (buffer) {
        snprintf(buffer, 64, "%lu s %lu us %lu ns", (unsigned long)sec, (unsigned long)usec, (unsigned long)nsec);
        buffer[63] = '\0';
    }

    return buffer;
}

void fossil_pizza_show_cases(const fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases) return;

    // Determine mode (list, tree, graph), default to list
    const char* mode = (engine && engine->pallet.show.mode) ? engine->pallet.show.mode : "list";

    for (size_t i = 0; i < suite->count; ++i) {

        const fossil_pizza_case_t* test_case = &suite->cases[i];
        const char* result_str =
                    (test_case->result == FOSSIL_PIZZA_CASE_EMPTY) ? "empty" :
                    (test_case->result == FOSSIL_PIZZA_CASE_PASS) ? "pass" :
                    (test_case->result == FOSSIL_PIZZA_CASE_FAIL) ? "fail" :
                    (test_case->result == FOSSIL_PIZZA_CASE_TIMEOUT) ? "timeout" :
                    (test_case->result == FOSSIL_PIZZA_CASE_SKIPPED) ? "skipped" :
                    (test_case->result == FOSSIL_PIZZA_CASE_UNEXPECTED) ? "unexpected" : "unknown";

        // Filtering logic
        if (engine && engine->pallet.show.test_name && pizza_io_cstr_compare(test_case->name, engine->pallet.show.test_name) != 0)
            continue;
        if (engine && engine->pallet.show.suite_name && pizza_io_cstr_compare(suite->suite_name, engine->pallet.show.suite_name) != 0)
            continue;
        if (engine && engine->pallet.show.tag && (!test_case->tags || !strstr(test_case->tags, engine->pallet.show.tag)))
            continue;
        if (engine && engine->pallet.show.result) {
            if (pizza_io_cstr_compare(result_str, engine->pallet.show.result) != 0)
                continue;
        }

        // Output according to mode and theme
        if (pizza_io_cstr_compare(mode, "tree") == 0) {
            switch (engine ? engine->pallet.theme : PIZZA_THEME_FOSSIL) {
            case PIZZA_THEME_FOSSIL:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("  {blue}├─{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Tags    {reset}: {white}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Criteria{reset}: {white}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Time    {reset}: {white}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("  {blue}│   └─{reset} {cyan}Result  {reset}: {green}%s{reset} {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  ::TEST:: %s\n", test_case->name);
                    pizza_io_printf("    ::TAGS:: %s\n", test_case->tags);
                    pizza_io_printf("    ::CRITERIA:: %s\n", test_case->criteria);
                    pizza_io_printf("    ::TIME:: %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    ::RESULT:: %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {blue}├─{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Tags    {reset}: {white}%s{reset}\n", test_case->tags);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Criteria{reset}: {white}%s{reset}\n", test_case->criteria);
                    pizza_io_printf("  {blue}│   ├─{reset} {cyan}Time    {reset}: {white}%s{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("  {blue}│   └─{reset} {cyan}Result  {reset}: {green}%s{reset}\n", result_str);
                }
                break;
            case PIZZA_THEME_CPPUTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("  {magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} %s {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} %s {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} %s {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} %s {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  {magenta}::CASE::{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}::TAGS::{reset} %s\n", test_case->tags);
                    pizza_io_printf("    {yellow}::CRITERIA::{reset} %s\n", test_case->criteria);
                    pizza_io_printf("    {yellow}::TIME::{reset} %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}::RESULT::{reset} %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {magenta}[CASE]{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} %s\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} %s\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} %s\n", result_str);
                }
                break;
            case PIZZA_THEME_TAP:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("  {yellow}# ├─{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Tags     {reset}: {white}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Criteria {reset}: {white}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Time     {reset}: {white}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("  {yellow}# │   └─{reset} {cyan}Result   {reset}: {green}%s{reset} {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  {yellow}# ::CASE::{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("  {yellow}#   ::TAGS::{reset} %s\n", test_case->tags);
                    pizza_io_printf("  {yellow}#   ::CRITERIA::{reset} %s\n", test_case->criteria);
                    pizza_io_printf("  {yellow}#   ::TIME::{reset} %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("  {yellow}#   ::RESULT::{reset} %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {yellow}# ├─{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Tags     {reset}: {white}%s{reset}\n", test_case->tags);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Criteria {reset}: {white}%s{reset}\n", test_case->criteria);
                    pizza_io_printf("  {yellow}# │   ├─{reset} {cyan}Time     {reset}: {white}%s{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("  {yellow}# │   └─{reset} {cyan}Result   {reset}: {green}%s{reset}\n", result_str);
                }
                break;
            case PIZZA_THEME_GOOGLETEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    // Google Test themed colors: blue, red, yellow, green (Google logo colors)
                    pizza_io_printf("  {blue}[----------]{reset} {cyan}%s{reset} {red}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} {green}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} {green}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} {green}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} {red}%s{reset} {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  [  CASE   ] ::CASE:: %s\n", test_case->name);
                    pizza_io_printf("    ::TAGS:: %s\n", test_case->tags);
                    pizza_io_printf("    ::CRITERIA:: %s\n", test_case->criteria);
                    pizza_io_printf("    ::TIME:: %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    ::RESULT:: %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {blue}[----------]{reset} {cyan}%s{reset} {red}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} {green}%s{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} {green}%s{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} {green}%s{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} {red}%s{reset}\n", result_str);
                }
                break;
            case PIZZA_THEME_UNITY:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("  {green}Unity Case:{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}Tags    {reset}: {white}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}Criteria{reset}: {white}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}Time    {reset}: {white}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}Result  {reset}: {green}%s{reset} {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  ::UNITY_CASE:: %s\n", test_case->name);
                    pizza_io_printf("    ::TAGS:: %s\n", test_case->tags);
                    pizza_io_printf("    ::CRITERIA:: %s\n", test_case->criteria);
                    pizza_io_printf("    ::TIME:: %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    ::RESULT:: %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {green}Unity Case:{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}Tags    {reset}: {white}%s{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}Criteria{reset}: {white}%s{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}Time    {reset}: {white}%s{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}Result  {reset}: {green}%s{reset}\n", result_str);
                }
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("  {magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} %s {yellow}[with tag]{reset}\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} %s {yellow}[given criteria]{reset}\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} %s {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} %s {yellow}[the result]{reset}\n", result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("  {magenta}::CASE::{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}::TAGS::{reset} %s\n", test_case->tags);
                    pizza_io_printf("    {yellow}::CRITERIA::{reset} %s\n", test_case->criteria);
                    pizza_io_printf("    {yellow}::TIME::{reset} %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}::RESULT::{reset} %s\n", result_str);
                } else { // plain or default
                    pizza_io_printf("  {magenta}[CASE]{reset} {cyan}%s{reset}\n", test_case->name);
                    pizza_io_printf("    {yellow}[Tags]{reset} %s\n", test_case->tags);
                    pizza_io_printf("    {yellow}[Criteria]{reset} %s\n", test_case->criteria);
                    pizza_io_printf("    {yellow}[Time]{reset} %s\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                    pizza_io_printf("    {yellow}[Result]{reset} %s\n", result_str);
                }
                break;
            default:
                pizza_io_printf("  - %s (Tags: %s, Criteria: %s, Time: %s, Result: %s)\n",
                test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                break;
            }
        } else if (pizza_io_cstr_compare(mode, "graph") == 0) {
            switch (engine ? engine->pallet.theme : PIZZA_THEME_FOSSIL) {
            case PIZZA_THEME_FOSSIL:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{blue}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}{green}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("::CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{blue}[CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset}{green}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_CPPUTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}{green}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset}{green} %s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset}{green}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_TAP:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{yellow}# [CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}{green}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("{yellow}# ::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset}{green} %s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else {
                    pizza_io_printf("{yellow}# [CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset}{green}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_GOOGLETEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    // Google Test themed colors: blue, red, yellow, green (Google logo colors)
                    pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} {red}[test case]{reset} --[{yellow}tags:{reset} {green}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset} {green}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset} {green}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset} {red}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("[  CASE   ] ::CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else {
                    pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} --[{yellow}tags:{reset} {green}%s{reset},{yellow}criteria:{reset} {green}%s{reset},{yellow}time:{reset} {green}%s{reset},{yellow}result:{reset} {red}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_UNITY:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{green}Unity Case:{reset} %s [test case] --[{yellow}tags:{reset}%s [with tag],{yellow}criteria:{reset}%s [given criteria],{yellow}time:{reset}%s [the time],{yellow}result:{reset}%s [the result]]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("::UNITY_CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else {
                    pizza_io_printf("{green}Unity Case:{reset} %s --[{yellow}tags:{reset}%s,{yellow}criteria:{reset}%s,{yellow}time:{reset}%s,{yellow}result:{reset}%s]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}{green}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset}{green} %s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else {
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset}{green}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            default:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{blue}- {reset}{cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}{green}%s{reset} {yellow}[the result]{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("::CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else {
                    pizza_io_printf("{blue}- {reset}{cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset}{green}%s{reset}]\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            }
        } else { // list (default)
            switch (engine ? engine->pallet.theme : PIZZA_THEME_FOSSIL) {
            case PIZZA_THEME_FOSSIL:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf(" {blue}-{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} {green}%s{reset} {yellow}[the result]{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf(" ::CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf(" {blue}-{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} {green}%s{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_CPPUTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} {green}%s{reset} {yellow}[the result]{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} ( {yellow}::TAGS::{reset} {white}%s{reset}, {yellow}::CRITERIA::{reset} {white}%s{reset}, {yellow}::TIME::{reset} {white}%s{reset}, {yellow}::RESULT::{reset} {green}%s{reset} )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} {green}%s{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_TAP:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("# {blue}-{reset} %s [test case] ({yellow}Tags:{reset} %s [with tag], {yellow}Criteria:{reset} %s [given criteria], {yellow}Time:{reset} %s [the time], {yellow}Result:{reset} %s [the result])\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("# ::CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("# {blue}-{reset} %s ({yellow}Tags:{reset} %s, {yellow}Criteria:{reset} %s, {yellow}Time:{reset} %s, {yellow}Result:{reset} %s)\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_GOOGLETEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    // Google Test themed colors: blue, red, yellow, green (Google logo colors)
                    pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} {red}[test case]{reset} ({yellow}Tags:{reset} {green}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {green}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {green}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} {red}%s{reset} {yellow}[the result]{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("[  CASE   ] ::CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {green}%s{reset}, {yellow}Criteria:{reset} {green}%s{reset}, {yellow}Time:{reset} {green}%s{reset}, {yellow}Result:{reset} {red}%s{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_UNITY:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{green}Unity Case:{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} {green}%s{reset} {yellow}[the result]{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf(" ::UNITY_CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{green}Unity Case:{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} {green}%s{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} {green}%s{reset} {yellow}[the result]{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                    pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} ( {yellow}::TAGS::{reset} {white}%s{reset}, {yellow}::CRITERIA::{reset} {white}%s{reset}, {yellow}::TIME::{reset} {white}%s{reset}, {yellow}::RESULT::{reset} {green}%s{reset} )\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                } else { // plain or default
                    pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} {green}%s{reset})\n",
                        test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                }
                break;
            default:
                pizza_io_printf("- %s (Tags: %s, Criteria: %s, Time: %s, Result: %s)\n",
                test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
                break;
            }
        }
    }
}

// --- Run One Test ---

// Utility function to convert seconds to nanoseconds
static uint64_t seconds_to_nanoseconds(uint64_t seconds) {
    return seconds * 1000000000ULL;
}

void fossil_pizza_run_test(const fossil_pizza_engine_t* engine, fossil_pizza_case_t* test_case, fossil_pizza_suite_t* suite) {
    if (!test_case || !suite) return;

    // Check if the test case name matches the --only filter
    if (engine->pallet.run.only && pizza_io_cstr_compare(engine->pallet.run.only, test_case->name) != 0) {
        return; // Skip this test case if it doesn't match the --only filter
    }

    // Check if the test case name matches the --skip filter
    if (engine->pallet.run.skip && pizza_io_cstr_compare(engine->pallet.run.skip, test_case->name) == 0) {
        test_case->result = FOSSIL_PIZZA_CASE_SKIPPED;
        return; // Skip this test case if it matches the --skip filter
    }

    for (int i = 0; i < (engine->pallet.run.repeat ? engine->pallet.run.repeat : 1); ++i) {
        if (test_case->setup) test_case->setup();

        uint64_t start_time = fossil_pizza_now_ns();

        if (test_case->run) {
            if (setjmp(test_jump_buffer) == 0) {
                test_case->run();
                uint64_t elapsed_time = fossil_pizza_now_ns() - start_time;

                if (elapsed_time > seconds_to_nanoseconds(G_PIZZA_TIMEOUT)) { // 1 minute in nanoseconds
                    test_case->result = FOSSIL_PIZZA_CASE_TIMEOUT;
                } else {
                    test_case->result = FOSSIL_PIZZA_CASE_PASS;
                }
            } else {
                test_case->result = FOSSIL_PIZZA_CASE_FAIL;
                if (engine->pallet.run.fail_fast) {
                    return; // Exit immediately if --fail-fast is enabled
                }
            }
        } else {
            test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
        }
        test_case->elapsed_ns = fossil_pizza_now_ns() - start_time;

        if (test_case->teardown) test_case->teardown();
    }

    // Output test case result
    fossil_pizza_show_cases(suite, engine);

    // Update scores based on result
    fossil_pizza_update_score(test_case, suite);
    _ASSERT_COUNT = 0; // Reset the assertion count for the next test case
}

// --- Algorithmic modifications ---

// --- Sorting Test Cases ---
static int compare_name_asc(const void* a, const void* b) {
    return pizza_io_cstr_compare(((fossil_pizza_case_t*)a)->name, ((fossil_pizza_case_t*)b)->name);
}

static int compare_name_desc(const void* a, const void* b) {
    return pizza_io_cstr_compare(((fossil_pizza_case_t*)b)->name, ((fossil_pizza_case_t*)a)->name);
}

static int compare_result_asc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)a)->result - ((fossil_pizza_case_t*)b)->result;
}

static int compare_result_desc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)b)->result - ((fossil_pizza_case_t*)a)->result;
}

static int compare_time_asc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)a)->elapsed_ns - ((fossil_pizza_case_t*)b)->elapsed_ns;
}

static int compare_time_desc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)b)->elapsed_ns - ((fossil_pizza_case_t*)a)->elapsed_ns;
}

void fossil_pizza_sort_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases || suite->count <= 1 || !engine) return;

    int (*compare)(const void*, const void*) = null;

    if (engine->pallet.sort.by) {
        if (pizza_io_cstr_compare(engine->pallet.sort.by, "name") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_name_desc : compare_name_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "result") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_result_desc : compare_result_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "time") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_time_desc : compare_time_asc;
        } else {
            // Invalid sort criteria
            return;
        }
    }

    if (engine->pallet.sort.order) {
        if (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) {
            compare = (compare == compare_name_asc) ? compare_name_desc : compare;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.order, "asc") == 0) {
            compare = (compare == compare_name_desc) ? compare_name_asc : compare;
        }
    }

    if (compare) {
        qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare);
    }
}

// --- Filtering Test Cases ---
size_t fossil_pizza_filter_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine, fossil_pizza_case_t** filtered_cases) {
    if (!suite || !suite->cases || !filtered_cases || !engine) return 0;

    size_t count = 0;
    for (size_t i = 0; i < suite->count; ++i) {
        fossil_pizza_case_t* test_case = &suite->cases[i];

        // Apply filters based on engine->pallet.filter
        if (engine->pallet.filter.test_name && pizza_io_cstr_compare(test_case->name, engine->pallet.filter.test_name) != 0) {
            continue;
        }
        if (engine->pallet.filter.suite_name && pizza_io_cstr_compare(suite->suite_name, engine->pallet.filter.suite_name) != 0) {
            continue;
        }
        if (engine->pallet.filter.tag && (!test_case->tags || !strstr(test_case->tags, engine->pallet.filter.tag))) {
            continue;
        }

        filtered_cases[count++] = test_case;
    }
    return count;
}

// --- Shuffling Test Cases ---
void fossil_pizza_shuffle_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases || suite->count < 2) return;

    unsigned int seed = (engine && engine->pallet.shuffle.seed) 
                        ? (unsigned int)atoi(engine->pallet.shuffle.seed) 
                        : (unsigned int)time(null);
    srand(seed);

    for (size_t i = suite->count - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        fossil_pizza_case_t temp = suite->cases[i];
        suite->cases[i] = suite->cases[j];
        suite->cases[j] = temp;
    }

    if (engine && engine->pallet.shuffle.by) {
        if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "name") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), 
                  (int (*)(const void*, const void*))pizza_io_cstr_compare);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "result") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_result_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "time") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_time_asc);
        }
    }
}

// --- Run One Suite ---
int fossil_pizza_run_suite(const fossil_pizza_engine_t* engine, fossil_pizza_suite_t* suite) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;
    if (suite->setup) suite->setup();

    suite->time_elapsed_ns = fossil_pizza_now_ns();
    suite->total_score = 0;
    suite->total_possible = 0;
    pizza_sys_memory_set(&suite->score, 0, sizeof(suite->score));

    if (!suite->cases) return FOSSIL_PIZZA_FAILURE;

    // Apply filtering, sorting, and shuffling
    fossil_pizza_case_t* filtered_cases[suite->count];
    size_t filtered_count = fossil_pizza_filter_cases(suite, engine, filtered_cases);

    if (filtered_count > 0) {
        fossil_pizza_sort_cases(suite, engine);
        fossil_pizza_shuffle_cases(suite, engine);

        for (size_t i = 0; i < filtered_count; ++i) {
            fossil_pizza_case_t* test_case = filtered_cases[i];
            fossil_pizza_run_test(engine, test_case, suite);
        }
    }

    suite->time_elapsed_ns = fossil_pizza_now_ns() - suite->time_elapsed_ns;

    if (suite->teardown) suite->teardown();
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Run All Suites ---
int fossil_pizza_run_all(fossil_pizza_engine_t* engine) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));
    engine->score_total = 0;
    engine->score_possible = 0;

    for (size_t i = 0; i < engine->count; ++i) {
        fossil_pizza_run_suite(engine, &engine->suites[i]);

        engine->score_total += engine->suites[i].total_score;
        engine->score_possible += engine->suites[i].total_possible;

        // aggregate suite scores
        fossil_pizza_score_t* src = &engine->suites[i].score;
        engine->score.passed     += src->passed;
        engine->score.failed     += src->failed;
        engine->score.skipped    += src->skipped;
        engine->score.timeout    += src->timeout;
        engine->score.unexpected += src->unexpected;
        engine->score.empty      += src->empty;
    }
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Summary Report ---
void fossil_pizza_summary_timestamp(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    uint64_t total_elapsed_ns = 0;
    for (size_t i = 0; i < engine->count; ++i) {
        total_elapsed_ns += engine->suites[i].time_elapsed_ns;
    }

    uint64_t total_elapsed_us = total_elapsed_ns / 1000;
    uint64_t total_elapsed_ms = total_elapsed_us / 1000;
    uint64_t total_elapsed_s = total_elapsed_ms / 1000;
    uint64_t minutes = total_elapsed_s / 60;
    uint64_t seconds = total_elapsed_s % 60;
    uint64_t microseconds = total_elapsed_us % 1000;
    uint64_t nanoseconds = total_elapsed_ns % 1000;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}\n========================================================================={reset}\n");
            pizza_io_printf("{blue,bold}Elapsed Time:{white} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n{reset}",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("{magenta}\n========================================================================={reset}\n");
            pizza_io_printf("{magenta}Elapsed Time:{reset} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("{magenta}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}\n========================================================================={reset}\n");
            pizza_io_printf("{cyan}[Elapsed Time]:{reset} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            pizza_io_printf("{cyan}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("\n# {yellow}Elapsed Time:{reset} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {blue}Elapsed Time:{reset} %llu minutes, %llu seconds, %llu microseconds, %llu nanoseconds\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Elapsed Time{reset}\n");
            pizza_io_printf("{cyan}Minutes:{reset} %llu, {cyan}Seconds:{reset} %llu, {cyan}Microseconds:{reset} %llu, {cyan}Nanoseconds:{reset} %llu\n",
                            minutes, seconds, microseconds, nanoseconds);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display elapsed time.\n");
            break;
    }

    // Calculate averages
    double avg_time_per_suite_ns = (engine->count > 0) ? (double)total_elapsed_ns / engine->count : 0;
    double avg_time_per_test_ns = (engine->score_possible > 0) ? (double)total_elapsed_ns / engine->score_possible : 0;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Average Time per Suite:{white} %.2f nanoseconds\n{reset}", avg_time_per_suite_ns);
            pizza_io_printf("{blue,bold}Average Time per Test :{white} %.2f nanoseconds\n{reset}", avg_time_per_test_ns);
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[Average Time per Suite]: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("[Average Time per Test ]: %.2f nanoseconds\n", avg_time_per_test_ns);
            pizza_io_printf("=========================================================================\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("# Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("# Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[----------] Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("[----------] Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Average Time per Suite: %.2f nanoseconds\n", avg_time_per_suite_ns);
            pizza_io_printf("Average Time per Test : %.2f nanoseconds\n", avg_time_per_test_ns);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display average times.\n");
            break;
    }
}

void fossil_pizza_summary_scoreboard(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    double success_rate = (engine->score_possible > 0) 
                          ? ((double)engine->score_total / engine->score_possible) * 100 
                          : 0;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Suites run:{cyan} %4zu, {blue}Test run:{cyan} %4d, {blue}Score:{cyan} %d/%d\n{reset}",
                engine->count, engine->score_possible, engine->score_total, engine->score_possible);
            pizza_io_printf("{blue}Passed    :{cyan} %4d\n{reset}", engine->score.passed);
            pizza_io_printf("{blue}Failed    :{cyan} %4d\n{reset}", engine->score.failed);
            pizza_io_printf("{blue}Skipped   :{cyan} %4d\n{reset}", engine->score.skipped);
            pizza_io_printf("{blue}Timeouts  :{cyan} %4d\n{reset}", engine->score.timeout);
            pizza_io_printf("{blue}Unexpected:{cyan} %4d\n{reset}", engine->score.unexpected);
            pizza_io_printf("{blue}Empty     :{cyan} %4d\n{reset}", engine->score.empty);
            pizza_io_printf("{blue}Success Rate:{cyan} %.2f%%\n{reset}", success_rate);
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            // Catch2/Doctest themed colors: magenta for headings, green for pass, red for fail, yellow for skip/timeout, cyan for empty
            pizza_io_printf("{magenta}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("{magenta}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("{magenta}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{green}Passed       :{reset} %d\n", engine->score.passed);
            pizza_io_printf("{red}Failed       :{reset} %d\n", engine->score.failed);
            pizza_io_printf("{yellow}Skipped      :{reset} %d\n", engine->score.skipped);
            pizza_io_printf("{yellow}Timeouts     :{reset} %d\n", engine->score.timeout);
            pizza_io_printf("{red}Unexpected   :{reset} %d\n", engine->score.unexpected);
            pizza_io_printf("{cyan}Empty        :{reset} %d\n", engine->score.empty);
            pizza_io_printf("{blue}Success Rate :{reset} %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}[TEST SUMMARY]{reset}\n");
            pizza_io_printf("{blue}[SUITES RUN   ]{reset} %zu\n", engine->count);
            pizza_io_printf("{blue}[TESTS RUN    ]{reset} %d\n", engine->score_possible);
            pizza_io_printf("{blue}[SCORE        ]{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{cyan}[  PASSED     ]{reset} %d\n", engine->score.passed);
            pizza_io_printf("{cyan}[  FAILED     ]{reset} %d\n", engine->score.failed);
            pizza_io_printf("{cyan}[  SKIPPED    ]{reset} %d\n", engine->score.skipped);
            pizza_io_printf("{cyan}[  TIMEOUTS   ]{reset} %d\n", engine->score.timeout);
            pizza_io_printf("{cyan}[UNEXPECTED   ]{reset} %d\n", engine->score.unexpected);
            pizza_io_printf("{cyan}[   EMPTY     ]{reset} %d\n", engine->score.empty);
            pizza_io_printf("{blue}[SUCCESS RATE ]{reset} %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# {yellow}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("# {yellow}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("# {yellow}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("# {green}Passed       :{reset} %d\n", engine->score.passed);
            pizza_io_printf("# {red}Failed       :{reset} %d\n", engine->score.failed);
            pizza_io_printf("# {yellow}Skipped      :{reset} %d\n", engine->score.skipped);
            pizza_io_printf("# {yellow}Timeouts     :{reset} %d\n", engine->score.timeout);
            pizza_io_printf("# {red}Unexpected   :{reset} %d\n", engine->score.unexpected);
            pizza_io_printf("# {cyan}Empty        :{reset} %d\n", engine->score.empty);
            pizza_io_printf("# {blue}Success Rate :{reset} %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {blue}Suites run:{reset} %zu\n", engine->count);
            pizza_io_printf("[----------] {yellow}Tests run :{reset} %d\n", engine->score_possible);
            pizza_io_printf("[==========] {green}Score     :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("[  {green}PASSED{reset}  ] %d tests.\n", engine->score.passed);
            pizza_io_printf("[  {red}FAILED{reset}  ] %d tests.\n", engine->score.failed);
            pizza_io_printf("[  {yellow}SKIPPED{reset} ] %d tests.\n", engine->score.skipped);
            pizza_io_printf("[ {yellow}TIMEOUTS{reset} ] %d tests.\n", engine->score.timeout);
            pizza_io_printf("[{red}UNEXPECTED{reset}] %d tests.\n", engine->score.unexpected);
            pizza_io_printf("[  {cyan}EMPTY{reset}   ] %d tests.\n", engine->score.empty);
            pizza_io_printf("[ {green}SUCCESS{reset}  ] %.2f%%\n", success_rate);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Summary{reset}\n");
            pizza_io_printf("{cyan}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("{cyan}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("{cyan}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{green}Passed       :{reset} %d\n", engine->score.passed);
            pizza_io_printf("{red}Failed       :{reset} %d\n", engine->score.failed);
            pizza_io_printf("{yellow}Skipped      :{reset} %d\n", engine->score.skipped);
            pizza_io_printf("{yellow}Timeouts     :{reset} %d\n", engine->score.timeout);
            pizza_io_printf("{red}Unexpected   :{reset} %d\n", engine->score.unexpected);
            pizza_io_printf("{cyan}Empty        :{reset} %d\n", engine->score.empty);
            pizza_io_printf("{blue}Success Rate :{reset} %.2f%%\n", success_rate);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display scoreboard.\n");
            break;
    }
}

void fossil_pizza_summary_heading(const fossil_pizza_engine_t* engine) {
    pizza_sys_hostinfo_system_t system_info;
    pizza_sys_hostinfo_endianness_t endianness_info;

    pizza_sys_hostinfo_get_system(&system_info);
    pizza_sys_hostinfo_get_endianness(&endianness_info);

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            pizza_io_printf("{blue}==={cyan} Fossil Pizza Summary {blue}===: os{magenta} %s {blue}endianess:{magenta} %s {reset}\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("{blue,bold}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("{magenta}========================================================================={reset}\n");
            pizza_io_printf("{magenta}=== Fossil Pizza Summary ===:{reset} os {cyan}%s{reset} endianess: {cyan}%s{reset}\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("{magenta}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}========================================================================={reset}\n");
            pizza_io_printf("{cyan}[Fossil Pizza Summary]{reset}: os {blue}%s{reset} endianess: {blue}%s{reset}\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            pizza_io_printf("{cyan}========================================================================={reset}\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# {yellow}Fossil Pizza Summary{reset}: os {cyan}%s{reset} endianess: {cyan}%s{reset}\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        case PIZZA_THEME_GOOGLETEST:
            // Google Test themed colors: blue, red, yellow, green (Google logo colors)
            pizza_io_printf("[==========] {blue}F{red}o{yellow}s{green}s{blue}i{red}l {yellow}P{green}i{blue}z{red}z{yellow}a {green}S{blue}u{red}m{yellow}m{green}a{blue}r{red}y{reset}\n");
            pizza_io_printf("[----------] OS: %s, Endianess: %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Summary{reset}\n");
            pizza_io_printf("{cyan}OS:{reset} %s, {cyan}Endianess:{reset} %s\n",
                system_info.os_name, endianness_info.is_little_endian ? "Little-endian" : "Big-endian");
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display heading.\n");
            break;
    }
}

void fossil_pizza_summary(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    fossil_pizza_summary_heading(engine);
    fossil_pizza_summary_scoreboard(engine);
    fossil_pizza_summary_timestamp(engine);
}

// --- End / Cleanup ---
int32_t fossil_pizza_end(fossil_pizza_engine_t* engine) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;
    for (size_t i = 0; i < engine->count; ++i) {
        fossil_pizza_suite_t* suite = &engine->suites[i];
        if (suite->cases) {
            for (size_t j = 0; j < suite->count; ++j) {
                fossil_pizza_case_t* test_case = &suite->cases[j];
                if (test_case->teardown) {
                    test_case->teardown();
                }
            }
            pizza_sys_memory_free(suite->cases);
        }
    }
    pizza_sys_memory_free(engine->suites);
    return FOSSIL_PIZZA_SUCCESS;
}

// -- Assume --

typedef struct {
    char *message;
    uint8_t hash[FOSSIL_PIZZA_HASH_SIZE];
    uint64_t timestamp;
} pizza_assert_ti_result;

extern uint64_t get_pizza_time_microseconds(void); // from common utilities

char *pizza_test_assert_messagef(const char *message, ...) {
    va_list args;
    va_start(args, message);

    size_t buffer_size = 1024;
    char *formatted_message = (char *)pizza_sys_memory_alloc(buffer_size);

    pizza_assert_ti_result result = {0};

    if (formatted_message) {
        pizza_io_vsnprintf(formatted_message, buffer_size, message, args);
        formatted_message[buffer_size - 1] = '\0'; // Ensure null-termination

        // TI upgrade: compute hash and timestamp
        result.message = formatted_message;
        result.timestamp = get_pizza_time_microseconds();

        // Hash both format string and final message to detect templating vs content errors
        fossil_pizza_hash(message, formatted_message, result.hash);
    }

    va_end(args);
    return formatted_message;
}

void pizza_test_assert_internal_output(const char *message, const char *file, int line, const char *func, int anomaly_count) {
    // Output assertion failure based on theme
    switch (G_PIZZA_THEME) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{red,bold}Assertion failed:{reset} {yellow}%s{reset} {blue}(%s:%d in %s){reset}\n",
                            message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("{yellow}Duplicate or similar assertion detected [Anomaly Count: %d]{reset}\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[ASSERTION FAILED] %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("[DUPLICATE ASSERTION] Anomaly Count: %d\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("not ok - Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("# Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[  FAILED  ] Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("[  WARNING ] Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Assertion Failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Unity Duplicate Assertion Detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        default:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (anomaly_count > 0) {
                pizza_io_printf("Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;
    }
}

static int pizza_test_assert_internal_detect_ti(const char *message, const char *file, int line, const char *func) {
    static uint8_t last_hash[FOSSIL_PIZZA_HASH_SIZE] = {0};
    static int anomaly_count = 0;

    char input_buf[512], output_buf[64];
    snprintf(input_buf, sizeof(input_buf), "%s:%d:%s", file, line, func);
    snprintf(output_buf, sizeof(output_buf), "%s", message);

    uint8_t current_hash[FOSSIL_PIZZA_HASH_SIZE];
    fossil_pizza_hash(input_buf, output_buf, current_hash);

    bool same_hash = memcmp(last_hash, current_hash, FOSSIL_PIZZA_HASH_SIZE) == 0;

    if (same_hash) {
        anomaly_count++;
    } else {
        anomaly_count = 0;
        memcpy(last_hash, current_hash, FOSSIL_PIZZA_HASH_SIZE);
    }

    return anomaly_count;
}

void pizza_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
    _ASSERT_COUNT++;

    if (!condition) {
        int anomaly_count = pizza_test_assert_internal_detect_ti(message, file, line, func);

        // Enhanced output can include anomaly count and possibly hashed context
        pizza_test_assert_internal_output(message, file, line, func, anomaly_count);

        longjmp(test_jump_buffer, 1);
    }
}


// *********************************************************************************************
// internal messages
// *********************************************************************************************

void _given(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}Given %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("Given: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[GIVEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# Given: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] Given: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity Given: %s\n", description);
                break;
            default:
                pizza_io_printf("Given: %s\n", description);
                break;
        }
    }
}

void _when(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}When %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("When: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[WHEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# When: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] When: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity When: %s\n", description);
                break;
            default:
                pizza_io_printf("When: %s\n", description);
                break;
        }
    }
}

void _then(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{blue}Then %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("Then: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[THEN] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# Then: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[----------] Then: %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity Then: %s\n", description);
                break;
            default:
                pizza_io_printf("Then: %s\n", description);
                break;
        }
    }
}

void _on_skip(const char *description) {
    if (description) {
        switch (G_PIZZA_THEME) {
            case PIZZA_THEME_FOSSIL:
                pizza_io_printf("{yellow}On Skip %s{reset}\n", description);
                break;
            case PIZZA_THEME_CATCH:
            case PIZZA_THEME_DOCTEST:
                pizza_io_printf("On Skip: %s\n", description);
                break;
            case PIZZA_THEME_CPPUTEST:
                pizza_io_printf("[SKIP] %s\n", description);
                break;
            case PIZZA_THEME_TAP:
                pizza_io_printf("# On Skip: %s\n", description);
                break;
            case PIZZA_THEME_GOOGLETEST:
                pizza_io_printf("[ SKIPPED ] %s\n", description);
                break;
            case PIZZA_THEME_UNITY:
                pizza_io_printf("Unity On Skip: %s\n", description);
                break;
            default:
                pizza_io_printf("On Skip: %s\n", description);
                break;
        }
    }
}
