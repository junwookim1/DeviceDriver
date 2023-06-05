#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project4/DeviceDriver.cpp"
#include "../Project4/App.cpp"

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



TEST(FlashMemoryDeviceTest, AppReadAndPrintTest1)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(_)).Times(25);

	DeivceTestApp app(&dd);

	app.ReadAndPrint(0x00, 0x04);
}

TEST(FlashMemoryDeviceTest, AppReadAndPrintTest2)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(_)).WillRepeatedly(Return(1));
	vector<int> expect{1, 1, 1, 1, 1};
	DeivceTestApp app(&dd);
	EXPECT_THAT(app.ReadAndPrint(0x00, 0x04), expect);
}



TEST(FlashMemoryDeviceTest, AppWriteAllTest1)
{
	FlashMemoryDeviceMock device_mock;
	DeviceDriver dd(&device_mock);
	EXPECT_CALL(device_mock, read(_)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(device_mock, write(_,_)).Times(5);

	DeivceTestApp app(&dd);

	app.WriteAll(1);
}
