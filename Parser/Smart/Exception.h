#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "iSymbol.h"
#include "../../Types/Exception.h"

namespace __DP_LIB_NAMESPACE__{
    class ParamsNotFound:public LineException{
		public:
            ParamsNotFound(const String& str):LineException(str, __LINE__, __FILE__){}
	};

    class PharserFailure:public LineException{
		public:
            PharserFailure(const String& str):LineException(str, __LINE__, __FILE__){}
	};
}

#endif /* EXCEPTION_H_ */
