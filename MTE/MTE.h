#ifndef MT_H
#define MT_H

#define capture '$'

#include <map>
#include <string>
#include <fstream>
#include<ostream>
#include<vector>
#include<algorithm>
#include <MTE/CodeOuter.h>

#include<iostream>

using std::map;
using std::vector;
using std::string;
using std::ifstream;
using std::ostream;

namespace DP{
	namespace MTE{

		class Triple{
			private:
				string symbol;
				int go;
				int status;
			public:
				Triple(){}
				Triple(string Symbol, int Go, int Status):go(Go),symbol(Symbol){
					if(Status<0){
						throw;
					}
					status=Status;
				}
				string Symbol() const{
					return symbol;
				}
				int Go() const{
					return go;
				}
				int Status()const{
					return status;
				}
				friend ostream& operator<<(ostream& os, const Triple& t){
					return os<<"Stat = "<<t.Status()<<"; Go = "<<t.Go()<<"; Symbol = "<<t.Symbol();
				}
		};

		class MT
		{
			private:
				enum class ReadType{NUL,Params,Comand};
				map<string, map<int,Triple> > tableOfGO;
				int n;
				int q;
				int final;
				int defaultStart;
				char DefaultSymbol;
				string word;
				void ReadParams(string& r,vector<string>& symbols);
				//MOD 3
				//29.9.2016
				string ScanNewValueInLoad(string old, string value, vector<string> symbols);
				void ReadComand(string& r, vector<string>& symbols);
				void run(const string& str);
			public:
				static inline string version(){
					string str="mte.myprogram.us 1.0.5";
					str+=nr;
					str+="3.10.2016";
					return str;
				}
				void print();

				void Load(const string&FileName);

				void LoadFromString(const string&Data);

				inline string runOnWord(string str){
					run(str);
					return word;
				}
				inline String runOnWord(){
					run(word);
					return word;
				}
				inline void setWord(const string&str){
					word=str;
					n=0;
					q=0;
				}
				string NextStep();

				void genOutCode(CodeOuter& gen);

				inline int getQ(){
					return q;
				}
				inline bool ScanWord(const string& str){
					try{
						run(str);
					} catch(...){
						return false;
					}
					return true;
				}
		};
	}
}

#endif
