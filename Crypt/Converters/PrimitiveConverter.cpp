/*
 * PrimitiveConverter.cpp
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#include "PrimitiveConverter.h"
#include "../../DPLib.conf.h"
#include "../../Converter/Converter.h"
#include "../../Types/Exception.h"

namespace __DP_LIB_NAMESPACE__{
	namespace Converter{
		Int Primitive::ord(UChar c){
			return (Int)c;
		}

		inline Char ByteToHex(Int b){
			if (b < 0)
				throw EXCEPTION("b < 0");
			//b = b<0 ? (-1)*b : b;
			if ( (b >= 0) && (b < 10) )
				return (char) ('0' + b);
			switch (b) {
				case 10:
					return 'A';
					break;
				case 11:
					return 'B';
					break;
				case 12:
					return 'C';
					break;
				case 13:
					return 'D';
					break;
				case 14:
					return 'E';
					break;
				case 15:
					return 'F';
					break;
			}
			return 'Z';
		}

		String Primitive::ToHex(Int b){
			return toString(ByteToHex(b/16)) + toString(ByteToHex(b%16));
		}

		inline Int HexToInt(Char c) {
			if ( (c <= '9') && (c >= '0') )
				return (Int) (c - '0');
			switch (c) {
				case 'A':
					return 10;
					break;
				case 'B':
					return 11;
					break;
				case 'C':
					return 12;
					break;
				case 'D':
					return 13;
					break;
				case 'E':
					return 14;
					break;
				case 'F':
					return 15;
					break;
				default:
					return 18;
					break;
			}
		}

		Int Primitive::HexToByte(const String &str){
			return HexToInt(str[0]) * 16 + HexToInt(str[1]);
		}

		Char Primitive::sym(Int c) {
			if (c < 0)
				return '\n';
			return (Char)(c);
		}
	}
}
