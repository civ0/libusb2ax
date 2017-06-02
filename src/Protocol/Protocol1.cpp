#include "./Protocol1.hpp"

namespace ex = Dynamixel::Exception;

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
	std::vector<uint8_t> packet(packetSize);

	packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = id;
	packet[3] = 2;
	packet[4] = static_cast<instr_t>(instruction);
	packet[5] = Checksum(packet);

	return packet;
}

std::vector<uint8_t> Protocol1::PackInstruction(id_t id, Instruction instruction,
                const std::vector<uint8_t>& parameters)
{
	const size_t packetSize = 2 // start
	                          + 1 // id
	                          + 1 // length
	                          + 1 // instruction
	                          + parameters.size() // parameters
	                          + 1 // checksum
	                          ;
	std::vector<uint8_t> packet(packetSize);

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

Protocol1::DecodeState Protocol1::Unpack(const std::vector<uint8_t>& packet, id_t& id,
                std::vector<uint8_t>& parameters, std::vector<ErrorCode>& errorVec)
{
	if (packet.size() < 6) // wait for minimum packet length
		return DecodeState::Ongoing;

	if (packet[0] != 0xFF || packet[1] != 0xFF) // check if header is correct
		return DecodeState::Invalid;

	length_t length = packet[3];
	if (length > packet.size() - 4) // wait for complete packet, if it is longer than minimum length
		return DecodeState::Ongoing;

	id = packet[2];
	uint8_t checksum = Checksum(packet);
	if (checksum != packet.back()) {
		return DecodeState::Invalid;
	} else {
		uint8_t errors = packet[4];
		if (errors != 0)
			GetErrors(errors, errorVec);
		return DecodeState::Done;
	}

	// static_cast<uint8_t>(length - 2) to suppress -Wsign-compare
	for (uint8_t i = 0; i < static_cast<uint8_t>(length - 2); ++i)
		parameters.push_back(packet[5 + i]);

	return DecodeState::Done;
}

bool Protocol1::DetectStatusHeader(const std::vector<uint8_t>& packet)
{
	if (packet.size() == 0)
		return false;
	if (packet.size() >= 1 && packet[0] != 0xFF)
		return false;
	if (packet.size() >= 2 && packet[1] != 0xFF)
		return false;
	return true;
}

void Protocol1::GetErrors(const uint8_t& errors, std::vector<ErrorCode>& errorVec)
{
	using ec = ErrorCode;
	if (errors & static_cast<uint8_t>(ec::InputVoltage))
		errorVec.push_back(ec::InputVoltage);
	if (errors & static_cast<uint8_t>(ec::AngleLimit))
		errorVec.push_back(ec::AngleLimit);
	if (errors & static_cast<uint8_t>(ec::Overheating))
		errorVec.push_back(ec::Overheating);
	if (errors & static_cast<uint8_t>(ec::Range))
		errorVec.push_back(ec::Range);
	if (errors & static_cast<uint8_t>(ec::Checksum))
		errorVec.push_back(ec::Checksum);
	if (errors & static_cast<uint8_t>(ec::Overload))
		errorVec.push_back(ec::Overload);
	if (errors & static_cast<uint8_t>(ec::Instruction))
		errorVec.push_back(ec::Instruction);
}

uint8_t Protocol1::Checksum(const std::vector<uint8_t>& packet)
{
	if (packet.size() == 0)
		throw ex::DynamixelPacketException()
		                << ex::StringInfo("Protocol1 checksum: packet is empty.");

	int sum = 0;
	for (size_t i = 2; i < packet.size() - 1; ++i)
		sum += packet[i];
	uint8_t checksum = sum & 0xFF;
	if (sum <= 255 && sum != checksum)
		throw ex::DynamixelPacketException()
		                << ex::StringInfo("Protocol1 checksum mismatch: id: "
		                                  + std::to_string(packet[2]) + ", checksum: "
		                                  + std::to_string(checksum) + ", sum: "
		                                  + std::to_string(sum) + ".");
	return ~checksum;
}

}
}