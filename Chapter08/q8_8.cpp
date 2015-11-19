#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/*
線形合同法により初期値xの乱数列を生成する。

生成される乱数列は、
	1. cとmが互いに素である。（最大公約数が1）
	2. a-1が、mの持つ全ての素因数で割りきれる。
	3. mが4の倍数である場合は、a-1も4の倍数である。
の各条件を満たす場合に最大周期mを持つ。
*/
int x = 2;	// 初期値 (x >= 0)

int randint(){
	int a = 91;	// 乗数 (a >= 2)
	int c = 23;	// 増分 (c >= 1)
	int m = numeric_limits<int>::max();	// 法 (m >= 1) → MAXINT(2147483647)

	x = abs((a * x + c) % m);
	return x;
}

int main(){
	cout << "seed > ";
	cin >> x;

	for(int i = 0; i < 40; ++i)
		cout << randint() << ' ';	
	cout << endl;
}