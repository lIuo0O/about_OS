#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Task{
    void (*task_fun)(void);
    long create_time;
    long push_time;
};
struct Task_Stack{
    int size;
    int used;
    struct Task *base;
    struct Task *top;
};
struct Task* create_task(void (*task_func)(void));
struct Task_Stack* init_task_stack(int size);
int push(struct Task_Stack *tst, struct Task *t);
struct Task* pop(struct Task_Stack *tst);

