/**
 * @file signaux.c
 * @author arxaqapi
 * @brief kill programm after 3 SIGINT received
 * @version 0.1
 * @date 2020-11-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int nb;
struct sigaction old;

__sighandler_t handler(int s)
{
    printf(" - received\n");
    nb += 1;
    if (nb == 2)
    {
        if (sigaction(SIGINT, &old, NULL) == -1)
        {
            perror("Error sigaction");
            exit(2);
        }
    }
}

int main(void)
{
    nb = 0;
    struct sigaction sa = {0};
    

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sa.sa_handler = handler;
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, &old) == -1)
    {
        perror("Error sigaction");
        exit(2);
    }

    while (nb != 5)
    {
        // idle
    }

    return 0;
}