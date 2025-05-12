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
#include "fossil/pizza/sanity.h"
#ifdef _WIN32
#include <windows.h>
#include <process.h>
#include <io.h>
#define access _access
#define F_OK 0
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

int fossil_sanity_sys_execute(const char* command) {
    if (!command) return -1;
    int status = system(command);
#ifdef _WIN32
    return status;
#else
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return -1;
#endif
}

int fossil_sanity_sys_getpid(void) {
#ifdef _WIN32
    return _getpid();
#else
    return getpid();
#endif
}

void fossil_sanity_sys_sleep(int milliseconds) {
#ifdef _WIN32
    Sleep((DWORD)milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int fossil_sanity_sys_create_file(const char* filename) {
    if (!filename) return -1;
    FILE* fp = fopen(filename, "w");
    if (!fp) return -2;
    fclose(fp);
    return 0;
}

int fossil_sanity_sys_file_exists(const char* filename) {
    if (!filename) return 0;
    return access(filename, F_OK) == 0 ? 1 : 0;
}
