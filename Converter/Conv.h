/*
 * Conv.h
 *
 *  Created on: 11 июн. 2017 г.
 *      Author: diman-pro
 */

#ifndef LIB_CONVERTER_CONV_H_
#define LIB_CONVERTER_CONV_H_

#include <sstream>
#include <string>


namespace DP{
	namespace Converter{
		template<typename T>
		std::string toString(const T& v){
			std::ostringstream tmp;
			tmp<<v;
			std::string res=tmp.str();
			return res;
		}
	}
}



#endif /* LIB_CONVERTER_CONV_H_ */
