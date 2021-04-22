#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/proc_pool.h"
int main(int argc,char* argv[])
{
    // link to server
    ARGS_CHECK(argc,3);
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_family = AF_INET;
    int ret = connect(sfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    ERROR_CHECK(ret,-1,"connect");

    char buf[4096];
    int recv_len;
    // file name
    recv(sfd,&recv_len,sizeof(int),0);
    char* name = (char*)malloc(recv_len + 1);
    memset(name,0,recv_len + 1);
    recv(sfd,buf,recv_len,0);
    memcpy(name,buf,recv_len);
    printf("file name = %s\n",name);
    // file type
    recv(sfd,&recv_len,sizeof(int),0);
    recv(sfd,buf,recv_len,0);
    mode_t mode = *(mode_t*)buf;
    printf("mode = %d\n",*(mode_t*)buf);
    int fd = open(name,O_RDWR|O_CREAT|O_EXCL,mode);
    ERROR_CHECK(fd,-1,"open");
    free(name);
    name = NULL;

    while(1)
    {
        recv(sfd,&recv_len,sizeof(int),0);
        if(recv_len == 0)
            break;
        recv(sfd,buf,recv_len,0);
        write(fd,buf,recv_len);
    }
    close(fd);
    close(sfd);
}
