// Win32Project1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"

typedef char*(*StartfuncPtrAdd)(char* p0);
typedef void(*StopfuncPtrAdd)(char* p0);
typedef int(*IsRunningfuncPtrAdd)(char* p0);

int _tmain(int argc, _TCHAR* argv[])
{
	// 加载模块
	HMODULE hModuleHandle = LoadLibraryA("proxy-sdk.dll");
	if (NULL == hModuleHandle || INVALID_HANDLE_VALUE == hModuleHandle)
	{
		// 找不到dll
		return -1;

	}
	// 获取模块函数地址
	StartfuncPtrAdd pFuncStart = (StartfuncPtrAdd)GetProcAddress(hModuleHandle, "Start");
	StopfuncPtrAdd pFuncStop = (StopfuncPtrAdd)GetProcAddress(hModuleHandle, "Stop");
	IsRunningfuncPtrAdd pFuncIsRunning = (IsRunningfuncPtrAdd)GetProcAddress(hModuleHandle, "IsRunning");
	// 检查函数是否获取成功
	if (pFuncStart == NULL)
	{
		printf("Start 函数地址获取失败");
		return -1;
	}
	if (pFuncStop == NULL)
	{
		printf("Stop 函数地址获取失败");
		return -1;
	}
	if (pFuncIsRunning == NULL)
	{
		printf("IsRunning 函数地址获取失败");
		return -1;
	}
	
	char* pSexVar = "http -p :7771";
	//GoString sGoStr = { pSexVar, strlen(pSexVar) };

	// 启动服务 返回空字符串说明启动成功;返回非空字符串说明启动失败,返回的字符串是错误原因
	char* pRetMessage = pFuncStart(pSexVar);
	printf("%s\r\n", pRetMessage);

	// 关闭服务 没有返回值
	pFuncStop(pSexVar);
	printf("have already stopped\r\n");

	// 检查服务是否在运行 0没有 1在运行
	int iRet = pFuncIsRunning(pSexVar);
	printf("current status %d\r\n", iRet);
	getchar();
	return 0;
}



