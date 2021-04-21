#include "../HeaderFile/queue.h"
#include "../HeaderFile/unixhead.h"

void init(queue_t* pque,int size)
{
    pque->data = (int*)malloc(sizeof(int)*(size + 1));
    pque->front = 0;
    pque->back = 0;
    pque->size = size;
}

int que_push(queue_t* pque, int val)
{
    if(que_size(pque) == pque->size)
        return -1;
    pque->data[pque->back] = val;
    pque->back = (pque->back + 1) % (pque->size + 1);
    return 0;
}

int que_pop(queue_t* pque)
{
    if(pque->front == pque->back)
        return -1;
    int ret = pque->data[pque->front];
    pque->front = (pque->front + 1) % (pque->size + 1);
    return ret;
}

int que_size(queue_t* pque)
{
    return  (pque->back >= pque->front)? pque->back - pque->front: pque->size + 1 - (pque->front - pque->back);
}
