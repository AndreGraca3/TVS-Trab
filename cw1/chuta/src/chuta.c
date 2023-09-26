////////////////////////////////////////////
//
// ISEL - System Virtualization Techniques
// Autumn/Winter 2023/24
//
// Coursework Assignment #1
//

#include "chuta.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int run_test(test_function tfunc);

void run_function_tests(test_function tests[], size_t num_tests, bool stop_at_first_failure) {
	for (int i = 0; i < num_tests; i++) {
		run_test(tests[i]);
	}
}

static int run_test(test_function tfunc) {
	pid_t pid = fork();
	if (pid == 0) { 
		// child
		return CH_ASSERT(tfunc);
	} else {
		// parent
		int res = 0;
		waitpid(pid, &res, 0);
		if (WIFEXITED(res)) {
			printf("PARENT: child returned %d\n", 
				WEXITSTATUS(res)
			);
		} else {
			printf("PARENT: child terminated\n"); 
		}
	}
}
