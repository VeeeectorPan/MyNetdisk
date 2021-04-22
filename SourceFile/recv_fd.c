#include "../HeaderFile/unixhead.h"

int recv_fd(int pipefd,int* fd)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    struct iovec iov[1];
    char buf[10] = "hello";
    iov[0].iov_base = buf;
    iov[0].iov_len = 5;
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
    return 0;
}

