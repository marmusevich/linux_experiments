#include <gtest/gtest.h>

#include "sharedLib/runOptions.h"


namespace NRunOptionsTest
{
	TEST(runOptions, emptyParam_returnDefault)
	{
		const char* argv[] = {"my_own_name_of_executable_file"};
		const auto pOpt = NRunOptions::runOptions(argv);
		ASSERT_TRUE(pOpt);
		const auto& opt = *pOpt;
		ASSERT_EQ("localhost", opt.addres);
		ASSERT_EQ(42042, opt.port);
	}

	TEST(runOptions, todo_extend_tests)
	{
		const char* argv[] = { "my_own_name_of_executable_file", "-p", "9999", "-a", "127.0.0.1" };
		const auto pOpt = NRunOptions::runOptions(argv);
		ASSERT_TRUE(pOpt);
		const auto& opt = *pOpt;
		ASSERT_EQ("127.0.0.1", opt.addres);
		ASSERT_EQ(9999, opt.port);
	}
}