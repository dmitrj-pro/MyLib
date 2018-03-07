/*
 * Driver.h
 *
 *  Created on: 17 мая 2017 г.
 *      Author: diman-pro
 */

#include <DPLib.conf.h>

#ifdef DP_LINUX
#ifndef NET_LINUX_DRIVER_H_
#define NET_LINUX_DRIVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <thread>
#include <string>
#include <vector>

#define DEBUG



#ifdef DEBUG
#include <iostream>
#include <stdio.h>
#endif


namespace DP{
	namespace NET{
		namespace Server{
			typedef  std::string String;
			typedef std::thread Thread;
			typedef std::vector<Thread*> Vector;

			class Error{
				private:
					String str;
				public:
					Error(const String& str):str(str){}
					String about (){ return str; }
			};

			class Server{
				private:
					int lisen;
					bool isRun=true;
				public:
					inline Server():lisen(-1){}
					//Begin Listen IP:port with function proc. Server
					//create new thread for proc.
					template<typename T>
					void ThreadListen(String IP, size_t port, T proc);
					//Begin Listen IP:port with function proc. Server no
					//create new thread for proc.
					template<typename T>
					void Listen(String IP, size_t port, T proc);
					//Send user id 'client' data ans
					static void Send(int client, const String& ans);
					//Read user question before input del
					static String Read(int Client,char del='\r');
					//Close Client
					static void CloseClient(int C);
					//Close Server
					void exit();

			};


			//ToDo
			template<typename T>
			void Server::ThreadListen(String IP, size_t port, T proc){
				isRun=true;
				struct sockaddr_in serverAddress;
				lisen= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				int turnOn = 1;
				if (setsockopt(lisen, SOL_SOCKET, SO_REUSEADDR, &turnOn, sizeof(turnOn)) == -1)
					throw Error("Set Socket Fail");
				serverAddress.sin_family = AF_INET;
				serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
				serverAddress.sin_port = htons(port);
				int errn=bind( lisen, (sockaddr *) &serverAddress, sizeof(serverAddress));
				if (errn == -1){
					#ifdef DEBUG
						perror("Bind failed:");
					#endif
					throw Error("Bind failed:");
				}
				if (listen(lisen, 1000) == -1)
					throw Error("listen failed:");
				Vector data;
				while(isRun){
					int *clientSocket = new int[1];
					*clientSocket = accept(lisen, NULL, NULL);
					if (*clientSocket < 0)
						throw Error("accept failed");
					Thread * t =new Thread(proc,*clientSocket);
					data.push_back(t);
				}
				for (int i=0;i<data.size();i++){
					data[i]->join();
				}
			}

			template<typename T>
			void Server::Listen(String IP, size_t port, T proc){
				isRun=true;
				struct sockaddr_in serverAddress;
				lisen= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				int turnOn = 1;
				if (setsockopt(lisen, SOL_SOCKET, SO_REUSEADDR, &turnOn, sizeof(turnOn)) == -1)
					throw Error("Set Socket Fail");
				serverAddress.sin_family = AF_INET;
				serverAddress.sin_addr.s_addr = inet_addr(IP.c_str());
				serverAddress.sin_port = htons(port);
				if (bind( lisen, (sockaddr *) &serverAddress, sizeof(serverAddress)) == -1){
					#ifdef DEBUG
						perror("Bind failed:");
					#endif
					throw Error("bind failed");
				}
				if (listen(lisen, 1000) == -1)
					throw Error("listen failed:");
				while(isRun){
				    int *clientSocket = new int[1];
				    *clientSocket = accept(lisen, NULL, NULL);
				    if (*clientSocket < 0)
				    	throw Error("accept failed");
				    proc(*clientSocket);
				}
			}

		}
	}
}
#endif /* NET_LINUX_DRIVER_H_ */

#endif
