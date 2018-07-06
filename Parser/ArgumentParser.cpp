#include "ArgumentParser.h"
#include "../Log/Log.h"

namespace DP {
	void ArgumentParser::Load(int argc, char *argv[]){
		Vector<String> params;
		for (int i = 0; i < argc ; i++){
			String str = argv[i];
			params.push_back(str);
		}

		for (int i = 0; i < params.size(); i++){
			if (DP::ConteinsKey(_all, params[i])){
				DP::log << "Execute params '" << params[i] << "'";
				DP::log.endl();
				_all[params[i]](*this, i, params);
			} else {
				DP::log << "Argement '" << params[i] << "' is not found. Use '--help'";
				DP::log.endl();
			}
		}
	}

	void ArgumentParser::Add (const String& name, function F){
		Map<String, function>& tmp = _all;
		tmp[name]=F;
	}
}