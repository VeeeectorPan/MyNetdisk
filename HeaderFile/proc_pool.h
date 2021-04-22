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

#define FILENAME "file"
typedef struct
{
    // 0 ~ _SC_PAGE_SIZE - sizeof(int)
    int data_len;
    char buf[_SC_PAGE_SIZE - sizeof(int)];
}trans_t;

// generate child process and set child process information.
int make_child_process(child_proc_t*,int);
// child process function
void child_process_handler(int pipefd);
// receive mission
int recv_sockfd(int*);
int recv_fd(int pipefd,int* fd);
int send_fd(int pipefd,int fd);


#endif
