#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <lwp.h>
#include <sys/mman.h>
#define RLIMIT_STACK 8388608 //8MB stack size


tid_t lwp_create(lwpfun function, void *argument)
{
    /*
    First allocate a stack and a context for each LWP
    struct registers registers= ...

    //when initializing thread's reg file init structure to predefined FPU_INIT
    
    
    newthread->state.fx = FPU_INIT;

    


    Each thread has it's own stack
    The lwpfun is the function that the lightweight process will be running

    


    char * stack
    size of the stack should be RLIMIT_STACK
    Each stack is individual and should not be shared
    stack = mmap(NULL, howbig, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_STACK, -1, 0)
    if(stack)
    {
        perror("MMAP")
    }

    */

    context *newthread = (context *)malloc(sizeof(struct threadinfo_st));
    newthread->state.fxsave = FPU_INIT;
    newthread->stack = mmap(NULL, RLIMIT_STACK, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS| MAP_STACK, -1, 0);



    //return  tid
}

static void lwp_wrap(lwpfun fun, void *arg)
{

}
void lwp_start(void)
{
    //start the LWP system.

}

void lwp_yield(void)
{

}

void lwp_exit(int exitval){

}

tid_t lwp_wait(int *status)
{

}

tid_t lwp_gettid(void)
{
    
}

thread tid2thread(tid_t tid)
{

}

void lwp_set_scheduler(scheduler sched)
{
    
}

scheduler lwp_get_scheduler(void)
{
    
}



 
int main(int argc, char *argv[])
{
    //Round Robin Scheduler
}
