#define DP_DEBUG
#include "Log.h"
#include <sstream>
#include <Log/Log.h>

using std::ostringstream;
using __DP_LIB_NAMESPACE__::Log;


#define Equal(X)\
	Assert(os.str() == X, "Write is not success.");

void test_write(){
	ostringstream os;
	Log<ostringstream> log(os);
	log << 1;
	LINE
	Equal("1 ");
	LINE
	log.endl();
	Equal("1 \n");
	(log << "Test 2" ) * -4.22;
	LINE
	Equal("1 \nTest 2 -4.22\n");
}

void Log_Tests(){
	reset_info();

	TEST(test_write);

	println_info();
}
