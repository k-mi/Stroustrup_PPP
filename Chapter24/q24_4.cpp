// 24_6_2とはほぼ同じ
// n = 2, A == { { 0 1 } { 1 0 }, b == { 5 6 } と入力することでq24_5の確認が可能

#include <iostream>
#include <stdexcept>
#include <utility>		// swap (C++11までは<algorithm>)
#include <cmath>		// abs(double)
#include "Matrix.h"
#include "MatrixIO.h"
using namespace std;

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;

void classical_elimination(Matrix& A, Vector& b){
	using namespace Numeric_lib;

	const Index n = A.dim1();
	// 最初の列から最後の次の列までトラバースし、
	// 対角線の下にあるすべての要素を0に設定する
	for(Index j = 0; j < n - 1; ++j){
		const double pivot = A(j, j);
		if(pivot == 0) throw runtime_error("Elim_failure " + to_string(j)); // Elim_failure(j);

		// i番目の行の対角線の下にある要素をそれぞれ0に設定する
		for(Index i = j + 1; i < n; ++i){
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);	// bをそれに合わせて変更する
		}
	}
}

void elim_with_partial_pivot(Matrix& A, Vector& b){
	using namespace Numeric_lib;

	const Index n = A.dim1();

	for(Index j = 0; j < n; ++j){
		Index pivot_row = j;

		// 適切なピボットを検索する
		for(Index k = j + 1; k < n; ++k)
			if(abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = k;

		// より適切なピボットが見つかった場合は行を入れ替える
		if(pivot_row != j){
			A.swap_rows(j, pivot_row);
			swap(b(j), b(pivot_row));
		}	

		// 削除
		for(Index i = j + 1; i < n; ++i){
			const double pivot = A(j, j);
			if(pivot == 0) throw runtime_error("can't solve: pivot == 0");
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);	// bをそれに合わせて変更する
		}
	}
}

Vector back_substitution(const Matrix& A, const Vector& b){
	using namespace Numeric_lib;

	const Index n = A.dim1();
	Vector x(n);

	for(Index i = n - 1; i >= 0; --i){
		double s = b(i) - dot_product(A[i].slice(i+1), x.slice(i+1));

		if(double m = A(i, i))
			x(i) = s / m;
		else
			throw runtime_error("Back_subst_failure " + to_string(i)); //throw Back_subst_failure(i);
	}

	return x;
}

Vector classical_gaussian_elimination(Matrix A, Vector b){
	classical_elimination(A, b);	// 前進消去
	return back_substitution(A, b);	// 後退代入
}

Vector elim_with_partial_pivot_elimination(Matrix A, Vector b){
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

// 行列とベクタの乗算
Vector operator*(const Matrix& m, const Vector& u){
	using namespace Numeric_lib;	
	
	const Index n = m.dim1();
	Vector v(n);
	for(Index i = 0; i < n; ++i) v(i) = dot_product(m[i], u);

	return v;
}

int main(){
	int n;
	cout << "input n: ";
	cin >> n;
	Matrix A(n, n);	// n*nの行列を作成
	Vector b(n);

	cout << "input A:" << endl;
	cin >> A;
	cout << "input b:" << endl;
	cin >> b;

	try{
		Vector x1 = elim_with_partial_pivot_elimination(A, b);
		cout << "partial pivot elim solition is x = " << x1 << endl;
		Vector v1 = A * x1;
		cout << " A * x = " << v1 << endl;

		Vector x2 = classical_gaussian_elimination(A, b);
		cout << "classical elim solition is x = " << x2 << endl;
		Vector v2 = A * x2;
		cout << " A * x = " << v2 << endl;
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
}