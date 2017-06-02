#include <iostream>
#include <string>
#include <vector>

#include "Controller/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "Protocol/Protocols.hpp"
#include "Servo/Servos.hpp"

namespace con = Dynamixel::Controller;
namespace sv = Dynamixel::Servo;
namespace proto = Dynamixel::Protocol;
namespace ex = Dynamixel::Exception;

int main(int argc, char** argv)
{
	try {
		con::USB2AX usb2ax(argv[1]);

		sv::Protocol1Servo<sv::AX12> servo(20);

		auto message = servo.Ping();
		for (const uint8_t& c : message) {
			std::cout << (unsigned)c << std::endl;
		}

		usb2ax.Send(message);
		auto res = usb2ax.Receive<proto::Protocol1>();

		if (res.ID() == 20)
			std::cout << "Fuck yeah!" << std::endl;

		// for (const auto& c : res.Parameters())
		// 	std::cout << c << std::endl;
		// std::cout << std::endl;

		usb2ax.CloseSerial();

		return 0;
	} catch (boost::exception& e) {
		if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}
