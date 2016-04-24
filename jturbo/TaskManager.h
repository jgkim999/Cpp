#pragma once

#include <thread>
#include <atomic>
#include <vector>

namespace jturbo {

class TaskThread;
class TaskQueue;
class Task;

class TaskManager
{
public:
	TaskManager(unsigned int threadNum);
	~TaskManager();

	void Push(std::shared_ptr<Task> pTask);
	size_t RemainSize() const;
private:
	void Stop();
	void ThreadProc();
	std::shared_ptr<TaskThread> GetFreeThread() const;
private:
	TaskQueue* m_pQueue;
	std::thread m_Thread;
	std::atomic<bool> m_Run;
	std::atomic<bool> m_Stop;
	std::vector<std::shared_ptr<TaskThread>> m_TaskThread;
};

} // namespace jturbo