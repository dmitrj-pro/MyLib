/*
 * MTE-Server.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <MTE/MTE.h>
#include <MTE/GenJS.h>
#include <NET/Server/Driver.h>

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using DP::NET::Server::Server;

class Serv{
	private:
		DP::NET::Server::Server srv;
	public:
		Serv(string Ip,size_t port){
			srv.ThreadListen(Ip,port,*this);
		}
		void operator()(int Cl){
			Server::Send(Cl,DP::MTE::MT::version()+"\n");
			string data;
			bool t=false;
			while (true){
				string tmp=Server::Read(Cl,'\r');
				Server::Read(Cl,'\n');
				if (tmp==""){
					std::cout<<"OK\n";
					if (t)
						break;
					else
						t=true;
					continue;
				}
				data+=tmp+"\n";
				t=true;
			}
			DP::MTE::MT m;
			std::cout<<data;
			try{
				m.LoadFromString(data);
				std::cout<<"Parsed\n";
			} catch(...){
				Server::Send(Cl,"Error");
			}
			try{
			DP::MTE::GenJS js{"tmp.js"};
			m.genOutCode(js);
			js.close();
			} catch(...){

			}
			std::cout<<"Compiled\n";
			ifstream f;
			f.open("tmp.js");
			while (!f.eof()){
				string str;
				getline(f,str);
				Server::Send(Cl,str+"\n");
			}
			f.close();
			Server::CloseClient(Cl);
			std::cout<<"End\n";
		}
};

int main(){
	std::cout<<"Start\n";
	Serv t{"127.0.0.1", 44};
	std::cout<<"End";
}


