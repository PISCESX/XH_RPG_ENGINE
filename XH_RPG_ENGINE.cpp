// XH_RPG_ENGINE.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Core.h>
#include <iostream>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	Engine::Core::CoreManager Core;

	Core.Operation.Print(Core.Operation.WaitInput());

	/* ���������� */
	return 0;
}

