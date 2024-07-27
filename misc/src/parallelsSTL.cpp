#include <algorithm>
#include <cmath>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

namespace
{
	constexpr int64_t SIZE = 50'000'000;
	const double PI = std::acos(-1);

	template <typename FUNC>
	void printExecTime(const std::string_view title, FUNC func)
	{
		const auto start = std::chrono::steady_clock::now();
		func();

		const std::chrono::duration<double> dur = std::chrono::steady_clock::now() - start;

		std::cout << title << " : " << dur.count() << " sec. \n";
	}
}



void stl_perfomance()
{
	std::cout << "\n";

	std::vector<double> values;
	values.reserve(SIZE);

	std::mt19937 engine;
	std::uniform_real_distribution<> urDistr(0, PI / 2);
	for (uint64_t i = 0; i < SIZE; ++i)
	{
		values.push_back(urDistr(engine));
	}

	std::vector<double> w(values);

	printExecTime("std::execution::seq", 
		[w]() mutable
		{
			std::transform(std::execution::seq, w.begin(), w.end(), w.begin(),
				[](double arg) { return std::tan(arg); });
		});

	printExecTime("std::execution::unseq",
		[w]() mutable
		{
			std::transform(std::execution::unseq, w.begin(), w.end(), w.begin(),
				[](double arg) { return std::tan(arg); });
		});

	printExecTime("std::execution::par_unseq",
		[w]() mutable
		{
			std::transform(std::execution::par_unseq, w.begin(), w.end(), w.begin(),
				[](double arg) { return std::tan(arg); });
		});

	printExecTime("std::execution::par",
		[w]() mutable
		{
			std::transform(std::execution::par, w.begin(), w.end(), w.begin(),
				[](double arg) { return std::tan(arg); });
		});



}

