#ifndef INSTRUCTIONPACKET_HPP
#define INSTRUCTIONPACKET_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Dynamixel
{

template <class ProtocolType>
class InstructionPacket {
public:
	InstructionPacket(uint8_t id, typename ProtocolType::Instruction instruction)
		: packet(ProtocolType::PackInstruction(id, instruction)) {}

	InstructionPacket(uint8_t id, typename ProtocolType::Instruction instruction,
	                  const std::vector<uint8_t>& parameters)
		: packet(ProtocolType::PackInstruction(id, instruction, parameters)) {}

	InstructionPacket(const InstructionPacket& other) : packet(other.packet) {}

	InstructionPacket(InstructionPacket&& other) : packet(other.packet) {}

	~InstructionPacket() = default;

public:
	decltype(auto) size() const
	{
		return packet.size();
	}

	decltype(auto) operator[](size_t index) const
	{
		return packet[index];
	}

	decltype(auto) begin()
	{
		return packet.begin();
	}

	decltype(auto) end()
	{
		return packet.end();
	}

	const uint8_t* DataPointer() const
	{
		return &packet.front();
	}

private:
	std::vector<uint8_t> packet;
};

}

#endif