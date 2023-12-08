#define _POSIX_C_SOURCE 1

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int text2bin(char nomFichSource[], char nomFichDest[])
{

    FILE *src;
    FILE *dest;

    int value;
    int occ;

    //fread, fwrite for binary files

    src = fopen(nomFichSource, "rt");
    dest = fopen(nomFichDest, "wb");
    
    while (!feof(src))
    {
        occ ++;
        fscanf(src, "%d", &value);
        // fscanf skip all the non integer values
        fwrite(&value, sizeof(int), 1, dest);
    }


    fclose(src);
    fclose(dest);

    return occ;

}

int bin2text(char nomFichSource[], char nomFichDest[])
{
    FILE *src = NULL;
    FILE *dest = NULL;
    src = fopen(nomFichSource, "rt");
    if (src == NULL)
    {
        perror();
        return -1;
    }
    
}


int main(int argc, char *argv[])
{
    /* if (argc =! 2)
    {
        exit(50);
    } */

    int a = text2bin("source.txt", "dest");

    return 0;
}