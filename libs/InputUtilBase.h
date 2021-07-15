#pragma once
#include <exception>
#include <Windows.h>

namespace InputBase
{
	enum class Result_
	{
		FAIL
		, SUCCESS
	};

	enum class ButtonType_
	{
		LEFT_BUTTON_DOWN
		, LEFT_BUTTON_UP
		, RIGHT_BUTTON_DOWN
		, RIGHT_BUTTON_UP
	};

	enum class MoveType_
	{
		MOVE_ABSOLUTE
		, MOVE_RELATIVE
	};

	enum class WheelType_
	{
		WHEEL_DOWN
		, WHELL_UP
	};

	enum class KeyType_
	{
		KEY_DOWN
		, KEY_UP
		, KEY_PRESS
	};

	class InputException : public std::exception
	{
	private:
		LPCSTR m_errorString;
	public:
		InputException(LPCSTR errorString = NULL) : m_errorString(NULL)
		{
		}

		virtual LPCSTR what() const noexcept override
		{
			return this->m_errorString;
		}
	};

	class InputUtilBaseClass
	{
	public:
		virtual Result_ button(ButtonType_ type) = 0;
		virtual Result_ move(UINT x, UINT y, MoveType_ type) = 0;
		virtual Result_ key(UINT virtualKeyCode, KeyType_ type) = 0;
		virtual Result_ wheel(UINT count, WheelType_ type) = 0;
		virtual Result_ str(LPCWSTR writeString) = 0;
	};
}