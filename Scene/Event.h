#ifndef XH_RPG_ENGINE_EVENT_H
#define XH_RPG_ENGINE_EVENT_H

#include "UI.h"
#include "XH_Script.h"

namespace Engine
{
	namespace Scene
	{
		using namespace Engine::Core;
		using namespace Engine::Core::Script;

		class SceneManager;

		class EventCmd : public CmdExpression
		{
		public:
			EventCmd(String& Cmd,CoreManager& Core);

			float Interpret(void);
		private:
			CoreManager& Core;
			String FindParameter(String& Sentence);
		};

		class EventScript : public XH_Script
		{
		public:
			EventScript(Core::CoreManager& CoreManager);
			~EventScript();

			void LoadFile(String FileName);
		private:
			Core::CoreManager& CoreManager;
			String EventFileName;

			String GetLine(void);
			Bool IsEnd(void);
			Expression* CreateCmdExpression(String& Cmd);
		};

		class EventManager
		{
		public:
			EventManager(Core::CoreManager& CoreManager);
			~EventManager();

			EventUIManager UI;
			EventScript Script;
		private:

		};

	}
}

#endif // !XH_RPG_ENGINE_EVENT_H
