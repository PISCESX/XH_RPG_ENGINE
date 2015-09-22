#ifndef XH_RPG_ENGINE_UI_H
#define XH_RPG_ENGINE_UI_H

#include <Core.h>

namespace Engine
{
	namespace Scene
	{
		
		class UI
		{
		public:
			UI(Core::CoreManager& CoreManager);
			~UI();

			virtual Error Show(uint32 Number) = 0;
		protected:
			Core::CoreManager& CoreManager;
		};

		class FieldManager : public UI
		{
		public:
			FieldManager(Core::CoreManager& CoreManager);
			~FieldManager();

			Error Show(uint32 SceneNumber);
		private:

		};

		class EventUIManager : public UI
		{
		public:
			EventUIManager(Core::CoreManager& CoreManager);
			~EventUIManager();

			Error Show(uint32 SceneNumber);
			String WaitInput(void);
		private:

		};

	}
}


#endif // !XH_RPG_ENGINE_UI_H
