#ifndef ADAPTER_BAUDRATE_HPP
#define ADAPTER_BAUDRATE_HPP

#include <cstddef>
#include <termios.h>

#include "../Exception/Exceptions.hpp"

namespace Dynamixel
{
namespace Controller
{

inline int GetBaudrate(const unsigned int baudrate)
{
	switch (baudrate) {
	case 0:
		return B0;
		break; /* hang up */
	case 50:
		return B50;
		break;
	case 75:
		return B75;
		break;
	case 110:
		return B110;
		break;
	case 134:
		return B134;
		break;
	case 150:
		return B150;
		break;
	case 200:
		return B200;
		break;
	case 300:
		return B300;
		break;
	case 600:
		return B600;
		break;
	case 1200:
		return B1200;
		break;
	case 1800:
		return B1800;
		break;
	case 2400:
		return B2400;
		break;
	case 4800:
		return B4800;
		break;
	case 9600:
		return B9600;
		break;
	case 19200:
		return B19200;
		break;
	case 38400:
		return B38400;
		break;
	case 57600:
		return B57600;
		break;
	case 115200:
		return B115200;
		break;
	case 230400:
		return B230400;
		break;
	default:
		throw Exception::DynamixelException() << Exception::StringInfo("Invalid baudrate: "
		                                      + baudrate);
	}
}

}
}

#endif