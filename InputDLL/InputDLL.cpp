// InputDLL.cpp : DLL을 위해 내보낸 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "InputDLL.h"


// 내보낸 변수의 예제입니다.
INPUTDLL_API int nInputDLL=0;

// 내보낸 함수의 예제입니다.
INPUTDLL_API int fnInputDLL(void)
{
    return 0;
}

// 내보낸 클래스의 생성자입니다.
CInputDLL::CInputDLL()
{
    return;
}

DWORD GetDD64Path(DWORD dwSize, LPWSTR lpBuffer)
{
	WCHAR szTemp[MAX_PATH] = { 0, };
	std::wstring strPath= L"";

	DWORD dwLen = GetTempPath(MAX_PATH, szTemp);
	if (dwLen == 0) return 0;

	strPath = szTemp;
	strPath += L"DD64.dll";

	if (dwSize <= strPath.length()) return 0;

	memcpy_s(lpBuffer, dwSize * sizeof(WCHAR), strPath.c_str(), strPath.length() * sizeof(WCHAR));

	return (DWORD)strPath.length();
}

BOOL SaveFileFromResource(HMODULE hModule, INT nResourceID, LPCTSTR lpszResourceType, LPCTSTR lpszSaveName)
{
	HRSRC hRsrc = ::FindResource(hModule, MAKEINTRESOURCE(nResourceID), lpszResourceType);
	if (hRsrc == NULL) return FALSE;

	HANDLE hRes = ::LoadResource(hModule, hRsrc);
	if (hRes == NULL) return FALSE;

	LPSTR lpRes = (LPSTR)::LockResource(hRes);
	if (lpRes == NULL) return FALSE;

	HANDLE hFile = ::CreateFile(lpszSaveName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	INT nFileSize = ::SizeofResource(hModule, hRsrc);
	DWORD dwWriteSize = 0;
	if (!::WriteFile(hFile, lpRes, nFileSize, &dwWriteSize, NULL))
	{
		::CloseHandle(hFile);
		return FALSE;
	}

	::CloseHandle(hFile);
	return TRUE;
}

BOOL SaveDD64(HMODULE hModule)
{
	WCHAR szBuf[MAX_PATH] = { 0, };
	if (GetDD64Path(MAX_PATH, szBuf) == 0) return FALSE;

	if (!SaveFileFromResource(hModule, IDR_DLL_DD64, L"DLL", szBuf))
	{
		return FALSE;
	}

	return TRUE;
}