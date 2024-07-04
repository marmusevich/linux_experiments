//#include <utility> //?

#include <boost/asio/ts/buffer.hpp>

#include "sharedLib/logger.h"

#include "cSession.h"


cSession::cSession(boost::asio::ip::tcp::socket socket)
	: mSocket(std::move(socket))
	, read_data()
	, write_data()
{
}

void cSession::start()
{
	do_read();
}


void cSession::do_read()
{
	auto self(shared_from_this());
	mSocket.async_read_some(boost::asio::buffer(read_data, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				LOG << "ON READ [ " << mSocket.remote_endpoint() << " ] (" << length << " bytes): ";

				std::memcpy(write_data, read_data, length);

				do_write(length);


				/*
				auto input = std::string(read_data, length);
				LOG << "ON READ [ " << mSocket.remote_endpoint() << " ] (" << length << " bytes): " << input;

				//process data
				std::string output;
				output = "[process data] --->" + input;
				std::strcpy(write_data, output.c_str());

				do_write(output.size());
				*/
			}
		});
}

void cSession::do_write(std::size_t length)
{
	//LOG << "DO WRITE [ " << mSocket.remote_endpoint() <<" ] (" << length << " bytes): " << std::string(write_data, length);

	auto self(shared_from_this());
	boost::asio::async_write(mSocket, boost::asio::buffer(write_data, length),
		[this, self](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				//LOG << "ON WRITE [ " << mSocket.remote_endpoint() << " ] (" << length << " bytes): " << std::string(write_data, length);

				do_read();
			}
		});
}

