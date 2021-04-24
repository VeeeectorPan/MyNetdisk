#ifndef __FACTORY__H
#define __FACTORY__H
#include "unixhead.h"
#include "queue.h"
typedef void*(*download_file_t)(void*);
typedef struct
{
    int stat_flag;
    int pthread_num;
    pthread_t* pthId_arr;
    download_file_t pthread_func;
    que_t que;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}factory_t;

int factory_init(factory_t *,int pthread_num,int que_capacity);
int factory_start(factory_t*);
int transfer_file(int sock_fd);
#endif
