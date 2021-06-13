#include "Arduino.h"

namespace Arduino
{

	std::map<BYTE, BYTE> g_keyMap = {
		{KEY_LEFT_CTRL, VK_LCONTROL}
		, {KEY_LEFT_SHIFT, VK_LSHIFT}
		, {KEY_LEFT_ALT, VK_LMENU}
		, {KEY_LEFT_GUI, VK_LWIN}
		, {KEY_RIGHT_CTRL, VK_RCONTROL}
		, {KEY_RIGHT_SHIFT, VK_RSHIFT}
		, {KEY_RIGHT_ALT, VK_RMENU}
		, {KEY_RIGHT_GUI, VK_RWIN}
		, {KEY_UP_ARROW, VK_UP}
		, {KEY_DOWN_ARROW, VK_DOWN}
		, {KEY_LEFT_ARROW, VK_LEFT}
		, {KEY_RIGHT_ARROW, VK_RIGHT}
		, {KEY_BACKSPACE, VK_BACK}
		, {KEY_TAB, VK_TAB}
		, {KEY_RETURN, VK_RETURN}
		, {KEY_ESC, VK_ESCAPE}
		, {KEY_INSERT, VK_INSERT}
		, {KEY_DELETE, VK_DELETE}
		, {KEY_PAGE_UP, VK_PRIOR}
		, {KEY_PAGE_DOWN, VK_NEXT}
		, {KEY_HOME, VK_HOME}
		, {KEY_END, VK_END}
		, {KEY_CAPS_LOCK, VK_CAPITAL}
		, {KEY_F1, VK_F1}
		, {KEY_F2, VK_F2}
		, {KEY_F3, VK_F3}
		, {KEY_F4, VK_F4}
		, {KEY_F5, VK_F5}
		, {KEY_F6, VK_F6}
		, {KEY_F7, VK_F7}
		, {KEY_F8, VK_F8}
		, {KEY_F9, VK_F9}
		, {KEY_F10, VK_F10}
		, {KEY_F11, VK_F11}
		, {KEY_F12, VK_F12}
		, {KEY_F13, VK_F13}
		, {KEY_F14, VK_F14}
		, {KEY_F15, VK_F15}
		, {KEY_F16, VK_F16}
		, {KEY_F17, VK_F17}
		, {KEY_F18, VK_F18}
		, {KEY_F19, VK_F19}
		, {KEY_F20, VK_F20}
		, {KEY_F21, VK_F21}
		, {KEY_F22, VK_F22}
		, {KEY_F23, VK_F23}
		, {KEY_F24, VK_F24}
	};

	ArduinoUtil::ArduinoUtil(LPCWSTR comPort) : m_serial()
	{
		this->m_serial.Init(comPort);
	}

	ArduinoUtil::~ArduinoUtil()
	{
		this->m_serial.DisPose();
	}

	Result ArduinoUtil::button(ButtonType type)
	{
		return Result::SUCCESS;
	}

	Result ArduinoUtil::move(UINT x, UINT y, MoveType type)
	{
		return Result::SUCCESS;
	}

	Result ArduinoUtil::key(UINT virtualKeyCode, KeyType type)
	{


		return Result::SUCCESS;
	}

	Result ArduinoUtil::wheel(UINT count, WheelType type)
	{
		return Result::SUCCESS;
	}

	Result ArduinoUtil::str(LPCWSTR writeString)
	{
		return Result::SUCCESS;
	}
}