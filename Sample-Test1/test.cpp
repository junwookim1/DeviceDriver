#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project4/DeviceDriver.cpp"
#include <vector>
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

};

TEST(FlashMemoryDeviceTest, Test1)
{
	//EXPECT_CALL(db_mock, getDBName).WillRepeatedly(Return(string("TEST DOUBLE")));
		
}
