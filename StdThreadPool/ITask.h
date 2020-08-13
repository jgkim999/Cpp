#pragma once

#include <future>

#include "IResultContext.h"

class ITask
{
public:
  ITask() = default;
  virtual ~ITask() = default;
  virtual void Execute() = 0;
  std::future<std::shared_ptr<IResultContext>> GetFuture() { return promise_.get_future(); }
protected:
  std::promise<std::shared_ptr<IResultContext>> promise_;
};