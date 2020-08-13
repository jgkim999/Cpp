#include "ThreadPool.h"
#include "ITask.h"

ThreadPool::ThreadPool(size_t num_threads)
  : num_threads_(num_threads), stop_all_(false)
{
  worker_threads_.reserve(num_threads_);
  for (size_t i = 0; i < num_threads_; ++i)
  {
    worker_threads_.emplace_back([this]() { this->WorkerThread(); });
  }
}

ThreadPool::~ThreadPool()
{
  stop_all_ = true;
  job_cv_.notify_all();
  for (auto& t : worker_threads_)
  {
    t.join();
  }
}

void ThreadPool::WorkerThread()
{
  while (true)
  {
    std::unique_lock<std::mutex> lock(job_mutex_);
    job_cv_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all_; });
    if (stop_all_ && this->jobs_.empty())
    {
      return;
    }
    // 맨 앞의 job 을 뺀다.
    std::shared_ptr<ITask> job = std::move(jobs_.front());
    jobs_.pop();
    lock.unlock();
    // 해당 job 을 수행한다 :)
    job->Execute();
  }
}

std::future<std::shared_ptr<IResultContext>> ThreadPool::EnqueueJob(std::shared_ptr<ITask> task)
{
  if (stop_all_)
  {
    throw std::runtime_error("ThreadPool 사용 중지됨");
  }
  std::lock_guard<std::mutex> lock(job_mutex_);
  auto future = task->GetFuture();
  jobs_.push(task);
  job_cv_.notify_one();
  return future;
}