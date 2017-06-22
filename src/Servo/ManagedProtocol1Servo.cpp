#include "ManagedProtocol1Servo.hpp"

namespace Dynamixel
{
namespace Servo
{

using p1Model = Protocol1Model;

ManagedProtocol1Servo::ManagedProtocol1Servo(p1Model::Name name, uint8_t id)
{
	_model = p1Model::FromName(name);
	_id = id;
}

}
}