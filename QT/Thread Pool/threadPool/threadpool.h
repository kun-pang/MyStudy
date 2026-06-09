#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

typedef struct ThreadPool ThreadPool;
// 创建线程池并且初始化
ThreadPool* threadpool_create(int queueCapacity,int minNum, int maxNum);

// 销毁线程池
int threadpool_destroy(ThreadPool *pool);

// 给线程池添加任务
void threadpool_add(ThreadPool *pool, void (*func)(void *),void* arg);

// 获取线程池中工作线程个数
int threadpool_busy_num(ThreadPool *pool);
// 获取线程池中存活线程个数
int threadpool_live_num(ThreadPool *pool);


// 工作回调函数
void* worker(void *arg);
// 管理回调函数
void* manager(void * arg);
// 退出线程函数
void threadExit(ThreadPool *pool);

#endif // __THREADPOOL_H__