#ifndef STATUSPACKET_H
#define STATUSPACKET_H

#include <cstddef>
#include <cstdint>
#include <vector>

#include "./Protocol/Protocols.hpp"

namespace Dynamixel
{

template <typename ProtocolType>
class StatusPacket {
public:
	using DecodeState = typename ProtocolType::DecodeState;
	StatusPacket() : _valid(false) { }
public:
	typename ProtocolType::id_t ID() const;
	const std::vector<uint8_t> Parameters() const;
	DecodeState Decode(const std::vector<uint8_t>&);
private:
	bool _valid;
	typename ProtocolType::id_t _id;
	std::vector<uint8_t> _parameters;
};

}

#endif