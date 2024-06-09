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
#ifndef FSCL_MOD_H
#define FSCL_MOD_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Adds two integers.
 *
 * This function takes two integer values, 'a' and 'b', and returns their sum.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of 'a' and 'b'.
 */
int add(int a, int b);

/**
 * Subtracts one integer from another.
 *
 * This function takes two integer values, 'a' and 'b', and returns the result of
 * subtracting 'b' from 'a'.
 *
 * @param a The integer from which 'b' will be subtracted.
 * @param b The integer to subtract from 'a'.
 * @return The result of 'a' - 'b'.
 */
int subtract(int a, int b);

#ifdef __cplusplus
}
#endif

#endif
