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
#ifndef FOSSIL_SANITY_H
#define FOSSIL_SANITY_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Executes a system command and returns the exit code.
 * 
 * This function takes a command string as input, executes it in the system shell,
 * and returns the exit code of the command. The exit code can be used to determine
 * whether the command executed successfully or encountered an error.
 * 
 * @param command A null-terminated string representing the system command to execute.
 *                The command should be formatted as it would be entered in a terminal.
 * @return int The exit code of the executed command. A value of 0 typically indicates
 *             success, while non-zero values indicate errors or specific exit statuses.
 */
int fossil_sanity_sys_execute(const char* command);

/**
 * @brief Retrieves the process ID of the current process.
 * 
 * This function returns the unique identifier (PID) of the process in which it is called.
 * The PID can be used for various purposes, such as debugging, inter-process communication,
 * or process management.
 * 
 * @return int The process ID of the current process.
 */
int fossil_sanity_sys_getpid(void);

/**
 * @brief Suspends the execution of the current thread for a specified duration.
 * 
 * This function pauses the execution of the calling thread for the given number of
 * milliseconds. It is useful for introducing delays or waiting for a specific amount
 * of time before proceeding with further execution.
 * 
 * @param milliseconds The number of milliseconds to sleep. Must be a non-negative value.
 *                     A value of 0 may yield the processor to other threads without delay.
 */
void fossil_sanity_sys_sleep(int milliseconds);

/**
 * @brief Creates an empty file at the specified location.
 * 
 * This function attempts to create an empty file with the given filename. If the file
 * already exists, its contents may be overwritten or truncated depending on the system's
 * behavior. The function returns a status code indicating success or failure.
 * 
 * @param filename A null-terminated string representing the path to the file to be created.
 *                 The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the file. Returns a negative value if
 *             the file could not be created due to errors such as insufficient permissions
 *             or invalid file paths.
 */
int fossil_sanity_sys_create_file(const char* filename);

/**
 * @brief Checks whether a file exists at the specified location.
 * 
 * This function determines if a file exists at the given path. It can be used to verify
 * the presence of a file before performing operations such as reading or writing. The
 * function does not differentiate between regular files, directories, or other file types.
 * 
 * @param filename A null-terminated string representing the path to the file to check.
 *                 The path can be relative or absolute.
 * @return int Returns 1 if the file exists, and 0 if it does not exist. Note that this
 *             function does not check for file accessibility or permissions.
 */
int fossil_sanity_sys_file_exists(const char* filename);

#ifdef __cplusplus
}
#endif

// *****************************************************************************
// Private API Macros
// *****************************************************************************

/**
 * @brief Executes a system command and returns the exit code.
 * 
 * This function takes a command string as input, executes it in the system shell,
 * and returns the exit code of the command. The exit code can be used to determine
 * whether the command executed successfully or encountered an error.
 * 
 * @param command A null-terminated string representing the system command to execute.
 *                The command should be formatted as it would be entered in a terminal.
 * @return int The exit code of the executed command. A value of 0 typically indicates
 *             success, while non-zero values indicate errors or specific exit statuses.
 */
#define _FOSSIL_SANITY_SYS_EXECUTE(command) \
    fossil_sanity_sys_execute(command)

/**
 * @brief Retrieves the process ID of the current process.
 * 
 * This function returns the unique identifier (PID) of the process in which it is called.
 * The PID can be used for various purposes, such as debugging, inter-process communication,
 * or process management.
 * 
 * @return int The process ID of the current process.
 */
#define _FOSSIL_SANITY_SYS_GETPID() \
    fossil_sanity_sys_getpid()

/**
 * @brief Suspends the execution of the current thread for a specified duration.
 * 
 * This function pauses the execution of the calling thread for the given number of
 * milliseconds. It is useful for introducing delays or waiting for a specific amount
 * of time before proceeding with further execution.
 * 
 * @param milliseconds The number of milliseconds to sleep. Must be a non-negative value.
 *                     A value of 0 may yield the processor to other threads without delay.
 */
#define _FOSSIL_SANITY_SYS_SLEEP(milliseconds) \
    fossil_sanity_sys_sleep(milliseconds)

/**
 * @brief Creates an empty file at the specified location.
 * 
 * This function attempts to create an empty file with the given filename. If the file
 * already exists, its contents may be overwritten or truncated depending on the system's
 * behavior. The function returns a status code indicating success or failure.
 * 
 * @param filename A null-terminated string representing the path to the file to be created.
 *                 The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the file. Returns a negative value if
 *             the file could not be created due to errors such as insufficient permissions
 *             or invalid file paths.
 */
#define _FOSSIL_SANITY_SYS_CREATE_FILE(filename) \
    fossil_sanity_sys_create_file(filename)

/**
 * @brief Checks whether a file exists at the specified location.
 * 
 * This function determines if a file exists at the given path. It can be used to verify
 * the presence of a file before performing operations such as reading or writing. The
 * function does not differentiate between regular files, directories, or other file types.
 * 
 * @param filename A null-terminated string representing the path to the file to check.
 *                 The path can be relative or absolute.
 * @return int Returns 1 if the file exists, and 0 if it does not exist. Note that this
 *             function does not check for file accessibility or permissions.
 */
#define _FOSSIL_SANITY_SYS_FILE_EXISTS(filename) \
    fossil_sanity_sys_file_exists(filename)

// *****************************************************************************
// Public API Macros
// *****************************************************************************

/**
 * @brief Executes a system command and returns the exit code.
 * 
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_EXECUTE function.
 * It is used to execute a system command and retrieve its exit code.
 * 
 * @param command A null-terminated string representing the system command to execute.
 *                The command should be formatted as it would be entered in a terminal.
 * @return int The exit code of the executed command. A value of 0 typically indicates
 *             success, while non-zero values indicate errors or specific exit statuses.
 */
#define FOSSIL_SANITY_SYS_EXECUTE(command) \
    _FOSSIL_SANITY_SYS_EXECUTE(command)

/**
 * @brief Retrieves the process ID of the current process.
 * 
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_GETPID function.
 * It is used to retrieve the unique identifier (PID) of the current process.
 * 
 * @return int The process ID of the current process.
 */
#define FOSSIL_SANITY_SYS_GETPID() \
    _FOSSIL_SANITY_SYS_GETPID()

/**
 * @brief Suspends the execution of the current thread for a specified duration.
 * 
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_SLEEP function.
 * It is used to pause the execution of the calling thread for a given number
 * of milliseconds.
 * 
 * @param milliseconds The number of milliseconds to sleep. Must be a non-negative value.
 *                     A value of 0 may yield the processor to other threads without delay.
 */
#define FOSSIL_SANITY_SYS_SLEEP(milliseconds) \
    _FOSSIL_SANITY_SYS_SLEEP(milliseconds)

/**
 * @brief Creates an empty file at the specified location.
 * 
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_CREATE_FILE function.
 * It is used to create an empty file with the given filename.
 * 
 * @param filename A null-terminated string representing the path to the file to be created.
 *                 The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the file. Returns a negative value if
 *             the file could not be created due to errors such as insufficient permissions
 *             or invalid file paths.
 */
#define FOSSIL_SANITY_SYS_CREATE_FILE(filename) \
    _FOSSIL_SANITY_SYS_CREATE_FILE(filename)

/**
 * @brief Checks whether a file exists at the specified location.
 * 
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_FILE_EXISTS function.
 * It is used to check if a file exists at the given path.
 * 
 * @param filename A null-terminated string representing the path to the file to check.
 *                 The path can be relative or absolute.
 * @return int Returns 1 if the file exists, and 0 if it does not exist. Note that this
 *             function does not check for file accessibility or permissions.
 */
#define FOSSIL_SANITY_SYS_FILE_EXISTS(filename) \
    _FOSSIL_SANITY_SYS_FILE_EXISTS(filename)

#endif // FOSSIL_SANITY_H
