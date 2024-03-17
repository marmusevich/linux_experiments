#pragma once
//#define BOOST_LOG_DYN_LINK 1


// TODO  wrap boost::log and make it as imol


#include <boost/log/trivial.hpp>


namespace NLogger
{

}

#define LOG                BOOST_LOG_TRIVIAL(info)
#define LOG_WARNING        BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR          BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL          BOOST_LOG_TRIVIAL(fatal)

