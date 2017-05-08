#include <iostream>
#include <string>
#include <vector>

#include "Adapter/USB2AX.hpp"
#include "Exception/Exceptions.hpp"
#include "Protocol/Protocols.hpp"
#include "Servo/Servos.hpp"

using namespace std;
using namespace Dynamixel;

int main(int argc, char** argv)
{
	try {
		Dynamixel::Adapter::USB2AX usb2ax(argv[1]);
		usb2ax.CloseSerial();

		// Servo::Protocol1Servo<Servo::AX12> servo(19);

		// vector<uint8_t> message = servo.Ping();
		// for (const uint8_t& c : message) {
		// 	cout << (unsigned)c << endl;
		// }


		return 0;
	} catch (boost::exception& e) {
		if (string const* error = boost::get_error_info<Exception::StringInfo>(e))
			cerr << "Error: " << *error << endl;

		return 1;
	}
}
