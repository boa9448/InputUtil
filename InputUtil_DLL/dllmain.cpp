// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"
#include "resource.h"
#include <fstream>

auto SaveFunc = []()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    HRSRC hRsrc = FindResource(hInstance, MAKEINTRESOURCE(IDR_DLL_CLASS_DD), L"DLL"); // 리소스 아이디, 리소스 형식 입력
    if (hRsrc == NULL) return;

    HANDLE hRes = LoadResource(hInstance, hRsrc);
    if (hRes == NULL) return;

    LPSTR lpRes = (LPSTR)LockResource(hRes);
    if (lpRes == NULL) return;

    std::wofstream file;
    file.open(L".\\temp.dll", std::ios::out | std::ios::binary);


    /*CFile file;
    if (!file.Open(_T("c:\\temp\\test.zip"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary | CFile::shareDenyNone)) // 파일명 입력
        return FAIL;

    file.Write(lpRes, SizeofResource(hInstance, hRsrc)); // 리소스를 파일로 저장
    file.Close();*/
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

