#ifndef AX12_H
#define AX12_H

#include <cstdint>

namespace Dynamixel
{
namespace Servo
{

class AX12 {
public:
	enum class Address : uint8_t {
		// EEPROM
		ModelNumber = 0x0,
		FirmwareVersion = 0x02,
		ID = 0x03,
		Baudrate = 0x04,
		ReturnDelayTime = 0x05,
		CWAngleLimit = 0x06,
		CCWAngleLimit = 0x08,
		TemperatureLimit = 0x0B,
		LowerVoltageLimit = 0x0C,
		UpperVoltageLimit = 0x0D,
		MaxTorque = 0x0E,
		StatusReturnLevel = 0x10,
		AlarmLED = 0x11,
		AlarmShutdown = 0x12,
		DownCalibration = 0x14,
		UpCalibration = 0x16,
		// RAM
		TorqueEnable = 0x18,
		LED = 0x19,
		CWComplianceMargin = 0x1A,
		CCWComplianceMargin = 0x1B,
		CWComplianceSlope = 0x1C,
		CCWComplianceSlope = 0x1D,
		GoalPosition = 0x1E,
		MovingSpeed = 0x20,
		TorqueLimit = 0x22,
		PresentPosition = 0x24,
		PresentSpeed = 0x26,
		PresentLoad = 0x28,
		PresentVoltage = 0x2A,
		PresentTemperature = 0x2B,
		RegisteredInstruction = 0x2C,
		Moving = 0x2E,
		Lock = 0x2F,
		Punch = 0x30
	};
};

}
}

#endif