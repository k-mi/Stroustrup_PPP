#include <iostream>
#include "Matrix.h"
using namespace std;
using namespace Numeric_lib;

void f(int n1, int n2, int n3){
	Matrix<double, 1> ad1(n1);	// 要素はdouble、1次元
	Matrix<int, 1> ai1(n1);		// 要素はint、1次元

	ad1(7) = 0;					// ()を使った添え字（Fortranスタイル）
	ad1[7] = 8;					// []でもうまくいく（Cスタイル）

	Matrix<double, 2> ad2(n1, n2);		// 2次元
	Matrix<double, 3> ad3(n1, n2, n3);	// 3次元
	ad2(3, 4) = 7.5;					// 多次元の添え字
	ad3(3, 4, 5) = 9.2;
}

int main(){
	int n1, n2, n3;		// n1 >= 8, n2 >= 5, n3 >= 6
	cin >> n1 >> n2 >> n3;
	
	f(n1, n2, n3);
}