#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"
using namespace std;
using namespace Numeric_lib;

Matrix<double> operator*(Matrix<double, 2>& m1, Matrix<double>& m2){
	if(m1.dim1() != m2.dim1()) throw runtime_error("invalid expression");

	Matrix<double> m(m2.dim1());
	for(Index i = 0; i < m1.dim2(); ++i)
		for(Index j = 0; j < m1.dim1(); ++j)
			m[i] += m1[i][j] * m2[j];

	return m;
}

Matrix<double, 1> operator+(Matrix<double, 1>& m1, Matrix<double, 1>& m2){
	if(m1.dim1() != m2.dim1()) 
		throw runtime_error("invalid expression");	

	Matrix<double> m(m1.dim1());
	for(Index i = 0; i < m1.dim1(); ++i)
		m[i] = m1[i] + m2[i];

	return m;
}

Matrix<double, 2> operator+(Matrix<double, 2>& m1, Matrix<double, 2>& m2){
	if(m1.dim1() != m2.dim1() || m1.dim2() != m2.dim2()) 
		throw runtime_error("invalid expression");	

	Matrix<double, 2> m(m1.dim1(), m1.dim2());
	for(Index i = 0; i < m1.dim1(); ++i)
		for(Index j = 0; j < m1.dim2(); ++j)
			m(i, j) = m1(i, j) + m2(i, j);

	return m;
}

Matrix<double, 3> operator+(Matrix<double, 3>& m1, Matrix<double, 3>& m2){
	if(m1.dim1() != m2.dim1() || m1.dim2() != m2.dim2() || m1.dim3() != m2.dim3()) 
		throw runtime_error("invalid expression");	

	Matrix<double, 3> m(m1.dim1(), m1.dim2(), m1.dim3());
	for(Index i = 0; i < m1.dim1(); ++i)
		for(Index j = 0; j < m1.dim2(); ++j)
			for(Index k = 0; k < m1.dim3(); ++k)
				m(i, j, k) = m1(i, j, k) + m2(i, j, k);

	return m;
}

int main(){
	int n;
	cout << "input n: ";
	cin >> n;

	Matrix<double> m1(n);
	Matrix<double, 2> m2(n, n);

	cout << "input m1: " << endl;
	cin >> m1;
	cout << "input m2: " << endl;
	cin >> m2;

	cout << "m1 * m2 = " << m2 * m1 << endl;

	cout << "m1 + m1 = " << m1 + m1 << endl;
	cout << "m2 + m2 = " << m2 + m2 << endl;
}