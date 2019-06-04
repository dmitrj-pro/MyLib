#include "Config.h"
#include "Finder.h"
#include "Application.h"
#include <Parser/ArgumentParser.h>
#include <vector>
#include <cstdlib>
#include <Converter/Converter.h>
#include <iostream>
#include <Parser/SmartParser.h>

using __DP_LIB_NAMESPACE__::ArgumentParser;
using __DP_LIB_NAMESPACE__::String;
using std::vector;
using std::cout;

Setting _setting;
SimpleApplication _appl;
String _file_name = "config.dpc";

void load(const String & file){
	_setting.Open(file);
	_appl.SetApplication(_setting.Application());
}

namespace ARGC{
	void OPEN(ArgumentParser&, int& i, vector<String>& par){
		String file = par[++i];
		load(file);
		_file_name = file;
	}

	void RANDOM_FILE(ArgumentParser&, int& i, vector<String>& par){
		auto li = SetFilter(GetFiles(_setting.GetFolder()), "${name}.ovpn");
		if (li.size() == 0){
			throw EXCEPTION("Files in folder " + _setting.GetFolder() + " is not found");
		}
		auto pos = rand() % li.size();
		_appl.Add(__DP_LIB_NAMESPACE__::ElementAT<String>(li, pos));
		_appl.run();
	}

	void EementFile(ArgumentParser&, int& i, vector<String>& par){
		String file = par[++i];
		_appl.Add(file);
		_appl.run();
	}

	void Set_Folder(ArgumentParser&, int& i, vector<String>& par){
		String folder = par[++i];
		_setting.SetFolder(folder);
		_setting.Save(_file_name);
	}

	void Add(ArgumentParser&, int& i, vector<String>& par){
		String name = par[++i];
		String File = par[++i];
		_setting.SetFromID(name, File);
		_setting.Save(_file_name);
	}

	void My_List(ArgumentParser&, int& i, vector<String>& par){
		auto l = _setting.GetIDS();
		if (l.size() == 0)
			cout << "List is empty\n";
		for (auto x= l.cbegin(); x != l.cend(); x++){
			cout << *x << " = " << _setting.GetFromID(*x) << "\n";
		}
	}

	void Run(ArgumentParser&, int& i, vector<String>& par){
		String ID = par[++i];
		_appl.Add(_setting.GetFromID(ID));
		_appl.run();
	}

	void SetApplication(ArgumentParser&, int& i, vector<String>& par){
		String App = par[++i];
		_appl.SetApplication(App);
		_setting.SetApplication(App);
		_setting.Save(_file_name);
	}

	void HELP(ArgumentParser&, int& i, vector<String>& par){
		cout << "-${NAME} \t Run program with ${NAME} from list (-l) file\n\n";

		cout << "-a ${NAME} ${FILE}\t Add in my list ${NAME} with ${FILE}\n";
		cout << "--a|--add|-add\n\n";

		cout << "-s ${NAME}\t Run program with ${NAME} from list (-l) file\n";
		cout << "--s\n\n";

		cout << "-l\t Show my saved list\n";
		cout << "--l|-list|--list\n\n";

		cout << "-h\t Print this information\n";
		cout << "--help|--h|-help\n\n";

		cout << "-c ${FILE}\t Set config file ${FILE}. Default is " << _file_name << "\n";
		cout << "--c|-config|--config\n\n";

		cout << "-p ${PROGRAM}\t Set run program\n";
		cout << "--p|-program|--program\n\n";

		cout << "-R\t Run with random file\n";
		cout << "--R|-r|--r\n\n";

		cout << "-f ${FOLDER}\t Set folder with files\n";
		cout << "--f|-folder|--folder\n\n";

		cout << "-i ${FILE}\t Run program with ${FILE}\n";
		cout << "--i|-file|--file\n\n";

		cout <<"\nBase on DP Lib " << __DP_LIB_NAMESPACE__::VERSION() << " at " << __DP_LIB_NAMESPACE__::__date_version << "\n";
	}

	void INIT(ArgumentParser & par){
		par.Add("-p", SetApplication);
		par.Add("--p", SetApplication);
		par.Add("-program", SetApplication);
		par.Add("--program", SetApplication);

		par.Add("-s", Run);
		par.Add("--s", Run);

		par.Add("-a", Add);
		par.Add("--a", Add);
		par.Add("-add", Add);
		par.Add("--add", Add);

		par.Add("-l", My_List);
		par.Add("--l", My_List);
		par.Add("-list", My_List);
		par.Add("--llist", My_List);

		par.Add("-i", EementFile);
		par.Add("--i", EementFile);
		par.Add("-file", EementFile);
		par.Add("--file", EementFile);

		par.Add("-f", Set_Folder);
		par.Add("--f", Set_Folder);
		par.Add("-folder", Set_Folder);
		par.Add("--folder", Set_Folder);

		par.Add("-c", OPEN);
		par.Add("--config", OPEN);
		par.Add("-config", OPEN);
		par.Add("--c", OPEN);

		par.Add("-h", HELP);
		par.Add("--h", HELP);
		par.Add("--help", HELP);
		par.Add("-help", HELP);

		par.Add("-R", RANDOM_FILE);
		par.Add("-r", RANDOM_FILE);
		par.Add("--R", RANDOM_FILE);
		par.Add("--r", RANDOM_FILE);
	}
}

int main(int argc, char *argv[]){
	try{
		srand(time(NULL));
		ArgumentParser parser;
		ARGC::INIT(parser);
		_setting.LoadDefault();
		load(_file_name);
		parser.Load(argc, argv);

		if (!_appl.GetIsRun()){
			static __DP_LIB_NAMESPACE__::SmartParser par ("-${argv}");
			for (int i = 0 ; i < argc; i++){
				String tmp = argv[i];
				if (par.Scan(tmp)){
					String t = par.GetParam("argv");
					if (_setting.IfIdExists(t)){
						_appl.Add(_setting.GetFromID(t));
						_appl.run();
						break;
					}
				}
			}
		}
	} catch (__DP_LIB_NAMESPACE__::LineException & e){
		cout << "Exception: ";
		cout << e.toString();
	} catch (__DP_LIB_NAMESPACE__::BaseException & e){
		cout << "Exception: ";
		cout << e.what();
	}

}
