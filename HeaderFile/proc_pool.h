#ifndef __PH__PROC__POOL
#define __PH__PROC__POOL

#define __DEBUG
#include "unixhead.h"
typedef struct
{
    pid_t pid;
    int fd;
    char isbusy;
}child_proc_t;

// generate child process and set child process information.
int make_child_process(child_proc_t*,int);
// child process function
void child_process_handler(int pipefd);
// receive mission
int recv_sockfd(int*);



#endif
