/******************************************************************************
* [2016] FLINT Incorporated.
* All Rights Reserved.
*/
#pragma once

#include <thread>
#include <atomic>
#include "Task.h"

namespace jturbo {

class TaskThread
{
public:
	TaskThread();
	~TaskThread();

	void SetTask(std::shared_ptr<Task> pTask);
	bool Joinable() const;
	void Join();
	void SignalWorkEvent();
	void SignalShutDownEvent();
	void SetBusy();
	bool IsBusy() const;
	std::thread::id GetId() const { return m_ThreadId; }
private:
	void ThreadFunc();
	void RunTask();
private:
	HANDLE  m_hWorkEvent[2]; // m_hWorkEvent[0] Work Event. m_hWorkEvent[1] ShutDown event
	std::thread m_Thread;
	std::atomic<bool> m_Run;
	std::atomic<bool> m_Busy;
	std::shared_ptr<Task> m_pTask;
	std::thread::id m_ThreadId;
};

} // namespace jturbo