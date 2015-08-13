// XH_RPG_ENGINE.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Core.h"
#include "UI.h"
#include "Scene.h"


using namespace std;
using namespace Engine;


int _tmain(int argc, _TCHAR* argv[])
{
	Engine::Core::CoreManager Core;

	Engine::Scene::SceneManager Scene(&Core);

	Error e = Scene.Field.Show(1);
	e = Scene.Event.Show(1);

	for ( ; ; );

	/* 主函数返回 */
	return 0;
}

