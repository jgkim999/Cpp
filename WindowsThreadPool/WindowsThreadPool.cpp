// WindowsThreadPool.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WindowsThreadPool.h"
#include "../jturbo/Task.h"
#include "../jturbo/TaskManager.h"
#include "../jturbo/StopWatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

void myPurecallHandler(void)
{
	printf("In _purecall_handler.");
	int* a = 0;
	*a = 1; // 크래시 유발. 오류 덤프 시스템으로 우회시키기.
}

void Test();

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 오류 코드를 필요에 따라 수정합니다.
            wprintf(L"심각한 오류: MFC를 초기화하지 못했습니다.\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.
			_set_purecall_handler(myPurecallHandler);
			Test();
        }
    }
    else
    {
        // TODO: 오류 코드를 필요에 따라 수정합니다.
        wprintf(L"심각한 오류: GetModuleHandle 실패\n");
        nRetCode = 1;
    }
	getchar();
    return nRetCode;
}

using namespace jturbo;

class LongTask : public Task
{
public:
	LongTask(int taskNum)
		: m_TaskNum(taskNum)
	{
	}
	virtual ~LongTask() {}
	virtual void Run() override
	{
// 		std::cout << m_TaskNum << "LongTask run." << std::endl;
// 		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
private:
	int m_TaskNum;
};

class ShortTask : public Task
{
public:
	ShortTask(int taskNum)
		: m_TaskNum(taskNum)
	{
	}
	virtual ~ShortTask() {}
	virtual void Run() override
	{
// 		std::cout << m_TaskNum << "ShortTask run." << std::endl;
// 		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
private:
	int m_TaskNum;
};

void Test()
{
	std::unique_ptr<TaskManager> pTaskManager(std::make_unique<TaskManager>(8));
	StopWatch<> stopWatch;
	for (int i = 0; i < 10000000; ++i)
	{
		std::shared_ptr<Task> pTask;
		int j = i % 2;
		if (j == 0)
			pTask = std::make_shared<LongTask>(i);
		else
			pTask = std::make_shared<ShortTask>(i);
		pTaskManager->Push(pTask);
	}

	while (pTaskManager->RemainSize() != 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << "Elsp " << stopWatch.GetMilliseconds() << "msec" << std::endl;
}