#include "MemoryManager.h"
#ifdef DP_LIB_DEBUG
    #include "../Log/Log.h"
#endif

namespace __DP_LIB_NAMESPACE__ {
	MemoryManager::~MemoryManager(){
		/*
		* Если кто-то не возвратил память, то возвращаем ее принудительно
		*/
		for (auto x = _mem.begin(); x != _mem.end(); x++)
			free(*x);
		#ifdef DP_LIB_DEBUG
			log<<"delete "<<_mem.size();
			log.endl();
		#endif
	}
	void MemoryManager::erase(void * mem){
		for (auto x = _mem.begin(); x != _mem.end(); x++)
			if (*x == mem){
			#ifdef DP_LIB_DEBUG
				log << "Delete memory "<<mem;
				log.endl();
			#endif
			_mem.erase(x);
			free(mem);
			return;
		}
	}
}
