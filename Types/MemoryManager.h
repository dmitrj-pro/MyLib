#ifndef MEMORYMANAGER_MEMORY_H_
#define MEMORYMANAGER_MEMORY_H_

#define __CPP__

#include "../DPLib.conf.h"
#include "Exception.h"
#include <cstdlib>
#ifdef DP_LIB_DEBUG
#include <Log/Log.h>
#endif


namespace __DP_LIB_NAMESPACE__{
	/*
	 * Данный класс выделяет динамическую память и контролирует ее возвращение ОС
	 */
	class MemoryManager{
		private:
			Vector<void*> _mem;
		public:
			inline MemoryManager(){}

			~MemoryManager();

			/*
			 * Получаем объект произвольного типа,для которого определен конструктор
			 */
			template<typename T>
			inline T& getMem(){
				void* memory = std::malloc(sizeof(T));
				T* res = new (memory)T();
				_mem.push_back(memory);
				return *res;
			}

			template <typename T, typename... Y>
			inline T& getMem(Y... __args){
				void* memory = std::malloc(sizeof(T));
				T* res = new (memory)T(__args...);
				_mem.push_back(memory);
				return *res;
			}

			/*
			 * Очищаем память в добровольном порядке
			 */
			template<typename T>
			void erase(T& x){
				void * mem = &x;
				x.~T();
				for (auto x = _mem.begin(); x != _mem.end(); x++)
					if (*x==mem){
						#ifdef DP_LIB_DEBUG
							log << "Delete memory " << mem;
							log.endl();
						#endif
						_mem.erase(x);
						free( mem);
						return;
					}
			}

			/*
			 * Очищаем память в добровольном порядке
			 */
			template<typename T>
			void erase(T* x){
				void * mem = x;
				x->~T();
				for (auto x = _mem.begin(); x != _mem.end(); x++)
					if (*x==mem){
						#ifdef DP_LIB_DEBUG
							log << "Delete memory " << mem;
							log.endl();
						#endif
						_mem.erase(x);
						free( mem);
						return;
					}
			}

			/*
			 * Очищаем память в добровольном порядке, но без
			 * вызова диструктора
			 */
			void erase(void * mem);
	};
}

#endif /* MEMORYMANAGER_MEMORY_H_ */
