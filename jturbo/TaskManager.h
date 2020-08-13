#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <tbb/concurrent_queue.h>

namespace jturbo {

class TaskThread;
class TaskQueue;
class Task;

class TaskManager
{
public:
  TaskManager(unsigned int threadNum);
  ~TaskManager();

  void push(std::shared_ptr<Task> pTask);
  size_t remainSize() const;
  void addFreeThread(int threadNum);
private:
  void stop();
  void threadProc();
  TaskThread* freeThread();
private:
  TaskQueue* taskQueue_;
  std::thread thread_;
  std::atomic<bool> run_;
  std::atomic<bool> stop_;
  std::vector<TaskThread*> taskThread_;
  tbb::concurrent_queue<int> waitThread_;
};
} // namespace jturbo