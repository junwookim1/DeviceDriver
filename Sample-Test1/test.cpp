#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project4/DeviceDriver.cpp"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(FlashMemoryDeviceTest, ReadTest1)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(0x1000)).Times(5);

	dd.read(0x1000);
}

TEST(FlashMemoryDeviceTest, ReadTest2)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(0x1000)).WillRepeatedly(Return(1));

	EXPECT_THAT(dd.read(0x1000), 1);
}

TEST(FlashMemoryDeviceTest, ReadTest3)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(0x1000)).WillOnce(Return(1))
		.WillOnce(Return(1))
		.WillOnce(Return(1))
		.WillOnce(Return(1))
		.WillOnce(Return(2));

	EXPECT_THROW(dd.read(0x1000), std::exception);

}

TEST(FlashMemoryDeviceTest, WriteTest1)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(0x1000)).WillRepeatedly(Return(0xFF));

	dd.write(0x1000, 1);
}

TEST(FlashMemoryDeviceTest, WriteTest2)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(0x1000)).WillRepeatedly(Return(0x0));

	EXPECT_THROW(dd.write(0x1000, 1), std::exception);
}
