#include "std_lib_facilities.h"

int x = 10;
int y = 100;

int f(){
	int x;	// グローバル変数を隠蔽するローカル変数
	x = 7;	// ローカルx
	cout << x << endl;
	{
		int x = y;	// 上記のローカルxを隠蔽
		cout << x << endl;
		++x;
		cout << x << endl;
	} 
	++x;
	cout << x << endl;
	return x;
}

int main(){
	f();
}