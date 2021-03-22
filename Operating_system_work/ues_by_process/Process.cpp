#include "stdafx.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
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
	DWORD dwExitCode;
	PROCESS_INFORMATION pi;
	STARTUPINFO si = {sizeof(si)};
	// 得到Windows目录
	GetWindowsDirectory(cWindowsDirectory, MAX_PATH);
	// 启动"记事本"程序的命令行
	sCommandLine = CString(cWindowsDirectory) + "\\NotePad.exe";
	::strcpy(cCommandLine, sCommandLine);
	// 启动"记事本"作为子进程
	BOOL ret = CreateProcess(NULL, cCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (ret) {
		// 关闭子进程的主线程句柄
		CloseHandle(pi.hThread);
		// 等待子进程的退出
		WaitForSingleObject(pi.hProcess, INFINITE);
		// 获取子进程的退出码
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		// 关闭子进程句柄
		CloseHandle(pi.hProcess);
	}
	return nRetCode;
}
