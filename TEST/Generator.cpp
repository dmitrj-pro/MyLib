#include "Generator.h"
#include <Generator/CodeGenerator.h>

using __DP_LIB_NAMESPACE__::String;

class TestClass_CODE_GEN{
	private:
		int Pos;
	public:
		int P2;
		DP_add_getter_setter(int, Pos)
		DP_add_getter_setter_name(int, Pos, Pos2)

		DP_add_getter(int, P2)
		DP_add_getter_name(int, P2, P22)

		String P3;
		DP_add_setter(String, P3)
		DP_add_setter_name(String, P3, P33)
};

#define Equals(X, Y) \
	Assert(X == Y, "Element is not equals");

void Test_getter_setter(){
	TestClass_CODE_GEN test;
	test.SetPos(12);
	LINE
	Equals(test.GetPos(), 12);
	test.SetPos(-12);
	LINE
	Equals(test.GetPos(), -12);
	test.SetPos(543);
	LINE
	Equals(test.GetPos(), 543);
}

void Test_getter_setter_name(){
	TestClass_CODE_GEN test;
	test.SetPos2(12);
	LINE
	Equals(test.GetPos2(), 12);
	test.SetPos2(-12);
	LINE
	Equals(test.GetPos2(), -12);
	test.SetPos2(543);
	LINE
	Equals(test.GetPos2(), 543);
}

void Test_getter(){
	TestClass_CODE_GEN test;
	test.P2=1;
	LINE
	Equals(test.GetP2(), 1);
	test.P2 = -2344;
	LINE
	Equals(test.GetP2(), -2344);
	test.P2 = 23;
	LINE
	Equals(test.GetP2(), 23);
}

void Test_getter_name(){
	TestClass_CODE_GEN test;
	test.P2=1;
	LINE
	Equals(test.GetP22(), 1);
	test.P2 = -2344;
	LINE
	Equals(test.GetP22(), -2344);
	test.P2 = 23;
	LINE
	Equals(test.GetP22(), 23);
}

void Test_setter(){
	TestClass_CODE_GEN test;
	test.SetP3("23");
	LINE
	Equals("23", test.P3);
	test.SetP3("234554354325tdfg");
	LINE
	Equals("234554354325tdfg", test.P3);
}

void Test_setter_name(){
	TestClass_CODE_GEN test;
	test.SetP33("23");
	LINE
	Equals("23", test.P3);
	test.SetP33("234554354325tdfg");
	LINE
	Equals("234554354325tdfg", test.P3);
}

void Generator_Tests(){
	reset_info();

	TEST(Test_getter_setter);
	TEST(Test_getter_setter_name);
	TEST(Test_getter);
	TEST(Test_getter_name);
	TEST(Test_setter);
	TEST(Test_setter_name);

	println_info();
}
