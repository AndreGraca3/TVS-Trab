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
#include <fcntl.h>
#include <string.h>

static int run_test(test_function tfunc);

static int run_prog(prog_test_spec prog);

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

void run_stdio_program_tests(prog_test_spec tests[], size_t num_tests, bool stop_at_first_failure) {
	for(int i = 0; i < num_tests; i++) {
		prog_test_spec prog = tests[i];
		printf("[%s]:", prog.test_name);
		int res = run_prog(prog);
		if (res != 0) {
			puts("Assertion Failed!");
			if (stop_at_first_failure) {
				return;
			}
		} else {
			puts("Assertion Succeded!");
		}
	}
}

static int run_prog(prog_test_spec prog) {
	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();
	if (pid == 0) {
		// child 
		close(pipefd[0]);

		dup2(pipefd[1],1); // redirec child's output to pipe.
		close(pipefd[1]);

		int inputFile = open(prog.input_path, O_RDONLY, 0640);
		if (inputFile == -1) {
			perror("open out.txt failed");
			exit(1);
		}
		dup2(inputFile, 0); // redirec child's input to in.txt
		close(inputFile); // close file

		execlp(prog.command, prog.command, NULL);
	} else {
		// parent
		close(pipefd[1]);

		int outputFile = open(prog.output_path, O_RDONLY, 0640);
		if (outputFile == -1) {
			perror("open out.txt failed");
			exit(1);
		}
	
		char expected[256];
		char actual[256];
		for (;;) {
			int nExpected = read(outputFile, expected, 255);
			int nActual = read(pipefd[0], actual, 255);
			if (nExpected == 0 || nActual == 0) break;
			
			expected[nExpected] = 0;
			actual[nActual] = 0;	
		}
		close(pipefd[0]);
		/*printf("[Expected]: %s", expected);
		printf("--------------------------------\n");
		printf("[Actual]: %s", actual);*/

		if (strcmp(actual, expected) != 0) {
			return -1;
		}
	}
	return 0;
}