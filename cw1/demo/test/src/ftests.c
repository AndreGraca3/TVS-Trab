////////////////////////////////////////////
//
// ISEL - System Virtualization Techniques
// Autumn/Winter 2023/24
//
// Coursework Assignment #1
//

#include "ftests.h"

#include "chuta.h"
#include "somecode.h"

void test_add() {
	
	int res = add(2, 2);
	
	CH_ASSERT(res == 4);
}

void test_sub() {
	
	int res = sub(5, 2);
	
	CH_ASSERT(res == 3);
}

void test_sub_with_message() {
	
	int res = sub(5, 2);

	CH_ASSERT_MSG(res == 3, "I can't believe its not 3!");
}

void test_strsize() {
	
	size_t size = strsize("ISEL");
	
	CH_ASSERT(size == 4);
}

void test_strsize_with_message() {

	size_t size = strsize("ISEL");

	CH_ASSERT_MSG(size == 4, "This never gets here because of termination inside strsize.");
}