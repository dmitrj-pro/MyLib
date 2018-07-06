#include <Crypt/Crypt.h>
#include "qgoogleauth.h"
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <QString>
#include <stdexcept>
#include <Parser/SmartParser.h>
#include <sstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::list;
using std::istringstream;


string filename="generator.sch";
string password="std::password";
bool isPassEmpty=true;

inline string getEncryptedData(){
    ifstream f;
    f.open(filename);
    if (f.fail()){
        return "";
    }
    string Data;
    getline(f,Data);
    f.close();
    #ifdef DP_V2
        DP::Crypt cr{password,"SCH5"};
    #endif
    #ifndef DP_V2
        DP_Crypt::Crypt cr {password,"SCH5"};
    #endif
    string tmp = cr.Dec(Data);
    if (tmp == "") {
        cout << "Password is not correct";
        throw std::exception();
    }
    return tmp;
}
inline void saveEncryptedData(const string & str){
    #ifdef DP_V2
        DP::Crypt cr{password,"SCH5"};
    #endif
    #ifndef DP_V2
        DP_Crypt::Crypt cr {password,"SCH5"};
    #endif
    string Data = cr.Enc(str);
    ofstream os;
    os.open(filename);
    os<<Data;
    os.close();
}

inline void add(const string&name,const string&key){
    string Data = getEncryptedData();
    Data+="\n"+name+":"+key;
    saveEncryptedData(Data);
}

list<string> parseData(const string & str){
    #ifdef DP_V2
        DP::SmartParser par("${before}:${after}");
    #endif
    #ifndef DP_V2
        DP::Parser::SmartParser par("${before}:${after}");
    #endif
    istringstream in;
    in.str(str);
    list<string> res;
    while (!in.eof()){
        string tmp;
        getline(in, tmp);
        if (par.Scan(tmp)){
            res.push_back(par.GetParam("before"));
            res.push_back(par.GetParam("after"));
        }
    }
    return res;
}

#define PASSWORD \
    if (isPassEmpty) {\
        cout << "Password: "; \
        getline(cin,password); \
        isPassEmpty =false; \
    }

int main(int argc, char* argv[]){
    try{
        if (argc<1){
            std::cout<<"No Password";
            return 0;
        }
        for (int i=0;i<argc;i++){
            string tmp=argv[i];
            if (tmp=="-add" || tmp == "--add"){
                PASSWORD
                add(argv[i+1], argv[i+2]);
                i+=2;
                continue;
            }
            if (tmp=="-pass"|| tmp=="--p" || tmp=="--pass"){
                password=argv[i+1];
                isPassEmpty = false;
                i+=1;
                continue;
            }
            if (tmp=="-f"){
                filename=argv[i+1];
                i++;
                continue;
            }
            if (tmp=="--dec"){
                PASSWORD
                cout<< getEncryptedData();
                return 0;
            }
            if (tmp=="--enc"){
                PASSWORD
                ifstream f;
                f.open(argv[i+1]);
                string Data;
                while (!f.eof()){
                    string tm;
                    getline(f, tm);
                    if (Data.size() > 0)
                        Data += "\n";
                    Data += tm;
                }
                f.close();
                #ifdef DP_V2
                    DP::Crypt cr{password,"SCH5"};
                #endif
                #ifndef DP_V2
                    DP_Crypt::Crypt cr {password,"SCH5"};
                #endif

                ofstream fo;
                fo.open(filename);
                fo<<cr.Enc(Data);
                fo.close();
                i+=1;
                continue;
            }
            if (tmp == "-help" || tmp == "--help" || tmp =="-h" || tmp =="--h"){
                cout << "-add ${Name} ${KEY} --- add key\n";
                cout << "--enc ${FILENAME} --- encrypt FILENAME and replace DB\n";
                cout << "--dec --- decrypt DB and echo on console";
                cout << "-f ${FILENAME} --- set FILENAME as DB \n";
                cout << "-pass ${PASSWORD} --- set password PASSWORD\n";
                return 0;
                continue;
            }

        }
        PASSWORD
        string res   = getEncryptedData();

        auto lis = parseData(res);
        for (auto x = lis.cbegin(); x!= lis.cend(); x++){
            cout << *x << ": ";
            x++;
            QString tmp = QString::fromStdString(*x).trimmed().toUpper();
            cout << QGoogleAuth::generatePin(tmp.toUtf8()).toStdString() << "\n";
        }
    } catch(...) {
        cout << "Error.\n";
    }
}
