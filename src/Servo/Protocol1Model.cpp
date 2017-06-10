#include "Protocol1Model.hpp"

#include "../Exception/Exceptions.hpp"

namespace ex = Dynamixel::Exception;

namespace Dynamixel
{
namespace Servo
{

void Protocol1Model::LoadAX12(Protocol1Model& model)
{
	// EEPROM
	model.ModelNumber = 0x0;
	model.FirmwareVersion = 0x02;
	model.ID = 0x03;
	model.Baudrate = 0x04;
	model.ReturnDelayTime = 0x05;
	model.CWAngleLimit = 0x06;
	model.CCWAngleLimit = 0x08;
	model.TemperatureLimit = 0x0B;
	model.LowerVoltageLimit = 0x0C;
	model.UpperVoltageLimit = 0x0D;
	model.MaxTorque = 0x0E;
	model.StatusReturnLevel = 0x10;
	model.AlarmLED = 0x11;
	model.AlarmShutdown = 0x12;
	model.DownCalibration = 0x14;
	model.UpCalibration = 0x16;
	// RAM
	model.TorqueEnable = 0x18;
	model.LED = 0x19;
	model.CWComplianceMargin = 0x1A;
	model.CCWComplianceMargin = 0x1B;
	model.CWComplianceSlope = 0x1C;
	model.CCWComplianceSlope = 0x1D;
	model.GoalPosition = 0x1E;
	model.MovingSpeed = 0x20;
	model.TorqueLimit = 0x22;
	model.PresentPosition = 0x24;
	model.PresentSpeed = 0x26;
	model.PresentLoad = 0x28;
	model.PresentVoltage = 0x2A;
	model.PresentTemperature = 0x2B;
	model.RegisteredInstruction = 0x2C;
	model.Moving = 0x2E;
	model.Lock = 0x2F;
	model.Punch = 0x30;
}

Protocol1Model Protocol1Model::FromName(Name name)
{
	Protocol1Model model;

	switch (name) {
	case Name::AX12:
		LoadAX12(model);
		break;
	default:
		throw ex::DynamixelUnknownServoModelException();
		break;
	}

	return model;
}

}
}