#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

// 可能であれば、sの文字を浮動小数点数値に変換する	
double str_to_double(string s){
	istringstream is(s);	// sから読み取りを行うためのストリームを作成する
	double d;
	is >> d;
	if(!is) throw runtime_error("double format error: " + s);
	return d;
}

int main(){
	double d1 = str_to_double("12.4");
	double d2 = str_to_double("1.34e+3");
	double d3 = str_to_double("twelve point three");	// error
}