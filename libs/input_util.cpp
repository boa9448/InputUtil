#include "input_util.h"

namespace utils
{
	namespace input
	{

		const std::vector<BYTE> ArduinoKeyList = { KEY_LEFT_CTRL,
												KEY_LEFT_SHIFT,
												KEY_LEFT_ALT,
												KEY_LEFT_GUI,
												KEY_RIGHT_CTRL,
												KEY_RIGHT_SHIFT,
												KEY_RIGHT_ALT,
												KEY_RIGHT_GUI,
												KEY_UP_ARROW,
												KEY_DOWN_ARROW,
												KEY_LEFT_ARROW,
												KEY_RIGHT_ARROW,
												KEY_BACKSPACE,
												KEY_TAB,
												KEY_RETURN,
												KEY_ESC,
												KEY_INSERT,
												KEY_DELETE,
												KEY_PAGE_UP,
												KEY_PAGE_DOWN,
												KEY_HOME,
												KEY_END,
												KEY_CAPS_LOCK,
												KEY_F1,
												KEY_F2,
												KEY_F3,
												KEY_F4,
												KEY_F5,
												KEY_F6,
												KEY_F7,
												KEY_F8,
												KEY_F9,
												KEY_F10,
												KEY_F11,
												KEY_F12,
												KEY_F13,
												KEY_F14,
												KEY_F15,
												KEY_F16,
												KEY_F17,
												KEY_F18,
												KEY_F19,
												KEY_F20,
												KEY_F21,
												KEY_F22,
												KEY_F23,
												KEY_F24 };
		const std::vector<BYTE> VKeyList = { VK_LCONTROL,
												VK_LSHIFT,
												VK_LMENU,
												VK_LWIN,
												VK_RCONTROL,
												VK_RSHIFT,
												VK_RMENU,
												VK_RWIN,
												VK_UP,
												VK_DOWN,
												VK_LEFT,
												VK_RIGHT,
												VK_BACK,
												VK_TAB,
												VK_RETURN,
												VK_ESCAPE,
												VK_INSERT,
												VK_DELETE,
												VK_PRIOR,
												VK_NEXT,
												VK_HOME,
												VK_END,
												VK_CAPITAL,
												VK_F1,
												VK_F2,
												VK_F3,
												VK_F4,
												VK_F5,
												VK_F6,
												VK_F7,
												VK_F8,
												VK_F9,
												VK_F10,
												VK_F11,
												VK_F12,
												VK_F13,
												VK_F14,
												VK_F15,
												VK_F16,
												VK_F17,
												VK_F18,
												VK_F19,
												VK_F20,
												VK_F21,
												VK_F22,
												VK_F23,
												VK_F24 };

		Serial::Serial() : m_dwErrors(0)
			, m_Status()
			, m_bConnected(FALSE)
			, m_hSerial(NULL)
		{
		}
		Serial::Serial(LPCWSTR lpPortName) : Serial()
		{
			this->Init(lpPortName);
		}

		Serial::~Serial()
		{
			//Check if we are connected before trying to disconnect
			if (this->m_bConnected)
			{
				//We're no longer connected
				this->m_bConnected = false;
				//Close the serial handler
				CloseHandle(this->m_hSerial);
			}
		}

		BOOL Serial::Init(LPCWSTR lpPortName)
		{
			//We're not yet connected
			this->m_bConnected = false;

			//Try to connect to the given port throuh CreateFile
			this->m_hSerial = CreateFile(lpPortName,
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			//Check if the connection was successfull
			if (this->m_hSerial == INVALID_HANDLE_VALUE)
			{
				//If not success full display an Error
				if (GetLastError() == ERROR_FILE_NOT_FOUND) {

					//Print Error if neccessary
					wprintf(L"ERROR: Handle was not attached. Reason: %s not available.\n", lpPortName);

				}
				else
				{
					wprintf(L"ERROR!!!");
				}

				return FALSE;
			}
			else
			{
				//If connected we try to set the comm parameters
				DCB dcbSerialParams = { 0 };

				//Try to get the current
				if (!GetCommState(this->m_hSerial, &dcbSerialParams))
				{
					//If impossible, show an error
					wprintf(L"failed to get current serial parameters!");
					return FALSE;
				}
				else
				{
					//Define serial connection parameters for the arduino board
					dcbSerialParams.BaudRate = CBR_9600;
					dcbSerialParams.ByteSize = 8;
					dcbSerialParams.StopBits = ONESTOPBIT;
					dcbSerialParams.Parity = NOPARITY;
					//Setting the DTR to Control_Enable ensures that the Arduino is properly
					//reset upon establishing a connection
					dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

					//Set the parameters and check for their proper application
					if (!SetCommState(this->m_hSerial, &dcbSerialParams))
					{
						wprintf(L"ALERT: Could not set Serial Port parameters");
						return FALSE;
					}
					else
					{
						//If everything went fine we're connected
						this->m_bConnected = true;
						//Flush any remaining characters in the buffers 
						PurgeComm(this->m_hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
						//We wait 2s as the arduino board will be reseting
						Sleep(SERIAL_WAIT_TIME);
					}
				}
			}

			return TRUE;
		}

		INT Serial::ReadData(BYTE* lpBuffer, UINT nBufSize)
		{
			//Number of bytes we'll have read
			DWORD bytesRead;
			//Number of bytes we'll really ask to read
			UINT toRead;

			//Use the ClearCommError function to get status info on the Serial port
			ClearCommError(this->m_hSerial, &this->m_dwErrors, &this->m_Status);

			//Check if there is something to read
			if (this->m_Status.cbInQue > 0)
			{
				//If there is we check if there is enough data to read the required number
				//of characters, if not we'll read only the available characters to prevent
				//locking of the application.
				if (this->m_Status.cbInQue > nBufSize)
				{
					toRead = nBufSize;
				}
				else
				{
					toRead = this->m_Status.cbInQue;
				}

				//Try to read the require number of chars, and return the number of read bytes on success
				if (ReadFile(this->m_hSerial, lpBuffer, toRead, &bytesRead, NULL))
				{
					return bytesRead;
				}

			}

			//If nothing has been read, or that an error was detected return 0
			return 0;

		}


		BOOL Serial::WriteData(BYTE* lpBuffer, UINT nWriteSize)
		{
			DWORD bytesSend;

			//Try to write the buffer on the Serial port
			if (!WriteFile(this->m_hSerial, (void*)lpBuffer, nWriteSize, &bytesSend, 0))
			{
				//In case it don't work get comm error and return false
				ClearCommError(this->m_hSerial, &this->m_dwErrors, &this->m_Status);

				return FALSE;
			}
			else
				return TRUE;
		}

		BOOL Serial::IsConnected()
		{
			//Simply return the connection status
			return this->m_bConnected;
		}


		DD::DD() : m_hModule(NULL)
			, m_pfDD_btn(NULL)
			, m_pfDD_mov(NULL)
			, m_pfDD_key(NULL)
			, m_pfDD_movR(NULL)
			, m_pfDD_str(NULL)
			, m_pfDD_whl(NULL)
			, m_pfDD_todc(NULL)
		{
		}

		DD::DD(LPCWSTR lpszDllPath) : m_hModule(NULL)
			, m_pfDD_btn(NULL)
			, m_pfDD_mov(NULL)
			, m_pfDD_key(NULL)
			, m_pfDD_movR(NULL)
			, m_pfDD_str(NULL)
			, m_pfDD_whl(NULL)
			, m_pfDD_todc(NULL)
		{
			if (this->Init(lpszDllPath) == FALSE)
			{
				MessageBox(NULL, TEXT("DD_초기화 실패"), TEXT("Error"), MB_OK);
			}
		}

		DD::~DD()
		{
			this->DisPose();
		}

		INT DD::Init(LPCWSTR lpszDllPath)
		{
			this->DisPose();

			this->m_hModule = LoadLibraryW(lpszDllPath);
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

		INT DD::DD_btn(INT nParam)
		{
			return this->m_pfDD_btn(nParam);
		}

		INT DD::DD_mov(INT x, INT y)
		{
			return this->m_pfDD_mov(x, y);
		}

		INT DD::DD_movR(INT dx, INT dy)
		{
			return this->m_pfDD_movR(dx, dy);
		}

		INT DD::DD_whl(INT nParam)
		{
			return this->m_pfDD_whl(nParam);
		}

		INT DD::DD_key(INT nParam1, INT nParam2)
		{
			return this->m_pfDD_key(nParam1, nParam2);
		}

		INT DD::DD_str(LPCSTR lpszSendString)
		{
			return this->m_pfDD_str(lpszSendString);
		}

		INT DD::DD_todc(INT nVK_Code)
		{
			return this->m_pfDD_todc(nVK_Code);
		}

		//volatile LONG g_bRunKeyEx = FALSE;
		INT DD::DD_keyEx(INT nKeyCode, INT nParam)
		{
			/*
			for (;;)
			{
				if (InterlockedCompareExchange(&g_bRunKeyEx, TRUE, FALSE) != TRUE) break;
				Sleep(1);
			}
			INT nRet = this->DD_key(this->DD_todc(nKeyCode), nParam);

			InterlockedExchange(&g_bRunKeyEx, FALSE);

			return nRet;
			*/
			return this->DD_key(this->DD_todc(nKeyCode), nParam);
		}

		void DD::key(INT nKeyCode, INT nKeyStatus)
		{
			this->DD_keyEx(nKeyCode, nKeyStatus);
		}

		void DD::click(INT nClickCode)
		{
			this->DD_btn(nClickCode);
		}

		void DD::move(INT x, INT y)
		{
			this->DD_mov(x, y);
		}


		ArduinoInput::ArduinoInput()
		{
		}

		ArduinoInput::ArduinoInput(LPCWSTR lpPortName) : m_Serial(lpPortName)
		{
		}

		ArduinoInput::~ArduinoInput()
		{
		}

		BOOL ArduinoInput::Init(LPCWSTR lpPortName)
		{
			return this->m_Serial.Init(lpPortName);
		}

		void ArduinoInput::key(INT nKeyCode, INT nKeyStatus)
		{
			//0 : 인풋타입(키, 마), 1 : 상태, 2 : 키코드
			BYTE WriteBuf[3] = { TYPE_KEY, (BYTE)nKeyStatus
				, (BYTE)this->VKCodeToArduinoCode(nKeyCode) };

			this->m_Serial.WriteData(WriteBuf, 3);
		}

		void ArduinoInput::click(INT nClickCode)
		{
			//0 : 인풋타입(키, 마), 1 : 클릭 코드
			BYTE WriteBuf[2] = { TYPE_MOUSE, (BYTE)nClickCode };
			this->m_Serial.WriteData(WriteBuf, 2);
		}

		void ArduinoInput::move(INT x, INT y)
		{
			//2020.12.13 : WDW : 아직 구현하지 않음
			//이 함수는 현재 마우스 커서를 기준으로 이동하는 식으로 구현되어야함
			//아두이노에서 현재 마우스 커서에서 상대 이동을 하는 방식임
			//듀얼모니터를 지원할 수 있도록 구현되어야함
			//0 : 인풋타입(키, 마), 1 ~ 2 : 상태, 3 ~ 4 : 키코드
			BYTE WriteBuf[3] = { TYPE_MOUSE, };
			this->m_Serial.WriteData(WriteBuf, 3);
		}

		BYTE ArduinoInput::VKCodeToArduinoCode(BYTE VkCode)
		{
			if (VkCode >= 65 && VkCode <= 127) return VkCode;
			for (INT a = 0; a < VKeyList.size(); a++)
			{
				if (VkCode == VKeyList[a]) return ArduinoKeyList[a];
			}

			return 0;
		}
	}
}