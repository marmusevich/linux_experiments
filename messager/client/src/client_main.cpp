
#include <clocale>//std::setlocale

#include <cstring>
#include <iostream>

#include <chrono>
#include <thread>
#include <string>

#include <locale>


#include <boost/asio.hpp>

#include "sharedLib/logger.h"
#include "sharedLib/runOptions.h"



//-----------------------------------------------------------------------------------------------------------------------
struct sLocaleHelper
{
    sLocaleHelper()

    {
#if defined(_WIN32) || defined(_WIN64)
        char const* l = std::setlocale(LC_ALL, nullptr);
        loc = (l == nullptr ? "" : l);
        std::setlocale(LC_ALL, "C");
#endif
    }

    ~sLocaleHelper()
    {
#if defined(_WIN32) || defined(_WIN64)
        if (!loc.empty())
        {
            std::setlocale(LC_ALL, loc.c_str());
        }
#endif
    }
private:
    std::string loc;
};
//-----------------------------------------------------------------------------------------------------------------------
enum { max_length = 1024 };
//-----------------------------------------------------------------------------------------------------------------------


int simple_client(const NRunOptions::sRunOptions& param)
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket soced(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);

        boost::asio::connect(soced, resolver.resolve(param.addres, std::to_string(param.port)));

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

int simple_client_w(const NRunOptions::sRunOptions& param)
{
    try
    {
        sLocaleHelper _sLocaleHelper;

        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket soced(io_context);
        boost::asio::ip::tcp::resolver resolver(io_context);

        boost::asio::connect(soced, resolver.resolve(param.addres, std::to_string(param.port)));

        while (true)
        {
            std::wcout << "Enter message: ";
            wchar_t request[max_length];
            std::wcin.getline(request, max_length);
            size_t request_length = std::wcslen(request);
            boost::asio::write(soced, boost::asio::buffer(request, request_length * sizeof(wchar_t)));

            //--------------------------

            wchar_t  reply[max_length];
            size_t reply_length = boost::asio::read(soced, boost::asio::buffer(reply, request_length * sizeof(wchar_t)));

            std::wcout << "Reply is: ";
            std::wcout <<" { " << std::wstring(reply, reply_length / sizeof(wchar_t)) <<" }";
            std::wcout << "\n";
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}



int test(const NRunOptions::sRunOptions& param)
{
    LOG << "test server.... \n";

    while (true)
    {
        try
        {
            boost::asio::io_context io_context;
            boost::asio::ip::tcp::socket soced(io_context);
            boost::asio::ip::tcp::resolver resolver(io_context);

            boost::asio::connect(soced, resolver.resolve(param.addres, std::to_string(param.port)));

            const auto id = std::this_thread::get_id();
            std::stringstream ss;
            ss <<"thread id = " << id;
            const auto sId = ss.str();

            //const char request[]{"Test request"};
            char request[max_length]{};
            std::strcpy(request, sId.c_str());
            
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
#endif


    const auto pOpt = NRunOptions::runOptions(std::span(argv, argc));
    if (!pOpt)
    {
        LOG_WARNING << "NO OPT SET\n";
        return -1;
    }

    LOG << "Try connect to: " << pOpt->addres << " : " << pOpt->port;



    //return test(*pOpt);

    //return simple_client(*pOpt);

    return simple_client_w(*pOpt);

}