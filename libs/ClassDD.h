#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include "InputUtilBase.h"

namespace ClassDD
{
	using namespace InputBase;

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

	const INT DD_KEY_DOWN = 1;
	const INT DD_KEY_UP = 2;

	typedef INT(WINAPI* PFDD_BTN)(INT param);
	typedef INT(WINAPI* PFDD_MOV)(INT x, INT y);
	typedef INT(WINAPI* PFDD_MOVR)(INT x, INT y);
	typedef INT(WINAPI* PFDD_WHL)(INT param);
	typedef INT(WINAPI* PFDD_KEY)(INT param1, INT param2);
	typedef INT(WINAPI* PFDD_STR)(LPCSTR sendString);
	typedef INT(WINAPI* PFDD_TODC)(INT virtualKeyCode);

	class DD : public InputUtilBaseClass
	{
	private:
		std::map<ButtonType_, INT> m_buttonMap;

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
		DD(LPCWSTR dllPath);
		virtual ~DD();

		BOOL Init(LPCWSTR dllPath);
		VOID DisPose();
		INT DD_btn(INT param);
		INT DD_mov(INT x, INT y);
		INT DD_movR(INT x, INT y);
		INT DD_whl(INT param);
		INT DD_key(INT param1, INT param2);
		INT DD_str(LPCSTR sendString);
		INT DD_todc(INT virtualKeyCode);
		INT DD_keyEx(INT virtualKeyCode, INT nParam);

		//가상함수의 구현
		virtual Result_ button(ButtonType_ type);
		virtual Result_ move(UINT x, UINT y, MoveType_ type);
		virtual Result_ key(UINT virtualKeyCode, KeyType_ type);
		virtual Result_ wheel(UINT count, WheelType_ type);
		virtual Result_ str(LPCWSTR writeString);
	};
}