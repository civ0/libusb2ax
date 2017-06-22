#ifndef SERVO_SERVOREGISTER_H
#define SERVO_SERVOREGISTER_H

namespace Dynamixel
{
namespace Servo
{

template <class T>
class ServoRegister {
public:
	ServoRegister() : _changed(false) {}
	inline void Set(T value)
	{
		_value = value;
	}
	inline void Update(T value)
	{
		_value = value;
		_changed = true;
	}
	inline void Reset()
	{
		_changed = false;
	}
	inline T Get() const
	{
		return _value;
	}
	inline bool Changed()
	{
		return _changed;
	}
private:
	T _value;
	bool _changed;
};

}
}

#endif