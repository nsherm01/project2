#ifndef LWPH
#define LWPH
#include <sys/types.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE O
#endif


#if defined(_x86_64)
#include <fp.h>
typedef struct_attribute_((aligned(16))) __attribute_((packed))
    registers
{
    unsigned long rax; /* the sixteen architecturally-visible regs. */
    unsigned long rbx;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rsi;
    unsigned long rdi;
    unsigned long rbp;
    unsigned long rsp;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;
    struct fxsave fxsave;
    /* space to save floating point state */
} rfile;
#else
    #error "This only works on x86_64 for now"
#endif

typedef unsigned long tid_t;
#define NO_THREAD 0 /* an always invalid thread id*/
typedef struct threadinfo_st *thread;
typedef struct threadinfo_st
{
    tid_t tid;
    unsigned long *stack;
    size_t stacksize;
    rfile state;
    unsigned int status;
    thread lib_one;
    thread lib_two;
    thread sched_one;
    thread sched_two;
    thread exited;

} context;

typedef int (*lwpfun)(void *);

typedef struct scheduler
{
    void (*init)(void);
    /* initialize any structures
     */
    void (*shutdown)(void);
    void (*admit)(thread new);
    void (*remove)(thread victim);
    /* remove a thread from the pool */
    thread (*next)(void);
    /* select a thread to schedule */

    int (*qlen)(void);
    /* number of ready threads */
} *scheduler;

/* lwp functions */
extern tid_t lwp_create(lwpfun, void *);
extern void lwp_exit(int status);
extern tid_t lwp_gettid(void);
extern void lwp_yield(void);
extern void lwp_start(void);
extern void lwp_stop(void);
extern tid_t lwp_wait(int *);
extern void lwp_set_scheduler(scheduler fun);
extern scheduler lwp_get_scheduler(void);
extern thread tid2thread(tid_t tid);
/* for lwp_wait */
#define TERMOFFSET 8
#define MKTERMSTAT(a, b) ((a) << TERMOFFSET | ((b) & ((1 << TERMOFFSET) - 1)))
#define LWP_TERM 1
#define LWP_LIVE 0
#define LWPTERMINATED (s)((((s) >> TERMOFFSET) & LWP_TERM) == LWP_TERM) #define LWPTERMSTAT(s)((s) & ((1 << TERMOFFSET) - 1))
#define LWPTERMSTAT(s) ((s) & ((1 << TERMOFFSET) - 1))

void swap_rfiles(rfile, *old, rfile, *new);
#endif
