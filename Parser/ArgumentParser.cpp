#include "ArgumentParser.h"
#include "../Log/Log.h"
#include "../Types/Exception.h"

namespace __DP_LIB_NAMESPACE__ {
	void ArgumentParser::Load(int argc, char *argv[]){
		if (argv == nullptr)
			throw EXCEPTION("argv=NULL");
		Vector<String> params;
		for (int i = 0; i < argc ; i++){
			String str = argv[i];
			params.push_back(str);
		}

		for (int i = 0; i < params.size(); i++){
			if (ConteinsKey(_all, params[i])){
				#ifdef DP_LIB_DEBUG
					log << "Execute params '" << params[i] << "'";
					log.endl();
				#endif
				_all[params[i]](*this, i, params);
			} else {
				#ifdef DP_LIB_DEBUG
					log << "Argement '" << params[i] << "' is not found. Use '--help'";
					log.endl();
				#endif
			}
		}
	}
}
