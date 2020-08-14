#pragma once

#include <future>
#include <mutex>
#include <queue>

class ITask;
class IResultContext;
/// <summary>
/// https://modoocode.com/285
/// </summary>
class ThreadPool
{
public:
  /// <summary>
  /// ThreadPool 생성자.
  /// </summary>
  /// <param name="num_threads">작업 thread 갯수</param>
  ThreadPool(size_t num_threads);
  ~ThreadPool();
  void WorkerThread();
  /// <summary>
  /// 작업을 등록한다.
  /// </summary>
  /// <param name="task">등록할 작업</param>
  /// <returns>작업 결과를 받을 future</returns>
  std::future<std::shared_ptr<IResultContext>> EnqueueJob(std::shared_ptr<ITask> task);
private:
  /// <summary>
  /// 생성된 work thread 갯수.
  /// </summary>
  size_t num_threads_;
  bool stop_all_;
  std::vector<std::thread> worker_threads_;
  std::queue<std::shared_ptr<ITask>> jobs_;
  std::condition_variable job_cv_;
  std::mutex job_mutex_;
};