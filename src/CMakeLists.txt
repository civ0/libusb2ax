cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS exception REQUIRED)

file(GLOB USB2AX_SOURCES
	*.cpp
	Controller/*.cpp 
	Protocol/*.cpp 
	Servo/*.cpp)

add_library(usb2ax STATIC ${USB2AX_SOURCES})