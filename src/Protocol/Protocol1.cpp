#include "./Protocol1.hpp"

using namespace std;
using namespace Dynamixel::Exception;

namespace Dynamixel
{
namespace Protocol
{

std::vector<uint8_t> Protocol1::PackInstruction(id_t id, Instruction instruction)
{
	const size_t packetSize = 2 // start
	                          + 1 // id
	                          + 1 // length
	                          + 1 // instruction
	                          + 1 // checksum
	                          ;
	vector<uint8_t> packet(packetSize);

	packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = id;
	packet[3] = 2;
	packet[4] = static_cast<instr_t>(instruction);
	packet[5] = Checksum(packet);

	return packet;
}

std::vector<uint8_t> Protocol1::PackInstruction(id_t id, Instruction instruction,
                const vector<uint8_t>& parameters)
{
	const size_t packetSize = 2 // start
	                          + 1 // id
	                          + 1 // length
	                          + 1 // instruction
	                          + parameters.size() // parameters
	                          + 1 // checksum
	                          ;
	vector<uint8_t> packet(packetSize);

	packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = id;
	packet[3] = 2;
	packet[4] = static_cast<instr_t>(instruction);

	for (size_t i = 0; i != parameters.size(); ++i)
		packet[5 + i] = parameters[i];

	packet[packetSize - 1] = Checksum(packet);

	return packet;
}

Protocol1::DecodeState Protocol1::Unpack(const vector<uint8_t>& packet, id_t& id, vector<uint8_t>& parameters)
{
	
}

bool DetectStatusHeader(const vector<uint8_t>& packet)
{
	if (packet.size() == 0)
		return false;
	if (packet.size() >= 1 && packet[0] != 0xFF)
		return false;
	if (packet.size() >= 2 && packet[1] != 0xFF)
		return false;
	return true;
}

uint8_t Protocol1::Checksum(const vector<uint8_t>& packet)
{
	if (packet.size() == 0)
		throw DynamixelPacketException()
		                << StringInfo("Protocol1 checksum: packet is empty.");

	int sum = 0;
	for (size_t i = 2; i < packet.size() - 1; ++i)
		sum += packet[i];
	uint8_t checksum = sum & 0xFF;
	if (sum <= 255 && sum != checksum)
		throw DynamixelPacketException()
		                << StringInfo("Protocol1 checksum mismatch: id: "
		                              + to_string(packet[2]) + ", checksum: "
		                              + to_string(checksum) + ", sum: "
		                              + to_string(sum) + ".");
	return ~checksum;
}

}
}