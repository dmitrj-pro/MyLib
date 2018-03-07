/*
 * MTE.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <MTE/MTE.h>
#include <MTE/JavaAdapt.h>
#include<sstream>

namespace DP{
	namespace MTE{
		void MT::ReadParams(string& r,vector<string>& symbols){
			string parametr="";
			string value;
			for(int i=0;i<r.length();i++){
				if(r[i]=='='){
					parametr=r.substr(0,i);
					value=r.substr(i+1);
					break;
				}
			}
			if(parametr=="end"){
				final=0;
				for(int i=0; i<value.size();i++){
					final=final*10+(value[i]-'0');
				}
				return;
			}
			if(parametr=="start"){
				for(int i=0; i<value.size();i++){
					defaultStart=defaultStart*10+(value[i]-'0');
				}
				return;
			}
			if(parametr=="defaultSymbol"){
				DefaultSymbol=value[0];
				return;
			}

			if(parametr=="A"){
				tableOfGO=map<string, map<int,Triple> >();
				string n="";
				for(int i=0;i<=value.size();i++){
					if((i==value.size())||(value[i]==',')){
						tableOfGO[n]=map<int,Triple>();
						if(find(symbols.begin(),symbols.end(),n)==symbols.end()){
							symbols.push_back(n);
						}
						n="";
						continue;
					}
					n+=value[i];
				}
				return;
			}
		}

		string MT::ScanNewValueInLoad(string old, string value, vector<string> symbols){
			if(value[0]==capture){
				if(value.length()==1){
					value=old;
				} else {
					int plus = Integer::parseInt(value.substr(2));
					if (find(symbols.begin(),symbols.end(),old)==symbols.end()) {
						switch (value[1]) {
						case '+':
							value = (char) (((int) old[0]) + plus) + "";
							break;
						case '-':
							value = (char) (((int) old[0]) - plus) + "";
							break;
						default:
							throw;// new ExceptionInInitializerError("Not Symbol" + value.charAt(1));
						}
					} else {
						int i;
						for(int j=0; j<symbols.size();j++){
							if(symbols[j]==old){
								i=j;
								break;
							}
						}
						switch (value[1]) {
						case '+':
							value = symbols[(i + plus) % symbols.size()];
							break;
						case '-':
							int tmps;
							tmps=i-plus;
							if(tmps<0){
								tmps+=symbols.size();
							}
							value = symbols[tmps];
							break;
						default:
							//throw new std::exception("Comand is not found");
							throw;// new ExceptionInInitializerError("Not Symbol" + value.charAt(1));
						}
					}
				}
			} else {
				symbols.push_back(old);
			}
			return value;
		}

		void MT::ReadComand(string& r, vector<string>& symbols){
			string parametr="";
			string value="";
			for(int i=0;i<r.length();i++){
				if(r[i]=='='){
					parametr=r.substr(0,i);
					value=r.substr(i+1);
					break;
				}
			}
			string Symbol=parametr.substr(0,parametr.find(','));
			string second=parametr.substr(parametr.find(',')+1);
			string first=value.substr(0,value.find(','));
			int t=value.find(',',value.find(',')+1);
			string t2=value.substr(value.find(',')+1,t);
			string t3=value.substr(t+1);
			int g1=0;
			int st=Integer::parseInt(t2);
			g1=Integer::parseInt(t3);
			int com=Integer::parseInt(second);
			if(Symbol[0]==capture){
				//Если передали шаблонный символ, то действия для него распространяем
				//на все остальные символы.
				for(int i=0; i<symbols.size();i++){
					bool tmp=true;
					for(auto x=tableOfGO[symbols[i]].begin();x!=tableOfGO[symbols[i]].end();x++){
						if((*x).first==com){
							tmp=false;
							break;
						}
					}
					if(tmp){
						//MOD 3
						//29.9.2016
						(tableOfGO[symbols[i]])[com]=Triple(ScanNewValueInLoad(symbols[i],first,symbols),g1,st);
					}
				}
			}else {
				//MOD 3
				//29.9.2016
				(tableOfGO[Symbol])[com]=Triple(ScanNewValueInLoad(Symbol,first,symbols),g1,st);
			}
		}

		void MT::run(const string& str){
			n=0;
			q=0;
			word=str;
			while(true){
				if(n<0){
					int tmp=(-1)*n;
					n=0;
					for(int i=0; i<tmp;i++){
						word=DefaultSymbol+word;
					}
				}
				if(n>=word.size()){
					int tmp=n-word.size()+1;
					for(int i=0;i<tmp;i++){
						word=word+DefaultSymbol;
					}
				}
				if(q==final){
					break;
				}
				string tmp="d";
				tmp[0]=word[n];
				if(tableOfGO.find(tmp)==tableOfGO.end()){
					throw;
				}
				if(this->tableOfGO[tmp].find(q)==this->tableOfGO[tmp].end()){
					throw;
				}
				const Triple& com=this->tableOfGO[tmp][q];
				word[n]=com.Symbol()[0];
				q=com.Status();
				n+=com.Go();
			}
		}

		void MT::print(){
			for(auto x=tableOfGO.begin();x!=tableOfGO.end();x++){
				std::cout<<"Symbol "<<(*x).first<<":";
				for(auto y=(*x).second.begin();y!=(*x).second.end();y++){
					std::cout<<" st = "<<(*y).first<<(*y).second;
				}
				std::cout<<")))\n";
			}
		}

		void MT::Load(const string&FileName){
			defaultStart=0;
			ifstream file;
			file.open(FileName.c_str());
			if(!file.is_open()){
				throw;
			}
			string r="";
			vector<string> symbols;
			ReadType typ=ReadType::Params;
			while(!file.eof()){
				getline(file,r);
				if(r=="<begin>"){
					typ=ReadType::Comand;
					continue;
				}
				if(r==""){
					continue;
				}
				switch(typ){
					case ReadType::Params:
						this->ReadParams(r,symbols);
						break;
					case ReadType::Comand:
						this->ReadComand(r,symbols);
						break;
					case ReadType::NUL:
						throw;
						break;
				}
			}
		}
		void MT::LoadFromString(const string&Data){
			std::istringstream file;
			file.str(Data);
			defaultStart=0;
			string r="";
			vector<string> symbols;
			ReadType typ=ReadType::Params;
			while(!file.eof()){
				getline(file,r);
				if(r=="<begin>"){
					typ=ReadType::Comand;
					continue;
				}
				if(r==""){
					continue;
				}
				switch(typ){
					case ReadType::Params:
						this->ReadParams(r,symbols);
						break;
					case ReadType::Comand:
						this->ReadComand(r,symbols);
						break;
					case ReadType::NUL:
						throw;
						break;
				}
			}
		}

		string MT::NextStep(){
			if(n<0){
				int tmp=(-1)*n;
				n=0;
				for(int i=0; i<tmp;i++){
					word=DefaultSymbol+word;
				}
			}
			if(n>=word.size()){
				int tmp=n-word.size()+1;
				for(int i=0;i<tmp;i++){
					word=word+DefaultSymbol;
				}
			}
			if(q==final){
				return "end";
			}
			string tmp="d";
			tmp[0]=word[n];
			if(tableOfGO.find(tmp)==tableOfGO.end()){
				throw;
			}
			if(this->tableOfGO[tmp].find(q)==this->tableOfGO[tmp].end()){
				throw;
			}
			const Triple& com=this->tableOfGO[tmp][q];
			word[n]=com.Symbol()[0];
			q=com.Status();
			n+=com.Go();
			string res="";
			for(int i=0; i<word.size();i++){
				if((i==n) ||(i==(n+1))){
					res+='|';
				}
				res+=word[i];
			}
			return res;
		}

		void MT::genOutCode(CodeOuter& gen){
				gen.header();
				vector<string> sost;
				for(auto x=tableOfGO.begin();x!=tableOfGO.end();x++){
					for(auto y=(*x).second.begin();y!=(*x).second.end();y++){
						string gg=Integer::toString((*y).first);
						if(std::find(sost.begin(),sost.end(),gg)==sost.end()){
							sost.push_back(gg);
						}
						gg=Integer::toString((*y).second.Status());
						if(std::find(sost.begin(),sost.end(),gg)==sost.end()){
							sost.push_back(gg);
						}
					}
				}
				for(int i=0; i<sost.size();i++){
					sost[i]="Q"+sost[i];
				}
				gen.enumc("condition",sost);
				gen.begin();
					gen.print("Cpp generate in DP autos Tjuning\\n");
					gen.print("Write word: ");
					gen.stringc("word","");
					gen.read("word");
					gen.intc("n",gen.nullIndexStrInt());
					gen.typec("condition","q",gen.EnumPrevix("condition")+sost[0]);
					gen.whilec("true");
						string gg=gen.EnumPrevix("condition")+"Q"+Integer::toString(final);
						gen.ifc("q=="+gg);
							gen.breakc();
						gen.ifE();
						gg="B";
						gg[0]=DefaultSymbol;
						gen.ifc("n<"+gen.nullIndexStr());
							gen.typec(gen.GetType("int"),"k","(-1)*n");
							gen.assign("n","0");
							gen.forc(gen.GetType("int")+" i=0","i<k","i+=1");
								gen.assign("word","'"+gg+"' + word");
							gen.ifE();
						gen.ifE();

						gen.ifc("n >= "+gen.strLen("word"));
							gen.typec("int","tmp","n-"+gen.strLen("word")+"+1");
							gen.forc(gen.GetType("int")+" i=0","i<tmp","i+=1");
								gen.assign("word","word + '"+gg+"'");
							gen.ifE();
						gen.ifE();

						gen.switchc("word[n]");
						for(auto x=tableOfGO.begin();x!=tableOfGO.end();x++){
							if((*x).first==""){
								continue;
							}
							gen.casec("'"+(*x).first+"'");
							gen.switchc("q");
							for(auto y=(*x).second.begin();y!=(*x).second.end();y++){
								gg=Integer::toString((*y).first);
								gen.casec(gen.EnumPrevix("condition")+"Q"+gg);
								//2.10.16
								if ((*x).first !=(*y).second.Symbol())
									gen.strReplaceChar("word","n",(*y).second.Symbol()[0]);
									//gen.assign("word[n]","'"+(*y).second.Symbol()+"'");
								gg=Integer::toString((*y).second.Status());
								gen.assign("q",gen.EnumPrevix("condition")+"Q"+gg);
								gg=Integer::toString((*y).second.Go());
								gen.pr("n",gg);
				//					gen.casec("default");
				//					gen.defaultc("throw;");
								gen.caseE();
							}
							gen.caseDefault();
							gen.throwc();
							//2.10.16
							gen.caseDefEnd();
							gen.whileE();
				//				gen.casec("default");
				//				gen.defaultc("throw;");
							gen.caseE();
						}
						gen.caseDefault();
						gen.throwc();
						gen.caseDefEnd();
						gen.whileE();
					gen.whileE();
					gen.print("Out: ");
					gen.printValue("word");
				gen.end();
			}


//		void genCpp(const string &FileName){
//			GenCPP gen(FileName);
//			gen.includec("iostream");
//			gen.includec("string");
//			gen.defaultc("using namespace std;");
//			vector<string> sost;
//			for(auto x=tableOfGO.begin();x!=tableOfGO.end();x++){
//				for(auto y=(*x).second.begin();y!=(*x).second.end();y++){
//					string gg=to_string((*y).first);
//					if(std::find(sost.begin(),sost.end(),gg)==sost.end()){
//						sost.push_back(gg);
//					}
//					gg=to_string((*y).second.Status());
//					if(std::find(sost.begin(),sost.end(),gg)==sost.end()){
//						sost.push_back(gg);
//					}
//				}
//			}
//			for(int i=0; i<sost.size();i++){
//				sost[i]="Q"+sost[i];
//			}
//			gen.enumc("condition",sost);
//			gen.begin();
//			gen.print("\"Cpp generate in DP auto's Tjuning\\n\"");
//			gen.print("\"Write word: \"");
//			gen.stringc("word","\"\"");
//			gen.read("word");
//			gen.intc("n");
//			gen.defaultc("condition q = "+sost[0]+";");
//			gen.whilec("true");
//			string gg=to_string(this->final);
//			gen.ifc("q=="+gg);
//				gen.defaultc("break;");
//			gen.ifE();
//			gg=" ";
//			gen.ifc("n<0");
//				gen.defaultc("int k = (-1)*n;");
//				gen.defaultc("n=0;");
//				gen.defaultc("for (int i=0; i<k;i++){");
//					gen.levP();
//					gg[0]=this->DefaultSymbol;
//					gen.defaultc("word = '"+	gg+"' + word;");
//					gen.levM();
//				gen.defaultc("}");
//			gen.ifE();
//			gen.ifc("n>=word.size()");
//				gen.defaultc("int tmp=n-word.size()+1;");
//				gen.defaultc("for (int i=0; i<tmp;i++){");
//					gen.levP();
//
//					gen.defaultc("word = word + '"+gg+"';");
//					gen.levM();
//				gen.defaultc("}");
//			gen.ifE();
//			gen.switchc("word[n]");
//			for(auto x=tableOfGO.begin();x!=tableOfGO.end();x++){
//				if((*x).first==""){
//					continue;
//				}
//				gen.casec("'"+(*x).first+"'");
//				gen.switchc("q");
//				for(auto y=(*x).second.begin();y!=(*x).second.end();y++){
//					gg=to_string((*y).first);
//					gen.casec("Q"+gg);
//					gen.defaultc("word[n] = '"+(*y).second.Symbol()+"';");
//					gg=to_string((*y).second.Status());
//					gen.defaultc("q = Q"+gg+";");
//					gg=to_string((*y).second.Go());
//					gen.defaultc("n+="+gg+";");
////					gen.casec("default");
////					gen.defaultc("throw;");
//					gen.caseE();
//				}
//				gen.defaultc("default:");
//					gen.levP();
//					gen.defaultc("throw;");
//					gen.caseE();
//				gen.whileE();
////				gen.casec("default");
////				gen.defaultc("throw;");
//				gen.caseE();
//			}
//			gen.defaultc("default:");
//			gen.levP();
//			gen.defaultc("throw;");
//			gen.caseE();
//			gen.whileE();
//			gen.whileE();
//			gen.print("\"Out: \"");
//			gen.print("word");
//			gen.whileE();
//		}


	}
}


