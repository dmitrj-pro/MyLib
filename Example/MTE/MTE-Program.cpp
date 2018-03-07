//============================================================================
// Name        : MTE.cpp
// Author      : Diman PRO
// Version     :
// Copyright   : ©Diman PRO 2015.  All rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <MTE/MTE.h>
#include <MTE/generatorCPP.h>
#include <MTE/GenPAS.h>

using std::cout;
using std::cin;

using DP::MTE::GenCPP;
using DP::MTE::GenPAS;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
enum class ParamsType{NIL, Comand, Parametr};
int main(int argc, char** argv) {
	string FileName="";
	string OutCPPFile="";
	string OutPASFile="";
	string word="";
	bool Debug=false;
	bool Scanning=false;
	DP::MTE::MT car;
	for(int i=1;i<argc;i++){
		string com=argv[i];
		if(com=="-f"){
			i++;
			FileName=argv[i];
			continue;
		}
		if (com=="-cpp"){
			i++;
			OutCPPFile=argv[i];
			continue;
		}
		if (com=="-pas"){
			i++;
			OutPASFile=argv[i];
			continue;
		}
		if (com=="-word"){
			i++;
			word=argv[i];
			continue;
		}
		if (com=="-d"){
			Debug=true;
			continue;
		}
		if (com=="-s"){
			Scanning=true;
			continue;
		}
		if(com=="-version"){
			cout<<car.version()<<nr;
			continue;
		}
	}
	cout<<"Auto names Tjuring\nAutor Dmitrij Proskurin 2016\n";
	if(FileName==""){
		cout<<"Input File Name:";
		cin>>FileName;
	}
	car.Load(FileName);
	if(OutCPPFile!=""){
		DP::MTE::GenCPP g=GenCPP(OutCPPFile);
		car.genOutCode(g);
		g.close();
		cout<<"CPP file Created\n";
	}
	if(OutPASFile!=""){
		DP::MTE::GenPAS g1=GenPAS(OutPASFile);
		car.genOutCode(g1);
		g1.close();
		cout<<"PAS file Created\n";
	}
	if(word==""){
		cout<<"Input word:";
		cin>>word;
	}
	//car.print();
	if(Debug){
		car.setWord(word);
		word=car.NextStep();
		cout<<"Debug start.\n";
		while(word!="end"){
			cout<<word<<"\tq="<<car.getQ()<<"\n";
			word=car.NextStep();
		}
	} else {
		if(Scanning){
			cout<<"Scan result is "<<car.ScanWord(word)<<"\n";
		} else {
			cout<<"New word is "<<car.runOnWord(word)<<"\n";
		}
	}


	return 0;
}
