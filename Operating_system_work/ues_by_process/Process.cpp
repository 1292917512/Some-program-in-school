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
	// ��ʱ����
	CString sCommandLine;
	char cWindowsDirectory[MAX_PATH];
	char cCommandLine[MAX_PATH];
	DWORD dwExitCode;
	PROCESS_INFORMATION pi;
	STARTUPINFO si = {sizeof(si)};
	// �õ�WindowsĿ¼
	GetWindowsDirectory(cWindowsDirectory, MAX_PATH);
	// ����"���±�"�����������
	sCommandLine = CString(cWindowsDirectory) + "\\NotePad.exe";
	::strcpy(cCommandLine, sCommandLine);
	// ����"���±�"��Ϊ�ӽ���
	BOOL ret = CreateProcess(NULL, cCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (ret) {
		// �ر��ӽ��̵����߳̾��
		CloseHandle(pi.hThread);
		// �ȴ��ӽ��̵��˳�
		WaitForSingleObject(pi.hProcess, INFINITE);
		// ��ȡ�ӽ��̵��˳���
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
		// �ر��ӽ��̾��
		CloseHandle(pi.hProcess);
	}
	return nRetCode;
}
