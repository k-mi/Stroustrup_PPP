#include <iostream>
using namespace std;

int main(){
	// 静的記憶域
	static int static1;
	static int static2;
	cout << "static: " << endl << &static1 << endl << &static2 << endl;

	// スタック
	int auto1;
	int auto2;
	cout << "auto: " << endl << &auto1 << endl << &auto2 << endl;

	// フリーストア
	int* variable1 = new int(10);
	int* variable2 = new int(20);
	cout << "variable: " << endl << &variable1 << endl << &variable2 << endl;

	// 配列
	int* array1 = new int[10];
	int* array2 = new int[1000000];
	cout << "small array: " << endl << array1 << endl << &array1[9] << endl;
	cout << "big array: " << endl << array2 << endl << &array2[999999] << endl;
}	