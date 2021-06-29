#pragma comment(lib, "..\\x64\\Debug\\InputDLL.lib")

#include "../InputDLL/InputDLL.h"

void InputTest()
{
	auto in = CreateInputUtil(Input::InputType::ARDUINO, (LPVOID)L"COM14");

	for (INT idx = 0; idx < 10; idx++)
	{
		in->key(VK_LEFT, InputBase::KeyType::KEY_DOWN);
		Sleep(300);
	}

}


void InputTest2()
{
	Input::InputUtil in(Input::InputType::ARDUINO, (LPVOID)L"COM14");

	for (INT idx = 0; idx < 10; idx++)
	{
		in.key(VK_LEFT, InputBase::KeyType::KEY_DOWN);
		Sleep(300);
	}
}

int main()
{
	InputTest();
	InputTest2();
}