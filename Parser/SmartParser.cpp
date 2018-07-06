#include "SmartParser.h"
#include "Smart/Exception.h"

namespace DP{
	SmartParser::SmartParser(const String&str){
		bool name = false;
		String tmp;
		for (int i = 0; i < str.size();i++){
			if (str[i] == '$'){
				name = true;
				continue;
			}
			if (name) {
				if (str[i] == '}'){
					name = false;
					sym.push_back(&memory.getMem<Params>(tmp));
					continue;
				}
				if (str[i] == '{'){
					tmp = "";
					continue;
				}
				tmp += str[i];
				continue;
			}
			sym.push_back(&memory.getMem<Symbol>(str[i]));
		}
	}

	String SmartParser::ToString()const{
		String str = "";
		for (int i = 0; i < sym.size(); i++)
			str += sym [i]->ToString ();
		return str;
	}

	String SmartParser::GetParam(const String &str)const throw (DP::ParamsNotFound){
		for (int i=0; i < sym.size(); i++){
			Params* tmp = dynamic_cast<Params*>(sym[i]);
			if (tmp == nullptr)
				continue;
			if (tmp->Name() == str)
				return tmp->Value();
		}
		throw DP::ParamsNotFound(str);
	}

	void SmartParser::SetParam(const String &param, const String & value) throw (DP::ParamsNotFound){
		for (int i = 0; i < sym.size(); i++){
			Params* tmp = dynamic_cast<Params*>(sym[i]);
			if (tmp == nullptr)
				continue;
			if (tmp->Name() == param)
				tmp->Value() = value;
		}
		throw DP::ParamsNotFound(param);
	}

	bool SmartParser::existParam(const String& str)const{
		for (int i = 0; i < sym.size();i++){
			Params* tmp=dynamic_cast<Params*>(sym[i]);
			if (tmp==nullptr)
				continue;
			if (tmp->Name()==str)
				return true;
		}
		return false;
	}

	Vector<String> SmartParser::GetAllParamsName()const{
		Vector<String> res;
		for (int i = 0; i < sym.size();i++){
			Params* tmp = dynamic_cast<Params*>(sym[i]);
			if (tmp == nullptr)
				continue;
			res.push_back(tmp->Name());
		}
		return res;
	}

	Vector<String> SmartParser::GetParamsValues()const{
		Vector<String> res;
		for (int i = 0; i < sym.size(); i++){
			Params* tmp=dynamic_cast<Params*>(sym[i]);
			if (tmp == nullptr)
				continue;
			res.push_back(tmp->Value());
		}
		return res;
	}

	inline bool isSymbol(SmartParser::ISymbol* sym){
		auto x=dynamic_cast<SmartParser::Symbol*>(sym);
		return x!=nullptr;
	}

	inline bool Equal(Char t, SmartParser::Symbol* x){
		if (x->Value() == '?')
			return true;
		if (x->Value() == '*')
			return true;
		return t==x->Value();
	}

	bool SmartParser::StartScan(const String &str, int StringIterator, Vect &list,int ListIterator)throw(DP::PharserFailure) {
		if (StringIterator >= str.length()) {
			if (ListIterator >= list.size()) {
				sym = list;
				return true;
			}
			if (ListIterator == (list.size()-1) && (!isSymbol(list [ListIterator]))){
				sym = list;
				return true;
			}
			return false;
		}
		if (ListIterator >= list.size())
			return false;
		if (isSymbol(list [ListIterator])) {
			SmartParser::Symbol* sym=(SmartParser::Symbol*)list [ListIterator];
			if ((str [StringIterator] == sym->Value()) || (sym->Value() == '?')) {
				bool t = StartScan (str, StringIterator + 1, list, ListIterator + 1);
				if (t)
					return t;
			}
			if (sym->Value() == '*') {
				for (int i = StringIterator; i < str.length(); i++) {
					bool t = StartScan (str, i, list, ListIterator + 1);
					if (t)
						return t;
				}
			}
			return false;
		} else {
			SmartParser::Params* par=(SmartParser::Params*)list [ListIterator];
			if ((ListIterator + 1) == list.size()) {
				par->SetValue(str.substr(StringIterator));
				sym = list;
				return true;
			}
			String tmp = "";
			for (int i = StringIterator; i < str.length(); i++) {
				if (!isSymbol(list [ListIterator+1]))
					throw DP::PharserFailure("Unexpected parameter");
				SmartParser::Symbol* sym=(SmartParser::Symbol*)list [ListIterator+1];
				if (str [i] == sym->Value()) {
					par->SetValue(tmp);
					bool t = StartScan (str, i+1, list, ListIterator + 2);
					if (t)
						return t;
					par->SetValue("");
				}
				tmp += str [i];
			}
		}
		return false;
	}
}