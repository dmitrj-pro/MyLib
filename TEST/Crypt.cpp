#include "Crypt.h"
#include <iostream>
#include <Crypt/Crypt.h>
#include <list>

using std::cout;
using std::list;
using __DP_LIB_NAMESPACE__::Crypt;


#define assert(B) \
	Assert(B, "Original != Decrypt")

#define TEST0(CR1, CR2, TXT) \
	{ \
		auto t1 = CR1.Enc(TXT); \
		auto t2 = CR2.Enc(TXT); \
		assert(t1==t2); \
		auto o1 = CR1.Dec(t1); \
		assert(o1 == CR2.Dec(t2)); \
		assert(o1 == TXT); \
	}

#define TEST1(CR, Pass, TYPE) \
	{ \
		STACK \
		Crypt __sddds (Pass, TYPE); \
		SLINE(27) \
		TEST0(CR, __sddds, "TEST_MESSAGE") \
		SLINE(29) \
		TEST0(CR, __sddds, "TEST_MESSAGE С русским текстом") \
		SLINE(31) \
		TEST0(CR, __sddds, "Проверьте, пожалуйста, возможность просмотра в более ранней версии приложения MegaFon.TV по следующей ссылке:\nhttps://drive.google.com/open?id=0B04DpmOu-qyqel9zMFNWdG1mRkE\nУстановленное ранее приложение необходимо удалить. Автообновление приложений в Play Маркет нужно будет отключить.") \
		POP \
	}

#define TEST2(Pass, Type) \
	{\
		Crypt d1(Pass, Type); \
		TEST1(d1, Pass, Type); \
	}


void SCH5_TESTS(){
	LINE
	TEST2("Oass:", "SCH5");

	LINE
	TEST2("Oadfsgdfsgdfgfgss:", "SCH5");
}

void Crypt_Tests(){
	reset_info();
	TEST(SCH5_TESTS);

	println_info();
}
