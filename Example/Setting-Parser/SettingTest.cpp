/*
 * SettingTest.cpp
 *
 *  Created on: 22 июл. 2017 г.
 *      Author: diman-pro
 */
#include <Parser/Setting.h>

#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::ifstream;

int main(){
	DP::Setting set;
	set.add("root.sys","rootSys");
	set.add("my","my1");
	set.add("my","my2");
	set.add("myVal","value");
	set.add("root.System.DP.Core.Lib.nr","NewLine");
	cout << set << "\n\n";
	set.Clear();
	ifstream f;
	f.open("setting.txt");
	f*set;
	cout<<set;

}



