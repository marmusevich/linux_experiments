#pragma once

#include <string>
#include <optional>
#include <span>
#include <iosfwd> //fwd std::ostream

/*
	get parameters from command promt
*/
namespace NRunOptions
{
	struct sRunOptions
	{
		uint32_t port;
		std::string addres;

		friend std::ostream& operator << (std::ostream& os, const sRunOptions& opt);
	};

	std::optional<sRunOptions> runOptions(std::span<const char*> arg);
}

