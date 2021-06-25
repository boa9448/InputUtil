#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <string>
#include "Serial.h"
#include "InputUtilBase.h"

namespace Arduino
{
	using namespace InputBase;
	using namespace Serial;


	const BYTE KEY_LEFT_CTRL = 0x80;
	const BYTE KEY_LEFT_SHIFT = 0x81;
	const BYTE KEY_LEFT_ALT = 0x82;
	const BYTE KEY_LEFT_GUI = 0x83;
	const BYTE KEY_RIGHT_CTRL = 0x84;
	const BYTE KEY_RIGHT_SHIFT = 0x85;
	const BYTE KEY_RIGHT_ALT = 0x86;
	const BYTE KEY_RIGHT_GUI = 0x87;

	const BYTE KEY_UP_ARROW = 0xDA;
	const BYTE KEY_DOWN_ARROW = 0xD9;
	const BYTE KEY_LEFT_ARROW = 0xD8;
	const BYTE KEY_RIGHT_ARROW = 0xD7;
	const BYTE KEY_BACKSPACE = 0xB2;
	const BYTE KEY_TAB = 0xB3;
	const BYTE KEY_RETURN = 0xB0;
	const BYTE KEY_ESC = 0xB1;
	const BYTE KEY_INSERT = 0xD1;
	const BYTE KEY_DELETE = 0xD4;
	const BYTE KEY_PAGE_UP = 0xD3;
	const BYTE KEY_PAGE_DOWN = 0xD6;
	const BYTE KEY_HOME = 0xD2;
	const BYTE KEY_END = 0xD5;
	const BYTE KEY_CAPS_LOCK = 0xC1;
	const BYTE KEY_F1 = 0xC2;
	const BYTE KEY_F2 = 0xC3;
	const BYTE KEY_F3 = 0xC4;
	const BYTE KEY_F4 = 0xC5;
	const BYTE KEY_F5 = 0xC6;
	const BYTE KEY_F6 = 0xC7;
	const BYTE KEY_F7 = 0xC8;
	const BYTE KEY_F8 = 0xC9;
	const BYTE KEY_F9 = 0xCA;
	const BYTE KEY_F10 = 0xCB;
	const BYTE KEY_F11 = 0xCC;
	const BYTE KEY_F12 = 0xCD;
	const BYTE KEY_F13 = 0xF0;
	const BYTE KEY_F14 = 0xF1;
	const BYTE KEY_F15 = 0xF2;
	const BYTE KEY_F16 = 0xF3;
	const BYTE KEY_F17 = 0xF4;
	const BYTE KEY_F18 = 0xF5;
	const BYTE KEY_F19 = 0xF6;
	const BYTE KEY_F20 = 0xF7;
	const BYTE KEY_F21 = 0xF8;
	const BYTE KEY_F22 = 0xF9;
	const BYTE KEY_F23 = 0xFA;
	const BYTE KEY_F24 = 0xFB;

	extern std::map<BYTE, BYTE> g_keyMap;

	class ArduinoException : public InputException
	{
	private:
		LPCSTR m_errorString;
	public:
		ArduinoException(LPCSTR errorString = NULL) : m_errorString(errorString)
		{
		}

		virtual LPCSTR what() const noexcept override
		{
			return this->m_errorString;
		}
	};

	enum class InputDataType
	{
		KEY
		, MOUSE
		, BUTTON
		, WHEEL
	};

	typedef struct _charData
	{
		DWORD mod;
		CHAR c;
	}CHAR_DATA;

#pragma pack(push, 1)
    typedef struct _InputData
    {
        BYTE inputType;
        INT16 data1;
        INT16 data2;
    }INPUT_DATA;
#pragma pack(pop)

    class ArduinoUtil : public InputUtilBaseClass
    {
	private:
		SerialUtil m_serial;

    public:
        ArduinoUtil(LPCWSTR comPort);
        virtual ~ArduinoUtil();

		BYTE virtualToArduino(BYTE vkCode);
		static std::vector<std::wstring> getPortList();

		virtual Result button(ButtonType type);
        virtual Result move(UINT x, UINT y, MoveType type);
        virtual Result key(UINT virtualKeyCode, KeyType type);
        virtual Result wheel(UINT count, WheelType type);
        virtual Result str(LPCWSTR writeString);
		virtual Result press(UINT virtualKeyCode, UINT waitTime = 30);
    };
}