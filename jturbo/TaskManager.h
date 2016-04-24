/******************************************************************************
* [2016] FLINT Incorporated.
* All Rights Reserved.
*/
#pragma once

#include "TaskQueue.h"
#include <thread>
#include <atomic>
#include <vector>

namespace jturbo {

class TaskThread;

class TaskManager
{
public:
	TaskManager(unsigned int threadNum);
	~TaskManager();

	void Push(std::shared_ptr<Task> pTask);
	bool Pop(std::shared_ptr<Task>& pTask);
	size_t RemainSize() const;
private:
	void ThreadProc();
	std::shared_ptr<TaskThread> GetFreeThread() const;
private:
	TaskQueue m_Queue;
	std::thread m_Thread;
	std::atomic<bool> m_Run;
	std::vector<std::shared_ptr<TaskThread>> m_TaskThread;
};

} // namespace jturbo