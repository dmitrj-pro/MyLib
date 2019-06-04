#ifndef __APPLICATION__
#define __APPLICATION__

#include <DPLib.conf.h>
#include <list>
#include <cstdlib>
#include <iostream>
#include <Generator/CodeGenerator.h>

using __DP_LIB_NAMESPACE__::String;
using std::list;

class SimpleApplication{
	private:
		String file;
		list<String> args;
		bool is_runner = false;
	public:
		SimpleApplication(const String & file = "", const list<String>& ar = list<String>()):file(file), args(ar){}
		inline void Add(const String& str){
			args.push_back(str);
		}

		DP_add_getter_setter_name(String, file, Application)
		DP_add_getter_name(bool, is_runner, IsRun)

		inline void run(){
			String tmp=file;
			for (auto x = args.cbegin(); x != args.cend(); x++){
				tmp += " " + *x;
			}
			std::cout << "Start: " << tmp << "\n";
			system(tmp.c_str());
			is_runner = true;
		}
};

#endif
