#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>

namespace utils
{
	namespace input
	{
		const INT SERIAL_WAIT_TIME = 2000;

		class Serial
		{
		private:
			//Serial comm handler
			HANDLE m_hSerial;
			//Connection status
			BOOL m_bConnected;
			//Get various information about the connection
			COMSTAT m_Status;
			//Keep track of last error
			DWORD m_dwErrors;

		public:
			//Initialize Serial communication with the given COM port
			Serial();
			Serial(LPCWSTR lpPortName);
			//Close the connection
			virtual ~Serial();

			BOOL Init(LPCWSTR lpPortName);
			//Read data in a buffer, if nbChar is greater than the
			//maximum number of bytes available, it will return only the
			//bytes available. The function return -1 when nothing could
			//be read, the number of bytes actually read.
			INT ReadData(BYTE* lpBuffer, UINT nBufSize);
			//Writes data from a buffer through the Serial connection
			//return true on success.
			BOOL WriteData(BYTE* lpBuffer, UINT nWriteSize);
			//Check if we are actually connected
			BOOL IsConnected();

		};

		class InputBaseClass
		{
		public:
			const BYTE TYPE_KEY = 1;
			const BYTE TYPE_MOUSE = 2;
			const BYTE KEY_DOWN = 1;
			const BYTE KEY_UP = 2;
			const BYTE MOUSE_L_DOWN = 1;
			const BYTE MOUSE_L_UP = 2;
			const BYTE MOUSE_R_DOWN = 4;
			const BYTE MOUSE_R_UP = 8;

			virtual void key(INT nKeyCode, INT nKeyStatus) = 0;
			virtual void click(INT nClickCode) = 0;
			virtual void move(INT x, INT y) = 0;
		};


		const INT DD_BTN_LBUTTONDOWN = 1;
		const INT DD_BTN_LBUTTONUP = 2;
		const INT DD_BTN_RBUTTONDOWN = 4;
		const INT DD_BTN_RBUTTONUP = 8;
		const INT DD_BTN_MBUTTONDOWN = 16;
		const INT DD_BTN_MBUTTONUP = 32;
		const INT DD_BTN_4BUTTONDOWN = 64;
		const INT DD_BTN_4BUTTONUP = 128;
		const INT DD_BTN_5BUTTONDOWN = 256;
		const INT DD_BTN_5BUTTONUP = 512;

		typedef INT(WINAPI* PFDD_BTN)(INT nParam);
		typedef INT(WINAPI* PFDD_MOV)(INT x, INT y);
		typedef INT(WINAPI* PFDD_MOVR)(INT dx, INT dy);
		typedef INT(WINAPI* PFDD_WHL)(INT nParam);
		typedef INT(WINAPI* PFDD_KEY)(INT nParam1, INT nParam2);
		typedef INT(WINAPI* PFDD_STR)(LPCSTR lpszSendString);
		typedef INT(WINAPI* PFDD_TODC)(INT nVK_Code);

		class DD : public InputBaseClass
		{
		private:
			HMODULE m_hModule;
			PFDD_BTN m_pfDD_btn = NULL;
			PFDD_MOV m_pfDD_mov = NULL;
			PFDD_MOVR m_pfDD_movR = NULL;
			PFDD_WHL m_pfDD_whl = NULL;
			PFDD_KEY m_pfDD_key = NULL;
			PFDD_STR m_pfDD_str = NULL;
			PFDD_TODC m_pfDD_todc = NULL;

		public:
			DD();
			DD(LPCWSTR lpszDllPath);
			virtual ~DD();

			BOOL Init(LPCWSTR lpszDllPath);
			VOID DisPose();
			inline INT DD_btn(INT nParam);
			inline INT DD_mov(INT x, INT y);
			inline INT DD_movR(INT dx, INT dy);
			inline INT DD_whl(INT nParam);
			inline INT DD_key(INT nParam1, INT nParam2);
			inline INT DD_str(LPCSTR lpszSendString);
			inline INT DD_todc(INT nVK_Code);
			inline INT DD_keyEx(INT nKeyCode, INT nParam);

			virtual void key(INT nKeyCode, INT nKeyStatus);
			virtual void click(INT nClickCode);
			virtual void move(INT x, INT y);
		};


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


		extern const std::vector<BYTE> ArduinoKeyList;
		extern const std::vector<BYTE> VKeyList;

		class ArduinoInput : public InputBaseClass
		{
		public:
			Serial m_Serial;

		public:
			ArduinoInput();
			ArduinoInput(LPCWSTR lpPortName);
			virtual ~ArduinoInput();

			BOOL Init(LPCWSTR lpPortName);

			inline BYTE VKCodeToArduinoCode(BYTE VkCode);
			virtual void key(INT nKeyCode, INT nKeyStatus);
			virtual void click(INT nClickCode);
			virtual void move(INT x, INT y);
		};

	}
}