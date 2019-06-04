/*
 * iConverter.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_ICONVERTER_H_
#define CRYPT_ICONVERTER_H_

#include "../DPLib.conf.h"

namespace __DP_LIB_NAMESPACE__{
	class iConverter{
		public:
			virtual ~iConverter(){}
			virtual Int ord(UChar c)=0;
			virtual String ToHex(Int b)=0;
			virtual Int HexToByte(const String &str)=0;
			virtual Char sym(Int c)=0;
	};
}


#endif /* CRYPT_ICONVERTER_H_ */
