#include "ServoManager.hpp"

#include "Servo/ManagedProtocol1Servo.hpp"

namespace Dynamixel
{

template <class Servo, class Protocol>
ServoManager<Servo, Protocol>::ServoManager(std::string deviceName) : usb2ax(deviceName)
{

}

template <class Servo, class Protocol>
void ServoManager<Servo, Protocol>::StartUpdating()
{
	updating = true;
	std::thread(Update, this).detach();
}

template <class Servo, class Protocol>
void ServoManager<Servo, Protocol>::StopUpdating()
{
	updating = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

template <class Servo, class Protocol>
void ServoManager<Servo, Protocol>::InsertInstruction(InstructionPacket<Protocol>&& instr,
                parameterCallback&& callback)
{
	write_lock lock(mtx);
	instructions.push_front(std::make_tuple(std::forward<InstructionPacket<Protocol>>(instr),
	                                        std::forward<parameterCallback>(callback)));
}

template<class Servo, class Protocol>
void ServoManager<Servo, Protocol>::Update(void* thisPointer)
{
	ServoManager<Servo, Protocol>* manager =
	        static_cast<ServoManager<Servo, Protocol>*>(thisPointer);

	for (auto it = manager->Servos.begin(); it != manager->Servos.end(); ++it) {
		it->second.UpdatePosition(false);
	}
	std::vector<std::tuple<InstructionPacket<Protocol>, parameterCallback>>
	                loop(manager->instructions.begin(), manager->instructions.end());
	manager->instructions.clear();

	auto loopIndex = loop.begin();
	while (manager->updating == true) {
		if (manager->instructions.size() != 0) {
			write_lock lock(manager->mtx);
			auto instr = manager->instructions.back();
			manager->instructions.pop_back();
			manager->usb2ax.Send(std::get<0>(instr));
			auto response = manager->usb2ax.Receive<Protocol>();
			std::get<1>(instr)(std::forward<std::vector<uint8_t>>(response.Parameters()));
		}

		manager->usb2ax.Send(std::get<0>(*loopIndex));
		auto response = manager->usb2ax.Receive<Protocol>();
		std::get<1>(*loopIndex)(response.Parameters());

		if (loopIndex != loop.end() - 1)
			++loopIndex;
		else
			loopIndex = loop.begin();

		// for (auto it = manager->Servos.begin(); it != manager->Servos.end(); ++it) {

		// }
	}

	return;
}

template class ServoManager<Servo::ManagedProtocol1Servo, Protocol::Protocol1>;

}