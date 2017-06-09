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

struct DynamixelControllerException : virtual boost::exception, virtual std::exception {};

struct DynamixelPacketException : virtual boost::exception, virtual std::exception {};

struct DynamixelStatusPacketException : virtual boost::exception, virtual std::exception {};

struct DynamixelUnknownServoModelException : virtual boost::exception, virtual std::exception {};

}
}

#endif