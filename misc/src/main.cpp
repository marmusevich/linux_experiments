#include "sharedLib/runOptions.h"
#include "sharedLib/logger.h"

//---
//#include <iostream>

int main(int argc, const char* argv[])
{
	const auto pOpt = NRunOptions::runOptions(argc, argv);

	if (pOpt)
	{
		LOG << *pOpt << "\n";
	}
	else
	{
		LOG_WARNING << "NO OPT SET\n";
	}

	return 0;
}