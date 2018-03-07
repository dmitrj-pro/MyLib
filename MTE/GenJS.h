/*
 * GenJavaScript.h
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#ifndef LIB_MTE_GENJS_H_
#define LIB_MTE_GENJS_H_

#include <MTE/CodeOuter.h>
#include <MTE/JavaAdapt.h>

namespace DP{
	namespace MTE{
		 class GenJS:public CodeOuter{
			 private:
				 ofstream* f;
				 string out="";
				 int level=0;
				 string GetTab();
				 void comand(string str){
					 out+=GetTab()+str+nr;
				 }
			 public:
				 inline GenJS(  string FileName){
					 f=new ofstream();
					 f->open(FileName.c_str());
				}
				inline GenJS(GenJS&& gen){
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
					//comand("for ( "+Into+"; "+predicate+"; "+Inc+"){");
					comand("for ( "+Into+"; "+predicate+"; "+Inc+"){");
					levP();
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
					comand("function MTE(WD) {");
					level++;
				}
				 void end(){
					levM();
					comand("}");
				}
				 string strLen(string str){
					return str+".length ";
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
					comand("var "+str+" = "+gg+" ;");
				}
				 void intc(string str){
					intc(str,0);
				}
				 void header(){

				}
				 void stringc(  string str,string value){
					comand("var "+str+" = \""+value+"\" ;");
				}
				 void stringc(string str){
					stringc(str,"");
				}
				 virtual string EnumPrevix(const string &name){
					 return name+".";
				 }
				 void print(  string str){
					comand("write( \""+str+"\") ;");
				}
				 void printValue(string str){
					comand("write( "+str+" );");
				}
				 void read(  string str){
					comand(str+" = WD ;");
				}
				 void throwc(){
					comand("throw \"Error\";");
				}
				 void caseDefault(){
					defaultc("default:");
					levP();
				}
				 void typec(string type, string name,string value){
					comand("var "+name+" = "+ value+";");
				}
				 void assign(string name,string value){
					comand(name+" = "+value+";");
				}
					virtual void strReplaceChar(string name,string index,char c){
						assign(name,name+".substr( 0, "+index+" ) + '"+c+"' + "+name+".substr( 1+"+index+")");
					}
				 void pr(string name,string value){
					comand(name+" += "+value+";");
				}
				 string GetType(string str){
					return "var";
				}
		};
	}
}


#endif /* LIB_MTE_GENJS_H_ */
