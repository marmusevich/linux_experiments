#include "sharedLib/runOptions.h"


//---
#include <iostream>

int main(int argc, char* argv[])
{
	const auto opt = NRunOptions::runOptions(argc, argv);

	if (opt)
	{
		std::cout << *opt << "\n";
	}
	else
	{
			std::cout << "NO OPT SET\n";
	}

	return 0;
}