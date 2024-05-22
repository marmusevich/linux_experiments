#include <memory>

//#include <utility> //?


#include "sharedLib/logger.h"

#include "cServer.h"
#include "cSession.h"


//using boost::asio::ip::tcp;


cServer::cServer(boost::asio::io_context& io_context, short port)
	: mAcceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	, mSocket(io_context)
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
				LOG_TRACE << "on accept:"
						  << "\n  - local_endpoint: " << mSocket.local_endpoint()
				          << "\n  - remote_endpoint: " << mSocket.remote_endpoint();

				std::make_shared<cSession>(std::move(mSocket))->start();
			}

			do_accept();
		});
}
