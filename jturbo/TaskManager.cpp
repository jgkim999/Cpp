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
	: m_Run(false)
	, m_Stop(false)
	, m_pQueue(new TaskQueue)
{
	m_Thread = std::thread(&TaskManager::ThreadProc, this);
	for (unsigned int i = 0; i < threadNum; ++i)
	{
		std::shared_ptr<TaskThread> pTaskThread(std::make_shared<TaskThread>(m_pQueue));
		m_TaskThread.emplace_back(pTaskThread);
	}
}

TaskManager::~TaskManager()
{
	Stop();
	for (auto& iter : m_TaskThread)
		iter->Stop();
	delete m_pQueue;
}

void TaskManager::Stop()
{
	m_Run = false;
	if (m_Thread.joinable())
		m_Thread.join();
	while (!m_Stop)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void TaskManager::Push(std::shared_ptr<Task> pTask)
{
	m_pQueue->Push(pTask);
}

void TaskManager::ThreadProc()
{
	m_Stop = false;
	m_Run = true;
	while (m_Run)
	{
		if (m_pQueue->Empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		std::shared_ptr<TaskThread> pTaskThead = GetFreeThread();
		if (pTaskThead)
			pTaskThead->SignalWorkEvent();
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	m_Stop = true;
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
	return m_pQueue->Size();
}

} // namespace jturbo