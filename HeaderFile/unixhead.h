#ifndef __PH__HEADER__H
#define __PH__HEADER__H
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/mman.h>
#include <libgen.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <syslog.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/time.h>
#include <sys/msg.h>
#include <sys/signal.h>
#include <sys/sem.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <pwd.h>
#include <fcntl.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define ARGS_CHECK(argc,num)\
{\
    if(argc != num)\
    {\
        fprintf(stderr,"Args error!\n");\
        return -1;\
    }\
}

#define ERROR_CHECK(ret,num,str)\
{\
    if(ret == num)\
    {\
        perror(str);\
        return -1;\
    }\
}
#define THREAD_ERROR_CHECK(ret,str)\
{\
    do\
    {\
        if(ret != 0)\
        {\
            printf("%s:%s",str,strerror(ret));\
        }\
    }while(0);  \
}

#endif
