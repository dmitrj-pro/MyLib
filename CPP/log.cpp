/*
 * log.cpp
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#include <Log/log.h>

namespace DP{
		Log::Log(char* File){
			f.open(File);
		}
		bool Log::Open(const char*&File){
			if(f.is_open()){
				f.close();
			}
			f.open(File);
			return f.is_open();
		}
		void Log::write(char* Word){
			f<<Word;
		}
		void Log::writeln(char* Word){
			this->write(Word);
			this->write("\n");
		}
		Log::~Log(){
			f.close();
		}
		void Log::close(){
			if(f.is_open()){
				f.close();
			}
		}

}


