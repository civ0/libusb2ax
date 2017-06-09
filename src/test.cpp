#include <iostream>
#include <string>
#include <vector>

#include "Controller/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "Protocol/Protocols.hpp"
#include "Servo/Servos.hpp"

namespace con = Dynamixel::Controller;
namespace sv = Dynamixel::Servo;
namespace ex = Dynamixel::Exception;

int main(int argc, char** argv)
{
	using proto = Dynamixel::Protocol::Protocol1;

	try {
		con::USB2AX usb2ax(argv[1]);

		sv::Protocol1Servo<sv::AX12> servo(19);

		auto message = servo.Ping();

		usb2ax.Send(message);
		auto res = usb2ax.Receive<proto>();

		if (res.ID() == 19)
			std::cout << "Fuck yeah!" << std::endl;

		message = servo.GetPosition();
		std::cout << std::endl << "Get Posistion: ";
		for (const auto& c : message)
			std::cout << static_cast<unsigned>(c) << " ";
		std::cout << std::endl;

		usb2ax.Send(message);
		res = usb2ax.Receive<proto>();
		std::cout << "Errors (" << res.Errors().size() << "): ";
		for (const auto& e : res.Errors())
			std::cout << static_cast<unsigned>(e) << " ";
		std::cout << std::endl;

		std::cout << "Parameters (" << res.Parameters().size() << "): ";
		for (const auto& p : res.Parameters())
			std::cout << static_cast<unsigned>(p) << " ";
		std::cout << std::endl;
		unsigned value = res.Parameters()[0] + (res.Parameters()[1] << 8);
		double degree = value / 1023.0 * 300.0 - 150.0;
		std::cout << degree << std::endl;


		for (int angle = -150; angle <= 150; angle += 10) {
			message = servo.SetPosition(angle);
			usb2ax.Send(message);
			sleep(1);
		}

		usb2ax.CloseSerial();
		return 0;
	} catch (boost::exception& e) {
		if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}
