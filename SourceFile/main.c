#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/tcp_link.h"
#include "../HeaderFile/epoll_operation.h"
#include "../HeaderFile/queue.h"
int exit_pipe[2];
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,4);
    int proc_num = atoi(argv[3]);
    if(proc_num < 0)
    {
        printf("proc_num error!\n");
        return -1;
    }
    child_proc_t* childInfoArr = (child_proc_t*)malloc(sizeof(child_proc_t)* proc_num);
    make_child_process(childInfoArr,proc_num);
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    int ret = bind_sfd(argv + 1,sfd); 
    ERROR_CHECK(ret,-1,"bind_sfd");

    ret = pipe(exit_pipe);
    ERROR_CHECK(ret,-1,"pipe");
    signal(SIGUSR1,exit_signal_handler);
    // epoll listen fd
    int epoll_fd = epoll_create(1);
    for(int i = 0; i < proc_num; ++i)
    {
        add_fd_to_epoll(epoll_fd,childInfoArr[i].fd,EPOLLIN);
    }
    add_fd_to_epoll(epoll_fd,sfd,EPOLLIN);
    add_fd_to_epoll(epoll_fd,exit_pipe[0],EPOLLIN);
    int listen_num = proc_num + 2;
    struct epoll_event* evs = (struct epoll_event*)malloc(sizeof(struct epoll_event)*listen_num);
    queue_t client_que,spare_que;
    init(&client_que,proc_num);
    init(&spare_que,proc_num);
    for(int i = 0; i < proc_num; ++i)
    {
        que_push(&spare_que,childInfoArr[i].fd);
    }
    listen(sfd,10);
    while(1)
    {
        int readyNum = epoll_wait(epoll_fd,evs,listen_num,-1);
        for(int i = 0; i < readyNum; ++i)
        {
            if(evs[i].data.fd == exit_pipe[0])
            {
                // shut down all process fd and sfd
                close(sfd);
                for(int i = 0; i < proc_num; ++i)
                {
                    send_fd(childInfoArr[i].fd,0,EXIT_SIG_FLAG);
                }
                for(int i = 0; i < proc_num; ++i)
                {
                    wait(NULL);
                }
                printf("server exit!\n");
                exit(0);
            }
            else if(evs[i].data.fd == sfd)
            {
                int client_fd = accept(sfd,NULL,NULL);
                if(que_size(&spare_que) > 0)
                {
                    int child_fd = que_pop(&spare_que);
                    send_fd(child_fd,client_fd,0);
                    close(client_fd);
                }
                else 
                {
                    ret = que_push(&client_que,client_fd);
                    if(ret == -1)
                    {
                        close(client_fd);
                        perror("server full!\n");
                    }
                }
            }
            else
            {
                // there are clients waitting
                int child_fd = evs[i].data.fd;
                char flag;
                read(child_fd,&flag,1);
                if(que_size(&client_que) > 0)
                {
                    int client_fd = que_pop(&client_que);
                    send_fd(child_fd,client_fd,0);
                    close(client_fd);
                }
                else
                {
                    que_push(&spare_que,child_fd);
                }
            }
        }
    }
    return  0;

}
void exit_signal_handler(int signum)
{
    signum = EXIT_SIG_FLAG;
    write(exit_pipe[1],&signum,sizeof(EXIT_SIG_FLAG));
}
