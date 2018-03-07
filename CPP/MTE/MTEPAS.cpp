/*
 * PAS.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <MTE/GenPAS.h>

namespace DP{
	namespace MTE{
		 string GenPAS::GetTab(){
			string res="";
			for(int i=0;i<level;i++){
				res+="\t";
			}
			return res;
		}
		 void GenPAS::enumc(string name, vector<string> value){
			out+=GetTab()+"type "+name+" = (";
			for(int i=0; i<value.size();i++){
				out+=value[i];
				if(i!=(value.size()-1)){
					out+=", ";
				}
			}
			out+=" );";
			out+=nr;
		}
	}
}

