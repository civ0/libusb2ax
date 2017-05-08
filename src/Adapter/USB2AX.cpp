#include "./USB2AX.hpp"

#include <cstring>
#include <fcntl.h>

using namespace std;

namespace Dynamixel
{
namespace Adapter
{

const size_t USB2AX::_recvBufferSize = 256;

void USB2AX::OpenSerial(const string& name)
{
	OpenSerial(name, B115200);
}

void USB2AX::OpenSerial(const string& name, int baudrate)
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

void USB2AX::CloseSerial()
{
	close(_fd);
	_fd = -1;
}

void USB2AX::Flush()
{
	tcflush(_fd, TCIFLUSH);
}

bool USB2AX::IsOpen()
{
	return (_fd != -1);
}

template <typename ProtocolType>
void USB2AX::Send(const InstructionPacket<ProtocolType>& packet)
{
	if (_fd == -1)
		throw Exception::DynamixelAdapterException()
		                << Exception::StringInfo("Adapter was closed while attempting to send");

	int ret = write(_fd, packet.DataPointer(), packet.size());

	if (ret != packet.size())
		throw Exception::DynamixelAdapterException()
		                << Exception::StringInfo("Error while writing packet");
}

template <typename ProtocolType>
StatusPacket<ProtocolType> USB2AX::Receive()
{
	
}

}
}