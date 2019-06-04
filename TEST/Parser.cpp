#include "Parser.h"
#include <Parser/ArgumentParser.h>
#include <Parser/SmartParser.h>
#include <Parser/Setting.h>
#include <sstream>

using __DP_LIB_NAMESPACE__::String;
using __DP_LIB_NAMESPACE__::Vector;
using __DP_LIB_NAMESPACE__::Int;
using __DP_LIB_NAMESPACE__::ArgumentParser;
using __DP_LIB_NAMESPACE__::SmartParser;
using __DP_LIB_NAMESPACE__::Setting;
using std::ostringstream;
using std::istringstream;



int t1_fun1=0;
void t1_fun1r(ArgumentParser&, int& i, Vector<String>& par){
	t1_fun1+=1;
}

int t1_fun2=0;
void t1_fun2r(ArgumentParser&, int& i, Vector<String>& par){
	t1_fun2++;
	if ((i+1) == par.size())
		return;

	String check = par[++i];
	if (check == "t1_fun2r")
		t1_fun2++;
}

int t1_fun3=0;
inline void print_st(){
	print(t1_fun1);
	print(" ");
	print(t1_fun2);
	print(" ");
	print(t1_fun3);
	print(" ");
}

void t1_fun3r(ArgumentParser&, int& i, Vector<String>& par){
	t1_fun3 ++;
	if ((i+1) == par.size())
		return;

	String check1 = par[++i];

	if (check1 == "check3")
		t1_fun3 ++;

	if ((i+1) != par.size()) {
		String check2 = par[++i];

		if (check2 == "check32")
			t1_fun3 ++;
	}
}

inline void clean(){
	t1_fun1 = 0;
	t1_fun2 = 0;
	t1_fun3 = 0;
}

void Test_ArgumentParser(){
	ArgumentParser par;
	par.Add("fun1", t1_fun1r);
	par.Add("fun2", t1_fun2r);
	par.Add("fun3", t1_fun3r);
	clean();

	{
		char *argv[] = {"fun1"};
		LINE
		par.Load(1, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 0) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun2"};
		LINE
		par.Load(1, argv);
		Assert((t1_fun1 == 0) && (t1_fun2 == 1) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun2", "t1_fun2r"};
		LINE
		par.Load(2, argv);
		Assert((t1_fun1 == 0) && (t1_fun2 == 2) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun2", "fun1", "t1_fun2r"};
		LINE
		par.Load(3, argv);
		Assert((t1_fun1 == 0) && (t1_fun2 == 1) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun2", "2", "fun1", "t1_fun2r"};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 1) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun2", "t1_fun2r", "fun1", ""};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 2) && (t1_fun3 == 0), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "t1_fu2n2r", "fun12", ""};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 0) && (t1_fun2 == 0) && (t1_fun3 == 1), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "t1_fu2n2r", "check3", ""};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 0) && (t1_fun2 == 0) && (t1_fun3 == 1), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check3", "check3", "fun1"};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 0) && (t1_fun3 == 2), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check3", "check32", "fun1"};
		LINE
		par.Load(4, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 0) && (t1_fun3 == 3), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check3", "check32", "fun1", "fun2"};
		LINE
		par.Load(5, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 1) && (t1_fun3 == 3), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check3", "check32", "fun1", "fun2", "t1_fun2r"};
		LINE
		par.Load(6, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 2) && (t1_fun3 == 3), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check32", "a", "fun1", "fun2", "t1_fun2r"};
		LINE
		par.Load(6, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 2) && (t1_fun3 == 1), "Unknow function is run");
	}
	clean();
	{
		char *argv[] = {"fun3", "check3", "a", "fun1", "fun2", "t1_fun2r"};
		LINE
		par.Load(6, argv);
		Assert((t1_fun1 == 1) && (t1_fun2 == 2) && (t1_fun3 == 2), "Unknow function is run");
	}
}


template <typename Cont>
void eq_vectors(const Cont & t1, const Cont & t2){
	Assert(t1.size() == t2.size(), "Container size is not equal");
	auto x1 = t1.cbegin();
	auto x2 = t2.cbegin();
	for (; x1 != t1.cend(); x1++, x2++){
		if ((*x1) != (*x2))
			Assert(false, "Element is not equal");
	}
}

void Test_SmartParser(){
	#define IsScan(X) \
		Assert(X, "Fail parse correct data");

	#define IsNotScan(X) \
		Assert (par.Scan(X) == false, "Fail parsed not correct data");

	#define Equal(X, Y) \
		Assert(X == Y, "Values is not equal");

	#define Detect1(X, Y, Name)\
		Assert(par.Scan(X), "Fail parse correct data"); \
		Assert(par.GetParam(Name) == Y, "Values is not equal");

	#define PARAM(X) \
		Assert(par.existParam(X), "Current paramet is not found");

	{
		SmartParser par("*");
		eq_vectors(par.GetAllParamsName(), Vector<String>());
		eq_vectors(par.GetParamsValues(), Vector<String>());
		LINE
		IsScan(par.Scan("1"));
		LINE
		IsScan(par.Scan("new std values for test"));
		LINE
		IsScan(par.Scan("Тест на корректность работы с разными kodиpobkaми"));
	}
	{
		SmartParser par("test No?");
		eq_vectors(par.GetAllParamsName(), Vector<String>());
		eq_vectors(par.GetParamsValues(), Vector<String>());
		LINE
		IsScan(par.Scan("test No1"));
		LINE
		IsScan(par.Scan("test No5"));
		LINE
		IsScan(par.Scan("test Nop"));
		LINE
		IsNotScan("test No56");
	}
	{
		SmartParser par("t?st No?");
		eq_vectors(par.GetAllParamsName(), Vector<String>());
		eq_vectors(par.GetParamsValues(), Vector<String>());
		LINE
		IsScan(par.Scan("test No1"));
		LINE
		IsScan(par.Scan("trst No5"));
		LINE
		IsScan(par.Scan("t4st Nop"));
		LINE
		IsNotScan("tast No56");
		LINE
		IsNotScan("tesst No2");
		IsNotScan("tese No2");
	}
	{
		SmartParser par("${var}");
		LINE
		eq_vectors(par.GetAllParamsName(), Vector<String>({"var"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({""}));
		PARAM("var");

		LINE
		Detect1("value", "value", "var");
		eq_vectors(par.GetParamsValues(), Vector<String>({"value"}));

		LINE
		Detect1("new std values for test","new std values for test", "var");
		eq_vectors(par.GetParamsValues(), Vector<String>({"new std values for test"}));

		LINE
		Detect1("Тест на корректность работы с разными kodиpobkaми", "Тест на корректность работы с разными kodиpobkaми", "var");
		eq_vectors(par.GetParamsValues(), Vector<String>({"Тест на корректность работы с разными kodиpobkaми"}));
	}
	{
		SmartParser par("h${value}o");
		PARAM("value");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"value"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({""}));

		LINE
		Detect1("hello", "ell", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"ell"}));

		LINE
		Detect1("hello my test for SmartParser No", "ello my test for SmartParser N", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"ello my test for SmartParser N"}));

		LINE
		IsNotScan("Hell");
	}
	{
		SmartParser par("${name}=${value}");
		PARAM("name");
		PARAM("value");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"name", "value"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({"", ""}));

		#define Detect2(TXT, X, Name1, Y, Name2) \
			Assert(par.Scan(TXT), "Fail parse correct data"); \
			Assert((par.GetParam(Name1) == X) && (par.GetParam(Name2) == Y), "Values is not equal");
		LINE
		Detect2("name=value", "name", "name", "value", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"name", "value"}));

		LINE
		Detect2(" name = value ", " name ", "name", " value ", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({" name ", " value "}));

		Detect2("1=2", "1", "name", "2", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"1", "2"}));

		Detect2("Dara = VALUES", "Dara ", "name", " VALUES", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"Dara ", " VALUES"}));

		IsNotScan("Hello");
		IsNotScan("s/1");
		IsNotScan("32");
		IsNotScan("=");
	}
	{
		SmartParser par("${name}:${value}");
		PARAM("name");
		PARAM("value");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"name", "value"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({"", ""}));

		LINE
		Detect2("name:value", "name", "name", "value", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"name", "value"}));

		LINE
		Detect2(" name : value ", " name ", "name", " value ", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({" name ", " value "}));

		LINE
		Detect2("1:2", "1", "name", "2", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"1", "2"}));

		LINE
		Detect2("Dara : VALUES", "Dara ", "name", " VALUES", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"Dara ", " VALUES"}));

		IsNotScan("Hello");
		IsNotScan("s/1");
		IsNotScan("32");
		IsNotScan(":");
	}
	{
		SmartParser par("${name}.zip*");
		PARAM("name");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"name"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({""}));

		LINE
		Detect1("data.zip", "data", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({"data"}));

		LINE
		Detect1("Darta.zip2", "Darta", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({"Darta"}));

		LINE
		Detect1("Darta.zip2sdsgfdgdz${Sdsd}", "Darta", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({"Darta"}));

		IsNotScan("ssdsd.jpged");
		IsNotScan("ass");
		IsNotScan("123");
	}
	{
		SmartParser par("*.${type}");
		PARAM("type");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"type"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({""}));

		LINE
		Detect1("Data.jpg", "jpg", "type");
		eq_vectors(par.GetParamsValues(), Vector<String>({"jpg"}));

		LINE
		Detect1("info.txt", "txt", "type");
		eq_vectors(par.GetParamsValues(), Vector<String>({"txt"}));

		LINE
		Detect1("config.cfg", "cfg", "type");
		eq_vectors(par.GetParamsValues(), Vector<String>({"cfg"}));

		LINE
		Detect1(".hide", "hide", "type");
		eq_vectors(par.GetParamsValues(), Vector<String>({"hide"}));

		IsNotScan("1");
		IsNotScan("1w2");
	}
	{
		SmartParser par("{name}=${value}");
		PARAM("value");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"value"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({""}));

		Assert(!par.existParam("name"), "Findet not param value");
		Assert(par.existParam("value"), "Not finder param");

		LINE
		Detect1("{name}=11", "11", "value");
		eq_vectors(par.GetParamsValues(), Vector<String>({"11"}));

		IsNotScan("ss=1");
		IsNotScan("1=");
	}
	{
		SmartParser par("${id}-${name}.?*");
		PARAM("id");
		PARAM("name");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"id", "name"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({"", ""}));

		LINE
		Detect2("01-re.mp3", "01", "id", "re", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({"01", "re"}));

		LINE
		Detect2("1- 443 .5", "1", "id", " 443 ", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({"1", " 443 "}));

		LINE
		Detect2(" 1 - ss.2", " 1 ", "id", " ss", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({" 1 ", " ss"}));

		LINE
		Detect2(" - .1", " ", "id", " ", "name");
		eq_vectors(par.GetParamsValues(), Vector<String>({" ", " "}));

		IsNotScan("12-re.");
		IsNotScan("-ss.2");
		IsNotScan("123");
		IsNotScan("123 12 3.22");
		IsNotScan("-.2");
	}
	{
		SmartParser par("${v1}*${v2}");
		PARAM("v1");
		PARAM("v2");
		eq_vectors(par.GetAllParamsName(), Vector<String>({"v1", "v2"}));
		eq_vectors(par.GetParamsValues(), Vector<String>({"", ""}));

		par.SetParam("v1", "1");
		par.SetParam("v2", "2");
		Equal(par.ToString(), "1*2");
		par.SetParam("v1", "1*2");
		par.SetParam("v2", "3");
		Equal(par.ToString(), "1*2*3");
	}
	{
		SmartParser par (".${second}");
		IsNotScan(".");
	}
}

void Tests_Setting(){
	Setting set;

	#define Exist(Key, Value) \
		Assert(set.Conteins(Key), "Exist key is not found"); \
		Assert(set.get(Key) == Value, "Set value is not equal");
	{
		istringstream str("[]\ntest=1");
		str * set;

		Exist("test", "1");
		LINE
		eq_vectors(set.getKeys<Vector<String>>("."), Vector<String> ({"test"}));

		set.add("test", "2");
		Exist("test", "2");

		set.add("test.info", "3");
		LINE
		eq_vectors(set.getFolders<Vector<String>>("."), Vector<String>({"test"}));

		Exist("test", "2");


		Exist("test.info", "3");
		LINE
		eq_vectors(set.getKeys<Vector<String>>("test"), Vector<String> ({"info"}));
		LINE
		eq_vectors(set.getFolders<Vector<String>>("."), Vector<String>({"test"}));

		set.add("test2", "2");
		Exist("test2", "2");
		LINE
		eq_vectors(set.getKeys<Vector<String>>("test"), Vector<String> ({"info"}));
		LINE
		eq_vectors(set.getKeys<Vector<String>>("."), Vector<String>({"test", "test2"}));

		ostringstream os;
		os << set;
		Equal(os.str(), "[]\ntest=2\ntest2=2\n[.test]\ninfo=3\n");
	}
}

void Parser_Tests(){
	reset_info();

	TEST(Test_ArgumentParser);
	TEST(Test_SmartParser);
	TEST(Tests_Setting);

	println_info();
}
