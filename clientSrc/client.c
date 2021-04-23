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
    ret = recv_n_bytes(sfd,&recv_len,sizeof(int));
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    char* name = (char*)malloc(recv_len + 1);
    memset(name,0,recv_len + 1);
    ret = recv_n_bytes(sfd,buf,recv_len);
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    memcpy(name,buf,recv_len);
    printf("file name = %s\n",name);
    // file type
    ret = recv_n_bytes(sfd,&recv_len,sizeof(int));
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    ret = recv_n_bytes(sfd,buf,recv_len);
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    mode_t mode = *(mode_t*)buf;
    printf("mode = %o\n",*(mode_t*)buf);
    int fd = open(name,O_RDWR|O_CREAT|O_EXCL,mode);
    ERROR_CHECK(fd,-1,"open");
    free(name);
    name = NULL;
    // file size
    ret = recv_n_bytes(sfd,&recv_len,sizeof(int));
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    ret = recv_n_bytes(sfd,buf,recv_len);
    ERROR_CHECK(ret,-1,"server disconnected!\n");
    off_t file_size = *(off_t*)buf;
    printf("total size = %ld.\n",file_size);

    // recv file
    time_t beg = time(NULL);
    ret = recv_file(sfd,fd,file_size);
    ERROR_CHECK(ret,-1,"recv_file");
    time_t end = time(NULL);
    printf("total time = %ld\n",end - beg);

    close(fd);
    close(sfd);
}
