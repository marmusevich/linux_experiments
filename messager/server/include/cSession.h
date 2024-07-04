#pragma once

#include <memory>

#include <boost/asio/ts/internet.hpp>


class cSession : public std::enable_shared_from_this<cSession>
{
public:
    cSession(boost::asio::ip::tcp::tcp::socket socket);

    void start();

private:
    void do_read();
    void do_write(std::size_t length);
	
    boost::asio::ip::tcp::socket mSocket;


    enum { max_length = 1024 };
    uint8_t read_data[max_length];
    uint8_t write_data[max_length];
};
