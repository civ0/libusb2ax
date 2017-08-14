#ifndef SERVO_ALARMLEDVALUES_HPP
#define SERVO_ALARMLEDVALUES_HPP

#include <cstdint>

namespace Dynamixel
{
namespace Servo
{

struct AlarmLEDValues{
	static const uint8_t InputVoltageError;
	static const uint8_t AngleLimitError;
	static const uint8_t OverheatingError;
	static const uint8_t RangeError;
	static const uint8_t ChecksumError;
	static const uint8_t OverloadError;
	static const uint8_t InstructionError;
};

}
}

#endif