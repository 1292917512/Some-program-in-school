#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "Process.h"
#include <stdlib.h>
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//函数声明部分
DWORD  WINAPI  Timing_Thread(LPVOID p);
int    func(void);


//全局变量和结构体定义部分
HANDLE  hEvent;		// 全局Event对象
HANDLE  hThread;	// 全局线程对象
int count=0;


/////////////////////////////////////////////////////////////////////////////
// The one and only application object
CWinApp theApp;
using namespace std;
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	// 临时变量
	CString sCommandLine;
	char cWindowsDirectory[MAX_PATH];
	char cCommandLine[MAX_PATH];
	DWORD dwExitCode;  //等待回收的子进程
	DWORD  threadID;    //开启的线程
	PROCESS_INFORMATION pi;
	STARTUPINFO si = {sizeof(si)};
	// 得到Windows目录
	GetWindowsDirectory(cWindowsDirectory, MAX_PATH);
	// 启动"记事本"程序的命令行
	sCommandLine = CString(cWindowsDirectory) + "\\NotePad.exe";
	::strcpy(cCommandLine, sCommandLine);
	// 启动"记事本"作为子进程
	BOOL ret = CreateProcess(NULL, cCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if(ret)
	{
		printf("process Working\n Timing Thread\n");
		hThread = CreateThread(NULL, 0, Timing_Thread, (LPVOID)&pi, 0, &threadID);  //进程创建 FuncThread为所要创建的进程，LPVOID为未命名类型指针，pi为传递进去的进程句柄。
		printf("主线程依旧在运行\n");
		DWORD  ret2 = WaitForSingleObject(hThread, 8000);  //等待进程的时间	
		if(ret2 ==  WAIT_OBJECT_0)
		{
			printf("程序运行完毕\n");
		}
		else if(ret2 == WAIT_TIMEOUT)
		{	
			printf("进程超时，将会3s后被关闭\n");
			Sleep(3000);
			char pID[101];
			char dp[101] = "taskkill /pid ";
			memset(pID, 0, sizeof(pID));
			sprintf(pID, "%d", pi.dwProcessId);		
			strcat(dp, pID);
			strcat(dp, " /f");
			system(dp);	 //关闭进程；
			printf("进程已经关闭\n");
		}
	}
	// 获取子进程的退出码
	GetExitCodeProcess(pi.hProcess, &dwExitCode);
	// 关闭子进程句柄
	CloseHandle(pi.hProcess);
	return nRetCode;
}


// FuncThreadB()使用bool型的循环条件控制循环
DWORD  WINAPI Timing_Thread(LPVOID p)
{
	PROCESS_INFORMATION pi = *(PROCESS_INFORMATION*)p;
	// 关闭子进程的主线程句柄
	CloseHandle(pi.hThread);
	printf("已经进入等待线程\n");
	// 等待子进程的退出
	WaitForSingleObject(pi.hProcess, INFINITE);
	return 0;
}
