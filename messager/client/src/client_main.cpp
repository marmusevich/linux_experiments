
#include <clocale>//std::setlocale

#include <cstring>
#include <iostream>

#include <boost/asio.hpp>

#include "sharedLib/logger.h"


enum { max_length = 1024 };

int main(int argc, const char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
    std::setlocale(LC_ALL, "ru_RU"); //optional - in my win machine instaled rus windows 64
#endif // DEBUG

    try
    {
        //if (argc != 3)
        //{
        //    std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
        //    return 1;
        //}

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket soced(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);

        //boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));
        boost::asio::connect(soced, resolver.resolve("localhost", "55000"));

        LOG << "started \n";


        while (true)
        {
            std::cout << "Enter message: ";
            char request[max_length];
            std::cin.getline(request, max_length);
            size_t request_length = std::strlen(request);
            boost::asio::write(soced, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(soced,boost::asio::buffer(reply, request_length));
            std::cout << "Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
