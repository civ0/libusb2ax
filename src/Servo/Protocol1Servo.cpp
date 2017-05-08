#include "./Protocol1Servo.hpp"

#include "./../Protocol/Protocols.hpp"

#include <iostream>
#include <string>

namespace Dynamixel
{
namespace Servo
{

template <typename Model>
InstructionPacket<Protocol1> Protocol1Servo<Model>::Ping()
{
	return InstructionPacket<Protocol1>(_id, Protocol1::Instruction::Ping);
}

template <typename Model>
void Protocol1Servo<Model>::Test()
{
	unsigned modelNumber = static_cast<unsigned>(Model::Address::ModelNumber);
	std::cout << modelNumber << std::endl;
}

template class Protocol1Servo<AX12>;

}
}