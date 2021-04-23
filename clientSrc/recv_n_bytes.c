#include "../HeaderFile/proc_pool.h"
#include "../HeaderFile/unixhead.h"

int recv_n_bytes(int fd,void* buf,int len)
{
    int total = 0;
    int ret;
    while(total < len)
    {
        ret = recv(fd,buf + total,len - total,0);
        if(ret == 0)
            break;
        total += ret;
    }
    return 0;
}
