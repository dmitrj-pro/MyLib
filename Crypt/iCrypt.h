/*
 * iCrypt.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_ICRYPT_H_
#define CRYPT_ICRYPT_H_

#include "../DPLib.conf.h"

namespace __DP_LIB_NAMESPACE__{
	class iCrypt{
		public:
			virtual ~iCrypt(){}
			virtual String Enc(const String &text)=0;
			virtual String Dec(const String &text)=0;
			virtual void SetKey(const String&key)=0;
	};
}

#endif /* CRYPT_ICRYPT_H_ */
