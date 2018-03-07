/*
 * CPP.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <MTE/generatorCPP.h>

namespace DP{
	namespace MTE{
		 string GenCPP::GetTab(){
			string res="";
			for(int i=0;i<level;i++){
				res+="\t";
			}
			return res;
		}
		 void GenCPP::enumc(string name, vector<string> value){
			out+=GetTab()+"enum "+name+" {";
			for(int i=0; i<value.size();i++){
				out+=value[i];
				if(i!=(value.size()-1)){
					out+=", ";
				}
			}
			out+=" };";
			out+=nr;
		}
	}
}


