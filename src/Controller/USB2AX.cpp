#include "./USB2AX.hpp"

#include <cstring>
#include <fcntl.h>

namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;

namespace Dynamixel
{
namespace Controller
{

const size_t USB2AX::_recvBufferSize = 256;

void USB2AX::OpenSerial(const std::string& name)
{
	OpenSerial(name, B115200);
}

void USB2AX::OpenSerial(const std::string& name, int baudrate)
{
	struct termios tio_serial;

	if (_fd != -1)
		throw ex::DynamixelControllerException()
		                << ex::StringInfo("Error opening adapter " + name
		                                  + ": resource busy");

	_fd = open(name.c_str(), O_RDWR | O_NOCTTY);
	if (_fd == -1)
		throw ex::DynamixelControllerException()
		                << ex::StringInfo("Error opening adapter " + name)
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
		throw ex::DynamixelControllerException()
		                << ex::StringInfo("Adapter was closed while attempting to send");

	int ret = write(_fd, packet.DataPointer(), packet.size());

	// check if bytes where sent and check if the correct number of bytes where sent
	if (ret > 0 && static_cast<size_t>(ret) != packet.size())
		throw ex::DynamixelControllerException()
		                << ex::StringInfo("Error while writing packet");
}

template void  USB2AX::Send<proto::Protocol1>(const InstructionPacket<proto::Protocol1>&);

template <typename ProtocolType>
StatusPacket<ProtocolType> USB2AX::Receive()
{
	using DecodeState = typename ProtocolType::DecodeState;

	if (_fd == -1)
		throw ex::DynamixelControllerException()
		                << ex::StringInfo("Adapter was closed while attempting to read");

	std::vector<uint8_t> packet;
	packet.reserve(_recvBufferSize);
	StatusPacket<ProtocolType> status;
	DecodeState state = DecodeState::Ongoing;
	auto time = std::chrono::steady_clock::now();
	do {
		auto currentTime = std::chrono::steady_clock::now();

		uint8_t byte;
		int ret = read(_fd, &byte, sizeof(byte));
		if (ret > 0) {
			packet.push_back(byte);
			state = status.Decode(packet);
			if (state == DecodeState::Invalid)
				throw ex::DynamixelStatusPacketException()
				                << ex::StringInfo("StatusPacket is invalid");

			time = currentTime;
		}

		if (currentTime - time > _recvTimeout)
			throw ex::DynamixelStatusPacketException()
			                << ex::StringInfo("fuck");
	} while (state != DecodeState::Done);

	return status;
}

template StatusPacket<proto::Protocol1> USB2AX::Receive();

}
}