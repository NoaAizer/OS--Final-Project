
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int pid;
    printf("check_pid ");
    struct stat  stt;
   
    scanf("%d", &pid);
     //if(stat(("/proc/%d",pid),&stt)==-1)
       // printf("fALSE");
    if (getpgid(pid)!=-1)
       printf("%d exists.\n",pid);
    else
    {
         printf("%d  does not exists.\n",pid);
    }
    

 
    return 0;
}
