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
#include "./../ServoManager.hpp"
#include "./ServoRegister.hpp"
#include "./Protocol1ServoCommands.hpp"
#include "./Protocol1Model.hpp"


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
	using parameterCallback = std::function<void(std::vector<uint8_t>&&)>;
public: // constructors
	ManagedProtocol1Servo();
	ManagedProtocol1Servo(ServoManager<ManagedProtocol1Servo, p1>*, p1Model::Name, uint8_t);
public: // methods
	bool Ping();
	void UpdatePosition();
	void SetPosition(double);
public: // attributes
	ServoRegister<uint8_t> ID;
	ServoRegister<double> GoalPosition;
	ServoRegister<double> PresentPosition;
private: // attributes
	ServoManager<ManagedProtocol1Servo, p1>* _manager;
	Protocol1Model _model;
	uint8_t _id;
};

}
}

#endif