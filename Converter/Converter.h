/*
 * Conv.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef LIB_CONVERTER_CONV_H_
#define LIB_CONVERTER_CONV_H_

#include "../DPLib.conf.h"
#include "../Types/Exception.h"

#ifndef LIB_TYPE_EXCEPTION_H_
    #define EXCEPTION(STR) \
        __DP_LIB_NAMESPACE__::LineException(STR, __LINE__, __FILE__)
#endif

namespace __DP_LIB_NAMESPACE__{
	class LineException;

	template<typename T>
	inline String toString(const T& v){
		OStrStream tmp;
		tmp << v;
		String res = tmp.str();
		return res;
	}

	String IntToString(Int in);

	template <typename Dict,typename Elem>
	bool ConteinsKey(const Dict & data, const Elem & key){
		for (auto x=data.begin();x!=data.end();x++)
			if ((*x).first==key)
				return true;
		return false;
	}

	template <typename Y, typename T>
	Y ElementAT(const T & list, UInt pos){
		for (auto x = list.cbegin(); x != list.cend(); x++){
			if (pos == 0)
				return *x;
			pos --;
		}
		throw EXCEPTION("Position is not found");
	}


	inline Char ByteToHex(UInt b){
        //b = b<0 ? (-1)*b : b;
		if (b < 0)
			throw EXCEPTION("Try convert negative integer");

		if ( (b >= 0) && (b < 10) )
			return (char) ('0' + b);

		switch (b) {
			case 10:
				return 'A';
				break;
			case 11:
				return 'B';
				break;
			case 12:
				return 'C';
				break;
			case 13:
				return 'D';
				break;
			case 14:
				return 'E';
				break;
			case 15:
				return 'F';
				break;
		}
		throw EXCEPTION("Try convert integer > 15");
	}

	inline Int HexToInt(Char c) {
		if ( (c <= '9') && (c >= '0') )
			return (Int) (c - '0');
		switch (c) {
			case 'A':
				return 10;
				break;
			case 'B':
				return 11;
				break;
			case 'C':
				return 12;
				break;
			case 'D':
				return 13;
				break;
			case 'E':
				return 14;
				break;
			case 'F':
				return 15;
				break;
			default:
				throw EXCEPTION("Try convert unknow symbol");
				break;
		}
	}
}

#endif /* LIB_CONVERTER_CONV_H_ */
