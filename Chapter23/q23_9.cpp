#include <iostream>
#include <fstream>
#include <string>		// stoi (C++11)
#include <regex>		// regex, smatch, regex_match (C++11)
#include <stdexcept>	// runtime_error
using namespace std;

int main(){
	ifstream in("table.txt");	// 入力ファイル
	if(!in) throw runtime_error("no input file\n");

	string line;				// 入力バッファ
	int lineno = 0;
	regex header("^[\\w\\s]+(\\t[\\w\\s]+)*$");
	regex row("^([\\w\\s]+)(\\t\\d+)(\\t\\d+)(\\t\\d+)$");

	if(getline(in, line)){		// 見出し行をチェックする
		smatch matches;
		if(!regex_match(line, matches, header))
			throw runtime_error("no header");
	}

	// 列の合計:
	int boys = 0;
	int girls = 0;

	while(getline(in, line)){
		++lineno;
		smatch matches;
		if(!regex_match(line, matches, row))
			cerr << "bad line: " << lineno << '\n';

		if(in.eof()) cout << "at eof \n";

		// 行をチェックする
		int curr_boy = stoi(matches[2]);
		int curr_girl = stoi(matches[3]);
		int curr_total = stoi(matches[4]);
		if(curr_boy + curr_girl != curr_total) 
			throw runtime_error("bad row sum \n");

		if((in >> ws).eof()){	// 最後の行
			if(curr_boy != boys) throw runtime_error("boys don't add up\n");
			if(curr_girl != girls) throw runtime_error("girls don't add up\n");
			//if(!(in>>ws).eof()) throw runtime_error("characters after total line");
			return 0;
		}

		// 合計を更新する
		boys += curr_boy;
		girls += curr_girl;
	}

	throw runtime_error("didn't find total line");
}