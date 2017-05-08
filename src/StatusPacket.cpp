#include "./StatusPacket.hpp"
#include "./Exception/Exceptions.hpp"

using namespace std;
using namespace Dynamixel::Exception;

namespace Dynamixel
{

template <typename ProtocolType>
typename ProtocolType::id_t StatusPacket<ProtocolType>::ID() const
{
	if (!_valid)
		throw DynamixelStatusPacketException()
		                << StringInfo("StatusPacket: tried to access ID before packet was valid");
	return _id;
}

template <typename ProtocolType>
const vector<uint8_t> StatusPacket<ProtocolType>::Parameters() const
{
	if (!_valid)
		throw DynamixelStatusPacketException()
		                << StringInfo("StatusPacket: tried to access parameters before packet was valid");
	return _parameters;
}

template <typename ProtocolType>
DecodeState StatusPacket<ProtocolType>::Decode(const vector<uint8_t>& packet)
{

}

}