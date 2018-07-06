/*
 * ConcreteConverter.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_CONVERTER_PRIMITIVECONVERTER_H_
#define CRYPT_CONVERTER_PRIMITIVECONVERTER_H_


#include "../iConverter.h"

namespace DP{
	namespace Converter{
		class Primitive:public iConverter{
			public:
				virtual Int ord(UChar c);
				virtual String ToHex(Int b);
				virtual Int HexToByte(const String &str);
				virtual Char sym(Int c);
		};
	}
}


#endif /* CRYPT_CONVERTER_PRIMITIVECONVERTER_H_ */
