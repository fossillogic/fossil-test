/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_TEST_PLATFORM_H
#define FOSSIL_TEST_PLATFORM_H

#include "common.h" // for introspection data

#ifdef __cplusplus
extern "C" {
#endif

// Utility function to get the architecture
static inline char* _fossil_test_get_architecture(void) {
    char* arch = (char*)malloc(10 * sizeof(char));  // Explicit cast for C++
    if (arch == NULL) {
        return NULL;
    }
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    switch (sysinfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            strncpy(arch, "x86_64", 9);
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            strncpy(arch, "ARM", 9);
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            strncpy(arch, "ARM64", 9);
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            strncpy(arch, "x86", 9);
            break;
        default:
            strncpy(arch, "unknown", 9);
    }
    arch[9] = '\0';
#else
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        strncpy(arch, buffer.machine, 9);
    } else {
        strncpy(arch, "unknown", 9);
    }
    arch[9] = '\0';
#endif
    return arch;
}

// Utility function to get the OS name
static inline char* _fossil_test_get_os_name(void) {
    char* os_name = (char*)malloc(20 * sizeof(char));  // Explicit cast for C++
    if (os_name == NULL) {
        return NULL;
    }
#ifdef _WIN32
    strncpy(os_name, "Windows", 19);
#else
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        strncpy(os_name, buffer.sysname, 19);
    } else {
        strncpy(os_name, "unknown", 19);
    }
#endif
    os_name[19] = '\0';
    return os_name;
}

// Utility function to check if the system is big endian
static inline bool _fossil_test_assert_is_big_endian(void) {
    uint16_t num = 0x1;
    return (*(uint8_t *)&num == 0);
}

// Utility function to get the number of CPUs
static inline int _fossil_test_get_num_cpus(void) {
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#elif defined(__APPLE__)
    int num_cpus;
    size_t size = sizeof(num_cpus);
    if (sysctlbyname("hw.ncpu", &num_cpus, &size, NULL, 0) == 0) {
        return num_cpus;
    } else {
        return 1; // Default to 1 if unable to get the number of CPUs
    }
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

// Utility function to get the total memory size in MB
static inline int _fossil_test_get_memory_size(void) {
#ifdef _WIN32
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    if (GlobalMemoryStatusEx(&status)) {
        return (int)(status.ullTotalPhys / (1024 * 1024));
    } else {
        fprintf(stderr, "Failed to get memory status on Windows\n");
        return 0;
    }
#elif defined(__APPLE__)
    int64_t mem_size;
    size_t size = sizeof(mem_size);
    if (sysctlbyname("hw.memsize", &mem_size, &size, NULL, 0) == 0) {
        return (int)(mem_size / (1024 * 1024));
    } else {
        fprintf(stderr, "Failed to get memory size on macOS\n");
        return 0;
    }
#elif defined(__linux__)
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        return (int)(info.totalram * info.mem_unit / (1024 * 1024));
    } else {
        fprintf(stderr, "Failed to get memory size on Linux\n");
        return 0;
    }
#else
    fprintf(stderr, "Unsupported platform\n");
    return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif
