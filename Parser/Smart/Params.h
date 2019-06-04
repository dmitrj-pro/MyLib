#ifndef PARAMS_H_
#define PARAMS_H_

#include "iSymbol.h"

namespace __DP_LIB_NAMESPACE__{
	class Params:public iSymbol{
		private:
			String str;
			String _value="";
		public:
			virtual String ToString()const;
			Params(const String&name):str(name){}

			virtual String Value()const;
			virtual String & Value ();
			virtual String Name()const;
			virtual String SetValue(const String&str);
	};
}

#endif /* PARAMS_H_ */
