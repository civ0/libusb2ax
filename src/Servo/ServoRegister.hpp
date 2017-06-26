#ifndef SERVO_SERVOREGISTER_H
#define SERVO_SERVOREGISTER_H

#include <shared_mutex>
#include <mutex>
#include <thread>

namespace Dynamixel
{
namespace Servo
{

template <class T>
class ServoRegister {
	using read_lock  = std::shared_lock<std::shared_timed_mutex>;
	using write_lock = std::unique_lock<std::shared_timed_mutex>;
public:
	ServoRegister() : _changed(false) {}

	ServoRegister(const ServoRegister<T>& other)
	{
		write_lock wl(mtx);
		read_lock rl(other.mtx);

		_value = other._value;
		_changed = other._changed;
	}

	inline void Set(T value)
	{
		write_lock g(mtx);
		_value = value;
	}

	inline void Update(T value)
	{
		write_lock g(mtx);
		_value = value;
		_changed = true;
	}

	inline void Reset()
	{
		_changed = false;
	}

	inline T Get() const
	{
		read_lock g(mtx);
		return _value;
	}

	inline bool Changed()
	{
		return _changed;
	}
private:
	mutable std::shared_timed_mutex mtx;
	T _value;
	bool _changed;
};

}
}

#endif