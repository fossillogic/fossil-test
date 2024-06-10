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

#include "fossil/common/common.h"
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

#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

extern fossil_test_command_t commands[];

/**
 * Create a new command object
 * 
 * @param description The description of the command
 * @param long_name The long name of the command
 * @param short_name The short name of the command
 * @param valid_args The valid arguments of the command
 * @param flag The flag of the command
 * @return A pointer to the newly created command object
 */

void fossil_test_cli_parse(int argc, char *argv[], fossil_test_command_t *commands);
void fossil_test_cli_show_help(fossil_test_command_t *commands);
void fossil_test_cli_handle_command(fossil_test_command_t *command, char *arg);

#ifdef __cplusplus
}
#endif

#endif
