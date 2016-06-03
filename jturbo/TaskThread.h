#pragma once

#include <thread>
#include <atomic>

namespace jturbo {

class Task;
class TaskManager;

class TaskThread
{
public:
	TaskThread(TaskManager* pTaskManager, int threadNum);
	~TaskThread();

	void stop();
	void setTask(std::shared_ptr<Task> task);
	std::thread::id id() const { return threadId_; }
	int threadNum() const { return threadNum_; }
private:
	void signalWorkEvent();
	void threadFunc();
	void runTask();
	bool joinable() const;
	void join();
	void signalShutDownEvent();
private:
	HANDLE  workEvent_[2]; // m_hWorkEvent[0] Work Event. m_hWorkEvent[1] ShutDown event
	std::thread thread_;
	std::atomic<bool> run_;
	std::atomic<bool> stop_;
	std::thread::id threadId_;
	TaskManager* taskManager_;
	int threadNum_;
	std::shared_ptr<Task> task_;
};

} // namespace jturbo