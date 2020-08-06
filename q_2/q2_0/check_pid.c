
#include <stdio.h>
#include <errno.h>
#include <signal.h>

int main()
{
    int pid;
    printf("check_pid ");
    scanf("%d", &pid);
    if (kill(pid,0)==-1)
       {
	    if(errno==EPERM)
		    printf("Process %d exists but we have no permission.\n",pid);
	    else if (errno == ESRCH)
		    printf("Process %d does not exists.\n",pid);
	    }
    else if(kill(pid,0)==0)
	    printf("Process %d exists.\n",pid);
 
    return 0;
}
