// ファーストネームの読み取りと書き込み	

#include "std_lib_facilities.h"

int main(){
	cout << "Please enter your first name (followed by 'enter'):\n";
	string first_name;	// first_nameはstring型の変数
	cin >> first_name;	// 文字をfirst_nameに読み込む
	cout << "Hello, " << first_name << "!\n";
}