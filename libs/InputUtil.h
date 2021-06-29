#pragma once
#include <Windows.h>
#include <memory>
#include "ClassDD.h"
#include "Arduino.h"

#ifdef INPUT_UTIL_DLL_EXPORT
#define INPUT_UTIL_DLL __declspec(dllexport)
#else
#ifdef INPUT_UTIL_STATIC
#define INPUT_UTIL_DLL 
#else
#define INPUT_UTIL_DLL __declspec(dllimport)
#endif
#endif

namespace Input
{
	using namespace InputBase;

	enum class InputType
	{
		CLASS_DD
		, ARDUINO
		, OTHER
	};


	class InputUtil
	{
	private:
		InputType m_type;
		std::shared_ptr<InputUtilBaseClass> m_inputObject;

	public:
		INPUT_UTIL_DLL InputUtil(InputType type, LPVOID param);
		INPUT_UTIL_DLL InputUtil(std::shared_ptr<InputUtilBaseClass> Implement);
		INPUT_UTIL_DLL virtual ~InputUtil();

		INPUT_UTIL_DLL Result button(ButtonType type);
		INPUT_UTIL_DLL Result move(UINT x, UINT y, MoveType type);
		INPUT_UTIL_DLL Result key(UINT virtualKeyCode, KeyType type);
		INPUT_UTIL_DLL Result wheel(UINT count, WheelType type);
		INPUT_UTIL_DLL Result str(LPCWSTR writeString);
	};

	INPUT_UTIL_DLL std::shared_ptr<InputUtil> CreateInputUtil(InputType type, LPVOID param);
}