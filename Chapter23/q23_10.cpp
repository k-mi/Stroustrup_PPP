#include <iostream>
#include <fstream>
#include <string>		// stoi (C++11)
#include <regex>		// regex, smatch, regex_match (C++11)
#include <stdexcept>	// runtime_error
#include <map>
using namespace std;

struct Data{
	Data() : boy(0), girl(0), total(0) { }
	int boy, girl, total;
};

int main(){
	ifstream in("table.txt");	// 入力ファイル
	if(!in) throw runtime_error("no input file\n");

	string line;				// 入力バッファ
	int lineno = 0;
	regex header("^[\\w\\s]+(\\t[\\w\\s]+)*$");
	regex row("^([\\w\\s]+)(\\t\\d+)(\\t\\d+)(\\t\\d+)$");

	string first, last;		// 文字列に変化は無いため、見出しと最後の行を保持
	map<int, Data> data;	// key: 学年（学年以外のREST等は除外）, value: 人数

	if(getline(in, line)){		// 見出し行をチェックする
		smatch matches;
		if(!regex_match(line, matches, header))
			throw runtime_error("no header");
		first = line;
	}

	while(getline(in, line)){
		++lineno;
		smatch matches;
		if(!regex_match(line, matches, row))
			cerr << "bad line: " << lineno << '\n';

		if((in >> ws).eof()){	// 最後の行
			last = matches[1];
			break;
		}

		// 値をマージする
		try{
			int index = stoi(matches[1]);
			data[index].boy += stoi(matches[2]);
			data[index].girl += stoi(matches[3]);
			data[index].total += stoi(matches[4]);
		}
		catch(invalid_argument){
			// 何もしない
		}
		catch(...){
			throw;	// 外に投げる
		}
	}

	// 列の合計:
	int boys = 0;
	int girls = 0;

	// 出力
	cout << first << endl;
	for(map<int, Data>::const_iterator it = data.begin(); it != data.end(); ++it){
		cout << it->first << '\t' << it->second.boy << '\t' << it->second.girl << '\t' << it->second.total << endl;

		// 合計を更新する
		boys += it->second.boy;
		girls += it->second.girl;
	}
	cout << last << '\t' << boys << '\t' << girls << '\t' << boys + girls << endl;
}