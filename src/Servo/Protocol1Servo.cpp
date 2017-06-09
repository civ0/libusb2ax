#include "./Protocol1Servo.hpp"

#include "./../Protocol/Protocols.hpp"

#include <iostream>
#include <string>

namespace Dynamixel
{
namespace Servo
{

using p1 = Dynamixel::Protocol::Protocol1;

Protocol1Servo::Protocol1Servo(p1Model::Name name, uint8_t id) :
	_model(p1Model::FromName(name)), _id(id) {}

InstructionPacket<p1> Protocol1Servo::Ping()
{
	return InstructionPacket<p1>(_id, Instruction::Ping);
}

InstructionPacket<p1> Protocol1Servo::SetPosition(double degree)
{
	degree += 150;
	uint16_t bytes = static_cast<uint16_t>(degree / 300 * 1023);
	uint8_t low = bytes & 0xFF;
	uint8_t high = (bytes & 0xFF00) >> 8;

	return InstructionPacket<p1>(_id, Instruction::Write,
	{_model.GoalPosition(), low, high});
}

}
}