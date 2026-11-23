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
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_SANITY_H
#define FOSSIL_SANITY_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Executes a system command and returns its exit code.
 *
 * @param command A null-terminated system command formatted as it would be entered in a shell.
 * 
 * @return int 0 on success; a non-zero value indicates an execution error or command status.
 * 
 * @note The command is executed by the system shell and may be platform-dependent.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_execute(const char* command);

/**
 * @brief Retrieves the process ID of the current process.
 *
 * @return int The current process ID.
 * 
 * @note The returned value can be used for debugging or process management.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_getpid(void);

/**
 * @brief Suspends the current thread for a specified duration.
 *
 * @param milliseconds The non-negative number of milliseconds to sleep.
 * 
 * @return void This function does not return a value.
 * 
 * @note A value of 0 may yield the processor to other threads without a delay.
 */
FOSSIL_MAIP_API void fossil_sanity_sys_sleep(int milliseconds);

/**
 * @brief Creates an empty file at the specified location.
 *
 * @param filename A null-terminated path for the file to create.
 * 
 * @return int 0 on success; a negative value if the file could not be created.
 * 
 * @note Existing file contents may be truncated according to platform behavior.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_create_file(const char* filename);

/**
 * @brief Checks whether a file exists at the specified location.
 *
 * @param filename A null-terminated path to check.
 * 
 * @return int 1 if the path exists, 0 otherwise.
 * 
 * @note This function does not verify that the path is accessible or is a regular file.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_file_exists(const char* filename);

/**
 * @brief Creates an empty directory at the specified location.
 *
 * @param dirname A null-terminated path for the directory to create.
 * 
 * @return int 0 on success; a negative value if the directory could not be created.
 * 
 * @note Behavior when the directory already exists is platform-dependent.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_create_dir(const char* dirname);

/**
 * @brief Checks whether a directory exists at the specified location.
 *
 * @param dirname A null-terminated path to check.
 * 
 * @return int 1 if the directory exists, 0 otherwise.
 * 
 * @note This function does not check directory accessibility or permissions.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_dir_exists(const char* dirname);

/**
 * @brief Reads the entire contents of a file into memory.
 *
 * @param filename A null-terminated path to the file to read.
 * 
 * @return char* A dynamically allocated null-terminated buffer on success, or NULL on failure.
 * 
 * @note The caller must free the returned buffer with free().
 */
FOSSIL_MAIP_API char* fossil_sanity_sys_read_file(const char* filename);

/**
 * @brief Writes data to a file, replacing any existing contents.
 *
 * @param filename A null-terminated path to the file to write.
 * @param data A null-terminated string to write to the file.
 * 
 * @return int 0 on success; a negative value on failure.
 * 
 * @note Any existing file contents are replaced.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_write_file(const char* filename, const char* data);

/**
 * @brief Deletes a file from the filesystem.
 *
 * @param filename A null-terminated path to the file to delete.
 * 
 * @return int 0 on success; a negative value on failure.
 * 
 * @note The file must exist and the caller must have permission to remove it.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_delete_file(const char* filename);

/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param name A null-terminated environment variable name.
 * 
 * @return const char* The variable value, or NULL if it is not found.
 * 
 * @note The returned pointer is owned by the environment implementation and must not be freed.
 */
FOSSIL_MAIP_API const char* fossil_sanity_sys_getenv(const char* name);

/**
 * @brief Sets or overrides an environment variable.
 *
 * @param name A null-terminated environment variable name.
 * @param value A null-terminated value to assign.
 * 
 * @return int 0 on success; a negative value on failure.
 * 
 * @note Environment variable behavior is platform-dependent.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_setenv(const char* name, const char* value);

/**
 * @brief Retrieves the current system timestamp as a formatted string.
 *
 * @return char* A dynamically allocated formatted timestamp, or NULL on failure.
 * 
 * @note The caller must free the returned string.
 */
FOSSIL_MAIP_API char* fossil_sanity_sys_timestamp(void);

/**
 * @brief Returns process uptime in milliseconds.
 *
 * @return long long Milliseconds elapsed since process launch.
 * 
 * @note The measurement begins when the process starts, not when this function is first called.
 */
FOSSIL_MAIP_API long long fossil_sanity_sys_uptime_ms(void);

/**
 * @brief Checks whether a process is still running.
 *
 * @param pid The process ID to check.
 * 
 * @return int 1 if running, 0 if not, or a negative value on error.
 * 
 * @note Results for processes that are not owned by the caller may be platform-dependent.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_is_running(int pid);

/**
 * @brief Attempts to terminate a process by its process ID.
 *
 * @param pid The process ID to terminate.
 * 
 * @return int 0 on success; a negative value on failure.
 * 
 * @note Termination requires sufficient platform permissions and may not be immediate.
 */
FOSSIL_MAIP_API int fossil_sanity_sys_kill(int pid);

#ifdef __cplusplus
}
#endif

// *****************************************************************************
// Private API Macros
// *****************************************************************************


#define _FOSSIL_SANITY_SYS_EXECUTE(command) \
    fossil_sanity_sys_execute(command)

#define _FOSSIL_SANITY_SYS_GETPID() \
    fossil_sanity_sys_getpid()

#define _FOSSIL_SANITY_SYS_SLEEP(milliseconds) \
    fossil_sanity_sys_sleep(milliseconds)

#define _FOSSIL_SANITY_SYS_CREATE_FILE(filename) \
    fossil_sanity_sys_create_file(filename)

#define _FOSSIL_SANITY_SYS_FILE_EXISTS(filename) \
    fossil_sanity_sys_file_exists(filename)

#define _FOSSIL_SANITY_SYS_CREATE_DIR(dirname) \
    fossil_sanity_sys_create_dir(dirname)

#define _FOSSIL_SANITY_SYS_DIR_EXISTS(dirname) \
    fossil_sanity_sys_dir_exists(dirname)

#define _FOSSIL_SANITY_SYS_READ_FILE(filename) \
    fossil_sanity_sys_read_file(filename)

#define _FOSSIL_SANITY_SYS_WRITE_FILE(filename, data) \
    fossil_sanity_sys_write_file(filename, data)

#define _FOSSIL_SANITY_SYS_DELETE_FILE(filename) \
    fossil_sanity_sys_delete_file(filename)

#define _FOSSIL_SANITY_SYS_GETENV(name) \
    fossil_sanity_sys_getenv(name)

#define _FOSSIL_SANITY_SYS_SETENV(name, value) \
    fossil_sanity_sys_setenv(name, value)

#define _FOSSIL_SANITY_SYS_TIMESTAMP() \
    fossil_sanity_sys_timestamp()

#define _FOSSIL_SANITY_SYS_UPTIME_MS() \
    fossil_sanity_sys_uptime_ms()

#define _FOSSIL_SANITY_SYS_IS_RUNNING(pid) \
    fossil_sanity_sys_is_running(pid)

#define _FOSSIL_SANITY_SYS_KILL(pid) \
    fossil_sanity_sys_kill(pid)

// *****************************************************************************
// Public API Macros
// *****************************************************************************

/**
 * @def FOSSIL_SANITY_SYS_EXECUTE(command)
 * @brief Executes a system command and returns the exit code.
 * @param command A null-terminated command string to execute.
 * @return int Exit code returned by the system command.
 * @note A zero return value typically indicates success; nonzero values indicate failure or a command-specific status.
 */
#define FOSSIL_SANITY_SYS_EXECUTE(command) \
    _FOSSIL_SANITY_SYS_EXECUTE(command)

/**
 * @def FOSSIL_SANITY_SYS_GETPID()
 * @brief Retrieves the process ID of the current process.
 * @return int The process ID of the current process.
 * @note The returned value is supplied by the underlying platform API.
 */
#define FOSSIL_SANITY_SYS_GETPID() \
    _FOSSIL_SANITY_SYS_GETPID()

/**
 * @def FOSSIL_SANITY_SYS_SLEEP(milliseconds)
 * @brief Suspends execution of the current thread for a duration.
 * @param milliseconds Number of milliseconds to sleep; must be nonnegative.
 * @return void This macro performs no value-producing operation.
 * @note A value of zero may yield execution to other threads without an intentional delay.
 */
#define FOSSIL_SANITY_SYS_SLEEP(milliseconds) \
    _FOSSIL_SANITY_SYS_SLEEP(milliseconds)

/**
 * @def FOSSIL_SANITY_SYS_CREATE_FILE(filename)
 * @brief Creates an empty file at the specified location.
 * @param filename Null-terminated path to the file to create.
 * @return int Zero on success, or a negative value on failure.
 * @note Existing files may be left unchanged or replaced according to platform behavior.
 */
#define FOSSIL_SANITY_SYS_CREATE_FILE(filename) \
    _FOSSIL_SANITY_SYS_CREATE_FILE(filename)

/**
 * @def FOSSIL_SANITY_SYS_FILE_EXISTS(filename)
 * @brief Checks whether a file exists at the specified location.
 * @param filename Null-terminated path to the file to check.
 * @return int One if the file exists, zero if it does not exist, or a negative value on error.
 * @note This check does not guarantee that the file is readable or writable.
 */
#define FOSSIL_SANITY_SYS_FILE_EXISTS(filename) \
    _FOSSIL_SANITY_SYS_FILE_EXISTS(filename)

/**
 * @def FOSSIL_SANITY_SYS_CREATE_DIR(dirname)
 * @brief Creates an empty directory at the specified location.
 * @param dirname Null-terminated path to the directory to create.
 * @return int Zero on success, or a negative value on failure.
 * @note The requested parent directories are not necessarily created.
 */
#define FOSSIL_SANITY_SYS_CREATE_DIR(dirname) \
    _FOSSIL_SANITY_SYS_CREATE_DIR(dirname)

/**
 * @def FOSSIL_SANITY_SYS_DIR_EXISTS(dirname)
 * @brief Checks whether a directory exists at the specified location.
 * @param dirname Null-terminated path to the directory to check.
 * @return int One if the directory exists, zero if it does not exist, or a negative value on error.
 * @note This check does not guarantee that the directory is accessible.
 */
#define FOSSIL_SANITY_SYS_DIR_EXISTS(dirname) \
    _FOSSIL_SANITY_SYS_DIR_EXISTS(dirname)

/**
 * @def FOSSIL_SANITY_SYS_READ_FILE(filename)
 * @brief Reads the entire contents of a file into memory.
 * @param filename Null-terminated path to the file to read.
 * @return char* Newly allocated, null-terminated buffer on success, or NULL on failure.
 * @note The caller must release the returned buffer with free().
 */
#define FOSSIL_SANITY_SYS_READ_FILE(filename) \
    _FOSSIL_SANITY_SYS_READ_FILE(filename)

/**
 * @def FOSSIL_SANITY_SYS_WRITE_FILE(filename, data)
 * @brief Writes data to a file, replacing any existing contents.
 * @param filename Null-terminated path to the file.
 * @param data Null-terminated string to write.
 * @return int Zero on success, or a negative value on failure.
 * @note The file is created if it does not already exist.
 */
#define FOSSIL_SANITY_SYS_WRITE_FILE(filename, data) \
    _FOSSIL_SANITY_SYS_WRITE_FILE(filename, data)

/**
 * @def FOSSIL_SANITY_SYS_DELETE_FILE(filename)
 * @brief Deletes a file from the filesystem.
 * @param filename Null-terminated path to the file to delete.
 * @return int Zero on success, or a negative value on failure.
 * @note Directories and missing files are not deleted by this operation.
 */
#define FOSSIL_SANITY_SYS_DELETE_FILE(filename) \
    _FOSSIL_SANITY_SYS_DELETE_FILE(filename)

/**
 * @def FOSSIL_SANITY_SYS_GETENV(name)
 * @brief Retrieves the value of an environment variable.
 * @param name Null-terminated name of the environment variable.
 * @return const char* Value associated with the variable, or NULL if not found.
 * @note The returned pointer's lifetime is managed by the platform environment API.
 */
#define FOSSIL_SANITY_SYS_GETENV(name) \
    _FOSSIL_SANITY_SYS_GETENV(name)

/**
 * @def FOSSIL_SANITY_SYS_SETENV(name, value)
 * @brief Sets or overrides an environment variable.
 * @param name Null-terminated name of the environment variable.
 * @param value Null-terminated value to assign.
 * @return int Zero on success, or a negative value on failure.
 * @note The variable remains set in the environment of the current process.
 */
#define FOSSIL_SANITY_SYS_SETENV(name, value) \
    _FOSSIL_SANITY_SYS_SETENV(name, value)

/**
 * @def FOSSIL_SANITY_SYS_TIMESTAMP()
 * @brief Retrieves the current system timestamp as a formatted string.
 * @return char* Newly allocated timestamp string on success, or NULL on failure.
 * @note The caller must release the returned string with free().
 */
#define FOSSIL_SANITY_SYS_TIMESTAMP() \
    _FOSSIL_SANITY_SYS_TIMESTAMP()

/**
 * @def FOSSIL_SANITY_SYS_UPTIME_MS()
 * @brief Returns elapsed time in milliseconds since process start.
 * @return long long Milliseconds elapsed since process launch.
 * @note The exact launch-time reference is determined by the underlying implementation.
 */
#define FOSSIL_SANITY_SYS_UPTIME_MS() \
    _FOSSIL_SANITY_SYS_UPTIME_MS()

/**
 * @def FOSSIL_SANITY_SYS_IS_RUNNING(pid)
 * @brief Checks whether a process is still running.
 * @param pid Process ID to check.
 * @return int One if running, zero if not running, or a negative value on error.
 * @note PID reuse and platform-specific process visibility may affect the result.
 */
#define FOSSIL_SANITY_SYS_IS_RUNNING(pid) \
    _FOSSIL_SANITY_SYS_IS_RUNNING(pid)

/**
 * @def FOSSIL_SANITY_SYS_KILL(pid)
 * @brief Requests termination of a running process.
 * @param pid Process ID to terminate.
 * @return int Zero on success, or a negative value on failure.
 * @note The caller needs sufficient platform permissions to terminate the process.
 */
#define FOSSIL_SANITY_SYS_KILL(pid) \
    _FOSSIL_SANITY_SYS_KILL(pid)

#endif // FOSSIL_SANITY_H
