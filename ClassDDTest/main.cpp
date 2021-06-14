#include <Windows.h>
#include "../libs/InputUtil.h"

using namespace InputBase;
using namespace Input;

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

int main()
{
	ddTest();
	inputUtilTest();

	return 0;
}