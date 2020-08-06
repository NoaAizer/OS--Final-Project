
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int counter=0;


void handler_sigint(int sig) 
{ 
  counter++;
}  

void handler_sigusr1(int sig) 
{ 
 printf("%d \n",counter);
} 

int main(){
    printf("pid=%d\n",getpid());
    if(signal(SIGUSR1, handler_sigusr1)== SIG_ERR)
      printf("\n cannot catch SIGUSR1");
   if(signal(SIGINT, handler_sigint) ==SIG_ERR)
      printf("\n cannot catch SIGINT");
    while(1);
  return 0;
}
