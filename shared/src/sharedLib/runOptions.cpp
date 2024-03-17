//see  https://www.boost.org/doc/libs/1_83_0/doc/html/program_options.html

#include "sharedLib/runOptions.h"
#include "sharedLib/logger.h"

#include <iostream>
#include <filesystem>
#include <boost/program_options.hpp>


namespace //meke local to this cpp
{
	namespace po = boost::program_options;
	namespace fs = std::filesystem;

	constexpr char* DEFIULT_CFG_FILE_NAME = "param.cfg";
}

namespace NRunOptions
{
	std::ostream& operator << (std::ostream& os, const sRunOptions& opt)
	{
		os << "addres:" << opt.addres << " port: " << opt.port;
		return os;
	}

	std::optional<sRunOptions> runOptions(int argc, char* argv[])
	{
		po::options_description desc(
			std::string("Param to connect or listen\n"
				"   also you can create config file '")
			+ DEFIULT_CFG_FILE_NAME +
			"' in binary folder"); //, or cpecifi by [config] param path
		desc.add_options()
			("help,h", "Show help")
			("addres,a", po::value<std::string>()->default_value("localhost"), "addres to server, only for the clien")
			("port,p", po::value<int>()->default_value(42042), "port to connect")
			//("config,c", po::value<std::string>(), "path to config file")
			;

		const auto fnPrintHelp = [&desc](bool isPrintUsage = false)
			{
				if (isPrintUsage)
				{
					std::cout << "To usage: " << "\n";
				}
				std::cout << desc << "\n";
			};

		po::variables_map vm;
		try
		{
			auto fnParseFile = [&desc, &vm](const char* filename)
				{
					std::error_code ec;
					bool isCfgEx = fs::exists(filename, ec);
					if (ec)
					{
						LOG_ERROR << "Error occuret by acces to config file'" << filename
							<< "' ( cat [" << ec.category().name() /*<< " - " << ec.category().message()*/ << "]\n"
							<< ec.value() << " - " << ec.message() << ")\n";
					}

					if(isCfgEx)
					{
						try
						{
							po::store(po::parse_config_file<char>(filename, desc), vm);
							return true;
						}
						catch (const po::reading_file& e)
						{
							LOG_ERROR << "Error occuret by parsing config file'" << filename << "' (" << e.what() << ")\n";
						}
					}
					return false;
				};

			if (!fnParseFile(DEFIULT_CFG_FILE_NAME))
			{
				po::store(po::parse_command_line(argc, argv, desc), vm);
			}
			po::notify(vm);

			if (vm.count("help"))
			{
				fnPrintHelp();
				return std::nullopt;
			}


			sRunOptions opt;
			if (vm.count("addres"))
			{
				opt.addres = vm["addres"].as<std::string>();
			}

			if (vm.count("port"))
			{
				opt.port = vm["port"].as<int>();
			}

			return opt;
		}
		catch (const std::exception& e)
		{
			LOG_ERROR << "Error occuret by parsing param (" << e.what() << ")\n";

			fnPrintHelp();
		}
		return std::nullopt;
	}
}