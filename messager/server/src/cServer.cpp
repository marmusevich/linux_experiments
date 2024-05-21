#include <iostream>

#include <memory>

//#include <utility> //?

#include "cServer.h"
#include "cSession.h"


using boost::asio::ip::tcp;


cServer::cServer(boost::asio::io_context& io_context, short port)
	: mAcceptor(io_context, tcp::endpoint(tcp::v4(), port)),
	mSocket(io_context)
{
	do_accept();
}

void cServer::do_accept()
{
	mAcceptor.async_accept(mSocket,
		[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::cout << "on accept: \n";
				std::cout << "  - local_endpoint: " << mSocket.local_endpoint()  << "\n";
				std::cout << "  - remote_endpoint: " << mSocket.remote_endpoint() << "\n";

				std::make_shared<cSession>(std::move(mSocket))->start();
			}

			do_accept();
		});
}
