#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace Numeric_lib;

int main(){
	Matrix<int> a(10);
	Matrix<int> b(100);
	Matrix<double> c(10);
	Matrix<int, 2> d(10, 10);
	Matrix<int, 3> e(10, 10, 10);

	// サイズ
	cout << "a: " << sizeof(a) << endl;
	cout << "b: " << sizeof(b) << endl;
	cout << "c: " << sizeof(c) << endl;
	cout << "d: " << sizeof(d) << endl;
	cout << "e: " << sizeof(e) << endl;
}