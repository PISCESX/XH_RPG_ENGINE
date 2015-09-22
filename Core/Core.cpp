#include "Core.h"

#ifdef WIN32
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include "windows.h"
#endif // WIN32

using namespace Engine;
using namespace Engine::Core;

/************************************************************************/
/* 引擎各类的基类                                                        */ 
/************************************************************************/
IErrorable::IErrorable()
{
	ErrorStatus = No_Error;
}

IErrorable::~IErrorable()
{

}

Error IErrorable::GetError(void)
{
	return this->ErrorStatus;
}

void IErrorable::CheckError(void)
{
	if (this->ErrorStatus != No_Error){
		/* 如果出现问题，打印调试信息并停止 */
#ifdef _WIN32
		printf(this->ErrorInf().c_str());
#endif
		while(1);
	}else{
		this->ClearError();
	}
}

String IErrorable::ErrorInf(void)
{
	switch (this->ErrorStatus)
	{
	case No_Error : return "\n无错误\n";
	case Script_FindFailed : return "\n脚本解释错误:语句不完整\n";
	case Event_ReadFailed : return "\nEvent_ReadFailed\n";
	default : return "\n未知错误\n";
	}
}

void IErrorable::ClearError(void)
{
	this->ErrorStatus = No_Error;
}

/************************************************************************/
/* 扩展标准库String类                                                    */ 
/************************************************************************/
String::String()
{
	
}

String::String(string& str) : std::string(str)
{

}

String::String(String& str)
{
	this->append(str);
}

String::String(const char* Format, ... )
{
	/* 字符处理缓冲区 */
	char c_String[50] = {0};

	/* 编译器可变参数处理 */
	va_list arg_list;
	va_start(arg_list,Format);

	/* 从参数表向基类输入字符 */
	while (*Format != '\0')
	{
		/* 格式化字符输入 */
		if (*Format == '%'){
			Format ++;
			switch (*Format)
			{
			case 'd' : 
				{
					int number = va_arg(arg_list,int);
					sprintf(c_String,"%d",number);
					this->append(c_String);
					break;
				}
			case 'f' :
				{
					double fnumber = va_arg(arg_list,double);
					sprintf(c_String,"%f",fnumber);
					this->append(c_String);
					break;
				}
			case 's' :
				{
					char* pString = va_arg(arg_list,char*);
					sprintf(c_String,"%s",pString);
					this->append(c_String);
					break;
				}
			default:
				break;
			}

			/* 不清缓存会与非格式化字符冲突 */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* 非格式化字符输入 */
			c_String[0] = *Format;
			this->append(c_String);
		}

		/* 向下一个字符进行 */
		Format ++;
	}

	va_end(arg_list);
}

String::~String()
{

}

uint32 String::ToUint32(void)
{
	std::stringstream ss;
	uint32 Uint32;
	ss << (*this);
	ss >> Uint32;

	return Uint32;
}

void String::trim(void)   
{  
	if ( this->empty() ){  
		return ;  
	}
	/* 去除空格 */
	this->erase(0,this->find_first_not_of(" "));  
	this->erase(this->find_last_not_of(" ") + 1);    
	/* 去除缩进 */
	this->erase(0,this->find_first_not_of("\t"));  
	this->erase(this->find_last_not_of("\t") + 1);    
}  

Error String::Format(const char* Format, ... )
{
	/* 字符处理缓冲区 */
	char c_String[50] = {0};

	/* 编译器可变参数处理 */
	va_list arg_list;
	va_start(arg_list,Format);

	/* 从参数表向基类输入字符 */
	while (*Format != '\0')
	{
		/* 格式化字符输入 */
		if (*Format == '%'){
			Format ++;
			switch (*Format)
			{
			case 'd' : 
				{
					int number = va_arg(arg_list,int);
					sprintf(c_String,"%d",number);
					this->append(c_String);
					break;
				}
			case 'f' : 
				{
					double fnumber = va_arg(arg_list,double);
					sprintf(c_String,"%f",fnumber);
					this->append(c_String);
					break;
				}
			case 's' :
				{
					char* pString = va_arg(arg_list,char*);
					sprintf(c_String,"%s",pString);
					this->append(c_String);
					break;
				}
			default:
				break;
			}

			/* 不清缓存会与非格式化字符冲突 */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* 非格式化字符输入 */
			c_String[0] = *Format;
			this->append(c_String);
		}

		/* 向下一个字符进行 */
		Format ++;
	}

	va_end(arg_list);

	return No_Error;
}

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

String OperationManeger::WaitInput(void)
{
	String Command;

	/* 底层操作，根据平台实现 */
#ifdef WIN32
	Command.resize(1000);
	scanf("%s",&Command[0]);

#endif // WIN32

	return Command;
}

void OperationManeger::Print(String Content)
{
	/* 底层操作，根据平台实现 */
#ifdef WIN32
	printf(Content.c_str());

#endif // WIN32
}

void OperationManeger::Clear(void)
{
	/* 底层操作，根据平台实现 */
#ifdef WIN32
	system("cls");

#endif // WIN32
}

void OperationManeger::Print(const char* Format, ... )
{
	/* 底层操作，根据平台实现 */
#ifdef WIN32
	string ThenString;

	/* 字符处理缓冲区 */
	char c_String[50] = {0};

	/* 编译器可变参数处理 */
	va_list arg_list;
	va_start(arg_list,Format);

	/* 从参数表向基类输入字符 */
	while (*Format != '\0')
	{
		/* 格式化字符输入 */
		if (*Format == '%'){
			Format ++;
			switch (*Format)
			{
			case 'd' : 
				{
					int number = va_arg(arg_list,int);
					sprintf(c_String,"%d",number);
					ThenString.append(c_String);
					break;
				}
			case 'f' :
				{
					double fnumber = va_arg(arg_list,double);
					sprintf(c_String,"%f",fnumber);
					ThenString.append(c_String);
					break;
				}
			case 's' :
				{
					char* pString = va_arg(arg_list,char*);
					sprintf(c_String,"%s",pString);
					ThenString.append(c_String);
					break;
				}
			default:
				break;
			}

			/* 不清缓存会与非格式化字符冲突 */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* 非格式化字符输入 */
			c_String[0] = *Format;
			ThenString.append(c_String);
		}

		/* 向下一个字符进行 */
		Format ++;
	}

	va_end(arg_list);

	printf( ThenString.c_str() );

#endif // WIN32
}


/************************************************************************/
/* 底层文件管理器                                                        */
/************************************************************************/
FileManager::FileManager()
{
	ThenFile = (void*)new fstream();
}

FileManager::~FileManager()
{

}

Bool FileManager::Open(String Name)
{
	Bool IfSuccess = False;

	/* 底层操作，根据平台实现 */
#ifdef WIN32
	((fstream*)ThenFile)->open(Name,ios::in | ios::out | ios::binary);

	if ( ((fstream*)this->ThenFile)->fail() == true ){
		IfSuccess = True;
	}else{
		IfSuccess = False;
	}

#endif // WIN32

	return IfSuccess;
}

Bool FileManager::Close(void)
{
	Bool IfSuccess = False;

	/* 底层操作，根据平台实现 */
#ifdef WIN32
	((fstream*)ThenFile)->close();

	if ( ((fstream*)ThenFile)->fail() == true ){
		IfSuccess = True;
	}else{
		IfSuccess = False;
	}

#endif // WIN32

	return IfSuccess;
}

String FileManager::GetLine(void)
{
	String Line;

	/* 底层操作，根据平台实现 */
	static char Line_c[1000] = {0};
	((fstream*)ThenFile)->getline(&Line_c[0],1000);
	Line += Line_c;

	if (Line != "END FILE"){
		/* 所以可读配置文件均以"END FILE结尾" */
		Line.erase(Line.find("\r"),1);
	}

	return Line;
}

String FileManager::GetAll(void)
{
	String All;

	/* 底层操作，根据平台实现 */
	uint32 Loop = 0;
	char Buf;
	while (((fstream*)ThenFile)->get(Buf))
	{
		All += Buf;
		Loop ++;
	}

	return All;
}

Bool FileManager::IsEnd(void)
{
	Bool End;

	/* 底层操作，根据平台实现 */
	End = (Bool)((fstream*)ThenFile)->eof();

	return End;
}
