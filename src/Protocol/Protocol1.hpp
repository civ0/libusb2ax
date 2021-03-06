#ifndef PROTOCOL_PROTOCOL1_HPP
#define PROTOCOL_PROTOCOL1_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../Exception/Exceptions.hpp"

namespace Dynamixel
{
namespace Protocol
{

class Protocol1
{
  public:
	enum class Instruction : uint8_t
	{
		Ping = 0x01,
		Read = 0x02,
		Write = 0x03,
		RegWrite = 0x04,
		Action = 0x05,
		FactoryReset = 0x06,
		SyncWrite = 0x83
	};

	enum class ErrorCode : uint8_t
	{
		InputVoltage = 0x01,
		AngleLimit = 0x02,
		Overheating = 0x04,
		Range = 0x08,
		Checksum = 0x10,
		Overload = 0x20,
		Instruction = 0x40
	};

	enum class DecodeState
	{
		Invalid,
		Ongoing,
		Done
	};

  public:
	Protocol1() = default;
	~Protocol1() = default;

  public:
	static std::vector<uint8_t> PackInstruction(uint8_t, Instruction);
	static std::vector<uint8_t> PackInstruction(uint8_t, Instruction, const std::vector<uint8_t> &);
	static DecodeState Unpack(const std::vector<uint8_t> &, uint8_t &, std::vector<uint8_t> &,
							  std::vector<ErrorCode> &);

  private:
	static bool DetectStatusHeader(const std::vector<uint8_t> &);
	static void GetErrors(const uint8_t &, std::vector<ErrorCode> &);
	static uint8_t Checksum(const std::vector<uint8_t> &);
};
}
}

#endif