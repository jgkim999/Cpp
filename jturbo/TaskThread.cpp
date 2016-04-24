#include "stdafx.h"
#include "TaskThread.h"
#include "TaskQueue.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace jturbo {

TaskThread::TaskThread(TaskQueue* pTaskQueue)
	: m_Run(false)
	, m_Busy(false)
	, m_Stop(false)
	, m_pTaskQueue(pTaskQueue)
{
	m_hWorkEvent[0] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hWorkEvent[1] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_Thread = std::thread(&TaskThread::ThreadFunc, this);
	m_ThreadId = m_Thread.get_id();
}

TaskThread::~TaskThread()
{
	Stop();
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

void TaskThread::Stop()
{
	SignalShutDownEvent();
	if (Joinable())
		Join();
	while (!m_Stop)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

bool TaskThread::Joinable() const
{
	return m_Thread.joinable();
}

void TaskThread::Join()
{
	m_Thread.join();
}

void TaskThread::ThreadFunc()
{
	m_Run = true;
	m_Stop = false;
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
	m_Stop = true;
}

void TaskThread::RunTask()
{
	m_Busy = true;
	std::shared_ptr<Task> pTask;
	if (m_pTaskQueue->Pop(pTask))
		pTask->Run();
	m_Busy = false;
}

} // namespace jturbo