#ifndef LIB_TYPE_EXCEPTION_H_
#define LIB_TYPE_EXCEPTION_H_

#include "../DPLib.conf.h"

namespace DP{
	class Exception{
		private:
			String _str;

		public:
			Exception(const String & str):_str(str){}
			virtual inline String what()const{
				return _str;
			}
			virtual ~Exception(){}
	};
}


#endif /* LIB_TYPE_EXCEPTION_H_ */
