#include "Params.h"

namespace __DP_LIB_NAMESPACE__{
	String Params::ToString()const{
		return _value;
	}
	String Params::Value()const{
		return _value;
	}
	String& Params::Value(){
		return _value;
	}
	String Params::Name()const{
		return str;
	}
	String Params::SetValue(const String&str){
		_value=str;
		return str;
	}
}

