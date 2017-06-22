#ifndef SERVO_MANAGEDPROTOCOL1SERVO_H
#define SERVO_MANAGEDPROTOCOL1SERVO_H

#include <atomic>
#include <cstdint>
#include <map>
#include <thread>

#include "../Controller/USB2AX.hpp"
#include "../Exception/Exceptions.hpp"
#include "../InstructionPacket.hpp"
#include "../Protocol/Protocols.hpp"
#include "../ReadOnly.hpp"
#include "Servos.hpp"

namespace Dynamixel
{
namespace Servo
{

namespace con = Dynamixel::Controller;
namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;

class ManagedProtocol1Servo {
	using p1Model = Protocol1Model;
	using p1 = Dynamixel::Protocol::Protocol1;
public:
	ManagedProtocol1Servo() = default;
	ManagedProtocol1Servo(p1Model::Name, uint8_t);
public:
	ReadOnly<ManagedProtocol1Servo, uint8_t> _id;
private:
	Protocol1Model _model;
};

}
}

#endif