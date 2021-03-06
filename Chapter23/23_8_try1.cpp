#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

// 入力からパターンと行セットを受け取る
// パターンをチェックし、行でそのパターンを検索する
int main(){
	regex pattern;

	string pat;
	cout << "enter pattern: ";
	getline(cin, pat);	// パターンを読み取る

	try{
		pattern = pat;
		cout << "pattern: " << pat << '\n';
	}
	catch(regex_error){
		cout << pat << " is not a vaild regular expression\n";
		exit(1);
	}

	cout << "now enter lines:\n";
	string line;		// 入力バッファ
	int lineno = 0;

	while(getline(cin, line)){
		++lineno;
		smatch matches;

		if(regex_search(line, matches, pattern)){
			cout << "line " << lineno << ": " << line << '\n';
			for(int i = 0; i < matches.size(); ++i)
				cout << "\tmatches[" << i << "]: " << matches[i] << '\n';
		}
		else
			cout << "didn't match\n";
	}
}