#include "headers/warning.h"
#include "headers/checkifran.h"
#include "headers/setup.h"
#include "headers/mainloop.h"


BOOL isAdmin() {
    BOOL isAdmin;
    SID_IDENTIFIER_AUTHORITY NTA = SECURITY_NT_AUTHORITY;
    PSID AdminGroup;
    AllocateAndInitializeSid(&NTA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdminGroup);
    CheckTokenMembership(NULL, AdminGroup, &isAdmin);
    FreeSid(AdminGroup);
    return isAdmin;
}


int main(int argc, char* argv[]){
    if(!isAdmin()){
        MessageBoxW(NULL, L"Please Run the Installer As Admin!", L"Installer", MB_OK | MB_ICONERROR);
        return -1;
    }
    if(!checkIfRan()){
        if(!warning()){
            return 1;
        }
        state state;
        state.currentFile = argv[0];
        setup(&state);
        return 0;
    }
    mainLoop();
    return 0;
}