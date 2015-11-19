#include <iostream>
using namespace std;

void infinite(){
	unsigned char max = 160;	// 非常に大きい

	// iが01111111(2) = 127(10)の時に1加算すると
	// オーバーフローして10000000(2) = -128となり
	// max = 160以上になることがないため無限ループ
	for(signed char i = 0; i < max; ++i)
		cout << int(i) << '\n';
}

int main(){
	infinite();	// 無限ループ
}