#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.h"

void taskFunc(void *arg) 
{
    // 强转解引用
    int num = *(int*)arg;
    printf("thread tid: %ld , num = %d\n",pthread_self(),num);
    usleep(1000);
}

int main()
{
    ThreadPool* pool = threadpool_create(500,4,12);
    for(int i =0 ;i < 10000; i++)
    {
        int *num = (int*)malloc(sizeof(int));
		*num = i + rand() % 100;
        threadpool_add(pool,taskFunc,num);
    }

    // 等待主线程运行完
    sleep(30);

    // 销毁线程池
    threadpool_destroy(pool);


    return 0;
}