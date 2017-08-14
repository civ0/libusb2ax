#include "AlarmLEDValues.hpp"

namespace Dynamixel
{
namespace Servo
{

const uint8_t AlarmLEDValues::InputVoltageError = 0;
const uint8_t AlarmLEDValues::AngleLimitError = 1;
const uint8_t AlarmLEDValues::OverheatingError = 2;
const uint8_t AlarmLEDValues::RangeError = 4;
const uint8_t AlarmLEDValues::ChecksumError = 8;
const uint8_t AlarmLEDValues::OverloadError = 16;
const uint8_t AlarmLEDValues::InstructionError = 32;

}
}