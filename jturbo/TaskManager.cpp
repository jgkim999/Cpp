/******************************************************************************
* [2016] FLINT Incorporated.
* All Rights Reserved.
*/
#include "stdafx.h"
#include "TaskManager.h"
#include "TaskThread.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace jturbo {

TaskManager::TaskManager(unsigned int threadNum)
	: m_Run(false)
{
	m_Thread = std::thread(&TaskManager::ThreadProc, this);
	for (unsigned int i = 0; i < threadNum; ++i)
	{
		std::shared_ptr<TaskThread> pTaskThread(std::make_shared<TaskThread>());
		m_TaskThread.emplace_back(pTaskThread);
	}
}

TaskManager::~TaskManager()
{
	m_Run = false;
	if (m_Thread.joinable())
		m_Thread.join();
	for (auto& iter : m_TaskThread)
	{
		iter->SignalShutDownEvent();
		if (iter->Joinable())
			iter->Join();
	}
}

void TaskManager::Push(std::shared_ptr<Task> pTask)
{
	m_Queue.Push(pTask);
}

bool TaskManager::Pop(std::shared_ptr<Task>& pTask)
{
	return m_Queue.Pop(pTask);
}

void TaskManager::ThreadProc()
{
	m_Run = true;
	while (m_Run)
	{
		if (m_Queue.Empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		std::shared_ptr<TaskThread> pTaskThead = GetFreeThread();
		if (pTaskThead)
		{
			std::shared_ptr<Task> pTask;
			if (m_Queue.Pop(pTask))
			{
				pTaskThead->SetTask(pTask);
				pTaskThead->SetBusy();
				pTaskThead->SignalWorkEvent();
			}
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	std::cout << "TaskManager stopped." << std::endl;
}

std::shared_ptr<TaskThread> TaskManager::GetFreeThread() const
{
	for (auto& iter : m_TaskThread)
	{
		if (!iter->IsBusy())
			return iter;
	}
	return nullptr;
}

size_t TaskManager::RemainSize() const
{
	return m_Queue.Size();
}

} // namespace jturbo