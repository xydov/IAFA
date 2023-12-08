#include "h.h"

void ouiuiuouiuouiuo(char *root_rep)
{
    struct Dir *repertory;
    struct dirent *el;
    struct stat laStat;



    if (!strcmp(root_rep, ".") && !strcmp(root_rep, "..")) {
        if (S_ISDIR("rep/elem".st_mode))
        {
            ouiuiuouiuouiuo(strcat(root_rep, "el"));
        }
        else {
            printf("%s", strcat(root_rep, "el"));
        }
        
    }
}