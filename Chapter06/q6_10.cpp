#include "std_lib_facilities.h"
#include <cassert>

int factorial(int n){
	assert(n >= 0);

	return n > 0 ? factorial(n-1) * n : 1;
}

int permutation(int a, int b){
	assert(a >= b);
	assert(a >= 0 && b >= 0);

	return factorial(a) / factorial(a-b);
}

int combination(int a, int b){
	assert(a >= b);
	assert(a >= 0 && b >= 0);

	return permutation(a, b) / factorial(b);
}

int main(){
	int a, b;
	cout << "順列・組み合わせの計算を行います。" << endl;
	cout << "2つの数字a, bを入力してください。（a >= b >= 0）" << endl;
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;

	if(a < b)
		error("aよりbの値が大きいです。");
	else if(a < 0 || b < 0)
		error("a, bには0以上の値を指定する必要があります。");

	char mode;
	cout << "順列の計算を行う場合はpを、組み合わせの計算を行う場合はcを入力してください。: ";
	cin >> mode;

	switch(mode){
		case 'p':	// 順列
			cout << permutation(a, b) << endl;
			break;
		case 'c':	// 組み合わせ
			cout << combination(a, b) << endl;
			break;
		default:
			error("正しいモードが選択されませんでした。");
			break;
	}
}