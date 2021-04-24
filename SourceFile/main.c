#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/factory.h"
#include "../HeaderFile/tcp_link.h"
#include "../HeaderFile/epoll_operation.h"
#include "../HeaderFile/queue.h"
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,5);
    factory_t fact;
    int ret = factory_init(&fact,atoi(argv[3]),atoi(argv[4]));
    if(ret == -1)
        return -1;
    factory_start(&fact);
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    ret = bind_sfd(argv + 1,sfd);
    ERROR_CHECK(ret,-1,"bind_sfd");
    int epoll_fd = epoll_create(1);
    add_fd_to_epoll(epoll_fd,sfd,EPOLLIN);
    struct epoll_event evs[10];
    listen(sfd,10);
    while(1)
    {
        int readyNum = epoll_wait(epoll_fd,evs,10,-1);
        for(int i = 0; i < readyNum; ++i)
        {
            if(evs[i].data.fd == sfd)
            {
                int client_fd = accept(sfd,NULL,NULL);
                pthread_mutex_lock(&fact.mutex);
                que_push(&fact.que,client_fd);
                pthread_cond_signal(&fact.cond);
                pthread_mutex_unlock(&fact.mutex);
            }
        }
    }
    que_free(&fact.que);
    close(sfd);
    close(epoll_fd);
    return 0;
}
