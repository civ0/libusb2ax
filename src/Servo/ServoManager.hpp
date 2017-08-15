#ifndef SERVOMANAGER_HPP
#define SERVOMANAGER_HPP

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../Controller/USB2AX.hpp"
#include "../Exception/Exceptions.hpp"
#include "../InstructionPacket.hpp"
#include "../Protocol/Protocols.hpp"
#include "../StatusPacket.hpp"

namespace Dynamixel
{
namespace Servo
{

namespace con = Dynamixel::Controller;
namespace ex = Dynamixel::Exception;
namespace proto = Dynamixel::Protocol;

template <class Servo, class Protocol>
class ServoManager {
	using p1 = Dynamixel::Protocol::Protocol1;
	using read_lock  = std::shared_lock<std::shared_timed_mutex>;
	using write_lock = std::unique_lock<std::shared_timed_mutex>;
	using parameterCallback = std::function<void(std::vector<uint8_t>&&)>;
public:
	ServoManager(std::string);
public:
	void StartUpdating();
	void StopUpdating();
	void InsertInstruction(InstructionPacket<Protocol>&&, parameterCallback&&);
private:
	static void Update(void*);
public:
	std::unordered_map<uint8_t, Servo> Servos;
private:
	mutable std::shared_timed_mutex mtx;
	con::USB2AX usb2ax;
	std::atomic<bool> updating;
	std::deque<std::tuple<InstructionPacket<Protocol>, parameterCallback>> instructions;
};


}
}

#endif