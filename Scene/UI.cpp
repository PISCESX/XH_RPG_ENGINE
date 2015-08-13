#include "UI.h"

#ifdef WIN32
#include "windows.h"
#endif // WIN32

using namespace Engine;
using namespace Engine::Scene;

#include <iostream>
using namespace std;


UI::UI(Core::CoreManager* Core)
{
	this->Core = Core;
}

UI::~UI()
{

}

/************************************************************************/
/* ���߳�������                                                          */
/************************************************************************/
FieldManager::FieldManager(Core::CoreManager* Core) : UI(Core)
{

}

FieldManager::~FieldManager()
{

}

Error FieldManager::Show(uint32 Number)
{

	String FileName(".\\Config\\Scene\\%d\\Field.ini",Number);
	Bool Fail = Core->File.Open(FileName);
	if (Fail){
		return Field_NoFile;
	}

	String FieldStr = Core->File.GetAll();
	String sNumber("#%d#",Number);

	string::size_type Position;
	string::size_type Start,Finish;

	Position = FieldStr.find(sNumber);
	if (Position != string::npos){
		/* ��2������β��\r��\n */
		Start = Position + sNumber.size() + 2;
		Position = FieldStr.find(sNumber,Start);
		if (Position != string::npos){
			Finish = Position;
			String new_str = FieldStr.substr(Start,Finish - Start);
			Core->Operation.Print(new_str);
		}else{
			return Field_NotFound;
		}
	}else{
		return Field_NotFound;
	}
	
	Core->File.Close();
	return No_Error;
}

/************************************************************************/
/* �¼��������                                                          */
/************************************************************************/
EventUIManager::EventUIManager(Core::CoreManager* Core) : UI(Core)
{

}

EventUIManager::~EventUIManager()
{

}

Error EventUIManager::Show(uint32 SceneNumber)
{
	char FileName_c[50];
	sprintf(FileName_c,".\\Config\\Scene\\%d\\Config.ini",SceneNumber);

	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	char Return[50];

	GetPrivateProfileString("Config","SceneName","",Return,50,FileName_c);
	Core->Operation.Print("��[%s]�㷢����:\n",Return);

	DWORD EventNumber = GetPrivateProfileInt("Config","EventNumber",0,FileName_c);
	for (uint32 i = 0; i < EventNumber; i++)
	{
		char sEventSection[20];
		sprintf(sEventSection,"Event_%d",i);
		GetPrivateProfileString(sEventSection,"Name","",Return,50,FileName_c);
		if (*Return != '\0'){
			Core->Operation.Print("[%d] %s\n",i,Return);
		}else{
			return Event_ReadFailed;
		}
	}

#endif // WIN32
	
	return No_Error;
}
