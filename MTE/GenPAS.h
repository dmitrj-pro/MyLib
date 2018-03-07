#ifndef _GEN_PAS
#define _GEN_PAS
#include <MTE/CodeOuter.h>
#include <MTE/JavaAdapt.h>
/**
 * Created by diman-pro on 26.09.16.
 */
namespace DP{
	namespace MTE{
		class GenPAS:public CodeOuter{
			private:
				 ofstream* f;
				 string out="";
				 int level=0;
				 string GetTab();
				 void comand(string str){
					 out+=GetTab()+str+nr;
				 }
			public:
				GenPAS( string FileName){
					f = new ofstream();
					f->open(FileName.c_str());
				}
				GenPAS(GenPAS&& gen){
					f=gen.f;
					gen.f=nullptr;
				}
				virtual void strReplaceChar(string name,string index,char c){
					string tmp="'"+c;
					tmp+="'";
					assign(name+" [ "+index+" ] ",tmp);
				}
				 virtual string EnumPrevix(const string &name){
					 return "";
				 }
				 void close(){
					 (*f)<<(out);
					 out="";
					 f->close();
				}
				 void whilec(  string str){
					comand("while "+str+" do");
					comand("begin");
					level++;
				}
				 void whileE(){
					level--;
					comand("end;");
				}
				 void breakc(){
					comand("break;");
				}
				 void forc(string Into,string predicate,string Inc){
					//2.10.16
					vector<string> st=split(Into,"=");
					vector<string> dst=split(st[0]," ");
					typec(dst[0], dst[1], st[1]);

					//this.defaultc(Into);
					whilec(predicate);
					defaultc(Inc+";");
					//comand("for ( "+Into+"; "+predicate+"; "+Inc+"){");
				}
				 string nullIndexStr(){
					 return "1";
				 }
				 int nullIndexStrInt(){
					 return 1;
				 }
				 void ifc(string str){
					if(str.find("==")!=-1){
						vector<string> st=split(str,"==");
						str=st[0]+" = "+ st[1];
					}
					comand("if "+str+" then");
					comand("begin");
					level++;
				}
				 void ifE(){
					level--;
					comand("end;");
				}
				 void enumc(string name, vector<string> value);
				 void begin(){
					comand("begin");
					level++;
				}
				 void end(){
					levM();
					comand("end.");
				}
				 void switchc(string str){
					comand("case "+str+" of");
					level++;
				}
				 void casec(string str){
					comand(str+":");
					level++;
					begin();
				}
				 void caseDefEnd(){
					level--;
					comand("end;");
				}
				 void caseE(){
					level--;
					comand("end;");
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
				 void intc(string str, int value){
					string gg=Integer::toString(value);
					comand("var "+str+":integer = "+gg+" ;");
				}
				 void intc(string str){
					intc(str,0);
				}
				 void header(){
					comand("program MTEOut;");
				}
				 void stringc(string str,string value){
					comand("var "+str+":string = '"+value+"' ;");
				}
				 void stringc(string str){
					stringc(str,"");
				}
				 void print(string str){
					comand("write ( '"+str+"' );");
				}
				 void printValue(string str){
					comand("write ( "+str +" );");
				}
				 void read(string str){
					comand("read ( "+str+" );");
				}
				 void throwc(){
					comand("raise new System.Exception();");
				}
				 void caseDefault(){
					defaultc("else begin");
					levP();
				}
				 string GetType(string str){
					if(str=="int"){
						return "Integer";
					}
					return str;
				}
				 string strLen(string str){
					return "length ( "+str+" ) ";
				}
				 void typec(string type, string name,string value){
					comand("var "+name+" : "+GetType(type)+" = "+ value+";");
				}
				 void assign(string name,string value){
					comand(name+" := "+value+";");
				}
				 void pr(string name,string value){
					comand(name+" += "+value+";");
				}
		};
	}
}
#endif
