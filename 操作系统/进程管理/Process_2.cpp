#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
HANDLE  hEvent;		// 全局Event对象
HANDLE  hThread;	// 全局线程对象
bool  bFlag;	// 控制线程循环的条件
int count=0;
DWORD  WINAPI  FuncThread(LPVOID p);
int    func(void);
int  main(int argc, char** argv)
{
	hEvent = INVALID_HANDLE_VALUE;
	hThread = INVALID_HANDLE_VALUE;
	bFlag = false;
	
	int ret = func();
	printf("func return: %d\n", ret);
	// ---------------------------------------
	
	if(hThread != INVALID_HANDLE_VALUE)	CloseHandle(hThread);
	if(hEvent != INVALID_HANDLE_VALUE)	CloseHandle(hEvent);

	return 0;
}

// funcB()在线程操作超时时， 改变线程的循环条件bFlag结束之
int  func(void)
{
	DWORD  threadID;
	int value = 222;
	bFlag = true;
	hThread = CreateThread(NULL, 0, FuncThread, (LPVOID)&value, 0, &threadID);
	DWORD  ret = WaitForSingleObject(hThread, 3000);
	if(ret ==  WAIT_OBJECT_0)
	{
		return 0;
	}
	else if(ret == WAIT_TIMEOUT)
	{
		bFlag = false;
		return 1;
	}
	return 2;
}

// FuncThreadB()使用bool型的循环条件控制循环
DWORD  WINAPI  FuncThread(LPVOID p)
{
	int value = *(int*)p;
	while(bFlag == true)
	{
		// do somethig....
count++;
		printf("FuncThreadB-%d,count=%d\n", value,count);
		Sleep(100);	
	}
	return 0;
}
