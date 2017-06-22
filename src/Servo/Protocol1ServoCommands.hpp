#ifndef SERVO_PROTOCOL1SERVOCOMMANDS_H
#define SERVO_PROTOCOL1SERVOCOMMANDS_H

#include "./Protocol1Model.hpp"
#include "./../Protocol/Protocols.hpp"
#include "./../InstructionPacket.hpp"

#include <cstdint>
#include <vector>

namespace Dynamixel
{
namespace Servo
{

class Protocol1ServoCommands {
	using p1Model = Protocol1Model;
	using p1 = Dynamixel::Protocol::Protocol1;
	using Instruction = Protocol::Protocol1::Instruction;
public:
	static InstructionPacket<p1> Ping(uint8_t id);
	static InstructionPacket<p1> SetPosition(const p1Model&, uint8_t id, double);
};

}
}

#endif