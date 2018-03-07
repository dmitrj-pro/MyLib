/*
 * log.h
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#ifndef LIB_LOG_LOG_H_
#define LIB_LOG_LOG_H_

#include <fstream>

#define FILE std::ofstream


namespace DP{
	class Log{
		private:
			FILE f;
		public:
			Log(){}
			Log(char* File);
			bool Open(const char*&File);
			void write(char* Word);
			void writeln(char* Word);
			~Log();
			void close();

	};
}


#endif /* LIB_LOG_LOG_H_ */
