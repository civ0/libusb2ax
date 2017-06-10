#ifndef READONLY_H
#define READONLY_H

namespace Dynamixel
{

template <class Owner, class Primitive>
class ReadOnly {
	friend Owner;
public:
	inline Primitive operator()() const
	{
		return _value;
	}
protected:
	template <class T> inline T operator=(const T& rhs)
	{
		return _value = rhs;
	}

	Primitive _value;
};

}

#endif