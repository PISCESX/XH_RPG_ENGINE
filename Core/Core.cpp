#include "Core.h"

#ifdef WIN32
#include <stdio.h>
#include <fstream>
#endif // WIN32

using namespace Engine::Core;

/************************************************************************/
/* 核心管理器                                                            */ 
/************************************************************************/
CoreManager::CoreManager()
{

}

CoreManager::~CoreManager()
{

}

/************************************************************************/
/* 底层操作管理器                                                        */ 
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

	/* 底层操作，根据平台实现 */
#ifdef WIN32
	Command.resize(1000);
	scanf("%s",&Command[0]);

#endif // WIN32

	return Command;
}

void OperationManeger::Print(string Content)
{
	/* 底层操作，根据平台实现 */
#ifdef WIN32
	printf(Content.c_str());

#endif // WIN32
}


/************************************************************************/
/* 底层文件管理器                                                        */
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

	/* 底层操作，根据平台实现 */
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

	/* 底层操作，根据平台实现 */
	Line.resize(1000);
	((fstream*)this->ThenFile)->getline(&Line[0],1000);

	return Line;
}
