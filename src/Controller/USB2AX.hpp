#ifndef ADAPTER_USB2AX_HPP
#define ADAPTER_USB2AX_HPP

#include <chrono>
#include <cstddef>
#include <string>
#include <termios.h>

#include "../Exception/Exceptions.hpp"
#include "../InstructionPacket.hpp"
#include "../StatusPacket.hpp"
#include "Baudrate.hpp"

namespace Dynamixel
{
namespace Controller
{

class USB2AX
{
  public:
	USB2AX()
		: recvTimeout(100), fd(-1) {}

	USB2AX(const std::string &name, int baudrate = B1000000, size_t timeout = 100)
		: recvTimeout(timeout), fd(-1)
	{
		OpenSerial(name, baudrate);
	}
	~USB2AX()
	{
		CloseSerial();
	}

  public:
	void OpenSerial(const std::string &);
	void OpenSerial(const std::string &, int);
	void CloseSerial();
	void Flush();
	bool IsOpen();
	template <class ProtocolType>
	void Send(const InstructionPacket<ProtocolType> &);
	template <class ProtocolType>
	StatusPacket<ProtocolType> Receive();

  private:
	int currentbBudrate;
	std::chrono::milliseconds recvTimeout;
	static const size_t _recvBufferSize;
	int fd;
};
}
}

#endif