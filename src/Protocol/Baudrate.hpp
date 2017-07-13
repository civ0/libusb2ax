#ifndef PROTOCOL_BAUDRATE_HPP
#define PROTOCOL_BAUDRATE_HPP

#include <cstddef>

#include "Protocol1.hpp"

namespace Dynamixel
{
namespace Protocol
{

template <class Protocol>
inline uint8_t GetBaudrateID(unsigned int baudrate)
{
	return 0;
}

template <>
inline uint8_t GetBaudrateID<class Protocol::Protocol1>(unsigned int baudrate)
{
	switch (baudrate) {
	case 9600:
		return 207;
	case 19200:
		return 103;
	case 57600:
		return 34;
	case 115200:
		return 16;
	case 200000:
		return 9;
	case 250000:
		return 7;
	case 400000:
		return 4;
	case 500000:
		return 3;
	case 1000000:
		return 1;
	default:
		return 0;
	}
}

}
}


#endif