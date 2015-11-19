// 名前と年齢の読み取り（第2バージョン）

#include "std_lib_facilities.h"

int main(){
	cout << "Please enter your first name and age\n";
	string first_name = "???";	// 文字列変数（"???"は「名前がわからない」ことを意味する）
	int age = -1;				// 整数変数（-1は「年齢がわからない」ことを意味する）
	cin >> first_name;			// 文字列の読み取り
	cin >> age;					// 整数の読み取り
	cout << "Hello, " << first_name << " (age " << age << ")\n";
}