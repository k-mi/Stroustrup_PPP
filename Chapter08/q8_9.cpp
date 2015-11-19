#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

int x = 2;	// 初期値 (x >= 0)

int randint(){
	int a = 91;	// 乗数 (a >= 2)
	int c = 23;	// 増分 (c >= 1)
	int m = numeric_limits<int>::max();	// 法 (m >= 1) → MAXINT(2147483647)

	x = abs((a * x + c) % m);
	return x;
}

int rand_in_range(int a, int b){
	return randint() % (b - a) + a;
}

int main(){
	cout << "seed > ";
	cin >> x;
	
	for(int i = 0; i < 40; ++i)
		cout << rand_in_range(20, 30) << ' ';	
	cout << endl;
}