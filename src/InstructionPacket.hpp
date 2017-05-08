#ifndef INSTRUCTIONPACKET_H
#define INSTRUCTIONPACKET_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace Dynamixel
{

template <typename ProtocolType>
class InstructionPacket {
public:
	InstructionPacket(typename ProtocolType::id_t id,
	                  typename ProtocolType::Instruction instruction)
		: _packet(ProtocolType::PackInstruction(id, instruction)) {}

	InstructionPacket(typename ProtocolType::id_t id,
	                  typename ProtocolType::Instruction instruction,
	                  const std::vector<uint8_t>& parameters)
		: _packet(ProtocolType::PackInstruction(id, instruction, parameters)) {}

	~InstructionPacket() = default;

public:
	size_t size() const
	{
		return _packet.size();
	}

	uint8_t operator[](size_t index) const
	{
		return _packet[index];
	}

	const uint8_t* DataPointer() const
	{
		return &_packet.front();
	}

private:
	std::vector<uint8_t> _packet;
};

}

#endif