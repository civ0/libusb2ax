#ifndef SERVO_SERVOREGISTER_HPP
#define SERVO_SERVOREGISTER_HPP

#include <mutex>
#include <shared_mutex>
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
	ServoRegister() : updated(false) {}

	ServoRegister(const ServoRegister<T>& other)
	{
		write_lock wl(mtx);
		read_lock rl(other.mtx);

		value = other.value;
		updated = other.updated;
	}

	inline void Set(T v, bool update = false)
	{
		write_lock wl(mtx);
		value = v;
		updated = update;
	}

	inline T Get() const
	{
		read_lock rl(mtx);
		return value;
	}

	inline bool Updated()
	{
		read_lock rl(mtx);
		return updated;
	}

	inline void Reset()
	{
		write_lock wl(mtx);
		updated = false;
	}
private:
	mutable std::shared_timed_mutex mtx;
	T value;
	bool updated;
};

}
}

#endif