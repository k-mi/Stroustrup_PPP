#include "std_lib_facilities.h"

int main(){
	string previous = " ";		// 前の単語を"not a word"に初期化する
	string current;				// 現在の単語
	while(cin >> current){		// 一連の単語を読み取る
		if(previous == current)	// 前の単語と同じかどうか確認する
			cout << "repeated word: " << current << '\n';
		previous = current;
	}
}