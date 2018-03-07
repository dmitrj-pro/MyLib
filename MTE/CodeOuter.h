#ifndef _CODE_OUTER
#define _CODE_OUTER
#include <MTE/JavaAdapt.h>
//#define string string

namespace DP{
	namespace MTE{
		class CodeOuter{
			public:
				virtual ~CodeOuter(){};
				CodeOuter(){}
				CodeOuter(const CodeOuter& c){}
				CodeOuter(string str){}
				 virtual void close(){};
				 virtual string EnumPrevix(const string &name){};
				 virtual void strReplaceChar(string name,string index,char c){};

				 virtual void whilec(string str){};
				 virtual void whileE(){};
				 virtual void breakc(){};

				 virtual void forc(string Into,string predicate,string Inc){};

				 virtual void ifc(string str){};
				 virtual void ifE(){};

				 virtual void enumc(string name, vector<string> value){};

				 virtual void begin(){};
				 virtual void end(){};

				 virtual void switchc(string str){};
				 virtual void casec(string str){};
				 virtual void caseE(){};
				 virtual void caseDefault(){};
				 virtual void caseDefEnd(){};

				 virtual void levP(){};
				 virtual void levM(){};

				 virtual void defaultc(string str){};

				 virtual void intc(string str,int value){};
				 virtual void intc(string str){};
				 virtual void stringc(string str,string value){};
				 virtual void stringc(string str){};
				 //3.10.16
				 virtual string nullIndexStr(){};
				 virtual int nullIndexStrInt(){};
				 virtual void typec(string type, string name,string value){};
				 virtual void assign(string name,string value){};
				 virtual string strLen(string str){};
				 virtual void pr(string name,string value){};
				 virtual string GetType(string str){};

				 virtual void print(string str)=0;
				 virtual void read(string str){};
				 virtual void printValue(string str){};

				 virtual void header(){};

				 virtual void throwc(){};
		};
	}
}

#endif
