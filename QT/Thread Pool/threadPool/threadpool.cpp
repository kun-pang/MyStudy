#include "threadpool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int NUMBER = 2;		// 一次销毁/创建2个

// 任务结构体
//	定义到.h中，在编译成动态库后，使用者能看见；
//	定义到.c中，编译成动态库后，使用者不能看见
//	使用typedef关键字，是为了定义时少写struct Task（起别名）（c语言规定结构体定义时:struct Task Tabc;）

typedef struct Task
{
	// void* arg是一种泛型，能兼容更多的数据类型
	void (*function)(void* arg);	// 接收处理的函数
	void* arg;						// 存储接收的处理函数的需要的参数	
}Task;


// 线程结构体
struct ThreadPool
{
	// 任务队列
	Task* taskQueue;
	int queueCapacity;				// 队列容量
	int queueSize;					// 当前任务个数
	int queueFront;					// 队头 -> 取出数据
	int queueRear;					// 队尾 -> 存入数据

	// 工作与管理相关线程
	pthread_t managerID;			// 管理者线程 唯一一个
	pthread_t* threadpoolIDs;		// 工作者线程 存在多个
	int minNum;						// 工作者线程最小个数
	int maxNum;						// 工作者线程最大个数
	int busyNum;					// 忙线程的个数（正在工作的线程）
	int exitNum;					// 需要销毁的线程个数
	int liveNum;					// 存活的线程个数

	// 线程同步
	pthread_mutex_t mutexPool;		// 锁整个线程池
	pthread_mutex_t mutexBusy;		// 锁busyNum变量（exitNum与liveNum变化没有这个剧烈）
	pthread_cond_t notFull;			// 任务队列为空
	pthread_cond_t notEmpty;		// 任务队列为满

	// 线程池销毁
	int shutdown;					// 销毁线程池，1销毁，0销毁
};

// 创建线程池并且初始化
ThreadPool* threadpool_create(int queueCapacity, int minNum, int maxNum)
{
	// 初始化线程池
	ThreadPool *threadPool = (ThreadPool*)malloc(sizeof(ThreadPool));
	do
	{
		// 判断threadPool是否分配成功
		if (threadPool == NULL)
		{
			printf("malloc threadPool fail\n");
			break;
		}

		// 初始化工作的线程数组
		threadPool->threadpoolIDs = (pthread_t*)malloc(sizeof(pthread_t) * maxNum);		// 根据最大数量初始化
		if (threadPool->threadpoolIDs == NULL)
		{
			printf("malloc threadpoolIDs fail\n");
			break;
		}
		memset(threadPool->threadpoolIDs, 0, sizeof(pthread_t) * maxNum);					// 初始化分配数据，获取判断该区域是不是0，然后进行添加或者销毁
		threadPool->minNum = minNum;
		threadPool->maxNum = maxNum;
		threadPool->busyNum = 0;
		threadPool->liveNum = minNum;			// 存活线程按最小值初始化
		threadPool->exitNum = 0;

		// 初始化锁，判断初始化是否成功
		if (pthread_mutex_init(&threadPool->mutexPool, NULL) != 0 ||
			pthread_mutex_init(&threadPool->mutexBusy, NULL) != 0 ||
			pthread_cond_init(&threadPool->notFull, NULL) != 0 ||
			pthread_cond_init(&threadPool->notEmpty, NULL) != 0)
		{
			printf("mutex or cond fail\n");
			break;
		}

		// 初始化任务队列
		threadPool->taskQueue = (Task*)malloc(sizeof(Task) * queueCapacity);
		if (threadPool->taskQueue == NULL)
		{
			printf("malloc taskQueu fail\n");
			break;
		}
		threadPool->queueCapacity = queueCapacity;
		threadPool->queueSize = 0;
		threadPool->queueRear = 0;
		threadPool->queueFront = 0;

		threadPool->shutdown = 0;

		// 创建管理者和工作者线程
		pthread_create(&threadPool->managerID, NULL, manager, threadPool);
		for (int i = 0; i < minNum; i++)
		{
			pthread_create(&threadPool->threadpoolIDs[i], NULL, worker, threadPool);		// 将threadPool传入worker方便调用threadPool中的任务队列
		}

		return threadPool;
	} while (0);

	if (threadPool && threadPool->threadpoolIDs) free(threadPool->threadpoolIDs);
	if (threadPool && threadPool->taskQueue) free(threadPool->taskQueue);
	if (threadPool) free(threadPool);

	return NULL;
}

int threadpool_destroy(ThreadPool* pool)
{
	// 判断线程是否存在
	if (pool == NULL) 
	{
		return -1;
	}

	// 关闭线程池，管理者线程在循环扫描时，会判断线程池是否关闭，若关闭则自杀
	pool->shutdown = 1;
	
	// 阻塞回收的管理线程
	pthread_join(pool->managerID, NULL);

	// 唤醒阻塞的消费者线程自杀
	for (int i = 0; i < pool->liveNum; i++)
	{
		pthread_cond_signal(&pool->notEmpty);
	}

	
	// 销毁锁资源
	pthread_mutex_destroy(&pool->mutexPool);
	pthread_mutex_destroy(&pool->mutexBusy);
	pthread_cond_destroy(&pool->notEmpty);
	pthread_cond_destroy(&pool->notFull);

	// 释放堆内存
	if (pool->taskQueue)
	{
		free(pool->taskQueue);
		pool->taskQueue = NULL;
	}
	if (pool->threadpoolIDs)
	{
		free(pool->threadpoolIDs);
		pool->threadpoolIDs = NULL;
	}
	free(pool);
	pool = NULL;



	return 0;
}

void threadpool_add(ThreadPool* pool, void(*func)(void*), void* arg)
{
	// 加锁
	pthread_mutex_lock(&pool->mutexPool);
	

	// 判断线程池存在，任务队列满
	while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
	{
		// 阻塞当前生产者（生产者线程）
		pthread_cond_wait(&pool->notFull,&pool->mutexPool);
	}

	// 判断线程池是销毁
	if (pool->shutdown)
	{
		pthread_mutex_unlock(&pool->mutexPool);
		return;
	}

	// 放入任务
	pool->taskQueue[pool->queueRear].function = func;
	pool->taskQueue[pool->queueRear].arg = arg;

	// 队尾后移
	pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
	pool->queueSize++;

	// 唤醒消费者
	pthread_cond_signal(&pool->notEmpty);

	// 解锁
	pthread_mutex_unlock(&pool->mutexPool);
}

int threadpool_busy_num(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexBusy);
	int busyNum = pool->busyNum;
	pthread_mutex_unlock(&pool->mutexBusy);
	return busyNum;
}

int threadpool_live_num(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexPool);
	int liveNum = pool->liveNum;
	pthread_mutex_unlock(&pool->mutexPool);
	return liveNum;
}

void* worker(void* arg)
{
	ThreadPool* pool = (ThreadPool*) arg;
	while (1)
	{
		// 加锁
		pthread_mutex_lock(&pool->mutexPool);
		// 判断当前任务队列是否有任务  线程池存在且任务为0
		while(pool->queueSize == 0 && pool->shutdown == 0) 
		{
			// 阻塞当前消费者（工作线程），等待新的任务出现(会自动释放自身资源，资源够了在重新上锁)
			pthread_cond_wait(&pool->notEmpty,&pool->mutexPool);

			// 自杀
			if (pool->exitNum > 0)
			{
				pool->exitNum--;
				// 判断当前存活线程是否大于最小线程，保证线程至少有minNum线程
				if (pool->liveNum > pool->minNum)
				{
					pool->liveNum--;
					// 归还资源
					pthread_mutex_unlock(&pool->mutexPool);
					threadExit(pool);
				}
			}
		}
		// 判断线程池是否被关闭
		if(pool->shutdown == 1)
		{
			// 解锁,退出线程
			pthread_mutex_unlock(&pool->mutexPool);
			threadExit(pool);
		}

		// 获取任务队列中的任务
		Task task;
		// 从头部取数据
		task.function = pool->taskQueue[pool->queueFront].function;
		task.arg = pool->taskQueue[pool->queueFront].arg;

		// 移动任务队列头节点,减少当前任务个数
		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
		pool->queueSize--;		

		//唤醒生产者
		pthread_cond_signal(&pool->notFull);

		// 解锁
		pthread_mutex_unlock(&pool->mutexPool);

		// 开始工作
		// 记录忙线程
		printf("start to work , busyNum+1 , tid = %ld\n",pthread_self());
		pthread_mutex_lock(&pool->mutexBusy);
		pool->busyNum++;
		pthread_mutex_unlock(&pool->mutexBusy);


		task.function(task.arg);			// 或者 (*task.function)(task.arg);
		// 释放堆内存，传入的参数是堆内存
		free(task.arg);
		task.arg = NULL;

		// 工作完成
		// 再次记录忙线程
		printf("finish the work , busyNum-1 , tid = %ld\n",pthread_self());
		pthread_mutex_lock(&pool->mutexBusy);
		pool->busyNum--;
		pthread_mutex_unlock(&pool->mutexBusy);

	}

	return NULL;
}


void* manager(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;
	// 线程池关闭退出
	while (!pool->shutdown)
	{
		// 每隔3s进行一次检查
		sleep(3);

		// 取出线程池中的任务数量和当前存活线程数量
		pthread_mutex_lock(&pool->mutexPool);
		int queuseSize = pool->queueSize;
		int liveNum = pool->liveNum;
		// int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutexPool);

		// 取出线程池中忙线程数量（写在上面也可以）
		pthread_mutex_lock(&pool->mutexBusy);
		int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);

		// 添加线程
		// 任务个数 > 当前存活线程数据量 && 存活线程数 < 最大线程数
		if (queuseSize > liveNum && liveNum < pool->maxNum) 
		{
			// 加锁，需要对pool->liveNum进行修改
			pthread_mutex_lock(&pool->mutexPool);
			// 一次创建2个
			int count = 0;
			for (int i = 0; i < pool->maxNum && 
				pool->liveNum < pool->maxNum && 
				count < NUMBER; i++)
			{
				// 当前threadpoolIDs存储的是0，代表没有被使用
				if (pool->threadpoolIDs[i] == 0)
				{
					pthread_create(&pool->threadpoolIDs[i],NULL,worker,pool);
					count++;
					pool->liveNum++;
				}
			}
			pthread_mutex_unlock(&pool->mutexPool);
		}

		// 销毁线程
		// 忙线程 * 2 < 当前存活线程 && 当前存活线程 > 最小线程数
		if (busyNum * 2 < liveNum && liveNum > pool->minNum)
		{
			// 添加销毁线程数
			pthread_mutex_lock(&pool->mutexPool);
			pool->exitNum = NUMBER;
			pthread_mutex_unlock(&pool->mutexPool);
			// 引导存活线程自己自杀
			for (int i = 0; i < NUMBER; i++) 
			{
				// 唤醒在worker中阻塞在pthread_cond_wait的线程
				pthread_cond_signal(&pool->notEmpty);
			}
		}

	}

	return nullptr;
}

void threadExit(ThreadPool* pool)
{
	// 获取当前线程ID
	pthread_t tid = pthread_self();
	// 加锁，防止多个线程同时修改
	pthread_mutex_lock(&pool->mutexPool); 
	for (int i = 0; i < pool->maxNum; i++) 
	{
		// 找到与要退出线程ID相同的ID
		if (pthread_equal(pool->threadpoolIDs[i],tid))
		{
			pool->threadpoolIDs[i] = 0;
			printf("exit ID: %ld\n",tid);
			break;
		}
	}
	// 解锁
	pthread_mutex_unlock(&pool->mutexPool); 
	pthread_exit(NULL);	
}

