#pragma once

#include <Parser/Setting.h>
#include <DPLib.conf.h>
#include <Types/Exception.h>
#include <fstream>
#include <list>

using __DP_LIB_NAMESPACE__::String;
using std::ifstream;
using std::list;
using std::ofstream;

class Setting{
	private:
		__DP_LIB_NAMESPACE__::Setting _set;
	public:
		Setting(const String& file){
			ifstream input;
			input.open(file);
			if (input.fail())
				return;
			input * _set;
			input.close();
		}
		Setting(){}
		#define APPLICATION_INI "config.application"
		#define ID_INI2 "id"
		#define ID_INI "id."
		#define FOLDER_INI "config.folder"

		inline void LoadDefault(){
			_set.add(APPLICATION_INI, "sudo openvpn");
			_set.add(FOLDER_INI, "~/vpn");
		}

		inline String Application(){
			return _set.get(APPLICATION_INI);
		}

		inline String SetApplication(const String& app){
			_set.add(APPLICATION_INI, app);
			return _set.get(APPLICATION_INI);
		}

		inline String GetFromID(const String& id) {
			String tmp = ID_INI;
			tmp += id;
			return _set.get(tmp);
		}

		inline bool IfIdExists(const String & id){
			String tmp = ID_INI;
			tmp += id;
			return _set.Conteins(tmp);
		}

		inline String SetFromID(const String & id, const String & value){
			String tmp = ID_INI;
			tmp += id;
			_set.add(tmp, value);
			return _set.get(tmp);
		}
		inline list<String> GetIDS(){
			return _set.getKeys<list<String>>(ID_INI2);
		}

		inline void Open(const String & file){
			ifstream input;
			input.open(file);
			if (input.fail())
				return;
			input * _set;
			input.close();
		}

		inline void Save(const String & file){
			ofstream os;
			os.open(file);
			if (os.fail())
				throw EXCEPTION("Fail to open file");
			os << _set;
			os.close();
		}

		inline String GetFolder() {
			return _set.get(FOLDER_INI);
		}

		inline String SetFolder(const String & folder){
			_set.add(FOLDER_INI, folder);
			return _set.get(FOLDER_INI);
		}

};

