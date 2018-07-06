#ifndef DP_LIB_SYS_H
#define DP_LIB_SYS_H

#include <string>
#include <sstream>
#include <ostream>
#include <utility>

#define DP_V2

#ifdef __CPP__
	#include <map>
	#include <vector>
#endif

#ifdef DP_DEBUG
	#include <iostream>
#endif


namespace DP{
	typedef std::string String;
	typedef std::ostringstream OStrStream;
	typedef int Int;
	typedef unsigned int UInt;
	typedef char Char;
	typedef unsigned char UChar;
	typedef std::ostream Ostream;
	#define nr "\n"
	
	#ifdef __CPP__
		template <typename X, typename Y>
		using Map = std::map<X, Y>;

		template <typename T>
		using Vector = std::vector<T>;

		typedef bool Bool;

		typedef size_t Size_t;
	#endif
	template <typename X, typename Y>
	using Pair = std::pair<X, Y>;

	extern String __hashe_version;
	extern String __date_version;
}

#endif // SYS_H
