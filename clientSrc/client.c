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
    recv_n_bytes(sfd,&recv_len,sizeof(int));
    char* name = (char*)malloc(recv_len + 1);
    memset(name,0,recv_len + 1);
    recv_n_bytes(sfd,buf,recv_len);
    memcpy(name,buf,recv_len);
    printf("file name = %s\n",name);
    // file type
    recv_n_bytes(sfd,&recv_len,sizeof(int));
    recv_n_bytes(sfd,buf,recv_len);
    mode_t mode = *(mode_t*)buf;
    printf("mode = %o\n",*(mode_t*)buf);
    int fd = open(name,O_RDWR|O_CREAT|O_EXCL,mode);
    ERROR_CHECK(fd,-1,"open");
    free(name);
    name = NULL;
    // file size
    recv_n_bytes(sfd,&recv_len,sizeof(int));
    recv_n_bytes(sfd,buf,recv_len);
    off_t file_size = *(off_t*)buf;
    printf("total size = %ld.\n",file_size);
    off_t download_size = 0;
    off_t last_download_size = 0;
    off_t slice_size = file_size / 10000;
    while(1)
    {
        recv_len = 0;
        recv_n_bytes(sfd,&recv_len,sizeof(int));
        if(recv_len == 0)
        {
            printf("%5.2f%%\n",100.00);
            break;
        }
        recv_n_bytes(sfd,buf,recv_len);
        write(fd,buf,recv_len);
        download_size += recv_len;
        if(download_size - last_download_size >= slice_size)
        {
            printf("%5.2f%%\r",(double)(download_size - last_download_size)/file_size);
            last_download_size = download_size;
        }
    }
    close(fd);
    close(sfd);
}
