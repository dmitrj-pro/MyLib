#ifndef ISYMBOL_H_
#define ISYMBOL_H_
#include "../../DPLib.conf.h"

namespace __DP_LIB_NAMESPACE__{
	class iSymbol{
		public:
			virtual ~iSymbol(){}
			virtual String ToString()const =0;
	};
}
#endif /* ISYMBOL_H_ */
