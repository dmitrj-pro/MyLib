/*
 * Crypt.cpp
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#define __CPP__

#include "../DPLib.conf.h"
#include "Crypt.h"
#include "iCrypt.h"
#include "../Types/Exception.h"

#include "SCH/v1/Crypt_v1.h"


namespace __DP_LIB_NAMESPACE__{
	//Global
	Map<Int, String> table_crypt;
	Map<Int, iCrypt*> ListCrypt;


	Int ID(const String &name){
		for (auto x = table_crypt.begin(); x != table_crypt.end(); x++)
			if (x->second==name)
				return x->first;
		throw EXCEPTION("Types crypt is not found");
	}

	String NameCrypt(Int id){
		for (auto x = table_crypt.begin(); x != table_crypt.end(); x++)
			if (x->first == id)
				return x->second;
		throw EXCEPTION("Types crypt is not found");
	}

	void AddCrypt(iCrypt&cr, const String & name) {
		auto n = table_crypt.size();
		table_crypt[n] = name;
		ListCrypt[n] = &cr;
	}

	iCrypt& getCrypt(const String & name){
		auto id = ID(name);
		return *ListCrypt[id];
	}

	iCrypt& getCryptfromId(Int id){
		return *ListCrypt[id];
	}

	void load_table(){
	iCrypt * cr = new __DP_LIB_NAMESPACE__::Collection::Ver1::Crypt("");
		AddCrypt(*cr, "SCH5");
	}

	Crypt::Crypt(const String & key, const String &name):key(key){
		load_table();
		version = ID(name);
	}

	Crypt::Crypt(){
		load_table();
		key = "std::password";
		version = 0;
	}

	String Crypt::Enc(const String & test){
		iCrypt& cr = getCryptfromId(version);
		cr.SetKey(key);
		return NameCrypt(version) + ":" + cr.Enc(test);
	}

	String Crypt::Dec(const String &text){
		String str = "";
		UInt i = 0;

		for (; i < text.length(); i++) {
			if (text[i] == ':')
				break;
			str += text[i];
		}
		if ( i >= text.size())
			i=-1;
		iCrypt * cr;
		if (str == "" || str == text)
			cr = &getCryptfromId(0);
		else
			cr = &getCrypt(str);

		cr->SetKey(key);
		return cr->Dec(text.substr(i+1));
	}
}
