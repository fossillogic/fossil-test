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
#ifndef FOSSIL_TEST_CONSOLE_H
#define FOSSIL_TEST_CONSOLE_H

#include "fossil/common/common.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void fossil_console_out(const char* color_name, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
