CXX=clang++
RM=rm -rf

INCLUDES=-I/usr/include/boost

CXXFLAGS=-std=c++14 -O3 -Wall -Wextra -Wshadow -pedantic -pthread -c $(INCLUDES)

LDFLAGS=-lpthread

LDLIBS=-L/usr/include/boost

SOURCES=src/Protocol/Protocol1.cpp                                                                 \
	src/Controller/USB2AX.cpp                                                                  \
	src/Servo/AlarmLEDValues.cpp                                                               \
	src/Servo/Protocol1Model.cpp                                                               \
	src/Servo/Protocol1ServoCommands.cpp                                                       \
	src/Servo/ManagedProtocol1Servo.cpp                                                        \
	src/StatusPacket.cpp                                                                       \
	src/ServoManager.cpp                                                                       \
	src/test.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDLIBS) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(EXECUTABLE)
