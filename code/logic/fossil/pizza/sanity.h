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

/**
 * @brief Creates an empty directory at the specified location.
 * 
 * This function attempts to create an empty directory with the given name. If the directory
 * already exists, the function may return an error or success depending on the system's
 * behavior. The function returns a status code indicating success or failure.
 * 
 * @param dirname A null-terminated string representing the path to the directory to be created.
 *                The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the directory. Returns a negative value if
 *             the directory could not be created due to errors such as insufficient permissions
 *             or invalid paths.
 */
int fossil_sanity_sys_create_dir(const char* dirname);

/**
 * @brief Checks whether a directory exists at the specified location.
 * 
 * This function determines if a directory exists at the given path. It can be used to verify
 * the presence of a directory before performing operations such as reading or writing. The
 * function does not differentiate between regular directories and other file types.
 * 
 * @param dirname A null-terminated string representing the path to the directory to check.
 *                The path can be relative or absolute.
 * @return int Returns 1 if the directory exists, and 0 if it does not exist. Note that this
 *             function does not check for directory accessibility or permissions.
 */
int fossil_sanity_sys_dir_exists(const char* dirname);

/**
 * @brief Reads the entire contents of a file into memory.
 *
 * The returned buffer is null-terminated and allocated dynamically.
 * The caller is responsible for freeing the returned memory using free().
 *
 * @param filename Path to the file to read.
 * @return char* Pointer to allocated null-terminated buffer on success, 
 *               or NULL on failure.
 */
char* fossil_sanity_sys_read_file(const char* filename);

/**
 * @brief Writes data to a file, replacing any existing contents.
 *
 * @param filename Path to the file.
 * @param data Null-terminated string to write.
 * @return int Returns 0 on success, negative on failure.
 */
int fossil_sanity_sys_write_file(const char* filename, const char* data);

/**
 * @brief Deletes a file from the filesystem.
 *
 * @param filename Path to the file to delete.
 * @return int Returns 0 on success, negative on failure.
 */
int fossil_sanity_sys_delete_file(const char* filename);

/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param name Name of the environment variable.
 * @return const char* Value of the variable, or NULL if not found.
 */
const char* fossil_sanity_sys_getenv(const char* name);

/**
 * @brief Sets or overrides an environment variable.
 *
 * @param name Name of the environment variable.
 * @param value Value to set.
 * @return int Returns 0 on success, negative on failure.
 */
int fossil_sanity_sys_setenv(const char* name, const char* value);

/**
 * @brief Retrieves the current system timestamp as a formatted string.
 *
 * @return char* Newly allocated string with timestamp (caller must free).
 */
char* fossil_sanity_sys_timestamp(void);

/**
 * @brief Returns uptime in milliseconds since process start.
 *
 * @return long long Milliseconds since process launch.
 */
long long fossil_sanity_sys_uptime_ms(void);

/**
 * @brief Checks if a process is still running.
 *
 * @param pid Process ID.
 * @return int Returns 1 if running, 0 if not, negative on error.
 */
int fossil_sanity_sys_is_running(int pid);

/**
 * @brief Attempts to terminate a process by PID.
 *
 * @param pid Process ID.
 * @return int Returns 0 on success, negative on failure.
 */
int fossil_sanity_sys_kill(int pid);

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

/**
 * @brief Creates an empty directory at the specified location.
 * This function attempts to create an empty directory with the given name. If the directory
 * already exists, the function may return an error or success depending on the system's
 * behavior.
 * 
 * @param dirname A null-terminated string representing the path to the directory to be created.
 *                The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the directory. Returns a negative value if
 *             the directory could not be created due to errors such as insufficient permissions
 *             or invalid paths.
 */
#define _FOSSIL_SANITY_SYS_CREATE_DIR(dirname) \
    fossil_sanity_sys_create_dir(dirname)

/**
 * @brief Checks whether a directory exists at the specified location.
 * This function determines if a directory exists at the given path. It can be used to verify
 * the presence of a directory before performing operations such as reading or writing. The
 * function does not differentiate between regular files, directories, or other file types.
 * 
 * @param dirname A null-terminated string representing the path to the directory to check.
 *                The path can be relative or absolute.
 * @return int Returns 1 if the directory exists, and 0 if it does not exist. Note that this
 *             function does not check for directory accessibility or permissions.
 */
#define _FOSSIL_SANITY_SYS_DIR_EXISTS(dirname) \
    fossil_sanity_sys_dir_exists(dirname)

/**
 * @brief Reads the entire contents of a file into memory.
 *
 * The returned buffer is null-terminated and allocated dynamically.
 * The caller is responsible for freeing the returned memory using free().
 *
 * @param filename Path to the file to read.
 * @return char* Pointer to allocated null-terminated buffer on success,
 *               or NULL on failure.
 */
#define _FOSSIL_SANITY_SYS_READ_FILE(filename) \
    fossil_sanity_sys_read_file(filename)

/**
 * @brief Writes data to a file, replacing any existing contents.
 *
 * @param filename Path to the file.
 * @param data Null-terminated string to write.
 * @return int Returns 0 on success, negative on failure.
 */
 #define _FOSSIL_SANITY_SYS_WRITE_FILE(filename, data) \
    fossil_sanity_sys_write_file(filename, data)

/**
 * @brief Deletes a file from the filesystem.
 *
 * @param filename Path to the file to delete.
 * @return int Returns 0 on success, negative on failure.
 */
#define _FOSSIL_SANITY_SYS_DELETE_FILE(filename) \
    fossil_sanity_sys_delete_file(filename)

/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param name Name of the environment variable.
 * @return const char* Value of the variable, or NULL if not found.
 */
#define _FOSSIL_SANITY_SYS_GETENV(name) \
    fossil_sanity_sys_getenv(name)

/**
 * @brief Sets or overrides an environment variable.
 *
 * @param name Name of the environment variable.
 * @param value Value to set.
 * @return int Returns 0 on success, negative on failure.
 */
#define _FOSSIL_SANITY_SYS_SETENV(name, value) \
    fossil_sanity_sys_setenv(name, value)

/**
 * @brief Retrieves the current system timestamp as a formatted string.
 *
 * @return char* Newly allocated string with timestamp (caller must free).
 */
#define _FOSSIL_SANITY_SYS_TIMESTAMP() \
    fossil_sanity_sys_timestamp()

/**
 * @brief Returns uptime in milliseconds since process start.
 *
 * @return long long Milliseconds since process launch.
 */
#define _FOSSIL_SANITY_SYS_UPTIME_MS() \
    fossil_sanity_sys_uptime_ms()

/**
 * @brief Checks if a process is still running.
 *
 * @param pid Process ID.
 * @return int Returns 1 if running, 0 if not, negative on error.
 */
#define _FOSSIL_SANITY_SYS_IS_RUNNING(pid) \
    fossil_sanity_sys_is_running(pid)

/**
 * @brief Attempts to terminate a process by PID.
 *
 * @param pid Process ID.
 * @return int Returns 0 on success, negative on failure.
 */
#define _FOSSIL_SANITY_SYS_KILL(pid) \
    fossil_sanity_sys_kill(pid)

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

/**
 * @brief Creates an empty directory at the specified location.
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_CREATE_DIR function.
 * It is used to create an empty directory with the given name.
 *
 * @param dirname A null-terminated string representing the path to the directory to be created.
 *                The path can be relative or absolute.
 * @return int Returns 0 on successful creation of the directory. Returns a negative value if
 *             the directory could not be created due to errors such as insufficient permissions
 *             or invalid paths.
 */
#define FOSSIL_SANITY_SYS_CREATE_DIR(dirname) \
    _FOSSIL_SANITY_SYS_CREATE_DIR(dirname)

/** 
 * @brief Checks whether a directory exists at the specified location.
 * This macro is a wrapper around the _FOSSIL_SANITY_SYS_DIR_EXISTS function.
 * It is used to check if a directory exists at the given path.
 *
 * @param dirname A null-terminated string representing the path to the directory to check.
 *                The path can be relative or absolute.
 * @return int Returns 1 if the directory exists, and 0 if it does not exist. Note that this
 *             function does not check for directory accessibility or permissions.
 */
#define FOSSIL_SANITY_SYS_DIR_EXISTS(dirname) \
    _FOSSIL_SANITY_SYS_DIR_EXISTS(dirname)

/**
 * @brief Reads the entire contents of a file into memory.
 *
 * The returned buffer is null-terminated and allocated dynamically.
 * The caller is responsible for freeing the returned memory using free().
 *
 * @param filename Path to the file to read.
 * @return char* Pointer to allocated null-terminated buffer on success,
 *               or NULL on failure.
 */
#define FOSSIL_SANITY_SYS_READ_FILE(filename) \
    _FOSSIL_SANITY_SYS_READ_FILE(filename)

/**
 * @brief Writes data to a file, replacing any existing contents.
 *
 * @param filename Path to the file.
 * @param data Null-terminated string to write.
 * @return int Returns 0 on success, negative on failure.
 */
#define FOSSIL_SANITY_SYS_WRITE_FILE(filename, data) \
    _FOSSIL_SANITY_SYS_WRITE_FILE(filename, data)

/**
 * @brief Deletes a file from the filesystem.
 *
 * @param filename Path to the file to delete.
 * @return int Returns 0 on success, negative on failure.
 */
#define FOSSIL_SANITY_SYS_DELETE_FILE(filename) \
    _FOSSIL_SANITY_SYS_DELETE_FILE(filename)

/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param name Name of the environment variable.
 * @return const char* Value of the variable, or NULL if not found.
 */
#define FOSSIL_SANITY_SYS_GETENV(name) \
    _FOSSIL_SANITY_SYS_GETENV(name)

/**
 * @brief Sets or overrides an environment variable.
 *
 * @param name Name of the environment variable.
 * @param value Value to set.
 * @return int Returns 0 on success, negative on failure.
 */
#define FOSSIL_SANITY_SYS_SETENV(name, value) \
    _FOSSIL_SANITY_SYS_SETENV(name, value)

/**
 * @brief Retrieves the current system timestamp as a formatted string.
 *
 * @return char* Newly allocated string with timestamp (caller must free).
 */
#define FOSSIL_SANITY_SYS_TIMESTAMP() \
    _FOSSIL_SANITY_SYS_TIMESTAMP()

/**
 * @brief Returns uptime in milliseconds since process start.
 *
 * @return long long Milliseconds since process launch.
 */
#define FOSSIL_SANITY_SYS_UPTIME_MS() \
    _FOSSIL_SANITY_SYS_UPTIME_MS()

/**
 * @brief Checks if a process is still running.
 *
 * @param pid Process ID.
 * @return int Returns 1 if running, 0 if not, negative on error.
 */
#define FOSSIL_SANITY_SYS_IS_RUNNING(pid) \
    _FOSSIL_SANITY_SYS_IS_RUNNING(pid)

/**
 * @brief Kills a running process.
 *
 * @param pid Process ID.
 * @return int Returns 0 on success, negative on failure.
 */
#define FOSSIL_SANITY_SYS_KILL(pid) \
    _FOSSIL_SANITY_SYS_KILL(pid)

#endif // FOSSIL_SANITY_H
