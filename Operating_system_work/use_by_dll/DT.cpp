#include <stdio.h>
#include <windows.h>
typedef int(*lpAddFun)(int, int); //�궨�庯��ָ������
typedef float(*lpAddFun_float)(float, float);
typedef char* (*lpAddFun_char)(char*);
int main(int argc, char* argv[])
{
	HINSTANCE hDll; //DLL��� 
	lpAddFun addFun; //����ָ��
	lpAddFun_float addFun_f;
	lpAddFun_char addFun_c;//�ַ����ຯ��ָ��
	char str[20] = "2704180316wcl";
	hDll = LoadLibrary("Dll1.dll");
	if (hDll != NULL)
	{
		addFun = (lpAddFun)GetProcAddress(hDll, "add");
		if (addFun != NULL)
		{
			int result = addFun(2, 3);
			printf("add:%d\n", result);
		}
		addFun = (lpAddFun)GetProcAddress(hDll, "sub");
		if (addFun != NULL)
		{
			int result = addFun(2, 3);
			printf("sub:%d\n", result);
		}
		addFun = (lpAddFun)GetProcAddress(hDll, "mul");
		if (addFun != NULL)
		{
			int result = addFun(2, 3);
			printf("mul:%d\n", result);
		}
		addFun_f = (lpAddFun_float)GetProcAddress(hDll, "div");
		if (addFun_f != NULL)
		{
			float result = addFun_f(3, 2);
			printf("div:%f\n", result);
		}
		printf("ԭ����%s\n",str);
		addFun_c = (lpAddFun_char)GetProcAddress(hDll, "key");
		if (addFun_c != NULL)
		{
			addFun_c(str);
			printf("���ܣ�%s\n", str);
		}
		addFun_c = (lpAddFun_char)GetProcAddress(hDll, "unkey");
		if (addFun_c != NULL)
		{
			addFun_c(str);
			printf("���ܣ�%s\n", str);
		}
		FreeLibrary(hDll);
	}
	return 0;
}
