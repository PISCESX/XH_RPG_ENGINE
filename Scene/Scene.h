#ifndef XH_RPG_ENGINE_SCENE_H
#define XH_RPG_ENGINE_SCENE_H

#include "Event.h"

namespace Engine
{
	namespace Scene
	{
		class SceneManager
		{
		public:
			SceneManager(Core::CoreManager& CoreManager);
			~SceneManager();

			FieldManager Field;
			EventManager Event;

			void ChangeScene(uint32 Number);
		private:
			uint32 ThenSceneNumber;
		};


	}
}

#endif // !XH_RPG_ENGINE_SCENE_H
