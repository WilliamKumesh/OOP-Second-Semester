#pragma once
#include <queue>
#include <vector>
#include <mutex>
#include <future>
#include "CustomerServiceTable.h"
#include "Customer.h"
#include "CustomerProvider.h"

class ThreadPool
{
	using Task = std::future<void>;

	std::queue<Task> tasks_queue;
	std::vector<std::jthread> threads;

	std::mutex task_mutex;
	std::condition_variable task_condition;
	std::atomic<bool> running{ true };

	inline static size_t max_threads = 7;
	void thread_run();
public:
	explicit ThreadPool(size_t threads_num = max_threads);

	template<class Func, class ...Args>
	void add_task(const Func& task_func, Args&&... args);

	void add_table_task(CustomerServiceTable& table,const Customer& customer);

	~ThreadPool();
};