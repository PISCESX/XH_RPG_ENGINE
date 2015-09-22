#include "UI.h"

#ifdef WIN32
#include "windows.h"
#endif // WIN32

using namespace Engine;
using namespace Engine::Scene;

#include <iostream>
using namespace std;


UI::UI(Core::CoreManager& CoreManager) : CoreManager(CoreManager)
{
	
}

UI::~UI()
{

}

/************************************************************************/
/* 行走场景界面                                                          */
/************************************************************************/
FieldManager::FieldManager(Core::CoreManager& CoreManager) : UI(CoreManager)
{

}

FieldManager::~FieldManager()
{

}

Error FieldManager::Show(uint32 Number)
{

	String FileName(".\\Config\\Scene\\%d\\Field.ini",Number);
	Bool Fail = CoreManager.File.Open(FileName);
	if (Fail){
		return Field_NoFile;
	}

	String FieldStr = CoreManager.File.GetAll();
	String sNumber("#%d#",Number);

	string::size_type Position;
	string::size_type Start,Finish;

	Position = FieldStr.find(sNumber);
	if (Position != string::npos){
		/* 加2忽略行尾的\r和\n */
		Start = Position + sNumber.size() + 2;
		Position = FieldStr.find(sNumber,Start);
		if (Position != string::npos){
			Finish = Position;
			String new_str = FieldStr.substr(Start,Finish - Start);
			CoreManager.Operation.Print(new_str);
		}else{
			return Field_NotFound;
		}
	}else{
		return Field_NotFound;
	}
	
	CoreManager.File.Close();
	return No_Error;
}

/************************************************************************/
/* 事件界面界面                                                          */
/************************************************************************/
EventUIManager::EventUIManager(Core::CoreManager& CoreManager) : UI(CoreManager)
{

}

EventUIManager::~EventUIManager()
{

}

Error EventUIManager::Show(uint32 SceneNumber)
{
	char FileName_c[50];
	sprintf(FileName_c,".\\Config\\Scene\\%d\\Config.ini",SceneNumber);

	/* 底层操作，根据平台实现 */
#ifdef WIN32
	char Return[50];

	GetPrivateProfileString("Config","SceneName","",Return,50,FileName_c);
	CoreManager.Operation.Print("在[%s]你发现了:\n",Return);

	DWORD EventNumber = GetPrivateProfileInt("Config","EventNumber",0,FileName_c);
	for (uint32 i = 0; i < EventNumber; i++)
	{
		char sEventSection[20];
		sprintf(sEventSection,"Event_%d",i);
		GetPrivateProfileString(sEventSection,"Name","",Return,50,FileName_c);
		if (*Return != '\0'){
			CoreManager.Operation.Print("[%d] %s\n",i,Return);
		}else{
			return Event_ReadFailed;
		}
	}

#endif // WIN32
	
	return No_Error;
}

String EventUIManager::WaitInput(void)
{
	CoreManager.Operation.Print("请输入指令:");

	return CoreManager.Operation.WaitInput();
}
