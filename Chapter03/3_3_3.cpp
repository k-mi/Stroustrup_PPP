#include "std_lib_facilities.h"

int main(){
	cout << "Please enter your first name and age\n";
	string first;
	string second;
	cin >> first >> second;		// 2つの文字列を読み取るり
	cout << "Hello, " << first << ' ' << second << '\n';
}