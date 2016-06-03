#pragma once

#include <tbb/concurrent_queue.h>
#include <memory>
#include "Task.h"

namespace jturbo {

/// Thread-safe. lock-free queue.
class TaskQueue
{
public:
	TaskQueue() {}
	~TaskQueue() {}

	void push(std::shared_ptr<Task> pTask)
	{
		if (pTask)
			queue_.push(pTask);
	}

	bool pop(std::shared_ptr<Task>& pTask)
	{
		return queue_.try_pop(pTask);
	}

	bool empty() const
	{
		return queue_.empty();
	}

	size_t size() const
	{
		return queue_.unsafe_size();
	}
private:
	tbb::concurrent_queue<std::shared_ptr<Task>> queue_;
};

} // namespace jturbo