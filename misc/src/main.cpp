#include <iostream>
#include <string>

//see  https://www.boost.org/doc/libs/1_83_0/doc/html/program_options.html
#include <boost/program_options.hpp>




namespace opt = boost::program_options;


int main( int argc, char *argv[])
{
    opt::options_description desc("All opt");
    desc.add_options()
        ("apples", opt::value<int>()->default_value(0), "how many apples do you have")
        ("oranges", opt::value<int>()->default_value(0), "how many oranges do you have")
        ("name,n", opt::value<std::string>(), "Some name")
        ("help,h", "produce help message")
        ;

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    auto it_a = vm.find("apples");
    auto it_o = vm.find("oranges");
    if (it_a != vm.end() && it_o != vm.end())
    {
        std::cout << "Fruits count: "
            << vm["apples"].as<int>() + vm["oranges"].as<int>()
            << "\n";
    }


    if (auto it = vm.find("name"); it != vm.end())
    {
        std::cout << it->first << " = " << it->second.as<std::string>() << "\n";
    }


    return 0;
}
