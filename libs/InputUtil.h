#pragma once
#include <Windows.h>
#include <memory>
#include "ClassDD.h"

namespace Input
{
	using namespace InputBase;

	enum class InputType
	{
		CLASS_DD
		, ARDUINO
	};


	class InputUtil
	{
	private:
		InputType m_type;
		std::shared_ptr<InputUtilBaseClass> m_inputObject;

	public:
		InputUtil(InputType type);
		virtual ~InputUtil();

		Result button(ButtonType type);
		Result move(UINT x, UINT y, MoveType type);
		Result key(UINT virtualKeyCode, KeyType type);
		Result wheel(UINT count, WheelType type);
		Result str(LPCWSTR writeString);
	};
}