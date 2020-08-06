#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#define SIGINT 2
#define SIGUSR1 10

int main()
{
    int server_pid, signal,counter;
    printf("client ");
    scanf("%d %d %d",&server_pid , &signal, &counter);
    if(signal==SIGINT) 
    {
        printf("SIGINT\n");
        for(int i=1;i<=counter;i++)
            kill(server_pid, SIGINT);
    }
    else if (signal==SIGUSR1)
    {
        printf("SIGUSR1\n");
        for(int j=1;j<=counter;j++)
            kill(server_pid, SIGUSR1);
    }

    return 0;
}