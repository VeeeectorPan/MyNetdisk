#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/proc_pool.h"

int recv_file(int sock_fd,int file_fd, int file_size)
{
    int total = 0;
    off_t download_size = 0;
    off_t last_download_size = 0;
    off_t slice_size = file_size / 10000;
    int pipefd[2];
    int ret = pipe(pipefd);
    ERROR_CHECK(ret,-1,"pipe");
    while(total < file_size)
    {
        ret = splice(sock_fd,NULL,pipefd[1],NULL,4096,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
        ret = splice(pipefd[0],NULL,file_fd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
        total += ret;
        download_size += ret;
        if(download_size - last_download_size > slice_size)
        {
            printf("%5.2f\r",(double)download_size/file_size * 100);
            fflush(stdout);
        }
    }
    printf("%-6s\n","100%");    
    return 0;
}

