#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

void child_process_handler(int pipefd)
{
    char flag = 1; 
    int sockfd;
    trans_t tran;
    int file_fd = open(FILENAME,O_RDWR);
    tran.data_len = strlen(FILENAME);
    memcpy(tran.buf,FILENAME,tran.data_len);
    struct stat file_st;
    while(1)
    {
        lseek(file_fd,0,SEEK_SET);
        recv_fd(pipefd,&sockfd);
        printf("Download!\n");
        // send filename
        send(sockfd,&tran,tran.data_len + sizeof(int),0);
        stat(FILENAME,&file_st);
        tran.data_len = sizeof(mode_t);
        memcpy(tran.buf,&file_st.st_mode,sizeof(mode_t));
        printf("mode = %d %d.\n",file_st.st_mode,*(mode_t*)tran.buf);
        // send filetype
        send(sockfd,&tran,tran.data_len + sizeof(int),0);
        while((tran.data_len = read(file_fd,tran.buf,sizeof(tran.buf))) != 0)
        {
            printf("n bytes = %d.\n",tran.data_len);
            send(sockfd,&tran,tran.data_len + sizeof(int),0);
        }
        printf("Download completed!\n");
        write(pipefd,&flag,1);
        close(sockfd);
    }

}
