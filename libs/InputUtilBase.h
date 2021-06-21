#pragma once
#include <exception>
#include <Windows.h>

namespace InputBase
{
	enum class Result
	{
		FAIL
		, SUCCESS
	};

	enum class ButtonType
	{
		LEFT_BUTTON_DOWN
		, LEFT_BUTTON_UP
		, RIGHT_BUTTON_DOWN
		, RIGHT_BUTTON_UP
	};

	enum class MoveType
	{
		MOVE_ABSOLUTE
		, MOVE_RELATIVE
	};

	enum class WheelType
	{
		WHEEL_DOWN
		, WHELL_UP
	};

	enum class KeyType
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
		virtual Result button(ButtonType type) = 0;
		virtual Result move(UINT x, UINT y, MoveType type) = 0;
		virtual Result key(UINT virtualKeyCode, KeyType type) = 0;
		virtual Result wheel(UINT count, WheelType type) = 0;
		virtual Result str(LPCWSTR writeString) = 0;
	};
}