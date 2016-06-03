#include "stdafx.h"
#include "TaskManager.h"
#include "TaskThread.h"
#include "TaskQueue.h"
#include "Task.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace jturbo {

TaskManager::TaskManager(unsigned int threadNum)
	: run_(false)
	, stop_(false)
	, taskQueue_(new TaskQueue)
{
	thread_ = std::thread(&TaskManager::threadProc, this);
	for (unsigned int i = 0; i < threadNum; ++i)
	{
		TaskThread* pTaskThread = new TaskThread(this, i);
		taskThread_.emplace_back(pTaskThread);
		waitThread_.push(i);
	}
}

TaskManager::~TaskManager()
{
	stop();
	for (auto& iter : taskThread_)
	{
		iter->stop();
		delete(iter);
	}
	delete taskQueue_;
}

void TaskManager::stop()
{
	run_ = false;
	if (thread_.joinable())
		thread_.join();
	while (!stop_)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void TaskManager::addFreeThread(int threadNum)
{
	waitThread_.push(threadNum);
}

void TaskManager::push(std::shared_ptr<Task> pTask)
{
	taskQueue_->push(pTask);
}

void TaskManager::threadProc()
{
	stop_ = false;
	run_ = true;
	while (run_)
	{
		if (taskQueue_->empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		TaskThread* pTaskThead = freeThread();
		if (pTaskThead)
		{
			std::shared_ptr<Task> pTask;
			if (taskQueue_->pop(pTask))
			{
				pTaskThead->setTask(pTask);
				//pTaskThead->SignalWorkEvent();
			}
			else
			{
				waitThread_.push(pTaskThead->threadNum());
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	stop_ = true;
	std::cout << "TaskManager stopped." << std::endl;
}

TaskThread* TaskManager::freeThread()
{
	if (waitThread_.empty())
		return nullptr;
	int threadNum = 0;
	if (waitThread_.try_pop(threadNum))
	{
		return taskThread_[threadNum];
	}
	else
	{
		return nullptr;
	}
}

size_t TaskManager::remainSize() const
{
	return taskQueue_->size();
}

} // namespace jturbo