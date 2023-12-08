#include "h.h"

long TailleRepCour(void)
{
    struct Dir *dir;
    struct dirent *el;
    struct stat laStat; // pas de pointeur
    size_t somme = 0;

    if ((dir = opendir('.')) == NULL)
    {
        perror(".");
        return -1;
    }
    

    while ((el = readdir(dir) != NULL))
    {
        if (stat(el->d_name, &laStat) != -1)
        {
            if (S_ISDIR(laStat.st_mode) == 0)
            {
                somme += laStat.st_size;
            }
            
        } else {
            perror(el->d_name);
        }
    }
    closedir(dir);
    return somme;
}