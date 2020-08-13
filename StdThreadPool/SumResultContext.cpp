#include "SumResultContext.h"
#include <cstdio>
#include <thread>

void SumResultContext::Execute()
{
  printf("SumResultContext. thread id:%x result:%d \n", std::this_thread::get_id(), result_);
}