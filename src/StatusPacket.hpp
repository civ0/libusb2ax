#ifndef STATUSPACKET_HPP
#define STATUSPACKET_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Protocol/Protocols.hpp"

namespace Dynamixel
{

template <class ProtocolType>
class StatusPacket {
public:
	using DecodeState = typename ProtocolType::DecodeState;
	using ErrorCode = typename ProtocolType::ErrorCode;
	StatusPacket() : _valid(false) { }
public:
	uint8_t ID() const;
	std::vector<uint8_t> Parameters() const;
	std::vector<ErrorCode> Errors() const;
	DecodeState Decode(const std::vector<uint8_t>&);
private:
	bool _valid;
	uint8_t id;
	std::vector<uint8_t> parameters;
	std::vector<ErrorCode> errors;
};

}

#endif