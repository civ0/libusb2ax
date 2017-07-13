#ifndef READONLY_HPP
#define READONLY_HPP

namespace Dynamixel
{

template <class Owner, class Primitive>
class ReadOnly {
	friend Owner;
public:
	inline Primitive operator()() const
	{
		return value;
	}
protected:
	template <class T> inline T operator=(const T& rhs)
	{
		return value = rhs;
	}

	Primitive value;
};

}

#endif