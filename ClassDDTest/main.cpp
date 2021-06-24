#include <Windows.h>
#include "../libs/InputUtil.h"

using namespace InputBase;
using namespace Input;
using namespace Arduino;

void ddTest()
{
	ClassDD::DD dd(L"..\\dlls\\DD64.dll");

	Sleep(3000);

	for (INT a = 0; a < 10; a++)
	{
		dd.key(VK_LEFT, KeyType::KEY_DOWN);
		Sleep(100);
		dd.key(VK_LEFT, KeyType::KEY_UP);
		Sleep(100);
	}
}

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

void inputUtilTest()
{
	InputUtil input(InputType::CLASS_DD, (LPVOID)L"..\\dlls\\DD64.dll");

	Sleep(3000);

	for (INT a = 0; a < 10; a++)
	{
		input.key(VK_LEFT, KeyType::KEY_DOWN);
		Sleep(100);
		input.key(VK_LEFT, KeyType::KEY_UP);
		Sleep(100);
	}

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
	//ddTest();
	ArduinoTest();
	//inputUtilTest();
	//comPortQueryTest();

	return 0;
}