#include "./Usb2Dynamixel.hpp"

#include <cstring>
#include <fcntl.h>

namespace Dynamixel
{
namespace Adapter
{

const size_t Usb2Dynamixel::_recvBufferSize = 256;

void Usb2Dynamixel::OpenSerial(const std::string& name)
{
	OpenSerial(name, B115200);
}

void Usb2Dynamixel::OpenSerial(const std::string& name, int baudrate)
{
	struct termios tio_serial;

	if (_fd != -1)
		throw Exception::DynamixelAdapterException()
		                << Exception::StringInfo("Error opening adapter " + name
		                                + ": resource busy");

	_fd = open(name.c_str(), O_RDWR | O_NOCTTY);
	if (_fd == -1)
		throw Exception::DynamixelAdapterException()
		                << Exception::StringInfo("Error opening adapter " + name)
		                << boost::errinfo_errno(errno);

	bzero(&tio_serial, sizeof(tio_serial));
	tio_serial.c_cflag = CS8 | CLOCAL | CREAD;
	tio_serial.c_iflag = IGNBRK | IGNPAR;
	tio_serial.c_oflag = 0;
	tio_serial.c_lflag = 0;
	tio_serial.c_cc[VMIN] = 0;

	cfsetispeed(&tio_serial, baudrate);
	cfsetospeed(&tio_serial, baudrate);

	cfgetispeed(&tio_serial);
	tcflush(_fd, TCIFLUSH);
	tcsetattr(_fd, TCSANOW, &tio_serial);
}

void Usb2Dynamixel::CloseSerial()
{
	close(_fd);
	_fd = -1;
}

void Usb2Dynamixel::Flush()
{
	tcflush(_fd, TCIFLUSH);
}

bool Usb2Dynamixel::IsOpen()
{
	return (_fd != -1);
}

}
}