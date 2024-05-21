#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ts/internet.hpp>

class cServer
{
public:
    cServer(boost::asio::io_context& io_context, short port);

private:
    void do_accept();


    boost::asio::ip::tcp::acceptor mAcceptor;
    boost::asio::ip::tcp::socket mSocket;
};
