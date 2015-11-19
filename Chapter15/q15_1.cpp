#include <iostream>
using namespace std;

// 反復による階乗
int fac1(int n){
	int r = 1;
	while(n > 1){
		r *= n;
		--n;
	}
	return r;
}

// 再帰による階乗
int fac2(int n){
	return n > 1 ? n * fac2(n - 1) : 1;
}

int main(){
	const int max = 15;

	for(int i = 0; i < max; ++i)
		cout << fac1(i) << endl;

	for(int i = 0; i < max; ++i)
		cout << fac2(i) << endl;
}