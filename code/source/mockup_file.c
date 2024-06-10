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
#include "fossil/mockup/file.h"
#include <string.h>

fossil_mockup_file_t* fossil_mockup_file_create(const char *filename, const char *content) {
    fossil_mockup_file_t *file = (fossil_mockup_file_t *)malloc(sizeof(fossil_mockup_file_t));
    if (file == NULL) {
        perror("Failed to allocate memory for file mock");
        exit(EXIT_FAILURE);
    }
    file->filename = _custom_fossil_mockup_core_strdup(filename);
    file->content = _custom_fossil_mockup_core_strdup(content);
    file->size = strlen(content);
    file->position = 0;
    file->next = NULL;
    return file;
}

size_t fossil_mockup_file_read(void *ptr, size_t size, size_t nmemb, fossil_mockup_file_t *file) {
    size_t bytes_to_read = size * nmemb;
    if (file->position + bytes_to_read > file->size) {
        bytes_to_read = file->size - file->position;
    }
    memcpy(ptr, file->content + file->position, bytes_to_read);
    file->position += bytes_to_read;
    return bytes_to_read / size;
}

size_t fossil_mockup_file_write(const void *ptr, size_t size, size_t nmemb, fossil_mockup_file_t *file) {
    size_t bytes_to_write = size * nmemb;
    if (file->position + bytes_to_write > file->size) {
        file->content = (char *)realloc(file->content, file->position + bytes_to_write + 1);
        file->size = file->position + bytes_to_write;
    }
    memcpy(file->content + file->position, ptr, bytes_to_write);
    file->position += bytes_to_write;
    file->content[file->position] = '\0'; // Null-terminate the content
    return bytes_to_write / size;
}

int fossil_mockup_file_seek(fossil_mockup_file_t *file, long offset, int whence) {
    switch (whence) {
        case SEEK_SET:
            file->position = offset;
            break;
        case SEEK_CUR:
            file->position += offset;
            break;
        case SEEK_END:
            file->position = file->size + offset;
            break;
        default:
            return -1;
    }
    if (file->position > file->size) {
        file->position = file->size;
    } else if (file->position <= 0) {
        file->position = 0;
    }
    return 0;
}

void fossil_mockup_file_reset(fossil_mockup_file_t *file) {
    file->position = 0;
}

void fossil_mockup_file_erase(fossil_mockup_file_t *file) {
    free(file->filename);
    free(file->content);
    free(file);
}
