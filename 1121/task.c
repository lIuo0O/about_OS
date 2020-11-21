#include "task.h"
struct Task* create_task(void (*task_func)(void)){
    struct Task* t = malloc(sizeof(struct Task));
    t->task_fun = task_func;
    t->create_time = time(0);
    return t;
}
struct Task_Stack* init_task_stack(int size){
    struct Task_Stack *tst = malloc(sizeof(struct Task_Stack));
    struct Task *base= malloc(sizeof(struct Task)*size);
    tst->size = size;
    tst->base = base;
    tst->top = tst->base-1;
    tst->used = 0;
    return tst;
}
int push(struct Task_Stack *tst, struct Task *t){
    while(tst->used);    
    tst->used = 1;
    if(tst->top - tst->base >= tst->size) {
        printf("stack is full, can't add a task\n");
        tst->used = 0;
        return 1;
    }
    tst->top++;
    tst->top->task_fun = t->task_fun;
    tst->top->create_time = t->create_time;
    tst->top->push_time = time(0);
    free(t);
    tst->used = 0;
    return 0;
}
struct Task* pop(struct Task_Stack *tst){
    while(tst->used);    
    tst->used = 1;
    if(tst->base > tst->top ){
        printf("stack is empty, can't pop a task\n");
        tst->used = 0;
        return NULL;
    }
    tst->used = 0;
    return tst->top--;
}

