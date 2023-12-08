#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define _POSIX_C_SOURCE 1

#define TAILLE_BLOC 512

int main (int argc, char argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "usage %s, source destination", argv[0]);
        exit(1);
    }
    int source, destination;
    if ( (source = open(argv[1], O_RDONLY)) == -1)
    {
        perror("argv[1]");
        exit(2);
    }
    if ((destination = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IRGRP | S_IWUSR)) == -1)
    {
        perror("argv[2]");
        exit(2);
    }
    int restant;
    char bloc[TAILLE_BLOC];

    //  Read or write: pointeur se déplace du nb octet lu/écrit
    while ((restant = read(source, bloc, TAILLE_BLOC)) > 0)
    {
        write(destination, &bloc, restant);
    }
    close(source);
    close(destination);
    exit(0);      
    

    return 0;
}