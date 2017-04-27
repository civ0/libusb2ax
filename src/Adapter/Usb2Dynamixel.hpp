#ifndef ADAPTER_USB2DYNAMIXEL_H
#define ADAPTER_USB2DYNAMIXEL_H

#include <cstddef>
#include <string>
#include <termios.h>

#include "./Baudrate.hpp"
#include "../Exception/Exceptions.hpp"

namespace Dynamixel
{
namespace Adapter
{

class Usb2Dynamixel {
public:
	Usb2Dynamixel()
		: _recvTimeout(0.1), _fd(-1), _reportBadPackets(false) {}

	Usb2Dynamixel(const std::string& name, int baudrate = B115200, double recvTimeout = 0.1)
		: _recvTimeout(recvTimeout), _fd(-1), _reportBadPackets(false)
	{
		OpenSerial(name, baudrate);
	}
	~Usb2Dynamixel()
	{
		CloseSerial();
	}
public:
	void OpenSerial(const std::string&);
	void OpenSerial(const std::string&, int);
	void CloseSerial();
	void Flush();
	bool IsOpen();
private:
	double _recvTimeout;
	static const size_t _recvBufferSize;
	int _fd;
	bool _reportBadPackets;

};

}
}

#endif