#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "ThreadPool.h"

void taskFunc(int* arg)
{
    int num = *arg;
    std::cout << "thread tid: " << pthread_self() << ", num = " << num << std::endl;
    usleep(1000);
}

int main()
{
    ThreadPool<int> pool(4, 12);
    for (int i = 0; i < 10000; i++)
    {
        int* num = new int(i + rand() % 100);
        pool.addTasks(taskFunc,num);
    }

    // 等待主线程运行完
    sleep(30);
    return 0;
}