#ifndef LIB_CPP_PARSER_SETTING_H_
#define LIB_CPP_PARSER_SETTING_H_

#include "../Types/MemoryManager.h"
#include "../DPLib.conf.h"
#include "SmartParser.h"
#include "../Converter/Converter.h"



namespace DP{
	class Setting{
		private:
			typedef Pair<String, String*> MyPair;
			Map<String, String> _data;
			Int & links;
			Map<String,Setting*> _node;
			DP::MemoryManager mem;

			MyPair parseKey(const String & key)const;

			template<typename Cout>
			Cout& cout(Cout&os, const String & prefix)const {
				os << "[" << prefix << "]" << nr;
				for (auto x = _data.begin(); x != _data.end(); x++)
					os << x-> first << "=" << x->second << nr;

				for (auto x = _node.begin(); x != _node.end(); x++){
					String tmp = prefix + ".";
					tmp += x->first;
					x->second->cout(os,tmp);
				}
				return os;
			}
			template<typename Cin>
			Cin& cin(Cin& os){
				DP::SmartParser Value{"${name}=${value}"};
				DP::SmartParser Head{"[.${name}]"};
				String Prefix="";
				while (!os.eof()){
					String str;
					getline(os, str);
					if (Value.Scan(str)){
						String tmp = Prefix;
						tmp += Value.GetParam("name");
						add(tmp, Value.GetParam("value"));
						continue;
					}
					if (Head.Scan(str)){
						Prefix = Head.GetParam("name")+".";
						continue;
					}
				}
				return os;
			}
		public:
			Setting():links(*(new int(0))){}
			Setting(const Setting& s):_data(s._data), links(s.links),_node(s._node){ links++; }

			bool Conteins(const String& key);
			void Clear();
			inline ~Setting(){
				links--;
				if (links == 0)
					Clear();
			}
			String get(const String& key);
			void add(const String&key, const String&value);
			template<typename Vect>
			Vect getKeys(const String&key=""){
				MyPair map=parseKey(key);
				if (map.second==nullptr){
					if (DP::ConteinsKey(_node,key)){
						Vect res;
						for (auto x=_node[key]->_data.begin(); x!=_node[key]->_data.end(); x++)
							res.push_back((*x).first);
						return res;
					} else
						return Vect();
				} else 
					return _node[map.first]->getKeys<Vect>(*(map.second));
			}
			template<typename Vect>
			Vect getFolders(const String&key=""){
				MyPair map=parseKey(key);
				if (map.second==nullptr){
					if (DP::ConteinsKey(_node,key)){
						Vect res;
						for (auto x = _node[key]->_node.begin(); x != _node[key]->_node.end(); x++)
							res.push_back((*x).first);
						return res;
					} else
						return Vect();
				} else 
					return _node[map.first]->getFolders<Vect>(*(map.second));
			}
			template <typename OSTream>
			inline friend Ostream& operator<<(OSTream&os, const Setting& s){
				String str="";
				return s.cout(os,str);
			}
			template <typename ISTream>
			inline friend ISTream& operator*(ISTream&os, Setting&set){
				set.cin(os);
				return os;
			}

	};
}



#endif /* LIB_CPP_PARSER_SETTING_H_ */
