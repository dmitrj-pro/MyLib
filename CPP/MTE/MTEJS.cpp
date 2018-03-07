/*
 * MTEJS.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <MTE/GenJS.h>
#include <Converter/Conv.h>

namespace DP{
	namespace MTE{
		 string GenJS::GetTab(){
			string res="";
			for(int i=0;i<level;i++){
				res+="\t";
			}
			return res;
		}
		 void GenJS::enumc(string name, vector<string> value){
			 out+=GetTab()+"var "+name+" = {"+nr;
			 level++;
			for(int i=0; i<value.size();i++){
				out+=GetTab()+value[i]+" : "+DP::Converter::toString(i);
				if(i!=(value.size()-1)){
					out+=",";
				}
				out+=nr;
			}
			level--;
			out+=GetTab()+"};"+nr;
		}
	}
}


