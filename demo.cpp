#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "src/Controller/USB2AX.hpp"
#include "src/Exception/Exceptions.hpp"
#include "src/Protocol/Protocols.hpp"
#include "src/Servo/Servos.hpp"
#include "src/Servo/ServoManager.hpp"

namespace dy = Dynamixel;
namespace con = Dynamixel::Controller;
namespace sv = Dynamixel::Servo;
namespace ex = Dynamixel::Exception;

int main(int argc, char **argv)
{
	using p1 = Dynamixel::Protocol::Protocol1;

	try
	{
		std::vector<uint8_t> servoIDs{19, 20, 21};
		// std::vector<uint8_t> servoIDs;
		// for (uint8_t i = 1; i <= 18; ++i)
		// servoIDs.push_back(i);
		sv::ServoManager<sv::ManagedProtocol1Servo, p1> manager(argv[1]);
		for (auto id : servoIDs)
			manager.Servos.emplace(id, sv::ManagedProtocol1Servo(&manager, sv::Protocol1Model::Name::AX12, id));
		manager.StartUpdating();
		sleep(1);

		auto start = std::chrono::steady_clock::now();
		auto printServos = [&]() {
			auto now = std::chrono::steady_clock::now();
			std::cout << "t=" << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() << std::endl;
			for (const auto &id : servoIDs)
				std::cout << "\t" << static_cast<unsigned>(id)
						  << "; Pos: " << std::setprecision(5) << std::setw(7) << manager.Servos[id].PresentPosition.Get()
						  << "; Speed: " << std::setprecision(5) << std::setw(7) << manager.Servos[id].PresentSpeed.Get()
						  << "; Temp: " << static_cast<unsigned>(manager.Servos[id].PresentTemperature.Get())
						  << "; Load: " << std::setprecision(5) << std::setw(7) << manager.Servos[id].PresentLoad.Get()
						  << std::endl;
		};

		auto setPositions = [&](double degree) {
			for (const auto &id : servoIDs)
				manager.Servos[id].SetPosition(degree);
		};

		auto setSpeeds = [&](double speed) {
			for (const auto &id : servoIDs)
				manager.Servos[id].SetSpeed(speed);
		};

		for (int i = 0; i != 5; ++i)
		{
			setSpeeds(0.2);
			setPositions(-50.0);
			do
			{
				printServos();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			} while (std::abs(manager.Servos[servoIDs[0]].PresentPosition.Get() + 50) > 1);

			setPositions(50.0);
			do
			{
				printServos();
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			} while (abs(manager.Servos[servoIDs[0]].PresentPosition.Get() - 50.0) > 1.0);
		}

		setPositions(0.0);
		do
		{
			printServos();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		} while (abs(manager.Servos[servoIDs[0]].PresentPosition.Get() - 0.0) > 1.0);

		manager.StopUpdating();
	}
	catch (boost::exception &e)
	{
		if (std::string const *error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}