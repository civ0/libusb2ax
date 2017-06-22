#include "ServoManager.hpp"

#include "./Servo/ManagedProtocol1Servo.hpp"

namespace Dynamixel
{

using p1 = Dynamixel::Protocol::Protocol1;

template <class Servo>
ServoManager<Servo>::ServoManager(std::string deviceName) : _usb2ax(deviceName)
{

}

template <class Servo>
StatusPacket<p1> ServoManager<Servo>::SendAndReceive(const InstructionPacket<p1>& packet)
{
	_usb2ax.Send(packet);
	return _usb2ax.Receive<p1>();
}

template class ServoManager<Servo::ManagedProtocol1Servo>;

}