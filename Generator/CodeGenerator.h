#ifndef __DP_LIB_COD_GEN_
#define __DP_LIB_COD_GEN_


#define DP_add_getter(TYPE, var) \
	inline TYPE Get##var() const {\
		return var; \
	}

#define DP_add_setter(TYPE, VAR) \
	inline TYPE Set##VAR(const TYPE & __dp_tmp_value) {\
		VAR = __dp_tmp_value; \
		return VAR; \
	}

#define DP_add_getter_setter(TYPE, VAR) \
	DP_add_getter(TYPE, VAR) \
	DP_add_setter(TYPE, VAR)

#define DP_To_String(X) \
	#X

#define DP_add_getter_name(TYPE, var, NAME) \
	inline TYPE Get##NAME() const {\
		return var; \
	}

#define DP_add_setter_name(TYPE, VAR, NAME) \
	inline TYPE Set##NAME(const TYPE & __dp_tmp_value) {\
		VAR = __dp_tmp_value; \
		return VAR; \
	}

#define DP_add_getter_setter_name(TYPE, VAR, NAME) \
	DP_add_getter_name(TYPE, VAR, NAME) \
	DP_add_setter_name(TYPE, VAR, NAME)


namespace DP {

}

#endif
