#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
using namespace std;

int main(){
	int alpha, digit, xdigit, upper, lower, alnum, punct, print, graph;
	alpha = digit = xdigit = upper = lower = alnum = punct = print = graph = 0;
	string str;
	string filename;

	cout << "ファイル名を入力してください。 > ";
	cin >> filename;
	ifstream ifs(filename.c_str());
	if(!ifs) throw runtime_error("ファイルを開けませんでした。: " + filename);

	while(ifs >> str){
		for(int i = 0; i < str.size(); ++i){
			if(isalpha(str[i])) alpha++;
			if(isdigit(str[i])) digit++;
			if(isxdigit(str[i])) xdigit++;
			if(isupper(str[i])) upper++;
			if(islower(str[i])) lower++;
			if(isalnum(str[i])) alnum++;
			if(ispunct(str[i])) punct++;
			if(isprint(str[i])) print++;
			if(isgraph(str[i])) graph++;
		}
	}	

	cout << "英字: " << alpha << endl
		 << "10進数字: " << digit << endl
		 << "16進数字: " << xdigit << endl
		 << "大文字: " << upper << endl
		 << "小文字: " << lower << endl
		 << "英数字: " << alnum << endl
		 << "記号: " << punct << endl
		 << "表示可能文字: " << print << endl
		 << "英数記号: " << graph << endl;
}