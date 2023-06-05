#include "DeviceDriver.h"
#include <windows.h>
#include <vector>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}


int DeviceDriver::read(long address)
{
	int first = m_hardware->read(address);
	for (int i = 1; i < 5; i++)
	{
		Sleep(10);
		int next = m_hardware->read(address);
		if (first != next) throw std::exception("Read Fail");
	}

	return first;
}

void DeviceDriver::write(long address, int data)
{

	int read_value = m_hardware->read(address);
	if (read_value != 0xFF) throw std::exception("Write Fail");
	m_hardware->write(address, (unsigned char)data);
}
