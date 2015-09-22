#ifndef XH_SCRIPT_H
#define XH_SCRIPT_H

#include "Core.h"
#include <deque>

namespace Engine
{
	namespace Core
	{
		namespace Script
		{

			class Expression : public IErrorable
			{
			public:
				Expression();
				~Expression();

				virtual float Interpret(void) = 0;
			private:

			};

			class CmdExpression : public Expression
			{
			public:
				CmdExpression(String& Cmd);

			protected:
				String Cmd;
			};

			class RepeatExpression : public Expression
			{
			public:
				RepeatExpression(Expression* expression,uint32 Number);
				~RepeatExpression();

				float Interpret(void);
			private:
				Expression* expression;
				uint32 Number;
			};

			class BlockExpression : public Expression
			{
			public:
				BlockExpression(deque<Expression*> &ExpDeque);
				~BlockExpression();

				float Interpret(void);
			private:
				deque<Expression*> ExpDeque;
			};

			class variable
			{
			public:
				//variable();
				//~variable();

			private:
				String Name;

			};


			class JudgeExpression : public Expression
			{
			public:
				JudgeExpression(String& Judge);
				~JudgeExpression();
				
			private:
				String Judge;
			};

			class IfExpression
			{
			public:
				IfExpression(Expression* JudgeExp,Expression* TrueExp,Expression* FalseExp);
				~IfExpression();

				float Interpret(void);
			private:
				Expression* TrueExp;
				Expression* FalseExp;
				Expression* JudgeExp;
			};

			

			class Sentence
			{
			public:
				Sentence(String& KeyWord,String& Content)
				{
					this->KeyWord = KeyWord;
					this->Content = Content;
				}
				Sentence(){}

			public:
				String KeyWord;
				String Content;
			};


			class XH_Script : public IErrorable
			{
			public:
				XH_Script();
				~XH_Script();

				void Run(void);
			protected:
				virtual String GetLine(void) = 0;
				virtual Bool IsEnd(void) = 0;
				virtual Expression* CreateCmdExpression(String& Cmd) = 0;
				//virtual Expression* CreateJudgeExpression(String& Judge) = 0;
			private:
				Sentence GetSentence(String& Line);
				Expression* Analysis(String& Line);
			};

		}
	}
}

#endif
