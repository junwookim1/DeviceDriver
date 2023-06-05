#include "DeviceDriver.h"

#include <exception>
#include <windows.h>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
	int first = m_hardware->read(address);

	for (int i = 1; i < 5; i++)
	{
		int next = m_hardware->read(address);
		if (first != next) throw std::exception("Read Fail");
	}

	return first;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}
