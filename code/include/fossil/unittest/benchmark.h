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
#ifndef FOSSIL_TEST_BENCHMARK_H
#define FOSSIL_TEST_BENCHMARK_H

#include "fossil/common/common.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Runs a test case with a specified fixture within the testing engine
void xbenchmark(char* duration_type, double expected, double actual);
void fossil_test_start_benchmark(void);
uint64_t fossil_test_stop_benchmark(void);

#ifdef __cplusplus
}
#endif

#endif
