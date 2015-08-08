// XH_RPG_ENGINE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Core.h>
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Engine::Core::CoreManager Core;

	Core.Operation.Print(Core.Operation.WaitInput());

	/* 主函数返回 */
	return 0;
}

