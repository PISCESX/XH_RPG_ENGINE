#include "Event.h"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Core::Script;

#include <iostream>
#include <sstream>
using namespace std;

/************************************************************************/
/* 事件命令表达式                                                        */ 
/************************************************************************/
#include "Scene.h"
extern SceneManager _SceneManager;

EventCmd::EventCmd(String& Cmd,CoreManager& Core) : CmdExpression(Cmd),Core(Core)
{
	
}

float EventCmd::Interpret(void)
{
	String KeyWord;
	/* 第一个#前为命令关键字 */
	int KeyWordLocation = Cmd.find('#');
	if (KeyWordLocation != string::npos)
	{
		/* 提取出关键字 */
		KeyWord = Cmd.substr(0,KeyWordLocation);

		String ParaList = Cmd.substr(KeyWordLocation + 1);
		
		/* 在屏幕上打印一行字 */
		if (KeyWord == "PRINT")
		{
			Core.Operation.Print(FindParameter(ParaList));
			/* 如果失败会返回空字符串，相当于没有打印 */
		}

		/* 转换场景 */
		if (KeyWord == "GOTO SCENE")
		{
			stringstream ss;

			/* 参数字符串输入字符串流 */
			ss << FindParameter(ParaList);

			/* 如果出现问题，打印调试信息并返回 */
			this->CheckError();

			/* 利用字符串流将字符串中的数字提取到uint32型变量中 */
			uint32 SceneNumber;
			ss >> SceneNumber;

			/* 按提取出的数字切换场景 */
			_SceneManager.ChangeScene(SceneNumber);
		}

		/* 清屏 */
		if (KeyWord == "CLEAR")
		{
			Core.Operation.Clear();
		}

		/* 回车 */
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
/* 事件脚本管理器                                                        */ 
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
	/* 去除首尾空格 */
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
