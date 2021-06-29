#include <Windows.h>
#include "../libs/InputUtil.h"

using namespace InputBase;
using namespace Input;
using namespace Arduino;


void ArduinoTest()
{
	ArduinoUtil ar(L"COM14");
	for (INT a = 0; a < 10; a++)
	{
		ar.key(VK_LEFT, KeyType::KEY_DOWN);
		Sleep(100);
		ar.key(VK_LEFT, KeyType::KEY_UP);
		Sleep(100);
	}

	ar.str(L"test string!");
}

void comPortQueryTest()
{
	auto comList = Arduino::ArduinoUtil::getPortList();

	for (auto& com : comList)
	{
		std::wcout << com << std::endl;
	}
}

int main()
{
	ArduinoTest();
	comPortQueryTest();

	return 0;
}