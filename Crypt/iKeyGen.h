/*
 * iKeyGen.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_IKEYGEN_H_
#define CRYPT_IKEYGEN_H_

#include "../DPLib.conf.h"

namespace DP{
	class iKey{
		public:
			virtual ~iKey(){}
			virtual Int operator()()=0;
			virtual Int operator()(int max)=0;
	};
}

#endif /* CRYPT_IKEYGEN_H_ */
