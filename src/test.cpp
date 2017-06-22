#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

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
	// using p1 = Dynamixel::Protocol::Protocol1;

	// dy::ServoManager<sv::Protocol1Servo> sm;

	// try {
	// 	con::USB2AX usb2ax(argv[1]);

	// 	std::map<size_t, sv::Protocol1Servo> servos;
	// 	std::vector<size_t> servoIDs{19, 20, 21};

	// 	for (const auto& id : servoIDs) {
	// 		servos[id] = sv::Protocol1Servo(sv::Protocol1Model::Name::AX12, id);
	// 		auto message = servos[id].Ping();
	// 		usb2ax.Send(message);
	// 		try {
	// 			auto response = usb2ax.Receive<p1>();
	// 			if (response.ID() == id)
	// 				std::cout << static_cast<unsigned>(id) << ": Ping successful"
	// 				          << std::endl;
	// 		} catch (boost::exception& e) {
	// 			if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
	// 				std::cerr << "Error: " << *error << std::endl;
	// 		}
	// 	}

	// 	for (const auto& id : servoIDs) {
	// 		auto message = servos[id].SetPosition(-150);
	// 		usb2ax.Send(message);
	// 		usb2ax.Receive<p1>();
	// 	}

	// 	sleep(1);

	// 	for (const auto& id : servoIDs) {
	// 		auto message = servos[id].SetPosition(150);
	// 		usb2ax.Send(message);
	// 		usb2ax.Receive<p1>();
	// 	}


	// 	// auto servo = sv::Protocol1Servo(sv::Protocol1Model::Name::AX12, 19);
	// 	// auto message = servo.Ping();
	// 	// usb2ax.Send(message);
	// 	// auto response = usb2ax.Receive<p1>();
	// 	// if (response.ID() == 19)
	// 	// 	std::cout << "Ping successfull" << std::endl;

	// 	// message = servo.SetPosition(-150);
	// 	// usb2ax.Send(message);
	// 	// sleep(1);
	// 	// message = servo.SetPosition(150);
	// 	// usb2ax.Send(message);

	// 	return 0;
	// } catch (boost::exception& e) {
	// 	if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
	// 		std::cerr << "Error: " << *error << std::endl;

	// 	return 1;
	// }
}
