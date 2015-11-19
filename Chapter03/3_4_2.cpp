// ファーストネームとセカンドネームの読み取り

#include "std_lib_facilities.h"

int main(){
	cout << "Please enter your first and second names\n";
	string first;
	string second;
	cin >> first >> second;				// 2つの文字列を読み取る
	string name = first + ' ' + second;	// 文字列を連結する
	cout << "Hello, " << name << '\n';
}