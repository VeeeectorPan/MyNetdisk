#ifndef __PH__PROC__POOL
#define __PH__PROC__POOL

#define __DEBUG
#include "unixhead.h"
typedef struct
{
    pid_t pid;
    int fd;
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
// transfer file function
int transfer_file(int sock_fd,int file_fd);
// receive mission
int recv_fd(int pipefd,int* fd);
// send mission
int send_fd(int pipefd,int fd);
// recv_N_bytes
int recv_n_bytes(int fd,void* buf,int len);

#endif
