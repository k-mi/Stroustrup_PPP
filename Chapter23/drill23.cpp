// 23_7_1.cppと同じ

#include <regex>	// regex, smatch, regex_search (C++11)
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
	ifstream in("file.txt");	// 入力ファイル
	if(!in) cerr << "no file\n";

	regex pat("\\w{2}\\s*\\d{5}(-\\d{4})?");	// 郵便番号パターン
	//cout << "pattern: " << pat << '\n';

	int lineno = 0;
	string line;	// 入力バッファ
	while(getline(in, line)){
		++lineno;
		smatch matches;	// マッチした文字列を保持する
		// smatchはmatch_results<std::string:const_iterator>と定義
		if(regex_search(line, matches, pat)){
			cout << lineno << ": " << matches[0] << '\n';	// 完全マッチ
			if(matches[1].matched)
				cout << "\t: " << matches[1] << '\n';		// サブマッチ
		}
	}
}