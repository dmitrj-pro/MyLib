#include <Crypt/Crypt.h>
#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;


int main(int argc, char* argv[]){
    DP::Crypt cr{"password","SCH5"};
    auto x = cr.Enc("Test");
    cout << x << "\n";
    cout << cr.Dec(x) << "\n";
}
