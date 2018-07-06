/*
 * Crypt.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_H_
#define CRYPT_H_

#include "iCrypt.h"

namespace DP{
	class Crypt:public iCrypt{
		private:
			String key;
			Int version;
		public:
			Crypt();
			Crypt(const String&key, const String &name);
			virtual String Enc(const String &test);
			virtual String Dec(const String &text);
			virtual void SetKey(const String&key){
				this->key=key;
			}
	};
}



#endif /* CRYPT_H_ */
