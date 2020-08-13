#include <iostream>
#include "ThreadPool.h"
#include "SumTask.h"

int main()
{
  printf("Main thread id:%x \n", std::this_thread::get_id());

  ThreadPool pool(8);
  std::vector<std::future<std::shared_ptr<IResultContext>>> futures;
  for (int i = 0; i < 10; ++i)
  {
    std::shared_ptr<ITask> task = std::make_shared<SumTask>(i % 3 + 1, i);
    futures.emplace_back(pool.EnqueueJob(task));
  }
  for (auto& f : futures)
  {
    f.get()->Execute();
  }
  return 0;
}