
#include <clocale>//std::setlocale

#include <iostream>

#include <boost/asio/io_context.hpp>

#include "cServer.h"



int main(int argc, const char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
    std::setlocale(LC_ALL, "ru_RU"); //optional - in my win machine instaled rus windows 64
#endif // DEBUG

    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        cServer s(io_context, std::atoi(argv[1]));

        std::cout << "Started on " << argv[1] <<" port\n";

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
