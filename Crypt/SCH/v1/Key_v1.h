/*
 * Key.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_SCH_VERSION_1_KEY_H_
#define CRYPT_SCH_VERSION_1_KEY_H_

#include "../../iKeyGen.h"

namespace __DP_LIB_NAMESPACE__{
	namespace Collection{
		namespace Ver1{
			class Key:public iKey{
				private:
					String _key;
					Int _pos;
					Int _prev;
					Int _num;
				public:
					Key(const String&key);
					virtual Int operator()();
					virtual Int operator()(Int max);
			};
		}
	}
}



#endif /* CRYPT_SCH_VERSION_1_KEY_H_ */
