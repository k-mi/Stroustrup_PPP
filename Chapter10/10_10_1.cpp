#include <iostream>
#include <stdexcept>
using namespace std;

void end_of_loop(istream& ist, char term, const string& message){
	if(ist.fail()){	// termを終了インジゲータまたはセパレータとして使用する
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return;	// すべて順調
		throw runtime_error(message);
	}
}

int main(){
	istream& ist = cin;
	ist.exceptions(ist.exceptions() | ios_base::badbit);
	int var;

	while(ist >> var){	// EOFまで読み取る
		// varが有効であることのチェック（必要に応じて）
		// varを使った何らかの処理
	}
	end_of_loop(ist, '|', "bad termination of file");	// 続行可能かどうかの評価

	// 続行: EOFまたは終了インジゲータが検出された	
}