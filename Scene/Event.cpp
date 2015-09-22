#include "Event.h"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Core::Script;

#include <iostream>
#include <sstream>
using namespace std;

/************************************************************************/
/* �¼�������ʽ                                                        */ 
/************************************************************************/
#include "Scene.h"
extern SceneManager _SceneManager;

EventCmd::EventCmd(String& Cmd,CoreManager& Core) : CmdExpression(Cmd),Core(Core)
{
	
}

float EventCmd::Interpret(void)
{
	String KeyWord;
	/* ��һ��#ǰΪ����ؼ��� */
	int KeyWordLocation = Cmd.find('#');
	if (KeyWordLocation != string::npos)
	{
		/* ��ȡ���ؼ��� */
		KeyWord = Cmd.substr(0,KeyWordLocation);

		String ParaList = Cmd.substr(KeyWordLocation + 1);
		
		/* ����Ļ�ϴ�ӡһ���� */
		if (KeyWord == "PRINT")
		{
			Core.Operation.Print(FindParameter(ParaList));
			/* ���ʧ�ܻ᷵�ؿ��ַ������൱��û�д�ӡ */
		}

		/* ת������ */
		if (KeyWord == "GOTO SCENE")
		{
			stringstream ss;

			/* �����ַ��������ַ����� */
			ss << FindParameter(ParaList);

			/* ����������⣬��ӡ������Ϣ������ */
			this->CheckError();

			/* �����ַ��������ַ����е�������ȡ��uint32�ͱ����� */
			uint32 SceneNumber;
			ss >> SceneNumber;

			/* ����ȡ���������л����� */
			_SceneManager.ChangeScene(SceneNumber);
		}

		/* ���� */
		if (KeyWord == "CLEAR")
		{
			Core.Operation.Clear();
		}

		/* �س� */
		if (KeyWord == "ENTER")
		{
			Core.Operation.Print("\n");
		}
	}

	return 1;
}

String EventCmd::FindParameter(String& Sentence)
{
	int FinishLocation = Sentence.find('$');

	if (FinishLocation != string::npos)
	{
		return Sentence.substr(0,FinishLocation);
	} 
	else
	{
		this->ErrorStatus = Script_CmdNoParameter;
		return "";
	}
}

/************************************************************************/
/* �¼��ű�������                                                        */ 
/************************************************************************/
EventScript::EventScript(Core::CoreManager& CoreManager) : CoreManager(CoreManager)
{

}

EventScript::~EventScript()
{

}

void EventScript::LoadFile(String FileName)
{
	CoreManager.File.Open(FileName);
}

String EventScript::GetLine(void)
{
	String Line = CoreManager.File.GetLine();
	/* ȥ����β�ո� */
	Line.trim();
	return Line;
}
Bool EventScript::IsEnd(void)
{
	return CoreManager.File.IsEnd();
}
Expression* EventScript::CreateCmdExpression(String& Cmd)
{
	return new EventCmd(Cmd,CoreManager);
}




EventManager::EventManager(Core::CoreManager& CoreManager) : UI(CoreManager),Script(CoreManager)
{

}

EventManager::~EventManager()
{

}
