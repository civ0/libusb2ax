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

ManagedProtocol1Servo::ManagedProtocol1Servo(ServoManager<ManagedProtocol1Servo>* manager,
                p1Model::Name name, uint8_t id)
	: _manager(manager), _model(p1Model::FromName(name)), _id(id)
{
	ID.Set(id);
}

bool ManagedProtocol1Servo::Ping()
{
	auto message = Protocol1ServoCommands::Ping(_id);
	auto status = _manager->SendAndReceive(message);
	if (status.ID() == _id)
		return true;
	else
		return false;
}

}
}