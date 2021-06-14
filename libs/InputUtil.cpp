#include "InputUtil.h"

namespace Input
{
	InputUtil::InputUtil(InputType type, LPVOID param)
		: m_inputObject(NULL)
	{
		if (InputType::CLASS_DD == type)
			this->m_inputObject = std::shared_ptr<InputUtilBaseClass>(new ClassDD::DD((LPCWSTR)param));
		else if (InputType::ARDUINO == type)
			this->m_inputObject = std::shared_ptr<InputUtilBaseClass>(new Arduino::ArduinoUtil((LPCWSTR)param));
		else
			throw InputException("Unsupported Type");

		this->m_type = type;
	}

	InputUtil::InputUtil(std::shared_ptr<InputUtilBaseClass> Implement)
		: m_inputObject(NULL)
	{
		this->m_type = InputType::OTHER;
		this->m_inputObject = Implement;
	}

	InputUtil::~InputUtil()
	{
		this->m_inputObject.reset();
	}

	Result InputUtil::button(ButtonType type)
	{
		return this->m_inputObject->button(type);
	}

	Result InputUtil::move(UINT x, UINT y, MoveType type)
	{
		return this->m_inputObject->move(x, y, type);
	}

	Result InputUtil::key(UINT virtualKeyCode, KeyType type)
	{
		return this->m_inputObject->key(virtualKeyCode, type);
	}

	Result InputUtil::wheel(UINT count, WheelType type)
	{
		return this->m_inputObject->wheel(count, type);
	}

	Result InputUtil::str(LPCWSTR writeString)
	{
		return this->m_inputObject->str(writeString);
	}

}
