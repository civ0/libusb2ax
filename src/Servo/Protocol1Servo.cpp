#include "./Protocol1Servo.hpp"

#include "./../Protocol/Protocols.hpp"

#include <iostream>
#include <string>

namespace Dynamixel
{
namespace Servo
{

using Protocol1 = proto::Protocol1;

template <typename Model>
InstructionPacket<Protocol1> Protocol1Servo<Model>::Ping()
{
	return InstructionPacket<Protocol1>(_id, Instruction::Ping);
}

template <typename Model>
InstructionPacket<Protocol1> Protocol1Servo<Model>::GetTemperature()
{
	return InstructionPacket<Protocol1>(_id, Instruction::Read,
	{static_cast<uint8_t>(Model::Address::PresentTemperature), 1});
}

template <typename Model>
InstructionPacket<Protocol1> Protocol1Servo<Model>::GetPosition()
{
	return InstructionPacket<Protocol1>(_id, Instruction::Read,
	{static_cast<uint8_t>(Model::Address::PresentPosition), 2});
}

template <typename Model>
InstructionPacket<Protocol1> Protocol1Servo<Model>::SetPosition(double degree)
{
	degree += 150;
	uint16_t bytes = static_cast<uint16_t>(degree / 300 * 1023);
	uint8_t low = bytes & 0xFF;
	uint8_t high = (bytes & 0xFF00) >> 8;

	return InstructionPacket<Protocol1>(_id, Instruction::Write,
	{static_cast<uint8_t>(Model::Address::GoalPosition), low, high});
}

template class Protocol1Servo<AX12>;

}
}