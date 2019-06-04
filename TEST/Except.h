#ifndef _DP_TEST_EXCEPT_
#define _DP_TEST_EXCEPT_

#include <Types/Exception.h>
#include <Generator/CodeGenerator.h>
#include <Parser/Smart/Exception.h>
#include <iostream>
#include <list>

using __DP_LIB_NAMESPACE__::Int;
using std::cout;
using __DP_LIB_NAMESPACE__::Pair;
using __DP_LIB_NAMESPACE__::String;
using std::list;

extern Int __all_tests;
extern Int __fail_tests;
extern Int __local_tests;
extern Int __local_fail_tests;
extern list<Pair<Int, String>> lines;

String getTree();

#define COUNT_TEST 10

#define LINE \
	(*lines.rbegin()).first = __LINE__ + 1; \
	(*lines.rbegin()).second = __FILE__;

#define SLINE(L)\
	(*lines.rbegin()).first = L; \

#define STACK \
	LINE \
	lines.push_back(Pair<Int, String>(__LINE__+1, __FILE__));

#define POP \
	if (lines.size() > 0) \
		lines.pop_back();

#define PRINT(X) \
	print(getTree()); \
	print(X);

#define PRINTLN(X) \
	print(getTree()); \
	println(X);

#define TEST(X) \
	PRINTLN(DP_To_String(X)); \
	STACK\
	X();\
	POP\



inline void _Assert(bool b, const String & mess = "Unknow", Int line=-1, const String & file = ""){
	if (!b){
		throw __DP_LIB_NAMESPACE__::LineException(mess, line, file);
	}
}

template <typename T>
inline void print(const T & x){
	cout << x;
}

template <typename T>
inline void println(const T & x){
	print (x);
	print (nr);
}

inline void print_stack(){
	PRINTLN("Call stack:");
	for (auto x = lines.rbegin(); x != lines.rend(); x++){
		PRINT("\t");
		print(x->second);
		print(": ");
		println(x->first);
	}
}

inline void println_info(){
	PRINTLN(nr);
	PRINT("Fail tests:");
	println(__local_fail_tests);
	PRINT("All tests:");
	println(__local_tests);
	println("");
}

inline void println_statistic(){
	println("");
	println("");
	PRINTLN("STATISTIC");
	PRINT("Fail tests:");
	println(__fail_tests);
	PRINT("All tests:");
	println(__all_tests);
}

inline void reset_info(){
	__local_fail_tests = 0;
	__local_tests = 0;
}

#define Assert(B, Mess) \
	try{ \
		__all_tests++; \
		__local_tests++; \
		_Assert(B, Mess, __LINE__, __FILE__); \
	} catch (__DP_LIB_NAMESPACE__::ParamsNotFound e) { \
		cout << e.what() << "\n"; \
		__fail_tests ++; \
		__local_fail_tests++; \
		print_stack(); \
	} catch (__DP_LIB_NAMESPACE__::LineException e) { \
		cout << e.toString() << "\n";\
		__fail_tests ++; \
		__local_fail_tests++; \
		print_stack(); \
	} catch (__DP_LIB_NAMESPACE__::BaseException e){ \
		cout << e.what() << "\n"; \
		__fail_tests ++; \
		__local_fail_tests++; \
		print_stack(); \
	} catch (...) { \
		cout << "SYS FAIL\n"; \
		__fail_tests ++; \
		__local_fail_tests++; \
		print_stack(); \
	}

#endif
