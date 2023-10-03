////////////////////////////////////////////
//
// ISEL - System Virtualization Techniques
// Autumn/Winter 2023/24
//
// Coursework Assignment #1
//

#ifndef CHUTA_H
#define CHUTA_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define ANSI_RED_CODE "\x1B[31m"
#define ANSI_RESET_CODE "\x1B[0m"

#define CH_ASSERT(test_expression) do { \
    if (!(test_expression)) { \
    	exit(EXIT_FAILURE); \
    } \
} while (0)

#define CH_ASSERT_MSG(test_expression, error_msg) do { \
    if (!(test_expression)) { \
		fprintf(stderr, \
        "Assertion failed %s at (%s : %d) \n -> Expected: %s(%s)%s \n -> Message: %s", \
        __FILE__, \
        __func__, \
        __LINE__, \
        ANSI_RED_CODE, \
        #test_expression, \
        ANSI_RESET_CODE, \
        error_msg); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

typedef void (*test_function)();

void run_function_tests(test_function tests[], size_t num_tests, bool stop_at_first_failure);

#endif // CHUTA_H

