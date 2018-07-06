#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "iSymbol.h"
#include "../../Types/Exception.h"

namespace DP{
	class ParamsNotFound:public Exception{
		public:
			ParamsNotFound(const String& str):Exception(str){}
	};

	class PharserFailure:public Exception{
		public:
			PharserFailure(const String& str):Exception(str){}
	};
}

#endif /* EXCEPTION_H_ */