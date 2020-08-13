#include "SumTask.h"
#include "SumResultContext.h"

SumTask::SumTask(int t, int id)
  : t_(t), id_(id)
{
}

void SumTask::Execute()
{
  printf("Start task at thread:%x id:%d \n", std::this_thread::get_id(), id_);
  std::this_thread::sleep_for(std::chrono::seconds(t_));
  printf("End task at thread:%x id:%d t:%ds\n", std::this_thread::get_id(), id_, t_);
  const auto result = std::make_shared<SumResultContext>(t_ + id_);
  promise_.set_value(result);
}