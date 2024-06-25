#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads_num)
{
	threads.reserve(threads_num);

	for(size_t i = 0; i < threads_num; i++)
	{
		threads.emplace_back(&ThreadPool::thread_run, this);
	}
}

template<class Func, class ...Args>
void ThreadPool::add_task(const Func& task_func, Args&&... args)
{
	std::unique_lock lock(task_mutex);
	tasks_queue.emplace(std::async(task_func, args...));
	task_condition.notify_one();
}

void ThreadPool::add_table_task(CustomerServiceTable& table, const Customer& customer)
{
	std::unique_lock lock(task_mutex);
	tasks_queue.push(std::async(std::launch::async, &CustomerServiceTable::work, std::ref(table), customer));
	//tasks_queue.push(std::async(std::launch::async, [&table, &customer]() { table.work(customer); }));
	task_condition.notify_one();
}


void ThreadPool::thread_run()
{
	while(running)
	{
		std::unique_lock lock(task_mutex);
		task_condition.wait_for(lock, std::chrono::milliseconds(500));
		while(!tasks_queue.empty())
		{
			Task task = std::move(tasks_queue.front());
			tasks_queue.pop();
			lock.unlock();
			task.get();
			lock.lock();
		}
	}
}

ThreadPool::~ThreadPool()
{
	running = false;
	task_condition.notify_all();

	for(auto& thread: threads)
	{
		thread.join();
	}
}
