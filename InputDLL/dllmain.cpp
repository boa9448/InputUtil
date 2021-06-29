// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include <string>
#include "pch.h"
#include "resource.h"

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
	if (GetTempPath(MAX_PATH, szBuf) == 0) return FALSE;

	std::wstring ddPath = szBuf;
	ddPath += L"DD64.dll";
	if (!SaveFileFromResource(hModule, IDR_DLL_DD64, L"DLL", ddPath.c_str()))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		if (!SaveDD64(hModule))
		{
			MessageBox(NULL, L"DLL을 초기화하는데 실패했습니다", L"[InputDLL.dll]", MB_OK);
			return FALSE;
		}
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

