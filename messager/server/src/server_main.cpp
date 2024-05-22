
#include <clocale>//std::setlocale


#include <boost/asio/io_context.hpp>

#include "cServer.h"

#include "sharedLib/logger.h"
#include "sharedLib/runOptions.h"



int main(int argc, const char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
    std::setlocale(LC_ALL, "ru_RU"); //optional - in my win machine instaled rus windows 64
#endif // DEBUG

    try
    {
        const auto pOpt = NRunOptions::runOptions(std::span(argv, argc));
        if (!pOpt)
        {
            LOG_WARNING << "NO OPT SET\n";
            return -1;
        }


        boost::asio::io_context io_context;

        cServer s(io_context, pOpt->port);

        LOG << "Started on " << pOpt->port <<" port";

        io_context.run();
    }
    catch (std::exception& e)
    {
        LOG_ERROR << "Exception: " << e.what();
    }

    return 0;
}
