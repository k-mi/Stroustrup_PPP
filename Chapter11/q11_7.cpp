#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

int main(){
	string line, convert_str, word;
	vector<string> vs;

	cout << "please enter words" << endl;
	while(getline(cin, line)){		// 1行ずつ取得
		convert_str = "";
		for(int i = 0; i < line.size(); ++i){
			// "can't"
			if(i + 4 < line.size() && (char)tolower(line[i]) == 'c'
				&& (char)tolower(line[i+1]) == 'a' && (char)tolower(line[i+2]) == 'n'
				&& line[i+3] == '\'' && (char)tolower(line[i+4]) == 't'){
				convert_str += "cannot";
				i += 4;
			}			
			// "n't"
			else if(i + 2 < line.size() && (char)tolower(line[i]) == 'n'
				&& line[i+1] == '\'' && (char)tolower(line[i+2]) == 't'){
				convert_str += " not";
				i += 2;
			}
			// 単語中のハイフン
			else if(i + 1 < line.size() && line[i] == '-' && isalpha(line[i-1]) && isalpha(line[i+1]))
				convert_str += '-';
			// その他記号
			else if(ispunct(line[i])) 
				convert_str += ' ';
			else	
				convert_str += (char)tolower(line[i]);	// 小文字に変換
		}
		
		istringstream ist(convert_str);
		while(ist >> word)
			vs.push_back(word);			// 辞書に追加
	}

	sort(vs.begin(), vs.end());			// 辞書式順序でソートする
	for(int i = 0; i < vs.size(); ++i)	// 辞書を書き出す
		if(i == 0 || vs[i] != vs[i-1])
			cout << vs[i] << endl;

	return 0;
}