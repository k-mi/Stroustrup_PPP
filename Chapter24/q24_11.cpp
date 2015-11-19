#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"

namespace Numeric_lib{
	// 注意: Matrix.hの相当するクラスメンバに宣言を追加する必要あり
	// （もともとあるswap_rowsは1次元のMatrixでは使用不可？）
	template<class T> void Matrix<T,1>::swap_columns(Index i, Index j){
		if(i == j) return;
		if(0 > i || i >= d1 || 0 > j || j >= d1) return;

		std::swap((*this)(i), (*this)(j));	// 通常のswapと同じ
	}

	template<class T> void Matrix<T,2>::swap_columns(Index i, Index j){
		if(i == j) return;
		if(0 > i || i >= d1 || 0 > j || j >= d1) return;

		for(Index index = 0; index < d2; ++index)
			std::swap((*this)(index, i), (*this)(index, j));
	}

	template<class T> void Matrix<T,3>::swap_columns(Index i, Index j){
		if(i == j) return;
		if(0 > i || i >= d2 || 0 > j || j >= d2) return;

		for(Index index = 0; index < d2; ++index)
			std::swap((*this)(index, i), (*this)(index, j));
	}

}

int main(){
	using namespace std;
	using namespace Numeric_lib;

	Matrix<double, 1> m1(5);
	for(int i = 0; i < m1.dim1(); ++i)
		m1[i] = i;
	cout << "m1 = " << m1 << endl;
	m1.swap_columns(1, 4);
	cout << "m1 = " << m1 << endl;

	Matrix<double, 2> m2(5, 5);
	for(int i = 0; i < m2.dim1(); ++i)
		for(int j = 0; j < m2.dim2(); ++j)
			m2[i][j] = i * j;

	m2.swap_columns(1, 4);
	cout << m2 << endl;
}
