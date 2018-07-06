#ifndef PARAMS_H
#define PARAMS_H

#define __CPP__
#include "../DPLib.conf.h"
#include "../Converter/Converter.h"

namespace DP{

	class ArgumentParser;
	typedef void (* function)(ArgumentParser&, int&, Vector<String>&);

	class ArgumentParser{
		private:
			Map<String, Vector<String>> _par;
			Map<String, function> _all;

		public:
			void Add (const String& name, function F);

			inline void Push(const String & name, const Vector<String>& value){ _par[name] = value; }
			inline Vector<String> Get(const String & name) {return _par[name]; }
			inline bool Conteins(const String & name){ return DP::ConteinsKey(_par,name); }
			void Load(int argc, char *argv[]);
	};
}

#endif // PARAMS_H
