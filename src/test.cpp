#include <iostream>

#include "Adapter/Usb2Dynamixel.hpp"
#include "Exception/Exceptions.hpp"

using namespace std;

int main(int argc, char** argv)
{
	Dynamixel::Adapter::Usb2Dynamixel adapter(argv[1]);

	adapter.CloseSerial();

	return 0;
}
