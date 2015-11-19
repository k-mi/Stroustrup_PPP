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

	// 要素の数
	cout << "a: " << a.size() << endl;
	cout << "b: " << b.size() << endl;
	cout << "c: " << c.size() << endl;
	cout << "d: " << d.size() << endl;
	cout << "e: " << e.size() << endl;
}