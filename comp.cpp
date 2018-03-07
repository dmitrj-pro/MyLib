/*
 * comp.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */
#include <cstdlib>
#include <vector>
#include <string>

using std::vector;
using std::string;

inline vector<string> getData(){
	vector<string> res;
	res.push_back("CPP/NET/Server/Linux/Driver.cpp");
	res.push_back("CPP/log.cpp");

	res.push_back("CPP/MTE/MTECPP.cpp");
	res.push_back("CPP/MTE/MTEPAS.cpp");
	res.push_back("CPP/MTE/MTEMTE.cpp");
	res.push_back("CPP/MTE/MTEJS.cpp");
	
	res.push_back("CPP/Thread/Manager.cpp");
	return res;
}


int main(){
	{
		string tmp="g++ -fpic -c -std=c++11 -I./";
		vector<string> tmpv=getData();
		for (int i=0; i<tmpv.size();i++){
			tmp+=" "+tmpv[i];
		}
		system(tmp.c_str());
	}
	system("ar rc lib.a *.o");
	system("rm -f *.o");
}
