#include "sharedLib/runOptions.h"
#include "sharedLib/logger.h"

//---
//#include <iostream>

int main(int argc, char* argv[])
{
	const auto opt = NRunOptions::runOptions(argc, argv);

	if (opt)
	{
		LOG << *opt << "\n";
	}
	else
	{
		LOG_WARNING << "NO OPT SET\n";
	}

	return 0;
}