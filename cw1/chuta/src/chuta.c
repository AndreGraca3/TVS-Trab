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
	int executed = 0;
	int succeded = 0;
	for (int i = 0; i < num_tests; i++) {
		int res = run_test(tests[i]);
		executed++;
		if (WIFEXITED(res)) {
			// EXIT
			if (WEXITSTATUS(res) == EXIT_SUCCESS) {
				printf("Test[%d]: SUCCESS\n", i);
				succeded++;
			} else {
				printf("Test[%d]: ASSERTION FAILED\n", i);
				if (stop_at_first_failure) break;
			}
		} else {
			// SIGNAL
			printf("Test[%d]: TERMINATED(%d)\n", i, WTERMSIG(res));
			if (stop_at_first_failure) break;
		}
	}
	printf("Total number of tests: %ld\n", num_tests);
	printf("The number of tests executed: %d\n", executed);
	printf("The number of tests succeded: %d\n", succeded);
}

static int run_test(test_function tfunc) {
	pid_t pid = fork();
	if (pid == 0) { 
		// child
		tfunc();
		exit(EXIT_SUCCESS);
	} else {
		// parent
		int res = 0;
		waitpid(pid, &res, 0);
		return res;
	}
}
