/*
 * Crypt.cpp
 *
 *  Created on: 13 02 2018 г.
 *      Author: diman-pro
 */

#include "Crypt_v1.h"
#include "UniKey_v1.h"
#include "../System.h"
#include "../../../Log/Log.h"
#include "../../../Converter/Converter.h"


namespace DP{
	namespace Collection{
		namespace Ver1{
			Crypt::Crypt(const String &key):_key(Key(key)){
				__key=key;
			}

			void Crypt::SetKey(const String & key){
				__key=key;
				_key=Key(key);
			}

			template<typename T>
			Int* ToByte(T N){
				UChar * matr=(UChar*)&N;
				Int * res = new Int[sizeof(T)];
				for (UInt i = 0; i < sizeof(T); i++)
					res[i]=(Int)matr[i];
				return res;
			}

			Int ToInt(Int*n){
				Int res=0;
				UChar * matr = (UChar*)&res;
				for (UInt i = 0; i < sizeof(Int); i++)
					matr[i]=n[i];
				return res;
			}

			Crypt::LocalVector Crypt::ENC_Step1(const String&str){
				LocalVector res;
				Map<Char, Int> map;
				for (UInt i = 0; i < str.length(); i++)
					if (!ConteinsKey(map,str[i]))
						map[str[i]]=0;
				_map_C = map.size();
				UniKey k{1,_map_C, _key};
				for (auto t = map.begin(); t != map.end(); t++) {
					auto tmo = k();
					map[t->first] = tmo;
					res.push_back(DP::Sys::convert->ord(t->first));
				}
				res.push_back(0);
				for (UInt i = 0; i < str.length(); i++)
					res.push_back(map[str[i]]);

				log << "Enc Step 1:";
				for (auto x = res.cbegin(); x != res.cend(); x++)
					log << *x;
				log.endl();

				return res;
			}

			String Crypt::DEC_Step1(const LocalVector& tmp){
				Map<Int, Char> map;
				UInt i = 0;
				for (i = 0; i < tmp.size(); i++)
					if (tmp[i] == 0)
						break;
				Key ktmp{__key};
				UniKey k {1, i, ktmp};
				for (UInt j = 0; j < i; j++)
					map[k()] = DP::Sys::convert->sym(tmp[j]);
				String res = "";
				for (UInt j = i + 1; j < tmp.size(); j++) {
					if (tmp[j] == 0)
						break;
					res += map[tmp[j]];
				}
				log << "Dec Step 1:";
				for (auto x = tmp.cbegin(); x != tmp.cend(); x++)
					log << *x;
				log.endl();
				return res;
			}

			Int Crypt::Step3_Get_Key(){
				Int res=1;
				for (UInt i = 0; i < __key.length(); i++)
					res *= DP::Sys::convert->ord(__key[i]);
				return res;
			}

			Crypt::LocalVector Crypt::ENC_Step2(const LocalVector & l){
				LocalVector res;
				Int MAX = sizeof(Int);
				Int dat[MAX];
				Int tmp = 0;
				Bool t=false;
				for (UInt i = 0; i < l.size(); i++){
					if (t) {
						if (tmp >= MAX) {
							res.push_back(ToInt(dat));
							tmp = 0;
						}
						dat[tmp++] = ToByte(l[i])[0];
						continue;
					}
					if (l[i] == 0) {
						dat[tmp++] = 0;
						t = true;
						continue;
					}
					res.push_back(l[i]);
				}
				for (Int i = tmp; i < MAX; i++)
					dat[i] = 0;
				res.push_back(ToInt(dat));
				log << "Enc Step 2:";
				for (auto x = res.cbegin(); x != res.cend(); x++)
					log << *x;
				log.endl();
				return res;
			}

			Crypt::LocalVector Crypt::DEC_Step2(const LocalVector & l){
				LocalVector res;
				UInt i = 0;
				for (; i < l.size(); i++){
					Int* r = ToByte(l[i]);
					if (r[0] == 0)
						break;
					res.push_back(l[i]);
					delete [] r;
				}
				for (UInt j = i; j < l.size(); j++) {
					Int* r = ToByte(l[j]);
					for (UInt k = 0; k < sizeof(l[j]); k++)
						res.push_back(r[k]);
					delete [] r;
				}
				log << "Dec Step 2:";
				for (auto x = l.cbegin(); x != l.cend(); x++)
					log << *x;
				log.endl();
				return res;
			}

			Crypt::LocalVector Crypt::ENC_Step3(const LocalVector & l){
				LocalVector res;
				Int MAX = Step3_Get_Key();
				for (UInt i = 0; i < l.size(); i++) {
					Int tmo = _key(MAX);
					res.push_back(l[i] ^ tmo);
				}
				log << "ENC Step 3:";
				for (auto x = res.cbegin(); x != res.cend(); x++)
					log << *x;
				log.endl();
				return res;
			}

			Crypt::LocalVector Crypt::DEC_Step3(const LocalVector & l){
				Key k{__key};
				for (UInt i = 0; i < _map_C; i++)
					k();
				LocalVector res;
				Int MAX = Step3_Get_Key();
				for (UInt i = 0; i < l.size(); i++){
					Int tmo = k(MAX);
					Int tmp = l[i] ^ tmo;
					//if (tmp < 0)
						//tmp += int.MaxValue;
					res.push_back(tmp);
				}
				log << "DEC Step 3:";
				for (auto x = l.cbegin(); x != l.cend(); x++)
					log << *x;
				log.endl();
				return res;
			}

			Crypt::LocalVector Crypt::ENC_Step4(LocalVector l){
				for (UInt i = 0; i < l.size(); i++){
					Int tmp = l[i];
					Int num = _key(l.size());
					l[i] = l[num];
					l[num] = tmp;
				}
				log << "ENC Step 4:";
				for (auto x = l.cbegin(); x != l.cend(); x++)
					log << *x;
				log.endl();
				return l;
			}
	
			Crypt::LocalVector Crypt::DEC_Step4(LocalVector  l){
				log << "DEC Step 4:";
				for (auto x = l.cbegin(); x != l.cend(); x++)
					log << *x;
				log.endl();
				Key k{__key};
				for (UInt i = 0; i < l.size()+_map_C; i++)
					k();
				Int st [l.size()];
				for (UInt i = 0; i < l.size(); i++){
					st[i] = k(l.size());
				}
				for (Int i = l.size() - 1; i >= 0; i--) {
					Int tmp = l[st[i]];
					l[st[i]] = l[i];
					l[i] = tmp;
				}
				return l;
			}

			String Crypt::ENC_Step5(const LocalVector& l){
				String res = DP::Sys::convert->ToHex(ToByte(_map_C)[0]);
				for (UInt i = 0; i < l.size(); i++) {
					Int* t = ToByte(l[i]);
					for (UInt j = 0; j < sizeof(l[i]); j++)
						res += DP::Sys::convert->ToHex(t[j]);

					delete [] t;
				}
				return res;
			}

			Crypt::LocalVector Crypt::DEC_Step5(const String &str){
				LocalVector res;
				String tmp {str[0]};
				tmp += str[1];
				_map_C = DP::Sys::convert->HexToByte(tmp);
				Int k = 0;
				Int ras = (str.size() - 2) / 2;
				if (ras % 4 != 0)
					//ToDo
					throw;
				Int bs[ras];
				for (UInt i = 2; i < str.length(); i+=2) {
					String tmps{str[i]};
					tmps += str[i + 1];
					bs[k++] = DP::Sys::convert->HexToByte(tmps);
				}
				for (Int i = 0; i < ras; i+=4)
					res.push_back(ToInt(bs+i));
				return res;
			}

			String Crypt::Enc(const String &text){
				return ENC_Step5(ENC_Step4(ENC_Step3(ENC_Step2(ENC_Step1(text)))));
			}

			String Crypt::Dec(const String &text){
				  return DEC_Step1(DEC_Step2(DEC_Step3(DEC_Step4(DEC_Step5(text)))));
			}
		}
	}
}
