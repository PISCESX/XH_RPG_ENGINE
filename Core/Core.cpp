#include "Core.h"

#ifdef WIN32
#include <stdio.h>
#include <fstream>
#endif // WIN32

using namespace Engine::Core;

/************************************************************************/
/* ���Ĺ�����                                                            */ 
/************************************************************************/
CoreManager::CoreManager()
{

}

CoreManager::~CoreManager()
{

}

/************************************************************************/
/* �ײ����������                                                        */ 
/************************************************************************/
OperationManeger::OperationManeger()
{

}

OperationManeger::~OperationManeger()
{

}

string OperationManeger::WaitInput(void)
{
	string Command;

	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	Command.resize(1000);
	scanf("%s",&Command[0]);

#endif // WIN32

	return Command;
}

void OperationManeger::Print(string Content)
{
	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	printf(Content.c_str());

#endif // WIN32
}


/************************************************************************/
/* �ײ��ļ�������                                                        */
/************************************************************************/
FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

Bool FileManager::Open(string Name)
{
	Bool IfSuccess = False;

	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	ThenFile = (void*)new fstream(Name,ios::in | ios::out | ios::binary);

	if ( ((fstream*)this->ThenFile)->fail() == true ){
		IfSuccess = True;
	}else{
		IfSuccess = False;
	}

#endif // WIN32

	return IfSuccess;
}

string FileManager::GetLine(void)
{
	string Line;

	/* �ײ����������ƽ̨ʵ�� */
	Line.resize(1000);
	((fstream*)this->ThenFile)->getline(&Line[0],1000);

	return Line;
}
