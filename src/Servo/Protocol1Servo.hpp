#ifndef SERVO_PROTOCOL1SERVO_H
#define SERVO_PROTOCOL1SERVO_H

#include "./Protocol1Model.hpp"
#include "./../Protocol/Protocols.hpp"
#include "./../InstructionPacket.hpp"

#include <cstdint>
#include <vector>

namespace Dynamixel
{
namespace Servo
{

class Protocol1Servo {
public:
	using p1Model = Protocol1Model;
	using p1 = Dynamixel::Protocol::Protocol1;
	using Instruction = Protocol::Protocol1::Instruction;

	Protocol1Servo() = default;
	~Protocol1Servo() = default;

	Protocol1Servo(p1Model::Name, uint8_t);
public:
	// Instructions
	InstructionPacket<p1> Ping();
	InstructionPacket<p1> SetPosition(double);
private:
	Protocol1Model _model;
	uint8_t _id;
};

}
}

#endif