/*
 * Conv.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef LIB_CONVERTER_CONV_H_
#define LIB_CONVERTER_CONV_H_

#include "../DPLib.conf.h"

namespace DP{
	template<typename T>
	String toString(const T& v){
		OStrStream tmp;
		tmp << v;
		String res = tmp.str();
		return res;
	}

	template<typename T>
	String toStringWithNull(const T& v){
		OStrStream tmp;
		tmp << v;
		String res = tmp.str();
		return res;
	}

	template <typename Dict,typename Elem>
	bool ConteinsKey(const Dict & data, const Elem & key){
		for (auto x=data.begin();x!=data.end();x++)
			if ((*x).first==key)
				return true;
		return false;
	}
}

#endif /* LIB_CONVERTER_CONV_H_ */
