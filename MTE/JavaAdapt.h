#ifndef _JAVAADAPTER
#define _JAVAADAPTER
#include <string>
#include <vector>
//#define String std::string
#define Exception std::exception
#define nr "\n"
#include <fstream>
#include <vector>

//string nr="\n";
using std::ofstream;
using std::vector;
using std::string;
using std::to_string;

namespace DP{
	namespace MTE{

		inline vector<string> split(string str, string w){
			int i=str.find(w);
			vector<string> res;
			res.push_back(str.substr(0,i));
			res.push_back(str.substr(i+w.length()));
			return res;
		}

		template <typename T>
		class Vector{
			private:
				vector<T> v;
			public:
				int size(){
					return v.size();
				}
				Vector(){}
				Vector(vector<T>& vec){
					v=vec;
				}
				T elementAt(size_t n){
					return v[n];
				}
				bool contains(T dat){
					if (find(v.begin(),v.end(),dat)==v.end()){
						return false;
					}
					return true;
				}
				int indexOf(T dat){
					for(int i=0; i<v.size();i++){
						if(v[i]==dat){
							return i;
						}
					}
					return -1;
				}
		//		vector<T>& operator vector<T>(){
		//			return v;
		//		}
				vector<T>& getVector(){
					return v;
				}
				vector<T> getVector()const {
					return v;
				}
				void push_back(T x){
					v.push_back(x);
				}
				T& operator[](size_t i){
					return v[i];
				}
				void add(T dat){
					v.push_back(dat);
				}
		};
		class String{
			private:
				string str;
			public:
				char charAt(int i){
					return str[i];
				}
				int length(){
					return str.size();
				}
				String(string& s){
					str=s;
				}
				String(const char* s){
					str=s;
				}
				string operator=(const string& s){
					return str=s;
				}
		//		string substring(int i){
		//			return str.substr(i);
		//		}
		//		string substring(int i, int j){
		//			return str.substr(i,j);
		//		}
		//		String substring(int i){
		//			return str.substr(i);
		//		}
		//		String substring(int i, int j){
		//			return str.substr(i,j);
		//		}
				char operator[](size_t i){
					return str[i];
				}
				int indexOf(char c, size_t j=0){
					for(int i=j; i<str.size();i++){
						if(str[i]==c){
							return i;
						}
					}
					return -1;
				}
				friend bool operator==(const String&str1, const String& str2){
					return str1.str==str2.str;
				}
		//		string& operator string(){
		//			return str;
		//		}
				string& getString(){
					return str;
				}
				string getString() const {
					return str;
				}
		};



		class Integer{
			public:
				static string toString (int i){
					return to_string(i);
				}
				static int parseInt(string str){
					return std::stoi(str);
				}
				static int parseInt(String str){
					return std::stoi(str.getString());
				}
		};

		class FileWriter{
			private:
				ofstream* f;
			public:
				FileWriter(){
					f=new ofstream;
				}
				FileWriter(FileWriter&& fw){
					f=fw.f;
					fw.f=nullptr;

				}
				FileWriter(string FileName, bool t){
					f=new ofstream();
					f->open(FileName.c_str());
				}
				void write(String str){
					(*f)<<str.getString();
				}
				void close(){
					f->close();
				}

		};
	}
}
#endif
