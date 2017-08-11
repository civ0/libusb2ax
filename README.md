# libusb2ax

## This project is currently work in progress

libusb2ax is a C++ library/interface for Dynamixal servo motors.

The code for communicating with the acutuators is heavily based on [resibots/libdynamixel](https://github.com/resibots/libdynamixel).

## Run the test program

### Dependencies:

* C++14
+ boost

Modify test.cpp to your Servo IDs and compile. To run the program without superuser rights and a
nice device name for the USB2AX you can install the included udev rule.

After that you can run:

    ./test /dev/usb2ax0