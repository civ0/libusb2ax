#include "../src/ReadOnly.hpp"

#include "gtest/gtest.h"

namespace
{

template <class T>
class ReadOnlyTestHelper {
public:
	T ReadWrite(T value)
	{
		ro = value;
		return ro();
	}
private:
	Dynamixel::ReadOnly<ReadOnlyTestHelper<T>, T> ro;
};

TEST(ReadOnlyTest, ReadWriteINT)
{
	ReadOnlyTestHelper<int> ro;
	for (int value = -5; value <= 5; ++ value)
		EXPECT_EQ(value, ro.ReadWrite(value));
}

}