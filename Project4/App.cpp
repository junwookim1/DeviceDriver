#include <vector>
#include "../Project4/DeviceDriver.h"
using namespace std;

class DeivceTestApp
{
public:
	DeivceTestApp(DeviceDriver* dd);

	vector<int> ReadAndPrint(int startAddr, int endAddr);

	void WriteAll(int value);

protected:
	DeviceDriver* dd;
};


DeivceTestApp::DeivceTestApp(DeviceDriver* dd) : dd(dd)
{
}

vector<int> DeivceTestApp::ReadAndPrint(int startAddr, int endAddr)
{
	vector<int> read_vector;
	for (int i = startAddr; i <= endAddr; i++)
	{
		read_vector.push_back(dd->read(i));
	}
	return read_vector;
}

void DeivceTestApp::WriteAll(int value)
{
	for(int i=0;i<5;i++)
	{
		dd->write(i, value);
	}
}
