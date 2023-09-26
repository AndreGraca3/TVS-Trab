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

#define CH_ASSERT(test_expression) \
	(do { \
		if (!(test_expression)) { \
			puts("Test Failed!"); \
		}; \
	} while (0))

typedef void (*test_function)();

void run_function_tests(test_function tests[], size_t num_tests, bool stop_at_first_failure);

#endif // CHUTA_H

