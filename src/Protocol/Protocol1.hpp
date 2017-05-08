#ifndef PROTOCOL_PROTOCOL1_H
#define PROTOCOL_PROTOCOL1_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include "../Exception/Exceptions.hpp"

namespace Dynamixel
{
namespace Protocol
{

class Protocol1 {
public:
	using id_t = uint8_t;
	using instr_t = uint8_t;
	using address_t = uint8_t;
	using length_t = uint8_t;

	enum class Instruction : instr_t {
		Ping = 0x01,
		Read = 0x02,
		Write = 0x03,
		RegWrite = 0x04,
		Action = 0x05,
		FactoryReset = 0x06,
		SyncWrite = 0x83
	};

	enum class DecodeState {
		Invalid,
		Ongoing,
		Done
	};
public:
	Protocol1() = default;
	~Protocol1() = default;
public:
	static std::vector<uint8_t> PackInstruction(id_t, Instruction);
	static std::vector<uint8_t> PackInstruction(id_t, Instruction, const std::vector<uint8_t>&);
	static DecodeState Unpack(const std::vector<uint8_t>&, id_t&, std::vector<uint8_t>&);
private:
	static bool DetectStatusHeader(const std::vector<uint8_t>&);
	static uint8_t Checksum(const std::vector<uint8_t>&);
};

}
}

#endif