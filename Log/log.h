#ifndef LOG_H
#define LOG_H

#include "../DPLib.conf.h"

namespace DP{
	template <typename Ostream>
	class Log{
		private:
			#ifdef DP_DEBUG
				Ostream & os;
			#endif
		public:
			#ifdef DP_DEBUG
				inline Log(Ostream&os):os(os){}
			#endif
			#ifndef DP_DEBUG
				inline Log(Ostream & os){}
				inline Log(){}
			#endif
			template<typename T>
			inline Log& operator()(const T& t){
				#ifdef DP_DEBUG
					os << t << " ";
					os.flush();
				#endif
				return *this;
			}
			inline void flush(){
				#ifdef DP_DEBUG
					os.flush();
				#endif
			}

			template<typename T>
			inline Log& operator*(const T& t){
				this->operator ()(t);
				this->operator ()("\n");
				return *this;
			}

			template<typename T>
			inline Log& endl(const T& t){
				(*this)*t;
				return *this;
			}
			inline Log& endl(){
				(*this)*"";
				return *this;
			}

			template <typename T>
			friend Log& operator << (Log& os, const T& x){
				return os(x);
			}

	};

	extern Log<Ostream> log;
	extern bool isError;
}
#endif // LOG_H
