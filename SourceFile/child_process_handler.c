#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

void child_process_handler(int pipefd)
{
    int flag;
    int sockfd;
    int file_fd = open(FILENAME,O_RDWR);
    while(1)
    {
        lseek(file_fd,0,SEEK_SET);
        recv_fd(pipefd,&sockfd,&flag);
        if(flag == EXIT_SIG_FLAG)
        {
            printf("%dexit\n",pipefd);
            exit(0);
        }
        printf("Download!\n");
        transfer_file(sockfd,file_fd);
        printf("Download completed!\n");
        write(pipefd,&flag,1);
        close(sockfd);
    }
}
