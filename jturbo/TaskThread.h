#pragma once

#include <thread>
#include <atomic>

namespace jturbo {

class TaskQueue;

class TaskThread
{
public:
	TaskThread(TaskQueue* pTaskQueue);
	~TaskThread();

	void SignalWorkEvent();
	bool IsBusy() const;
	void Stop();
	std::thread::id GetId() const { return m_ThreadId; }
private:
	void ThreadFunc();
	void RunTask();
	bool Joinable() const;
	void Join();
	void SignalShutDownEvent();
private:
	HANDLE  m_hWorkEvent[2]; // m_hWorkEvent[0] Work Event. m_hWorkEvent[1] ShutDown event
	std::thread m_Thread;
	std::atomic<bool> m_Run;
	std::atomic<bool> m_Busy;
	std::atomic<bool> m_Stop;
	std::thread::id m_ThreadId;
	TaskQueue* m_pTaskQueue;
};

} // namespace jturbo