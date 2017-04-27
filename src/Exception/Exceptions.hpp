#ifndef EXCEPTION_EXCEPTIONS_H
#define EXCEPTION_EXCEPTIONS_H

#include <cstddef>
#include <exception>
#include <iostream>
#include <string>

#include <boost/exception/all.hpp>

namespace Dynamixel
{
namespace Exception
{

typedef boost::error_info<struct tag_StringInfo, std::string> StringInfo;
struct DynamixelException : virtual boost::exception, virtual std::exception {};

struct DynamixelAdapterException : virtual boost::exception, virtual std::exception {};

}
}

#endif