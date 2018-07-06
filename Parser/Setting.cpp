#include "Setting.h"

namespace DP{
	void Setting::Clear(){
		for (auto x=_node.begin();x!=_node.end();x++)
			mem.erase(x->second);
		_node.clear();
		_data.clear();
	}
	Setting::MyPair Setting::parseKey(const String & key)const{
		DP::SmartParser par("${first}.${last}");
		MyPair res("",nullptr);
		if (par.Scan(key)){
			res.first=par.GetParam("first");
			res.second=new String(par.GetParam("last"));
			return res;
		} else {
			res.first=key;
			return res;
		}
	}
	void Setting::add(const String&key, const String&value){
		MyPair map=parseKey(key);
		if (map.second==nullptr){
			if (DP::ConteinsKey(_data,key)){
				_data[key]=value;
			} else {
				_data[key]=value;
			}
		} else {
			if (!DP::ConteinsKey(_node,map.first))
				_node[map.first]=&mem.getMem<Setting>();
			_node[map.first]->add(*(map.second),value);
		}
	}
	String Setting::get(const String& key) {
		MyPair map=parseKey(key);
		if (map.second==nullptr){
			if (DP::ConteinsKey(_data,key)){
				return _data[key];
			} else
				return "";
		} else {
			if (DP::ConteinsKey(_node,map.first)){
				return _node[map.first]->get(*(map.second));
			} else
				return "";
		}
	}
	bool Setting::Conteins(const String& key) {
		MyPair map=parseKey(key);
		if (map.second==nullptr){
			return DP::ConteinsKey(_data,key);
		} else {
			if (DP::ConteinsKey(_node,map.first)){
				return _node[map.first]->Conteins(*(map.second));
			} else
				return false;
		}
	}
}