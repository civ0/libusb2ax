CXX=g++
RM=rm -rf

INCLUDES=-I/usr/include/boost

CXXFLAGS=-std=c++14 -O3 -Wall -pedantic -pthread -lboost_exception -c $(INCLUDES)

LDFLAGS=-lpthread

LDLIBS=-L/usr/include/boost

SOURCES=src/Protocol/Protocol1.cpp                                                                 \
	src/Adapter/Usb2Dynamixel.cpp                                                              \
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