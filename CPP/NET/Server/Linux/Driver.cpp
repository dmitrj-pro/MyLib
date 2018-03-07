/*
 * Driver.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <NET/Server/Driver.h>

#ifdef DP_LINUX

namespace DP{
	namespace NET{
		namespace Server{
			void Server::Send(int client, const String& ans){
				send( client,  &ans[0], ans.size(), 0 );
			}
			String Server::Read(int Client, char del){
			    int err=10;
			    char Buf=0;
			    String query;
			    while (err > 0 && Buf != del){
			    	if (Buf!=0)
			    		query+=Buf;
			    	err = recv(Client, &Buf, 1, 0);

			    }
			    if (err < 0)
			    	throw Error("recv failed");
			    if (err == 0) return ""; //клиент разорвал соединение
//			    recv(Client, &Buf, 1, 0); // получаем \n
				#ifdef DEBUG
			    	std::cout << "Data received: " << query << "\n";
				#endif
			    return query;
			}
			void Server::CloseClient(int C){
				close(C);
			}
			void Server::exit(){
				isRun=false;
			}


		}
	}
}


#endif
