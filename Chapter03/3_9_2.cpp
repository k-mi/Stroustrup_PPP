#include "std_lib_facilities.h"

int main(){
	double d = 0;
	while(cin >> d){					// 数字を入力している間、以下の文を繰り返し実行する
		int i = d;						// doubleからintへの変換を試みる
		char c = i;						// intからcharへの変換を試みる
		int i2 = c;						// 文字の整数値を取得する
		cout << "d==" << d				// 元のdouble値
			 << " i==" << i 			// intへの変換
			 << " i2==" << i2			// charのint値
			 << " char(" << c << ")\n";	// char
	}
}