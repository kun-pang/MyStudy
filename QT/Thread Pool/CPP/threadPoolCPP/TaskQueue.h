#pragma once
#include <queue>
#include <pthread.h>

// 使用模板优化传入参数
// 使用using简化函数指针
template<typename T>
using callback = void(*)(T* arg);

// 任务结构体
template<typename T>
struct Task
{
	Task()
	{
		m_func = nullptr;
		m_arg = nullptr;
	}
	Task(callback<T> func, T* arg)
	{
		m_func = func;
		m_arg = arg;
	}
	callback<T> m_func;
	T* m_arg;
};

// 任务队列
template<typename T>
class TaskQueue
{
public:
	TaskQueue();
	~TaskQueue();

	// 添加任务
	void addTask(callback<T> func, T* arg);
	void addTask(Task<T>& task);

	// 取出一个任务
	Task<T> takeTask();

	// 获取当前任务的个数
	size_t taskNumber();

private:
	// 任务队列
	std::queue<Task<T>> m_taskQ;
	// 互斥锁
	pthread_mutex_t m_mutex;
};

template<typename T>
TaskQueue<T>::TaskQueue()
{
	pthread_mutex_init(&m_mutex, NULL);
}

template<typename T>
TaskQueue<T>::~TaskQueue()
{
	pthread_mutex_destroy(&m_mutex);
}

template<typename T>
void TaskQueue<T>::addTask(callback<T> func, T* arg)
{
	pthread_mutex_lock(&m_mutex);
	Task<T> task(func, arg);
	m_taskQ.push(task);
	pthread_mutex_unlock(&m_mutex);
}

template<typename T>
void TaskQueue<T>::addTask(Task<T>& task)
{
	pthread_mutex_lock(&m_mutex);
	m_taskQ.push(task);
	pthread_mutex_unlock(&m_mutex);
}

template<typename T>
Task<T> TaskQueue<T>::takeTask()
{
	Task<T> t;
	pthread_mutex_lock(&m_mutex);
	if (m_taskQ.size() > 0)
	{
		t = m_taskQ.front();
		m_taskQ.pop();
	}
	pthread_mutex_unlock(&m_mutex);
	return t;
}

template<typename T>
size_t TaskQueue<T>::taskNumber()
{
	size_t num = 0;
	pthread_mutex_lock(&m_mutex);
	num = m_taskQ.size();
	pthread_mutex_unlock(&m_mutex);
	return num;
}
