/*
 * Crypt.h
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#ifndef CRYPT_SCH_VERSION_1_CRYPT_H_
#define CRYPT_SCH_VERSION_1_CRYPT_H_

#define __CPP__
#include "../../iCrypt.h"
#include "Key_v1.h"


namespace __DP_LIB_NAMESPACE__{
	namespace Collection{
		namespace Ver1{
			class Crypt: public __DP_LIB_NAMESPACE__::iCrypt{
				private:
					Key _key;
					String __key;
					UInt _map_C = 0;
					typedef Vector<Int> LocalVector;

				public:
					Crypt(const String &key);
					virtual String Enc(const String & text);
					virtual String Dec(const String & text);
					virtual void SetKey(const String& key);

					LocalVector ENC_Step1(const String& str);
 					String DEC_Step1(const LocalVector& tmp);
					Int Step3_Get_Key();
					LocalVector ENC_Step2(const LocalVector & l);
					LocalVector DEC_Step2(const LocalVector & l);
					LocalVector ENC_Step3(const LocalVector & l);
					LocalVector DEC_Step3(const LocalVector & l);
					//Don't const
					LocalVector ENC_Step4(LocalVector l);
					LocalVector DEC_Step4(LocalVector l);
					String ENC_Step5(const LocalVector& l);
					LocalVector DEC_Step5(const String &str);

			};
		}
	}
}



#endif /* CRYPT_SCH_VERSION_1_CRYPT_H_ */
