// ガウス消去法の過程を表示

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

			// 過程を表示
			cout << "A = " << A << endl;
			cout << "b = " << b << endl;
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
	classical_elimination(A, b);
	return back_substitution(A, b);
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
		Vector x = classical_gaussian_elimination(A, b);
		cout << "classical elim solition is x = " << x << endl;
	}
	catch(const exception& e){
		cerr << e.what() << endl;
	}
}