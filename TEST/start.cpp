#include "Crypt.h"
#include "Converter.h"
#include "Generator.h"
#include "Log.h"
#include "Parser.h"
#include <cstdlib>
#include <ctime>

void TEST_START(){
	TEST(Crypt_Tests);
	TEST(Converter_Tests);
	TEST(Generator_Tests);
	TEST(Log_Tests);
	TEST(Parser_Tests);

	println_statistic();
}

int main(){
	srand(time(NULL));
	print("Test Lib version ");
	print(DP_LIB);
	print("-");
	print(__DP_LIB_NAMESPACE__::__hashe_version);
	print(" at ");
	println (__DP_LIB_NAMESPACE__::__date_version);
	TEST(TEST_START);
}
