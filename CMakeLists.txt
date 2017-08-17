cmake_minimum_required(VERSION 2.8.2)
project(libusb2ax)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

find_package(Boost COMPONENTS exception REQUIRED)

add_compile_options(-O3 -Wall -Wextra -Wshadow -pedantic)

file(GLOB SOURCES demo.cpp
	src/*.cpp
	src/Controller/*.cpp 
	src/Protocol/*.cpp 
	src/Servo/*.cpp)

add_executable(demo ${SOURCES})
target_link_libraries (demo ${CMAKE_THREAD_LIBS_INIT})
