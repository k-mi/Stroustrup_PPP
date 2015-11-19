// 名前と年齢の読み取り

#include "std_lib_facilities.h"

int main(){
	cout << "Please enter your first name and age\n";
	string first_name;	// 文字列変数
	int age;			// 整数変数
	cin >> first_name;	// 文字列の読み取り
	cin >> age;			// 整数の読み取り
	cout << "Hello, " << first_name << " (age " << age << ")\n";
}