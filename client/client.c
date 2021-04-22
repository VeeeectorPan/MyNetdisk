#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/client.h"
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

    // select the file you want to download
    printf("what file do you want to download?\n");
    printf("Enter file ID:");
    show_file();

}
