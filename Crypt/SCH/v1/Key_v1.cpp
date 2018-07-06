/*
 * Key.cpp
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */


#include "Key_v1.h"
#include "../System.h"

namespace DP{
	namespace Collection{
		namespace Ver1{
			Key::Key(const String&key){
				_num = 1;
				_pos = 0;
				Int tmp = 0;
				for (UInt i = 0; i < key.length(); i++)
					tmp += DP::Sys::convert->ord(key[i]);
				tmp *= key.length();
				_key = key;
				_prev = tmp;
			}

			Int Key::operator()(){
				if (_pos >= _key.length())
					_pos = 0;
				Int tmp = _prev * _num * DP::Sys::convert->ord(_key[_pos]) + _pos;
				if (tmp < 0)
					tmp *= -1;
				_prev = tmp;
				_num++;
				_pos++;
				return tmp;
			}

			Int Key::operator()(Int max){
				if (max<=0)
					return (*this)();
				return (*this)()%max;
			}
		}
	}
}

