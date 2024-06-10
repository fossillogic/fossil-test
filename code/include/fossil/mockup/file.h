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
#ifndef FOSSIL_MOCK_FILE_H
#define FOSSIL_MOCK_FILE_H

#include "internal.h"

#ifdef __cplusplus
extern "C"
{
#endif

// File mock object type
typedef struct fossil_mockup_file {
    char *filename;
    char *content;
    size_t size;
    size_t position;
    struct fossil_mockup_file *next; // for chaining files
} fossil_mockup_file_t;

/** 
 * Create a new file mock object
 * 
 * @param filename The name of the file
 * @param content The content of the file
 * @return A pointer to the created file mock object
 */
fossil_mockup_file_t* fossil_mockup_file_create(const char *filename, const char *content);

/** 
 * Read from the mocked file
 * 
 * @param ptr Pointer to the buffer where the read data will be stored
 * @param size Size of each element to be read
 * @param nmemb Number of elements to be read
 * @param file Pointer to the file mock object
 * @return The total number of elements successfully read
 */
size_t fossil_mockup_file_read(void *ptr, size_t size, size_t nmemb, fossil_mockup_file_t *file);

/** 
 * Write to the mocked file
 * 
 * @param ptr Pointer to the buffer containing the data to be written
 * @param size Size of each element to be written
 * @param nmemb Number of elements to be written
 * @param file Pointer to the file mock object
 * @return The total number of elements successfully written
 */
size_t fossil_mockup_file_write(const void *ptr, size_t size, size_t nmemb, fossil_mockup_file_t *file);

/** 
 * Seek to a position in the mocked file
 * 
 * @param file Pointer to the file mock object
 * @param offset Number of bytes to offset from the position specified by whence
 * @param whence Position used as reference for the offset
 * @return 0 if successful, -1 otherwise
 */
int fossil_mockup_file_seek(fossil_mockup_file_t *file, long offset, int whence);

/** 
 * Reset the mocked file object for reuse
 * 
 * @param file Pointer to the file mock object
 */
void fossil_mockup_file_reset(fossil_mockup_file_t *file);

/** 
 * Erase the mocked file object
 * 
 * @param file Pointer to the file mock object
 */
void fossil_mockup_file_erase(fossil_mockup_file_t *file);

#ifdef __cplusplus
}
#endif

#endif
