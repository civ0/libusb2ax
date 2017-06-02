#include "./StatusPacket.hpp"
#include "./Exception/Exceptions.hpp"

namespace ex = Dynamixel::Exception;

namespace Dynamixel
{

template <typename ProtocolType>
typename ProtocolType::id_t StatusPacket<ProtocolType>::ID() const
{
	if (!_valid)
		throw ex::DynamixelStatusPacketException()
		                << ex::StringInfo("StatusPacket: tried to access ID before packet was valid");
	return _id;
}

template <typename ProtocolType>
const std::vector<uint8_t> StatusPacket<ProtocolType>::Parameters() const
{
	if (!_valid)
		throw ex::DynamixelStatusPacketException()
		                << ex::StringInfo("StatusPacket: tried to access parameters before packet was valid");
	return _parameters;
}

template <typename ProtocolType>
const std::vector<typename ProtocolType::ErrorCode> StatusPacket<ProtocolType>::Errors() const
{
	return _errors;
}

template <typename ProtocolType>
typename ProtocolType::DecodeState StatusPacket<ProtocolType>::Decode(const std::vector<uint8_t>& packet)
{
	using DecodeState = typename ProtocolType::DecodeState;
	DecodeState state = ProtocolType::Unpack(packet, _id, _parameters, _errors);
	if (state == DecodeState::Done)
		_valid = true;
	return state;
}

template class StatusPacket<Protocol::Protocol1>;

}