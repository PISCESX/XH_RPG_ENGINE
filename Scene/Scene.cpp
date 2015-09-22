#include "Scene.h"

using namespace Engine;
using namespace Engine::Scene;

SceneManager::SceneManager(Core::CoreManager& CoreManager) : Field(CoreManager),Event(CoreManager)
{
	
}

SceneManager::~SceneManager()
{

}

void SceneManager::ChangeScene(uint32 Number)
{
	this->ThenSceneNumber = Number;
}

