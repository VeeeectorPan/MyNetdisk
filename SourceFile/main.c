#include "../HeaderFile/unixhead.h"
#include "../HeaderFile/proc_pool.h"
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,4);
    int proc_num = atoi(argv[3]);
    child_proc_t* childInfoArr = (child_proc_t*)malloc(sizeof(child_proc_t)* proc_num);
    make_child_process(childInfoArr,proc_num);
    while(1);
    return  0;

}
