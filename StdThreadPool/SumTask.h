#pragma once

#include "ITask.h"

class SumTask : public ITask
{
public:
  SumTask(int t, int id);
  virtual ~SumTask() = default;
  void Execute() override;
private:
  int t_;
  int id_;
};
