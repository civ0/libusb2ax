#ifndef SERVO_MANAGEDPROTOCOL1SERVO_HPP
#define SERVO_MANAGEDPROTOCOL1SERVO_HPP

#include <atomic>
#include <cstdint>
#include <map>
#include <thread>

#include "../Controller/USB2AX.hpp"
#include "../Exception/Exceptions.hpp"
#include "../Global.hpp"
#include "../InstructionPacket.hpp"
#include "../Protocol/Protocols.hpp"
#include "../ReadOnly.hpp"
#include "ServoManager.hpp"
#include "Protocol1Model.hpp"
#include "Protocol1ServoCommands.hpp"
#include "ServoRegister.hpp"


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
	using parameterCallback = std::function < void(std::vector<uint8_t>&&) >;
public: // constructors
	ManagedProtocol1Servo();
	ManagedProtocol1Servo(ServoManager<ManagedProtocol1Servo, p1>*, p1Model::Name, uint8_t);
public: // methods
	bool Ping();
	void UpdateAlarmLED(bool);
	void SetAlarmLED(uint8_t);
	void UpdatePosition(bool);
	void SetPosition(double);
	void UpdateSpeed(bool);
	void SetSpeed(double);
	void UpdateTemperature(bool);
	void UpdateLoad(bool);
	void SetTorqueLimit(double);
private:
	inline parameterCallback GetEmptyCallback()
	{
		parameterCallback callback = [this](std::vector<uint8_t> && parameters) {
			unused(parameters);
		};
		return callback;
	}

	template <class T>
	inline void WaitForUpdate(ServoRegister<T>& reg)
	{
		while (!reg.Updated()); // wait for update
		reg.Reset(); // reset update state
	}
public: // attributes
	ServoRegister<uint8_t> ID;
	ServoRegister<uint8_t> AlarmLED;
	ServoRegister<double> GoalPosition;
	ServoRegister<double> PresentPosition;
	ServoRegister<double> MovingSpeed;
	ServoRegister<double> PresentSpeed;
	ServoRegister<uint8_t> PresentTemperature;
	ServoRegister<double> PresentLoad;
	ServoRegister<double> TorqueLimit;
private: // attributes
	ServoManager<ManagedProtocol1Servo, p1>* manager;
	Protocol1Model model;
	uint8_t id;
};

}
}

#endif