#include "stdafx.h"
#ifndef LIB_H
#define LIB_H
extern "C" int __declspec(dllexport)add(int x, int y);
extern "C" int __declspec(dllexport)sub(int x, int y);
extern "C" int __declspec(dllexport)mul(int x,int y);
extern "C" float __declspec(dllexport)div(float x,float y);
extern "C" void __declspec(dllexport)key(char* mes);
extern "C" void __declspec(dllexport)unkey(char* mes);
#endif


int add(int x, int y)
{
	return x + y;
}
int sub(int x,int y)
{
	return x-y;
}
int mul(int x,int y)
{
	return x*y;
}
float div(float x,float y)
{
	return x/y;
}

void key(char mes[])
{
	int i;
	for(i=0;mes[i]!='\0';++i)
	{
		mes[i]=char(int(mes[i])+i);
	}
}
void unkey(char mes[])
{
	int i;
	for(i=0;mes[i]!='\0';++i)
	{
		mes[i]=char(int(mes[i]-i));
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
)
{
    return TRUE;
}

