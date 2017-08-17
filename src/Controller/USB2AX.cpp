#include "USB2AX.hpp"

#include <cstring>
#include <fcntl.h>
#include <thread>

namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;

namespace Dynamixel
{
namespace Controller
{

const size_t USB2AX::_recvBufferSize = 256;

void USB2AX::OpenSerial(const std::string &name)
{
	OpenSerial(name, B115200);
}

void USB2AX::OpenSerial(const std::string &name, int baudrate)
{
	currentbBudrate = baudrate;

	struct termios tio_serial;

	if (fd != -1)
		throw ex::DynamixelControllerException()
			<< ex::StringInfo("Error opening adapter " + name + ": resource busy");

	fd = open(name.c_str(), O_RDWR | O_NOCTTY);
	if (fd == -1)
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
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &tio_serial);
}

void USB2AX::CloseSerial()
{
	close(fd);
	fd = -1;
}

void USB2AX::Flush()
{
	tcflush(fd, TCIFLUSH);
}

bool USB2AX::IsOpen()
{
	return (fd != -1);
}

template <class ProtocolType>
void USB2AX::Send(const InstructionPacket<ProtocolType> &packet)
{
	if (fd == -1)
		throw ex::DynamixelControllerException()
			<< ex::StringInfo("Adapter was closed while attempting to send");

	// Hack: the elements of the vector are stored consecutively, so pointer arithmetic can be
	// used
	int ret = write(fd, packet.DataPointer(), packet.size());

	// check if bytes where sent and check if the correct number of bytes where sent
	if (ret > 0 && static_cast<size_t>(ret) != packet.size())
		throw ex::DynamixelControllerException()
			<< ex::StringInfo("Error while writing packet");
}

template void USB2AX::Send<proto::Protocol1>(const InstructionPacket<proto::Protocol1> &);

template <class ProtocolType>
StatusPacket<ProtocolType> USB2AX::Receive()
{
	using DecodeState = typename ProtocolType::DecodeState;

	if (fd == -1)
		throw ex::DynamixelControllerException()
			<< ex::StringInfo("Adapter was closed while attempting to read");

	std::vector<uint8_t> packet;
	packet.reserve(_recvBufferSize);
	StatusPacket<ProtocolType> status;
	DecodeState state = DecodeState::Ongoing;
	auto time = std::chrono::steady_clock::now();
	do
	{
		auto currentTime = std::chrono::steady_clock::now();

		uint8_t byte;
		int ret = read(fd, &byte, sizeof(byte));
		if (ret > 0)
		{
			packet.push_back(byte);
			state = status.Decode(packet);
			if (state == DecodeState::Invalid)
				throw ex::DynamixelStatusPacketException()
					<< ex::StringInfo("StatusPacket is invalid");

			time = currentTime;
		}

		// wait the time one byte needs to arrive
		auto sleepFor = std::chrono::duration<double>(8.0 / currentbBudrate);
		std::this_thread::sleep_for(sleepFor);

		if (currentTime - time > recvTimeout)
			throw ex::DynamixelStatusPacketException()
				<< ex::StringInfo("Timeout while reading bytes");
	} while (state != DecodeState::Done);

	return status;
}

template StatusPacket<proto::Protocol1> USB2AX::Receive();
}
}