#include <regex>
#include <iostream>
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

	string line, str = "";	// ファイルのすべての文字をstrに格納
	while(getline(ifs, line)) str += line + '\n';

	smatch matches;
	if(regex_search(str, matches, pattern)){
		for(int i = 0; i < matches.size(); ++i)
			cout << "matches[" << i << "]: " << matches[i] << endl;
	}
	else cout << "didn't match\n";
}