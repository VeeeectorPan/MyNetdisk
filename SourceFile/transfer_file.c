#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

int transfer_file(int sock_fd,int file_fd)
{
    trans_t tran;
    struct stat file_st;
    fstat(file_fd,&file_st);

    // send file name
    tran.data_len = strlen(FILENAME);
    strcpy(tran.buf,FILENAME);
    int ret = send(sock_fd,&tran,tran.data_len + sizeof(int),MSG_NOSIGNAL);
    ERROR_CHECK(ret,-1,"send");

    // send file mode
    tran.data_len = sizeof(mode_t);
    memcpy(tran.buf,&file_st.st_mode,sizeof(mode_t));
    ret = send(sock_fd,&tran,tran.data_len + sizeof(int),MSG_NOSIGNAL);
    ERROR_CHECK(ret,-1,"send");

    // send file size
    tran.data_len = sizeof(off_t);
    memcpy(tran.buf,&file_st.st_size,sizeof(off_t));
    ret = send(sock_fd,&tran,tran.data_len + sizeof(int),MSG_NOSIGNAL);
    ERROR_CHECK(ret,-1,"send");

    ret = sendfile(sock_fd,file_fd,NULL,file_st.st_size);
    ERROR_CHECK(ret,-1,"sendfile");
    return 0;
}
