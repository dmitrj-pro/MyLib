#include "Except.h"

Int __all_tests;
Int __fail_tests;
Int __local_tests;
Int __local_fail_tests;
list<Pair<Int, String>> lines = list<Pair<Int, String>>();

String getTree(){
	String res = "";

	for (auto x = lines.rbegin(); x != lines.rend(); x++){
		res += "\t";
	}
	return res;
}
