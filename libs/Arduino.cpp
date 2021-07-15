#include "Arduino.h"

namespace Arduino
{

	std::map<BYTE, BYTE> g_keyMap = {
		{VK_LCONTROL, KEY_LEFT_CTRL}
		, {VK_LSHIFT, KEY_LEFT_SHIFT}
		, {VK_LMENU, KEY_LEFT_ALT}
		, {VK_LWIN, KEY_LEFT_GUI}
		, {VK_RCONTROL, KEY_RIGHT_CTRL}
		, {VK_RSHIFT, KEY_RIGHT_SHIFT}
		, {VK_RMENU, KEY_RIGHT_ALT}
		, {VK_RWIN, KEY_RIGHT_GUI}
		, {VK_UP, KEY_UP_ARROW}
		, {VK_DOWN, KEY_DOWN_ARROW}
		, {VK_LEFT, KEY_LEFT_ARROW}
		, {VK_RIGHT, KEY_RIGHT_ARROW}
		, {VK_BACK, KEY_BACKSPACE}
		, {VK_TAB, KEY_TAB}
		, {VK_RETURN, KEY_RETURN}
		, {VK_ESCAPE, KEY_ESC}
		, {VK_INSERT, KEY_INSERT}
		, {VK_DELETE, KEY_DELETE}
		, {VK_PRIOR, KEY_PAGE_UP}
		, {VK_NEXT, KEY_PAGE_DOWN}
		, {VK_HOME, KEY_HOME}
		, {VK_END, KEY_END}
		, {VK_CAPITAL, KEY_CAPS_LOCK}
		, {VK_F1, KEY_F1}
		, {VK_F2, KEY_F2}
		, {VK_F3, KEY_F3}
		, {VK_F4, KEY_F4}
		, {VK_F5, KEY_F5}
		, {VK_F6, KEY_F6}
		, {VK_F7, KEY_F7}
		, {VK_F8, KEY_F8}
		, {VK_F9, KEY_F9}
		, {VK_F10, KEY_F10}
		, {VK_F11, KEY_F11}
		, {VK_F12, KEY_F12}
		, {VK_F13, KEY_F13}
		, {VK_F14, KEY_F14}
		, {VK_F15, KEY_F15}
		, {VK_F16, KEY_F16}
		, {VK_F17, KEY_F17}
		, {VK_F18, KEY_F18}
		, {VK_F19, KEY_F19}
		, {VK_F20, KEY_F20}
		, {VK_F21, KEY_F21}
		, {VK_F22, KEY_F22}
		, {VK_F23, KEY_F23}
		, {VK_F24, KEY_F24}
	};

	ArduinoUtil::ArduinoUtil(LPCWSTR comPort) : m_serial()
	{
		std::wstring portName = std::wstring(L"\\\\.\\") + comPort;
		if (!this->m_serial.Init(portName.c_str()))
		{
			throw ArduinoException("com port open fail...");
		}
	}

	ArduinoUtil::~ArduinoUtil()
	{
		this->m_serial.DisPose();
	}

	inline BYTE ArduinoUtil::virtualToArduino(BYTE vkCode)
	{
		auto it = g_keyMap.find(vkCode);
		return it != g_keyMap.end() ? it->second : vkCode;
	}

	std::vector<std::wstring> ArduinoUtil::getPortList()
	{
		std::vector<std::wstring> comList;
		WCHAR lpTargetPath[MAX_PATH];

		for (int i = 0; i < 255; i++)
		{
			//COM1 과 같은 문자열로 만듬
			std::wstring str = L"COM" + std::to_wstring(i);

			//해당 장치가 사용 가능한지 체크
			DWORD test = QueryDosDevice(str.c_str(), lpTargetPath, MAX_PATH);

			if (test != 0)
			{
				//사용 가능하다면 리스트에 추가
				comList.push_back(str);
			}
		}

		return comList;
	}

	Result_ ArduinoUtil::button(ButtonType_ type)
	{
		INPUT_DATA data = { 0, };
		data.inputType = (BYTE)InputDataType::BUTTON;
		data.data1 = (INT16)type;
		data.data2 = 0;

		return this->m_serial.WriteData((BYTE*)&data, sizeof(data)) ? Result_::SUCCESS : Result_::FAIL;
	}

	Result_ ArduinoUtil::move(UINT x, UINT y, MoveType_ type)
	{
		INPUT_DATA data = { 0, };
		data.inputType = (BYTE)InputDataType::MOUSE;
		data.data1 = (INT16)x;
		data.data2 = (INT16)y;

		return this->m_serial.WriteData((BYTE*)&data, sizeof(data)) ? Result_::SUCCESS : Result_::FAIL;
	}

	Result_ ArduinoUtil::key(UINT virtualkeyCode, KeyType_ type)
	{
		INPUT_DATA data = { 0, };
		data.inputType = (BYTE)InputDataType::KEY;
		data.data1 = (INT16)type;
		data.data2 = this->virtualToArduino(virtualkeyCode);

		return this->m_serial.WriteData((BYTE*)&data, sizeof(data)) ? Result_::SUCCESS : Result_::FAIL;
	}

	Result_ ArduinoUtil::chr(UINT virtualkeyCode, KeyType_ type)
	{
		INPUT_DATA data = { 0, };
		data.inputType = (BYTE)InputDataType::KEY;
		data.data1 = (INT16)type;
		data.data2 = virtualkeyCode;

		return this->m_serial.WriteData((BYTE*)&data, sizeof(data)) ? Result_::SUCCESS : Result_::FAIL;
	}

	Result_ ArduinoUtil::wheel(UINT count, WheelType_ type)
	{
		INPUT_DATA data = { 0, };
		data.inputType = (BYTE)InputDataType::WHEEL;
		data.data1 = (INT16)type;
		data.data2 = (INT16)count;

		return this->m_serial.WriteData((BYTE*)&data, sizeof(data)) ? Result_::SUCCESS : Result_::FAIL;
	}

	Result_ ArduinoUtil::str(LPCWSTR writeString)
	{
		/*std::wstring temp = writeString;
		std::vector<CHAR_DATA> buf(temp.length());
		for (auto& c : temp)
		{
			CHAR_DATA data = { 0, c };
			if (!std::islower(c)) data.mod = VK_SHIFT;

			buf.push_back(data);
		}

		//여기서 실제 키입력 작업 작성할것.
		*/
		for (INT idx = 0; idx < lstrlen(writeString); idx++)
		{
			if (this->chr(writeString[idx], InputBase::KeyType_::KEY_DOWN) == Result_::FAIL) return Result_::FAIL;
			Sleep(30);
			if (this->chr(writeString[idx], InputBase::KeyType_::KEY_UP) == Result_::FAIL) return Result_::FAIL;
			Sleep(30);
		}

		return Result_::SUCCESS;
	}

	Result_ ArduinoUtil::press(UINT virtualkeyCode, UINT waitTime)
	{
		Result_ result;

		result = this->key(virtualkeyCode, KeyType_::KEY_DOWN);
		Sleep(waitTime);
		result = this->key(virtualkeyCode, KeyType_::KEY_UP);
		Sleep(waitTime);

		return result;
	}
}