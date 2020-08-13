#pragma once

#include <future>
#include <mutex>
#include <queue>

class ITask;
class IResultContext;

class ThreadPool
{
public:
  ThreadPool(size_t num_threads);
  ~ThreadPool();
  void WorkerThread();
  std::future<std::shared_ptr<IResultContext>> EnqueueJob(std::shared_ptr<ITask> task);
private:
  size_t num_threads_;
  bool stop_all_;
  std::vector<std::thread> worker_threads_;
  std::queue<std::shared_ptr<ITask>> jobs_;
  std::condition_variable job_cv_;
  std::mutex job_mutex_;
};