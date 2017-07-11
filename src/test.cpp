#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <cstdlib>

#include "Controller/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "Protocol/Protocols.hpp"
#include "Servo/Servos.hpp"
#include "ServoManager.hpp"

namespace dy = Dynamixel;
namespace con = Dynamixel::Controller;
namespace sv = Dynamixel::Servo;
namespace ex = Dynamixel::Exception;

int main(int argc, char** argv)
{
	using p1 = Dynamixel::Protocol::Protocol1;

	try {
		const uint8_t servoID = 19;
		dy::ServoManager<sv::ManagedProtocol1Servo, p1> manager(argv[1]);
		manager.Servos.emplace(servoID, sv::ManagedProtocol1Servo(&manager, sv::Protocol1Model::Name::AX12, servoID));
		manager.StartUpdating();
		sleep(1);
		manager.Servos[servoID].SetPosition(-150.0);
		while (std::abs(manager.Servos[servoID].PresentPosition.Get() + 150) > 1) {
			std::cout << "Pos: " << manager.Servos[servoID].PresentPosition.Get() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		manager.Servos[servoID].SetPosition(150.0);
		while (abs(manager.Servos[servoID].PresentPosition.Get() - 150.0) > 1.0) {
			std::cout << "Pos: " << manager.Servos[servoID].PresentPosition.Get() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		manager.StopUpdating();

	} catch (boost::exception& e) {
		if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}