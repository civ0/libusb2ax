#ifndef READONLY_H
#define READONLY_H

namespace Dynamixel
{

template <typename Owner, typename Primitive>
class ReadOnly {
	friend Owner;
public:
	inline Primitive operator()() const
	{
		return _value;
	}
protected:
	template <typename T> inline T operator=(const T& rhs)
	{
		return _value = rhs;
	}

	Primitive _value;
};

}

#endif