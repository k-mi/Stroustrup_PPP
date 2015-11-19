// gccでは -std=c++11オブションが必要

#include <iostream>
#include <vector>
using namespace std;

// c++11から可能になった初期化の表記
vector<int> gv = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

int factorial(int n){
	return n > 1 ? n * factorial(n - 1) : 1;
}

void f(vector<int>& gv){
	// a
	vector<int> lv(gv.size());

	// b
	lv = gv;

	// c
	for(int i = 0; i < lv.size(); ++i)
		cout << lv[i] << ' ';
	cout << endl;

	// d
	vector<int> lv2 = gv;

	// e
	for(int i = 0; i < lv2.size(); ++i)
		cout << lv2[i] << ' ';
	cout << endl;
}

int main(){
	// a
	f(gv);

	// b
	vector<int> vv(10);
	for(int i = 0; i < vv.size(); ++i)
		vv[i] = factorial(i + 1);

	// c
	f(vv);
}