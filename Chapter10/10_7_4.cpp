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

// cinからintを読み取る
int get_int(){
	int n = 0;
	while(true){
		if(cin >> n) return n;
		cout << "Sorry, that was not a number; please try agein\n";
		skip_to_int();
	}
}

// cinから[low:high]の範囲内のintを読み取る
int get_int(int low, int high){
	cout << "Please enter an integer in the range " << low << " to " << high << " (inclusice):\n";
	while(true){
		int n = get_int();
		if(low <= n && n <= high) return n;
		cout << "Sorry " << n << " is not in the [" << low << ':' << high << "] range; please try agein\n";
	}
}

int main(){
	cout << get_int(1, 10) << endl;
}