/*
 * UniKey.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_SCH_VERSION_1_UNIKEY_H_
#define CRYPT_SCH_VERSION_1_UNIKEY_H_

#define __CPP__
#include "Key_v1.h"


namespace DP{
	namespace Collection{
		namespace Ver1{
			class UniKey{
				private:
					Key & _key;
					Vector<Int> _l;

				public:
					UniKey(Int start, Size_t N, Key & k);
					Int operator()();
			};
		}
	}
}


#endif /* CRYPT_SCH_VERSION_1_UNIKEY_H_ */
