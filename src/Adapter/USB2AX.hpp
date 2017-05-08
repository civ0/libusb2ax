#ifndef ADAPTER_USB2AX_H
#define ADAPTER_USB2AX_H

#include <cstddef>
#include <string>
#include <termios.h>

#include "./Baudrate.hpp"
#include "./../Exception/Exceptions.hpp"
#include "./../InstructionPacket.hpp"
#include "./../StatusPacket.hpp"

namespace Dynamixel
{
namespace Adapter
{

class USB2AX {
public:
	USB2AX()
		: _recvTimeout(0.1), _fd(-1), _reportBadPackets(false) {}

	USB2AX(const std::string& name, int baudrate = B115200, double recvTimeout = 0.1)
		: _recvTimeout(recvTimeout), _fd(-1), _reportBadPackets(false)
	{
		OpenSerial(name, baudrate);
	}
	~USB2AX()
	{
		CloseSerial();
	}
public:
	void OpenSerial(const std::string&);
	void OpenSerial(const std::string&, int);
	void CloseSerial();
	void Flush();
	bool IsOpen();
	template <typename ProtocolType>
	void Send(const InstructionPacket<ProtocolType>&);
	template <typename ProtocolType>
	StatusPacket<ProtocolType> Receive();
private:
	double _recvTimeout;
	static const size_t _recvBufferSize;
	int _fd;
	bool _reportBadPackets;

};

}
}

#endif