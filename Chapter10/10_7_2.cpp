#include <iostream>
#include <cctype>
#include <stdexcept>
using namespace std;

int main(){
	cout << "Please enter an integer in the range 1 to 10 (inclusice):\n";
	int n = 0;
	while(true){
		cin >> n;
		if(cin){	// 整数を取得したので、それを確認する
			if(1 <= n && n <= 10) break;
			cout << "Sorry " << n << " is not in the [1:10] range; please try agein\n";
		}
		else if(cin.fail()){	// 整数でないものが検出された
			cin.clear();		// 状態をgoodに戻す
								// 文字を調べたい
			cout << "Sorry, that was not a number; please try agein\n";
			char ch;
			while(cin >> ch && !isdigit(ch));	// 数字でないものを破棄する
			if(!cin) throw runtime_error("no input");
			cin.unget();	// 数字を戻して、読み取れるようにする
		}
		else{
			throw runtime_error("no input");	// eofまたはbadなので、断念する
		}
	}
	// ここに到達した場合、nは[1:10]の範囲内である
}