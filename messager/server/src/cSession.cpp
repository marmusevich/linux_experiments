//#include <utility> //?

#include <boost/asio/ts/buffer.hpp>

#include "sharedLib/logger.h"

#include "cSession.h"


cSession::cSession(boost::asio::ip::tcp::socket socket)
	: mSocket(std::move(socket))
	, data_()
{
}

void cSession::start()
{
	do_read();
}


void cSession::do_read()
{
	auto self(shared_from_this());
	mSocket.async_read_some(boost::asio::buffer(data_, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				do_write(length);
			}
		});
}

void cSession::do_write(std::size_t length)
{
	LOG << "[ " << mSocket.remote_endpoint() <<" ] (" << length << " bytes): " << std::string(data_, length) << "\n";

	auto self(shared_from_this());
	boost::asio::async_write(mSocket, boost::asio::buffer(data_, length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				do_read();
			}
		});
}

