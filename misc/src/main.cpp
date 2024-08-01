#include <span>

#include "sharedLib/runOptions.h"
#include "sharedLib/logger.h"

//---
//#include <iostream>


void co_main();
void stl_perfomance();

void fsm_main();

void cv_main();
void tq_main();

int main(int argc, const char* argv[])
{
	co_main();
	//stl_perfomance();
	//fsm_main();
	//cv_main();
	//tq_main();
	return 0;

	const auto pOpt = NRunOptions::runOptions(std::span(argv, argc));

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