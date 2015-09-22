// XH_RPG_ENGINE.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "Core.h"
#include "UI.h"
#include "Scene.h"

using namespace std;
using namespace Engine;


Engine::Core::CoreManager CoreManager;

Engine::Scene::SceneManager _SceneManager(CoreManager);

int _tmain(int argc, _TCHAR* argv[])
{

	Error e = _SceneManager.Field.Show(1);
	e = _SceneManager.Event.UI.Show(1);
	//SceneManger.Event.UI.WaitInput();

	_SceneManager.Event.Script.LoadFile(".\\Config\\Scene\\1\\DuanYu.event");
	_SceneManager.Event.Script.Run();

	_SceneManager.Event.Script.CheckError();

	for ( ; ; );

	/* ���������� */
	return 0;
}

