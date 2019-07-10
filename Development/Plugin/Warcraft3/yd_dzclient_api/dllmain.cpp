// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"

namespace warcraft3::dzapi {
	void initialize();
}

//初始化函数
void Initialize()
{


}

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID /*lpReserved*/
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
	}
	else if(ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		
	}

	return TRUE;
}

