#ifndef SCANER_SYMBOL_H_
#define SCANER_SYMBOL_H_

#include "iSymbol.h"

namespace __DP_LIB_NAMESPACE__{
	class Symbol:public iSymbol{
		private:
			Char str;
		public:
			virtual String ToString()const;
			Symbol(Char c):str(c){}
			inline Char Value()const noexcept{
				return str;
			}
	};
}

#endif /* SCANER_SYMBOL_H_ */
