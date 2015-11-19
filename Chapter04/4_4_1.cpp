#include "std_lib_facilities.h"

int main(){
	int a = 0;
	int b = 0;
	cout << "Please enter two integers\n";
	cin >> a >> b;

	if(a < b)	// 条件
				// 1つ目の選択肢（条件がtrueの場合に選択される）
		cout << "max(" << a << ", " << b << ") is " << b << "\n";
	else		// 2つ目の選択肢（条件がfalseの場合に選択される）
		cout << "max(" << a << ", " << b << ") is " << a << "\n";
}