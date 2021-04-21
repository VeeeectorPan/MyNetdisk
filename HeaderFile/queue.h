#ifndef __QUEUE__PH
#define __QUEUE__PH

typedef struct 
{
    int front;
    int back;
    int size;
    int* data;
}queue_t;

void init(queue_t* pque,int size);
int que_push(queue_t* pque, int val);
int que_pop(queue_t* pque);
int que_size(queue_t* pque);

#endif
