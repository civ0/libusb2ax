#ifndef SERVO_PROTOCOL1SERVOCOMMANDS_HPP
#define SERVO_PROTOCOL1SERVOCOMMANDS_HPP

#include <cstdint>
#include <vector>

#include "../InstructionPacket.hpp"
#include "../Protocol/Protocols.hpp"
#include "Protocol1Model.hpp"

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
	static InstructionPacket<p1> GetPosition(const p1Model&, uint8_t);
	static InstructionPacket<p1> SetPosition(const p1Model&, uint8_t, double);
	static InstructionPacket<p1> GetSpeed(const p1Model&, uint8_t);
	static InstructionPacket<p1> SetSpeed(const p1Model&, uint8_t, double);
	static InstructionPacket<p1> GetTemperature(const p1Model&, uint8_t);
};

}
}

#endif