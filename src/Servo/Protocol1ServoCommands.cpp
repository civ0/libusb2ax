#include "Protocol1ServoCommands.hpp"

#include "../Protocol/Protocols.hpp"

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

InstructionPacket<p1> Protocol1ServoCommands::GetPosition(const p1Model& model, uint8_t id)
{
	return InstructionPacket<p1>(id, Instruction::Read, {model.PresentPosition(), 2});
}

InstructionPacket<p1> Protocol1ServoCommands::SetPosition(const p1Model& model, uint8_t id,
                double degree)
{
	degree += 150;
	uint16_t bytes = static_cast<uint16_t>(degree / 300 * 1023);
	uint8_t low = bytes & 0xFF;
	uint8_t high = (bytes & 0xFF00) >> 8;
	return InstructionPacket<p1>(id, Instruction::Write, {model.GoalPosition(), low, high});
}

InstructionPacket<p1> Protocol1ServoCommands::GetSpeed(const p1Model& model, uint8_t id)
{
	return InstructionPacket<p1>(id, Instruction::Read, {model.PresentSpeed(), 2});
}

InstructionPacket<p1> Protocol1ServoCommands::SetSpeed(const p1Model& model, uint8_t id,
                double speed)
{
	uint16_t bytes = static_cast<uint16_t>(speed * 1023);
	uint8_t low = bytes & 0xFF;
	uint8_t high = (bytes & 0xFF00) >> 8;
	return InstructionPacket<p1>(id, Instruction::Write, {model.MovingSpeed(), low, high});
}

}
}