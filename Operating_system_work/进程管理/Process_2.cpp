#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
HANDLE  hEvent;		// ȫ��Event����
HANDLE  hThread;	// ȫ���̶߳���
bool  bFlag;	// �����߳�ѭ��������
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

// funcB()���̲߳�����ʱʱ�� �ı��̵߳�ѭ������bFlag����֮
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

// FuncThreadB()ʹ��bool�͵�ѭ����������ѭ��
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
