#include <iostream>
#include <cstring>	// memcpy
using namespace std;

int ga[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

int factorial(int n){
	return n > 1 ? n * factorial(n - 1) : 1;
}

// aにint型の配列を、sizeにaの要素数を引数にとる
void f(int* a, int size){
	// a
	int la[10];

	// b
	memcpy(la, a, size * sizeof(*a));

	// c
	for(int i = 0; i < size; ++i)
		cout << la[i] << ' ';
	cout << endl;

	// d
	int* p = new int[size];

	// e
	memcpy(p, a, sizeof(a) * size);

	// f
	for(int i = 0; i < size; ++i)
		cout << la[i] << ' ';
	cout << endl;

	// g
	delete[] p;
}

int main(){
	// a
	f(ga, sizeof(ga) / sizeof(ga[0]));

	// b
	const int aa_size = 10;
	int aa[aa_size];
	for(int i = 0; i < aa_size; ++i)
		aa[i] = factorial(i+1);

	// c
	f(aa, aa_size);
}