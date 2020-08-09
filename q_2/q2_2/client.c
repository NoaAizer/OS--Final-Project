#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#define SIGINT 2
#define SIGUSR1 10

int isNumber(char* p ){
    while (*p != '\0')
    {
        if (*p<'0' || *p>'9')
        {
            
            return -1;
        }
        p++;
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc < 4){ //CHECK- amount of arguments
        printf ("Don't forget to pass all arguments!\n");
        return -1;
    }

    if(isNumber(argv[1])==-1 || isNumber(argv[2])==-1 || isNumber(argv[3])==-1){
        printf("Invalid input\n");
        return 0;
    }
    int server_pid = atoi(argv[1]);
    int signal  = atoi(argv[2]);
    int counter = atoi(argv[3]);

    if(signal!=10 && signal!=2){
        printf("Signal should be 2 or 10, got %d\n.",signal);
        return 0;
    }

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