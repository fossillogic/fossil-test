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
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

int pizza_sys_call_execute(const char *command) {
#ifdef _WIN32
    return system(command); // On Windows, use the system function to execute the command.
#else
    return system(command); // On Unix-like systems, use the system function to execute the command.
#endif
}

int pizza_sys_call_getpid(void) {
#ifdef _WIN32
    return GetCurrentProcessId(); // On Windows, use the GetCurrentProcessId function to get the process ID.
#else
    return getpid(); // On Unix-like systems, use the getpid function to get the process ID.
#endif
}

void pizza_sys_call_sleep(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds); // On Windows, use the Sleep function to sleep for the specified number of milliseconds.
#else
    sleep(milliseconds * 1000); // On Unix-like systems, use the usleep function to sleep for the specified number of microseconds.
#endif
}

int pizza_sys_call_create_file(const char *filename) {
#ifdef _WIN32
    HANDLE hFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return -1; // If the file handle is invalid, return an error code.
    CloseHandle(hFile); // Close the file handle.
    return 0; // Return success.
#else
    int fd = open(filename, O_CREAT | O_WRONLY, 0644); // On Unix-like systems, use the open function to create the file.
    if (fd == -1) return -1; // If the file descriptor is invalid, return an error code.
    close(fd); // Close the file descriptor.
    return 0; // Return success.
#endif
}

int fossil_sanity_sys_execute(const char* command) {
    return pizza_sys_call_execute(command);
}

int fossil_sanity_sys_getpid(void) {
    return pizza_sys_call_getpid();
}

void fossil_sanity_sys_sleep(int milliseconds) {
    pizza_sys_call_sleep(milliseconds);
}

int fossil_sanity_sys_create_file(const char* filename) {
    return pizza_sys_call_create_file(filename);
}

int fossil_sanity_sys_file_exists(const char* filename) {
#ifdef _WIN32
    #include <sys/stat.h> // Ensure the correct header is included for _stat
    struct _stat buffer;
    return (_stat(filename, &buffer) == 0); // On Windows, use the _stat function to check if the file exists.
#else
    struct stat buffer;
    return (stat(filename, &buffer) == 0); // On Unix-like systems, use the stat function to check if the file exists.
#endif
}
