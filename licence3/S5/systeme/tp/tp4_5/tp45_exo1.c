#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
// #include <semaphore.h>

#define MAX_PROC 10
#define NB_TOURS 2

int n_processes;
typedef struct msg
{
    pid_t emmeteur;
    const int value;
    int acc;
} msg_s;

void proc(int mon_num, int **tubes)
{
    msg_s msg;
    int next = ((mon_num + 1) % (n_processes));
    // close unused tube
    for (int i = 0; i < n_processes; i++)
    {
        if (i != next)
        {
            close(tubes[i][1]);
        }
    }

    while (read(tubes[mon_num][0], &msg, sizeof(msg_s)) > 0)
    {
        // msg initialized
        char text[200] = "";
        sprintf(text, "Processus de pid %d, n°%d dans l’anneau : j’ai reçu de %d, j’envoie au n°%d l’info [%d – %d – %d]\n",
                getpid(), mon_num, msg.emmeteur, next,
                /*[*/
                getpid(), msg.value, ++msg.acc
                /*]*/
        );
        msg.emmeteur = getpid();
        // afficher info
        write(STDOUT_FILENO, &text, sizeof(text));
        // send msg to next
        close(tubes[next][0]);
        write(tubes[next][1], &msg, sizeof(msg));
    }
    close(tubes[next][1]);    // -> EOF to next
    close(tubes[mon_num][0]); // <- EOF

    exit(mon_num + 1);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s Nombre de processus\n", argv[0]);
        exit(1);
    }
    n_processes = atoi(argv[1]);
    // limit the number of process creation
    if (n_processes > MAX_PROC)
    {
        n_processes = MAX_PROC;
    }
    //init
    pid_t *processes = calloc(n_processes, sizeof(pid_t));

    // Create/activate pipes
    int **tubes = calloc(n_processes, sizeof(int *));
    for (int i = 0; i < n_processes; i++)
    {
        tubes[i] = calloc(2, sizeof(int));
        if (pipe(tubes[i]) == -1)
        {
            perror("Erreur création des pipes");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i < n_processes; i++)
    {
        switch (processes[i] = fork())
        {
        case 0:
            proc(i, tubes); // child process
            break;
        case -1:
            perror("Echec fork");
            exit(EXIT_FAILURE);
            break;
        }
    }
    // parent process -> send to 1
    msg_s data = {.emmeteur = getpid(), .value = 999, .acc = 1};
    int next = 1;

    // print pid info
    char text[200] = "";

    // close
    for (int i = 0; i < n_processes; i++)
    {
        if (i != next)
        {
            close(tubes[i][1]);
        }
    }
    //
    close(tubes[next][0]);
    // bcl nb tours
    for (int i = 0; i < NB_TOURS; i++)
    {
        sprintf(text, "Processus de pid %d, n°%d dans l’anneau :j’envoie au n°%d l’info [%d – %d – %d]\n",
                data.emmeteur, 0, next,
                /*[*/
                data.emmeteur, data.value, data.acc
                /*]*/
        );
        // stdout
        write(STDOUT_FILENO, &text, sizeof(text));
        write(tubes[next][1], &data, sizeof(data));

        if (read(tubes[0][0], &data, sizeof(data)) > 0)
        {
            printf("Processus de pid %d : l’information m’est revenue de %d, je peux me terminer\n", getpid(), data.emmeteur);
        }
    }
    close(tubes[next][1]); // -> EOF
    // fin nb tours
    close(tubes[0][0]);
    close(tubes[0][1]);

    // attendre la fin des processus fils
    while (wait(NULL) != -1)
        ;

    return 0;
}
