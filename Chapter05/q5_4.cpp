#include "std_lib_facilities.h"

// 摂氏(℃)を華氏（℉）に変換する
double ctok(double c){
	if(c < -273.15) 
		error("ctok()の引数cが絶対零度-273.15℃を下回ります。");

	double k = c * 1.8 + 32;
	return k;
}

int main(){
	double c = 0;			// 入力変数を宣言する
	cin >> c;				// 気温値を入力変数に取り出す
	double k = ctok(c);		// 気温値を変換する
	cout << k << endl;		// 気温値を出力する
}