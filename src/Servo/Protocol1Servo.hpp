#ifndef SERVO_PROTOCOL1SERVO_H
#define SERVO_PROTOCOL1SERVO_H

#include "./ServoModels.hpp"
#include "./../Protocol/Protocols.hpp"
#include "./../InstructionPacket.hpp"

#include <cstdint>
#include <vector>

namespace proto = Dynamixel::Protocol;

namespace Dynamixel
{
namespace Servo
{

template <typename Model>
class Protocol1Servo {
public:
	using Protocol1 = proto::Protocol1;
	using Instruction = proto::Protocol1::Instruction;

	Protocol1Servo() = default;
	~Protocol1Servo() = default;

	Protocol1Servo(uint8_t id) : _id(id) { }
public:
	// Instructions
	InstructionPacket<Protocol1> Ping();
	InstructionPacket<Protocol1> GetTemperature();
	InstructionPacket<Protocol1> GetPosition();
	InstructionPacket<Protocol1> SetPosition(double);
private:
	uint8_t _id;
};

}
}

#endif