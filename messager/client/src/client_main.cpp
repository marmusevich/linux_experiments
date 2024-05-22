
#include <clocale>//std::setlocale

#include <cstring>
#include <iostream>

#include <chrono>
#include <thread>
#include <string>


#include <boost/asio.hpp>

#include "sharedLib/logger.h"


enum { max_length = 1024 };

int main1(int argc, const char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket soced(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);

        boost::asio::connect(soced, resolver.resolve(argv[1], argv[2]));
        //boost::asio::connect(soced, resolver.resolve("localhost", "55000"));

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


int test()
{
    LOG << "test server.... \n";

    while (true)
    {
        try
        {
            boost::asio::io_context io_context;
            boost::asio::ip::tcp::socket soced(io_context);
            boost::asio::ip::tcp::resolver resolver(io_context);

            boost::asio::connect(soced, resolver.resolve("localhost", "55000"));

            const char request[]{"Test request"};
            size_t request_length = std::strlen(request);
            boost::asio::write(soced, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(soced, boost::asio::buffer(reply, request_length));

            LOG  <<(request_length == reply_length ? "OK" : "FALL") << " Request is: [" << request << "] Reply is: [" << std::string(reply, reply_length) <<"]";

        }
        catch (std::exception& e)
        {
            LOG_ERROR << "Exception: " << e.what() << "\n";
        }


        using namespace std::chrono_literals;
        std::this_thread::sleep_for(5000ms);

    }

    return 0;
}

int main(int argc, const char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
    std::setlocale(LC_ALL, "ru_RU"); //optional - in my win machine instaled rus windows 64
#endif // DEBUG

    return test();

    const char* fake_argv[] = { "main", "localhost", "55000" };
    return main1(3, fake_argv);

}