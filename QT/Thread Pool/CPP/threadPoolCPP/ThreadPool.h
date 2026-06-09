#pragma once
#include "TaskQueue.h"
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>



template<typename T0>
class ThreadPool
{
public:
	// 创建线程池并且初始化
	ThreadPool(int minNum, int maxNum);

	// 销毁线程池
	~ThreadPool();

	// 给线程池添加任务
	void addTasks(callback<T0> func, T0* arg);

	// 获取线程池中工作线程数量
	int getBusyNum();
	// 获取线程池中存活线程数量
	int getAlive_num();

private:
	// 工作线程回调函数 只有静态函数（未被初始化的时候有地址，类对象只有实例化（创建对象后）才有地址
	// pthread_create只能接受 void* (*)(void*)
	// 静态函数没有this指针，不属于任何类对象，属于类
	static void* worker(void* arg);
	// 管理者线程回调函数
	static void* manager(void* arg);
	// 单个线程退出函数
	void threadExit();

private:
	// 任务队列
	TaskQueue<T0>* m_taskQueue;

	// 线程池中的线程
	pthread_t m_managerID;			// 管理者线程 唯一一个
	std::vector<pthread_t>* m_threadpoolIDs = nullptr;		// 工作者线程 存在多个 动态
	int m_minNum;						// 线程池最小线程数量
	int m_maxNum;						// 线程池最大线程数量
	int m_busyNum;					// 忙线程的个数（正在工作的线程）
	int m_exitNum;					// 需要销毁的线程数量
	int m_aliveNum;					// 存活线程数量

	// 锁和条件变量
	pthread_mutex_t m_lock;
	pthread_cond_t m_notEmpty;

	// 关闭线程池的标志位
	bool m_shutdown = false;

	// 一次创建或销毁的线程数量
	static const int NUMBER = 2;
};

// 创建线程池并初始化
template<typename T0>
ThreadPool<T0>::ThreadPool(int minNum, int maxNum)
{
	// 实例化任务队列
	m_taskQueue = new TaskQueue<T0>;
	do
	{
		// 初始化线程池
		m_minNum = minNum;
		m_maxNum = maxNum;
		m_busyNum = 0;
		m_aliveNum = minNum;
		m_exitNum = 0;

		// 根据线程的最大上限给线程数组分配内存
		m_threadpoolIDs = new std::vector<pthread_t>(maxNum);
		if (m_threadpoolIDs == nullptr)
		{
			std::cout << "new threadpool failed..." << std::endl;
			break;
		}

		// 初始化互斥锁和条件变量
		if (pthread_mutex_init(&m_lock, NULL) != 0 ||
			pthread_cond_init(&m_notEmpty, NULL) != 0)
		{
			std::cout << "init mutex or condition failed..." << std::endl;
			break;
		}

		// 创建管理者线程
		pthread_create(&m_managerID, NULL, manager, this);

		// 创建工作线程
		for (int i = 0; i < minNum; ++i)
		{
			pthread_create(&(*this->m_threadpoolIDs)[i], NULL, worker, this);
		}
		return;
	} while (0);

	// 释放资源
	if (m_taskQueue) delete m_taskQueue;
	if (m_threadpoolIDs) delete m_threadpoolIDs;
}

// 销毁线程池
template<typename T0>
ThreadPool<T0>::~ThreadPool()
{
	m_shutdown = true;
	// 阻塞回收管理者线程
	pthread_join(m_managerID, NULL);
	// 唤醒所有消费者线程
	for (int i = 0; i < m_aliveNum; ++i)
	{
		pthread_cond_signal(&m_notEmpty);
	}

	// 释放堆内存
	if (m_taskQueue) delete m_taskQueue;
	if (m_threadpoolIDs) delete m_threadpoolIDs;
	pthread_mutex_destroy(&m_lock);
	pthread_cond_destroy(&m_notEmpty);
}

// 给线程池添加任务
template<typename T0>
void ThreadPool<T0>::addTasks(callback<T0> func, T0* arg)
{
	if (m_shutdown)
	{
		return;
	}
	// 添加任务，不需要加锁，任务队列中有锁
	m_taskQueue->addTask(func, arg);
	// 唤醒工作的线程
	pthread_cond_signal(&m_notEmpty);
}

// 获取线程池中工作的线程的个数
template<typename T0>
int ThreadPool<T0>::getBusyNum()
{
	int busyNum = 0;
	pthread_mutex_lock(&m_lock);
	busyNum = m_busyNum;
	pthread_mutex_unlock(&m_lock);
	return busyNum;
}

// 获取线程池中活着的线程的个数
template<typename T0>
int ThreadPool<T0>::getAlive_num()
{
	int aliveNum = 0;
	pthread_mutex_lock(&m_lock);
	aliveNum = m_aliveNum;
	pthread_mutex_unlock(&m_lock);
	return aliveNum;
}

// 工作线程任务函数
template<typename T0>
void* ThreadPool<T0>::worker(void* arg)
{
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	while (true)
	{
		// 访问任务队列(共享资源)加锁
		pthread_mutex_lock(&pool->m_lock);
		// 判断任务队列是否为空, 如果为空工作线程阻塞
		while (pool->m_taskQueue->taskNumber() == 0 && !pool->m_shutdown)
		{
			// 阻塞工作线程
			pthread_cond_wait(&pool->m_notEmpty, &pool->m_lock);

			// 解除阻塞之后, 判断是否要销毁线程
			if (pool->m_exitNum > 0)
			{
				pool->m_exitNum--;
				if (pool->m_aliveNum > pool->m_minNum)
				{
					pool->m_aliveNum--;
					pthread_mutex_unlock(&pool->m_lock);
					pool->threadExit();
				}
			}
		}

		// 判断线程池是否被关闭了
		if (pool->m_shutdown)
		{
			pthread_mutex_unlock(&pool->m_lock);
			pool->threadExit();
		}

		// 从任务队列中取出一个任务
		Task<T0> task = pool->m_taskQueue->takeTask();
		// 工作的线程+1
		pool->m_busyNum++;
		// 线程池解锁
		pthread_mutex_unlock(&pool->m_lock);

		// 执行任务
		std::cout << "thread " << pthread_self() << " start working..." << std::endl;
		task.m_func(task.m_arg);
		task.m_arg = nullptr;

		// 任务处理结束
		std::cout << "thread " << pthread_self() << " end working..." << std::endl;
		pthread_mutex_lock(&pool->m_lock);
		pool->m_busyNum--;
		pthread_mutex_unlock(&pool->m_lock);
	}

	return nullptr;
}

// 管理者线程任务函数
template<typename T0>
void* ThreadPool<T0>::manager(void* arg)
{
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	while (!pool->m_shutdown)
	{
		// 每隔3s检测一次
		sleep(3);
		// 取出线程池中的任务数和线程数量
		// 取出工作的线程池数量
		pthread_mutex_lock(&pool->m_lock);
		int queueSize = static_cast<int>(pool->m_taskQueue->taskNumber());
		int liveNum = pool->m_aliveNum;
		int busyNum = pool->m_busyNum;
		pthread_mutex_unlock(&pool->m_lock);

		// 创建线程
		// 当前任务个数>存活的线程数 && 存活的线程数<最大线程个数
		if (queueSize > liveNum && liveNum < pool->m_maxNum)
		{
			// 线程池加锁
			pthread_mutex_lock(&pool->m_lock);
			int counter = 0;
			for (int i = 0; i < pool->m_maxNum && counter < NUMBER && pool->m_aliveNum < pool->m_maxNum; ++i)
			{
				// 如果当前线程ID为0，表示这个线程还没有被创建
				if ((*pool->m_threadpoolIDs)[i] == 0)
				{
					pthread_create(&(*pool->m_threadpoolIDs)[i], NULL, worker, pool);
					counter++;
					pool->m_aliveNum++;
				}
			}
			pthread_mutex_unlock(&pool->m_lock);
		}

		// 销毁多余的线程
		// 忙线程*2 < 存活的线程数目 && 存活的线程数 > 最小线程数量
		if (busyNum * 2 < liveNum && liveNum > pool->m_minNum)
		{
			// 线程池加锁
			pthread_mutex_lock(&pool->m_lock);
			pool->m_exitNum = NUMBER;
			pthread_mutex_unlock(&pool->m_lock);
			// 让工作的线程自杀
			for (int i = 0; i < NUMBER; ++i)
			{
				pthread_cond_signal(&pool->m_notEmpty);
			}
		}
	}
	return nullptr;
}

// 单个线程退出
template<typename T0>
void ThreadPool<T0>::threadExit()
{
	pthread_t tid = pthread_self();
	for (int i = 0; i < m_maxNum; ++i)
	{
		if ((*m_threadpoolIDs)[i] == tid)
		{
			(*m_threadpoolIDs)[i] = 0;
			std::cout << "threadExit() called, " << tid << " exiting..." << std::endl;
			break;
		}
	}
	pthread_exit(NULL);
}


