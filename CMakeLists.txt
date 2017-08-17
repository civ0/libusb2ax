cmake_minimum_required(VERSION 2.8.2)
project(libusb2ax)

enable_testing()

option(BUILD_TESTS "Build test programs" ON)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

find_package(Boost COMPONENTS exception REQUIRED)

#add_compile_options(-O3 -Wall -pedantic)

file(GLOB SOURCES demo.cpp
	src/*.cpp
	src/Controller/*.cpp 
	src/Protocol/*.cpp 
	src/Servo/*.cpp)

add_executable(demo ${SOURCES})
target_link_libraries (demo ${CMAKE_THREAD_LIBS_INIT})

if(BUILD_TESTS)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(ReadOnly_test tests/ReadOnly_test.cpp)
target_link_libraries(ReadOnly_test gtest_main)
add_test(ReadOnly ReadOnly_test)

endif(BUILD_TESTS)