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
#ifndef FOSSIL_TEST_COMMANDS_H
#define FOSSIL_TEST_COMMANDS_H

#include "fossil/_common/common.h"
#include "types.h"

typedef struct {
    char *description;  // Description of the command
    char *long_name;    // Long name of the command (e.g., --help)
    char *short_name;   // Short name of the command (e.g., -h)
    char **valid_args;  // Array of valid arguments for the command
    int32_t flag;       // Flag indicating if the command is a flag (1) or requires arguments (0)
} fossil_test_command_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Array of available commands.
 */
extern fossil_test_command_t commands[];

/**
 * Parses the command line arguments and populates the provided `fossil_test_command_t` structure.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings representing the command line arguments.
 * @param commands A pointer to the `fossil_test_command_t` structure to be populated.
 */
void fossil_test_cli_parse(int argc, char *argv[], fossil_test_command_t *commands);

/**
 * Displays the help information for the available commands.
 *
 * @param commands A pointer to the `fossil_test_command_t` structure containing the commands.
 */
void fossil_test_cli_show_help(fossil_test_command_t *commands);

/**
 * Handles the execution of a specific command with the provided argument.
 *
 * @param command A pointer to the `fossil_test_command_t` structure representing the command to be executed.
 * @param arg A string representing the argument for the command.
 */
void fossil_test_cli_handle_command(fossil_test_command_t *command, char *arg);

#ifdef __cplusplus
}
#endif

#endif
