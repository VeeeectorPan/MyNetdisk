#ifndef  __PTHREAD__POOL__
#define  __PTHREAD__POOL__
#include "queue.h"
#include "unixhead.h"
#define FILENAME "file"
typedef struct
{
    int data_len;
    char buf[_SC_PAGE_SIZE - sizeof(int)];
}trans_t;

int recv_n_bytes(int fd,void* buf,int len);
int recv_file(int sock_fd,int file_fd, int file_size);

#endif
