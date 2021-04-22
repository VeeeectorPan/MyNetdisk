#include "../HeaderFile/unixhead.h"
int send_fd(int pipefd,int fd)
{
    struct msghdr msg;
    memset(&msg,0,sizeof(msg));
    struct iovec iov[1];
    char buf[10] = "hello";
    iov[0].iov_base = buf;
    iov[0].iov_len = 5;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    struct cmsghdr* cmsg;
    int cmsglen = CMSG_LEN(sizeof(int));
    cmsg= (struct cmsghdr *)malloc(cmsglen);
    cmsg->cmsg_len = cmsglen;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(cmsg) = fd;
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsglen;
    int ret;
    ret = sendmsg(pipefd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
