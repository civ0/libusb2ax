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

ManagedProtocol1Servo::ManagedProtocol1Servo(ServoManager<ManagedProtocol1Servo, p1>* manager,
                p1Model::Name name, uint8_t id)
	: _manager(manager), _model(p1Model::FromName(name)), _id(id)
{
	ID.Set(id);
}

bool ManagedProtocol1Servo::Ping()
{
	// auto message = Protocol1ServoCommands::Ping(_id);
	// auto status = _manager->SendAndReceive(message);
	// if (status.ID() == _id)
	// 	return true;
	// else
	return false;
}

void ManagedProtocol1Servo::SetPosition(double degree)
{
	auto message = Protocol1ServoCommands::SetPosition(_model, _id, degree);
	parameterCallback callback = [this](std::vector<uint8_t> parameters) {};
	_manager->InsertInstruction(std::move(message), std::move(callback));
}

void ManagedProtocol1Servo::UpdatePosition()
{
	auto message = Protocol1ServoCommands::GetPosition(_model, _id);
	parameterCallback callback = [this](std::vector<uint8_t> parameters) {
		uint16_t value = parameters[0] + (parameters[1] << 8);
		this->PresentPosition.Set(static_cast<double>(value) / 1023.0 * 300.0 - 150.0);
	};
	_manager->InsertInstruction(std::move(message), std::move(callback));
}

}
}