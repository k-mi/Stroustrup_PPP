#include <iostream>
using namespace std;

int main(){
	int i = 0x00000000; 	// オール0
	unsigned int ui = i;
	cout << i << '\t' << ui << endl;

	i = ui = 0xFFFFFFFF;	// オール1
	cout << i << '\t' << ui << endl;

	i = ui = 0xAAAAAAAA;	// 1と0の交互（左端が1）
	cout << i << '\t' << ui << endl;

	i = ui = 0x55555555;	// 1と0の交互（左端が0）
	cout << i << '\t' << ui << endl;

	i = ui = 0xCCCCCCCC;	// 1100...パターン
	cout << i << '\t' << ui << endl;

	i = ui = 0x33333333;	// 0011...パターン
	cout << i << '\t' << ui << endl;

	i = ui = 0xFF00FF00;	// オール1で始まるオール1のバイトとオール0のバイトのパターン
	cout << i << '\t' << ui << endl;

	i = ui = 0x00FF00FF;	// オール0で始まるオール1のバイトとオール0のバイトのパターン
	cout << i << '\t' << ui << endl;
}