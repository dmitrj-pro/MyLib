#include "Converter.h"

#include <Converter/Converter.h>
#include <Generator/CodeGenerator.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

using __DP_LIB_NAMESPACE__::toString;


void Test_To_String(){
	#define equals(X, Y)\
		Assert(X==Y, "X != Y");
	#define as(X) \
		equals(toString(X), DP_To_String(X));
	LINE
	as(1);
	LINE
	equals("sss", "sss");
	LINE
	as(-1);
	LINE
	as(-23);
	LINE
	as(355);
	LINE
	as(3.14);
	LINE
	as(-3.14);
	LINE
	as(-24.34);
	LINE
	as(355.234);
	LINE
	as(0);
	LINE


	#undef as

}

template <typename Z, typename T>
void Test_T(const T& test){
	try{
		LINE
		auto x = __DP_LIB_NAMESPACE__::ElementAT<Z>(test, -1);
		Assert(false, "Element -1 found in list");
	} catch (__DP_LIB_NAMESPACE__::LineException e){
		Assert(true, "");
	}
	{
		auto it_list = test.cbegin();
		for (int i = 0; i < test.size(); i++){
			try{
				LINE
				auto x = __DP_LIB_NAMESPACE__::ElementAT<Z>(test, i);
				Assert(x == *it_list, "Finded element is not equals");
			} catch ( __DP_LIB_NAMESPACE__::LineException e ) {
				Assert ( false, "Element from IN index not found");
			}
			it_list++;
		}
	}
	{
		auto it_list = test.rbegin();
		for (int i = test.size()-1; i >= 0; i--){
			try{
				LINE
				auto x = __DP_LIB_NAMESPACE__::ElementAT<Z>(test, i);
				Assert(x == *it_list, "Finded element is not equals");
			} catch ( __DP_LIB_NAMESPACE__::LineException e ) {
				Assert ( false, "Element from index 0..11 not found");
			}
			it_list++;
		}
	}
	try{
		LINE
		auto x = __DP_LIB_NAMESPACE__::ElementAT<Z>(test, test.size() + 1);
		Assert(false, "Finded element list.size()+1");
	} catch (__DP_LIB_NAMESPACE__::LineException e) {
		Assert(true, "");
	}
}

void Test_ElementAT(){
	std::vector<int> test{0,1,2,3,4,5,6,7,8,9,10};
	Test_T<int>(test);
	std::list<int> test2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Test_T<int>(test2);

	std::vector <__DP_LIB_NAMESPACE__::String> test3{"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	Test_T<__DP_LIB_NAMESPACE__::String>(test3);

	std::list<__DP_LIB_NAMESPACE__::String> test4{"-1", "0-1+1", "${prev}+1", "${prev}+1", "3", "Test String"};
	Test_T<__DP_LIB_NAMESPACE__::String>(test4);
}

template <typename Y, typename MAP>
void INSERTED_ConteinsKey(const MAP & m, Y (*gen)(int)){
	LINE
	for (auto x = m.cbegin(); x != m.cend(); x++){
		Assert(__DP_LIB_NAMESPACE__::ConteinsKey(m, x->first), "Conteins key is not found");
	}
	LINE
	for (int i = 0; i < COUNT_TEST; i++){
		Assert(!__DP_LIB_NAMESPACE__::ConteinsKey(m, gen(i)), "Finded not found elem");
	}
}

void Test_ConteinsKey(){
	std::map<int, int> test1;
	test1[0] = 1;
	test1[-5] = 5;
	test1[5] = 5;
	test1[3234] = 321;
	test1[43] = 3;
	INSERTED_ConteinsKey<int> ( test1, [](int i){
		return 1000+i*5;
	});

	std::map<String, int> test2;
	test2["-1"] = -1;
	test2["0"] = 0;
	test2["1"] = 1;
	test2["2"] = 2;
	test2["3"] = 3;
	test2["4"] = 4;
	test2["5"] = 45;
	INSERTED_ConteinsKey<String> (test2, [](int i){
		String tmp = "key_";
		return tmp + __DP_LIB_NAMESPACE__::toString(i);
	});

	std::unordered_map<int, int> test3;
	test3[-1] = -1;
	test3[0] = 0;
	test3[2] = 2;
	test3[53] = 54;
	test3[54] = 55;
	test3[24] = 33;
	INSERTED_ConteinsKey<int> ( test3, [](int i){
		return 1000+i*5;
	});

	std::unordered_map<String, String> test4;
	test4["-1"] = "-1";
	test4["0"] = "0";
	test4["1"] = "1";
	test4["2"] = "2";
	test4["3"] = "3";
	test4["4"] = "4";
	test4["5"] = "45";
	INSERTED_ConteinsKey<String> (test4, [](int i){
		String tmp = "key_";
		return tmp + __DP_LIB_NAMESPACE__::toString(i);
	});
}

void Test_ByteToHex(){
	for (int i = 0; i < 10; i++){
		LINE
		Assert(__DP_LIB_NAMESPACE__::ByteToHex(i) == ((__DP_LIB_NAMESPACE__::toString(i))[0]), "Converted data is not equals");
	}
	std::vector<__DP_LIB_NAMESPACE__::Char> dat {'A', 'B', 'C', 'D', 'E', 'F'};
	int i = 10;
	for (auto x = dat.cbegin(); x != dat.cend(); x++){
		LINE
		Assert(__DP_LIB_NAMESPACE__::ByteToHex(i) == (dat[i-10]), "Converted data is not equals");
		i++;
	}

	for (int i = -1; i > -20; i--){
		try{
			LINE
			__DP_LIB_NAMESPACE__::ByteToHex(i);
			Assert(false, "negative int converted");
		} catch (__DP_LIB_NAMESPACE__::LineException e){
			Assert(true, "");
		}
	}

	for (int i = 16; i < 20; i++){
		try{
			LINE
			__DP_LIB_NAMESPACE__::ByteToHex(i);
			Assert(false, "negative int converted");
		} catch (__DP_LIB_NAMESPACE__::LineException e){
			Assert(true, "");
		}
	}

}

void Test_HexToInt(){
	for (int i = 0; i < 10; i++){
		LINE
		Assert(__DP_LIB_NAMESPACE__::HexToInt((__DP_LIB_NAMESPACE__::toString(i))[0]) == i, "Converted data is not equals");
	}

	std::vector<__DP_LIB_NAMESPACE__::Char> dat {'A', 'B', 'C', 'D', 'E', 'F'};
	int i = 10;
	for (auto x = dat.cbegin(); x != dat.cend(); x++){
		LINE
		Assert(__DP_LIB_NAMESPACE__::HexToInt(dat[i-10]) == i, "Converted data is not equals");
		i++;
	}


	for (int i = -1; i > -20; i--){
		try{
			LINE
			__DP_LIB_NAMESPACE__::HexToInt((__DP_LIB_NAMESPACE__::toString(i))[0]);
			Assert(false, "negative int converted");
		} catch (__DP_LIB_NAMESPACE__::LineException e){
			Assert(true, "");
		}
	}

	std::vector<__DP_LIB_NAMESPACE__::Char> data{'Z', '-', 'K', '@', ';', '\\'};
	for (auto x = data.cbegin(); x != data.cend(); x++){
		try{
			LINE
			__DP_LIB_NAMESPACE__::HexToInt(*x);
			Assert(false, "negative int converted");
		} catch (__DP_LIB_NAMESPACE__::LineException e){
			Assert(true, "");
		}
	}
}

void Converter_Tests(){
	reset_info();
	TEST(Test_To_String);
	TEST(Test_ElementAT);
	TEST(Test_ConteinsKey);
	TEST(Test_ByteToHex);
	TEST(Test_HexToInt);
	println_info();
}
