#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

void child_process_handler(int pipefd)
{
    char flag = 1; 
    int sockfd;
    while(1)
    {
        recv_sockfd(&sockfd);
        printf("Download!\n");
        // mission completed!
        printf("Download completed!\n");
        write(sockfd,&flag,1);
    }

}
