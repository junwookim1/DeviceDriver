#include "DeviceDriver.h"
#include <windows.h>
#include <vector>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}


int DeviceDriver::read(long address)
{
	vector<int> read_vector;
	int first = m_hardware->read(address);
	read_vector.push_back(first);
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
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}
