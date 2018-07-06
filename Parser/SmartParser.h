#ifndef SCANER_SCANER_H_
#define SCANER_SCANER_H_

#include "../Types/MemoryManager.h"
#include "Smart/iSymbol.h"
#include "Smart/Symbol.h"
#include "Smart/Params.h"
#include "Smart/Exception.h"

namespace DP{
	class SmartParser{
		public:
			typedef DP::iSymbol ISymbol;
			typedef DP::Params Params;
			typedef DP::Symbol Symbol;
		private:
			typedef MemoryManager Mem;
			typedef Vector<ISymbol*> Vect;

			Vect sym;
			Mem memory;

			bool StartScan(const String &str, int si, Vect &list,int li) throw (DP::PharserFailure);

		public:
			~SmartParser(){
				for (auto x = sym.begin(); x!=sym.end(); x++){
					memory.erase(*x);
				}
			}
			SmartParser(const String&str);
			String ToString()const;
			String GetParam(const String &str)const throw (DP::ParamsNotFound);
			void SetParam(const String &param, const String & value) throw (DP::ParamsNotFound);
			bool existParam(const String& str)const;
			Vector<String> GetAllParamsName()const ;
			Vector<String> GetParamsValues()const ;

			inline bool Scan(String str) throw (DP::PharserFailure){
				return StartScan (str, 0, sym, 0);
			}

	};
}


#endif /* SCANER_SCANER_H_ */