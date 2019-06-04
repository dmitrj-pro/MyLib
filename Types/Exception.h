#ifndef LIB_TYPE_EXCEPTION_H_
#define LIB_TYPE_EXCEPTION_H_

#include "../DPLib.conf.h"

namespace __DP_LIB_NAMESPACE__{
	String IntToString(Int in);

	class Exception:public BaseException{
		protected:
			String _str;

		public:
			Exception(const String & str):_str(str){}

			virtual inline const char * what () const throw () {
				return _str.c_str();
			}

			virtual inline String toString() const{
				return _str;
			}

			virtual ~Exception(){}
	};

	class LineException: public Exception {
		private:
			Int _line;
			String _file_name;

		public:
			inline LineException(const String & wh, Int line = -1, const String & file = "main"): Exception(wh),
					 _line(line), _file_name (file){}

			virtual inline String toString() const {
				String tmp = _file_name + " " + IntToString(_line) + ": " + Exception::toString();
				return tmp;
			}

			virtual inline const char * what() const noexcept {
				String tmp = _file_name + " " + IntToString(_line) + ": " + Exception::toString();
				return tmp.c_str();
			}

	};

	#define EXCEPTION(STR) \
		__DP_LIB_NAMESPACE__::LineException(STR, __LINE__, __FILE__)
}


#endif /* LIB_TYPE_EXCEPTION_H_ */
