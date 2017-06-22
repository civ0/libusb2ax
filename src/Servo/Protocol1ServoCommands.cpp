#include "./Protocol1ServoCommands.hpp"

#include "./../Protocol/Protocols.hpp"

#include <iostream>
#include <string>

namespace Dynamixel
{
namespace Servo
{

using p1 = Dynamixel::Protocol::Protocol1;


InstructionPacket<p1> Protocol1ServoCommands::Ping(uint8_t id)
{
	return InstructionPacket<p1>(id, Instruction::Ping);
}

InstructionPacket<p1> Protocol1ServoCommands::SetPosition(const p1Model& model, uint8_t id, double degree)
{
	degree += 150;
	uint16_t bytes = static_cast<uint16_t>(degree / 300 * 1023);
	uint8_t low = bytes & 0xFF;
	uint8_t high = (bytes & 0xFF00) >> 8;

	return InstructionPacket<p1>(id, Instruction::Write,
	{model.GoalPosition(), low, high});
}

}
}