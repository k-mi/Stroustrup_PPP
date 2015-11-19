#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"
using namespace std;
using namespace Numeric_lib;

template<class T> struct triple{
	T operator()(T& i){
		return i *= 3;
	}
};

int main(){
	Matrix<int> a(5);
	for(int i = 0; i < a.size(); ++i) a[i] = i + 1;
	cout << a << endl;

	cout << apply(triple<int>(), a) << endl;	// 3倍
	cout << a << endl;

	a.apply(triple<int>());						// 3倍
	cout << a << endl;
}