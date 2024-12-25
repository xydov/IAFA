#define _POSIX_C_SOURCE 1

#include "h.h"

void disp_inf()
{
    pid_t p;
    /* char *c;
    uid_t u;
    gid_t g; */
    p = getpid();
    printf("pid: %d\n", p);
    p = getppid();
    printf("ppid: %d\n", p);
    p = getpgrp();
    printf("pgrp: %d\n", p);
    /* c = getlogin();
    printf("login: %s\n", c);
    u = getuid();
    printf("uid: %d\n", u);
    g = getgid();
    printf("gid: %d\n", g); */
}

int main(void)
{
    pid_t pid;
    /* pid_t pid_fils; */


    int circ; // réservation de la case mémoire permettant l'accès + tard
    // si circ est un pointeur, alors il ne réserva pas la mémoire de l'élément pointé

    switch (pid = fork())
    {
    case -1:
        printf("Problème!!\n");
        break;
    case 0:
        // dans le fils la wesh
        printf("Fils\n");
        disp_inf();
        exit(4);
        // dans le fils la wesh

    default:

        if (wait(&circ) != -1)
        {
            printf("Code de retour fils = %d\n", WEXITSTATUS(circ));
        }

        printf("Père\n");
        disp_inf();
        break;
    }

    return 0;
}