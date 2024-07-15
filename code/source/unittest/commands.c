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
#include "fossil/unittest/commands.h"
#include "fossil/unittest/framework.h"
#include "fossil/unittest/console.h"
#include <stdio.h>
#include <stdlib.h>

fossil_options_t _CLI;

// Initialize the options structure
fossil_options_t init_options(void) {
    fossil_options_t options;
    options.show_version = false;
    options.show_help = false;
    options.show_tip = false;
    options.show_info = false;
    options.show_author = false;
    options.only_tags = false;
    options.reverse = false;
    options.repeat_enabled = false;
    options.repeat_count = 1;
    options.shuffle_enabled = false;
    options.verbose_enabled = false;
    options.verbose_level = 1;
    options.list_tests = false;
    options.summary_enabled = false;
    options.color_enabled = false;
    options.sanity_enabled = false;
    return options;
}

// Parse command-line arguments
fossil_options_t fossil_options_parse(int argc, char **argv) {
    fossil_options_t options = init_options();
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            options.show_version = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            options.show_help = true;
        } else if (strcmp(argv[i], "--tip") == 0) {
            options.show_tip = true;
        } else if (strcmp(argv[i], "--info") == 0) {
            options.show_info = true;
        } else if (strcmp(argv[i], "--author") == 0) {
            options.show_author = true;
        } else if (strcmp(argv[i], "only") == 0) {
            options.only_tags = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                strcpy(options.only_tags_value, argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "reverse") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.reverse = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.reverse = false;
            }
        } else if (strcmp(argv[i], "repeat") == 0) {
            options.repeat_enabled = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options.repeat_count = atoi(argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "shuffle") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.shuffle_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.shuffle_enabled = false;
            }
        } else if (strcmp(argv[i], "verbose") == 0) {
            options.verbose_enabled = true;
            if (i + 1 < argc && strcmp(argv[i + 1], "cutback") == 0) {
                options.verbose_level = 0;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "verbose") == 0) {
                options.verbose_level = 2;
            }
        } else if (strcmp(argv[i], "list") == 0) {
            options.list_tests = true;
        } else if (strcmp(argv[i], "summary") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.summary_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.summary_enabled = false;
            }
        } else if (strcmp(argv[i], "color") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.color_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.color_enabled = false;
            }
        } else if (strcmp(argv[i], "sanity") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.sanity_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.sanity_enabled = false;
            }
        }
    }
    
    return options;
}
