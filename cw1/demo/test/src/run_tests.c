////////////////////////////////////////////
//
// ISEL - System Virtualization Techniques
// Autumn/Winter 2023/24
//
// Coursework Assignment #1
//

#include "chuta.h"
#include "ftests.h"

///////////////////////////////
// 
// DECLARE ALL FUNCTION TESTS
//
test_function all_function_tests[] = {
	test_add,
	test_sub,
	test_sub_with_message,
	test_strsize,
	test_strsize_with_message,
};

//////////////////////////////
// 
// DECLARE ALL PROGRAM TESTS
//

char input_path[] = "files/input.txt";

prog_test_spec all_program_tests[] = {
	{"cat test", "cat", input_path, "files/cat_output.txt"}, // Succeded!
	{"grep test", "grep -i ficheiro", input_path, "files/grep_output.txt"},
	{"sort test", "sort", input_path, "files/sort_output.txt"}, // Succeded!
	{"another sort test", "sort", input_path, "files/wc_output.txt"}, // Note: this test is meant to fail !
	{"wc test", "wc", input_path, "files/wc_output.txt"} // Succeded!
};

////////////////////////
// 
// RUN ALL TESTS
//
#define ARRLEN(arr) (sizeof(arr)/sizeof(arr[0]))

const size_t num_function_tests = ARRLEN(all_function_tests);
const size_t num_program_tests = ARRLEN(all_program_tests);

int main() {
	
	run_function_tests(all_function_tests, num_function_tests, false);
	
	run_stdio_program_tests(all_program_tests, num_program_tests, false);
	
	return 0;
}
