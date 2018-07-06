#ifndef MEMORYMANAGER_MEMORY_H_
#define MEMORYMANAGER_MEMORY_H_

#define __CPP__
#include "../DPLib.conf.h"
#include <cstdlib>


//Включение логов
//#define Logue

#ifdef Logue
#include "../ProcessManager/MultiThreadOut.h"
using Proces_MNG::console;
#endif


namespace DP{
	/*
	 * Данный класс выделяет динамическую память и контролирует ее возвращение ОС
	 */
	class MemoryManager{
		private:
			Vector<void*> _mem;
		public:
			MemoryManager(){}

			~MemoryManager(){
				/*
				 * Если кто-то не возвратил память, то возвращаем ее принудительно
				 */
				for (auto x = _mem.begin(); x != _mem.end(); x++){
					free(*x);
				}
				#ifdef Logue
					console<<"\ndelete "<<_mem.size()<<"\n";
				#endif
			}

			/*
			 * Получаем объект произвольного типа,для которого определен конструктор
			 */
			template<typename T>
			T& getMem(){
				void* memory = std::malloc(sizeof(T));
				T* res = new (memory)T();
				_mem.push_back(memory);
				return *res;
			}

			template <typename T, typename... Y>
			T& getMem(Y... __args){
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
						#ifdef Logue
							Proces_MNG::console<<"\nDelete memory"<<mem<<"\n";
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
						#ifdef Logue
							Proces_MNG::console<<"\nDelete memory"<<mem<<"\n";
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
			void erase(void * mem){
				for (auto x = _mem.begin(); x != _mem.end(); x++)
					if (*x == mem){
						#ifdef Logue
							Proces_MNG::console<<"\nDelete memory"<<mem<<"\n";
						#endif
						_mem.erase(x);
						free(mem);
						return;
					}
			}
	};
}

#endif /* MEMORYMANAGER_MEMORY_H_ */