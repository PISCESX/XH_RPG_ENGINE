#include "XH_Script.h"
#include <sstream>

#include <stack>

using namespace Engine;
using namespace Engine::Core;
using namespace Engine::Core::Script;


/************************************************************************/
/* ���ʽ�������                                                        */ 
/************************************************************************/
Expression::Expression()
{

}

Expression::~Expression()
{

}

/************************************************************************/
/* ������ʽ�������                                                    */ 
/************************************************************************/
CmdExpression::CmdExpression(String& Cmd)
{
	this->Cmd = Cmd;
}

/************************************************************************/
/* �ظ����ʽ��                                                          */ 
/************************************************************************/
RepeatExpression::RepeatExpression(Expression* expression,uint32 Number)
{
	this->expression = expression;
	this->Number = Number;
}

RepeatExpression::~RepeatExpression()
{
	delete this->expression;
}

float RepeatExpression::Interpret(void)
{
	if (expression == NULL){
		return 0;
	}

	for (uint32 n = 0; n < this->Number; n++){
		expression->Interpret();
	}

	return 1;
}

/************************************************************************/
/* �������ʽ��                                                        */ 
/************************************************************************/
BlockExpression::BlockExpression(deque<Expression*> &ExpDeque)
{
	this->ExpDeque = ExpDeque;
}

BlockExpression::~BlockExpression()
{
	for (uint32 n = 0; n < ExpDeque.size(); n++)
	{
		if (ExpDeque[n] != NULL)
		{
			delete ExpDeque[n];
		}
	}
}

float BlockExpression::Interpret(void)
{
	for (uint32 n = 0; n < ExpDeque.size(); n++)
	{
		if (ExpDeque[n] != NULL)
		{
			ExpDeque[n]->Interpret();
		}
	}

	return 1;
}

/************************************************************************/
/* �жϱ��ʽ��                                                          */ 
/************************************************************************/
JudgeExpression::JudgeExpression(String& Judge)
{
	this->Judge = Judge;
}

JudgeExpression::~JudgeExpression()
{

}

/************************************************************************/
/* If���ʽ��                                                          */ 
/************************************************************************/
IfExpression::IfExpression(Expression* JudgeExp,Expression* TrueExp,Expression* FalseExp)
{
	this->JudgeExp = JudgeExp;
	this->TrueExp  = TrueExp;
	this->FalseExp = FalseExp;
}

IfExpression::~IfExpression()
{
	delete JudgeExp,TrueExp,FalseExp;
}

float IfExpression::Interpret(void)
{
	if ((JudgeExp == NULL) || (TrueExp == NULL) || (FalseExp == NULL)){
		return 0;
	}

	if ( JudgeExp->Interpret() ){
		TrueExp->Interpret();
	}else{
		FalseExp->Interpret();
	}

	return 1;
}

/************************************************************************/
/* �Ż��ű�������                                                        */ 
/************************************************************************/
XH_Script::XH_Script()
{

}


XH_Script::~XH_Script()
{

}

void XH_Script::Run(void)
{
	while ( !IsEnd() )
	{
		/* ��ȡһ�� */
		String Line = GetLine();
		/* ����һ�п�ʼ���� */
		Expression* ResultExp = Analysis(Line);
		/* ������ʽ��������ͱ��ʽ */
		if (ResultExp != NULL){
			ResultExp->Interpret();
		}
	}
}

Expression* XH_Script::Analysis(String& Line)
{
	/* ��������ջ */
	//stack<Expression*>* pAnalysisStack = new stack<Expression*>;
	/* ������ʽ */
	Expression* ResultExp = NULL;
	/* ��������һ�а����ľ��� */
	Sentence ThenSentence = GetSentence(Line);
	Error SentenceError = GetError();
	if (SentenceError == No_Error)
	{
		/* ���ݲ�ͬ�ؼ��ִ�����ͬ���ʽ */
		if (ThenSentence.KeyWord == "CMD"){/* ִ��һ������ */
			// ������ʽ��ʵ�ֽ���ʵ���࣬�������ﶯ̬����Ĺ��������麯��
			ResultExp = CreateCmdExpression(ThenSentence.Content);	
		}else if(ThenSentence.KeyWord == "REPEAT"){
			/* ����һ�е�������Ϊ�ظ����� */
			Line = GetLine();
			Expression* ExpToRepeat = Analysis(Line);
			uint32 TimeToRepeat = ThenSentence.Content.ToUint32();
			ResultExp = new RepeatExpression(ExpToRepeat,TimeToRepeat);
		}else if(ThenSentence.KeyWord == "IF"){

		}else if(ThenSentence.KeyWord == "BLOCK"){
			deque<Expression*> ExpDeque;
			while(Line != "ENDBLOCK;")
			{
				Line = GetLine();
				if ( (Line == "ENDBLOCK;") || (IsEnd()) ){
					break;
				}

				Expression* Exp = Analysis(Line);
				ExpDeque.push_back(Exp);
			}

			ResultExp = new BlockExpression(ExpDeque);
		}else{

		}

	}else{
		/* ���л�������,������һ�в�������� */
		this->ErrorStatus = No_Error;
	}

	//delete pAnalysisStack;
	return ResultExp;
}

Sentence XH_Script::GetSentence(String& Line)
{
	/* ���ҷָ���(����ð�� ':') */
	int SeparatornLoc = Line.find(':');

	Sentence SentenceBuf;
	if (SeparatornLoc != string::npos){
		// ����ҵ��ָ���(����ð�� ':')
		// ��ָ���ǰΪ�ؼ���,
		// �ָ����������(����';')֮��Ϊ���� 
		String KeyWord = Line.substr(0,SeparatornLoc);	// ��ȡ�ؼ���

		String Content = Line.substr(SeparatornLoc + 1,string::npos);	// ��ȡ����
		char FinishChar = Content[Content.length() - 1];					// Ѱ�ҷֺ�
		if (FinishChar == ';'){
			/* ȥ���ֺż��Ժ�����ݣ�����ð�źͷֺ�֮������� */
			Content = Content.substr(0,Content.length() - 1);
			/* ��������ɣ����Sentence���󲢷��� */
			SentenceBuf.KeyWord = KeyWord;
			SentenceBuf.Content = Content;
			return SentenceBuf;
		}else{
			/* ���û�ҵ��ֺţ����׳��������� */
			this->ErrorStatus = Script_FindFailed;
			return SentenceBuf;
		}
	}else{
		/* �Ҳ����ָ���,�׳��������� */
		this->ErrorStatus = Script_FindFailed;
		return SentenceBuf;
	}
}
