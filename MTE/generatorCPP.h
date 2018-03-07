#ifndef _GENERATORcPP
#define _GENERATORcPP
#include <MTE/CodeOuter.h>
#include <MTE/JavaAdapt.h>

namespace DP{
	namespace MTE{
		 class GenCPP:public CodeOuter{
			 private:
				 ofstream* f;
				 string out="";
				 int level=0;
				 string GetTab();
				 void comand(string str){
					 out+=GetTab()+str+nr;
				 }
			 public:
				 inline GenCPP(  string FileName){
					 f=new ofstream();
					 f->open(FileName.c_str());
				}
				 virtual string EnumPrevix(const string &name){
					 return "";
				 }
				inline GenCPP(GenCPP&& gen){
					 f=gen.f;
					 gen.f=nullptr;
				 }
				inline void close(){
					 (*f)<<(out);
					 out="";
					 f->close();
				}
				inline void whilec(  string str){
					comand("while ("+str+") {");
					level++;
				}
				inline void whileE(){
					level--;
					comand("}");
				}
				inline void breakc(){
					comand("break;");
				}
				inline void forc(string Into,string predicate,string Inc){
					comand("for ( "+Into+"; "+predicate+"; "+Inc+"){");
					levP();
				}
				virtual void strReplaceChar(string name,string index,char c){
					string tmp="'"+c;
					tmp+="'";
					assign(name+" [ "+index+" ] ",tmp);
				}
				inline string nullIndexStr(){
					 return "0";
				 }
				inline int nullIndexStrInt(){
					 return 0;
				 }
				inline void ifc(string str){
					comand("if ("+str+") {");
					level++;
				}
				inline void ifE(){
					level--;
					comand("}");
				}
				 void enumc(string name, vector<string> value);
				 void begin(){
					comand("int main() {");
					level++;
				}
				 void end(){
					levM();
					comand("}");
				}
				 string strLen(string str){
					return str+".size ()";
				}
				 void switchc(  string str){
					comand("switch ( "+str+" ) {");
					level++;
				}
				 void casec(  string str){
					comand("case "+str+":");
					level++;
				}
				 void caseE(){
					comand("break;");
					level--;
				}
				 void caseDefEnd(){
					level--;
				}
				 void levP(){
					level++;
				}
				 void levM(){
					level--;
				}
				 void defaultc(string str){
					comand(str);
				}
				 void intc(  string str, int value){
					string gg=Integer::toString(value);
					comand("int "+str+" = "+gg+" ;");
				}
				 void intc(string str){
					intc(str,0);
				}
				 void header(){
					 string str="#include <iostream>";
					 str+=nr;
					 str+="#include <string>";
					 str+=nr;
					 str+="using std::cout;";
					 str+=nr;
					 str+="using std::cin;";
					 str+=nr;
					 str+="using std::string;";
					comand(str);
				}
				 void stringc(  string str,string value){
					comand("string "+str+" = \""+value+"\" ;");
				}
				 void stringc(string str){
					stringc(str,"");
				}
				 void print(  string str){
					comand("cout << \""+str+"\" ;");
				}
				 void printValue(string str){
					comand("cout << "+str+" ;");
				}
				 void read(  string str){
					comand("cin >> "+str+" ;");
				}
				 void throwc(){
					comand("throw;");
				}
				 void caseDefault(){
					defaultc("default:");
					levP();
				}
				 void typec(string type, string name,string value){
					comand(type+" "+name+" = "+ value+";");
				}
				 void assign(string name,string value){
					comand(name+" = "+value+";");
				}
				 void pr(string name,string value){
					comand(name+" += "+value+";");
				}
				 string GetType(string str){
					return str;
				}
		};
	}
}

#endif
