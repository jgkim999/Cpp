#include "stdafx.h"
#include "TaskThread.h"
#include "TaskQueue.h"
#include "TaskManager.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace jturbo {

TaskThread::TaskThread(TaskManager* pTaskManager, int threadNum)
  : run_(false)
  , stop_(false)
  , taskManager_(pTaskManager)
  , threadNum_(threadNum)
{
  workEvent_[0] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
  workEvent_[1] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
  thread_ = std::thread(&TaskThread::threadFunc, this);
  threadId_ = thread_.get_id();
}

TaskThread::~TaskThread()
{
  stop();
  ::CloseHandle(workEvent_[0]);
  ::CloseHandle(workEvent_[1]);
}

void TaskThread::setTask(std::shared_ptr<Task> task)
{
  if (task)
  {
    task_ = task;
    signalWorkEvent();
  }
}

void TaskThread::signalWorkEvent()
{
  ::SetEvent(workEvent_[0]);
}

void TaskThread::signalShutDownEvent()
{
  run_ = false;
  ::SetEvent(workEvent_[1]);
}

void TaskThread::stop()
{
  signalShutDownEvent();
  if (joinable())
    join();
  while (!stop_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool TaskThread::joinable() const
{
  return thread_.joinable();
}

void TaskThread::join()
{
  thread_.join();
}

void TaskThread::threadFunc()
{
  run_ = true;
  stop_ = false;
  while (run_)
  {
    DWORD dwWaitResult = ::WaitForMultipleObjects(2, workEvent_, FALSE, INFINITE);
    switch (dwWaitResult)
    {
    case WAIT_OBJECT_0:
      runTask();
      break;
    case WAIT_OBJECT_0 + 1:
      break;
    default:
      break;
    }
  }
  stop_ = true;
}

void TaskThread::runTask()
{
  if (task_)
  {
    task_->run();
    task_.reset();
  }
  ::ResetEvent(workEvent_[0]);
  taskManager_->addFreeThread(threadNum_);
}
} // namespace jturbo