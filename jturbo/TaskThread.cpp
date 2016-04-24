/******************************************************************************
* [2016] FLINT Incorporated.
* All Rights Reserved.
*/
#include "stdafx.h"
#include "TaskThread.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace jturbo {

TaskThread::TaskThread()
	: m_Run(false)
	, m_Busy(false)
{
	m_hWorkEvent[0] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hWorkEvent[1] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_Thread = std::thread(&TaskThread::ThreadFunc, this);
	m_ThreadId = m_Thread.get_id();
}

TaskThread::~TaskThread()
{
	::CloseHandle(m_hWorkEvent[0]);
	::CloseHandle(m_hWorkEvent[1]);
}

void TaskThread::SignalWorkEvent()
{
	::SetEvent(m_hWorkEvent[0]);
}

void TaskThread::SignalShutDownEvent()
{
	m_Run = false;
	::SetEvent(m_hWorkEvent[1]);
}

bool TaskThread::IsBusy() const
{
	return m_Busy;
}

void TaskThread::SetTask(std::shared_ptr<Task> pTask)
{
	m_pTask = pTask;
}

bool TaskThread::Joinable() const
{
	return m_Thread.joinable();
}

void TaskThread::Join()
{
	m_Thread.join();
}

void TaskThread::SetBusy()
{
	m_Busy = true;
}

void TaskThread::ThreadFunc()
{
	m_Run = true;
	while (m_Run)
	{
		DWORD dwWaitResult = ::WaitForMultipleObjects(2, m_hWorkEvent, FALSE, INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			RunTask();
			break;
		case WAIT_OBJECT_0 + 1:
			break;
		default:
			break;
		}
	}
	std::cout << "TaskThread stopped." << m_ThreadId << std::endl;
}

void TaskThread::RunTask()
{
	if (m_pTask)
	{
		m_pTask->Run();
		m_pTask.reset();
	}
	m_Busy = false;
}

} // namespace jturbo