#include <sys/types.h>
#include <unistd.h>


int n_ieme(int fd, int n)
{
    int ENTIER;
    lseek(fd, (n - 1) * sizeof(int), SEEK_SET);
    read(fd, &ENTIER, sizeof(ENTIER));
    return ENTIER;
}