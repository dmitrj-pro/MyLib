#include "Finder.h"
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <Parser/SmartParser.h>

using std::cout;

list <String> GetFiles(const String & folder){
	DIR *dp;
	struct dirent *dent;

	if( (dp = opendir(folder.c_str())) == NULL) {
		cout << "opendir: " << folder << "\n";
		return list<String>();
	}
	list<String> all;
	while(dent = readdir(dp))
		if(strcmp(".", dent->d_name) && strcmp("..", dent->d_name))
			all.push_back(dent->d_name);
	closedir(dp);
	return all;
}

list<String> SetFilter(const list<String> & data, const String& filter){
	static __DP_LIB_NAMESPACE__::SmartParser par(filter);

	list<String> res;
	for (auto x = data.cbegin(); x != data.cend(); x++){
		if (par.Scan(*x)){
			res.push_back(*x);
		}
	}
	return res;
}
