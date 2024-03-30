#include <gtest/gtest.h>
//#include "../src/global.h"

int add(int a, int b) {
	return a + b;
}

TEST(TEST_ADD, UNSIGNED_INT_VALUE) {
	int result = add(100, 200);
	EXPECT_EQ(result, 300);
	result = add(200, 300);
	EXPECT_NE(result, 400);
}

//
//TEST(TEST_getpublicipaddress, UNSIGNED_INT_VALUE) {
//	getpublicipaddress();
//	int result = add(100, 200);
//	EXPECT_EQ(result, 300);
//	result = add(200, 300);
//	EXPECT_NE(result, 400);
//}

