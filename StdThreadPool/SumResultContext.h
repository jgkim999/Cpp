#pragma once

#include "IResultContext.h"

class SumResultContext : public IResultContext
{
public:
  SumResultContext(int result)
    : result_(result)
  {
  }
  virtual ~SumResultContext() = default;
  void Execute() override;
private:
  int result_;
};