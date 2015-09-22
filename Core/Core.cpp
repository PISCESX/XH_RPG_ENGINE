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
/* �������Ļ���                                                        */ 
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
		/* ����������⣬��ӡ������Ϣ��ֹͣ */
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
	case No_Error : return "\n�޴���\n";
	case Script_FindFailed : return "\n�ű����ʹ���:��䲻����\n";
	case Event_ReadFailed : return "\nEvent_ReadFailed\n";
	default : return "\nδ֪����\n";
	}
}

void IErrorable::ClearError(void)
{
	this->ErrorStatus = No_Error;
}

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
	/* ȥ���ո� */
	this->erase(0,this->find_first_not_of(" "));  
	this->erase(this->find_last_not_of(" ") + 1);    
	/* ȥ������ */
	this->erase(0,this->find_first_not_of("\t"));  
	this->erase(this->find_last_not_of("\t") + 1);    
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

void OperationManeger::Clear(void)
{
	/* �ײ����������ƽ̨ʵ�� */
#ifdef WIN32
	system("cls");

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
	static char Line_c[1000] = {0};
	((fstream*)ThenFile)->getline(&Line_c[0],1000);
	Line += Line_c;

	if (Line != "END FILE"){
		/* ���Կɶ������ļ�����"END FILE��β" */
		Line.erase(Line.find("\r"),1);
	}

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

Bool FileManager::IsEnd(void)
{
	Bool End;

	/* �ײ����������ƽ̨ʵ�� */
	End = (Bool)((fstream*)ThenFile)->eof();

	return End;
}
