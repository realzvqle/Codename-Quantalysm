#include "headers/checkifran.h"
#include <winbase.h>





BOOL checkIfRan(){
    OFSTRUCT OpenBuff;
    HFILE file = OpenFile("C:\\ProgramData\\APHostClient.sys", &OpenBuff, OF_EXIST);
    if(file == HFILE_ERROR){
        return FALSE;
    }
    else{
        return TRUE;
    }
}