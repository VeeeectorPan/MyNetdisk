#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

int make_child_process(child_proc_t* infoArr,int proc_num)
{
    for(int i = 0; i < proc_num; ++i)
    {
        int fds[2];
        int ret = socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        if(!(infoArr[i].pid = fork()))
        {
            close(fds[0]);
            child_process_handler(fds[1]);
        }
        close(fds[1]);
        infoArr[i].isbusy = 0;
        infoArr[i].fd = fds[0];
    }
#ifdef __DEBUG
    for(int i = 0; i < proc_num; ++i)
    {
        printf("pid = %d, pipefd = %d\n",infoArr[i].pid,infoArr[i].fd);
    }
#endif
    return 0;
}
