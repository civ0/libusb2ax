#ifndef SERVO_PROTOCOL1SERVO_H
#define SERVO_PROTOCOL1SERVO_H

#include "./ServoModels.hpp"
#include "./../Protocol/Protocols.hpp"
#include "./../InstructionPacket.hpp"

#include <cstdint>
#include <vector>

using namespace Dynamixel::Protocol;

namespace Dynamixel
{
namespace Servo
{

template <typename Model>
class Protocol1Servo {
public:
	Protocol1Servo() = default;
	~Protocol1Servo() = default;

	Protocol1Servo(uint8_t id) : _id(id) { }
public:
	InstructionPacket<Protocol1> Ping();
	void Test();
private:
	uint8_t _id;
};

}
}

#endif