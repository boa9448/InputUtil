#pragma comment(lib, "..\\x64\\Debug\\InputDLL.lib")

#include "../InputDLL/InputDLL.h"

void InputTest()
{
	auto in = CreateInputUtil(Input::InputType::ARDUINO, (LPVOID)L"COM10");

	for (INT idx = 0; idx < 10; idx++)
	{
		in->key(VK_LEFT, Input::KeyType::KEY_DOWN);
		Sleep(300);
	}

}


void InputTest2()
{
	Input::InputUtil in(Input::InputType::ARDUINO, (LPVOID)L"COM10");

	for (INT idx = 0; idx < 10; idx++)
	{
		in.key(VK_LEFT, Input::KeyType::KEY_DOWN);
		Sleep(300);
	}

	in.str(L"test string!");
}

void ddTest()
{
	WCHAR szPath[MAX_PATH] = { 0, };
	GetDD64Path(MAX_PATH, szPath);
	Input::InputUtil dd(Input::InputType::CLASS_DD, (LPVOID)szPath);

	Sleep(3000);

	for (INT a = 0; a < 10; a++)
	{
		dd.key(VK_LEFT, InputBase::KeyType_::KEY_DOWN);
		Sleep(100);
		dd.key(VK_LEFT, InputBase::KeyType_::KEY_UP);
		Sleep(100);
	}
}

int main()
{
	//ddTest();
	//InputTest();
	InputTest2();
}