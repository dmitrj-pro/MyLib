#ifndef DP_LIB_SYS_H
#define DP_LIB_SYS_H

#include <string>
#include <sstream>
#include <ostream>
#include <utility>
#include <stdexcept>

#define DP_LIB 2.2
#define DP_LIB_V2 DP_LIB

#define SET_NMSPC

#ifdef SET_NMSPC
	#ifndef __DP_LIB_NAMESPACE__
		#define __DP_LIB_NAMESPACE__ DP
	#endif
#endif

//Enable Log
//#define DP_LIB_DEBUG

#include <map>
#include <vector>

#ifdef DP_DEBUG
	#include <iostream>
#endif


namespace __DP_LIB_NAMESPACE__{
	typedef std::string String;
	typedef std::ostringstream OStrStream;
	typedef int Int;
	typedef unsigned int UInt;
	typedef char Char;
	typedef unsigned char UChar;
	typedef std::ostream Ostream;
	typedef std::exception BaseException;
	#define nr "\n"


	template <typename X, typename Y>
	using Map = std::map<X, Y>;

	template <typename T>
	using Vector = std::vector<T>;

	typedef bool Bool;

	typedef size_t Size_t;

	template <typename X, typename Y>
	using Pair = std::pair<X, Y>;

	extern String __hashe_version;
	extern String __date_version;
	inline String VERSION(){
		#define DP_VERSION_CNV(X) \
			#X
		String tmp = DP_VERSION_CNV(DP_LIB);
		tmp += "-" + __hashe_version;
		#undef DP_VERSION_CNV
		return tmp;
	}
}

#endif // SYS_H
