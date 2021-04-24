#include "../HeaderFile/factory.h"
#include "../HeaderFile/queue.h"

void* thread_func(void*);
int factory_init(factory_t *p_fact,int pthread_num,int que_capacity)
{
    if(pthread_num < 1 || que_capacity < 1)
    {
        puts("pthread_num or que_capacity error!\n");
        return -1;
    }

    que_init(&p_fact->que,que_capacity);
    pthread_cond_init(&p_fact->cond,NULL);
    pthread_mutex_init(&p_fact->mutex,NULL);
    p_fact->pthread_num = pthread_num;
    p_fact->pthId_arr = (pthread_t*)malloc(sizeof(pthread_t) * pthread_num);
    p_fact->pthread_func = thread_func;
    p_fact->stat_flag = 0;
    return 0;
}

void* thread_func(void* p)
{
    factory_t *p_fact = (factory_t*)p;
    struct Queue_node* node = NULL;
    int client_fd = 0;
    while(1)
    {
        pthread_mutex_lock(&p_fact->mutex);
        if(p_fact->que.que_size == 0)
        {
            pthread_cond_wait(&p_fact->cond,&p_fact->mutex);
        }
        que_pop(&p_fact->que,&node);
        pthread_mutex_unlock(&p_fact->mutex);
        client_fd = node->client_fd;
        printf("client_fd = %d\n",client_fd);
        free(node);
        transfer_file(client_fd);
        close(client_fd);
    }
    pthread_exit(NULL);
}
