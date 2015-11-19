#include <iostream>
#include <cctype>
#include <stdexcept>
using namespace std;

void skip_to_int(){	
	if(cin.fail()){		// 整数でないものが検出された
		cin.clear();	// 文字を調べたい
		char ch;
		while(cin >> ch){		// 数字でないものを破棄する
			if(isdigit(ch) || ch == '-'){
				cin.unget();	// 数字を戻して、読み取れるようにする
				return;
			}
		}	
		throw runtime_error("no input");	// eofまたはbadなので、断念する
	}
}

int main(){
	cout << "Please enter an integer in the range 1 to 10 (inclusice):\n";
	int n = 0;
	while(true){
		cin >> n;
		if(cin){	// 整数を取得したので、それを確認する
			if(1 <= n && n <= 10) break;
			cout << "Sorry " << n << " is not in the [1:10] range; please try agein\n";
		}
		else{		// 整数でないものが検出された
			cout << "Sorry, that was not a number; please try agein\n";
			skip_to_int();
		}
	}
	// ここに到達した場合、nは[1:10]の範囲内である
}