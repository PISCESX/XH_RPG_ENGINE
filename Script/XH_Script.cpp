#include "XH_Script.h"
#include <sstream>

#include <stack>

using namespace Engine;
using namespace Engine::Core;
using namespace Engine::Core::Script;


/************************************************************************/
/* 表达式抽象基类                                                        */ 
/************************************************************************/
Expression::Expression()
{

}

Expression::~Expression()
{

}

/************************************************************************/
/* 命令表达式抽象基类                                                    */ 
/************************************************************************/
CmdExpression::CmdExpression(String& Cmd)
{
	this->Cmd = Cmd;
}

/************************************************************************/
/* 重复表达式类                                                          */ 
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
/* 块语句表达式类                                                        */ 
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
/* 判断表达式类                                                          */ 
/************************************************************************/
JudgeExpression::JudgeExpression(String& Judge)
{
	this->Judge = Judge;
}

JudgeExpression::~JudgeExpression()
{

}

/************************************************************************/
/* If表达式类                                                          */ 
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
/* 信花脚本解释器                                                        */ 
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
		/* 获取一行 */
		String Line = GetLine();
		/* 从这一行开始解析 */
		Expression* ResultExp = Analysis(Line);
		/* 如果表达式存在则解释表达式 */
		if (ResultExp != NULL){
			ResultExp->Interpret();
		}
	}
}

Expression* XH_Script::Analysis(String& Line)
{
	/* 创建解析栈 */
	//stack<Expression*>* pAnalysisStack = new stack<Expression*>;
	/* 结果表达式 */
	Expression* ResultExp = NULL;
	/* 解析出这一行包含的句子 */
	Sentence ThenSentence = GetSentence(Line);
	Error SentenceError = GetError();
	if (SentenceError == No_Error)
	{
		/* 根据不同关键字创建不同表达式 */
		if (ThenSentence.KeyWord == "CMD"){/* 执行一条命令 */
			// 命令表达式的实现交给实现类，所以这里动态分配的工作交给虚函数
			ResultExp = CreateCmdExpression(ThenSentence.Content);	
		}else if(ThenSentence.KeyWord == "REPEAT"){
			/* 以下一行的内容作为重复内容 */
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
		/* 空行或发生错误,跳过这一行并清除错误 */
		this->ErrorStatus = No_Error;
	}

	//delete pAnalysisStack;
	return ResultExp;
}

Sentence XH_Script::GetSentence(String& Line)
{
	/* 查找分隔符(西文冒号 ':') */
	int SeparatornLoc = Line.find(':');

	Sentence SentenceBuf;
	if (SeparatornLoc != string::npos){
		// 如果找到分隔符(西文冒号 ':')
		// 则分隔符前为关键字,
		// 分隔符与结束符(西文';')之间为内容 
		String KeyWord = Line.substr(0,SeparatornLoc);	// 截取关键字

		String Content = Line.substr(SeparatornLoc + 1,string::npos);	// 截取内容
		char FinishChar = Content[Content.length() - 1];					// 寻找分号
		if (FinishChar == ';'){
			/* 去掉分号及以后的内容，保留冒号和分号之间的内容 */
			Content = Content.substr(0,Content.length() - 1);
			/* 解析已完成，填充Sentence对象并返回 */
			SentenceBuf.KeyWord = KeyWord;
			SentenceBuf.Content = Content;
			return SentenceBuf;
		}else{
			/* 如果没找到分号，则抛出解析错误 */
			this->ErrorStatus = Script_FindFailed;
			return SentenceBuf;
		}
	}else{
		/* 找不到分隔符,抛出解析错误 */
		this->ErrorStatus = Script_FindFailed;
		return SentenceBuf;
	}
}
