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
	using p1 = Dynamixel::Protocol::Protocol1;

	try {
		dy::ServoManager<sv::ManagedProtocol1Servo> manager(argv[1]);
		manager.Servos.emplace(19, sv::ManagedProtocol1Servo(&manager, sv::Protocol1Model::Name::AX12, 19));
		std::cout << manager.Servos[19].Ping() << std::endl;

	} catch (boost::exception& e) {
		if (std::string const* error = boost::get_error_info<ex::StringInfo>(e))
			std::cerr << "Error: " << *error << std::endl;

		return 1;
	}
}