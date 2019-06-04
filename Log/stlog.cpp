#ifndef STLOG_H
#define STLOG_H

#include "Log.h"

namespace __DP_LIB_NAMESPACE__ {
	#ifdef DP_DEBUG
		Log<Ostream> log = Log<Ostream>(std::cout);
	#endif
	#ifndef DP_DEBUG
		Log<Ostream> log;
	#endif
	bool isError = false;
}

#endif // STLOG_H
