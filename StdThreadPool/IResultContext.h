#pragma once

class IResultContext
{
public:
  IResultContext() {}
  virtual ~IResultContext() {}
  virtual void Execute() = 0;
};