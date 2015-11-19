#include <iostream>
#include <fstream>
#include <regex>		// regex, smatch, regex_match
#include <stdexcept>	// runtime_error
using namespace std;

int main(){
	ifstream in("table.txt");	// 入力ファイル
	if(!in) throw runtime_error("no input file\n");

	string line;				// 入力バッファ
	int lineno = 0;
	regex header("^[\\w\\s]+(\\t[\\w\\s]+)*$");				// \tを使用
	regex row("^[\\w\\s]+(\\t\\d+)(\\t\\d+)(\\t\\d+)$");	// \tを使用

	if(getline(in, line)){		// 見出し行をチェックする
		smatch matches;
		if(!regex_match(line, matches, header))
			throw runtime_error("no header");
	}
	while(getline(in, line)){
		++lineno;
		smatch matches;
		if(!regex_match(line, matches, row))
			throw runtime_error("bad line "+ to_string(lineno));
	}
}