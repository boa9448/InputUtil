#include "../libs/InputUtil.h"


void InputTest()
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

	return 0;
}