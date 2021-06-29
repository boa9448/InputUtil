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

int main()
{
	ddTest();

	return 0;
}