#include "../HeaderFile/unixhead.h"

int recv_fd(int pipefd,int* fd,int *flag)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    struct iovec iov[1];
    int flag_buf = 0;
    iov[0].iov_base = &flag_buf;
    iov[0].iov_len = 4;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    struct cmsghdr * cmsg;
    int cmsg_len = CMSG_LEN(sizeof(int));
    cmsg = (struct cmsghdr *)calloc(1,cmsg_len);
    cmsg->cmsg_len = cmsg_len;
    cmsg->cmsg_type = SOL_SOCKET;
    cmsg->cmsg_level = SCM_RIGHTS;
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg_len;
    int ret = recvmsg(pipefd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd = *(int*)CMSG_DATA(cmsg);
    *flag = *(int*)iov[0].iov_base;
    return 0;
}

