#include "ClassDD.h"


namespace ClassDD
{
	DD::DD() : m_hModule(NULL)
		, m_pfDD_btn(NULL)
		, m_pfDD_mov(NULL)
		, m_pfDD_key(NULL)
		, m_pfDD_movR(NULL)
		, m_pfDD_str(NULL)
		, m_pfDD_whl(NULL)
		, m_pfDD_todc(NULL)
	{
		this->m_buttonMap = {
			{ButtonType::LEFT_BUTTON_DOWN, DD_BTN_LBUTTONDOWN}
			, {ButtonType::LEFT_BUTTON_UP, DD_BTN_LBUTTONUP}
			, {ButtonType::RIGHT_BUTTON_DOWN, DD_BTN_RBUTTONDOWN}
			, {ButtonType::RIGHT_BUTTON_UP, DD_BTN_RBUTTONUP}
		};
	}

	DD::DD(LPCWSTR dllPath) : m_hModule(NULL)
		, m_pfDD_btn(NULL)
		, m_pfDD_mov(NULL)
		, m_pfDD_key(NULL)
		, m_pfDD_movR(NULL)
		, m_pfDD_str(NULL)
		, m_pfDD_whl(NULL)
		, m_pfDD_todc(NULL)
	{
		if (this->Init(dllPath) == FALSE)
		{
			MessageBox(NULL, TEXT("DD_초기화 실패"), TEXT("Error"), MB_OK);
		}
	}

	DD::~DD()
	{
		this->DisPose();
	}

	INT DD::Init(LPCWSTR dllPath)
	{
		this->DisPose();

		this->m_hModule = LoadLibraryW(dllPath);
		if (this->m_hModule == NULL)
		{
			return FALSE;
		}


		//함수를 못 찾았을 때 에러처리 추가할 것.
		this->m_pfDD_btn = (PFDD_BTN)GetProcAddress(this->m_hModule, "DD_btn");
		this->m_pfDD_mov = (PFDD_MOV)GetProcAddress(this->m_hModule, "DD_mov");
		this->m_pfDD_key = (PFDD_KEY)GetProcAddress(this->m_hModule, "DD_key");
		this->m_pfDD_movR = (PFDD_MOVR)GetProcAddress(this->m_hModule, "DD_movR");
		this->m_pfDD_str = (PFDD_STR)GetProcAddress(this->m_hModule, "DD_str");
		this->m_pfDD_whl = (PFDD_WHL)GetProcAddress(this->m_hModule, "DD_whl");
		this->m_pfDD_todc = (PFDD_TODC)GetProcAddress(this->m_hModule, "DD_todc");

		return TRUE;
	}

	VOID DD::DisPose()
	{
		if (this->m_hModule != NULL)
		{
			FreeLibrary(this->m_hModule);
			this->m_hModule = NULL;
		}
	}

	INT DD::DD_btn(INT param)
	{
		return this->m_pfDD_btn(param);
	}

	INT DD::DD_mov(INT x, INT y)
	{
		return this->m_pfDD_mov(x, y);
	}

	INT DD::DD_movR(INT x, INT y)
	{
		return this->m_pfDD_movR(x, y);
	}

	INT DD::DD_whl(INT param)
	{
		return this->m_pfDD_whl(param);
	}

	INT DD::DD_key(INT param1, INT param2)
	{
		return this->m_pfDD_key(param1, param2);
	}

	INT DD::DD_str(LPCSTR sendString)
	{
		return this->m_pfDD_str(sendString);
	}

	INT DD::DD_todc(INT virtualKeyCode)
	{
		return this->m_pfDD_todc(virtualKeyCode);
	}

	INT DD::DD_keyEx(INT virtualKeyCode, INT param)
	{
		return this->DD_key(this->DD_todc(virtualKeyCode), param);
	}

	Result DD::button(ButtonType type)
	{
		INT ddType = this->m_buttonMap[type];

		if (ddType == 0) return Result::FAIL;
		this->m_pfDD_btn(ddType);

		return Result::SUCCESS;
	}

	Result DD::move(UINT x, UINT y, MoveType type)
	{
		if (type == MoveType::MOVE_ABSOLUTE) this->m_pfDD_mov(x, y);
		else if (type == MoveType::MOVE_RELATIVE) this->m_pfDD_movR(x, y);
		else return Result::FAIL;

		return Result::SUCCESS;
	}

	Result DD::key(UINT virtualKeyCode, KeyType type)
	{
		UINT ddCode = this->m_pfDD_todc(virtualKeyCode);
		INT ddKeyType = type == KeyType::KEY_DOWN ? DD_KEY_DOWN : DD_KEY_UP;
		this->m_pfDD_key(ddCode, ddKeyType);

		return Result::SUCCESS;
	}

	Result DD::wheel(UINT count, WheelType type)
	{
		return Result::SUCCESS;
	}

	Result DD::str(LPCWSTR writeString)
	{
		return Result::SUCCESS;
	}
}