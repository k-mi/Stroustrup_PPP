#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

// 入力からパターンと行セットを受け取る
// パターンをチェックし、行でそのパターンを検索する
int main(){
	string filename;
	cout << "input file: ";
	getline(cin, filename);
	ifstream ifs(filename);
	if(!ifs){
		cout << "no " << filename << endl;
		exit(EXIT_FAILURE); 
	}

	regex pattern;
	string pat;
	cout << "enter pattern: ";
	getline(cin, pat);	// パターンを読み取る

	try{
		pattern = pat;
	}
	catch(regex_error){
		cout << pat << " is not a vaild regular expression\n";
		exit(EXIT_FAILURE);
	}

	string line;
	int lineno = 0;
	while(getline(ifs, line)){
		++lineno;
		if(regex_search(line, pattern))
			cout << lineno << ": " << line << '\n';
	}
}