#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "task.h"
void produce(struct Task_Stack *tst);
void consume(struct Task_Stack *tst);
void task1(void);
void task2(void);

int main(void){
    int v = 0;
    int f = 0;
    printf("start work\n");
    struct Task_Stack *tst = init_task_stack(100);    
    pthread_t t1, t2;
    void *retval;
    pthread_create(&t1, NULL, (void*)&produce, (void*)tst);
    pthread_create(&t2, NULL, (void*)&consume, (void*)tst);
    pthread_join(t1, &retval);
    pthread_join(t2, &retval);
    getchar();
    return 0;
}
// create a thread random create task ;
// pthread_create(&t1, NULL, (void*)&create_task, (void*)func);
void produce(struct Task_Stack *tst){
    void (*func)(void);
    while(1){
        int v = rand()%3;
        if(v%2){
            func = task2;
        }else{
            func = task1;
        }
        struct Task *t = create_task(func);
        sleep(1);
        push(tst, t);
        int size = tst->top - tst->base;
        printf("task_stack's size=%d\n", size);
        if(size > 10){
            sleep(30);
        }
    }
}
// create a thread run task;
// pthread_create
void consume(struct Task_Stack *tst){
    while(1){
        struct Task *t = pop(tst);
        if(t==NULL){
            printf("task stack empty\n");
            sleep(4);
        }else{
            printf("task create at:%ld, push at:%ld\n", t->create_time, t->push_time);
            (*t->task_fun)();
            printf("task end at:%ld\n", time(0));
        }
    }
}
void task1(void){
    printf("task1 start\n");
    sleep(0);
    printf("task1 end\n");
}
void task2(void){
    printf("task2 start\n");
    sleep(2);
    printf("task2 end\n");
}
