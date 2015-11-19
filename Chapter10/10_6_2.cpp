#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// EOFまたは終了インジゲータが検出されるまでistからvに整数を読み取る
void fill_vector(istream& ist, vector<int>& v, char terminator){
	int i = 0;
	while(ist >> i) v.push_back(i);
	if(ist.eof()) return;		// OK: EOFが検出された

	if(ist.fail()){				// できるだけ後始末をし、問題を報告する
		ist.clear();			// ストリームの状態をクリアし、終了インジゲータを調査できるようにする
		char c;
		ist >> c;				// 文字を読み取る（終了インジゲータでありますように）
		if(c != terminator){	// 予想外の文字
			ist.unget();
			ist.clear(ios_base::failbit);	// 状態をfailに設定する
		}
	}
}

int main(){
	vector<int> v;
	cin.exceptions(cin.exceptions() | ios_base::badbit);

	fill_vector(cin, v, '*');
}