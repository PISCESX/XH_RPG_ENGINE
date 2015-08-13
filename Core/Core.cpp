#include "Core.h"

#ifdef WIN32
#include <stdio.h>
#include <fstream>
#include <cstdarg>
#endif // WIN32

using namespace Engine;
using namespace Engine::Core;

/************************************************************************/
/* ��չ��׼��String��                                                    */ 
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
	/* �ַ��������� */
	char c_String[50] = {0};

	/* �������ɱ�������� */
	va_list arg_list;
	va_start(arg_list,Format);

	/* �Ӳ���������������ַ� */
	while (*Format != '\0')
	{
		/* ��ʽ���ַ����� */
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

			/* ���建�����Ǹ�ʽ���ַ���ͻ */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* �Ǹ�ʽ���ַ����� */
			c_String[0] = *Format;
			this->append(c_String);
		}

		/* ����һ���ַ����� */
		Format ++;
	}

	va_end(arg_list);
}

String::~String()
{

}

Error String::Format(const char* Format, ... )
{
	/* �ַ��������� */
	char c_String[50] = {0};

	/* �������ɱ�������� */
	va_list arg_list;
	va_start(arg_list,Format);

	/* �Ӳ���������������ַ� */
	while (*Format != '\0')
	{
		/* ��ʽ���ַ����� */
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

			/* ���建�����Ǹ�ʽ���ַ���ͻ */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* �Ǹ�ʽ���ַ����� */
			c_String[0] = *Format;
			this->append(c_String);
		}

		/* ����һ���ַ����� */
		Format ++;
	}

	va_end(arg_list);

	return No_Error;
}

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

String OperationManeger::WaitInput(void)
{
	String Command;

	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	Command.resize(1000);
	scanf("%s",&Command[0]);

#endif // WIN32

	return Command;
}

void OperationManeger::Print(String Content)
{
	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	printf(Content.c_str());

#endif // WIN32
}

void OperationManeger::Print(const char* Format, ... )
{
	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	string ThenString;

	/* �ַ��������� */
	char c_String[50] = {0};

	/* �������ɱ�������� */
	va_list arg_list;
	va_start(arg_list,Format);

	/* �Ӳ���������������ַ� */
	while (*Format != '\0')
	{
		/* ��ʽ���ַ����� */
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

			/* ���建�����Ǹ�ʽ���ַ���ͻ */
			memset(c_String,0, sizeof(c_String) );
		} 
		else{
			/* �Ǹ�ʽ���ַ����� */
			c_String[0] = *Format;
			ThenString.append(c_String);
		}

		/* ����һ���ַ����� */
		Format ++;
	}

	va_end(arg_list);

	printf( ThenString.c_str() );

#endif // WIN32
}


/************************************************************************/
/* �ײ��ļ�������                                                        */
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

	/* �ײ����������ƽ̨ʵ�� */
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

	/* �ײ����������ƽ̨ʵ�� */
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

	/* �ײ����������ƽ̨ʵ�� */
	Line.resize(1000);
	((fstream*)ThenFile)->getline(&Line[0],1000);

	return Line;
}

String FileManager::GetAll(void)
{
	String All;

	/* �ײ����������ƽ̨ʵ�� */
	uint32 Loop = 0;
	char Buf;
	while (((fstream*)ThenFile)->get(Buf))
	{
		All += Buf;
		Loop ++;
	}

	return All;
}
