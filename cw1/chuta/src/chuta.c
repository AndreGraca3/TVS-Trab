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
		printf("Test %d: ", i + 1);

		if (WIFEXITED(res)) {
			// EXIT
			if (WEXITSTATUS(res) == EXIT_SUCCESS) {
				puts("SUCCESS");
				succeded++;
			} else {
				puts("ASSERTION_FAILED");
				if (stop_at_first_failure) break;
			}
		} else {
			// SIGNAL
			printf("TERMINATED(%d)\n", WTERMSIG(res));
			if (stop_at_first_failure) break;
		}
		puts("");
	}
	printf("-> %d/%ld tests executed: %d passed, %d failed\n", executed, num_tests, succeded, executed - succeded);
}

static int run_test(test_function tfunc) {
	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();
	if (pid == 0) {
		// child
		close(pipefd[0]);
		dup2(pipefd[1], 2);

		tfunc();

		close(pipefd[1]);
		exit(EXIT_SUCCESS);
	} else {
		// parent
		close(pipefd[1]);

		for(;;) {
			char msg[256];
			int n = read(pipefd[0], msg, 255);
			if (n == 0) break; // wait for all pipe output descriptors to be closed

			printf("%s\n", msg);
		}
		close(pipefd[0]);

		int res = 0;
		waitpid(pid, &res, 0);
		return res;
	}
}
