
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sched.h>
#include <sys/syscall.h>


struct sched_attr {
    uint32_t size;              /* Size of this structure */
    uint32_t sched_policy;      /* Policy (SCHED_*) */
    uint64_t sched_flags;       /* Flags */
    int32_t sched_nice;         /* Nice value (SCHED_OTHER, SCHED_BATCH) */
    uint32_t sched_priority;    /* Static priority (SCHED_FIFO, SCHED_RR) */
    /* Remaining fields are for SCHED_DEADLINE */
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};

int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags)
{
   return syscall(__NR_sched_setattr, pid, attr, flags);
}

void print_policy(){
 printf("policy=%s\n",
    (sched_getscheduler(0)==0)? "SCHED_OTHER" :
     (sched_getscheduler(0)==1)? "SCHED_FIFO" :
     (sched_getscheduler(0)==2)? "SCHED_RR" :
     (sched_getscheduler(0)==3)? "SCHED_BATCH" :
     (sched_getscheduler(0)==5)? "SCHED_IDLE" :
     (sched_getscheduler(0)==6)? "SCHED_DEADLINE" :""
     ); 
}

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

int main (int argc , char* argv[]){

        if (argc < 3){ //CHECK- amount of arguments
        printf ("Don't forget to pass all arguments!\n");
        return -1;
    }
    if(isNumber(argv[1])==-1){
        printf("Invalid policy\n");
        return 0;
    }
    if(isNumber(argv[2])==-1){
        printf("Invalid priority\n");
        return 0;
    }
    int policy=atoi(argv[1]); //convert to int
    if(policy!=0 && policy !=1 && policy !=2 && policy!=3 && policy!=5 && policy!=6){ //CHECK- policy number
        printf("Invalid policy number (should be 0/1/2/3/5/6), got %d\n",policy);
        return 0;
    }
   
    int pr= atoi(argv[2]); //convert to int
    printf("Input: priority=%d policy=%d\n",pr,policy);

    //CHECK- priority number
    if((policy==0 || policy==3 || policy==5 || policy==6) && pr!=0){
        printf("Priority must be 0 , got %d.\n",pr);
        return 0;
    }

    if((policy==1 || policy==2) && (pr<1 || pr>99)){
        printf("Priority must be between 1-99 , got %d.\n",pr);
        return 0;
    }

    struct sched_param param;
    sched_getparam(0,&param);

    printf("\nBefore the update:\n\n");
    printf("priority=%d, ",param.sched_priority); //get priority
    print_policy();
   
    param.sched_priority=pr; //set priority

    struct sched_attr attr ={
        .size= sizeof(attr),
        .sched_policy = policy,
        .sched_runtime = 10*1000*1000,
        .sched_period = 2*1000*1000*1000,
        .sched_deadline= 11*1000*1000
    
    };

    if(sched_setattr(0,&attr,0)==-1)
           printf("errorno=%d\n",errno);
     
    if(policy!=6)
    if(sched_setscheduler(0,policy,&param)==-1)
         printf("errorno=%d\n",errno);


     printf("\nAfter the update:\n\n");
     printf("priority=%d, ",param.sched_priority); //get priority
     print_policy();

    return 0;
}
