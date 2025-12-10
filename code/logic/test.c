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

    engine->suites = NULL;
    engine->count = 0;
    engine->capacity = 0;
    engine->score_total = 0;
    engine->score_possible = 0;

    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));

    engine->pallet = fossil_pizza_pallet_create(argc, argv);

    // --- TI Meta Initialization ---
    engine->meta.hash = NULL;
    engine->meta.prev_hash = NULL;
    engine->meta.timestamp = time(NULL);
    engine->meta.origin_device_id = "unknown";
    engine->meta.author = "anonymous";
    engine->meta.trust_score = 0.0;
    engine->meta.confidence = 0.0;
    engine->meta.immutable = false;
    engine->meta.signature = NULL;

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

    // Resize if needed
    if (engine->count >= engine->capacity) {
        size_t new_cap = engine->capacity ? engine->capacity * 2 : 4;
        fossil_pizza_suite_t* resized = pizza_sys_memory_realloc(engine->suites, new_cap * sizeof(*engine->suites));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        engine->suites = resized;
        engine->capacity = new_cap;
    }

    // --- TI Metadata Initialization ---
    suite.meta.timestamp = time(NULL);
    if (!suite.meta.origin_device_id) suite.meta.origin_device_id = "unknown";
    if (!suite.meta.author)           suite.meta.author = "anonymous";

    suite.meta.trust_score = 0.0;
    suite.meta.confidence  = 0.0;
    suite.meta.immutable   = false;

    // Previous hash from engine
    char* prev_hash = engine->meta.hash ? engine->meta.hash : "";
    suite.meta.prev_hash = prev_hash;

    // Prepare input string
    char input_buf[1000] = {0};
    if (!pizza_io_cstr_append(input_buf, sizeof(input_buf), suite.suite_name) ||
        !pizza_io_cstr_append(input_buf, sizeof(input_buf), suite.meta.author) ||
        !pizza_io_cstr_append(input_buf, sizeof(input_buf), suite.meta.origin_device_id)) {
        return FOSSIL_PIZZA_FAILURE;
    }

    // Compute hash
    uint8_t hash_raw[32];
    fossil_pizza_hash(input_buf, prev_hash, hash_raw);

    // Convert to hex
    char* hash_hex = pizza_sys_memory_alloc(65);
    if (!hash_hex) return FOSSIL_PIZZA_FAILURE;

    static const char hex[] = "0123456789abcdef";
    for (int i = 0; i < 32; ++i) {
        hash_hex[i * 2]     = hex[(hash_raw[i] >> 4) & 0xF];
        hash_hex[i * 2 + 1] = hex[hash_raw[i] & 0xF];
    }
    hash_hex[64] = '\0';
    suite.meta.hash = hash_hex;

    // Add to engine
    engine->suites[engine->count++] = suite;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Add Case ---
#define FOSSIL_PIZZA_HASH_HEX_LEN 65

int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case) {
    if (!suite) return FOSSIL_PIZZA_FAILURE;

    // Resize case array if needed
    if (suite->count >= suite->capacity) {
        size_t new_cap = suite->capacity ? suite->capacity * 2 : 4;
        fossil_pizza_case_t* resized = pizza_sys_memory_realloc(suite->cases, new_cap * sizeof(*suite->cases));
        if (!resized) return FOSSIL_PIZZA_FAILURE;
        suite->cases = resized;
        suite->capacity = new_cap;
    }

    // --- TI Metadata Initialization ---
    test_case.meta.timestamp = time(NULL);
    test_case.meta.origin_device_id = test_case.meta.origin_device_id ? test_case.meta.origin_device_id : "unknown";
    test_case.meta.author = test_case.meta.author ? test_case.meta.author : "anonymous";
    test_case.meta.trust_score = 0.0;
    test_case.meta.confidence = 0.0;
    test_case.meta.immutable = false;

    // Link to suite’s hash as previous
    test_case.meta.prev_hash = suite->meta.hash ? suite->meta.hash : NULL;

    // Prepare input string
    char input_buf[1000] = {0};
    if (!pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case.name) ||
        !pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case.criteria) ||
        !pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case.meta.author)) {
        return FOSSIL_PIZZA_FAILURE; // Overflow occurred
    }

    // Compute hash
    uint8_t hash_raw[32];
    char* prev_hash = test_case.meta.prev_hash ? test_case.meta.prev_hash : "";
    fossil_pizza_hash(input_buf, prev_hash, hash_raw);

    // Convert hash to hex string
    char* hash_hex = pizza_sys_memory_alloc(FOSSIL_PIZZA_HASH_HEX_LEN);
    if (!hash_hex) return FOSSIL_PIZZA_FAILURE;

    for (int i = 0; i < 32; ++i)
        sprintf(&hash_hex[i * 2], "%02x", hash_raw[i]);

    test_case.meta.hash = hash_hex;

    // Add test case to suite
    suite->cases[suite->count++] = test_case;
    return FOSSIL_PIZZA_SUCCESS;
}

// --- Update Score ---
void fossil_pizza_update_score(fossil_pizza_case_t* test_case, fossil_pizza_suite_t* suite) {
    if (!test_case || !suite) return;

    // --- Set result timestamp ---
    test_case->meta.timestamp = time(NULL);

    // --- Update individual suite score ---
    switch (test_case->result) {
        case FOSSIL_PIZZA_CASE_PASS:
            suite->score.passed++;
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

    // --- Recompute suite totals for safety ---
    suite->total_score = suite->score.passed;
    suite->total_possible = suite->count;

    // --- Build hash input ---
    char input_buf[512] = {0};
    char temp[64];

    pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case->name ? test_case->name : "unnamed");
    pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case->meta.author ? test_case->meta.author : "anonymous");
    pizza_io_cstr_append(input_buf, sizeof(input_buf), test_case->meta.origin_device_id ? test_case->meta.origin_device_id : "unknown");

    snprintf(temp, sizeof(temp), "%d", test_case->result);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%.2f", test_case->meta.trust_score);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%.2f", test_case->meta.confidence);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%lld", (long long)test_case->meta.timestamp);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    // --- Determine previous hash ---
    char* prev_hash = NULL;
    if (suite->count > 0) {
        fossil_pizza_case_t* last_case = &suite->cases[suite->count - 1];
        if (last_case != test_case && last_case->meta.hash) {
            prev_hash = last_case->meta.hash;
        }
    }
    test_case->meta.prev_hash = prev_hash;

    // --- Free old hash if present to prevent memory leak ---
    if (test_case->meta.hash) {
        pizza_sys_memory_free(test_case->meta.hash);
        test_case->meta.hash = NULL;
    }

    // --- Compute new hash ---
    uint8_t hash_raw[32];
    fossil_pizza_hash(input_buf, prev_hash ? prev_hash : "", hash_raw);

    char* hash_hex = pizza_sys_memory_alloc(65);
    if (!hash_hex) return;

    for (int i = 0; i < 32; ++i)
        snprintf(&hash_hex[i * 2], 3, "%02x", hash_raw[i]);

    test_case->meta.hash = hash_hex;
}

void fossil_pizza_cleanup_suite(fossil_pizza_suite_t* suite) {
    if (!suite) return;
    for (size_t i = 0; i < suite->count; ++i) {
        if (suite->cases[i].meta.hash) {
            pizza_sys_memory_free(suite->cases[i].meta.hash);
            suite->cases[i].meta.hash = NULL;
        }
    }
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

void fossil_pizza_show_cases(const fossil_pizza_suite_t* suite, const fossil_pizza_case_t* test_case, const fossil_pizza_engine_t* engine) {
    if (!test_case) return;

    // Determine mode (list, tree, graph), default to list
    const char* mode = (engine && engine->pallet.show.mode) ? engine->pallet.show.mode : "list";

    const char* result_str =
                (test_case->result == FOSSIL_PIZZA_CASE_EMPTY)      ? "{cyan}empty{reset}" :
                (test_case->result == FOSSIL_PIZZA_CASE_PASS)       ? "{green}pass{reset}" :
                (test_case->result == FOSSIL_PIZZA_CASE_FAIL)       ? "{red}fail{reset}" :
                (test_case->result == FOSSIL_PIZZA_CASE_TIMEOUT)    ? "{yellow}timeout{reset}" :
                (test_case->result == FOSSIL_PIZZA_CASE_SKIPPED)    ? "{yellow}skipped{reset}" :
                (test_case->result == FOSSIL_PIZZA_CASE_UNEXPECTED) ? "{magenta}unexpected{reset}" : "{white}unknown{reset}";

    // Filtering logic
    if (engine && engine->pallet.show.test_name && pizza_io_cstr_compare(test_case->name, engine->pallet.show.test_name) != 0)
        return;
    if (engine && engine->pallet.show.suite_name && pizza_io_cstr_compare(suite->suite_name, engine->pallet.show.suite_name) != 0)
        return;
    if (engine && engine->pallet.show.tag && (!test_case->tags || !strstr(test_case->tags, engine->pallet.show.tag)))
        return;
    if (engine && engine->pallet.show.result) {
        if (pizza_io_cstr_compare(result_str, engine->pallet.show.result) != 0)
            return;
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
                pizza_io_printf("  {blue}│   └─{reset} {cyan}Result  {reset}: %s {yellow}[the result]{reset}\n", result_str);
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
                pizza_io_printf("  {blue}│   └─{reset} {cyan}Result  {reset}: %s\n", result_str);
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
                pizza_io_printf("  {yellow}# │   └─{reset} {cyan}Result   {reset}: %s {yellow}[the result]{reset}\n", result_str);
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
                pizza_io_printf("  {yellow}# │   └─{reset} {cyan}Result   {reset}: %s\n", result_str);
            }
            break;
        case PIZZA_THEME_GOOGLETEST:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                // Google Test themed colors: blue, red, yellow, green (Google logo colors)
                pizza_io_printf("  {blue}[----------]{reset} {cyan}%s{reset} {red}[test case]{reset}\n", test_case->name);
                pizza_io_printf("    {yellow}[Tags]{reset} {green}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                pizza_io_printf("    {yellow}[Criteria]{reset} {green}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                pizza_io_printf("    {yellow}[Time]{reset} {green}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                pizza_io_printf("    {yellow}[Result]{reset} %s {yellow}[the result]{reset}\n", result_str);
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
                pizza_io_printf("    {yellow}[Result]{reset} %s\n", result_str);
            }
            break;
        case PIZZA_THEME_UNITY:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf("  {green}Unity Case:{reset} {cyan}%s{reset} {yellow}[test case]{reset}\n", test_case->name);
                pizza_io_printf("    {yellow}Tags    {reset}: {white}%s{reset} {yellow}[with tag]{reset}\n", test_case->tags);
                pizza_io_printf("    {yellow}Criteria{reset}: {white}%s{reset} {yellow}[given criteria]{reset}\n", test_case->criteria);
                pizza_io_printf("    {yellow}Time    {reset}: {white}%s{reset} {yellow}[the time]{reset}\n", fossil_pizza_format_ns(test_case->elapsed_ns));
                pizza_io_printf("    {yellow}Result  {reset}: %s {yellow}[the result]{reset}\n", result_str);
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
                pizza_io_printf("    {yellow}Result  {reset}: %s\n", result_str);
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
                pizza_io_printf("{blue}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}%s {yellow}[the result]{reset}]\n",
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
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}%s {yellow}[the result]{reset}]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else { // plain or default
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        case PIZZA_THEME_TAP:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf("{yellow}# [CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}%s {yellow}[the result]{reset}]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("{yellow}# ::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else {
                pizza_io_printf("{yellow}# [CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        case PIZZA_THEME_GOOGLETEST:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                // Google Test themed colors: blue, red, yellow, green (Google logo colors)
                pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} {red}[test case]{reset} --[{yellow}tags:{reset} {green}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset} {green}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset} {green}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset} %s {yellow}[the result]{reset}]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("[  CASE   ] ::CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else {
                pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} --[{yellow}tags:{reset} {green}%s{reset},{yellow}criteria:{reset} {green}%s{reset},{yellow}time:{reset} {green}%s{reset},{yellow}result:{reset} %s]\n",
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
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset}%s {yellow}[the result]{reset}]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} --[{yellow}::TAGS::{reset}{white} %s{reset},{yellow}::CRITERIA::{reset}{white} %s{reset},{yellow}::TIME::{reset}{white} %s{reset},{yellow}::RESULT::{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else {
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        default:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf("{blue}- {reset}{cyan}%s{reset} {yellow}[test case]{reset} --[{yellow}tags:{reset}{white}%s{reset} {yellow}[with tag]{reset},{yellow}criteria:{reset}{white}%s{reset} {yellow}[given criteria]{reset},{yellow}time:{reset}{white}%s{reset} {yellow}[the time]{reset},{yellow}result:{reset} %s {yellow}[the result]{reset}]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("::CASE:: %s --[::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else {
                pizza_io_printf("{blue}- {reset}{cyan}%s{reset} --[{yellow}tags:{reset}{white}%s{reset},{yellow}criteria:{reset}{white}%s{reset},{yellow}time:{reset}{white}%s{reset},{yellow}result:{reset} %s]\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        }
    } else { // list (default)
        switch (engine ? engine->pallet.theme : PIZZA_THEME_FOSSIL) {
        case PIZZA_THEME_FOSSIL:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf(" {blue}-{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} %s {yellow}[the result]{reset})\n",
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
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} %s {yellow}[the result]{reset})\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} ( {yellow}::TAGS::{reset} {white}%s{reset}, {yellow}::CRITERIA::{reset} {white}%s{reset}, {yellow}::TIME::{reset} {white}%s{reset}, {yellow}::RESULT::{reset} %s )\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else { // plain or default
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} %s)\n",
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
                pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} {red}[test case]{reset} ({yellow}Tags:{reset} {green}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {green}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {green}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} %s {yellow}[the result]{reset})\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("[  CASE   ] ::CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else { // plain or default
                pizza_io_printf("{blue}[  CASE   ]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {green}%s{reset}, {yellow}Criteria:{reset} {green}%s{reset}, {yellow}Time:{reset} {green}%s{reset}, {yellow}Result:{reset} %s)\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        case PIZZA_THEME_UNITY:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf("{green}Unity Case:{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} %s {yellow}[the result]{reset})\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf(" ::UNITY_CASE:: %s ( ::TAGS:: %s, ::CRITERIA:: %s, ::TIME:: %s, ::RESULT:: %s )\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else { // plain or default
                pizza_io_printf("{green}Unity Case:{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} %s)\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            }
            break;
        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "doge") == 0) {
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} {yellow}[test case]{reset} ({yellow}Tags:{reset} {white}%s{reset} {yellow}[with tag]{reset}, {yellow}Criteria:{reset} {white}%s{reset} {yellow}[given criteria]{reset}, {yellow}Time:{reset} {white}%s{reset} {yellow}[the time]{reset}, {yellow}Result:{reset} %s {yellow}[the result]{reset})\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else if (engine && engine->pallet.show.verbose && pizza_io_cstr_compare(engine->pallet.show.verbose, "ci") == 0) {
                pizza_io_printf("{magenta}::CASE::{reset} {cyan}%s{reset} ( {yellow}::TAGS::{reset} {white}%s{reset}, {yellow}::CRITERIA::{reset} {white}%s{reset}, {yellow}::TIME::{reset} {white}%s{reset}, {yellow}::RESULT::{reset} %s )\n",
                    test_case->name, test_case->tags, test_case->criteria, fossil_pizza_format_ns(test_case->elapsed_ns), result_str);
            } else { // plain or default
                pizza_io_printf("{magenta}[CASE]{reset} {cyan}%s{reset} ({yellow}Tags:{reset} {white}%s{reset}, {yellow}Criteria:{reset} {white}%s{reset}, {yellow}Time:{reset} {white}%s{reset}, {yellow}Result:{reset} %s)\n",
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

// --- Run One Test ---

// Utility function to convert seconds to nanoseconds
static uint64_t seconds_to_nanoseconds(uint64_t seconds) {
    return seconds * 1000000000ULL;
}

// from sanity, should be implemented and placed in common.c
extern uint64_t get_pizza_time_microseconds(void);


void fossil_pizza_run_test(const fossil_pizza_engine_t* engine,
                           fossil_pizza_case_t* test_case,
                           fossil_pizza_suite_t* suite) {
    if (!test_case || !suite || !engine) return;

    // --- Filter: --only ---
    if (engine->pallet.run.only &&
        pizza_io_cstr_compare(engine->pallet.run.only, test_case->name) != 0) {
        return;
    }

    // --- Filter: --skip ---
    if (engine->pallet.run.skip &&
        pizza_io_cstr_compare(engine->pallet.run.skip, test_case->name) == 0) {
        test_case->result = FOSSIL_PIZZA_CASE_SKIPPED;
        fossil_pizza_update_score(test_case, suite);
        return;
    }

    size_t repeat_count =
        (size_t)(engine->pallet.run.repeat > 0 ? engine->pallet.run.repeat : 1);

    for (size_t i = 0; i < repeat_count; ++i) {
        if (test_case->setup) test_case->setup();

        test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
        _ASSERT_COUNT = 0; // Reset before running test
        uint64_t start_time = fossil_pizza_now_ns();

        if (test_case->run) {
            if (setjmp(test_jump_buffer) == 0) {
                test_case->run();

                uint64_t end_time = fossil_pizza_now_ns();
                uint64_t elapsed = end_time - start_time;
                test_case->elapsed_ns = elapsed;

                #ifndef FOSSIL_PIZZA_TIMEOUT
                #define FOSSIL_PIZZA_TIMEOUT 60
                #endif

                if (elapsed > seconds_to_nanoseconds(FOSSIL_PIZZA_TIMEOUT)) {
                    test_case->result = FOSSIL_PIZZA_CASE_TIMEOUT;
                } else if (_ASSERT_COUNT == 0) {
                    test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
                } else {
                    test_case->result = FOSSIL_PIZZA_CASE_PASS;
                }

            } else {
                test_case->result = FOSSIL_PIZZA_CASE_FAIL;
                test_case->elapsed_ns = fossil_pizza_now_ns() - start_time;

                if (engine->pallet.run.fail_fast) {
                    fossil_pizza_update_score(test_case, suite);
                    fossil_pizza_show_cases(suite, test_case, engine);
                    return;
                }
            }
        } else {
            test_case->result = FOSSIL_PIZZA_CASE_EMPTY;
            test_case->elapsed_ns = 0;
        }

        if (test_case->teardown) test_case->teardown();
    }

    fossil_pizza_update_score(test_case, suite);
    fossil_pizza_show_cases(suite, test_case, engine);
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

static int compare_priority_asc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)a)->priority - ((fossil_pizza_case_t*)b)->priority;
}

static int compare_priority_desc(const void* a, const void* b) {
    return ((fossil_pizza_case_t*)b)->priority - ((fossil_pizza_case_t*)a)->priority;
}

static int compare_hash_asc(const void* a, const void* b) {
    return memcmp(((fossil_pizza_case_t*)a)->meta.hash, ((fossil_pizza_case_t*)b)->meta.hash, FOSSIL_PIZZA_HASH_SIZE);
}

static int compare_hash_desc(const void* a, const void* b) {
    return memcmp(((fossil_pizza_case_t*)b)->meta.hash, ((fossil_pizza_case_t*)a)->meta.hash, FOSSIL_PIZZA_HASH_SIZE);
}

void fossil_pizza_sort_cases(fossil_pizza_suite_t* suite, const fossil_pizza_engine_t* engine) {
    if (!suite || !suite->cases || suite->count <= 1 || !engine) return;

    int (*compare)(const void*, const void*) = NULL;

    if (engine->pallet.sort.by) {
        if (pizza_io_cstr_compare(engine->pallet.sort.by, "name") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_name_desc : compare_name_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "result") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_result_desc : compare_result_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "time") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_time_desc : compare_time_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "priority") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_priority_desc : compare_priority_asc;
        } else if (pizza_io_cstr_compare(engine->pallet.sort.by, "hash") == 0) {
            compare = (pizza_io_cstr_compare(engine->pallet.sort.order, "desc") == 0) ? compare_hash_desc : compare_hash_asc;
        } else {
            // Invalid sort criteria
            return;
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
                        : (unsigned int)time(NULL);
    srand(seed);

    // Fisher-Yates shuffle
    for (size_t i = suite->count - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        fossil_pizza_case_t temp = suite->cases[i];
        suite->cases[i] = suite->cases[j];
        suite->cases[j] = temp;
    }

    // Optional secondary shuffle/sort by field
    if (engine && engine->pallet.shuffle.by) {
        if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "name") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_name_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "result") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_result_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "time") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_time_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "priority") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_priority_asc);
        } else if (pizza_io_cstr_compare(engine->pallet.shuffle.by, "hash") == 0) {
            qsort(suite->cases, suite->count, sizeof(fossil_pizza_case_t), compare_hash_asc);
        }
    }
}

// --- Run One Suite ---
int fossil_pizza_run_suite(const fossil_pizza_engine_t* engine, fossil_pizza_suite_t* suite) {
    if (!suite || !suite->cases) return FOSSIL_PIZZA_FAILURE;

    if (suite->setup) suite->setup();

    // --- TI meta timestamp ---
    suite->meta.timestamp = time(NULL);

    // --- Reset suite stats ---
    suite->time_elapsed_ns = fossil_pizza_now_ns();
    suite->total_score = 0;
    suite->total_possible = 0;
    pizza_sys_memory_set(&suite->score, 0, sizeof(suite->score));

    // --- Filtering ---
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

    // --- TI: Generate suite hash ---
    char input_buf[512] = {0};

    // Identity components
    pizza_io_cstr_append(input_buf, sizeof(input_buf), suite->suite_name);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), suite->meta.author ? suite->meta.author : "anonymous");
    pizza_io_cstr_append(input_buf, sizeof(input_buf), suite->meta.origin_device_id ? suite->meta.origin_device_id : "unknown");

    // Execution time
    char temp[64];
    snprintf(temp, sizeof(temp), "%" PRIu64, suite->time_elapsed_ns);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    // Pass/fail stats
    snprintf(temp, sizeof(temp), "%d", suite->score.passed);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);
    snprintf(temp, sizeof(temp), "%d", suite->score.failed);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    // Previous hash (for chaining)
    char* prev_hash = (engine && engine->meta.hash) ? engine->meta.hash : NULL;

    static uint8_t hash_raw[32];
    fossil_pizza_hash(input_buf, prev_hash ? prev_hash : "", hash_raw);

    static char hash_buf[65];
    for (int i = 0; i < 32; ++i)
        snprintf(&hash_buf[i * 2], 3, "%02x", hash_raw[i]);

    suite->meta.hash = hash_buf;
    suite->meta.prev_hash = prev_hash;

    return FOSSIL_PIZZA_SUCCESS;
}

// --- Run All Suites ---
int fossil_pizza_run_all(fossil_pizza_engine_t* engine) {
    if (!engine) return FOSSIL_PIZZA_FAILURE;

    // --- Reset global engine score ---
    pizza_sys_memory_set(&engine->score, 0, sizeof(engine->score));
    engine->score_total = 0;
    engine->score_possible = 0;

    // --- TI: Record engine-level timestamp ---
    engine->meta.timestamp = time(NULL);

    // --- Run all test suites ---
    for (size_t i = 0; i < engine->count; ++i) {
        fossil_pizza_run_suite(engine, &engine->suites[i]);

        engine->score_total    += engine->suites[i].total_score;
        engine->score_possible += engine->suites[i].total_possible;

        const fossil_pizza_score_t* src = &engine->suites[i].score;
        engine->score.passed     += src->passed;
        engine->score.failed     += src->failed;
        engine->score.skipped    += src->skipped;
        engine->score.timeout    += src->timeout;
        engine->score.unexpected += src->unexpected;
        engine->score.empty      += src->empty;
    }

    // --- TI: Generate engine hash ---
    char input_buf[512] = {0};
    pizza_io_cstr_append(input_buf, sizeof(input_buf), engine->meta.author ? engine->meta.author : "anonymous");
    pizza_io_cstr_append(input_buf, sizeof(input_buf), engine->meta.origin_device_id ? engine->meta.origin_device_id : "unknown");

    char temp[64];
    snprintf(temp, sizeof(temp), "%d", engine->score_total);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%d", engine->score_possible);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%d", engine->score.passed);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    snprintf(temp, sizeof(temp), "%d", engine->score.failed);
    pizza_io_cstr_append(input_buf, sizeof(input_buf), temp);

    // Chain from last suite hash (if any)
    char* prev_hash = NULL;
    if (engine->count > 0 && engine->suites[engine->count - 1].meta.hash) {
        prev_hash = engine->suites[engine->count - 1].meta.hash;
    }

    static uint8_t hash_raw[32];
    fossil_pizza_hash(input_buf, prev_hash ? prev_hash : "", hash_raw);

    static char hash_buf[65];
    for (int i = 0; i < 32; ++i)
        snprintf(&hash_buf[i * 2], 3, "%02x", hash_raw[i]);

    engine->meta.hash = hash_buf;
    engine->meta.prev_hash = prev_hash;

    return FOSSIL_PIZZA_SUCCESS;
}

// --- Summary Report ---

const char* fossil_test_summary_feedback(const fossil_pizza_score_t* score) {
    if (!score) return "No results available.";

    static char message[512];
    int total = score->passed + score->failed + score->skipped +
                score->timeout + score->unexpected + score->empty;

    if (total == 0) return "No tests were run.";

    double pass_rate = (double)score->passed / total * 100.0;
    double fail_rate = (double)(score->failed + score->unexpected) / total * 100.0;

    // --- AI-Style Feedback Pool (300 responses) ---
    static const char* ai_feedback[] = {
        // 0-29: Perfect
        "Outstanding! All tests passed. Your code is a masterpiece.",
        "Flawless execution. Every test succeeded.",
        "Perfect score! Your code is robust and reliable.",
        "All green! No issues detected.",
        "Impeccable work. Every test case passed.",
        "100% success rate. Your code is production-ready.",
        "No failures, no warnings. Just perfection.",
        "All systems go. Excellent job.",
        "Every test passed. You nailed it.",
        "Zero defects. Your code is solid.",
        "All assertions succeeded. Superb quality.",
        "No errors found. Your code is pristine.",
        "All tests green. Keep up the great work.",
        "No bugs detected. Your code is clean.",
        "All cases passed. Outstanding reliability.",
        "Perfect run. Your code is bulletproof.",
        "No failures. Your code is top-notch.",
        "All checks passed. Excellent engineering.",
        "No issues found. Your code is exemplary.",
        "All tests succeeded. You're on fire.",
        "Flawless test results. Well done.",
        "No problems detected. Your code is stellar.",
        "All cases green. Fantastic job.",
        "Zero issues. Your code is impeccable.",
        "All tests passed. You're a coding wizard.",
        "No errors. Your code is rock solid.",
        "All assertions true. Brilliant work.",
        "No failures. Your code is perfect.",
        "All tests green. You're unstoppable.",
        "100% pass rate. Legendary performance.",

        // 30-59: Near-perfect
        "Almost perfect! Just a minor issue.",
        "Great job! Only a tiny hiccup.",
        "Excellent work. Nearly all tests passed.",
        "Just one test failed. Review for edge cases.",
        "Superb effort. One small fix needed.",
        "Very strong results. Minor improvement possible.",
        "Almost flawless. One test needs attention.",
        "Fantastic job. Just a single failure.",
        "Impressive! Only one test didn't pass.",
        "Nearly there. One case to review.",
        "Strong performance. One test failed.",
        "Excellent coverage. One minor issue.",
        "Great results. One test needs fixing.",
        "Almost all green. One test failed.",
        "Very good. Just one test to check.",
        "Solid code. One test didn't pass.",
        "Strong showing. One case failed.",
        "Great work. One test needs review.",
        "Almost perfect. One test failed.",
        "Very close. One test to address.",
        "Excellent job. One test failed.",
        "Nearly perfect. One test needs work.",
        "Great effort. One test failed.",
        "Almost flawless. One test failed.",
        "Very good results. One test failed.",
        "Strong results. One test failed.",
        "Excellent code. One test failed.",
        "Almost all passed. One test failed.",
        "Great job. One test failed.",
        "Very close to perfect. One test failed.",

        // 60-89: Good/Mixed
        "Good job! Most tests passed.",
        "Solid effort. A few tests failed.",
        "Strong results. Some improvements needed.",
        "Most tests succeeded. Review failures.",
        "Good coverage. Address failed cases.",
        "Nice work. Some tests need attention.",
        "Majority passed. Check failed tests.",
        "Good performance. Some failures detected.",
        "Most cases green. Review the rest.",
        "Solid code. Some tests failed.",
        "Good results. Some issues remain.",
        "Most tests passed. Fix the rest.",
        "Nice job. Some tests failed.",
        "Majority succeeded. Review failures.",
        "Good showing. Some tests failed.",
        "Most cases passed. Address failures.",
        "Solid results. Some tests failed.",
        "Good work. Some tests failed.",
        "Most tests green. Some failed.",
        "Nice effort. Some tests failed.",
        "Majority passed. Some failed.",
        "Good code. Some tests failed.",
        "Most tests succeeded. Some failed.",
        "Solid performance. Some failed.",
        "Good results. Some failed.",
        "Most cases passed. Some failed.",
        "Nice work. Some failed.",
        "Majority succeeded. Some failed.",
        "Good showing. Some failed.",
        "Most tests passed. Some failed.",

        // 90-119: Warning
        "Warning: Significant number of tests failed.",
        "Caution: Many tests did not pass.",
        "Alert: Multiple failures detected.",
        "Review needed: Several tests failed.",
        "Attention: Numerous test failures.",
        "Warning: Code stability at risk.",
        "Caution: High failure rate.",
        "Alert: Many cases failed.",
        "Review: Multiple failures.",
        "Warning: Code needs improvement.",
        "Caution: Several failed tests.",
        "Alert: High number of failures.",
        "Review: Many tests failed.",
        "Warning: Code reliability low.",
        "Caution: Multiple failed cases.",
        "Alert: Numerous failures.",
        "Review: High failure count.",
        "Warning: Code needs attention.",
        "Caution: Many failed tests.",
        "Alert: Several failures.",
        "Review: Code stability low.",
        "Warning: Multiple failures.",
        "Caution: High failure count.",
        "Alert: Code needs review.",
        "Review: Numerous failed tests.",
        "Warning: Code needs fixes.",
        "Caution: Many failures.",
        "Alert: Code needs work.",
        "Review: High failure rate.",
        "Warning: Code needs review.",

        // 120-149: Critical
        "Critical: Most tests failed.",
        "Severe: Code is unstable.",
        "Urgent: Major failures detected.",
        "Critical: Code needs immediate attention.",
        "Severe: High failure rate.",
        "Urgent: Code is unreliable.",
        "Critical: Code is broken.",
        "Severe: Major issues found.",
        "Urgent: Code is failing.",
        "Critical: Code is not working.",
        "Severe: Code is unstable.",
        "Urgent: Code needs fixing.",
        "Critical: Code is failing.",
        "Severe: Code is broken.",
        "Urgent: Code is not reliable.",
        "Critical: Code needs repair.",
        "Severe: Code is not working.",
        "Urgent: Code is unstable.",
        "Critical: Code needs overhaul.",
        "Severe: Code is failing.",
        "Urgent: Code needs attention.",
        "Critical: Code is not stable.",
        "Severe: Code needs fixing.",
        "Urgent: Code is broken.",
        "Critical: Code needs work.",
        "Severe: Code needs repair.",
        "Urgent: Code needs overhaul.",
        "Critical: Code needs fixing.",
        "Severe: Code needs attention.",
        "Urgent: Code needs review.",

        // 150-179: Recovery
        "Recovery needed: Many tests failed.",
        "Action required: Code needs fixes.",
        "Intervention needed: Code is unstable.",
        "Recovery: Code needs improvement.",
        "Action: Code needs repair.",
        "Intervention: Code needs attention.",
        "Recovery: Code needs overhaul.",
        "Action: Code needs fixing.",
        "Intervention: Code needs review.",
        "Recovery: Code needs work.",
        "Action: Code needs repair.",
        "Intervention: Code needs overhaul.",
        "Recovery: Code needs fixing.",
        "Action: Code needs attention.",
        "Intervention: Code needs review.",
        "Recovery: Code needs repair.",
        "Action: Code needs overhaul.",
        "Intervention: Code needs fixing.",
        "Recovery: Code needs attention.",
        "Action: Code needs review.",
        "Intervention: Code needs work.",
        "Recovery: Code needs repair.",
        "Action: Code needs overhaul.",
        "Intervention: Code needs fixing.",
        "Recovery: Code needs attention.",
        "Action: Code needs review.",
        "Intervention: Code needs work.",
        "Recovery: Code needs repair.",
        "Action: Code needs overhaul.",
        "Intervention: Code needs fixing.",

        // 180-209: Encouragement
        "Keep going! Some tests passed.",
        "Don't give up! Progress is being made.",
        "You're on the right track. Keep improving.",
        "Some tests succeeded. Keep working.",
        "Progress detected. Continue refining.",
        "You're making progress. Keep at it.",
        "Some cases passed. Keep going.",
        "Improvement seen. Keep working.",
        "You're getting there. Keep refining.",
        "Some tests succeeded. Keep improving.",
        "Progress made. Continue working.",
        "You're making headway. Keep going.",
        "Some cases succeeded. Keep refining.",
        "Improvement detected. Keep working.",
        "You're on your way. Keep improving.",
        "Some tests passed. Keep going.",
        "Progress noted. Continue refining.",
        "You're making strides. Keep working.",
        "Some cases passed. Keep improving.",
        "Improvement observed. Keep going.",
        "You're moving forward. Keep refining.",
        "Some tests succeeded. Keep working.",
        "Progress achieved. Continue improving.",
        "You're advancing. Keep going.",
        "Some cases succeeded. Keep refining.",
        "Improvement made. Keep working.",
        "You're progressing. Keep improving.",
        "Some tests passed. Keep going.",
        "Progress shown. Continue refining.",
        "You're improving. Keep working.",

        // 210-239: Suggestions
        "Consider reviewing failed tests for edge cases.",
        "Check your logic for possible errors.",
        "Review failed cases for potential bugs.",
        "Investigate failed tests for root causes.",
        "Analyze failures for improvement opportunities.",
        "Check error messages for clues.",
        "Review code for possible mistakes.",
        "Investigate test failures for solutions.",
        "Analyze failed cases for fixes.",
        "Check your code for logic errors.",
        "Review failed tests for debugging.",
        "Investigate failures for corrections.",
        "Analyze failed cases for improvements.",
        "Check your code for possible bugs.",
        "Review failed tests for troubleshooting.",
        "Investigate failures for resolutions.",
        "Analyze failed cases for enhancements.",
        "Check your code for errors.",
        "Review failed tests for analysis.",
        "Investigate failures for fixes.",
        "Analyze failed cases for solutions.",
        "Check your code for improvements.",
        "Review failed tests for insights.",
        "Investigate failures for better results.",
        "Analyze failed cases for optimization.",
        "Check your code for refinements.",
        "Review failed tests for better outcomes.",
        "Investigate failures for better performance.",
        "Analyze failed cases for better reliability.",
        "Check your code for better stability.",

        // 240-269: Motivation
        "Don't be discouraged! Every failure is a learning opportunity.",
        "Keep trying! You'll get there.",
        "Failure is the first step to success.",
        "Every bug fixed is progress made.",
        "Persistence leads to improvement.",
        "Keep pushing! Success is within reach.",
        "Every test failed is a chance to learn.",
        "Don't give up! You're improving.",
        "Failure is feedback. Keep going.",
        "Every mistake is a lesson learned.",
        "Keep working! You'll succeed.",
        "Failure is temporary. Success is permanent.",
        "Every error is a step forward.",
        "Don't stop! You're making progress.",
        "Failure is part of the process.",
        "Every bug is an opportunity.",
        "Keep going! You're getting better.",
        "Failure is not the end.",
        "Every test failed is a chance to grow.",
        "Don't quit! You're on your way.",
        "Failure is a stepping stone.",
        "Every mistake brings you closer to success.",
        "Keep improving! You're making progress.",
        "Failure is just feedback.",
        "Every error is a chance to learn.",
        "Don't lose hope! You're advancing.",
        "Failure is part of learning.",
        "Every bug fixed is a victory.",
        "Keep at it! You're progressing.",
        "Failure is just a detour.",

        // 270-299: Humor
        "Did you try turning it off and on again?",
        "Looks like the bugs are winning this round.",
        "The code elves are on strike.",
        "Have you considered bribing the compiler?",
        "It's not a bug, it's an undocumented feature.",
        "The tests are revolting.",
        "The code gremlins are at it again.",
        "Maybe the tests need more coffee.",
        "The bugs are multiplying.",
        "The code is on vacation.",
        "The tests are playing hide and seek.",
        "The bugs are having a party.",
        "The code is feeling shy.",
        "The tests are on strike.",
        "The bugs are taking over.",
        "The code is in a bad mood.",
        "The tests are confused.",
        "The bugs are celebrating.",
        "The code is lost in thought.",
        "The tests are daydreaming.",
        "The bugs are plotting.",
        "The code is napping.",
        "The tests are distracted.",
        "The bugs are dancing.",
        "The code is meditating.",
        "The tests are philosophizing.",
        "The bugs are writing poetry.",
        "The code is composing music.",
        "The tests are painting.",
        "The bugs are telling jokes."
    };

    // --- AI Feedback Selection Logic ---
    const char* chosen = NULL;
    if (pass_rate == 100.0) {
        chosen = ai_feedback[rand() % 30]; // 0-29: Perfect
    } else if (pass_rate > 90.0) {
        chosen = ai_feedback[30 + rand() % 30]; // 30-59: Near-perfect
    } else if (pass_rate > 70.0) {
        chosen = ai_feedback[60 + rand() % 30]; // 60-89: Good/Mixed
    } else if (fail_rate > 40.0) {
        chosen = ai_feedback[90 + rand() % 30]; // 90-119: Warning
    } else if (fail_rate > 60.0) {
        chosen = ai_feedback[120 + rand() % 30]; // 120-149: Critical
    } else if (pass_rate > 50.0) {
        chosen = ai_feedback[180 + rand() % 30]; // 180-209: Encouragement
    } else if (pass_rate > 30.0) {
        chosen = ai_feedback[210 + rand() % 30]; // 210-239: Suggestions
    } else if (pass_rate > 10.0) {
        chosen = ai_feedback[240 + rand() % 30]; // 240-269: Motivation
    } else {
        chosen = ai_feedback[270 + rand() % 30]; // 270-299: Humor
    }

    // --- Compose Final Message ---
    snprintf(message, sizeof(message), "%s", chosen);

    return message;
}

void fossil_pizza_summary_timestamp(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    // --- Total Elapsed Time Calculation ---
    uint64_t total_elapsed_ns = 0;
    for (size_t i = 0; i < engine->count; ++i) {
        total_elapsed_ns += engine->suites[i].time_elapsed_ns;
    }

    // Derive time components directly from nanoseconds
    uint64_t total_elapsed_s  = total_elapsed_ns / 1000000000ULL;
    uint64_t hours            = total_elapsed_s / 3600;
    uint64_t minutes          = (total_elapsed_s % 3600) / 60;
    uint64_t seconds          = total_elapsed_s % 60;
    uint64_t microseconds     = (total_elapsed_ns / 1000ULL) % 1000000ULL;
    uint64_t nanoseconds_part = total_elapsed_ns % 1000ULL;

    char time_buffer[64];
    snprintf(time_buffer, sizeof(time_buffer),
            "%02llu:%02llu:%02llu.%06llu,%03llu",
            (unsigned long long)hours,
            (unsigned long long)minutes,
            (unsigned long long)seconds,
            (unsigned long long)microseconds,
            (unsigned long long)nanoseconds_part);

    // --- Theme-Aware Elapsed Time Display ---
    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}\n=================================================================================={reset}\n");
            pizza_io_printf("{blue,bold}Elapsed Time:{white} %s (hh:mm:ss.micro,nano)\n{reset}", time_buffer);
            pizza_io_printf("{blue,bold}=================================================================================={reset}\n");
            break;
        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("{magenta}\n=================================================================================={reset}\n");
            pizza_io_printf("{magenta}Elapsed Time:{reset} %s (hh:mm:ss.micro,nano)\n", time_buffer);
            pizza_io_printf("{magenta}=================================================================================={reset}\n");
            break;
        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}\n=================================================================================={reset}\n");
            pizza_io_printf("{cyan}[Elapsed Time]:{reset} %s (hh:mm:ss.micro,nano)\n", time_buffer);
            pizza_io_printf("{cyan}=================================================================================={reset}\n");
            break;
        case PIZZA_THEME_TAP:
            pizza_io_printf("\n# {yellow}Elapsed Time:{reset} %s (hh:mm:ss.micro,nano)\n", time_buffer);
            break;
        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {blue}Elapsed Time:{reset} %s (hh:mm:ss.micro,nano)\n", time_buffer);
            break;
        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Elapsed Time:{reset}\n");
            pizza_io_printf("{cyan}HH:MM:SS:{reset} %02llu:%02llu:%02llu, {cyan}Micro:{reset} %06llu, {cyan}Nano:{reset} %03llu\n",
                            (unsigned long long)hours, (unsigned long long)minutes, (unsigned long long)seconds,
                            (unsigned long long)microseconds, (unsigned long long)nanoseconds_part);
            break;
        default:
            pizza_io_printf("Unknown theme. Unable to display elapsed time.\n");
            break;
    }

    // --- Average Times ---
    if (engine->count == 0 || engine->score_possible == 0) {
        pizza_io_printf("No suites or tests executed; averages not available.\n");
        return;
    }

    double avg_suite_ns = (double)total_elapsed_ns / (double)engine->count;
    double avg_test_ns  = (double)total_elapsed_ns / (double)engine->score_possible;

    double avg_suite_us = avg_suite_ns / 1e3;
    double avg_suite_ms = avg_suite_ns / 1e6;
    double avg_test_us  = avg_test_ns / 1e3;
    double avg_test_ms  = avg_test_ns / 1e6;

    // Theme-aware average reporting
    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Average Time per Suite:{white} %12.2f ns (%8.2f us | %8.3f ms)\n{reset}",
                            avg_suite_ns, avg_suite_us, avg_suite_ms);
            pizza_io_printf("{blue,bold}Average Time per Test :{white} %12.2f ns (%8.2f us | %8.3f ms)\n{reset}",
                            avg_test_ns, avg_test_us, avg_test_ms);
            pizza_io_printf("{blue,bold}=================================================================================={reset}\n");
            break;
        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
        case PIZZA_THEME_UNITY:
            pizza_io_printf("Average Time per Suite: %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_suite_ns, avg_suite_us, avg_suite_ms);
            pizza_io_printf("Average Time per Test : %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_test_ns, avg_test_us, avg_test_ms);
            break;
        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[Average Time per Suite]: %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_suite_ns, avg_suite_us, avg_suite_ms);
            pizza_io_printf("[Average Time per Test ]: %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_test_ns, avg_test_us, avg_test_ms);
            break;
        case PIZZA_THEME_TAP:
            pizza_io_printf("# Average Time per Suite: %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_suite_ns, avg_suite_us, avg_suite_ms);
            pizza_io_printf("# Average Time per Test : %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_test_ns, avg_test_us, avg_test_ms);
            break;
        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[----------] Average Time per Suite: %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_suite_ns, avg_suite_us, avg_suite_ms);
            pizza_io_printf("[----------] Average Time per Test : %12.2f ns (%8.2f µs | %8.3f ms)\n",
                            avg_test_ns, avg_test_us, avg_test_ms);
            break;
        default:
            pizza_io_printf("Unknown theme. Unable to display average times.\n");
            break;
    }
}

void fossil_pizza_summary_scoreboard(const fossil_pizza_engine_t* engine) {
    if (!engine) return;

    int total_tests = engine->score_possible > 0 ? engine->score_possible : 1;
    double pass_pct       = (double)engine->score.passed     / total_tests * 100.0;
    double fail_pct       = (double)engine->score.failed     / total_tests * 100.0;
    double skip_pct       = (double)engine->score.skipped    / total_tests * 100.0;
    double timeout_pct    = (double)engine->score.timeout    / total_tests * 100.0;
    double unexpected_pct = (double)engine->score.unexpected / total_tests * 100.0;
    double empty_pct      = (double)engine->score.empty      / total_tests * 100.0;

    double success_rate = (engine->score_possible > 0) 
                          ? ((double)engine->score_total / engine->score_possible) * 100.0 
                          : 0.0;

    // AI calculations: reliability, anomaly, coverage, stability, risk, health
    double reliability = pass_pct - (fail_pct + unexpected_pct + timeout_pct);
    double anomaly_rate = unexpected_pct + empty_pct;
    double coverage = 100.0 - skip_pct - empty_pct;
    double stability = 100.0 - fail_pct - timeout_pct - unexpected_pct;
    double risk = fail_pct + timeout_pct + unexpected_pct;
    double health = reliability * 0.6 + coverage * 0.2 + stability * 0.2;

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}Suites run:{cyan} %4zu, {blue}Test run:{cyan} %4d, {blue}Score:{cyan} %d/%d\n{reset}",
            engine->count, engine->score_possible, engine->score_total, engine->score_possible);
            pizza_io_printf("{blue}Passed      :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.passed, pass_pct);
            pizza_io_printf("{blue}Failed      :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.failed, fail_pct);
            pizza_io_printf("{blue}Skipped     :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.skipped, skip_pct);
            pizza_io_printf("{blue}Timeouts    :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("{blue}Unexpected  :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("{blue}Empty       :{cyan} %4d {blue}-{cyan}(%06.2f%%){reset}\n", engine->score.empty, empty_pct);
            pizza_io_printf("{blue}Coverage    :{cyan} %06.2f%% {blue}| Stability:{cyan} %06.2f%% {blue}| Health :{cyan} %06.2f%%{reset}\n", coverage, stability, health);
            pizza_io_printf("{blue}Success Rate:{cyan} %06.2f%% {blue}| Risk     :{cyan} %06.2f%% {blue}| Anomaly:{cyan} %06.2f%%{reset}\n", success_rate, risk, anomaly_rate);
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("{magenta}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("{magenta}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("{magenta}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{magenta}Passed       :{reset} {green}%d{reset} ({green}%06.2f%%{reset})\n", engine->score.passed, pass_pct);
            pizza_io_printf("{magenta}Failed       :{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.failed, fail_pct);
            pizza_io_printf("{magenta}Skipped      :{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.skipped, skip_pct);
            pizza_io_printf("{magenta}Timeouts     :{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("{magenta}Unexpected   :{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("{magenta}Empty        :{reset} {cyan}%d{reset} ({cyan}%06.2f%%{reset})\n", engine->score.empty, empty_pct);
            pizza_io_printf("{magenta}Coverage     :{reset} %06.2f%% | Stability: %06.2f%% | Health: %06.2f%%\n", coverage, stability, health);
            pizza_io_printf("{magenta}Success Rate :{reset} {green}%06.2f%%{reset} | Risk: %06.2f%% | Anomaly: %06.2f%%\n", success_rate, risk, anomaly_rate);
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}[TEST SUMMARY]{reset}\n");
            pizza_io_printf("{cyan}[SUITES RUN   ]{reset} %zu\n", engine->count);
            pizza_io_printf("{cyan}[TESTS RUN    ]{reset} %d\n", engine->score_possible);
            pizza_io_printf("{cyan}[SCORE        ]{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{cyan}[  PASSED     ]{reset} {green}%d{reset} ({green}%06.2f%%{reset})\n", engine->score.passed, pass_pct);
            pizza_io_printf("{cyan}[  FAILED     ]{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.failed, fail_pct);
            pizza_io_printf("{cyan}[  SKIPPED    ]{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.skipped, skip_pct);
            pizza_io_printf("{cyan}[  TIMEOUTS   ]{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("{cyan}[UNEXPECTED   ]{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("{cyan}[   EMPTY     ]{reset} {cyan}%d{reset} ({cyan}%06.2f%%{reset})\n", engine->score.empty, empty_pct);
            pizza_io_printf("{cyan}[ COVERAGE    ]{reset} %06.2f%% | [STABILITY] %06.2f%% | [HEALTH] %06.2f%%\n", coverage, stability, health);
            pizza_io_printf("{cyan}[SUCCESS RATE ]{reset} {green}%06.2f%%{reset} | [RISK] %06.2f%% | [ANOMALY] %06.2f%%\n", success_rate, risk, anomaly_rate);
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# {yellow}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("# {yellow}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("# {yellow}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("# {green}Passed       :{reset} %d ({green}%06.2f%%{reset})\n", engine->score.passed, pass_pct);
            pizza_io_printf("# {red}Failed       :{reset} %d ({red}%06.2f%%{reset})\n", engine->score.failed, fail_pct);
            pizza_io_printf("# {yellow}Skipped      :{reset} %d ({yellow}%06.2f%%{reset})\n", engine->score.skipped, skip_pct);
            pizza_io_printf("# {yellow}Timeouts     :{reset} %d ({yellow}%06.2f%%{reset})\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("# {red}Unexpected   :{reset} %d ({red}%06.2f%%{reset})\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("# {cyan}Empty        :{reset} %d ({cyan}%06.2f%%{reset})\n", engine->score.empty, empty_pct);
            pizza_io_printf("# Coverage   : %06.2f%% | Stability: %06.2f%% | Health: %06.2f%%\n", coverage, stability, health);
            pizza_io_printf("# Success Rate: %06.2f%% | Risk: %06.2f%% | Anomaly: %06.2f%%\n", success_rate, risk, anomaly_rate);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {blue}Suites run:{reset} %zu\n", engine->count);
            pizza_io_printf("[----------] {yellow}Tests run :{reset} %d\n", engine->score_possible);
            pizza_io_printf("[==========] {green}Score     :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("[  {green}PASSED{reset}  ] {green}%d{reset} tests ({green}%06.2f%%{reset}).\n", engine->score.passed, pass_pct);
            pizza_io_printf("[  {red}FAILED{reset}  ] {red}%d{reset} tests ({red}%06.2f%%{reset}).\n", engine->score.failed, fail_pct);
            pizza_io_printf("[  {yellow}SKIPPED{reset} ] {yellow}%d{reset} tests ({yellow}%06.2f%%{reset}).\n", engine->score.skipped, skip_pct);
            pizza_io_printf("[ {yellow}TIMEOUTS{reset} ] {yellow}%d{reset} tests ({yellow}%06.2f%%{reset}).\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("[{red}UNEXPECTED{reset}] {red}%d{reset} tests ({red}%06.2f%%{reset}).\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("[  {cyan}EMPTY{reset}   ] {cyan}%d{reset} tests ({cyan}%06.2f%%{reset}).\n", engine->score.empty, empty_pct);
            pizza_io_printf("[ COVERAGE ] %06.2f%% | [STABILITY] %06.2f%% | [HEALTH] %06.2f%%\n", coverage, stability, health);
            pizza_io_printf("[ {green}SUCCESS{reset}  ] {green}%06.2f%%{reset} | [RISK] %06.2f%% | [ANOMALY] %06.2f%%\n", success_rate, risk, anomaly_rate);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Summary{reset}\n");
            pizza_io_printf("{green}Suites run   :{reset} %zu\n", engine->count);
            pizza_io_printf("{green}Tests run    :{reset} %d\n", engine->score_possible);
            pizza_io_printf("{green}Score        :{reset} %d/%d\n", engine->score_total, engine->score_possible);
            pizza_io_printf("{green}Passed       :{reset} {green}%d{reset} ({green}%06.2f%%{reset})\n", engine->score.passed, pass_pct);
            pizza_io_printf("{green}Failed       :{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.failed, fail_pct);
            pizza_io_printf("{green}Skipped      :{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.skipped, skip_pct);
            pizza_io_printf("{green}Timeouts     :{reset} {yellow}%d{reset} ({yellow}%06.2f%%{reset})\n", engine->score.timeout, timeout_pct);
            pizza_io_printf("{green}Unexpected   :{reset} {red}%d{reset} ({red}%06.2f%%{reset})\n", engine->score.unexpected, unexpected_pct);
            pizza_io_printf("{green}Empty        :{reset} {cyan}%d{reset} ({cyan}%06.2f%%{reset})\n", engine->score.empty, empty_pct);
            pizza_io_printf("{green}Coverage     :{reset} %06.2f%% | Stability: %06.2f%% | Health: %06.2f%%\n", coverage, stability, health);
            pizza_io_printf("{green}Success Rate :{reset} {green}%06.2f%%{reset} | Risk: %06.2f%% | Anomaly: %06.2f%%\n", success_rate, risk, anomaly_rate);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display scoreboard.\n");
            break;
    }
}

void fossil_pizza_summary_heading(const fossil_pizza_engine_t* engine) {
    pizza_sys_hostinfo_system_t system_info;
    pizza_sys_hostinfo_endianness_t endianness_info;
    pizza_sys_hostinfo_architecture_t arch_info;

    pizza_sys_hostinfo_get_system(&system_info);
    pizza_sys_hostinfo_get_endianness(&endianness_info);
    pizza_sys_hostinfo_get_architecture(&arch_info);

    // Choose color based on endianness
    const char* endian_str  = endianness_info.is_little_endian ? "Little-endian" : "Big-endian";
    const char* endian_color = endianness_info.is_little_endian ? "{green}" : "{red}";

    switch (engine->pallet.theme) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{blue,bold}=================================================================================={reset}\n");
            pizza_io_printf("{blue}=== {cyan}Pizza Summary{blue} ===: OS {green}%s{blue}, Endianness: %s%s{blue}, Architecture: {green}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            pizza_io_printf("{blue,bold}=================================================================================={reset}\n");
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("{magenta}=================================================================================={reset}\n");
            pizza_io_printf("{magenta}=== Pizza Summary ===:{reset} OS {magenta}%s{reset}, Endianness: %s%s{reset}, Architecture: {magenta}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            pizza_io_printf("{magenta}=================================================================================={reset}\n");
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("{cyan}=================================================================================={reset}\n");
            pizza_io_printf("{cyan}[Pizza Summary]{reset}: OS {cyan}%s{reset}, Endianness: %s%s{reset}, Architecture: {cyan}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            pizza_io_printf("{cyan}=================================================================================={reset}\n");
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("TAP version 13\n");
            pizza_io_printf("# {yellow}Pizza Summary{reset}: OS {yellow}%s{reset}, Endianness: %s%s{reset}, Architecture: {yellow}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[==========] {blue}F{red}o{yellow}s{green}s{blue}i{red}l {yellow}P{green}i{blue}z{red}z{yellow}a {green}Summary{reset}\n");
            pizza_io_printf("[----------] OS: {blue}%s{reset}, Endianness: %s%s{reset}, Architecture: {green}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("{green}Unity Test Summary{reset}\n");
            pizza_io_printf("{cyan}OS:{reset} {green}%s{reset}, {cyan}Endianness:{reset} %s%s{reset}, {cyan}Architecture:{reset} {green}%s{reset}\n",
            system_info.os_name, endian_color, endian_str, arch_info.architecture);
            break;

        default:
            pizza_io_printf("Unknown theme. Unable to display summary heading.\n");
            break;
    }

}

void fossil_pizza_summary(const fossil_pizza_engine_t* engine) {
    if (!engine) return;
    
    // Classic Summary Components
    fossil_pizza_summary_heading(engine);
    fossil_pizza_summary_scoreboard(engine);
    fossil_pizza_summary_timestamp(engine);

    // AI-Generated Feedback
    pizza_io_printf("\n{blue,bold}Feedback:{reset} {cyan}%s{reset}\n", fossil_test_summary_feedback(&engine->score));
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

// --- AI Result Struct ---
typedef struct {
    char *message;
    uint8_t hash[FOSSIL_PIZZA_HASH_SIZE];
    uint64_t timestamp;
    int root_cause_code; // 0: unknown, 1: logic, 2: timeout, 3: memory, 4: io, 5: coverage, 6: range, 7: float, 8: string, 9: soap/text
} pizza_assert_ti_result;

extern uint64_t get_pizza_time_microseconds(void); // from common utilities

// --- Root Cause Detection Helper ---
// Enhanced to support assumption macros and their message patterns
static int pizza_test_detect_root_cause(const char *message) {
    if (!message) return 0;

    // Memory errors
    if (strstr(message, "null") || strstr(message, "NULL") || strstr(message, "cnull") || strstr(message, "not cnull") ||
        strstr(message, "pointer") || strstr(message, "memory") || strstr(message, "buffer") ||
        strstr(message, "valid memory") || strstr(message, "not valid memory") ||
        strstr(message, "zeroed") || strstr(message, "not zeroed"))
        return 3; // memory

    // Timeout
    if (strstr(message, "timeout") || strstr(message, "timed out"))
        return 2; // timeout

    // I/O errors
    if (strstr(message, "file") || strstr(message, "I/O") || strstr(message, "io error"))
        return 4; // io

    // Range errors
    if (strstr(message, "range") || strstr(message, "not within range") || strstr(message, "within range") ||
        strstr(message, "overflow") || strstr(message, "underflow"))
        return 6; // range

    // Floating-point
    if (strstr(message, "float") || strstr(message, "double") ||
        strstr(message, "NaN") || strstr(message, "nan") ||
        strstr(message, "infinity") || strstr(message, "infinite") ||
        strstr(message, "tolerance"))
        return 7; // float

    // String/buffer
    if (strstr(message, "string") || strstr(message, "C string") ||
        strstr(message, "strlen") || strstr(message, "cstr") ||
        strstr(message, "starts with") || strstr(message, "ends with") ||
        strstr(message, "contains") || strstr(message, "not contain") ||
        strstr(message, "length of"))
        return 8; // string

    // SOAP/text
    if (strstr(message, "soap") || strstr(message, "text") || strstr(message, "tone") ||
        strstr(message, "rot-brain"))
        return 9; // soap/text

    // Coverage/empty/skipped/not implemented
    if (strstr(message, "empty") || strstr(message, "skipped") || strstr(message, "not implemented"))
        return 5; // coverage

    // Logic errors (default for assumption failures)
    if (strstr(message, "Expected") || strstr(message, "not be") || strstr(message, "to be") ||
        strstr(message, "fail") || strstr(message, "logic") || strstr(message, "assert"))
        return 1; // logic

    return 0; // unknown
}

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

        // Root cause detection
        result.root_cause_code = pizza_test_detect_root_cause(formatted_message);
    }

    va_end(args);
    return formatted_message;
}

void pizza_test_assert_internal_output(const char *message, const char *file, int line, const char *func, int anomaly_count, int root_cause_code) {
    // Output assertion failure based on theme, with root cause if detected
    // Advanced root cause analysis for assumption macros and patterns

    // --- Advanced root cause detection ---
    // If root_cause_code is unknown (0), try to analyze message for assumption patterns
    if (root_cause_code == 0 && message) {
        // Boolean assumption patterns
        if (strstr(message, "Expected") && strstr(message, "to be true")) {
            root_cause_code = 1; // logic
        } else if (strstr(message, "Expected") && strstr(message, "to be false")) {
            root_cause_code = 1; // logic
        } else if (strstr(message, "to not be true") || strstr(message, "to not be false")) {
            root_cause_code = 1; // logic
        }

        // Floating point assumption patterns
        else if (strstr(message, "within tolerance") || strstr(message, "to be equal") || strstr(message, "to not be equal")) {
            if (strstr(message, "value %f") || strstr(message, "value %lf")) {
                root_cause_code = 7; // float
            }
        } else if (strstr(message, "to be less than") || strstr(message, "to be more than") ||
                   strstr(message, "to be less than or equal to") || strstr(message, "to be more than or equal to") ||
                   strstr(message, "to not be less than") || strstr(message, "to not be more than") ||
                   strstr(message, "to not be less than or equal to") || strstr(message, "to not be more than or equal to")) {
            if (strstr(message, "value %f") || strstr(message, "value %lf")) {
                root_cause_code = 7; // float
            }
        } else if (strstr(message, "to be NaN") || strstr(message, "to be infinity")) {
            root_cause_code = 7; // float
        }

        // Numeric/range assumption patterns
        else if (strstr(message, "is not within range") || strstr(message, "is within range")) {
            root_cause_code = 6; // range
        }

        // Memory assumption patterns
        else if (strstr(message, "to be zeroed") || strstr(message, "to not be zeroed") ||
                 strstr(message, "to be equal") || strstr(message, "to not be equal") ||
                 strstr(message, "to be more than") || strstr(message, "to be less than") ||
                 strstr(message, "to be more than or equal to") || strstr(message, "to be less than or equal to") ||
                 strstr(message, "to not be more than") || strstr(message, "to not be less than") ||
                 strstr(message, "to not be more than or equal to") || strstr(message, "to not be less than or equal to") ||
                 strstr(message, "to be valid") || strstr(message, "to not be valid")) {
            if (strstr(message, "memory") || strstr(message, "pointer")) {
                root_cause_code = 3; // memory
            }
        }

        // Null pointer assumption patterns
        else if (strstr(message, "to be cnull") || strstr(message, "to not be cnull")) {
            root_cause_code = 3; // memory (null pointer)
        }

        // String assumption patterns
        else if (strstr(message, "C string") || strstr(message, "cstr") ||
                 strstr(message, "to be equal") || strstr(message, "to not be equal") ||
                 strstr(message, "length of") || strstr(message, "to start with prefix") ||
                 strstr(message, "to end with suffix") || strstr(message, "to contain substring") ||
                 strstr(message, "to not contain substring") || strstr(message, "to contain") ||
                 strstr(message, "to not contain") || strstr(message, "occurrences of substring")) {
            root_cause_code = 8; // string
        }

        // SOAP/text assumption patterns
        else if (strstr(message, "rot-brain") || strstr(message, "tone of text")) {
            root_cause_code = 9; // soap/text
        }
    }

    // --- Suggestion hints for assumption failures ---
    const char *hint_str = NULL;
    if (message) {
        // Boolean hints
        if (strstr(message, "to be true")) {
            hint_str = "Check your logic or expected condition. Ensure the value is true.";
        } else if (strstr(message, "to be false")) {
            hint_str = "Check your logic or expected condition. Ensure the value is false.";
        } else if (strstr(message, "to not be true")) {
            hint_str = "Check your logic. The value should not be true.";
        } else if (strstr(message, "to not be false")) {
            hint_str = "Check your logic. The value should not be false.";
        }
        // Floating point hints
        else if (strstr(message, "within tolerance")) {
            hint_str = "Check your tolerance value and floating-point comparison.";
        } else if (strstr(message, "to be equal") && (strstr(message, "value %f") || strstr(message, "value %lf"))) {
            hint_str = "Check your floating-point values and consider rounding or tolerance.";
        } else if (strstr(message, "to not be equal") && (strstr(message, "value %f") || strstr(message, "value %lf"))) {
            hint_str = "Check your floating-point values and ensure they differ beyond tolerance.";
        } else if (strstr(message, "to be less than")) {
            hint_str = "Check the actual and expected values. Actual should be less than expected.";
        } else if (strstr(message, "to be more than")) {
            hint_str = "Check the actual and expected values. Actual should be more than expected.";
        } else if (strstr(message, "to be less than or equal to")) {
            hint_str = "Check the actual and expected values. Actual should be <= expected.";
        } else if (strstr(message, "to be more than or equal to")) {
            hint_str = "Check the actual and expected values. Actual should be >= expected.";
        } else if (strstr(message, "to not be less than")) {
            hint_str = "Check the actual and expected values. Actual should not be less than expected.";
        } else if (strstr(message, "to not be more than")) {
            hint_str = "Check the actual and expected values. Actual should not be more than expected.";
        } else if (strstr(message, "to not be less than or equal to")) {
            hint_str = "Check the actual and expected values. Actual should be > expected.";
        } else if (strstr(message, "to not be more than or equal to")) {
            hint_str = "Check the actual and expected values. Actual should be < expected.";
        } else if (strstr(message, "to be NaN")) {
            hint_str = "Check for NaN values. Use isnan() for validation.";
        } else if (strstr(message, "to be infinity")) {
            hint_str = "Check for infinity values. Use isinf() for validation.";
        }
        // Range hints
        else if (strstr(message, "is not within range")) {
            hint_str = "Check the value and range boundaries. Ensure value is within [min, max].";
        } else if (strstr(message, "is within range")) {
            hint_str = "Check the value and range boundaries. Ensure value is outside [min, max].";
        }
        // Memory hints
        else if (strstr(message, "to be zeroed")) {
            hint_str = "Check memory initialization. Use memset or equivalent.";
        } else if (strstr(message, "to not be zeroed")) {
            hint_str = "Check memory contents. Ensure not all bytes are zero.";
        } else if (strstr(message, "to be valid")) {
            hint_str = "Check pointer validity. Ensure pointer is not null and points to valid memory.";
        } else if (strstr(message, "to not be valid")) {
            hint_str = "Check pointer validity. Ensure pointer is null or invalid.";
        } else if (strstr(message, "to be cnull")) {
            hint_str = "Check pointer assignment. Ensure pointer is NULL.";
        } else if (strstr(message, "to not be cnull")) {
            hint_str = "Check pointer assignment. Ensure pointer is not NULL.";
        }
        // String hints
        else if (strstr(message, "C string") || strstr(message, "cstr")) {
            hint_str = "Check string contents and length. Use strcmp or strlen for validation.";
        } else if (strstr(message, "to start with prefix")) {
            hint_str = "Check string prefix. Use strncmp or custom prefix check.";
        } else if (strstr(message, "to end with suffix")) {
            hint_str = "Check string suffix. Use string length and memcmp.";
        } else if (strstr(message, "to contain substring")) {
            hint_str = "Check substring presence. Use strstr or custom search.";
        } else if (strstr(message, "to not contain substring")) {
            hint_str = "Check substring absence. Use strstr or custom search.";
        } else if (strstr(message, "occurrences of substring")) {
            hint_str = "Check substring count. Use a loop or custom count function.";
        }
        // SOAP/text hints
        else if (strstr(message, "rot-brain")) {
            hint_str = "Check for inappropriate language or tone in text.";
        } else if (strstr(message, "tone of text")) {
            hint_str = "Check tone detection logic and expected tone value.";
        }
    }

    const char *root_cause_str = NULL;
    switch (root_cause_code) {
        case 1: root_cause_str = "Logic error"; break;
        case 2: root_cause_str = "Timeout"; break;
        case 3: root_cause_str = "Memory error"; break;
        case 4: root_cause_str = "I/O error"; break;
        case 5: root_cause_str = "Coverage/Empty"; break;
        case 6: root_cause_str = "Range error"; break;
        case 7: root_cause_str = "Floating-point"; break;
        case 8: root_cause_str = "String/buffer"; break;
        case 9: root_cause_str = "Text/SOAP"; break;
        default: root_cause_str = NULL; break;
    }

    switch (G_PIZZA_THEME) {
        case PIZZA_THEME_FOSSIL:
            pizza_io_printf("{red,bold}Assertion failed:{reset} {yellow}%s{reset} {blue}(%s:%d in %s){reset}\n",
                            message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("{magenta}Root Cause:{reset} %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("{yellow}Duplicate or similar assertion detected [Anomaly Count: %d]{reset}\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CATCH:
        case PIZZA_THEME_DOCTEST:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("Root Cause: %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_CPPUTEST:
            pizza_io_printf("[ASSERTION FAILED] %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("[ROOT CAUSE] %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("[DUPLICATE ASSERTION] Anomaly Count: %d\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_TAP:
            pizza_io_printf("not ok - Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("# Root Cause: %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("# Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_GOOGLETEST:
            pizza_io_printf("[  FAILED  ] Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("[  ROOT    ] %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("[  WARNING ] Duplicate or similar assertion detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        case PIZZA_THEME_UNITY:
            pizza_io_printf("Unity Assertion Failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("Unity Root Cause: %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
            if (anomaly_count > 0) {
                pizza_io_printf("Unity Duplicate Assertion Detected [Anomaly Count: %d]\n", anomaly_count);
            }
            break;

        default:
            pizza_io_printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
            if (root_cause_str || hint_str) {
                pizza_io_printf("Root Cause: %s%s%s\n",
                    root_cause_str ? root_cause_str : "Unknown",
                    (root_cause_str && hint_str) ? " - " : "",
                    hint_str ? hint_str : "");
            }
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

        // Compute hash for clustering
        char input_buf[512], output_buf[64];
        snprintf(input_buf, sizeof(input_buf), "%s:%d:%s", file, line, func);
        snprintf(output_buf, sizeof(output_buf), "%s", message);
        uint8_t hash[FOSSIL_PIZZA_HASH_SIZE];
        fossil_pizza_hash(input_buf, output_buf, hash);

        int root_cause_code = pizza_test_detect_root_cause(message);

        // Enhanced output includes anomaly count and root cause
        pizza_test_assert_internal_output(message, file, line, func, anomaly_count, root_cause_code);

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
