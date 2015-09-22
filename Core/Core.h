#ifndef XH_RPG_ENGINE_CORE_H
#define XH_RPG_ENGINE_CORE_H

#include <String>

using namespace std;

namespace Engine
{
	typedef enum xh_bool{
		True = 1,False = 0
	}Bool;
	
	typedef unsigned int uint32;

	typedef enum xh_error{
		No_Error = 0,
		Field_NotFound,
		Field_NoFile,
		Event_ReadFailed,
		Script_FindFailed,
		Script_CmdNoFinish,
		Script_CmdNoParameter
	}Error;
	

	class String : public std::string
	{
	public:
		String();
		String(string& str);
		String(String& str);
		String(const char* Format, ... );
		~String();

		Error Format(const char* Format, ... );
		uint32 ToUint32(void);
		void trim(void);
	private:

	};

	class IErrorable
	{
	public:
		IErrorable();
		~IErrorable();

		void CheckError(void);
		String ErrorInf(void);
		void ClearError(void);
		Error GetError(void);
	protected:
		Error ErrorStatus;
	};

	namespace Core
	{

		class OperationManeger
		{
		public:
			OperationManeger();
			~OperationManeger();

			static String WaitInput(void);
			static void Print(String Content);
			static void Print(const char* Format, ... );
			static void Clear(void);
		private:

		};

		class FileManager
		{
		public:
			FileManager();
			~FileManager();

			Bool Open(String Name);
			Bool Close(void);
			String GetLine(void);
			String GetAll(void);
			Bool IsEnd(void);
		private:
			void* ThenFile;
		};

		class CoreManager
		{
		public:
			CoreManager();
			~CoreManager();

		public:
			OperationManeger Operation;
			FileManager		 File;
		};

	}
}

#endif // !XH_RPG_ENGINE_CORE_H
