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
	using p1 = Dynamixel::Protocol::Protocol1;

	try {
		con::USB2AX usb2ax(argv[1]);

		auto servo = sv::Protocol1Servo(sv::Protocol1Model::Name::AX12, 19);
		auto message = servo.Ping();
		usb2ax.Send(message);
		auto response = usb2ax.Receive<p1>();
		if (response.ID() == 19)
			std::cout << "Ping successfull" << std::endl;

		message = servo.SetPosition(-150);
		usb2ax.Send(message);
		sleep(1);
		message = servo.SetPosition(150);
		usb2ax.Send(message);

		return 0;
	} catch (boost::exception& e) {
		if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}
