#ifndef SERVOMANAGER_H
#define SERVOMANAGER_H

#include <atomic>
#include <cstdint>
#include <map>
#include <thread>

#include "Controller/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "InstructionPacket.hpp"
#include "Protocol/Protocols.hpp"
#include "Servo/Servos.hpp"

namespace Dynamixel
{

namespace con = Dynamixel::Controller;
namespace sv = Dynamixel::Servo;
namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;


template <class Servo>
class ServoManager {
public:
	ServoManager();
private:

public:
	std::map<size_t, std::atomic<Servo>> Servos;
private:
	std::atomic<bool> _updating;
};


}

#endif