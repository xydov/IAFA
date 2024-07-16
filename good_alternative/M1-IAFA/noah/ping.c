#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
    char msg[] = "ping ";
    int tube[2];
    char *car;
    pid_t pid;
    if(pipe(tube)==-1)
        exit(1);
    pid = fork();
    switch (pid)
    {
        case -1:
            printf("echec");
            break;
        case 0:
            close(tube[0]);
            for(int  i = 0; i < 6; i++){
                printf("ping \n");
                write(tube[1], (void *)msg, sizeof(char) * (strlen(msg)+1));
                sleep(1);
            }
            close(tube[1]);
            break;
        default:
            close(tube[1]);
            while(read(tube[0], (void *)&car, sizeof(char) * (strlen(msg)+1))){
                printf("pong \n");
            }
            close(tube[0]);
            break;
    }

}