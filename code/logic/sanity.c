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
    struct _stat buffer;
    return (_stat(filename, &buffer) == 0); // On Windows, use the _stat function to check if the file exists.
#else
    struct stat buffer;
    return (stat(filename, &buffer) == 0); // On Unix-like systems, use the stat function to check if the file exists.
#endif
}

int fossil_sanity_sys_create_dir(const char* dirname) {
#ifdef _WIN32
    return CreateDirectoryA(dirname, NULL) ? 0 : -1; // On Windows, use the CreateDirectoryA function to create the directory.
#else
    return mkdir(dirname, 0755); // On Unix-like systems, use the mkdir function to create the directory.
#endif
}

int fossil_sanity_sys_dir_exists(const char* dirname) {
#ifdef _WIN32
    struct _stat buffer;
    return (_stat(dirname, &buffer) == 0 && (buffer.st_mode & _S_IFDIR)); // On Windows, use the _stat function to check if the directory exists.
#else
    struct stat buffer;
    return (stat(dirname, &buffer) == 0 && S_ISDIR(buffer.st_mode)); // On Unix-like systems, use the stat function to check if the directory exists.
#endif
}

// *****************************************************************************
// File I/O
// *****************************************************************************

char* fossil_sanity_sys_read_file(const char* filename) {
    if (!filename) return NULL;

    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    if (size < 0) { fclose(f); return NULL; }

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) { fclose(f); return NULL; }

    size_t read = fread(buffer, 1, size, f);
    buffer[read] = '\0';
    fclose(f);

    return buffer;
}

int fossil_sanity_sys_write_file(const char* filename, const char* data) {
    if (!filename || !data) return -1;

    FILE* f = fopen(filename, "wb");
    if (!f) return -1;

    size_t len = strlen(data);
    size_t written = fwrite(data, 1, len, f);
    fclose(f);

    return (written == len) ? 0 : -1;
}

int fossil_sanity_sys_delete_file(const char* filename) {
    if (!filename) return -1;
    return remove(filename) == 0 ? 0 : -1;
}

// *****************************************************************************
// Environment Variables
// *****************************************************************************

const char* fossil_sanity_sys_getenv(const char* name) {
    if (!name) return NULL;
    return getenv(name);
}

int fossil_sanity_sys_setenv(const char* name, const char* value) {
    if (!name || !value) return -1;

#ifdef _WIN32
    return _putenv_s(name, value) == 0 ? 0 : -1;
#else
    return setenv(name, value, 1) == 0 ? 0 : -1;
#endif
}

// *****************************************************************************
// Time Utilities
// *****************************************************************************

char* fossil_sanity_sys_timestamp(void) {
    time_t now = time(NULL);
    if (now == (time_t)-1) return NULL;

    struct tm tstruct;
#ifdef _WIN32
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif

    char buf[64];
    if (strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct) == 0)
        return NULL;

    char* out = strdup(buf);
    return out;
}

long long fossil_sanity_sys_uptime_ms(void) {
#ifdef _WIN32
    return GetTickCount64();
#else
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) return -1;
    return (long long)tv.tv_sec * 1000LL + (tv.tv_usec / 1000);
#endif
}

// *****************************************************************************
// Process Utilities
// *****************************************************************************

int fossil_sanity_sys_is_running(int pid) {
    if (pid <= 0) return -1;
#ifdef _WIN32
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, (DWORD)pid);
    if (!h) return 0;
    DWORD code;
    int running = (GetExitCodeProcess(h, &code) && code == STILL_ACTIVE);
    CloseHandle(h);
    return running ? 1 : 0;
#else
    return (kill(pid, 0) == 0) ? 1 : 0;
#endif
}

int fossil_sanity_sys_kill(int pid) {
    if (pid <= 0) return -1;
#ifdef _WIN32
    HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)pid);
    if (!h) return -1;
    int result = TerminateProcess(h, 1) ? 0 : -1;
    CloseHandle(h);
    return result;
#else
    return (kill(pid, SIGTERM) == 0) ? 0 : -1;
#endif
}
