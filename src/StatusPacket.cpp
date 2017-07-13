#include "StatusPacket.hpp"

#include "Exception/Exceptions.hpp"

namespace ex = Dynamixel::Exception;

namespace Dynamixel
{

template <class ProtocolType>
uint8_t StatusPacket<ProtocolType>::ID() const
{
	if (!_valid)
		throw ex::DynamixelStatusPacketException()
		                << ex::StringInfo("StatusPacket: tried to access ID before packet was valid");
	return id;
}

template <class ProtocolType>
std::vector<uint8_t> StatusPacket<ProtocolType>::Parameters() const
{
	if (!_valid)
		throw ex::DynamixelStatusPacketException()
		                << ex::StringInfo("StatusPacket: tried to access parameters before packet was valid");
	return parameters;
}

template <class ProtocolType>
std::vector<typename ProtocolType::ErrorCode> StatusPacket<ProtocolType>::Errors() const
{
	return errors;
}

template <class ProtocolType>
typename ProtocolType::DecodeState StatusPacket<ProtocolType>::Decode(
        const std::vector<uint8_t>& packet)
{
	using DecodeState = typename ProtocolType::DecodeState;
	DecodeState state = ProtocolType::Unpack(packet, id, parameters, errors);
	if (state == DecodeState::Done)
		_valid = true;
	return state;
}

template class StatusPacket<Protocol::Protocol1>;

}