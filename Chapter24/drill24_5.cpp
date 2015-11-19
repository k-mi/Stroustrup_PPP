#include <iostream>
#include "Matrix.h"
#include "MatrixIO.h"
using namespace std;
using namespace Numeric_lib;

int main(){
	Matrix<double> matrix(10);

	for(int i = 0; i < matrix.size(); ++i)
		cin >> matrix[i];

	cout << matrix << endl;
}