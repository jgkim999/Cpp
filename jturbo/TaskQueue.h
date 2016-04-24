/******************************************************************************
* [2016] FLINT Incorporated.
* All Rights Reserved.
*/
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

	void Push(std::shared_ptr<Task> pTask)
	{
		if (pTask)
			m_Queue.push(pTask);
	}

	bool Pop(std::shared_ptr<Task>& pTask)
	{
		return m_Queue.try_pop(pTask);
	}

	bool Empty() const
	{
		return m_Queue.empty();
	}

	size_t Size() const
	{
		return m_Queue.unsafe_size();
	}
private:
	tbb::concurrent_queue<std::shared_ptr<Task>> m_Queue;
};

} // namespace jturbo