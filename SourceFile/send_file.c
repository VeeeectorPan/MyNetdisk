#include "../HeaderFile/pthread_pool.h"
#include "../HeaderFile/client.h"
int send_file(int client_fd,int file_fd)
{
    struct stat st;
    fstat(file_fd,&st);
    int ret = send(client_fd,&st,sizeof(struct stat),MSG_NOSIGNAL);
    if(ret == -1)
        return -1;
    int ctl_num = -1;
    ret = recv(client_fd,&ctl_num,sizeof(int),0);
    if(ret == 0)
        return -1;
    if(ctl_num == GETS_NOT_EXIST)
    {
        ret = recv(client_fd,&ctl_num,sizeof(int),0);
        if(ret == 0 || ctl_num == GETS_STOP_RECV)
            return -1;
        sendfile(client_fd,file_fd,NULL,st.st_size);
        recv(client_fd,&ctl_num,sizeof(int),0);
        printf("after sendfile ctl_num = %d\n",ctl_num);
    }
    if(ctl_num == GETS_EXIST)
    {

    }
    return 0;
}
