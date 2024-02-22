#include "headers/warning.h"


BOOL warning(){
    
    if(MessageBoxW(NULL, 
                  L"This Is Trojen.Win32.Vuvuria\nThis Will Do Unreversable Damage To Your Machine\nAre You Sure You Want to Continue?", 
                  L"Trojen.Win32.Vuvuria", MB_YESNO | MB_ICONWARNING) == IDNO)
    {
        return FALSE;
    }
    if(MessageBoxW(NULL, 
                  L"This Is Your Second Warning\nI Will Not Take Responibilty For Any Damages\nDo You Want To Continue?", 
                  L"Trojen.Win32.Vuvuria", MB_YESNO | MB_ICONWARNING) == IDNO)
    {
        return FALSE;
    }
    return TRUE;
}