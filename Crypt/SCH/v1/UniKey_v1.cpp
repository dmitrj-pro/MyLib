/*
 * UniKey.cpp
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#include "UniKey_v1.h"

namespace DP{
	namespace Collection{
		namespace Ver1{
			UniKey::UniKey(Int start, Size_t N, Key&k):_key(k){
				for (UInt i = 0; i < N; i++)
					_l.push_back( i + start );
			}

			Int UniKey::operator()(){
				if (_l.size() <= 0)
					return 0;
				Int i = _key() % _l.size();
				Int res = _l[i];
				_l.erase(_l.begin()+i);
				return res;
			}
		}
	}
}


