
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

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

int main(int agrc, char* argv[])
{

    if(isNumber(argv[1])==-1){
        printf("Invalid pid\n");
        return 0;
    }
    int pid= atoi(argv[1]); //convert to int
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
