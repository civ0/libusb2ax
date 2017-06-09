#ifndef SERVO_PROTOCOL1MODEL_H
#define SERVO_PROTOCOL1MODEL_H

#include "./../ReadOnly.hpp"

#include <cstdint>

namespace Dynamixel
{
namespace Servo
{

class Protocol1Model {
public:
	enum class Name { AX12 };
	static Protocol1Model FromName(Name);
	~Protocol1Model() = default;
private:
	Protocol1Model() = default;
	static void LoadAX12(Protocol1Model&);
public:
	// EEPROM
	ReadOnly<Protocol1Model, uint8_t> ModelNumber;
	ReadOnly<Protocol1Model, uint8_t> FirmwareVersion;
	ReadOnly<Protocol1Model, uint8_t> ID;
	ReadOnly<Protocol1Model, uint8_t> Baudrate;
	ReadOnly<Protocol1Model, uint8_t> ReturnDelayTime;
	ReadOnly<Protocol1Model, uint8_t> CWAngleLimit;
	ReadOnly<Protocol1Model, uint8_t> CCWAngleLimit;
	ReadOnly<Protocol1Model, uint8_t> TemperatureLimit;
	ReadOnly<Protocol1Model, uint8_t> LowerVoltageLimit;
	ReadOnly<Protocol1Model, uint8_t> UpperVoltageLimit;
	ReadOnly<Protocol1Model, uint8_t> MaxTorque;
	ReadOnly<Protocol1Model, uint8_t> StatusReturnLevel;
	ReadOnly<Protocol1Model, uint8_t> AlarmLED;
	ReadOnly<Protocol1Model, uint8_t> AlarmShutdown;
	ReadOnly<Protocol1Model, uint8_t> DownCalibration;
	ReadOnly<Protocol1Model, uint8_t> UpCalibration;
	// RAM
	ReadOnly<Protocol1Model, uint8_t> TorqueEnable;
	ReadOnly<Protocol1Model, uint8_t> LED;
	ReadOnly<Protocol1Model, uint8_t> CWComplianceMargin;
	ReadOnly<Protocol1Model, uint8_t> CCWComplianceMargin;
	ReadOnly<Protocol1Model, uint8_t> CWComplianceSlope;
	ReadOnly<Protocol1Model, uint8_t> CCWComplianceSlope;
	ReadOnly<Protocol1Model, uint8_t> GoalPosition;
	ReadOnly<Protocol1Model, uint8_t> MovingSpeed;
	ReadOnly<Protocol1Model, uint8_t> TorqueLimit;
	ReadOnly<Protocol1Model, uint8_t> PresentPosition;
	ReadOnly<Protocol1Model, uint8_t> PresentSpeed;
	ReadOnly<Protocol1Model, uint8_t> PresentLoad;
	ReadOnly<Protocol1Model, uint8_t> PresentVoltage;
	ReadOnly<Protocol1Model, uint8_t> PresentTemperature;
	ReadOnly<Protocol1Model, uint8_t> RegisteredInstruction;
	ReadOnly<Protocol1Model, uint8_t> Moving;
	ReadOnly<Protocol1Model, uint8_t> Lock;
	ReadOnly<Protocol1Model, uint8_t> Punch;
};

}
}

#endif