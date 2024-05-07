#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Erreur nb de paramètres: %d au lieu de 3", argc - 1);
        exit(1);
    }
    int stdin_f, stdo_f;
    if ((stdin_f = open(argv[2], O_RDONLY)) == -1)
    {
        perror(argv[2]);
        exit(2);
    }

    if ((stdo_f = open(argv[3], O_WRONLY | O_CREAT | O_APPEND,
                       S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR)) == -1) // readd all , write proprio
    {
        perror(argv[3]);
        close(stdin_f);
        exit(2);
    }

    if (dup2(stdin_f, STDIN_FILENO) == -1)
    {
        perror("Probleme redirection, de l'entree standard");
        close(stdin_f);
        close(stdo_f);
        exit(4);
    }
    if (dup2(stdo_f, STDOUT_FILENO) == -1)
    {
        perror("Probleme redirection de la sortie standart");
        close(stdin_f);
        close(stdo_f);
        exit(5);
    }
    if (fork() == 0) /* Proc fils */
    {
        execl(argv[1], argv[1], NULL]);
        perror(argv[1]);
        close(stdin_f);
        close(stdo_f);
        exit(6);
    }

    close(stdin_f);
    close(stdo_f);
    exit(0);

    return 0;
}