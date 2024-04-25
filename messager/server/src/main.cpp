

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

int main()
{
#ifdef _WIN32 || _WIN64
    std::setlocale(LC_ALL, "ru_RU"); //optional - in my win machine instaled rus windows 64
#endif // DEBUG


    namespace asio = boost::asio;

    boost::system::error_code ec;
    asio::io_context context;

    constexpr char* ADDRES{ "93.184.216.34" };
    //constexpr char* ADDRES{ "localhost" };
    //constexpr char* ADDRES{ "127.0.0.1" };
    //constexpr char* ADDRES{ "www.google.com" };

    asio::ip::tcp::endpoint ad{ asio::ip::make_address(ADDRES, ec), 80 };

    if (ec)
    {
        std::cout << "Error construct addres '" << ADDRES << "'  <" << ec.message() << "> \n";
        return 0;
    }

    asio::ip::tcp::socket soc{ context };
    soc.connect(ad, ec);

    if (!ec)
    {
        std::cout << "OK\n";
    }
    else
    {
        std::cout << "Error connect to '" << ADDRES << "'  <"<<ec.message() << "> \n";
        return 0;
    }

    if (!soc.is_open())
    {
        return 0;
    }

    const std::string req
    {
        "GET index.html HTTP/1.1\r\n"
        "Host: exemple.com\r\n"
        "Connection: close\r\n\r\n"
    };

    soc.write_some(asio::buffer(req.data(), req.size()), ec);
    std::cout << "write_some  <" << ec.message() << "> \n";

    auto bytes = soc.available();
    std::cout << "bytes: " << bytes << "\n";

    if (bytes > 0)
    {
        std::vector<char> buf(bytes);
        auto readed = soc.read_some(asio::buffer(buf.data(), buf.size()), ec);

        std::cout << "read_some readed = "<< readed <<"  <" << ec.message() << "> \n";

        for (auto c : buf) 
        {
            std::cout << c;
        }
            
        std::cout << "\n";
    }

    return 0;
}