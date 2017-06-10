#include "ServoManager.hpp"

namespace Dynamixel
{

template <class Servo>
ServoManager<Servo>::ServoManager()
{

}

template class ServoManager<sv::Protocol1Servo>;

}