#ifndef SERVOMANAGER_H
#define SERVOMANAGER_H

#include <cstdint>
#include <map>
#include <vector>
#include <string>

#include "Controller/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "InstructionPacket.hpp"
#include "Protocol/Protocols.hpp"
#include "StatusPacket.hpp"

namespace Dynamixel
{

namespace con = Dynamixel::Controller;
namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;


template <class Servo>
class ServoManager {
	using p1 = Dynamixel::Protocol::Protocol1;
public:
	ServoManager(std::string);
public:
	StatusPacket<p1> SendAndReceive(const InstructionPacket<p1>&);
public:
	std::map<uint8_t, Servo> Servos;
private:
	con::USB2AX _usb2ax;
	// std::atomic<bool> _updating;
};


}

#endif