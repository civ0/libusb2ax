#include "ManagedProtocol1Servo.hpp"

namespace Dynamixel
{
namespace Servo
{

using p1Model = Protocol1Model;

ManagedProtocol1Servo::ManagedProtocol1Servo()
{
	// needed for compilation because no default constructor can be sythesized.
	// if not defined, ServoManager.Servos.emplace will not compile, as it uses the default constructor
}

ManagedProtocol1Servo::ManagedProtocol1Servo(ServoManager<ManagedProtocol1Servo, p1>* man,
                p1Model::Name name, uint8_t servoID)
	: manager(man), model(p1Model::FromName(name)), id(servoID)
{
	ID.Set(id);
}

bool ManagedProtocol1Servo::Ping()
{
	// auto message = Protocol1ServoCommands::Ping(id);
	// auto status = manager->SendAndReceive(message);
	// if (status.ID() == id)
	// 	return true;
	// else
	return false;
}

/*
 * Callback Explanation
 *
 * The callback lambda gets called from the update thread. Because the lambda uses other members,
 * the this pointer must be captured. The capturing must be done by value, as the execution of
 * the lambda can happen after the creating function returned.
 */

void ManagedProtocol1Servo::UpdateAlarmLED(bool wait)
{
	auto message = Protocol1ServoCommands::GetAlarmLED(model, id);
	parameterCallback callback = [this, wait](std::vector<uint8_t> && parameters) {
		this->AlarmLED.Set(parameters[0], wait);
	};
	manager->InsertInstruction(std::move(message), std::move(callback));
	if (wait)
		WaitForUpdate(AlarmLED);
}

void ManagedProtocol1Servo::SetAlarmLED(uint8_t value)
{
	auto message = Protocol1ServoCommands::SetAlarmLED(model, id, value);
	manager->InsertInstruction(std::move(message), GetEmptyCallback());
	// don't move result of GetEmptyCallback() as it would prevent copy elision
}

void ManagedProtocol1Servo::UpdatePosition(bool wait)
{
	auto message = Protocol1ServoCommands::GetPosition(model, id);
	parameterCallback callback = [this, wait](std::vector<uint8_t> && parameters) {
		uint16_t value = parameters[0] + (parameters[1] << 8);
		this->PresentPosition.Set(static_cast<double>(value) / 1023.0 * 300.0 - 150.0, wait);
	};
	manager->InsertInstruction(std::move(message), std::move(callback));
	if (wait)
		WaitForUpdate(PresentPosition);
}

void ManagedProtocol1Servo::SetPosition(double degree)
{
	auto message = Protocol1ServoCommands::SetPosition(model, id, degree);
	manager->InsertInstruction(std::move(message), GetEmptyCallback());
}

void ManagedProtocol1Servo::UpdateSpeed(bool wait)
{
	auto message = Protocol1ServoCommands::GetSpeed(model, id);
	parameterCallback callback = [this, wait](std::vector<uint8_t> && parameters) {
		uint16_t value = parameters[0] + (parameters[1] << 8);
		this->PresentSpeed.Set(static_cast<double>(value / 1023.0), wait);
	};
	manager->InsertInstruction(std::move(message), std::move(callback));
	if (wait)
		WaitForUpdate(PresentSpeed);
}

void ManagedProtocol1Servo::SetSpeed(double speed)
{
	auto message = Protocol1ServoCommands::SetSpeed(model, id, speed);
	manager->InsertInstruction(std::move(message), GetEmptyCallback());
}

void ManagedProtocol1Servo::UpdateTemperature(bool wait)
{
	auto message = Protocol1ServoCommands::GetTemperature(model, id);
	parameterCallback callback = [this, wait](std::vector<uint8_t> && parameters) {
		this->PresentTemperature.Set(parameters[0], wait);
	};
	manager->InsertInstruction(std::move(message), std::move(callback));
	if (wait)
		WaitForUpdate(PresentTemperature);
}

void ManagedProtocol1Servo::UpdateLoad(bool wait)
{
	auto message = Protocol1ServoCommands::GetPresentLoad(model, id);
	parameterCallback callback = [this, wait](std::vector<uint8_t> && parameters) {
		uint16_t value = parameters[0] + (parameters[1] << 8);
		int direction = (value & (1 << 10)) == 0 ? -1 : 1;
		int load = value & 0x3FF;
		this->PresentLoad.Set(static_cast<double>((direction * load) / 1023.0), wait);
	};
	manager->InsertInstruction(std::move(message), std::move(callback));
	if (wait)
		WaitForUpdate(PresentLoad);
}

void ManagedProtocol1Servo::SetTorqueLimit(double torqueLimit)
{
	throw ex::DynamixelNotImplementedException()
	                << ex::StringInfo("ManagedProtocol1Servo::SetTorqueLimit not implemented");
}

}
}