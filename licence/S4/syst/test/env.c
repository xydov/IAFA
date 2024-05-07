#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (getenv(argv[i]) != NULL)
            {
                printf("%s\n", getenv(argv[i]));
            } else
            {
                fprintf(stderr, "ERREUR LOL %s", argv[0]);
                //  exit(2);
                return 1;
            }
            
        }
        
    } else
    {
        fprintf(stderr, "Not enough argupments, argc = %d", argc);
        //  exit(1);
        return 1;
    }
    
    return 0;
}